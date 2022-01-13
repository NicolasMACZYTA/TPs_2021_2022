#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "ncurses.h"

#define TAILLE 10
#define CLICKZONE 12
#define MAX 20

int main(){
    int i, sourisX, sourisY;
    WINDOW* fenetre;
    WINDOW* fenetre2;
    WINDOW* sous_fenetre;

    ncurses_initialiser();
    ncurses_souris();
    ncurses_couleurs();
    ncurses_palette();

    if((COLS < TAILLE) || (LINES < MAX)) {
        ncurses_stopper();
        fprintf(stderr, 
                "Les dimensions du terminal sont insufisantes : l=%d,h=%d au lieu de l=%d,h=%d\n", 
                COLS, LINES, TAILLE, MAX);
        exit(EXIT_FAILURE);
    }  

    clear();
    refresh();
    fenetre = newwin(TAILLE, COLS, 1, 0);
    box(fenetre, 0, 0);
    fenetre2 = newwin(CLICKZONE, CLICKZONE, TAILLE+1, 0);
    box(fenetre2, 0, 0);
    sous_fenetre = subwin(fenetre, TAILLE-2, COLS-2, 2, 1);
    scrollok(sous_fenetre, TRUE);
    
    wrefresh(fenetre);
    wrefresh(sous_fenetre);
    wrefresh(fenetre2);

    printw("Cliquez dans la deuxiéme fenetre; pressez F2 pour quitter...");  
    refresh();
    while((i = getch()) != KEY_F(2)) {
        if((i == KEY_MOUSE) && (souris_getpos(&sourisX, &sourisY, NULL) == OK)){
                if((sourisX > 0) && (sourisX < CLICKZONE-1) && (sourisY > TAILLE+1) && (sourisY < TAILLE+CLICKZONE)){
                    wprintw(sous_fenetre, "Clique en (%d : %d)\n", sourisX, sourisY);
                    attron(COLOR_PAIR(2));
                    mvprintw(sourisY, sourisX, "X");
                    attroff(COLOR_PAIR(2));
                    wrefresh(sous_fenetre);
                }
        }
    }

    /* Suppression des fenêtres */
    delwin(sous_fenetre);
    delwin(fenetre);
    delwin(fenetre2);
    
    /* Arrêt de ncurses */
    ncurses_stopper();

    return 0;
}