#include "flightdataarchive.h"
#include <QtQuick/QQuickView>
#include <QApplication>
#include <QFile>
#include <QTableView>
#include <QtQml/QQmlContext>
#include <QDateTime>

FlightDataArchive::FlightDataArchive()
{
    qmlFiles.clear();
    qmlFiles.append("mainWindow.qml");
    qmlFiles.append("settingsWindow.qml");
    qmlFiles.append("WindowButton.qml");
    qmlFiles.append("WindowButtonText.qml");
    qmlFiles.append("TextEditWidget.qml");
    qmlFiles.append("windowAddNew.qml");
    qmlFiles.append("tableModelDescription.qml");
    qmlFiles.append("editObjectWindow.qml");

    init();
}

FlightDataArchive::~FlightDataArchive()
{
    m_db.closeDB();
}

void FlightDataArchive::init()
{

  //это обновление таблицы
  connect(this, SIGNAL(updateView()), this, SLOT(onUpdateView()));

  // Путь к папке, содержащей QML файлы
  QString contentPath;

#ifdef QT_DEBUG
  // В отладочной версии это абсолютный путь к папке проекта
  contentPath = "D:\\progs_git\\FlightData_database_FB042019\\FlightData_Archive";
#else
  // В релизе это путь к папке, в которой расположено приложение
  contentPath = QApplication::applicationDirPath();
#endif

  int errIdx;
  bool resqml = checkAllQMlFiles(contentPath, &errIdx);
  if (!resqml && errIdx != -1)
  {
      //ShowMessageBox(errIdx + 2, critical);
      ::exit(0);
  }

 // setFocusPolicy(Qt::StrongFocus);
  // Изменять размеры QML объекта под размеры окна
  // Возможно делать и наоборот,
  // передавая QDeclarativeView::SizeViewToRootObject
  setResizeMode(QQuickView::SizeRootObjectToView);

  // Загрузить QML файл
  setSource(QUrl::fromLocalFile(contentPath + "/mainWindow.qml"));

  rootContext()->setContextProperty("window", this);

  //setWindowFlags(Qt::CustomizeWindowHint |  Qt::WindowMinMaxButtonsHint);

  //читаем настройки, если что жёстко закрываем
  ws.setFileName(contentPath + QString("\\config\\config.ini"));
  int res = ws.initSets();
  if (res != SUCCESS)
      ::exit(0);

  ///блок с базами данных

  //после инициализации устанавливаем настройки базы данных
  m_db.setSqlSets(ws.getValue().database_param);

  //а есть ли такой файл?
  if (!QFile(m_db.getSqlSets().dbName).open(QIODevice::ReadOnly))
      //ShowMessageBox(10, warning);
  {}
  else
      QFile(m_db.getSqlSets().dbName).close();

  m_db.openDB();
  if (!m_db.isActive())
  {
      //ShowMessageBox(9, critical);
      ::exit(0);
  }

  //проверка базы данных на наличие таблиц
  QString resStr;
  res = checkTablesDB(&resStr);
  if (res != SUCCESS)
  {
      //ShowMessageBox(9, critical);
  }

  rootContext()->setContextProperty("table", &m_tbl);

  ///конец блока с базами данных

  //инициализируем окно настроек
  res = ws.init(contentPath, "/settingsWindow.qml", "windowSets");
  if (res == SUCCESS)
  {
      ws.settingsToWindow(ws.getValue());
      hide();
  }

  res = ws.ew.init(contentPath, "/editObjectWindow.qml", "windowSetsType");
  if (res == SUCCESS)
  {
      ws.ew.hide();
      ws.ew.setEdit(noneEdit);
  }

  connect(&ws, SIGNAL(onClose()), this, SLOT(closeSets()));
  connect(&ws.ew, SIGNAL(onClose()), this, SLOT(closeSetsE()));
  connect(&ws.ew, SIGNAL(newRec(QVariantMap)), this, SLOT(onWriteNewType(QVariantMap)));
  connect(this, SIGNAL(rlsInfoRead(QStringList, int, int)), &ws.ew, SLOT(newRecs(QStringList,int,int)));
   connect(&ws.ew, SIGNAL(updateFromMain(QString, int)), this, SLOT(updateTS(QString, int)));

  //инициализируем окно добавления нового полёта
  res = wa.init(contentPath, "/windowAddNew.qml", "windowAdd");
  if (res == SUCCESS)
      hide();

  connect(&wa, SIGNAL(onClose()), this, SLOT(closeAdd()));
  connect(&wa, SIGNAL(writeNewDB(QVariantMap)), this, SLOT(onWriteNewDB(QVariantMap)));
  connect(this, SIGNAL(rlsInfoRead(QStringList, int, int)), &wa, SLOT(newRecs(QStringList,int,int)));
  connect(&wa, SIGNAL(updateFromMain(QString, int)), this, SLOT(updateTS(QString, int)));

  //заполним главную таблицу
  emit updateView();

  //инициализация окна добавления и описания входных и выходных файлов
  res = wa.w_dsc_input.init(contentPath, "/tableModelDescription.qml", "tableModelDesc");
  if (res == SUCCESS)
  {
      wa.w_dsc_input.hide();
      wa.w_dsc_input.setInputOutput(INPUT_FILES);
  }

  res = wa.w_dsc_output.init(contentPath, "/tableModelDescription.qml", "tableModelDesc");
  if (res == SUCCESS)
  {
      wa.w_dsc_output.hide();
      wa.w_dsc_output.setInputOutput(OUTPUT_FILES);
  }

  connect(&wa.w_dsc_input, SIGNAL(onClose()), this, SLOT(closeWi()));
  connect(&wa.w_dsc_output, SIGNAL(onClose()), this, SLOT(closeWo()));

  connect(this, SIGNAL(iChanged(QString)), &wa.w_dsc_input, SLOT(onNewDBName(QString)));
  connect(this, SIGNAL(oChanged(QString)), &wa.w_dsc_output, SLOT(onNewDBName(QString)));

}

