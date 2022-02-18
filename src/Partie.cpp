 #include "Partie.hpp"
#include <sstream>


Partie::Partie(){
    
    std::cout << B << std::endl ;
    printf("lettre du joueur 1 et il reste %i lettre dans le sac\n",sac->nb);
    for(int i=0;i<7;i++){
        printf("  %c  ",J1->liste_lettre[i].lettre);
    }
    printf("\n");
    //sleep(15);
    while(sac->nb>0){
    printf("lettre du joueur 1 et il reste %i lettre dans le sac\n",sac->nb);

    Liste_coup();
        std::cout<<"score "<<J1->score<<endl;
        printf("lettre du joueur 1 et il reste %i lettre dans le sac\n",sac->nb);
        for(int i=0;i<7;i++){
            printf("  %c  ",J1->liste_lettre[i].lettre);
        }
        printf("\n");
        sleep(1);
    }
}

void Partie::Liste_coup(){
    noeud * A=nullptr; // ici ou on mettra le dico
    //pour le meilleur coup on utilisera Lcoup pour stocker le meilleur coup de chaque position puis on determinera le meilleur coup parmi eux.
    vector <string> Lcoups;
    char lettrej[7];
    for(int k=0;k<7;k++){
        lettrej[k]=J1->liste_lettre[k].lettre; //mets les lettres dans un tableau
    }
    vector <char> mottemp;
    vector <string> Mc;//tab meilleur mot possible pour chaque cases verticale
    vector <int> Motpos;//tab d'indentifiant des cases ou on peut écrire en verticale
    vector <int> Motpoints;// tab ou sont stockés tous les points des meillleurs coup en verticale
    vector <string> McH; // meme utilité que Mc mais pour l'horizontale
    vector <int> MotpointsH;//meme utilité que Motpoints mais pour l'horizontale
    vector <int> MidH;//identifiant du meilleur coup possible a l'horizontale
    vector <int> MidV;//identifiant du meilleur coup possible a la verticale
    bool reset=true;
    int temp;
    int i=157;
    int j=0;
    for( i=0;i<225;i++){
        if(B.spots[i].letter!=0){
             vector <string> Emp;//esemble des mots a la verticale
            vector <string> EmpH;//esemble des mots a l'horizontale
            MidH.push_back(NULL);
            MidV.push_back(NULL);
            A=Dico.bidon->suivant[int(B.spots[i].letter-65)];
            mottemp.clear();
            mottemp.push_back(B.spots[i].letter);
            Emp=Liste_C_poss(A,lettrej, Emp,mottemp,i,i,true,false);//recherche mot verticale
            EmpH=Liste_C_poss(A,lettrej, EmpH,mottemp,i,i,false,false);//recherche mot horizontale
                       Motpos.push_back(i);
            if(Emp.size()>0){
                reset=false;
            temp=meilleurcoup(i,Emp,Mc,MidV[j],true);//recherche du meilleur coup possible sur la case i en verticale
            Motpoints.push_back(temp);
            }else{
                Motpoints.push_back(0);
                Mc.push_back("");
            }
            if(EmpH.size()>0){
                reset=false;
            temp=meilleurcoup(i,EmpH,McH,MidH[j],false);//recherche du meilleur coup possible sur la case i en horizontale
            MotpointsH.push_back(temp);
            }else{
                MotpointsH.push_back(0);
                McH.push_back("");
            }
            j++;
        }
        
        
    }
    if(j==0){//lorsqu'on a aucune lettre sur le BOARD c'est a dire au debut de la parti uniquement
        vector <string> Emp;
        vector <string> EmpH;
        MidH.push_back(NULL);
        MidV.push_back(NULL);
        A=Dico.bidon;
        mottemp.clear();
        Emp=Liste_C_poss(A,lettrej, Emp,mottemp,112,112,true,false);
        EmpH=Liste_C_poss(A,lettrej, EmpH,mottemp,112,112,false,false);
        Motpos.push_back(112);
        
        if(Emp.size()>0){
        reset=false;
        temp=meilleurcoup(112,Emp,Mc,MidV[j],true);
        Motpoints.push_back(temp);
        }else{
            Motpoints.push_back(0);
            Mc.push_back("");
        }
        if(EmpH.size()>0){
            reset=false;
        temp=meilleurcoup(112,EmpH,McH,MidH[j],false);
        MotpointsH.push_back(temp);
        }else{
            MotpointsH.push_back(0);
            McH.push_back("");
        }
        j++;
    }
    if(reset==true){
        std::cout<<"pas de solution donc on échange nos lettre"<<endl;
        J1->reset(*sac);
        }else{
            int idv=0;
            for(i=1;i<j;i++){
                if(Motpoints[idv]<Motpoints[i]){
                    idv=i;
                }
            }
    
            int idh=0;
            for(i=1;i<j;i++){
                if(MotpointsH[idh]<MotpointsH[i]){
                    idh=i;
                }
            }
            if(McH[idh]>Mc[idv]){
                std::cout <<"le meilleur mots est " <<McH[idh]<<" avec "<<MotpointsH[idh]<<" points de pos "<<Motpos[idh]<< "pos de lettre "<<MidH[idh]<<endl;
                ecriture(Motpos[idh],MotpointsH[idh],McH[idh],MidH[idh],McH[idh].size(),false);
                std::cout << B << std::endl ;
                
            }else {
                std::cout <<"le meilleur mots est " <<Mc[idv]<<" avec "<<Motpoints[idv]<<" points de pos "<<Motpos[idv]<< "pos de lettre "<<MidV[idv]<<endl;
                ecriture(Motpos[idv],Motpoints[idv],Mc[idv],MidV[idv],Mc[idv].size(),true);
                std::cout << B << std::endl;
                
            }
    
        }
}
vector <string> Partie::Liste_C_poss(noeud * A, char tab[7],vector <string>  Lmot,vector <char>  mot,int pos,int posB,bool vert,bool plus){
    //plus nous permet de savoir si on est passé sur la lettre + ou pas
    //l'objectif est qu'a l'aide de la position dans le board , du sens de lecture qu'on determine la liste des coups possibles a écrire
    //tout ce qui est a gauche du + est a ecrire derriere la lettre et ce qui est a droite est a ecrire devant la lettre
    //pour ecrire on verifie d'abord si une lettre est du board est sur notre chemin si oui on continu et si non on teste sur chaque lettre qu'on a
    //std::cout<< "liste coup debut"<<endl;
    
    if(pos<0 || pos>224){//pour ne pas ecrire hors du cadre
        return Lmot;
    }
    
    
    if(vert==true){
        
        if(plus){
            while(B.spots[pos+15].letter!=0 ){
                //std::cout<< B.spots[pos+15].letter<< " pos "<< pos+15<<" dicopos "<<int(B.spots[pos+15].letter)-65 <<endl;
                //std::cout<< "premiere boucle +"<<endl;
                if(A->vef_voisin(B.spots[pos+15].letter) && int(B.spots[pos+15].letter)-65>=0 && int(B.spots[pos+15].letter)-65<27){
                pos=pos+15;
                A=A->suivant[int(B.spots[pos].letter-65)];
                //mot.resize(mot.size()+1);
                //mot.push_back(B.spots[pos+15].letter);
                //std::cout<< "teste +"<< A->lettre<<endl;
                mot.push_back(A->lettre);
                //std::cout<< "teste +"<<endl;
                }else{
                    return Lmot;
                }
            }
        }else{
            while(B.spots[pos-15].letter!=0 ){
                //std::cout<< "premiere boucle -"<<endl;
                if(A->vef_voisin(B.spots[pos-15].letter) && int(B.spots[pos-15].letter)-65>=0 && int(B.spots[pos-15].letter)-65<27){
                A=A->suivant[int(B.spots[pos-15].letter-65)];
               // mot.push_back(B.spots[pos-15].letter);
                mot.push_back(A->lettre);
                pos=pos-15;
                char temp=A->lettre;
                for (int s=mot.size()-1;s>0;s--){
                    mot[s]=mot[s-1];
                }
                mot[0]=temp;
                //std::cout<< "OK"<<endl;
                }else{
                    return Lmot;
                }
            }
        }
    }else {
        if(pos<posB-posB%15 || pos>posB+(14-(posB%15))) {//pour ne pas ecrire hors du cadre
            return Lmot;
        }
        
        if(plus){
            while(B.spots[pos+1].letter!=0 ){
               // std::cout<< B.spots[pos+1].letter<< " pos "<< pos+1<<endl;
                //std::cout<< "premiere boucle +"<<endl;
                if(A->vef_voisin(B.spots[pos+1].letter) && int(B.spots[pos+1].letter)-65>=0 && int(B.spots[pos+1].letter)-65<27){
                pos=pos+1;
                A=A->suivant[int(B.spots[pos].letter-65)];
                //mot.resize(mot.size()+1);
                //mot.push_back(B.spots[pos+15].letter);
                //std::cout<< "teste +"<< A->lettre<<endl;
                mot.push_back(A->lettre);
                //std::cout<< "teste +"<<endl;
                }else{
                    return Lmot;
                }
            }
        }else{
            while(B.spots[pos-1].letter!=0 ){
                //std::cout<< "premiere boucle -"<<endl;
                if(A->vef_voisin(B.spots[pos-1].letter) && int(B.spots[pos-1].letter)-65>=0 && int(B.spots[pos-1].letter)-65<27){
                A=A->suivant[int(B.spots[pos-1].letter-65)];
               // mot.push_back(B.spots[pos-15].letter);
                mot.push_back(A->lettre);
                pos=pos-1;
                char temp=A->lettre;
                for (int s=mot.size()-1;s>0;s--){
                    mot[s]=mot[s-1];
                }
                mot[0]=temp;
                //std::cout<< "OK"<<endl;
                }else{
                    return Lmot;
                }
            }
        }
                
    }
    
    //inserer le mot si il est valide ou pas en suivant les normes du scrables
    int t=0;
    bool ecris=false;
    for(int i=0;i<7;i++){
        if(tab[i]=='\0'){
            t++;
        }
        if(t>1)ecris=true;
    }
    
    if(A->terminal && ecris){
        std::string s(mot.begin(), mot.end());
        bool dejaecris=false;
        int z=0;
        while (!dejaecris && z<Lmot.size() ){
            if(Lmot[z]==s)dejaecris=true;
            z++;
        }
        if(!dejaecris){
            Lmot.push_back(s);
            //std::cout<< "mot valide "<< s <<endl;
        }
    }
    
    char lettrej[7];
    vector <char> mottemp;
    for(int i=0;i<7;i++){
        //std::cout<< "testlettre "<< i <<endl;

        //std::cout<< tab[i]<<endl;
        if(tab[i]!='\0'){
            if(A->vef_voisin(tab[i])){
                if(plus){//verification de la position dans l'arbre
                    //lettrej=tab;
                    for(int j=0;j<7;j++){
                        lettrej[j]=tab[j];
                    }
                    lettrej[i]='\0';
                    mottemp=mot;
                    //mottemp.resize(mot.size());
                    mottemp.push_back(tab[i]);
                    //mottemp[mottemp.size()-1]=tab[i];
                    //appelle de la fonction liste coup a ce niveau
                    if(vert==true){
                        if(motexiste(false,pos+15,A->suivant[int(tab[i]-65)]->lettre)){
                            Lmot=Liste_C_poss(A->suivant[int(tab[i]-65)],lettrej, Lmot,mottemp,pos+15,posB,true,plus);
                        }
                    
                    }else{
                        if(motexiste(true,pos+1,A->suivant[int(tab[i]-65)]->lettre)){
                            Lmot=Liste_C_poss(A->suivant[int(tab[i]-65)],lettrej, Lmot,mottemp,pos+1,posB,false,plus);
                        }
                        
                    }
                }else{
                    //lettrej=tab;
                    //std::cout<< "entree"<<endl;

                    for(int j=0;j<7;j++){
                        lettrej[j]=tab[j];
                    }
                    lettrej[i]='\0';
                    mottemp=mot;
                    mottemp.push_back(tab[i]);
                    for (int s=mottemp.size()-1;s>0;s--){
                        mottemp[s]=mottemp[s-1];
                    }
                    mottemp[0]=tab[i];
                    //appelle de la fonction liste coup a ce niveau
                    if(vert==true){
                        if(motexiste(false,pos-15,A->suivant[int(tab[i]-65)]->lettre)){
                            Lmot=Liste_C_poss(A->suivant[int(tab[i]-65)],lettrej, Lmot,mottemp,pos-15,posB,true,plus);
                        }
                    
                    }else{
                        if(motexiste(true,pos-1,A->suivant[int(tab[i]-65)]->lettre)){
                            Lmot=Liste_C_poss(A->suivant[int(tab[i]-65)],lettrej, Lmot,mottemp,pos-1,posB,false,plus);
                        }
                }
            }
            
            if(A->vef_voisin('+') && plus==false){
                //lettrej=tab;
                for(int j=0;j<7;j++){
                    lettrej[j]=tab[j];
                }
                mottemp=mot;
                //pos=posB;
                //appelle de la fonction liste coup a ce niveau
                //std::cout<< "plus"<<endl;
                Lmot=Liste_C_poss(A->suivant[26],lettrej, Lmot,mottemp,posB,posB,vert,true);

            }
        }
    }
    
    }
    return Lmot;
}
bool Partie::motexiste(bool vert,int pos,char l) {
    int dg=pos;
    int dd=pos;
    vector <char> motG;
    vector <char> motD;

    if(vert){
        while (B.spots[dg-15].letter!=0 ) {
            motG.push_back(B.spots[dd-15].letter);
            for (int s=motG.size()-1;s>0;s--){
                motG[s]=motG[s-1];
            }
            motG[0]=B.spots[dd-15].letter;
            dg=dg-15;
        }
        while (B.spots[dd+15].letter!=0 ) {
            motD.push_back(B.spots[dd+15].letter);
            dd=dd+15;
        }
    }else{
        while (B.spots[dg-1].letter!=0 ) {
            motG.push_back(B.spots[dd-1].letter);
            for (int s=motG.size()-1;s>0;s--){
                motG[s]=motG[s-1];
            }
            motG[0]=B.spots[dd-1].letter;
            dg=dg-1;
        }
        while (B.spots[dd+1].letter!=0 ) {
                motD.push_back(B.spots[dd+1].letter);
                dd=dd+1;
        }
    }
    motG.push_back(l);
    char mot[motG.size()+motD.size()+1];
    mot[0]=motG[0];
    mot[1]='+';
    int i=2;
    for(int j=1;j<motG.size();j++){
        mot[i]=motG[j];
        i++;
    }
    for(int k=0;k<motD.size();k++){
        mot[i]=motD[k];
        i++;
    }
    //std::cout<<"mot a tester "<<mot <<i<<endl;
    if(i<=2){
        return true;
    }else{
        return Dico.recherche(mot);
    }
}


