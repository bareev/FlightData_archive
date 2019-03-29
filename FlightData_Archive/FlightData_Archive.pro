#-------------------------------------------------
#
# Project created by QtCreator 2019-02-07T10:41:02
#
#-------------------------------------------------

QT       += core gui sql qml quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlightData_Archive
TEMPLATE = app


SOURCES += main.cpp\
        flightdataarchive.cpp \
    settings.cpp \
    message.cpp \
    settingswindow.cpp \
    dbmanager.cpp \
    tablemodel.cpp \
    addwindow.cpp \
    descriptionfiles.cpp \
    wcore.cpp \
    editwindow.cpp

HEADERS  += flightdataarchive.h \
    settings.h \
    message.h \
    structs.h \
    settingswindow.h \
    dbmanager.h \
    tablemodel.h \
    addwindow.h \
    descriptionfiles.h \
    wcore.h \
    editwindow.h

OTHER_FILES += \
    mainWindow.qml \
    WindowButton.qml \
    settingsWindow.qml \
    WindowButtonText.qml \
    TextEditWidget.qml \
    windowAddNew.qml \
    tableModelDescription.qml \
    editObjectWindow.qml

RESOURCES += \
    resource.qrc

FORMS +=
