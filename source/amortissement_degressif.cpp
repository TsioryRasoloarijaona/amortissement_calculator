#include "../head/amortissement_degressif.h"

amortissement_degressif::amortissement_degressif() {}

//taux_lineaire , taux , dotation , cumule , valeur_net

amortissement_degressif::amortissement_degressif(int annee, float taux_lineaire, float cumule, float valeur_net ,float taux_degressif , float base_amortie , float dotation){
    this->annee = annee ;
    this->taux_lineaire = taux_lineaire ;
    this->taux_degressif = taux_degressif ;
    this->dotation = dotation ;
    this->cumule = cumule ;
    this->valeur_net = valeur_net ;
    this->base_amortie = base_amortie ;
} ;

int amortissement_degressif::get_annee() {
    return annee;
}


float amortissement_degressif::get_taux_lineaire() {
    return taux_lineaire;
}

float amortissement_degressif::get_taux_degressif() {
    return taux_degressif;
}


float amortissement_degressif::get_dotation() {
    return dotation;
}


float amortissement_degressif::get_cumule() {
    return cumule;
}


float amortissement_degressif::get_valeur_net() {
    return valeur_net;
}

float amortissement_degressif::get_base_amortie()
{
    return base_amortie;
}

float amortissement_degressif::coeff_degressif(int annee_utilisation) {
    float n = 0.0  ;
    if (annee_utilisation >= 3 and annee_utilisation <= 4 ) {
        n = 1.25 ;
    }
    else if(annee_utilisation >= 5 and annee_utilisation <= 6){
        n = 2 ;
    }
    else if (annee_utilisation >6) {
        n = 2.25 ;
    }
    return n ;
}

float amortissement_degressif::dotation_calculate(float taux , float base) {
    return (taux * base) / 100 ;
}


QVector<amortissement_degressif> amortissement_degressif::calculate(materiel m , float prix) {
    QVector<amortissement_degressif> results ;
    int duree_vie = m.get_dure_vie()  ;
    int mois_total = duree_vie * 12 ;
    float coefficient = coeff_degressif(duree_vie) ;
    float base = prix ;

    QDate date_aquision = m.get_date() ;
    int mois = 13 - date_aquision.month() ;
    int year = date_aquision.year() ;
    float cumule_dotation = 0.0;
    int nbre_annee = m.get_date().month() > 1 ? duree_vie : duree_vie - 1 ;

    for (int i = 0 ; i <= nbre_annee ; i++){
        int mois_utiliser;

        if (i == 0) {
            mois_utiliser = mois;
        } else if (i == nbre_annee && mois != 12) {
            mois_utiliser = 12 - mois;
        } else {
            mois_utiliser = 12;
        }
        int annee = year ;
        float base_ammortissement = base ;
        float taux_lineaire = (float)mois_utiliser / (float)mois_total * 100.0;
        float taux_degressif = ( 100 / duree_vie ) * coefficient * mois_utiliser / 12;
        float taux_utiliser = taux_lineaire > taux_degressif ? taux_lineaire : taux_degressif;
        float dotation = base * (taux_utiliser / 100) ;
        float valeur_net = base - dotation;
        cumule_dotation = cumule_dotation + dotation;

        amortissement_degressif result = amortissement_degressif(annee,
                                                                 taux_lineaire,
                                                                 cumule_dotation,
                                                                 valeur_net,
                                                                 taux_degressif,
                                                                 base_ammortissement,
                                                                 dotation);

        results.append(result);

        year++;
        base = valeur_net;
        mois_total = mois_total - mois_utiliser;
    }

    return results ;
}


