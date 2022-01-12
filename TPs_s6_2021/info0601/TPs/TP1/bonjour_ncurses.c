#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

void ncurses_initialisation();
void ncurses_stopper();
void ncurses_couleurs();



int main(int argc, char** argv){
    FILE *fptr;
    int ch, posX, posY;
    int color = 1;
    ncurses_initialisation();
    ncurses_couleurs();
    curs_set(FALSE);
    posX = COLS / 2 - 1; posY = LINES / 2 - 1;
    
        mvprintw(posY, posX, "Bonjour :)");

    while((ch = getch()) != KEY_F(2)) {
        switch (ch)
        {
        case KEY_F(4):
            attron(COLOR_PAIR(color));
            mvprintw(posY, posX, "F2 pour quitter, entree pour editer, haut, bas pour changer de bloc de 128 octets");
            break;
        }
        color++;
        if(color > 4){
            color = 1;
        }
    }

ncurses_stopper();


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