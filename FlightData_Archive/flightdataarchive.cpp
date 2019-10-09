#include "flightdataarchive.h"
#include <QtQuick/QQuickView>
#include <QApplication>
#include <QFile>
#include <QTableView>
#include <QtQml/QQmlContext>
#include <QDateTime>
#include <QFileInfo>
#include <QDir>

FlightDataArchive::FlightDataArchive()
{
    qmlFiles.clear();
    qmlFiles.append("/qml/mainWindow.qml");
    qmlFiles.append("/qml/settingsWindow.qml");
    qmlFiles.append("/qml/WindowButton.qml");
    qmlFiles.append("/qml/WindowButtonText.qml");
    qmlFiles.append("/qml/TextEditWidget.qml");
    qmlFiles.append("/qml/windowAddNew.qml");
    qmlFiles.append("/qml/tableModelDescription.qml");
    qmlFiles.append("/qml/editObjectWindow.qml");
    qmlFiles.append("/qml/progressBar.qml");
    qmlFiles.append("/qml/FileDialogDef.qml");

    //а внесли ли мы изменения?
    currentDB.clear();
    connect(this, SIGNAL(newWriteDel()), this, SLOT(isSave()));

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
  contentPath = "D:\\progs_git\\FlightData_archive_FB052019\\FlightData_Archive";
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

  // Изменять размеры QML объекта под размеры окна
  // Возможно делать и наоборот,
  // передавая QDeclarativeView::SizeViewToRootObject
  setResizeMode(QQuickView::SizeRootObjectToView);

  // Загрузить QML файл
  setSource(QUrl::fromLocalFile(QString(contentPath).append(qmlFiles.at(0))));

  rootContext()->setContextProperty("window", this);

  //читаем настройки, если что жёстко закрываем
  ws.setFileName(contentPath + QString("\\config\\config.ini"));
  int res = ws.initSets();
  if (res != SUCCESS)
      ::exit(0);

  ///блок с прогресс баром
  //инициализируем окно настроек
  res = winitial.init(contentPath, qmlFiles.at(8), "initialW");
  connect(&winitial, SIGNAL(onClose()), this, SLOT(closeIW()));
  connect(this, SIGNAL(initialText(bool)), &winitial, SLOT(chText(bool)));
  if (res == SUCCESS)
  {
      bool res = TryCopyDB(false, ws.getValue().dbFile, contentPath);
      if (!res)
      {
          ///@todo - continue with current
      }
  }
  else
  {
      slCloseOrEnable(nonecl);
      ///@todo - no init pb
  }

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
  //проверим размер (надо ли сохранять?)
  emit newWriteDel();

  rootContext()->setContextProperty("table", &m_tbl);

  ///конец блока с базами данных

  //инициализируем окно настроек
  res = ws.init(contentPath, qmlFiles.at(1), "windowSets");
  if (res == SUCCESS)
  {
      ws.settingsToWindow(ws.getValue());
      hide();
  }

  res = ws.ew.init(contentPath, qmlFiles.at(7), "windowSetsType");
  if (res == SUCCESS)
  {
      ws.ew.hide();
      ws.ew.setEdit(noneEdit);
  }

  connect(&ws, SIGNAL(onClose()), this, SLOT(closeSets()));
  connect(&ws.ew, SIGNAL(onClose()), this, SLOT(closeSetsE()));
  connect(&ws.ew, SIGNAL(onClose()), &ws, SLOT(slotWinEnabled()));
  connect(&ws.ew, SIGNAL(newRec(QVariantMap)), this, SLOT(onWriteNewType(QVariantMap)));
  connect(this, SIGNAL(rlsInfoRead(QStringList, int, int)), &ws.ew, SLOT(newRecs(QStringList,int,int)));
  connect(&ws.ew, SIGNAL(updateFromMain(QString, int)), this, SLOT(updateTS(QString, int)));
  connect(&ws.ew, SIGNAL(loadCurrentInfoFromDB(int, QString)), this, SLOT(onUpdateInfoForSettings(int, QString)));

  //инициализируем окно добавления нового полёта
  res = wa.init(contentPath, qmlFiles.at(5), "windowAdd");
  if (res == SUCCESS)
      hide();

  connect(&wa, SIGNAL(onClose()), this, SLOT(closeAdd()));
  connect(&wa, SIGNAL(writeNewDB(QVariantMap, int)), this, SLOT(onWriteNewDB(QVariantMap, int)));
  connect(this, SIGNAL(rlsInfoRead(QStringList, int, int)), &wa, SLOT(newRecs(QStringList,int,int)));
  connect(&wa, SIGNAL(updateFromMain(QString, int)), this, SLOT(updateTS(QString, int)));

  //заполним главную таблицу
  emit updateView();

  //инициализация окна добавления и описания входных и выходных файлов
  res = wa.w_dsc_input.init(contentPath, qmlFiles.at(6), "tableModelDesc");
  if (res == SUCCESS)
  {
      wa.w_dsc_input.hide();
      wa.w_dsc_input.setInputOutput(INPUT_FILES);
  }

  res = wa.w_dsc_output.init(contentPath, qmlFiles.at(6), "tableModelDesc");
  if (res == SUCCESS)
  {
      wa.w_dsc_output.hide();
      wa.w_dsc_output.setInputOutput(OUTPUT_FILES);
  }

  //все связи таблицы со входными и выходными файлами
  connect(&wa.w_dsc_input, SIGNAL(onClose()), this, SLOT(closeWi()));
  connect(&wa.w_dsc_output, SIGNAL(onClose()), this, SLOT(closeWo()));

  connect(this, SIGNAL(iChanged(QString)), &wa.w_dsc_input, SLOT(onNewDBName(QString)));
  connect(this, SIGNAL(oChanged(QString)), &wa.w_dsc_output, SLOT(onNewDBName(QString)));

  connect(&wa.w_dsc_input, SIGNAL(recOrUp(int, QString, QStringList, int)), this, SLOT(onRecOtUpIO(int, QString, QStringList, int)));
  connect(&wa.w_dsc_output, SIGNAL(recOrUp(int, QString, QStringList, int)), this, SLOT(onRecOtUpIO(int, QString, QStringList, int)));

}

