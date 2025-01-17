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

void DB_manager::closeConnection() {
    if (QSqlDatabase::contains("amortissement_connection")) {
        QSqlDatabase db = QSqlDatabase::database("amortissement_connection");
        if (db.isOpen()) {
            db.close(); // Fermer la connexion
            QSqlDatabase::removeDatabase("amortissement_connection");
            qDebug() << "Connexion SQLite fermée et supprimée.";
        }
    }
}

DB_manager::~DB_manager() {
    closeConnection();
}
