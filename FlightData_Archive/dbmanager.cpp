#include "dbmanager.h"
#include <QSqlError>

dbManager::dbManager()
{
    state = false;
}

bool dbManager::openDB(QString _dbName, QString _type, QString _user, QString _pass)
{
    bool res = false;
    if (isActive())
        closeDB();

    res = loadDrive(_type);
    if (!res)
        return res;

    if (!_dbName.isEmpty())
        dataBase_users.setDatabaseName(_dbName);
    else
    {
        res = false;
        return res;
    }

    loadUser(_user);
    loadPass(_pass);

    // Открываем базу данных
    res = dataBase_users.open();
    state = dataBase_users.isOpen()?true:false;

    return res;
}

bool dbManager::openDB(sqlSets _sets)
{
    QString _dbName = _sets.dbName;
    QString _type = _sets.type;
    QString _user = _sets.user;
    QString _pass = _sets.password;

    return openDB(_dbName, _type, _user, _pass);
}

bool dbManager::openDB(QString _dbName)
{
    QString _type = getSqlSets().type;
    QString _user = getSqlSets().user;
    QString _pass = getSqlSets().password;

    return openDB(_dbName, _type, _user, _pass);
}

bool dbManager::openDB()
{
    QString _dbName = getSqlSets().dbName;
    QString _type = getSqlSets().type;
    QString _user = getSqlSets().user;
    QString _pass = getSqlSets().password;

    return openDB(_dbName, _type, _user, _pass);
}

void dbManager::closeDB()
{
    dataBase_users.close();
    state = dataBase_users.isOpen()?true:false;
    return;
}

bool dbManager::runSqlQuerryReturn(QString querryStr, QSqlQuery *query)
{
    QSqlQuery q(dataBase_users);

    if (!q.exec(querryStr))
    {
        le = q.lastError().text();
        return false;
    }

    *query = q;
    return true;
}

bool dbManager::runSqlQuerryReturnBindValues(QString querryStr, QVariantMap values, QSqlQuery *query)
{

    if (values.isEmpty())
        return runSqlQuerryReturn(querryStr, query);

    else
    {
        QSqlQuery q(dataBase_users);
        q.prepare(querryStr);
        QStringList keys = values.keys();

        for (int i = 0; i < keys.length(); i++)
            q.addBindValue(values.value(keys.at(i)));

        if (!q.exec())
        {
            le = q.lastError().text();
            return false;
        }

        *query = q;
        return true;
    }
}


//запрос select
bool dbManager::selectParamsFromTable(QStringList params, QString tableName, QSqlQuery *q)
{
    QVariantMap whereParams;
    whereParams.clear();

    return selectParamsFromTableWhereParams(params, tableName, whereParams, q);
}


//запрос select
bool dbManager::selectParamsFromTable(QString params, QString tableName, QSqlQuery *q)
{
    QStringList paramsList;
    paramsList.clear();
    paramsList.append(params);

    return selectParamsFromTable(paramsList, tableName, q);
}

//запрос select
bool dbManager::selectParamsFromTableWhereParams(QString params, QString tableName, QVariantMap whereParams, QSqlQuery *q)
{
    QStringList paramList;
    paramList.clear();
    paramList.append(params);

    return selectParamsFromTableWhereParams(paramList, tableName, whereParams, q);
}

//запрос select
bool dbManager::selectParamsFromTableWhereParams(QStringList params, QString tableName, QVariantMap whereParams, QSqlQuery *q)
{
    if (params.isEmpty() || tableName.isEmpty())
        return false;

    QString runquery;
    runquery.clear();

    runquery.append("SELECT ");
    for (int i = 0; i < params.length(); i++)
        runquery.append(params.at(i)).append(", ");

    //запятую и пробел
    runquery.chop(2);
    runquery.append(" FROM ").append(tableName);

    if (!whereParams.isEmpty())
    {
        QStringList keys = whereParams.keys();
        runquery.append(" WHERE (");
        for (int i = 0; i < keys.length(); i++)
            runquery.append(keys.at(i)).append("=? AND ");
        runquery.chop(5);
        runquery.append(")");
    }

    return runSqlQuerryReturnBindValues(runquery, whereParams, q);
}

bool dbManager::insertParamsInTable(QVariantMap _map, QString tableName)
{
    if (_map.isEmpty() || tableName.isEmpty())
        return false;

    QString runquery;
    runquery.clear();

    runquery.append("INSERT INTO ").append(tableName).append(" (");

    QStringList keys = _map.keys();
    for (int i = 0; i < keys.length(); i++)
        runquery.append(keys.at(i)).append(", ");

    runquery.chop(2);
    runquery.append(") VALUES (");

    for (int i = 0; i < keys.length(); i++)
        runquery.append("?, ");

    runquery.chop(2);
    runquery.append(")");

    QSqlQuery q(dataBase_users);
    q.clear();
    q.prepare(runquery);

    for (int i = 0; i < keys.length(); i++)
        q.addBindValue(_map.value(keys.at(i)));

    return runSqlQuerry(q);
}

