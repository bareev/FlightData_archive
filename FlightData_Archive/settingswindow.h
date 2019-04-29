#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <wcore.h>
#include <settings.h>
#include <editwindow.h>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public Wcore, public Settings
{
    Q_OBJECT

public:
    Q_INVOKABLE void openDir();
    Q_INVOKABLE void openDirDB();
    void settingsToWindow(GenSet _s);
    Q_INVOKABLE void saveSettings(QString _s, QString _s2);
    EditWindow ew;
    Q_INVOKABLE void openButtonSets(int n);

signals:
    void textChanged(const QString& s);
    void textChangedpath(const QString& s);

};

#endif // SETTINGSWINDOW_H