//а если из других форм пришел запрос, то другой сигнал
void FlightDataArchive::updateTS(QString txt, int w)
{
    return onCurrentTextChanged(txt, w);
}

//изменили позицию, а значит и ТС
void FlightDataArchive::onCurrentTextChanged(QString txt, int w)
{
    if (!txt.isEmpty())
    {
        QStringList nameCoords;
        QSqlQuery q;
        q.clear();
        QVariantMap WhereParams;
        WhereParams.clear();
        WhereParams["parentPlace"] = txt;

        if (m_db.selectParamsFromTableWhereParams("name_coords", STATE_POINTS_DATABASE_NAME, WhereParams, &q))
        {
            while (q.next())
                nameCoords.append(q.value(0).toString());

            emit rlsInfoRead(nameCoords, COORDS, w);
        }
        else
        {
            /// @todo - ошибка чтения
        }
    }

    return;
}

//обновим таблицу
void FlightDataArchive::onUpdateView()
{
    m_tbl.setQuery(QSqlQuery(QString("SELECT date, type, placeStr, description FROM %1;").arg(GENERAL_DATABASE_NAME)));

    //выберем все типы станций и места испытаний
    QSqlQuery q;
    q.clear();

    QStringList result, resPlaces;
    result.clear();
    resPlaces.clear();

    QVector<int>who;
    who.clear();
    who.append(MAIN_WINDOW);
    who.append(ADD_WINDOW);
    who.append(SETTINGS_WINDOW);

    if (m_db.selectParamsFromTable("type", RLS_TYPE_DATABASE_NAME, &q))
    {
        while (q.next())
            result.append(q.value(0).toString());
        emitAll(result, TYPE, who);
    }
    else
    {
        /// @todo - ошибка чтения
    }

    q.clear();
    if (m_db.selectParamsFromTable("place", PLACE_DATABASE_NAME, &q))
    {
        while (q.next())
            resPlaces.append(q.value(0).toString());
        emitAll(resPlaces, PLACE, who);
    }
    else
    {
        /// @todo - ошибка чтения
    }

    if (!resPlaces.isEmpty())
    {
        //первый параметр по умолчанию
        foreach (int i, who)
        {
            if (i == SETTINGS_WINDOW)
            {
                q.clear();
                QStringList coords;
                coords.clear();
                if (m_db.selectParamsFromTable("name_coords", STATE_POINTS_DATABASE_NAME, &q))
                {
                    while (q.next())
                        coords.append(q.value(0).toString());
                    emit rlsInfoRead(coords, COORDS, i);
                }
                else
                {
                    ///@todo - error not opened!!!

                }
            }
            else
                onCurrentTextChanged(resPlaces.at(0), who.at(i));
        }
    }

    return;
}

//отправить сигнал нужным абонентам
void FlightDataArchive::emitAll(QStringList l, int t, QVector<int> who)
{
    if (who.isEmpty() || l.isEmpty())
        return;
    for (int j = 0; j < who.count(); j++)
        emit rlsInfoRead(l, t, who.at(j));
    return;
}

void FlightDataArchive::closeWi()
{
    slCloseOrEnable(nonecl);
    wa.w_dsc_input.hide();
}

void FlightDataArchive::closeWo()
{
    slCloseOrEnable(nonecl);
    wa.w_dsc_output.hide();
}


