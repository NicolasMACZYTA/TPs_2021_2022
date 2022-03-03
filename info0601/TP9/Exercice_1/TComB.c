#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>

#include "fonctions.h"
#include "fenetre.h"
#include "include.h"

int main(int argc, char *argv[]) {
    bool quitter = FALSE;
    fenetre_t *terrain, *infos;
    int n, i, j, k;
    int posX, posY, x, y;
    unsigned char *carte;
    
    // #TODO# : créer un segment de mémoire partagé contenant :
    // - la carte
    
    // #TODO# : à supprimer
    // Allocation et initialisation de la carte 
    if((carte = malloc(sizeof(unsigned char) * LARGEUR * HAUTEUR)) == NULL) {
        perror("Erreur lors de l'allocation de la carte ");
        exit(EXIT_FAILURE);
    }
    memset(carte, ' ', sizeof(unsigned char) * LARGEUR * HAUTEUR);
    
    // Initialisation de ncurses
    setlocale(LC_ALL, "");
    ncurses_init();
    ncurses_initsouris();
    ncurses_couleurs(); 
    palette();
    clear();
    refresh();
    timeout(1000);
    
    // Vérification des dimensions du terminal
    if((COLS < LARGEUR + 2) || (LINES < HAUTEUR + 9)) {
        ncurses_stop();
        fprintf(stderr, 
              "Les dimensions du terminal sont insufisantes : l=%d,h=%d au lieu de l=%d,h=%d\n", 
              COLS, LINES, LARGEUR + 2, HAUTEUR + 9);
        exit(EXIT_FAILURE);
    }
    
    // Création des fenêtres
    infos = fenetre_creer(0, 0, COLS, 7, "Informations", TRUE);
    terrain = fenetre_creer(0, 7, LARGEUR + 2, HAUTEUR + 2, "Carte", FALSE);    
    fenetre_printw(infos, "Cliquez sur les virus pour les détruire.");
    fenetre_refresh(infos);
    
    // Boucle principale
    while((quitter == FALSE) && (n = getch())) {
        switch(n) {
            case 'q':
            case 'Q':
                quitter = TRUE;
                break;
            case KEY_MOUSE:
                if(souris_getpos(&posX, &posY) == OK) {
                    if(fenetre_getcoordonnees(terrain, posX, posY, &x, &y) == TRUE) {
                        if(carte[y * LARGEUR + x] != ' ')
                            fenetre_printw(infos, "\nVous avez détruit un virus.");
                        else
                            fenetre_printw(infos, "\nVous avez cliqué à côté.");
                        fenetre_refresh(infos);
                        carte[y * LARGEUR + x] = ' ';
                    }
                }
                // Pas de break
            case ERR:
                // On raffraîchit la carte
                k = 0;
                for(j = 0; j < HAUTEUR; j++) {
                    for(i = 0; i < LARGEUR; i++) {
                        if(carte[k] != ' ')
                            fenetre_mvaddch(terrain, j, i, carte[k]);
                        else 
                            fenetre_mvaddch(terrain, j, i, ' ');
                        k++;
                    }
                } 
                fenetre_refresh(terrain);
                fenetre_refresh(infos);
                break;
        }        
    }
    
    // Arrêt de ncurses
    fenetre_supprimer(&terrain);
    fenetre_supprimer(&infos);
    ncurses_stop();
    
    // Libération de la mémoire
    free(carte);   

    return EXIT_SUCCESS;    
}