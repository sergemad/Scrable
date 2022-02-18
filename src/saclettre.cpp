#include "saclettre.hpp"
#include <stdlib.h>
#include <time.h>

saclettre::saclettre() {
   srand( time( NULL ) );
    nb=102;
    printf("Debut ");

    //tableau de lettre
    char  lettre[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    printf("tab lettre ");
    printf("%c \n",lettre[5]);

    //tableau de nombre correspondant au lettre
    int lettreNB[26]={9,2,2,3,15,2,2,2,8,1,1,5,3,6,6,2,3,6,6,6,6,2,1,1,1,1};
    printf("tab nb ");
    printf("%i \n",lettreNB[5]);

    //tableau de valeur correspondant au lettre
    int lettreV[26]={1,3,3,2,1,4,2,4,1,8,10,1,2,1,1,3,2,1,1,1,1,4,10,10,10,10};
    printf("tab val ");
    printf("%i \n",lettreV[5]);
    int l=0;
    //remplie le tableau de pion avec l'ordre alphabetique
    for(int j=0;j<nb;j++){
        
        sac[j].valeur=lettreV[l];
        sac[j].lettre=lettre[l];
        printf("%c // \n",lettre[l]);

        for (int i=1;i<lettreNB[l];i++){
            j++;
            sac[j].valeur=lettreV[l];
            sac[j].lettre=lettre[l];
           // printf("%i // \n",j);

        }
        l++;
    }
    
    
    printf("les valeur mise dans le tableau \n");
    printf("%c \n",sac[0].lettre);
    char tempchar;
    int tempval;
    int j;
    //melange le tableau de pion
    for(int i=0;i<nb;i++){
        j=rand()%nb;
        tempchar=sac[i].lettre;
        tempval=sac[i].valeur;
        sac[i].lettre=sac[j].lettre;
        sac[i].valeur=sac[j].valeur;
        sac[j].valeur=tempval;
        sac[j].lettre=tempchar;
    }
    

}

pion saclettre::pioche(){
    srand( time( NULL ) );
    int i=rand()%nb;
    pion temp=sac[i];
    for(int j=i;j<nb-1;j++){
        sac[j]=sac[j+1];
    }
    nb--;
    return temp;
}

void saclettre::remplace(pion p){
    srand( time( NULL ) );
    sac[nb]=p;
    nb++;
}
void saclettre::affichage(){
    for(int i=0;i<nb;i++){
        printf("%c | %i || \n",sac[i].lettre,sac[i].valeur);
    }
}
