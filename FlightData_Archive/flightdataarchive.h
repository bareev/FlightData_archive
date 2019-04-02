#ifndef FLIGHTDATAARCHIVE_H
#define FLIGHTDATAARCHIVE_H

#include <QtQuick/QQuickView>
#include <settings.h>
#include <settingswindow.h>
#include <dbmanager.h>
#include <tablemodel.h>
#include <addwindow.h>

class FlightDataArchive : public QQuickView//, public Message
{
    Q_OBJECT

public:
    FlightDataArchive();
    void init();
    Q_INVOKABLE void quit();
    Q_INVOKABLE void showSets();
    Q_INVOKABLE void showAdd();
    Q_INVOKABLE void onCurrentTextChanged(QString txt, int w);
    ~FlightDataArchive();

private:
    void slCloseOrEnable(closeEnable);
    SettingsWindow ws;
    AddWindow wa;
    bool checkAllQMlFiles(QString dir, int* idx);
    QStringList qmlFiles;
    dbManager m_db;
    tableModel m_tbl;
    int checkTablesDB(QString *res);
    void emitAll(QStringList l, int t, QVector<int>who);

public slots:
    void closeSets();
    void closeSetsE();
    void closeAdd();
    void closeWi();
    void closeWo();
    int onWriteNewDB(QVariantMap _map);
    int onWriteNewType(QVariantMap _map);
    void onUpdateView();
    void updateTS(QString, int w);

signals:
    void iChanged(QString s);
    void oChanged(QString s);
    void updateView();
    void rlsInfoRead(QStringList s, int t, int w);

};

#endif // FLIGHTDATAARCHIVE_H
