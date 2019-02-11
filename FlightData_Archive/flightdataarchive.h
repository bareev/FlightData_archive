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
    Settings genSets;
    void slCloseOrEnable(closeEnable);
    SettingsWindow ws;
    void closeSets();
};

#endif // FLIGHTDATAARCHIVE_H
