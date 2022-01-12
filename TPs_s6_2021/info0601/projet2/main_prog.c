#include <ncurses.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "ihm_ncurses.h"

int main(int argc, char** argv){
    int ch;
    
    
    WIN *win;
    WIN *win2;
    WIN *win3;
    
    ncurses_initialisation();
    ncurses_couleurs();
    curs_set(FALSE);
    ncurses_initsouris();

    win = initialiser_win(0,0,9,55,"Evenement");
    afficher_win(win);
    refresh_win(win);

    win2= initialiser_win(0,9,12,43,"Etat des clients");
    afficher_win(win2);
    refresh_win(win2);

    win3= initialiser_win(43,9,6,12,"Outils");
    afficher_win(win3);
    refresh_win(win3);

   /*code a executer au lancement de la fenetre*/


   while((ch = getch()) != KEY_F(2)){

        switch(ch) {
            case KEY_MOUSE :
                
            
            break;
            case KEY_DC :
            


            break;
            case 10 :
            
            break;
            case KEY_DOWN :
            
            
            break;

        }


   }
ncurses_stopper();

return(EXIT_SUCCESS);
}