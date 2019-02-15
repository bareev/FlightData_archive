#ifndef FLIGHTDATAARCHIVE_H
#define FLIGHTDATAARCHIVE_H

#include <QDeclarativeView>
#include <QObject>
#include <message.h>
#include <settings.h>
#include <settingswindow.h>

class FlightDataArchive : public QDeclarativeView, public Message
{
    Q_OBJECT

public:
    FlightDataArchive();
    void init();
    Q_INVOKABLE void quit();
    Q_INVOKABLE void showSets();
    ~FlightDataArchive();

private:
    void slCloseOrEnable(closeEnable);
    SettingsWindow ws;
    bool checkAllQMlFiles(QString dir, int* idx);
    QStringList qmlFiles;

public slots:
    void closeSets();
};

#endif // FLIGHTDATAARCHIVE_H
