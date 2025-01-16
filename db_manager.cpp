#include "db_manager.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

DB_manager::DB_manager() {}

QSqlDatabase DB_manager::connection() {
    QString path = "/home/tsiory/Documents/sqlite_db/amortissement.db" ;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path) ;

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données :" << db.lastError().text();

    }
    return db ;
}
