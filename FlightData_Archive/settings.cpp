#include "settings.h"
#include <QFile>
#include <QObject>

Settings::Settings()
{ 
}

Settings::~Settings()
{
    if (fileSets)
        delete fileSets;
}

QVariant Settings::readingParam(QString param, QVariant defaultVal, int numberError)
{
    //путь к базе данных
    QVariant def;
    def.clear();
    QVariant res = fileSets->value(param, def);
    if (res.isNull())
    {
        //ShowMessageBox(numberError, warning);
        res = defaultVal;
    }

    return res;
}

int Settings::initSets()
{
    //проверка валидности файла настроек
    QFile sets(getFileName());
    bool op = sets.open(QIODevice::ReadWrite);
    if (!op || !sets.isReadable() || !sets.isWritable())
    {
        op = false;
        //ShowMessageBox(0, critical);
    }
    if (sets.isOpen())
        sets.close();

    //что возвращаем в итоге при инициализации
    if (!op)
        return -1;

    //получаем данные
    fileSets = new QSettings(getFileName(), QSettings::IniFormat);
    fileSets->setIniCodec("UTF-8");
    fileSets->sync();


    QString dataBasePath = readingParam("General/DBPath", QString::fromUtf8("N:/НПЦ Нижний Новгород/Общий обмен/_Отдел 104/Бареев/fly_data"), 1).toString();
    QString dbFile = readingParam("General/DBFile", dataBasePath + QString::fromUtf8("/fly_data_archive.db"), 5).toString();
    QString dbType = readingParam("DataBase/Type", "QSQLITE", 6).toString();
    QString dbUserName = readingParam("DataBase/User", "user", 7).toString();
    QString dbPassword = readingParam("DataBase/Password", "12345678", 8).toString();


    generalSet.dataBasePath = dataBasePath;
    generalSet.dbFile = dbFile;
    generalSet.database_param.dbName = dbFile;
    generalSet.database_param.password = dbPassword;
    generalSet.database_param.type = dbType;
    generalSet.database_param.user = dbUserName;

    //setState(nonecl);
    return SUCCESS;

}


void Settings::writeAll()
{
    GenSet _s = getValue();
    fileSets->setValue("General/DBPath", QString(_s.dataBasePath.toUtf8()));
    fileSets->setValue("General/DBFile", QString(_s.dbFile.toUtf8()));
    return;
}
