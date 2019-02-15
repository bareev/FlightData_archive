#include "flightdataarchive.h"
#include <QDeclarativeContext>
#include <QApplication>
#include <QFile>


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
  contentPath = "D:\\progs_git\\FlightData_database - FB_FEB2019\\FlightData_Archive";
#else
  // В релизе это путь к папке, в которой расположено приложение
  contentPath = QApplication::applicationDirPath();
#endif

  int errIdx;
  bool resqml = checkAllQMlFiles(contentPath, &errIdx);
  if (!resqml && errIdx != -1)
  {
      ShowMessageBox(errIdx + 2, critical);
      ::exit(0);
  }

  setFocusPolicy(Qt::StrongFocus);
  // Изменять размеры QML объекта под размеры окна
  // Возможно делать и наоборот,
  // передавая QDeclarativeView::SizeViewToRootObject
  setResizeMode(QDeclarativeView::SizeRootObjectToView);

  // Загрузить QML файл
  setSource(QUrl::fromLocalFile(contentPath + "/mainWindow.qml"));

  rootContext()->setContextProperty("window", this);
  setWindowFlags(Qt::CustomizeWindowHint |  Qt::WindowMinMaxButtonsHint);

  //читаем настройки, если что жёстко закрываем
  ws.setFileName(contentPath + QString("\\config\\config.ini"));
  int res = ws.initSets();
  if (res != SUCCESS)
      ::exit(0);

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
        setEnabled(true);
        break;
    case closeT:
        quit();
        break;
    case enableT:
        setEnabled(false);
        break;
    default:
        break;
    }
}
