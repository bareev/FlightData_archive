#include "settingswindow.h"
#include <QtQml/QQmlContext>
//#include <QFileDialog>
//#include <QDeclarativeEngine>
//#include <QDeclarativeComponent>

SettingsWindow::SettingsWindow()
{
    absDir.clear();
}

SettingsWindow::SettingsWindow(QString _absDir)
{
    setAbsDir(_absDir);
}

SettingsWindow::~SettingsWindow()
{
}

void SettingsWindow::settingsToWindow(GenSet _s)
{
    emit textChanged(_s.dataBasePath);
    emit textChangedpath(_s.dbFile);
}

int SettingsWindow::init()
{
    if (!absDir.isEmpty())
    {

        //setFocusPolicy(Qt::StrongFocus);
        setResizeMode(QQuickView::SizeRootObjectToView);
        setSource(QUrl::fromLocalFile(absDir + "/settingsWindow.qml"));
        rootContext()->setContextProperty("windowSets", this);
        //setWindowFlags(Qt::CustomizeWindowHint |  Qt::WindowMinMaxButtonsHint);

        //QQmlEngine engine;
        //QDeclarativeComponent component(rootContext()->engine(), QUrl::fromLocalFile(absDir + "/settingsWindow.qml"));
        //object = component.create();

        return SUCCESS;
    }
    else
    {
        //ShowMessageBox(3, error);
        return -1;
    }

}

int SettingsWindow::init(QString _absDir)
{
    setAbsDir(_absDir);
    return init();
}

void SettingsWindow::closeSets()
{
    emit onClose();
    return;
}

void SettingsWindow::openDir()
{

    //QString res = QFileDialog::getExistingDirectory( this, trUtf8("Выбрать директорию с данными"), trUtf8("Директории"), QFileDialog::ShowDirsOnly );
    //if (!res.isEmpty())
    {
        //emit textChanged(res);
    }
}

void SettingsWindow::openDirDB()
{

    //QString res = QFileDialog::getOpenFileName( this, trUtf8("Выбрать файл с данными"), trUtf8("Базы данных"), "*.db" );
    //if (!res.isEmpty())
    {
        //emit textChangedDB(res);
    }
}

void SettingsWindow::saveSettings(QString _s, QString _s_dbFile)
{
    GenSet structs;
    structs = getValue();
    structs.dataBasePath = _s;
    structs.dbFile = _s_dbFile;
    setValue(structs);
    writeAll();
}
