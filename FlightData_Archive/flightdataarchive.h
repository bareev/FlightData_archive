#ifndef FLIGHTDATAARCHIVE_H
#define FLIGHTDATAARCHIVE_H

#include <QtQuick/QQuickView>
#include <settings.h>
#include <settingswindow.h>
#include <dbmanager.h>
#include <tablemodel.h>
#include <addwindow.h>
#include <initialdialog.h>
#include <QFileInfo>

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
    Q_INVOKABLE void saveDB();
    ~FlightDataArchive();

private:
    void slCloseOrEnable(closeEnable);
    SettingsWindow ws;
    AddWindow wa;
    InitialDialog winitial;
    bool checkAllQMlFiles(QString dir, int* idx);
    QStringList qmlFiles;
    dbManager m_db;
    tableModel m_tbl;
    int checkTablesDB(QString *res);
    void emitAll(QStringList l, int t, QVector<int>who);
    bool changed();
    QString currentDB;
    QFileInfo initialSize;
    bool TryCopyDB(bool save, QString input_f, QString out_d);

public slots:
    void closeSets();
    void closeSetsE();
    void closeAdd();
    void closeWi();
    void closeWo();
    void closeIW();
    int onWriteNewDB(QVariantMap _map);
    int onWriteNewType(QVariantMap _map);
    void onUpdateView();
    void updateTS(QString, int w);
    void isSave();

signals:
    void iChanged(QString s);
    void oChanged(QString s);
    void updateView();
    void rlsInfoRead(QStringList s, int t, int w);
    void setEnabled(bool e);
    void saveEnabled(bool e);
    void newWriteDel();
    void initialText(bool t);

};

#endif // FLIGHTDATAARCHIVE_H