int Partie::meilleurcoup(int pos,vector <string> Em, vector <string> & Mc, int & id,bool vert){
    //utilise vert pour determiner la direction d'écriture
    
        //std::cout<< "OK 1"<<endl;
        //pour les mots de positions pos
    if(id!=NULL){//ici je calcule les points aux allentours du mots que j'ecris
        if(vert==true){
            int posG=pos-15;
            int posD=pos+15;
            int score=0;
            while(B.spots[posG].letter!=0){
                score=score+sac->lettreV[int(B.spots[posG].letter)-65];
                posG=posG-15;
            }
            while(B.spots[posD].letter!=0){
                score=score+sac->lettreV[int(B.spots[posD].letter)-65];
                posD=posD+15;
            }
            return score;
        }else{
            int posG=pos-1;
            int posD=pos+1;
            int score=0;
            while(B.spots[posG].letter!=0){
                score=score+sac->lettreV[int(B.spots[posG].letter)-65];
                posG=posG-1;
            }
            while(B.spots[posD].letter!=0){
                score=score+sac->lettreV[int(B.spots[posD].letter)-65];
                posD=posD+1;
            }
            return score;
        }
    }else{
        
    
        if(vert==true){
        int i=0;
        int tempid=0;
        int temp;
        vector <int> score;
        vector <int> scoreM;
        vector <int> idM;

        while (i<Em.size()) {
            
            score.push_back(0);
            for(int y=0;y<Em[i].size();y++){
                //std::cout<< "OK for"<< y<<endl;
                scoreM.push_back(0);
                //int a=0;
                scoreM[y]=0;
               // if(B.spots[pos].letter==Em[i][y]){
                    bool G=true;
                    bool D=true;
                    int lg=y;
                    int ld=y+1;
                    int posG=pos;
                    int posD=pos+15;
                    while(G && lg>=0){
                        //std::cout<< "debut de la procedure Gauche"<<endl;
                        if(B.spots[posG].letter!=0){
                            //std::cout<<" cool on teste le C"<<endl;

                            if(B.spots[posG].letter==Em[i][lg]){
                                //std::cout<<scoreM[y] <<endl;
                                scoreM[y]=scoreM[y]+sac->lettreV[int(Em[i][lg])-65];
                                //std::cout<<" cool"<<scoreM[y] <<endl;

                            }else{
                                G=false;
                                scoreM[y]=0;
                                //std::cout<<"mort"<<endl;

                            }
                        }else{
                            if(sac->lettreV[int(Em[i][lg])-65]*B.spots[posG].bonus.letter_factor==sac->lettreV[int(Em[i][lg])-65]){
                            scoreM[y]=scoreM[y]+sac->lettreV[int(Em[i][lg])-65]*B.spots[posG].bonus.word_factor;
                                //std::cout<<" cool"<<scoreM[y] <<endl;
                            }else{
                            scoreM[y]=scoreM[y]+sac->lettreV[int(Em[i][lg])-65]*B.spots[posG].bonus.letter_factor;
                                //std::cout<<" cool"<<scoreM[y] <<endl;
                            }
                            
                                if(!motexiste(false,posG,Em[i][lg])){
                                    G=false;
                                    scoreM[y]=0;
                                }else{
                                    vector <string> N;
                                    int a=1;
                                    scoreM[y]=scoreM[y]+meilleurcoup(posG,Em,N,a,false);
                                }
                            

                        }
                        lg--;
                        
                            posG=posG-15;
                        
                    }
                    
                    while( G && D && ld<Em[i].size()){
                        //std::cout<<" debut de proc droite"<<endl;
                        if(B.spots[posD].letter!=0){
                            //std::cout<<" cool on teste le C"<<endl;
                            if(B.spots[posD].letter==Em[i][ld]){
                                scoreM[y]=scoreM[y]+sac->lettreV[int(Em[i][ld])-65];
                                //std::cout<<" cool"<<scoreM[y] <<endl;
                            }else{
                                D=false;
                                scoreM[y]=0;
                                //std::cout<<" mort"<<endl;
                            }
                        }else{
                            if(sac->lettreV[int(Em[i][ld])-65]*B.spots[posD].bonus.letter_factor==sac->lettreV[int(Em[i][ld])-65]){
                            scoreM[y]=scoreM[y]+sac->lettreV[int(Em[i][ld])-65]*B.spots[posD].bonus.word_factor;
                                //std::cout<<" cool"<<scoreM[y] <<endl;
                            }else{
                            scoreM[y]=scoreM[y]+sac->lettreV[int(Em[i][ld])-65]*B.spots[posD].bonus.letter_factor;
                                //std::cout<<" cool"<<scoreM[y] <<endl;
                            }
                           
                                if(!motexiste(false,posD,Em[i][ld])){
                                    D=false;
                                    scoreM[y]=0;
                                    //std::cout<<" mort"<<endl;
                                }else{
                                    vector <string> N;
                                    int a=1;
                                    scoreM[y]=scoreM[y]+meilleurcoup(posD,Em,N,a,false);
                                }

                        }
                        ld++;
                        
                            posD=posD+15;
                        
                        
                    }
                    //
                //}
                
            }
            //comparaison pour en garder qu'un
           temp=scoreM[0];
            idM.push_back(0);
            for(int j=1;j<scoreM.size();j++){
                
                if(temp<scoreM[j]){
                    temp=scoreM[j];
                    idM[i]=j;
                }
            }
            score[i]=temp;
            
            if(score[i]==0){
                std::cout<< Em[i]<< " false "<<score[i]<<" "<<i<<endl;
            }else{
                //std::cout<< Em[i]<< " true "<<idM[i]<<endl;
            }
            i++;
        }
        
        //comparaison a nouveau pour en garder qu'un
        tempid=0;
        temp=score[0];
        id=idM[0];
        for(int j=1;j<score.size();j++){
            
            if(temp<score[j]){
                temp=score[j];
                tempid=j;
                id=idM[j];
            }
        }
        
        Mc.push_back(Em[tempid]);
        
        return temp;
            
        }else if(vert==false){
            
            int i=0;
            int tempid=0;
            int temp;
            vector <int> score;
            vector <int> scoreM;
            vector <int> idM;
            while (i<Em.size()) {
                
                score.push_back(0);
                for(int y=0;y<Em[i].size();y++){
                    //std::cout<< "OK for"<< y<<endl;
                    scoreM.push_back(0);
                    //int a=0;
                    scoreM[y]=0;
                   // if(B.spots[pos].letter==Em[i][y]){
                        bool G=true;
                        bool D=true;
                        int lg=y;
                        int ld=y+1;
                        int posG=pos;
                        int posD=pos+1;
                    
                        
                        while(G && lg>=0){
                            //std::cout<< "debut de la procedure Gauche"<<endl;
                            if(B.spots[posG].letter!=0){
                                //std::cout<<" cool on teste le C"<<endl;

                                if(B.spots[posG].letter==Em[i][lg]){
                                    //std::cout<<scoreM[y] <<endl;
                                    scoreM[y]=scoreM[y]+sac->lettreV[int(Em[i][lg])-65];
                                    //std::cout<<" cool"<<scoreM[y] <<endl;

                                }else{
                                    G=false;
                                    scoreM[y]=0;
                                    //std::cout<<"mort"<<endl;

                                }
                            }else{
                                if(sac->lettreV[int(Em[i][lg])-65]*B.spots[posG].bonus.letter_factor==sac->lettreV[int(Em[i][lg])-65]){
                                scoreM[y]=scoreM[y]+sac->lettreV[int(Em[i][lg])-65]*B.spots[posG].bonus.word_factor;
                                    //std::cout<<" cool"<<scoreM[y] <<endl;
                                }else{
                                scoreM[y]=scoreM[y]+sac->lettreV[int(Em[i][lg])-65]*B.spots[posG].bonus.letter_factor;
                                    //std::cout<<" cool"<<scoreM[y] <<endl;
                                }
                               
                                    if(!motexiste(true,posG,Em[i][lg])){
                                        G=false;
                                        scoreM[y]=0;
                                    }else{
                                        vector <string> N;
                                        int a=1;
                                        scoreM[y]=scoreM[y]+meilleurcoup(posG,Em,N,a,true);
                                    }
                                

                            }
                            lg--;
                            
                                posG=posG-1;
                            
                        }
                        
                        while( G && D && ld<Em[i].size()){
                            //std::cout<<" debut de proc droite"<<endl;
                            if(B.spots[posD].letter!=0){
                                //std::cout<<" cool on teste le C"<<endl;
                                if(B.spots[posD].letter==Em[i][ld]){
                                    scoreM[y]=scoreM[y]+sac->lettreV[int(Em[i][ld])-65];
                                    //std::cout<<" cool"<<scoreM[y] <<endl;
                                }else{
                                    D=false;
                                    scoreM[y]=0;
                                    //std::cout<<" mort"<<endl;
                                }
                            }else{
                                if(sac->lettreV[int(Em[i][ld])-65]*B.spots[posD].bonus.letter_factor==sac->lettreV[int(Em[i][ld])-65]){
                                scoreM[y]=scoreM[y]+sac->lettreV[int(Em[i][ld])-65]*B.spots[posD].bonus.word_factor;
                                    //std::cout<<" cool"<<scoreM[y] <<endl;
                                }else{
                                scoreM[y]=scoreM[y]+sac->lettreV[int(Em[i][ld])-65]*B.spots[posD].bonus.letter_factor;
                                    //std::cout<<" cool"<<scoreM[y] <<endl;
                                }
                               
                                    if(!motexiste(true,posD,Em[i][ld])){
                                        D=false;
                                        scoreM[y]=0;
                                        //std::cout<<" mort"<<endl;
                                    }else{
                                        vector <string> N;
                                        int a=1;
                                        scoreM[y]=scoreM[y]+meilleurcoup(posD,Em,N,a,true);
                                    }
                                

                            }
                            ld++;
                            
                                posD=posD+1;
                            
                            
                        }
                        //
                    //}
                    
                }
                //comparaison pour en garder qu'un
               temp=scoreM[0];
                idM.push_back(0);
                for(int j=1;j<scoreM.size();j++){
                    
                    if(temp<scoreM[j]){
                        temp=scoreM[j];
                        idM[i]=j;
                    }
                }
                score[i]=temp;
                
                if(score[i]==0){
                    std::cout<< Em[i]<< " false "<<score[i]<<endl;
                }else{
                    //std::cout<< Em[i]<< " true "<<idM[i]<<endl;
                }
                i++;
            }
            
            //comparaison a nouveau pour en garder qu'un
            tempid=0;
            temp=score[0];
            id=idM[0];
            for(int j=1;j<score.size();j++){
                
                if(temp<score[j]){
                    temp=score[j];
                    tempid=j;
                    id=idM[j];
                }
            }
            
            Mc.push_back(Em[tempid]);
            
            return temp;
        }
    }
    return 0;
    
}


