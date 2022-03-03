#ifndef _FONCTIONS_
#define _FONCTIONS_

// Constantes pour les couleurs
#define WHITE       1
#define GREEN       2
#define BLUE        3
#define RED         4 
#define YELLOW      5
#define CYAN        6
#define MAGENTA     7
#define FD_WHITE    8
#define FD_GREEN    9
#define FD_BLUE    10
#define FD_RED     11
#define FD_YELLOW  12
#define FD_CYAN    13
#define FD_MAGENTA 14

/**
 * Définition de la palette.
 */
void palette();

/**
 * Initialisation de ncurses.
 */
void ncurses_init();

/**
 * Fin de ncurses.
 */
void ncurses_stop();

/**
 * Initialisation des couleurs.
 */
void ncurses_couleurs();

/**
 * Initialisation de la souris.
 */
void ncurses_initsouris();

/**
 * Récupération de la position de la souris.
 * @param[out] x la position en x de la souris
 * @param[out] y la position en y de la souris
 * @return OK ou ERR en cas d'erreur 
 */
int souris_getpos(int *x, int *y);

#endif