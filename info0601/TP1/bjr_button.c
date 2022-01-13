#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "ncurses.h"

int main(int argc, char** argv){
    int ch, posX, posY, sourisX, sourisY, bouton;
    ncurses_initialiser();
    ncurses_couleurs();
    ncurses_palette();
    ncurses_souris();
    scrollok(stdscr, TRUE);
    curs_set(TRUE);
    posX = COLS / 2-1;
    posY = LINES / 2-1;

    mvprintw(posY, posX, "Bonjour.\n");

    attron(COLOR_PAIR(4));
    mvprintw(posY+2, posX/2, " ");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(5));
    mvprintw(posY+2, posX, " ");
    attroff(COLOR_PAIR(5));
    attron(COLOR_PAIR(6));
    mvprintw(posY+2, posX + posX/2, " ");
    attroff(COLOR_PAIR(6));
    printw("\n\nAppuyez sur une couleur ou une touche pour changer la couleur de Bonjour.\n");
    printw("1: Bleu | 2: Rouge | 3: Vert\nF2: Exit\n");

    while((ch = getch()) != KEY_F(2)){
        switch(ch){
            case '1':
                attron(COLOR_PAIR(1));
                mvprintw(posY, posX, "Bonjour.\n");
                attroff(COLOR_PAIR(1));
                break;
            case '2':
                attron(COLOR_PAIR(2));
                mvprintw(posY, posX, "Bonjour.\n");
                attroff(COLOR_PAIR(2));
                break;
            case '3':
                attron(COLOR_PAIR(3));
                mvprintw(posY, posX, "Bonjour.\n");
                attroff(COLOR_PAIR(3));
                break;
            case KEY_MOUSE:
                if(souris_getpos(&sourisX, &sourisY, &bouton) == OK){
                    if(bouton & BUTTON1_CLICKED){               
                        if((sourisX == posX/2) & (sourisY == posY+2)){
                            attron(COLOR_PAIR(1));
                            mvprintw(posY, posX, "Bonjour.\n");
                            attroff(COLOR_PAIR(1));
                        }
                        if((sourisX == posX) & (sourisY == posY+2)){
                            attron(COLOR_PAIR(2));
                            mvprintw(posY, posX, "Bonjour.\n");
                            attroff(COLOR_PAIR(2));
                        }
                        if((sourisX == posX + posX/2) & (sourisY == posY+2)){
                            attron(COLOR_PAIR(3));
                            mvprintw(posY, posX, "Bonjour.\n");
                            attroff(COLOR_PAIR(3));
                        }
                    }
                    refresh();
                }
        }
    }

    ncurses_stopper();

    return 0;
}