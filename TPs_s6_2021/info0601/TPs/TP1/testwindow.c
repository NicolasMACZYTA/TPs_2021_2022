#include <ncurses.h>
#include <stdlib.h>
int main(void) {
    WINDOW *haut, *gauche, *droite, *subwin_gauche;
    
    initscr();
    haut= subwin(stdscr, 7, COLS, 0, 0);        // Créé une fenêtre de 'LINES / 2' lignes et de COLS colonnes en 0, 0
    gauche= subwin(stdscr, 18, 34, 7, 0); // Créé la même fenêtre que ci-dessus sauf que les coordonnées changent
    droite= subwin(stdscr, 18, 10, 7, 34); // Créé la même fenêtre que ci-dessus sauf que les coordonnées changent
    subwin_gauche=subwin(gauche,16,32,8,1);


    box(haut, ACS_VLINE, ACS_HLINE);
    box(gauche, ACS_VLINE, ACS_HLINE);
    box(droite, ACS_VLINE, ACS_HLINE);
    
    mvwprintw(haut, 0, 1, "fenetre 1");
    mvwprintw(gauche, 0, 1, "fenetre 2");
    mvwprintw(droite, 0, 1, "fenetre 3");

    wprintw(subwin_gauche,"00000000 00 00 00 00 00 00 00 00");
    wprintw(subwin_gauche,"00000000 00 00 00 00 00 00 00 00");
    wprintw(subwin_gauche,"00000000 00 00 00 00 00 00 00 00");
    wprintw(subwin_gauche,"00000000 00 00 00 00 00 00 00 00");
    wprintw(subwin_gauche,"00000000 00 00 00 00 00 00 00 00");
    wprintw(subwin_gauche,"00000000 00 00 00 00 00 00 00 00");
    wprintw(subwin_gauche,"00000000 00 00 00 00 00 00 00 00");
    wprintw(subwin_gauche,"00000000 00 00 00 00 00 00 00 00");
    wprintw(subwin_gauche,"00000000 00 00 00 00 00 00 00 00");
    wprintw(subwin_gauche,"00000000 00 00 00 00 00 00 00 00");
    
    wrefresh(haut);
    wrefresh(gauche);
    wrefresh(droite);


    refresh();
    getch();
    endwin();
    
    
    
    return 0;
}