//запись нового типа в БД
int FlightDataArchive::onWriteNewType(QVariantMap _map)
{
    QString dbName;
    dbName.clear();

    WhoEdit e = (WhoEdit)_map.value("who").toInt();

    switch (e)
    {
    case rlsEdit:
        dbName = RLS_TYPE_DATABASE_NAME;
        break;
    case placeEdit:
        dbName = PLACE_DATABASE_NAME;
        break;
    case tsEdit:
        dbName = STATE_POINTS_DATABASE_NAME;
        break;
    default:
        return -1;
        break;
    }

    if (m_db.checkTable(dbName) == SUCCESS)
    {
        QVariantMap newWrite;
        newWrite.clear();

        newWrite["description"] = _map.value("description").toString();
        QString name = _map.value("name").toString();
        QString id_name;
        QString nn;
        switch (e)
        {
        case rlsEdit:
            newWrite["type"] = name;
            id_name = "id_types";
            nn = "type";
            break;
        case placeEdit:
            newWrite["place"] = name;
            id_name = "id_place";
            nn = "place";
            break;
        case tsEdit:
            newWrite["name_coords"] = name;
            newWrite["latitude"] = _map.value("latitude").toFloat();
            newWrite["longitude"] = _map.value("longitude").toFloat();
            newWrite["parentPlace"] = _map.value("place").toString();
            id_name = "id_coords";
            nn = "name_coords";
            break;
        default:
            break;
        }

        bool nw = _map.value("newWrite").toBool();
        if (nw)
        {
            if (!m_db.insertParamsInTable(newWrite, dbName))
            {
                return -2;
                ///@todo - error;
            }
            else
            {
                emit updateView();
                ///@warning  - message;
            }
        }
        else
        {
            int id = 0;
            QVariantMap whereParams;
            QVariantMap ids;
            ids.clear();
            whereParams.clear();
            whereParams[nn] = name;
            QSqlQuery q;
            q.clear();
            if (m_db.selectParamsFromTableWhereParams(id_name, dbName, whereParams, &q))
            {
                while (q.next())
                    id = q.value(0).toInt();

                ids[id_name] = id;
                if (!m_db.updateParamsInTable(newWrite, dbName, ids))
                {
                    return -2;
                    ///@todo - error;
                }
                else
                {
                    emit updateView();
                    ///@warning  - message;
                }
            }
        }


    }
    else
        return -10;

    return SUCCESS;
}


//запись новой строки в основную базу!!!
int FlightDataArchive::onWriteNewDB(QVariantMap _map)
{
    if (m_db.checkTable(GENERAL_DATABASE_NAME) == SUCCESS)
    {

        QVariantMap newWrite;
        newWrite.clear();

        QString dateIO;
        if (_map.value("date").toString().length() < 10)
        {
            ///@todo show message
            dateIO = _map.value("date").toString();
        }
        else
            dateIO = _map.value("date").toString().left(10);

        QSqlQuery q;
        q.clear();
        QVariantMap tp;
        tp.clear();

        //база точек стояния
        tp.clear();
        tp["name_coords"] = _map.value("ts").toString();
        q.clear();
        QStringList coords;
        coords.clear();
        coords.append("latitude");
        coords.append("longitude");
        QVector<float> geo;
        geo.clear();
        geo.resize(2);
        int ii = 0;
        if (m_db.selectParamsFromTableWhereParams(coords, STATE_POINTS_DATABASE_NAME, tp, &q))
        {
            while (q.next())
            {
                if (ii > 1)
                    break;
                geo.replace(ii, q.value(0).toFloat());
                ii++;
            }
        }
        else
        {
            return -1;
            ///@todo - error
        }

        srand((unsigned int)QDateTime::currentDateTime().toTime_t());
        QString nameInput = QString("i_%1_%2_%3").arg(dateIO).arg(_map.value("type").toString()).arg(rand());
        QString nameOutput = QString("o_%1_%2_%3").arg(dateIO).arg(_map.value("type").toString()).arg(rand());


        //формируем окончательный запрос
        newWrite["date"] = QDateTime::fromString(_map.value("date").toString(), "yyyy-MM-dd hh:mm:ss");
        newWrite["type"] = _map.value("type").toString();;
        newWrite["input_files_table"] = nameInput;
        newWrite["output_files_table"] = nameOutput;
        newWrite["placeStr"] = _map.value("place").toString();
        newWrite["latitude"] = geo.at(0);
        newWrite["longitude"] = geo.at(1);
        newWrite["description"] = _map.value("message").toString();

        if (!m_db.insertParamsInTable(newWrite, GENERAL_DATABASE_NAME))
        {
            return -2;
            ///@todo - error;
        }
        else
        {
            emit iChanged(nameInput);
            emit oChanged(nameOutput);
            emit updateView();
            ///@warning  - message;
        }

    }
    else
        return -10;

    return SUCCESS;
}


