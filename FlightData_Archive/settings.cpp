#include "settings.h"
#include <QFile>

Settings::Settings()
{ 
}

void Settings::init()
{
    QFile sets(getFileName());

    if (!sets.isReadable() || !sets.isWritable())
    {
        ShowMessageBox(0, critical);
    }

}
