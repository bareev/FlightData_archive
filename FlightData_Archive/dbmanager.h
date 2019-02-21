#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <structs.h>

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
    QSqlQuery querry;
    bool state;
};

#endif // DBMANAGER_H
