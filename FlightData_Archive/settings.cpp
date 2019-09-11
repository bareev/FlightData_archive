#include "settings.h"
#include <QFile>
#include <QObject>
#include <QStringList>
#include <QFileInfo>
#include <QDir>

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


    QString dataBasePath = readingParam("DBPath", QString::fromUtf8("N:/НПЦ Нижний Новгород/Общий обмен/_Отдел 104/Бареев/fly_data"), 1).toString();
    QString dbFile = readingParam("DBFile", dataBasePath + QString::fromUtf8("/fly_data_archive.db"), 5).toString();
    QString dbType = readingParam("DataBase/Type", "QSQLITE", 6).toString();
    QString dbUserName = readingParam("DataBase/User", "user", 7).toString();
    QString dbPassword = readingParam("DataBase/Password", "12345678", 8).toString();
    QString fileCyril = readingParam("FileCyril/path", "/config/CyrilToLatin.txt", 9).toString();

    generalSet.dataBasePath = dataBasePath;
    generalSet.dbFile = dbFile;
    generalSet.database_param.dbName = dbFile;
    generalSet.database_param.password = dbPassword;
    generalSet.database_param.type = dbType;
    generalSet.database_param.user = dbUserName;
    generalSet.fileCyril = fileCyril;

    //setState(nonecl);
    return SUCCESS;

}


void Settings::writeAll()
{
    GenSet _s = getValue();
    fileSets->setValue("DBPath", QString(_s.dataBasePath.toUtf8()));
    fileSets->setValue("DBFile", QString(_s.dbFile.toUtf8()));
    return;
}

QString Settings::cyrilToLatin(QString symbol)
{
    QString res;
    res.clear();
    for (int i = 0; i < symbol.length(); i++)
        res.append(cyrilic(symbol.at(i)));
    return res;
}

QString Settings::cyrilic(QChar symbol)
{
    QString res = QString(symbol);
    QFile f(generalSet.fileCyril);
    if (f.open(QIODevice::ReadOnly))
    {
        while (!f.atEnd())
        {
            QString read = f.readLine();

            //убираем лишние символы
            int pos1 = read.indexOf("\r");
            int pos2 = read.indexOf("\n");

            if (pos1 > -1 && pos2 > pos1)
                read = read.left(pos1);
            else if (pos1 == -1 && pos2 > 0)
                read = read.left(pos2);
            else if (pos2 > -1 && pos1 > pos2)
                read = read.left(pos2);
            else if (pos2 == -1 && pos1 > 0)
                read = read.left(pos1);
            //end - убираем лишние символы

            QStringList listRead = read.split(";");
            if (listRead.length() > 0)
            {
                if (!res.compare(listRead.at(0)))
                {
                    if (listRead.length() > 1)
                        res = listRead.at(1);
                    else
                        res = "";
                    break;
                }
            }
        }
        f.close();
    }

    return res;
}

bool Settings::removePath(const QString &path)
{
    bool result = true;
    QFileInfo info(path);
    if (info.isDir())
    {
        QDir dir(path);
        foreach (const QString &entry, dir.entryList(QDir::AllDirs | QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot)) {
            result &= removePath(dir.absoluteFilePath(entry));
        }
        if (!info.dir().rmdir(info.fileName()))
            return false;
    }
    else
    {
        result = QFile::remove(path);
    }
    return result;
}
