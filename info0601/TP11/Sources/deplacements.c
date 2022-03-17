/**
 * Ce programme permet de déplacer un caractère dans une grille.
 * @author Cyril Rabat
 **/
#include <locale.h>
#include <stdlib.h>
#include <ncurses.h>

#include "fonctions.h"
#include "fenetre.h"

#define LARGEUR 40
#define HAUTEUR 20

int main() {
    unsigned char grille[HAUTEUR][LARGEUR];    
    int posX = LARGEUR / 2, posY = HAUTEUR / 2, ch;
    fenetre_t *win_grille, *win_infos;
    int quitter = 0, i, j;
    
    // Initialisation de ncurses
    setlocale(LC_ALL, "");
    ncurses_init();
    ncurses_couleurs(); 
    palette();
    clear();
    refresh();

    // Vérification des dimensions du terminal
    if((COLS < LARGEUR + 2) || (LINES < HAUTEUR + 9)) {
        ncurses_stop();
        fprintf(stderr, 
              "Les dimensions du terminal sont insufisantes : l=%d,h=%d au lieu de l=%d,h=%d\n", 
              COLS, LINES, LARGEUR + 2, HAUTEUR + 9);
        exit(EXIT_FAILURE);
    }
    
    // Création des fenêtres
    win_infos = fenetre_creer(0, 0, COLS, 7, "Informations", TRUE);
    win_grille = fenetre_creer(0, 7, LARGEUR + 2, HAUTEUR + 2, "Grille", FALSE);    
    fenetre_printw(win_infos, "Déplacez le caractère avec les flèches et tapez 'q' pour quitter.");
    fenetre_refresh(win_infos);    

    // Initialisation et affichage de la grille
    for(i = 0; i < HAUTEUR; i++) {
        for(j = 0; j < LARGEUR; j++) {
            if((j == 0) || (i == 0) || (j == LARGEUR - 1) || (i == HAUTEUR - 1))
                grille[i][j] = 'X';
            else
                grille[i][j] = ' ';
            fenetre_addch(win_grille, grille[i][j]);
        }
    }
    grille[posY][posX] = '1';
    fenetre_mvaddch(win_grille, posY, posX, '1');
    fenetre_refresh(win_grille);
  
    // Boucle principale : arrêt en pressant F2
    while(quitter == 0) {
        ch = getch();

        // Gestion des touches pressées
        switch(ch) {
            case 'q':
            case 'Q':
                // Demande d'arrêt
                quitter = 1;
                break;
            case KEY_LEFT:
                // Déplacement vers la gauche
                if(grille[posY][posX - 1] == ' ') {
                    fenetre_mvaddch(win_grille, posY, posX, ' ');
                    posX--;
                    fenetre_mvaddch(win_grille, posY, posX, '1');
                    fenetre_refresh(win_grille);
                }                
                break;
            case KEY_RIGHT:
                // Déplacement vers la droite
                if(grille[posY][posX + 1] == ' ') {
                    fenetre_mvaddch(win_grille, posY, posX, ' ');
                    posX++;
                    fenetre_mvaddch(win_grille, posY, posX, '1');
                    fenetre_refresh(win_grille);
                }            
                break;
            case KEY_UP:
                // Déplacement vers le haut
                if(grille[posY - 1][posX] == ' ') {
                    fenetre_mvaddch(win_grille, posY, posX, ' ');
                    posY--;
                    fenetre_mvaddch(win_grille, posY, posX, '1');
                    fenetre_refresh(win_grille);
                } 
                break;
            case KEY_DOWN:
                // Déplacement vers le bas
                if(grille[posY + 1][posX] == ' ') {
                    fenetre_mvaddch(win_grille, posY, posX, ' ');
                    posY++;
                    fenetre_mvaddch(win_grille, posY, posX, '1');
                    fenetre_refresh(win_grille);
                } 
                break;
        }
    }

     // Arrêt de ncurses
    fenetre_supprimer(&win_grille);
    fenetre_supprimer(&win_infos);
    ncurses_stop();

    return EXIT_SUCCESS;
}