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
