#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "fonctions.h"
#include "fenetre.h"
#include "include.h"

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
    bool quitter = FALSE, jouer;
    fenetre_t *win_joueur, *win_ordi, *win_infos;
    int n, reste, indice;
    int posX, posY, x, y;
    unsigned char *grille_joueur, *grille_ordi;
    int *reste_joueur, *reste_ordi;
 
    // Initialisation du générateur de nombres pseudo-aléatoire
    srand(time(NULL) + getpid());
 
    // #TODO# : créer un segement de mémoire partagé contenant :
    // - les grilles du joueur et de l'ordinateur
    // - les compteurs de bateaux
    // - le message généré par l'ordinateur à afficher
    
    // #TODO# : à supprimer
    // Allocation de la grille du joueur
    if((grille_joueur = malloc(sizeof(unsigned char) * LARGEUR * HAUTEUR)) == NULL) {
        perror("Erreur lors de l'allocation de la grille du joueur ");
        exit(EXIT_FAILURE);
    }
    
    // #TODO# : à supprimer
    // Allocation de la grille de l'ordinateur
    if((grille_ordi = malloc(sizeof(unsigned char) * LARGEUR * HAUTEUR)) == NULL) {
        perror("Erreur lors de l'allocation de la grille de l'ordinateur ");
        exit(EXIT_FAILURE);
    }
    
    // Initialisation des grilles
    memset(grille_joueur, ' ', sizeof(unsigned char) * LARGEUR * HAUTEUR);
    memset(grille_ordi, ' ', sizeof(unsigned char) * LARGEUR * HAUTEUR);
    
    // #TODO# : à supprimer    
    // Normalement, les compteurs poitent dans le segment
    int tmp_joueur, tmp_ordi;
    reste_joueur = &tmp_joueur;
    reste_ordi = &tmp_ordi;
    
    // Initialisation des bateaux restants
    *reste_joueur = BATEAUX;
    *reste_ordi = BATEAUX;
        
    // Initialisation de ncurses
    setlocale(LC_ALL, "");
    ncurses_init();
    ncurses_initsouris();
    ncurses_couleurs(); 
    palette();
    clear();
    refresh();
    
    // Vérification des dimensions du terminal
    if((COLS < LARGEUR * 2 + 2) || (LINES < HAUTEUR + 9)) {
        ncurses_stop();
        fprintf(stderr, 
              "Les dimensions du terminal sont insufisantes : l=%d,h=%d au lieu de l=%d,h=%d\n", 
              COLS, LINES, LARGEUR * 2 + 2, HAUTEUR + 9);
        exit(EXIT_FAILURE);
    }
    
    // Création des fenêtres
    win_infos = fenetre_creer(0, 0, COLS, 7, "Informations", TRUE);
    win_joueur = fenetre_creer(0, 7, LARGEUR + 2, HAUTEUR + 2, "Joueur", FALSE);    
    win_ordi = fenetre_creer(LARGEUR + 2, 7, LARGEUR + 2, HAUTEUR + 2, "Ordinateur", FALSE);    
        
    
    // Boucle pour placer les bateaux
    fenetre_printw(win_infos, "Placez vos %d bateaux en cliquant dans votre grille.", BATEAUX);
    fenetre_refresh(win_infos);
    reste = BATEAUX;
    while((quitter == FALSE) && (reste > 0) && (n = getch())) {
        switch(n) {
            case 'q':
            case 'Q':
                quitter = TRUE;
                break;
            case KEY_MOUSE:
                if(souris_getpos(&posX, &posY) == OK) {
                    if(fenetre_getcoordonnees(win_joueur, posX, posY, &x, &y) == TRUE) {
                        if(grille_joueur[y * LARGEUR + x] != 'X') {
                            grille_joueur[y * LARGEUR + x] = 'X';
                            fenetre_mvaddch_col(win_joueur, y, x, WHITE, 'X');
                            fenetre_refresh(win_joueur);
                            fenetre_printw(win_infos, "\nVous avez placé un bateau (%d,%d).", x, y);
                            reste--;
                        }
                        else
                            fenetre_printw(win_infos, "\nIl y a déjà un bateau ici...");
                        fenetre_refresh(win_infos);
                    }
                }
                break;
        }
    }
    
    if(quitter == FALSE) {
        // Bateaux placés
        fenetre_printw(win_infos, "\nEn attente de l'ordinateur.");
        fenetre_refresh(win_infos);
        
        // #TODO# : comment attendre que l'ordinateur démarre et place ses bateaux ?
        
        // #TODO# : à supprimer (code à placer dans l'ordinateur)
        // Remplissage aléatoire de la carte
        reste = BATEAUX;
        while(reste > 0) {
            y = alea(0, HAUTEUR - 1);
            x = alea(0, LARGEUR - 1);
            
            indice = y * LARGEUR + x;
            if(grille_ordi[indice] == ' ') {
                grille_ordi[indice] = 'X';
                reste--;
                
                // #TODO# : à supprimer
                // Affichage des bateaux de l'ordinateur
                fenetre_mvaddch_col(win_ordi, y, x, WHITE, 'X');
                fenetre_refresh(win_ordi);
            }
        }
        
        fenetre_printw(win_infos, "\nL'ordinateur est connecté et a placé ses bateaux.");
        fenetre_refresh(win_infos);
    }    
    
    // Boucle principale
    while((quitter == FALSE) && (*reste_joueur > 0) && (*reste_ordi > 0)) {
        // Au joueur de jouer
        fenetre_printw(win_infos, "\nCliquez sur une case de la grille de l'ordinateur pour tirer.");
        fenetre_refresh(win_infos);
        jouer = FALSE;
        while((quitter == FALSE) && (jouer == FALSE)) {
            n = getch();
            switch(n) {
                case 'q':
                case 'Q':
                    quitter = TRUE;
                    break;
                case KEY_MOUSE:
                    if(souris_getpos(&posX, &posY) == OK) {
                        if(fenetre_getcoordonnees(win_ordi, posX, posY, &x, &y) == TRUE) {
                            indice = y * LARGEUR + x;
                            if((grille_ordi[indice] != ' ') && (grille_ordi[indice] != 'X'))
                                fenetre_printw(win_infos, "\nVous avez déjà tiré ici.");
                            else {
                                jouer = TRUE;
                                if(grille_ordi[indice] == 'X') {
                                    fenetre_printw(win_infos, "\nVous avez détruit un bateau.");
                                    fenetre_mvaddch_col(win_ordi, y, x, RED, 'T');
                                    fenetre_refresh(win_ordi);
                                    grille_joueur[indice] = 'T';
                                    *reste_ordi -= 1;
                                }
                                else {
                                    fenetre_printw(win_infos, "\nVous avez tiré à côté.");
                                    fenetre_mvaddch_col(win_ordi, y, x, WHITE, 'M');
                                    fenetre_refresh(win_ordi);
                                    grille_joueur[indice] = 'M';
                                }
                            }
                            fenetre_refresh(win_infos);
                        }
                    }
                    break;
            }
        }
        
        // À l'ordinateur de jouer
        if((quitter == FALSE) && (*reste_joueur > 0) && (*reste_ordi > 0)) {
            // #TODO# : comment attendre que l'ordinateur termine ?
            
            // #TODO# : à supprimer
            // Choix de l'ordinateur aléatoire
            do {
                y = alea(0, HAUTEUR - 1);
                x = alea(0, LARGEUR - 1);
            
                indice = y * LARGEUR + x;
            } while((grille_joueur[indice] != ' ') && (grille_joueur[indice] != 'X'));
            
            if(grille_joueur[indice] == ' ') {
                grille_joueur[indice] = 'M';
                fenetre_mvaddch_col(win_joueur, y, x, WHITE, 'M');
            }
            else {
                grille_joueur[indice] = 'T';
                *reste_joueur -= 1;
                fenetre_mvaddch_col(win_joueur, y, x, RED, 'T');
            }
            fenetre_refresh(win_joueur);
        
            // #TODO#
            // - afficher le message dans le segment de mémoire partagé
            // - mise-à-jour de l'affichage (coup de l'ordinateur)
        }
    }
    
    // Fin de partie ou arrêt demandé
    if(quitter == FALSE) {
        if(*reste_joueur == 0)
            fenetre_printw(win_infos, "\nVous avez perdu !");
        else
            fenetre_printw(win_infos, "\nVous avez gagné !");
    }
    else
        fenetre_printw(win_infos, "\nVous avez arrêté la partie.");
    fenetre_refresh(win_infos);
    sleep(2);
    
    // Arrêt de ncurses
    fenetre_supprimer(&win_joueur);
    fenetre_supprimer(&win_ordi);
    fenetre_supprimer(&win_infos);
    ncurses_stop();
    
    // Libération mémoire
    free(grille_joueur);
    free(grille_ordi);

    return EXIT_SUCCESS;    
}