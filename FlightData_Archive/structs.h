#ifndef STRUCTS_H
#define STRUCTS_H
#include <QString>


#define GENERAL_DATABASE_NAME "general_database_name"
#define RLS_TYPE_DATABASE_NAME "rls_type_database_name"
#define PLACE_DATABASE_NAME "place_database_name"

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

struct sqlSets
{
    QString password;
    QString dbName;
    QString type;
    QString user;
};

struct GenSet
{
    QString dataBasePath;
    QString dbFile;
    sqlSets database_param;
};





#endif // STRUCTS_H
