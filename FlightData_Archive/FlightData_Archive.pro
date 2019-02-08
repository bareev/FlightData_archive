#-------------------------------------------------
#
# Project created by QtCreator 2019-02-07T10:41:02
#
#-------------------------------------------------

QT       += core gui declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlightData_Archive
TEMPLATE = app


SOURCES += main.cpp\
        flightdataarchive.cpp \
    settings.cpp \
    message.cpp

HEADERS  += flightdataarchive.h \
    settings.h \
    message.h \
    structs.h

OTHER_FILES += \
    mainWindow.qml \
    WindowButton.qml

RESOURCES += \
    resource.qrc
