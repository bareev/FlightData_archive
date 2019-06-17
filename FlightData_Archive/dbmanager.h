#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <structs.h>
#include <QStringList>
#include <QVariantMap>

class dbManager
{
public:
    dbManager();
    sqlSets getSqlSets(){return structdB;}
    void setSqlSets(sqlSets _s){structdB = _s; return;}
    int initDB();
    void setPass(QString pass){structdB.password = pass; return;}
    void setType(QString type){structdB.type = type; return;}
    void setDBName(QString name){structdB.dbName = name; return;}
    void setUserName(QString user){structdB.user = user; return;}
    bool openDB();
    bool openDB(sqlSets _sets);
    bool openDB(QString _dbName);
    bool openDB(QString _dbName, QString _type, QString _user = "", QString _pass = "");
    bool isActive(){return state;}
    void closeDB();
    int createTableIfNeed(QString nameTable, QVariantMap params);
    int createTableIfNeed(QString nameTable, QVariantMap params, QStringList namesNotNullAutoIncrement);
    int checkTable(QString nameTable);
    QString lastError(){return le;}
    bool runSqlQuerryReturn(QString querry, QSqlQuery *q);
    bool runSqlQuerryReturnBindValues(QString querryStr, QVariantMap values, QSqlQuery *query);
    bool selectParamsFromTableWhereParams(QString params, QString tableName, QVariantMap whereParams, QSqlQuery *q);
    bool selectParamsFromTableWhereParams(QStringList params, QString tableName, QVariantMap whereParams, QSqlQuery *q);
    bool selectParamsFromTable(QStringList params, QString tableName, QSqlQuery *q);
    bool selectParamsFromTable(QString params, QString tableName, QSqlQuery *q);
    bool insertParamsInTable(QVariantMap _map, QString tableName);
    bool updateParamsInTable(QVariantMap _map, QString tableName, QVariantMap id);
    bool clearAllRows(QString tableName);

private:
    bool loadDrive();
    bool loadDrive(QString _s);
    bool loadDrive(sqlSets _sets);
    bool loadPass();
    bool loadPass(QString _s);
    bool loadPass(sqlSets _sets);
    bool loadUser();
    bool loadUser(QString _s);
    bool loadUser(sqlSets _sets);
    QSqlDatabase dataBase_users;
    sqlSets structdB;
    bool state;
    bool runSqlQuerry(QString querry);
    bool runSqlQuerry(QSqlQuery q);
    QString le;
};

#endif // DBMANAGER_H