//проверка и создание таблиц
int FlightDataArchive::checkTablesDB(QString *resName)
{
    resName->clear();
    int res = -1;

    if (m_db.checkTable(GENERAL_DATABASE_NAME) != SUCCESS)
    {
        QVariantMap _map;
        _map.clear();
        _map["id_table"] = "INTEGER";
        _map["date"] = "DATETIME";
        _map["type"] = "NVARCHAR(20)";
        _map["input_files_table"] = "NVARCHAR(60)";
        _map["output_files_table"] = "NVARCHAR(60)";
        _map["placeStr"] = "NVARCHAR(20)";
        _map["latitude"] = "FLOAT";
        _map["longitude"] = "FLOAT";
        _map["description"] = "NVARCHAR";

        QStringList autoInc;
        autoInc.clear();
        autoInc.append("id_table");

        res = m_db.createTableIfNeed(GENERAL_DATABASE_NAME, _map, autoInc);

        if (res != SUCCESS)
        {
            resName->append(GENERAL_DATABASE_NAME);
            return -1;
        }
    }

    if (m_db.checkTable(RLS_TYPE_DATABASE_NAME) != SUCCESS)
    {
        QVariantMap _map;
        _map.clear();
        _map["id_type"] = "INTEGER";
        _map["type"] = "NVARCHAR(20)";
        _map["description"] = "NVARCHAR";

        QStringList autoInc;
        autoInc.clear();
        autoInc.append("id_type");

        res = m_db.createTableIfNeed(RLS_TYPE_DATABASE_NAME, _map, autoInc);

        if (res != SUCCESS)
        {
            resName->append(RLS_TYPE_DATABASE_NAME);
            return -1;
        }
    }

    if (m_db.checkTable(PLACE_DATABASE_NAME) != SUCCESS)
    {
        QVariantMap _map;
        _map.clear();
        _map["id_place"] = "INTEGER";
        _map["place"] = "NVARCHAR(20)";
        _map["description"] = "NVARCHAR";

        QStringList autoInc;
        autoInc.clear();
        autoInc.append("id_place");

        res = m_db.createTableIfNeed(PLACE_DATABASE_NAME, _map, autoInc);

        if (res != SUCCESS)
        {
            resName->append(PLACE_DATABASE_NAME);
            return -1;
        }
    }

    if (m_db.checkTable(STATE_POINTS_DATABASE_NAME) != SUCCESS)
    {
        QVariantMap _map;
        _map.clear();
        _map["id_coords"] = "INTEGER";
        _map["name_coords"] = "NVARCHAR(20)";
        _map["parentPlace"] = "NVARCHAR(20)";
        _map["latitude"] = "FLOAT";
        _map["longitude"] = "FLOAT";
        _map["description"] = "NVARCHAR";

        QStringList autoInc;
        autoInc.clear();
        autoInc.append("id_coords");

        res = m_db.createTableIfNeed(STATE_POINTS_DATABASE_NAME, _map, autoInc);

        if (res != SUCCESS)
        {
            resName->append(STATE_POINTS_DATABASE_NAME);
            return -1;
        }
    }

    return SUCCESS;
}

//проверка всех файлов
bool FlightDataArchive::checkAllQMlFiles(QString dir, int *idx)
{
    *idx = -1;
    bool op = true;
    for (int i = 0; i < qmlFiles.length(); i++)
    {
        //проверка валидности файла настроек
        QFile sets(dir.append("\\").append(qmlFiles.at(i)));
        bool op = sets.open(QIODevice::ReadWrite);
        if (!op || !sets.isReadable() || !sets.isWritable())
        {
            op = false;
            *idx = i;
            if (sets.isOpen())
                sets.close();
            break;
        }
        if (sets.isOpen())
            sets.close();
    }
    return op;
}

//закрытие приложения
void FlightDataArchive::quit()
{
    QApplication::quit();
}

//показываем настройки
void FlightDataArchive::showSets()
{
    slCloseOrEnable(enableT);
    ws.show();
}

//показываем добавить новый полёт
void FlightDataArchive::showAdd()
{
    slCloseOrEnable(enableT);
    wa.setftype(newRecord);
    wa.show();
}

//закрытие настроек
void FlightDataArchive::closeSets()
{
    slCloseOrEnable(nonecl);
    ws.hide();
}

//закрытие настроек
void FlightDataArchive::closeSetsE()
{
    slCloseOrEnable(nonecl);
    ws.ew.hide();
}


//закрытие настроек
void FlightDataArchive::closeAdd()
{
    slCloseOrEnable(nonecl);
    wa.hide();
}

//закрыть или сделать неактивным
void FlightDataArchive::slCloseOrEnable(closeEnable t)
{
    Q_UNUSED(enableAll);

    switch (t)
    {
    case nonecl:
        //setEnabled(true);
        break;
    case closeT:
        quit();
        break;
    case enableT:
        //setEnabled(false);
        break;
    default:
        break;
    }
}
