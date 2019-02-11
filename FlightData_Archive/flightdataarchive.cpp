#include "flightdataarchive.h"
#include <QDeclarativeContext>
#include <QApplication>


FlightDataArchive::FlightDataArchive()
{
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
  genSets.setFileName(contentPath + QString("\\config\\config.ini"));
  int res = genSets.init();
  if (res != SUCCESS)
      ::exit(0);

  //инициализируем окно настроек
  res = ws.init(contentPath);
  if (res == SUCCESS)
      hide();
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
