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

  if (m_db.checkTable(GENERAL_DATABASE_NAME) != SUCCESS)
  {
      QVariantMap _map;
      _map.clear();
      _map["id_table"] = "INT";
      _map["date"] = "DATETIME";
      _map["type"] = "VARCHAR(5)";
      _map["input_files_table"] = "VARCHAR(20)";
      _map["output_files_table"] = "VARCHAR(20)";
      _map["placeStr"] = "NVARCHAR";
      _map["placeGeo"] = "GEOGRAPHY";
      _map["description"] = "NVARCHAR";

      res = m_db.createTableIfNeed(GENERAL_DATABASE_NAME, _map);

      if (res != SUCCESS)
      {
          //ShowMessageBox(11, error);
      }
  }

  m_tbl.setQuery(QSqlQuery(QString("SELECT date, type, placeStr, description FROM %1;").arg(GENERAL_DATABASE_NAME)));

  rootContext()->setContextProperty("table", &m_tbl);

  //tbl.setModel(m_tbl);
  //tbl.setupViewport();
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
