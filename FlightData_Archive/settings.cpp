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

int Settings::initSets()
{
    //проверка валидности файла настроек
    QFile sets(getFileName());
    bool op = sets.open(QIODevice::ReadWrite);
    if (!op || !sets.isReadable() || !sets.isWritable())
    {
        ShowMessageBox(0, critical);
    }
    if (sets.isOpen())
        sets.close();

    //что возвращаем в итоге при инициализации
    if (getState() != nonecl)
        return -1;

    //получаем данные
    fileSets = new QSettings(getFileName(), QSettings::IniFormat);
    fileSets->setIniCodec("UTF-8");
    fileSets->sync();

    //путь к базе данных
    QString dataBasePath = fileSets->value("General/DBPath", "").toString();
    if (dataBasePath.isEmpty())
    {
        ShowMessageBox(1, warning);
        dataBasePath = QString::fromUtf8("N:/НПЦ Нижний Новгород/Общий обмен/_Отдел 104/Бареев/fly_data");
    }

    //имя базы данных
    QString dbFile = fileSets->value("General/DBFile", "").toString();
    if (dbFile.isEmpty())
    {
        ShowMessageBox(5, warning);
        dbFile = dataBasePath + QString::fromUtf8("/fly_data_archive.db");
    }

    generalSet.dataBasePath = dataBasePath;
    generalSet.dbFile = dbFile;

    setState(nonecl);
    return SUCCESS;

}

void Settings::writeAll()
{
    GenSet _s = getValue();
    fileSets->setValue("General/DBPath", QString(_s.dataBasePath.toUtf8()));
    fileSets->setValue("General/DBFile", QString(_s.dbFile.toUtf8()));
    return;
}
