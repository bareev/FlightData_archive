#include "settingswindow.h"
#include <QDeclarativeContext>

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

int SettingsWindow::init()
{
    if (!absDir.isEmpty())
    {

        setFocusPolicy(Qt::StrongFocus);
        setResizeMode(QDeclarativeView::SizeRootObjectToView);
        setSource(QUrl::fromLocalFile(absDir + "/settingsWindow.qml"));
        rootContext()->setContextProperty("windowSets", this);
        setWindowFlags(Qt::CustomizeWindowHint |  Qt::WindowMinMaxButtonsHint);

        return SUCCESS;
    }
    else
    {
        ShowMessageBox(2, error);
        return -1;
    }

}

int SettingsWindow::init(QString _absDir)
{
    setAbsDir(_absDir);
    return init();
}
