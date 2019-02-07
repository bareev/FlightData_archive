#ifndef FLIGHTDATAARCHIVE_H
#define FLIGHTDATAARCHIVE_H

#include <QMainWindow>
#include <QDeclarativeView>

class FlightDataArchive : public QDeclarativeView
{
    Q_OBJECT

public:
    FlightDataArchive();
    void init();
    Q_INVOKABLE void quit();
    ~FlightDataArchive();
};

#endif // FLIGHTDATAARCHIVE_H
