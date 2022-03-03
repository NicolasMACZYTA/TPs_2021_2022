#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>
#include <signal.h>
#include <time.h>

#include "include.h"

int stop = 0;

/**
 * Gestionnaire pour le signal SIGINT
 * @param signum le numéro du signal (ici SIGINT)
 */
void handler(int signum) {
    printf("Signal de fin reçu.\n");
    stop = 1;
}

/**
 * Génère un entier aléatoire dans un intervalle [a, b].
 * @param a la borne minimale
 * @param b la borne maximale
 * @return l'entier aléatoire
 */
int alea(int a, int b) {
    return rand() % (b - a + 1) + a;
}

int main(int argc, char *argv[]) {
    unsigned char *carte;
    int i, j, indice, newx, newy;
    struct sigaction action;

    // Initialisation du générateur de nombres pseudo-aléatoire
    srand(time(NULL) + getpid());

    // #TODO#
    // - Récupérer le segment de mémoire partagé

    // #TODO# : à supprimer
    // Allocation et initialisation d'une carte
    // #TODO# : la carte doit être dans le segment de mémoire partagé
    if((carte = malloc(sizeof(unsigned char) * LARGEUR * HAUTEUR)) == NULL) {
        perror("Erreur lors de l'allocation de la carte ");
        exit(EXIT_FAILURE);
    }
    memset(carte, ' ', sizeof(unsigned char) * LARGEUR * HAUTEUR);

    // Positionnement du gestionnaire
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_handler = handler;
    if(sigaction(SIGINT, &action, NULL) == -1) {
        perror("Erreur lors du placement du gestionnaire ");
        exit(EXIT_FAILURE);    
    }
    
    // Boucle principale
    while(stop == 0) {
        indice = 0;
        for(j = 0; j < HAUTEUR; j++) {
            for(i = 0; i < LARGEUR; i++) {
                if(carte[indice] == 'C') {
                    // Déplacement d'un virus
                    carte[indice] = ' ';
                    newx = alea(i - 1, i + 1);
                    newy = alea(j - 1, j + 1);
                    
                    if(newx < 0) newx = 0;
                    if(newx >= LARGEUR) newx = LARGEUR - 1;
                    if(newy < 0) newy = 0;
                    if(newy >= HAUTEUR) newy = HAUTEUR - 1;

                    if(carte[newy * LARGEUR + newx] != ' ') {
                        // On ne déplace pas le virus
                        carte[indice] = 'C';
                    }
                    else {
                        // On déplace le virus : on indique 'D' pour ne pas le déplacer deux fois
                        carte[newy* LARGEUR + newx] = 'D';
                    }
                }
                else if((carte[indice] == ' ') &&
                        ((i == 0) || (i == LARGEUR - 1) || (j == 0) || (j == HAUTEUR - 1))) {
                    if(alea(0, INTERVALLE) < CREATION) {
                        // Création d'un nouveau virus
                        printf("%s : j'ajoute un virus\n", argv[0]);
                        carte[indice] = 'C';
                    }
                }
                indice++;
            }
        }
        
        // Remplacement des D par des C
        indice = 0;
        for(j = 0; j < HAUTEUR; j++) {
            for(i = 0; i < LARGEUR; i++) {
                if(carte[indice] == 'D')
                    carte[indice] = 'C';
                indice++;
            }
        }
        
        // Pause
        usleep(VITESSE);
    }
    
    printf("%s : terminé\n", argv[0]);
 
    // #TODO# : à supprimer
    // Libération de la mémoire
    free(carte);
    
    return EXIT_SUCCESS;
}