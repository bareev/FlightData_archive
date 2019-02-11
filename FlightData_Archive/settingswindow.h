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

private:
    QString absDir;

};

#endif // SETTINGSWINDOW_H
