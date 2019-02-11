#ifndef STRUCTS_H
#define STRUCTS_H
#include <QString>
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
};



#endif // STRUCTS_H
