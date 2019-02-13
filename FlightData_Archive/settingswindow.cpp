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
    if (object)
        delete object;
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
        QDeclarativeComponent component(rootContext()->engine(), QUrl::fromLocalFile(absDir + "/settingsWindow.qml"));
        object = component.create();

        emit textChanged(getValue().dataBasePath);

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
        QList<QObject*> textInputs = object->findChildren<QObject*>("absDirInput");
        if (!textInputs.isEmpty())
        {
            int idx = -1;
            for (int s = 0; s < textInputs.length(); s++)
            {
                if (textInputs.at(s)->objectName().compare("absDirInput", Qt::CaseInsensitive) == 0)
                {
                    idx = s;
                    break;
                }
            }
            if (idx != -1)
                emit textChanged(res);
        }
    }
}