//а если из других форм пришел запрос, то другой сигнал
void FlightDataArchive::updateTS(QString txt, int w)
{
    return onCurrentTextChanged(txt, w);
}


//а надо ли сохранять базу данных?
void FlightDataArchive::isSave()
{
    bool res = changed();
    if (res)
    {
        setTitle(QString(MAIN_TITLE).append("*"));
        setColor(Qt::red);
    }
    else
    {
        setTitle(QString(MAIN_TITLE));
        setColor(Qt::gray);
    }
    //подсветим кнопку сохранить
    emit saveEnabled(res);
}

//сохранить БД
void FlightDataArchive::saveDB()
{
    if (currentDB != ws.getValue().dbFile && !currentDB.isEmpty())
    {
        QString dir = QFileInfo(ws.getValue().dbFile).absoluteDir().absolutePath();
        bool res = TryCopyDB(true, currentDB, dir);
        if (!res)
        {
            ///@todo - error while save
        }
    }
    return;
}


//запись или создание таблицы входных (выходных) файлов
void FlightDataArchive::onRecOtUpIO(int type, QString table_name, QStringList params, int io)
{    
    QVariantMap _map;
    QStringList autoInc;
    switch (type)
    {
    case newRecord:
        if (m_db.checkTable(table_name) != SUCCESS)
        {
            int res = -1;
           // QVariantMap _map;
            _map.clear();
            _map["id_table"] = "INTEGER";
            _map["files_name"] = "NVARCHAR";
            _map["description"] = "NVARCHAR";

            //QStringList autoInc;
            autoInc.clear();
            autoInc.append("id_table");

            res = m_db.createTableIfNeed(table_name, _map, autoInc);
            if (res != SUCCESS)
            {
                ///@todo - не удается создать таблицу ...
                return;
            }
        }
        break;
    case updateRecord:
    {
        if (io == INPUT_FILES)
            table_name = wa.getIfile();
        else if (io == OUTPUT_FILES)
            table_name = wa.getOfile();

        if (m_db.checkTable(table_name) != SUCCESS)
        {
            ///@todo - обращение к несуществующей таблице ...
            return;
        }
        //очистили, чтобы записать заново
        if (m_db.dropTable(table_name) != SUCCESS)
        {
            ///@todo - ошибка очистки ...
            return;
        }

        int res = -1;
        // QVariantMap _map;
        _map.clear();
        _map["id_table"] = "INTEGER";
        _map["files_name"] = "NVARCHAR";
        _map["description"] = "NVARCHAR";

        //QStringList autoInc;
        autoInc.clear();
        autoInc.append("id_table");

        res = m_db.createTableIfNeed(table_name, _map, autoInc);
        if (res != SUCCESS)
        {
            ///@todo - не удается создать таблицу ...
            return;
        }
    }
        break;

    default:
        return;
        break;
    }

    //_map.clear();
    bool res = true;

    //копирование файлов на сервер
    QDir dir(ws.getValue().dataBasePath);
    dir.mkdir(table_name);
    dir.cd(table_name);
    QString dirServer = dir.absolutePath();
    for (int i = 0; i < params.length(); i++)
    {
        _map.clear();
        QStringList files = params.at(i).split(";");
        if (files.length() > 0)
        {
            QString fname = files.at(0);
            int pos = fname.lastIndexOf("/");
            if (pos > -1)
                fname = fname.right(fname.length() - pos - 1);
            if (!fname.isEmpty())
            {
                QString fwrite = dirServer;
                fwrite.append("/").append(fname);
                bool cop = QFile(files.at(0)).copy(fwrite);
                if (!cop)
                    fname = files.at(0);
                else
                    fname = fwrite;
            }
            _map["files_name"] = fname;
            if (files.length() > 1)
                _map["description"] = files.at(1);
            else
                _map["description"] = "";
        }
        res &= m_db.insertParamsInTable(_map, table_name);

    }
    if (!res)
    {
        ///@todo - error while writting
    }
}

