#include <iostream>
#include <cstdlib>
#include <ctime>

#include "morpion.h"

// --------------------------------------------------
// Joue UN coup aléatoire
// --------------------------------------------------
void hasard(char** tab, int size, char pion) {

    int nbr_libre = 0;

    // compter les cases libres
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            if(tab[i][j] == ' ')
                nbr_libre++;

    if(nbr_libre == 0) return;

    int choix = rand() % nbr_libre;
    int compteur = 0;

    // jouer sur la case choisie
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(tab[i][j] == ' ') {
                if(compteur == choix) {
                    placer_morpion(tab, size, i, j, pion);
                    return;
                }
                compteur++;
            }
        }
    }
}

// --------------------------------------------------
// Simule une partie complète au hasard
// retourne :  1 = victoire IA
//             0 = nul
//            -1 = défaite IA
// --------------------------------------------------
int simulerPartie(char** tab, int size, int nbPion, char pionIA) {

    char joueur = pionIA;
    int coup = 0;

    while(coup < size * size) {

        hasard(tab, size, joueur);

        if(victoire_morpion(tab, size, nbPion, joueur)) {
            if(joueur == pionIA)
                return 1;
            else
                return -1;
        }

        // changer de joueur
        if(joueur == 'X')
            joueur = 'O';
        else
            joueur = 'X';

        coup++;
    }

    return 0; // match nul
}

// --------------------------------------------------
// IA Monte-Carlo : choisit le meilleur coup
// --------------------------------------------------
void parcours_tab(char** & tab, int size, int nbPion, char pion) {

    const int S = 200;          // nombre de simulations par coup
    double bestScore = -1.0;
    int bestI = -1, bestJ = -1;

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {

            if(estLibre_morpion(tab, size, i, j)) {

                // coup candidat
                char** tab2 = copie_morpion(tab, size);
                placer_morpion(tab2, size, i, j, pion);

                int win = 0, draw = 0;

                // simulations
                for(int s = 0; s < S; s++) {

                    char** sim = copie_morpion(tab2, size);
                    int r = simulerPartie(sim, size, nbPion, pion);

                    if(r == 1) win++;
                    else if(r == 0) draw++;

                    delete_morpion(sim, size);
                }

                double score = (win + 0.5 * draw) / S;

                if(score > bestScore) {
                    bestScore = score;
                    bestI = i;
                    bestJ = j;
                }

                delete_morpion(tab2, size);
            }
        }
    }

    // jouer le meilleur coup trouvé
    if(bestI != -1 && bestJ != -1) {
        placer_morpion(tab, size, bestI, bestJ, pion);
    }
}
