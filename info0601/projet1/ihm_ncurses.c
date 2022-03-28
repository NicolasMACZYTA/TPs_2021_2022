#include "ihm_ncurses.h"
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

WIN * initialiser_win(int startx_,int starty_,int height_,int width_,char *window_text_){
	/*initialiser_win(x départ, y départ, hauteur, largeur, texte bordure)
	hauteur largeur correspond a la bordure et non a l'interieur de la fenetre
	*/
	
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
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_RED, COLOR_BLACK);

}
}

int char_selectionne(int posX, int posY){
	int x = posX-35, y = posY-8;
	return (y*8+x);
}

int hex_selectionne(int posX, int posY){
	int x = (posX-1), y = posY-8;
	return (y*40+x);
}


int selection(int posX,int posY, int * typeselection){
	int res;
	
	if(posX >= 1 && posX <=40 && posY>=8 && posY<=27){
		res = hex_selectionne(posX,posY);
		*typeselection = 0;
	}else if(posX >= 43 && posX <=50 && posY>=8 && posY<=23){
		res = char_selectionne(posX,posY);
		*typeselection = 1;
	}else{
		res=0;
		*typeselection= 0;
	}
	return res;
}

void afficher_selection(int selected_octet,WIN * hex_window,WIN * char_window,char *buf,int typeselection){
	char* hex = malloc(8*sizeof(char));
	int x_hex,x_char;
	int y_hex,y_char;
	sprintf((char*)(hex), "%02X", buf[selected_octet]);
	x_hex = (selected_octet%40);
	x_char = selected_octet%8;
	y_hex = selected_octet/40;
	y_char = selected_octet/8;

	if(typeselection==0){
	wattron(hex_window->content_window,COLOR_PAIR(2));
	}
	wattron(hex_window->content_window,A_STANDOUT);
	mvwprintw(hex_window->content_window,y_hex,x_hex,"%c",buf[selected_octet]);
	wattroff(hex_window->content_window,A_STANDOUT);
	if(typeselection==0){
	wattroff(hex_window->content_window,COLOR_PAIR(2));
	}

	if(typeselection==1){
	wattron(char_window->content_window,COLOR_PAIR(2));
	}
	wattron(char_window->content_window,A_STANDOUT);
	mvwprintw(char_window->content_window,y_char,x_char,"%c",buf[selected_octet]);
	wattroff(char_window->content_window,A_STANDOUT);
	if(typeselection==1){
	wattroff(char_window->content_window,COLOR_PAIR(2));
	}
	free(hex);
}


void afficher_carte(WIN * fenetre_carte,char* carte){
	/* TODO */
}
