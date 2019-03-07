#include "flightdataarchive.h"
#include <QtQuick/QQuickView>
#include <QApplication>
#include <QFile>
#include <QTableView>
#include <QtQml/QQmlContext>


FlightDataArchive::FlightDataArchive()
{
    qmlFiles.clear();
    qmlFiles.append("mainWindow.qml");
    qmlFiles.append("settingsWindow.qml");
    qmlFiles.append("WindowButton.qml");
    qmlFiles.append("WindowButtonText.qml");
    qmlFiles.append("TextEditWidget.qml");

    init();
}

FlightDataArchive::~FlightDataArchive()
{
}

void FlightDataArchive::init()
{

  // Путь к папке, содержащей QML файлы
  QString contentPath;

#ifdef QT_DEBUG
  // В отладочной версии это абсолютный путь к папке проекта
  contentPath = "D:\\progs_git\\FlightData_database_FB032019\\FlightData_Archive";
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

  rootContext() ->setContextProperty("window", this);

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

  m_tbl.setQuery(QSqlQuery(QString("SELECT date, type, placeStr, description FROM %1;").arg(GENERAL_DATABASE_NAME)));

  rootContext()->setContextProperty("table", &m_tbl);

  //выберем все типы станций и места испытаний
  QSqlQuery q;
  q.clear();
  QString types;
  types.clear();
  QStringList result, resPlaces;
  result.clear();
  resPlaces.clear();

  types.append("SELECT string FROM ").append(RLS_TYPE_DATABASE_NAME);
  if (m_db.runSqlQuerryReturn(types, &q))
  {
      while (q.next())
          result.append(q.value(0).toString());
  }
  else
  {
      /// @todo - ошибка чтения
  }

  types.clear();
  q.clear();
  types.append("SELECT plcae FROM ").append(PLACE_DATABASE_NAME);
  if (m_db.runSqlQuerryReturn(types, &q))
  {
      while (q.next())
          resPlaces.append(q.value(0).toString());
  }
  else
  {
      /// @todo - ошибка чтения
  }



  ///конец блока с базами данных

  //инициализируем окно настроек
  res = ws.init(contentPath);
  if (res == SUCCESS)
  {
      ws.settingsToWindow(ws.getValue());
      hide();
  }

  connect(&ws, SIGNAL(onClose()), this, SLOT(closeSets()));
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
        _map["id_table"] = "INT";
        _map["date"] = "DATETIME";
        _map["type"] = "NVARCHAR(5)";
        _map["input_files_table"] = "NVARCHAR(20)";
        _map["output_files_table"] = "NVARCHAR(20)";
        _map["placeStr"] = "NVARCHAR(20)";
        _map["placeGeo"] = "GEOGRAPHY";
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
        _map["id_type"] = "INT";
        _map["type"] = "NVARCHAR(5)";
        _map["string"] = "NVARCHAR(50)";
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
        _map["id_place"] = "INT";
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

//закрытие настроек
void FlightDataArchive::closeSets()
{
    slCloseOrEnable(nonecl);
    ws.hide();
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
