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
    editwindow.cpp \
    initialdialog.cpp

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
    editwindow.h \
    initialdialog.h

OTHER_FILES += \
    qml/WindowButtonText.qml \
    qml/WindowButton.qml \
    qml/windowAddNew.qml \
    qml/TextEditWidget.qml \
    qml/tableModelDescription.qml \
    qml/settingsWindow.qml \
    qml/progressBar.qml \
    qml/mainWindow.qml \
    qml/editObjectWindow.qml

RESOURCES += \
    resource.qrc

FORMS +=
