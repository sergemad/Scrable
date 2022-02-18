#pragma once
#include "saclettre.hpp"
#include "Arbre_G.hpp"
#include "board.hpp"
#include <vector>
#include <unistd.h>

struct joueur{
    pion liste_lettre[7];
    int score;
    
    joueur(saclettre & sac){
        score=0;
        for(int i=0;i<7;i++){
            liste_lettre[i]=sac.pioche();
        }
    }
    
    void reset(saclettre & sac){
        for(int i=0;i<7;i++){
        sac.remplace(liste_lettre[i]);
           liste_lettre[i]=sac.pioche();
        }
    }
     void jpioche(int nbl,saclettre & sac){
        for(int i=0;i<7;i++){
            if(liste_lettre[i].valeur==NULL && sac.nb>0)
            liste_lettre[i]=sac.pioche();
        }
    }
    
};

class Partie{
public:
    Arbre_G Dico;
    saclettre* sac=new saclettre();
    joueur *J1=new joueur(*sac);
    Board B;
    
    //constructeur de la partie
    Partie();
    //liste des coup possible
    void Liste_coup();
    //liste de coup possible a partir d'une lettre
     vector <string> Liste_C_poss(noeud * A, char tab[7],vector <string>   Lmot,vector <char> mot,int pos,int posB,bool vert,bool plus);
    //me permet de determiner si les mots ecrits existent ou pas dans le dico
    bool motexiste(bool vert ,int pos,char l);
    
    //meilleur coup qui fera tous les calculs et les comparaisons pour connaitre le meilleur coup.
    int meilleurcoup(int pos, vector <string> Em, vector <string> & Mc,int & id,bool vert);
    
    //ecris le meilleur coup dans le board et piche de nouveau pion;
    void ecriture(int pos,int score,string ME,int idM,int taille,bool vert);
};
