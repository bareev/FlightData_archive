#ifndef FLIGHTDATAARCHIVE_H
#define FLIGHTDATAARCHIVE_H

#include <QMainWindow>
#include <QDeclarativeView>
#include <QObject>
#include <message.h>
#include <settings.h>

class FlightDataArchive : public QObject, public QDeclarativeView, public Message
{
    Q_OBJECT

public:
    FlightDataArchive();
    void init();
    Q_INVOKABLE void quit();
    ~FlightDataArchive();

private:
    Settings genSets;
    void slCloseOrEnable(closeEnable);
};

#endif // FLIGHTDATAARCHIVE_H
