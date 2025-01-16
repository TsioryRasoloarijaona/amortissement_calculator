#ifndef MATERIEL_H
#define MATERIEL_H
#include<QDate>
#include<QVector>
#include<QDate>
using namespace std ;


class materiel
{
private :
    int id ;
    QString nom ;
    int duree_vie ;
    float taux_amortissement ;
    QDate date_aquisition ;

public:
    materiel();
    materiel(int , QString , int) ;
    materiel(int , QString , int , QDate) ;
    int get_id() ;
    QString get_nom() ;
    int get_dure_vie() ;
    float get_taux() ;
    QDate get_date() ;
    void set_date(QDate) ;
    static QVector<materiel> get_all() ;
    static materiel get_by_id (int) ;
    static void insert(QString nom , int duree_vie) ;
    static materiel get_by_name(QString);


};

#endif // MATERIEL_H
