#include <iostream>
using namespace std;

#pragma once

 struct pion{
    char lettre;
    int valeur;
};

class saclettre{
public:
    int nb;
     int lettreV[26]={1,3,3,2,1,4,2,4,1,8,10,1,2,1,1,3,2,1,1,1,1,4,10,10,10,10};
    pion sac[102];
    //constructeur
    saclettre();
    //affichage du sac de lettre
    void affichage();
    //piocher une lettre
    pion pioche();
    //met une lettre dans le sac
    void remplace(pion p);
};

