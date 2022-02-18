
#ifndef ARBRE_G_HPP
#define ARBRE_G_HPP
#include <cassert>
#include <new>
using namespace std;

class noeud{
    friend class Arbre_G;
public:
    char lettre;
    bool voisin[27];
    bool terminal=false;
    noeud* suivant[27];
    //constructeur de noeud
    noeud(){
    lettre='\0';
    for(int i=0;i<27;i++){
        suivant[i]=nullptr;
    }
        for(int i=0;i<27;i++){
            voisin[i]=false;
        }
    };
    bool vef_voisin(char l){
        if(l=='+')return voisin[26];
        return voisin[int(l)-65];
    };
    
    
    
};

class Arbre_G {
public:
    noeud *bidon=nullptr;
    //constructeur
    Arbre_G();
    //ajout d'un mot
    void ajout_mot(char mot[]);
    //recherche d'un mot
    bool recherche(char mot[]);
    //ensemble de mots
    void ensemble(char mot[]);
    
};
#endif