bool dbManager::updateParamsInTable(QVariantMap _map, QString tableName, QVariantMap where)
{
    if (_map.isEmpty() || tableName.isEmpty() || where.isEmpty())
        return false;

    QString runquery;
    runquery.clear();

    runquery.append("UPDATE ").append(tableName).append(" SET ");

    QStringList keys = _map.keys();
    for (int i = 0; i < keys.length(); i++)
        runquery.append(keys.at(i)).append(" = ?, ");

    runquery.chop(2);
    runquery.append(" WHERE ").append(where.keys().at(0)).append(" = ?");

    QSqlQuery q(dataBase_users);
    q.clear();
    q.prepare(runquery);

    for (int i = 0; i < keys.length(); i++)
        q.addBindValue(_map.value(keys.at(i)));

    q.addBindValue(where.value(where.keys().at(0)));

    return runSqlQuerry(q);
}

bool dbManager::clearAllRows(QString tableName)
{
    if (tableName.isEmpty())
        return false;

    QString runquery;
    runquery.clear();
    runquery.append("DELETE FROM ").append(tableName);

    QSqlQuery q(dataBase_users);
    q.clear();
    q.prepare(runquery);

    return runSqlQuerry(q);
}


bool dbManager::runSqlQuerry(QSqlQuery querryStr)
{

    if (!querryStr.exec())
    {
        le = querryStr.lastError().text();
        return false;
    }

    return true;
}

bool dbManager::runSqlQuerry(QString querryStr)
{
    QSqlQuery q(dataBase_users);

    if (!q.exec(querryStr))
    {
        le = q.lastError().text();
        return false;
    }

    return true;
}

int dbManager::dropTable(QString nameTable)
{
    if (!isActive() || nameTable.isEmpty())
        return -1;

    QString sqlquery;
    sqlquery.clear();
    sqlquery = QString("DROP TABLE %1").arg(nameTable);

    if (!runSqlQuerry(sqlquery))
        return -1;

    return SUCCESS;
}

int dbManager::checkTable(QString nameTable)
{
    if (!isActive() || nameTable.isEmpty())
        return -1;

    QStringList tables = dataBase_users.tables();

    if (!tables.contains(nameTable))
        return -1;

    return SUCCESS;
}

int dbManager::createTableIfNeed(QString name, QVariantMap params)
{
    if (!isActive() || params.isEmpty() || name.isEmpty())
        return -1;

    QString querryString;
    querryString.clear();

    querryString.append("CREATE TABLE ").append(name).append(" ");
    querryString.append("( ");

    QStringList keys = params.uniqueKeys();
    for (int i = 0; i < keys.length(); i++)
    {
        QString type = params.value(keys.at(i)).toString();
        querryString.append(keys.at(i)).append(" ").append(type).append(", ");
    }

    //, space
    querryString.chop(2);
    querryString.append(" )");

    if (!runSqlQuerry(querryString))
        return -1;

    return SUCCESS;
}

//с не убывающей последовательностью!!!
int dbManager::createTableIfNeed(QString name, QVariantMap params, QStringList namesNotNull)
{

    if (namesNotNull.isEmpty())
        return createTableIfNeed(name, params);
    else
    {
        if (!isActive() || params.isEmpty() || name.isEmpty())
            return -1;

        QString querryString;
        querryString.clear();

        querryString.append("CREATE TABLE ").append(name).append(" ");
        querryString.append("( ");

        QStringList keys = params.uniqueKeys();
        for (int i = 0; i < keys.length(); i++)
        {
            QString type = params.value(keys.at(i)).toString();
            if (namesNotNull.contains(keys.at(i), Qt::CaseInsensitive))
                querryString.append(keys.at(i)).append(" ").append(type).append(" PRIMARY KEY AUTOINCREMENT NOT NULL, ");
            else
                querryString.append(keys.at(i)).append(" ").append(type).append(", ");
        }

        //, space
        querryString.chop(2);
        querryString.append(" )");

        if (!runSqlQuerry(querryString))
            return -1;

        return SUCCESS;
    }
}

bool dbManager::loadDrive(QString _drive)
{
    if (_drive.isEmpty())
        return false;

    if (isActive())
        closeDB();

    dataBase_users = QSqlDatabase::addDatabase(_drive);
    return true;
}

bool dbManager::loadDrive()
{
    QString driver = getSqlSets().type;
    return loadDrive(driver);
}

bool dbManager::loadDrive(sqlSets _sets)
{
    QString driver = _sets.type;
    return loadDrive(driver);
}

bool dbManager::loadPass(QString _drive)
{
    if (_drive.isEmpty())
        return false;

    dataBase_users.setPassword(_drive);
    return true;
}

bool dbManager::loadPass()
{
    QString driver = getSqlSets().password;
    return loadPass(driver);
}

bool dbManager::loadPass(sqlSets _sets)
{
    QString driver = _sets.password;
    return loadPass(driver);
}

bool dbManager::loadUser(QString _drive)
{
    if (_drive.isEmpty())
        return false;

    dataBase_users.setUserName(_drive);
    return true;
}

bool dbManager::loadUser()
{
    QString driver = getSqlSets().user;
    return loadUser(driver);
}

bool dbManager::loadUser(sqlSets _sets)
{
    QString driver = _sets.user;
    return loadUser(driver);
}
