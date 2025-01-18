#ifndef AMORTISSEMENT_DEGRESSIF_H
#define AMORTISSEMENT_DEGRESSIF_H
#include <QVector>
#include "materiel.h"

class amortissement_degressif
{
private :
    int annee ;
    float base_amortie ,  taux_lineaire , taux_degressif , dotation , cumule , valeur_net ;

public:
    amortissement_degressif();
    amortissement_degressif(int , float , float , float , float , float , float) ;
    int get_annee () ;
    float get_taux_lineaire () ;
    float get_taux_degressif() ;
    float get_dotation () ;
    float get_cumule () ;
    float get_valeur_net () ;
    float get_base_amortie();
    static float coeff_degressif (int) ;
    static float dotation_calculate (float , float) ;
    static QVector<amortissement_degressif> calculate (materiel , float) ;

    };

#endif // AMORTISSEMENT_DEGRESSIF_H
