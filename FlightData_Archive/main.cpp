#include "flightdataarchive.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FlightDataArchive w;
    w.show();

    return a.exec();
}
