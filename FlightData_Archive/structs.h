#ifndef STRUCTS_H
#define STRUCTS_H
#include <QUrl>
#define SUCCESS 0


enum msgType
{
    none,
    warning,
    error,
    critical
};

enum closeEnable
{
    nonecl,
    closeT,
    enableT,
    enableAll
};


struct GenSet
{
    QString dataBasePath;
    QString dbFile;
};

struct sqlSets
{
    QString password;
    QString dbName;
    QString type;
    QString user;
};



#endif // STRUCTS_H
