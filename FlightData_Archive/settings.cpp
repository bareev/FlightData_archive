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
    QString dataBasePath = fileSets->value("general/DBPath", "").toString();
    if (dataBasePath.isEmpty())
    {
        ShowMessageBox(1, warning);
        dataBasePath = QString::fromUtf8("N:/НПЦ Нижний Новгород/Общий обмен/_Отдел 104/Бареев/fly_data");
    }

    generalSet.dataBasePath = dataBasePath;

    setState(nonecl);
    return SUCCESS;

}

void Settings::writeAll()
{
    GenSet _s = getValue();
    fileSets->setValue("general/DBPath", QString(_s.dataBasePath.toUtf8()));
    return;
}
