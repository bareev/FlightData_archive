#include "settingswindow.h"
#include <QDeclarativeContext>
#include <QFileDialog>

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
    QString res = QFileDialog::getOpenFileName(this, tr("Выберите директорию с данными"), QDir::currentPath(), tr("Директории"));
    if (!res.isEmpty())
    {
        QObject *textInputs = findChild<QObject*>("absDirInput");
        textInputs->setProperty("text", QUrl(res));
    }
}
