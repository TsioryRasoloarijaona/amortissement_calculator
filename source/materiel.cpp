#include "../head/materiel.h"
#include "../head/db_manager.h"
#include<QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

materiel::materiel() {}

materiel::materiel(int id , QString n, int vie ) {
    this->id = id ;
    nom = n ;
    duree_vie = vie ;
    taux_amortissement = 100.0 /(float) vie ;
}

materiel::materiel(int id , QString n, int vie , QDate date) {
    this->id = id ;
    nom = n ;
    duree_vie = vie ;
    taux_amortissement = 100.0 /(float) vie ;
    date_aquisition = date ;
}


int materiel::get_dure_vie() {
    return duree_vie ;
}

QString materiel::get_nom(){
    return nom ;
}


int materiel::get_id(){
    return id ;
}

float materiel::get_taux(){
    return taux_amortissement ;
}

QDate materiel::get_date () {
    return date_aquisition ;
}

void materiel::set_date(QDate date) {
    date_aquisition = date ;
}

QVector<materiel> materiel::get_all() {
    QVector<materiel> materiels ;
    QSqlDatabase db = DB_manager::connection() ;
    QSqlQuery query ;
    if (query.exec("select * from materiel")) {
        while (query.next()) {
            int id = query.value("id").toInt() ;
            QString nom = query.value("nom").toString() ;
            int vie = query.value("duree_de_vie").toInt() ;
            materiel mat = materiel(id , nom , vie) ;
            materiels.append(mat) ;
        }
    }
    db.close() ;
    return materiels ;
}

materiel materiel::get_by_id(int id) {
    materiel mat ;
    QSqlDatabase db = DB_manager::connection() ;
    QSqlQuery query ;
    query.prepare("select * from materiel where id = :id") ;
    query.bindValue(":id" , id) ;

    if(query.exec() && query.next()){
        int id = query.value("id").toInt() ;
        QString nom = query.value("nom").toString();
        int vie = query.value("duree_de_vie").toInt() ;
        mat = materiel(id , nom , vie) ;
    } else {
        qDebug() << "Erreur d'exécution de la requête :" << query.lastError().text();
    }

    db.close() ;
    return mat ;
}

void materiel::insert(QString nom , int duree_vie) {
    QSqlDatabase db = DB_manager::connection() ;
    QSqlQuery query ;
    query.prepare("insert into materiel (nom , duree_de_vie) values (:nom , :duree_vie)") ;
    query.bindValue(":nom" , nom) ;
    query.bindValue(":duree_vie" , duree_vie) ;
    query.exec() ;
}

materiel materiel::get_by_name(QString nom) {
    materiel mat ;
    QSqlDatabase db = DB_manager::connection() ;
    QSqlQuery query ;
    query.prepare("select * from materiel order by id desc limit 1") ;
    query.bindValue(":nom" , nom) ;

    if(query.exec() && query.next()){
        int id = query.value("id").toInt() ;
        QString nom = query.value("nom").toString();
        int vie = query.value("duree_de_vie").toInt() ;
        mat = materiel(id , nom , vie) ;
    } else {
        qDebug() << "Erreur d'exécution de la requête :" << query.lastError().text();
    }

    db.close() ;
    return mat ;
}

optional<materiel> materiel::check_doublon(QString nom) {
    optional<materiel> mat ;
    QSqlDatabase db = DB_manager::connection() ;
    QSqlQuery query ;
    query.prepare("SELECT * FROM materiel WHERE nom =:nom COLLATE NOCASE;") ;
    query.bindValue(":nom" , nom) ;

    if(query.exec() && query.next()){
        int id = query.value("id").toInt() ;
        QString nom = query.value("nom").toString();
        int vie = query.value("duree_de_vie").toInt() ;
        mat = materiel(id , nom , vie) ;
    } else {
        qDebug() << "Erreur d'exécution de la requête :" << query.lastError().text();
    }

    db.close() ;
    return mat ;
}

void materiel::update_materiel(QString nom, int duree)
{
    DB_manager::connection();
    QSqlQuery query;
    query.prepare("UPDATE materiel SET duree_de_vie = :duree WHERE nom = :nom COLLATE NOCASE");
    query.bindValue(":duree", duree);
    query.bindValue(":nom", nom);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour:" << query.lastError().text();
        return;
    }

    qDebug() << "Mise à jour réussie. Lignes affectées :";
}







