#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDeclarativeView>
#include <settings.h>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDeclarativeView, public Settings
{
    Q_OBJECT

public:
    SettingsWindow();
    SettingsWindow(QString _absDir);
    int init();
    int init(QString _absDir);
    ~SettingsWindow();
    void setAbsDir(QString _absDir){absDir = _absDir; return;}
    Q_INVOKABLE void closeSets();
    Q_INVOKABLE void openDir();

private:
    QString absDir;


signals:
    void onClose();

};

#endif // SETTINGSWINDOW_H