//запрос настроек
void FlightDataArchive::onUpdateInfoForSettings(int type, QString name)
{
    QString dbName("");
    QStringList params;
    params.clear();
    QSqlQuery q;
    q.clear();
    QVariantMap whereParams;
    whereParams.clear();
    switch (type)
    {
    case rlsEdit:
        whereParams["type"] = name;
        params.append("description");
        dbName = RLS_TYPE_DATABASE_NAME;
        break;
    case tsEdit:
        whereParams["name_coords"] = name;
        params.append("parentPlace");
        params.append("latitude");
        params.append("longitude");
        params.append("description");
        dbName = STATE_POINTS_DATABASE_NAME;
        break;
    case placeEdit:
        whereParams["place"] = name;
        params.append("description");
        dbName = PLACE_DATABASE_NAME;
        break;
    default:
        return;
    }

    bool res = m_db.selectParamsFromTableWhereParams(params, dbName, whereParams, &q);

    QString descr("");
    double lat = 0;
    double lon = 0;
    QString parent("");
    if (res)
    {
        while (q.next())
        {
            descr = q.value("description").toString();
            lat = q.value("latitude").toDouble();
            lon = q.value("longitude").toDouble();
            parent = q.value("parentPlace").toString();
        }
        ws.ew.fillInfo(descr, parent, lat, lon);
    }
    else
    {
        //Вывести ошибку!!!
        return;
    }

}