void Partie::ecriture(int pos,int score,string ME,int idM,int taille,bool vert){
    std::stringstream ss ;
    J1->score=J1->score+score;
    if(vert==true){
        int posM=idM;
        int posB=pos;
        char c;
        while (posM>=0) {
            
            if(B.spots[posB].letter==0){
                
                ss<<ME[posM]<<std::endl;
                ss>>c;
                B.spots[posB].letter=c;
                int i=0;
                bool pioche=true;
                while(i<7 && pioche){
                    if(J1->liste_lettre[i].lettre==ME[posM] && sac->nb>0){
                        J1->liste_lettre[i]=sac->pioche();
                        pioche=false;
                    }else if(J1->liste_lettre[i].lettre==ME[posM] && sac->nb<1){
                        J1->liste_lettre[i].lettre='\0';
                    }
                    i++;
                }
            }
            posM--;
            posB=posB-15;
        }
        posM=idM+1;
        posB=pos+15;
        while (posM<taille) {
            if(B.spots[posB].letter==0){
                ss<<ME[posM]<<std::endl;
                ss>>c;
                B.spots[posB].letter=c;
                int i=0;
                bool pioche=true;
                while(i<7 && pioche ){
                    if(J1->liste_lettre[i].lettre==ME[posM] && sac->nb>0){
                        J1->liste_lettre[i]=sac->pioche();
                        pioche=false;
                    }else if(J1->liste_lettre[i].lettre==ME[posM] && sac->nb<1){
                            J1->liste_lettre[i].lettre='\0';
                        }
                    i++;
                }
            }
            posM++;
            posB=posB+15;
        }
    }else{
        int posM=idM;
        int posB=pos;
        char c;
        while (posM>=0) {
            
            if(B.spots[posB].letter==0){
                ss<<ME[posM]<<std::endl;
                ss>>c;
                B.spots[posB].letter=c;
                int i=0;
                bool pioche=true;
                while(i<7 && pioche){
                    if(J1->liste_lettre[i].lettre==ME[posM] && sac->nb>0){
                        J1->liste_lettre[i]=sac->pioche();
                        pioche=false;
                    }else if(J1->liste_lettre[i].lettre==ME[posM] && sac->nb<1){
                            J1->liste_lettre[i].lettre='\0';
                        }
                    i++;
                }
            }
            posM--;
            posB=posB-1;
        }
        posM=idM+1;
        posB=pos+1;
        while (posM<taille) {
            if(B.spots[posB].letter==0){
                ss<<ME[posM]<<std::endl;
                ss>>c;
                B.spots[posB].letter=c;
                int i=0;
                bool pioche=true;
                while(i<7 && pioche){
                    if(J1->liste_lettre[i].lettre==ME[posM] && sac->nb>0){
                        J1->liste_lettre[i]=sac->pioche();
                        pioche=false;
                    }else if(J1->liste_lettre[i].lettre==ME[posM] && sac->nb<1){
                            J1->liste_lettre[i].lettre='\0';
                        }
                    i++;
                }
            }
            posM++;
            posB=posB+1;
        }
    }
    
}
