#include <cstdlib>
#include <limits>
#include <cmath>
#include "morpion.h"



// ETAPE 1 : Je cherche si j'ai mon alignement :

void mon_alignement (char** & tab, int size, int nbPion, char pion){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(estLibre_morpion(tab,size,i,j)==true){
                tab[i][j]=pion;
            if(victoire_morpion(tab,size,nbPion,pion)==true){
                return;
            }
            tab[i][j]=' ';

            }
        }
    }
}

// ETAPE 2 : Je cherche si mon adverssaire a son alignement

char pion_adv(char pion){
    char advPion;
    if(pion =='X'){
        return 'O';
    }
    else {
        return 'X';
    }
}

void bloquer_adverssaire (char** & tab, int size, int nbPion, char pion){
    char advPion=pion_adv(pion);
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(estLibre_morpion(tab,size,i,j)==true){
                tab[i][j]=advPion;
            if(victoire_morpion(tab,size,nbPion,advPion)==true){
                tab[i][j]=pion;
                return;
            }
            tab[i][j]=' ';

            }
        }
    }
}

// ETAPE 3 : Calculer la distance

int distance_tchbyshev(int x1, int y1, int x2, int y2){
    int dx=std::abs(x1-x2);
    int dy=std::abs(y1-y2);
    if(dx>dy){
        return dx;
    }
    else {
        return dy;
    }
}


void jouer_dist(char** & tab, int size, char pion){
    char advPion=pion_adv(pion);
    for(int x=0;x<size;x++){
        for(int y=0;y<size;y++){
            if(tab[x][y]==advPion){
                for(int i=0;i<size;i++){
                    for(int j=0;j<size;j++){
                        if(estLibre_morpion(tab,size,i,j)){
                            int d=distance_tchbyshev(x,y,i,j);
                            if(d==1){
                                tab[i][j]=pion;
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}





