bool FlightDataArchive::TryCopyDB(bool save, QString input_f, QString out_d)
{
    if (input_f.isEmpty() || out_d.isEmpty())
        return false;

    //инициализируем окно настроек
    emit initialText(save);
    slCloseOrEnable(enableT);
    winitial.showE();
    winitial.setCopy(input_f, out_d);
    int res = winitial.getBytesCopy();
    winitial.closeSets();
    if (res == SUCCESS)
    {
        if (!save)
        {
            QString nf = winitial.getNewFileName();
            //переназначаем файл базы данных
            GenSet s = ws.getValue();
            s.database_param.dbName = nf;
            ws.setValue(s);

            ///размеры и текущая базза данных!!!
            currentDB = ws.getValue().database_param.dbName;
        }

        initialSize = QFileInfo(currentDB);

        //если мы сохранили базу, возможно её не надо уже сохранять
        if (save)
            isSave();
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

bool FlightDataArchive::changed()
{
    QFileInfo ic = QFileInfo(currentDB);
    if ((ic.size() == initialSize.size()) && (ic.lastModified() == initialSize.lastModified()))
        return false;

    return true;
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

//запрос данных по строке
void FlightDataArchive::getData(int row)
{
    QVariantMap res = m_tbl.getData(row);

    //запрос остальных параметров, не видных в таблице
    QStringList otherParam;
    otherParam.clear();
    otherParam.append("id_table");
    otherParam.append("input_files_table");
    otherParam.append("output_files_table");
    otherParam.append("latitude");
    otherParam.append("longitude");

    int id = -1;
    QString i, o;
    i.clear();
    o.clear();
    double lat, lon;
    lat = lon = -1.0;
    QSqlQuery q;
    q.clear();

    m_db.selectParamsFromTableWhereParams(otherParam, GENERAL_DATABASE_NAME, res, &q);
    while (q.next())
    {
        id = q.value("id_table").toUInt();
        i = q.value("input_files_table").toString();
        o = q.value("output_files_table").toString();
        lat = q.value("latitude").toDouble();
        lon = q.value("longitude").toDouble();
    }

    //запрос информации о входных и выходных файлах
    for (int s = 0; s < 2; s++)
    {
        q.clear();
        otherParam.clear();
        otherParam.append("files_name");
        otherParam.append("description");
        QString resFiles = (s == 0?i:o);
        m_db.selectParamsFromTable(otherParam, resFiles, &q);
        QStringList files;
        files.clear();
        while (q.next())
        {
            files.append(q.value("files_name").toString());
            files.append(q.value("description").toString());
        }
        resFiles.clear();
        for (int count = 0; count < files.length(); count++)
            resFiles.append(QString("%1;").arg(files.at(count)));
        resFiles.chop(1);
        QString key = (s == 0?"ifiles":"ofiles");
        res[key] = resFiles;
    }

    //запрос информации об имени точки стояния
    q.clear();
    otherParam.clear();
    otherParam.append("name_coords");
    QVariantMap latlon;
    latlon.clear();
    latlon["latitude"] = lat;
    latlon["longitude"] = lon;
    m_db.selectParamsFromTableWhereParams(otherParam, STATE_POINTS_DATABASE_NAME, latlon, &q);
    while (q.next())
        res["coord"] = q.value(0).toString();

    slCloseOrEnable(enableT);
    //сюда ещё запрос о таблице входных и выходных имён!!!
    wa.setIfile(i);
    wa.setOfile(o);
    wa.setftype(updateRecord, id);
    wa.fillData(res);
    wa.showE();

    return;
}

//запрос на удаление данных из базы
void FlightDataArchive::delData(int row)
{
    QVariantMap res = m_tbl.getData(row);
    QVariantMap map;
    map.clear();
    QStringList otherParam;
    otherParam.clear();
    otherParam.append("id_table");
    otherParam.append("input_files_table");
    otherParam.append("output_files_table");
    QSqlQuery q;
    q.clear();
    QString i, o;

    m_db.selectParamsFromTableWhereParams(otherParam, GENERAL_DATABASE_NAME, res, &q);
    while (q.next())
    {
        map["id_table"] = q.value("id_table").toUInt();
        i = q.value("input_files_table").toString();
        o = q.value("output_files_table").toString();
    }

    m_db.clearRowWhere(GENERAL_DATABASE_NAME, map);
    m_db.dropTable(i);
    m_db.dropTable(o);

    i = ws.getValue().dataBasePath + tr("/") + i;
    o = ws.getValue().dataBasePath + tr("/") + o;

    bool s1 = ws.removePath(i);
    bool s2 = ws.removePath(o);

    if (!s1)
    {
        ///@todo - warning;
    }

    if (!s2)
    {
        ///@todo - warning;
    }

    emit updateView();
    //проверим размер (надо ли сохранять?)
    emit newWriteDel();

    return;
}

void FlightDataArchive::createFilterRequest(int time, int type, int place, int coord, QString timeS, QString timeEnd, QString typeS, QString placeS, QString coordS)
{
    QVariantMap map;
    map.clear();

    if (time != Qt::Unchecked)
    {
        map["date_s"] = timeS;
        map["date_e"] = timeEnd;
    }

    if (type != Qt::Unchecked)
    {
        map["type"] = typeS;
    }

    if (place != Qt::Unchecked)
    {
        map["placeStr"] = placeS;
    }

    if (coord != Qt::Unchecked)
    {
        QStringList params;
        params.clear();
        params.append("latitude");
        params.append("longitude");
        QVariantMap where;
        where.clear();
        where["name_coords"] = coordS;
        QSqlQuery qq;
        qq.clear();
        m_db.selectParamsFromTableWhereParams(params, STATE_POINTS_DATABASE_NAME, where, &qq);
        while (qq.next())
        {
            map["latitude"] = qq.value("latitude");
            map["longitude"] = qq.value("longitude");
        }
    }

    updateWithFilter(map);
}

//для фильтрации
void FlightDataArchive::updateWithFilter(QVariantMap whereParams)
{
    if (whereParams.isEmpty())
        return onUpdateView();

    QString sqlQ = QString("SELECT date, type, placeStr, description FROM %1 WHERE ( ").arg(GENERAL_DATABASE_NAME);
    QStringList keys = whereParams.keys();
    QString timeSql;
    timeSql.clear();

    for (int i = 0; i < keys.length(); i++)
    {
        if (keys.at(i) == "date_s")
        {
            timeSql.append(QString("date>='%1' AND ").arg(whereParams.value(keys.at(i)).toDateTime().toString("yyyy-MM-ddThh:mm:ss")));
        }
        else if (keys.at(i) == "date_e")
        {
            timeSql.append(QString("date<='%1' AND ").arg(whereParams.value(keys.at(i)).toDateTime().toString("yyyy-MM-ddThh:mm:ss")));
        }
        else
            sqlQ.append(keys.at(i)).append(QString("='%1' AND ").arg(whereParams.value(keys.at(i)).toString()));
    }
    if (!timeSql.isEmpty())
        sqlQ.append(timeSql);

    sqlQ.chop(5);
    sqlQ.append(" )");

    QSqlQuery q = QSqlQuery(sqlQ);

    m_tbl.setQuery(q);

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
            id_name = "id_type";
            nn = "type";
            break;
        case placeEdit:
            newWrite["place"] = name;
            id_name = "id_place";
            nn = "place";
            break;
        case tsEdit:
            newWrite["name_coords"] = name;
            newWrite["latitude"] = _map.value("latitude").toDouble();
            newWrite["longitude"] = _map.value("longitude").toDouble();
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

    //проверим размер (надо ли сохранять?)
    emit newWriteDel();

    return SUCCESS;
}


//запись новой строки в основную базу!!!
int FlightDataArchive::onWriteNewDB(QVariantMap _map, int f_type)
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
        dateIO.replace("-", "_");

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
        QVector<double> geo;
        geo.clear();
        geo.resize(2);
        int ii = 0;
        if (m_db.selectParamsFromTableWhereParams(coords, STATE_POINTS_DATABASE_NAME, tp, &q))
        {
            while (q.next())
            {
                for (; ii < 2; ii++)
                    (ii == 0?geo.replace(ii, q.value("latitude").toDouble()):geo.replace(ii, q.value("longitude").toDouble()));
            }
        }
        else
        {
            return -1;
            ///@todo - error
        }

        QString nameInput, nameOutput;

        if (f_type == newRecord)
        {
            srand((unsigned int)QDateTime::currentDateTime().toTime_t());
            nameInput = QString("i_%1_%2_%3").arg(dateIO).arg(_map.value("type").toString()).arg(rand());
            nameOutput = QString("o_%1_%2_%3").arg(dateIO).arg(_map.value("type").toString()).arg(rand());

            //переделаем в латиницу
            nameInput = ws.cyrilToLatin(nameInput);
            nameOutput = ws.cyrilToLatin(nameOutput);
        }
        else if (f_type == updateRecord)
        {
            nameInput = wa.getIfile();
            nameOutput = wa.getOfile();
        }

        //формируем окончательный запрос
        newWrite["date"] = QDateTime::fromString(_map.value("date").toString(), "yyyy-MM-dd hh:mm:ss");
        newWrite["type"] = _map.value("type").toString();;
        newWrite["input_files_table"] = nameInput;
        newWrite["output_files_table"] = nameOutput;
        newWrite["placeStr"] = _map.value("place").toString();
        newWrite["latitude"] = geo.at(0);
        newWrite["longitude"] = geo.at(1);
        newWrite["description"] = _map.value("message").toString();

        bool ok(false);
        if (f_type == newRecord)
        {
            if (!m_db.insertParamsInTable(newWrite, GENERAL_DATABASE_NAME))
            {
                return -2;
                ///@todo - error;
            }
            else
                ok = true;
        }
        else if (f_type == updateRecord && wa.getId() > -1)
        {
            QVariantMap id;
            id.clear();
            id["id_table"] = wa.getId();
            if (!m_db.updateParamsInTable(newWrite, GENERAL_DATABASE_NAME, id))
            {
                return -2;
                ///@todo - error;
            }
            else
                ok = true;
        }
        if (ok)
        {
            emit iChanged(nameInput);
            emit oChanged(nameOutput);
            emit updateView();

            //проверим размер (надо ли сохранять?)
            emit newWriteDel();
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
        _map["latitude"] = "DOUBLE";
        _map["longitude"] = "DOUBLE";
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

//переопределяем закрытие окна
bool FlightDataArchive::event(QEvent *event)
{
    if (event->type() == QEvent::Close)
    {
        quit();
    }
    return QQuickView::event(event);
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
    ws.initSets();
    ws.showE();
}

//показываем добавить новый полёт
void FlightDataArchive::showAdd()
{
    slCloseOrEnable(enableT);
    wa.setftype(newRecord);
    wa.clearForm();
    wa.showE();
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
    //slCloseOrEnable(nonecl);
    ws.ew.hide();
}


//закрытие настроек
void FlightDataArchive::closeAdd()
{
    slCloseOrEnable(nonecl);
    wa.hide();
}

//загрытие прогресс-бара
void FlightDataArchive::closeIW()
{
    slCloseOrEnable(nonecl);
    winitial.hide();
}

//закрыть или сделать неактивным
void FlightDataArchive::slCloseOrEnable(closeEnable t)
{
    Q_UNUSED(enableAll);

    switch (t)
    {
    case nonecl:
        emit setEnabled(true);
        break;
    case closeT:
        quit();
        break;
    case enableT:
        emit setEnabled(false);
        break;
    default:
        break;
    }
}
