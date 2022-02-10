#include "fonctions.h"

#include <ncurses.h>   // Pour toutes les fonctions/constantes ncurses
#include <stdlib.h>    // Pour exit, EXIT_FAILURE

/**
 * Définition de la palette.
 */
void palette() {
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(FD_WHITE, COLOR_BLACK, COLOR_WHITE);
    init_pair(FD_GREEN, COLOR_BLACK, COLOR_GREEN);
    init_pair(FD_BLUE, COLOR_BLACK, COLOR_BLUE);
    init_pair(FD_RED, COLOR_BLACK, COLOR_RED);
    init_pair(FD_YELLOW, COLOR_BLACK, COLOR_YELLOW);
    init_pair(FD_CYAN, COLOR_BLACK, COLOR_CYAN);
    init_pair(FD_MAGENTA, COLOR_BLACK, COLOR_MAGENTA);
}

/**
 * Initialisation de ncurses.
 */
void ncurses_init() {
  initscr();	        // Démarre le mode ncurses
  cbreak();	            // Désactive la mise en buffer
  noecho();             // Désactive l'affichage des caractères saisis
  keypad(stdscr, TRUE);	// Active les touches spécifiques (flèches)
  refresh();            // Met à jour l'affichage
  curs_set(FALSE);      // Masque le curseur
}

/**
 * Fin de ncurses.
 */
void ncurses_stop() {
  endwin();
}

/**
 * Initialisation des couleurs.
 */
void ncurses_couleurs() {
  // Verification du support de la couleur
  if(has_colors() == FALSE) {
    ncurses_stop();
    fprintf(stderr, "Le terminal ne supporte pas les couleurs.\n");
    exit(EXIT_FAILURE);
  }

  // Activation des couleurs
  start_color();
}

/**
 * Initialisation de la souris.
 */
void ncurses_initsouris() {
  if(!mousemask(BUTTON1_PRESSED, NULL)) {
    ncurses_stop();
    fprintf(stderr, "Pas de gestion de la souris.\n");
    exit(EXIT_FAILURE);
  }
}

/**
 * Récupération de la position de la souris.
 * @param[out] x la position en x de la souris
 * @param[out] y la position en y de la souris
 * @return OK ou ERR en cas d'erreur
 */
int souris_getpos(int *x, int *y) {
  MEVENT event;
  int resultat = getmouse(&event);
  if(resultat == OK) {
    *x = event.x;
    *y = event.y;
  }
  return resultat;
}