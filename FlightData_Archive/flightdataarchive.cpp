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
  contentPath = "D:\\progs_git\\FlightData_database\\FlightData_Archive";
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
}

//закрытие приложения
void FlightDataArchive::quit()
{
    QApplication::quit();
}
