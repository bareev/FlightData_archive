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
    ~SettingsWindow();
    SettingsWindow(QString _absDir);
    int init();
    int init(QString _absDir);   
    void setAbsDir(QString _absDir){absDir = _absDir; return;}
    Q_INVOKABLE void closeSets();
    Q_INVOKABLE void openDir();
    void settingsToWindow(GenSet _s);
    Q_INVOKABLE void saveSettings(QString _s);

private:
    QString absDir;
    //QObject *object;


signals:
    void textChanged(QString s);


signals:
    void onClose();

};

#endif // SETTINGSWINDOW_H
