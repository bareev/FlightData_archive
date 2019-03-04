#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QtQuick/QQuickView>
#include <settings.h>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QQuickView, public Settings
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
    Q_INVOKABLE void openDirDB();
    void settingsToWindow(GenSet _s);
    Q_INVOKABLE void saveSettings(QString _s, QString _s2);

private:
    QString absDir;
    //QObject *object;

signals:
    void textChanged(const QString& s);
    void textChangedpath(const QString& s);
    void onClose();

};

#endif // SETTINGSWINDOW_H
