#include "Arbre_G.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <vector>
#define TAILLE_MAX 25
//constructeur


    
    
Arbre_G::Arbre_G(){
    //printf("debut constructeur");
    noeud *base=new noeud();
    
    bidon=base;
    FILE* fichier = NULL;

    fichier = fopen("data/dico.txt", "r+");
    
    if (fichier != NULL)
    {
        char mot[TAILLE_MAX]="";
        
            
            while (fgets(mot, TAILLE_MAX, fichier)!=NULL) {
                
                int nb=0;
                char temp;
                vector<thread> a;

                while (mot[nb]!='\n') {
                    nb++;
                }
                for(int i=nb;i>0;i--){
                    mot[i+1]=mot[i];
                }
                mot[1]='+';
                
                //a.push_back(thread (Arbre_G::ajout_mot,bidon,mot));
                ajout_mot(mot);
                //printf("le mot : %s",mot);
                int j=2;
                temp=mot[j];
                while(temp!='\n'){
                    for(int k=j-1;k>=0;k--){
                        mot[k+1]=mot[k];
                    }
                    mot[0]=temp;
                    j++;
                    temp=mot[j];
                    
                    //a.push_back(thread (Arbre_G::ajout_mot,bidon,mot));

                    ajout_mot(mot);
                    //printf("le mot : %s",mot);
                }
                for(int l=0;l<TAILLE_MAX;l++){
                    mot[l]='\0';
                }
               // for (int h=0; h<nb; h++) {
                   // a[h].join();
                //}

            }
            printf("OK dico complet");

       
        
        
        fclose(fichier);
    }
    else
    {
        // affiche un message d'erreur
        printf("Impossible d'ouvrir le fichier dico.txt /n");
    }
}

//ajouter un mot

void Arbre_G::ajout_mot(char mot[]){
    noeud* Ncourant=bidon;
    int i=0;
    while (mot[i]!='\n') {
        char temp=mot[i];
        //printf("%c \n",mot[i]);
        if(Ncourant->vef_voisin(temp)){
            if(temp=='+'){
                Ncourant=Ncourant->suivant[26];
            }else{
                Ncourant=Ncourant->suivant[int(temp)-65];
            }
            Ncourant->lettre=temp;
        }else {
            while (mot[i]!='\n') {
                temp=mot[i];
                noeud* newN=new noeud();
                newN->lettre=mot[i];
                if(temp=='+'){
                    Ncourant->suivant[26]=newN;
                    Ncourant->voisin[26]=true;
                    Ncourant=Ncourant->suivant[26];
                }else{
                    Ncourant->suivant[int(newN->lettre)-65]=newN;
                    Ncourant->voisin[int(newN->lettre)-65]=true;
                    Ncourant=Ncourant->suivant[int(newN->lettre)-65];
                }
                i++;
            }
            Ncourant->terminal=true;
            break;
        }
     i++;
    }
}


bool Arbre_G::recherche(char mot[]){
    noeud* Ncourant=bidon;
    int i=0;
    //printf("debut recherche\n");
    while (mot[i]!='\n') {
       // printf("Debut boucle\n");
        char temp=mot[i];
        if(Ncourant->vef_voisin(temp)){
           // printf("lettre validé verifions la suite\n");
            Ncourant=Ncourant->suivant[int(temp)-65];
            if(i==0 && !Ncourant->vef_voisin('+'))return false;
            if(i==0)Ncourant=Ncourant->suivant[26];
        }else {
            //printf("lettre non validé terminé\n");
            return false;
            }
        i++;
        }
    if(Ncourant->terminal==true){
       // printf("mot validé terminé\n");
        return true;
    }
return false;
}

void Arbre_G::ensemble(char mot[]){
    int nb=0;
    char temp;
    printf("le mot : %s \n",mot);
    while (mot[nb]!='\n') {
        nb++;
    }
    for(int i=nb;i>0;i--){
        mot[i+1]=mot[i];
    }
    mot[1]='+';
    printf( "notre mot %s \n",mot);
    int j=2;
    temp=mot[j];
    while(temp!='\n'){
        for(int k=j-1;k>=0;k--){
            mot[k+1]=mot[k];
        }
        mot[0]=temp;
        j++;
        temp=mot[j];
        printf( "notre mot %s ",mot);
    }
    
}
