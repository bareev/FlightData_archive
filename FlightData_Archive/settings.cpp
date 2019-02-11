#include "settings.h"
#include <QFile>

Settings::Settings()
{ 
}

int Settings::init()
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
    fileSets.setDefaultFormat(QSettings::IniFormat);
    fileSets.setPath(QSettings::IniFormat, QSettings::SystemScope, getFileName());

    QString dataBasePath = fileSets.value("GENERAL/DBPath", "").toString();
    if (dataBasePath.isEmpty())
    {
        ShowMessageBox(1, warning);
        dataBasePath = QString("N:\\НПЦ Нижний Новгород\\Общий обмен\\_Отдел 104\\Бареев\\fly_data");
    }

    generalSet.dataBasePath = dataBasePath;

    setState(nonecl);
    return SUCCESS;

}
