#ifndef DB_MANAGER_H
#define DB_MANAGER_H
#include <QtSql/QSqlDatabase>

class DB_manager
{
public:
    DB_manager();
    static QSqlDatabase connection() ;

};

#endif
