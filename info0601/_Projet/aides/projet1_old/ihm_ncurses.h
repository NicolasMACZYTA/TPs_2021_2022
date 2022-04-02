#ifndef IHM_NCURSES_H
#define IHM_NCURSES_H

#include <ncurses.h>

typedef struct WIN{
	WINDOW *border_window;
	WINDOW *content_window;
	/* pas utile dans l'état actuel du code peut etre plus tard
	int startx,starty,height,width;
	*/
	char *window_text;
}WIN;

WIN* initialiser_win(int startx_,int starty_,int height_,int width_,char*text);
void refresh_win(WIN*window);
void print_win(WIN*window,char*text);
void afficher_win(WIN*window);
void ncurses_initialisation();
void ncurses_stopper();
void ncurses_couleurs();
void ncurses_initsouris();
int souris_getpos(int *x, int *y);
int char_selectionne(int posX, int posY);
int hex_selectionne(int posX, int posY);
int selection(int posX,int posY, int* typeselection);
void afficher_selection(int selected_octet,WIN * hex_window,WIN * char_window,char * buf,int typeselection);
#endif

