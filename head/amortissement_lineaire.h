#ifndef AMORTISSEMENT_LINEAIRE_H
#define AMORTISSEMENT_LINEAIRE_H
#include <QDate>
#include "materiel.h"
#include <QVector>

class amortissement_lineaire
{
private :
    int annee ;
    float base_amortissement , valeur_net , cumule ;
     ;

public:
    amortissement_lineaire();
    amortissement_lineaire(int , float , float , float) ;
    static QVector<amortissement_lineaire> calculate (materiel , float) ;
    int get_annee () ;
    float get_base () ;
    float get_net() ;
    float get_cumule() ;


};

#endif // AMORTISSEMENT_LINEAIRE_H

