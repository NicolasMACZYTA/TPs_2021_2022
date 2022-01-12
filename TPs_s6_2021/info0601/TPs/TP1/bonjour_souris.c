#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

void ncurses_initialisation();
void ncurses_stopper();
void ncurses_couleurs();
void ncurses_initsouris();
int souris_getpos(int *x, int *y);







int main(int argc, char** argv){
    int ch, posX, posY;
    //int x,y;
    //int color = 1;
    ncurses_initialisation();
    ncurses_couleurs();
    curs_set(FALSE);
    ncurses_initsouris();


    //MEVENT event;
    posX = COLS / 2 - 1; posY = LINES / 2 - 1;

    
        mvprintw(posY, posX, "Bonjour :)");

   while((ch = getch()) != KEY_F(2)){

        switch(ch) {
            case KEY_MOUSE:
            if(souris_getpos(&posX, &posY) == OK)
                mvprintw(LINES - 1, 2,"Click a la position (%d, %d)",posX, posY);
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