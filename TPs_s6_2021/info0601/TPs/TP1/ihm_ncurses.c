#include "ihm_ncurses.h"
#include <stdlib.h>

WIN * initialiser_win(int startx_,int starty_,int height_,int width_,char *window_text_){
	WIN * window;
	window=malloc(sizeof(WIN));
	/* pas utile dans l'état actuel du code, peut être plus tard

	window->height=height_;
	window->width=width_;
	window->startx=startx_;
	window->starty=starty_;
	*/

	window->border_window=subwin(stdscr, height_, width_, starty_, startx_);
	window->content_window=subwin(window->border_window,height_-2,width_-2,starty_+1,startx_+1);
	window->window_text=window_text_;
	return window;
}

void afficher_win(WIN*window){
	box(window->border_window, ACS_VLINE, ACS_HLINE);
	mvwprintw(window->border_window, 0, 1, window->window_text);
	refresh_win(window);
}


void refresh_win(WIN*window){
	wrefresh(window->border_window);
	wrefresh(window->content_window);
}

void print_win(WIN*window,char*text){
	wprintw(window->content_window,text);
}

void ncurses_initsouris() {
    if(!mousemask(BUTTON1_PRESSED, NULL)) {
        ncurses_stopper();
        fprintf(stderr, "Pas de gestion de la souris.\n");
        exit(EXIT_FAILURE);
    }
}

int souris_getpos(int *x, int *y) {
MEVENT event;
int resultat = getmouse(&event);
if(resultat == OK) {
*x = event.x; *y = event.y;
}
return resultat;
}


void ncurses_initialisation() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();
    curs_set(FALSE);
}

void ncurses_stopper() {
    endwin();
}

void ncurses_couleurs() {
/* Vérification du support de la couleur */
if(has_colors() == FALSE) {
ncurses_stopper();
fprintf(stderr, "Pas de gestion de la couleurpour ce terminal.\n");
exit(EXIT_FAILURE);
}else{
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    init_pair(2, COLOR_CYAN, COLOR_BLUE);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_RED, COLOR_MAGENTA);

}
}