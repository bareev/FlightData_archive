#include "settingswindow.h"
#include <QDeclarativeContext>
#include <QFileDialog>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>

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
}

int SettingsWindow::init()
{
    if (!absDir.isEmpty())
    {

        setFocusPolicy(Qt::StrongFocus);
        setResizeMode(QDeclarativeView::SizeRootObjectToView);
        setSource(QUrl::fromLocalFile(absDir + "/settingsWindow.qml"));
        rootContext()->setContextProperty("windowSets", this);
        setWindowFlags(Qt::CustomizeWindowHint |  Qt::WindowMinMaxButtonsHint);

        //QQmlEngine engine;
        //QDeclarativeComponent component(rootContext()->engine(), QUrl::fromLocalFile(absDir + "/settingsWindow.qml"));
        //object = component.create();

        return SUCCESS;
    }
    else
    {
        ShowMessageBox(3, error);
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

    QString res = QFileDialog::getExistingDirectory( this, trUtf8("Выбрать директорию с данными"), trUtf8("Директории"), QFileDialog::ShowDirsOnly );
    if (!res.isEmpty())
    {
        emit textChanged(res);
    }
}

void SettingsWindow::saveSettings(QString _s)
{
    GenSet structs;
    structs = getValue();
    structs.dataBasePath = _s;
    setValue(structs);
    writeAll();
}
