#ifndef STRUCTS_H
#define STRUCTS_H
#include <QString>


#define GENERAL_DATABASE_NAME "general_database_name"
#define RLS_TYPE_DATABASE_NAME "rls_type_database_name"
#define PLACE_DATABASE_NAME "place_database_name"
#define STATE_POINTS_DATABASE_NAME "state_points_database_name"

#define SUCCESS 0

#define INPUT_FILES 0
#define OUTPUT_FILES 1

#define TYPE 1
#define PLACE 2
#define COORDS 3

//режим редактирования или записи нового
enum formType
{
    noneRecord = 0,
    newRecord,
    updateRecord
};

enum WhoEdit
{
    noneEdit = 0,
    rlsEdit,
    placeEdit,
    tsEdit
};

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
