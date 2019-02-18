#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QtSql/QSql>
#include <structs.h>

class dbManager
{
public:
    dbManager();
    sqlSets getSqlSets(){return structdB;}
    void setSqlSets(sqlSets _s){structdB = _s; return;}
    int initDB();
private:
    sqlSets structdB;
    bool openDB();
};

#endif // DBMANAGER_H
