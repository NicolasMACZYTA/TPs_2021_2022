#include "ihm_ncurses.h"
#include <ncurses.h>



int main(int argc, char** argv){
    ncurses_initialisation();
    ncurses_couleurs();
    curs_set(FALSE);
    ncurses_initsouris();

    int ch, posX, posY;
    WIN *win = initialiser_win(0,0,LINES,COLS,"test");
    afficher_win(win);
    print_win(win,"test2");
    refresh_win(win);

   while((ch = getch()) != KEY_F(2)){

        switch(ch) {
            case KEY_MOUSE:
            if(souris_getpos(&posX, &posY) == OK)
                mvprintw(LINES - 1, 2,"Click a la position (%d, %d)",posX, posY);
        }
   }

   //free(boite);
ncurses_stopper();
}