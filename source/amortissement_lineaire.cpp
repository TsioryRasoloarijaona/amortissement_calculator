#include "../head/amortissement_lineaire.h"

amortissement_lineaire::amortissement_lineaire() {}

amortissement_lineaire::amortissement_lineaire(int annee, float base , float cumule , float VN){
    this->annee = annee ;
    base_amortissement = base ;
    this->cumule = cumule ;
    valeur_net = VN ;
}

int amortissement_lineaire::get_annee(){
    return annee ;

}

float amortissement_lineaire::get_base() {
    return base_amortissement ;
}

float amortissement_lineaire::get_cumule(){
    return cumule ;
}

float amortissement_lineaire::get_net() {
    return valeur_net ;
}

QVector<amortissement_lineaire> amortissement_lineaire::calculate(materiel m , float prix) {
    QVector<amortissement_lineaire> resultat ;
    float cumul_compteur = 0.0 ;
    int duree_vie = m.get_dure_vie() ;
    int annee_compteur = m.get_date().year() ;
    int mois_utilisation = 13 - m.get_date().month() ;

    int fin ;
    if (m.get_date().month() > 1 ) {
        fin = duree_vie ;
    }else {
        fin = duree_vie - 1 ;
    }
    for (int i = 0 ; i <= fin ; i++) {
        int n ;
        if(i == 0) {
            n = mois_utilisation ;
        }
        else if (i == fin && mois_utilisation != 12){
            n = 12 - mois_utilisation ;
        }else {
          n = 12 ;
        }

        int annee = annee_compteur ;
        float base = prix * (m.get_taux() / 100.0) *  (n/12.0);
        float cumule = cumul_compteur + base ;
        float valeur_net = prix - cumule ;
        amortissement_lineaire amortissement = amortissement_lineaire(annee , base , cumule , valeur_net) ;
        resultat.append(amortissement) ;
        annee_compteur++ ;
        cumul_compteur = cumul_compteur + base ;
    }
    return resultat ;
}
