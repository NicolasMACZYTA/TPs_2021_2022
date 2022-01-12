#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

void ncurses_initialisation();
void ncurses_stopper();
void ncurses_couleurs();
void ncurses_initsouris();
int souris_getpos(int *x, int *y);
WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);







int main(int argc, char** argv){
    int ch, posX, posY;
    int height = 3;
	int width = 10;
    

    //int x,y;
    //int color = 1;
    ncurses_initialisation();
    ncurses_couleurs();
    curs_set(FALSE);
    ncurses_initsouris();
    int starty = (LINES - height) / 2;	/* Calculating for a center placement */
	int startx = (COLS - width) / 2;	/* of the window		*/
    printw("Press F2 to exit");

    //MEVENT event;
    posX = COLS / 2 - 1; posY = LINES / 2 - 1;
    WINDOW * my_win = create_newwin(height, width, starty, startx);

    
        mvprintw(posY, posX, "Bonjour :)");

   while((ch = getch()) != KEY_F(2)){

        switch(ch) {
            case KEY_MOUSE:
            if(souris_getpos(&posX, &posY) == OK)
                mvprintw(LINES - 1, 2,"Click a la position (%d, %d)",posX, posY);
            case KEY_LEFT:
				destroy_win(my_win);
				my_win = create_newwin(height, width, starty,--startx);
				break;
			case KEY_RIGHT:
				destroy_win(my_win);
				my_win = create_newwin(height, width, starty,++startx);
				break;
			case KEY_UP:
				destroy_win(my_win);
				my_win = create_newwin(height, width, --starty,startx);
				break;
			case KEY_DOWN:
				destroy_win(my_win);
				my_win = create_newwin(height, width, ++starty,startx);
        }
   }



ncurses_stopper();


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

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void destroy_win(WINDOW *local_win)
{	
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}