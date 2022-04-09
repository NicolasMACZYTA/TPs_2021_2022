#include <ncurses.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "ihm_ncurses.h"
#include "fichier.h"

#define TAILLE_GRILLE 800

int main(int argc, char** argv){

    int ch, posX, posY, fd, size, tmp=0, typeselection;
    int selected_tool=1;

    char buf[TAILLE_GRILLE+1];
    char buf2[TAILLE_GRILLE+1];
    char * disp;
    char * disp2;

    char tmpch;
    int offset=0;
    WIN *win;
    WIN *win_carte;
    WIN *win_outils;

    ncurses_initialisation();
    ncurses_couleurs();
    curs_set(FALSE);
    ncurses_initsouris();

    win = initialiser_win(0,0,7,COLS,"Informations");
    afficher_win(win);
    refresh_win(win);

    /*win_carte = carte*/


    win_carte= initialiser_win(0,7,22,42,"Carte");
    afficher_win(win_carte);
    refresh_win(win_carte);

    win_outils= initialiser_win(42,7,22,18,"Outils");
    afficher_win(win_outils);
    refresh_win(win_outils);

    if(0<open(argv[1],O_RDONLY)){
        attron(A_STANDOUT);
        mvprintw(29, 0, "F2 pour quitter, entree pour editer, haut, bas pour changer de bloc de 128 octets");
        attroff(A_STANDOUT);
        print_win(win,argv[1]);
        fd = open(argv[1], O_RDWR);
        size = lseek(fd, 0, SEEK_END);
        wprintw(win->content_window, "\nest de taille : %d octets\n",size);
        wprintw(win->content_window,"cliquez sur l'octet que vous voulez modifier.\n appuyez sur entrée pour éditer,\n ou suppr. pour supprimmer un octet");
        refresh_win(win);
        lseek(fd, 0, SEEK_SET);
        
        if(0<read(fd, buf, 800)){

            buf[800]='\0';


        }else{
            ncurses_stopper();
            return(EXIT_FAILURE);
        }

        lseek(fd, 800,SEEK_SET);
        if(0<read(fd, buf2, 800)){

            buf2[800]='\0';

        }else{
            ncurses_stopper();
            return(EXIT_FAILURE);
        }


            print_outils(win_outils,selected_tool);
            refresh_win(win_outils);
            disp = to_disp(buf);
            disp2 = to_disp(buf2);
            print_map(win_carte,disp,disp2);
            refresh_win(win_carte);


    }else{
        ncurses_stopper();
        return(EXIT_FAILURE);
    }

   while((ch = getch()) != KEY_F(2)){

        switch(ch) {
            case KEY_MOUSE :
            if(souris_getpos(&posX, &posY) == OK){
                wclear(win_carte->content_window);
                wclear(win_outils->content_window);
                
                

                tmp = selection(posX,posY,&typeselection,&selected_tool);   /*a changer*/
                if(typeselection==0){
                    switch (selected_tool)
                    {
                    case 1:
                        buf[tmp]='h';
                        break;
                    case 2:
                        buf[tmp]='s';
                        break;
                    case 3:
                        buf[tmp]='e';
                        break;
                    case 4:
                        buf[tmp]='m';
                        break;
                    case 5:
                        buf2[tmp]='X';
                        break;
                    case 6:
                        buf2[tmp]='$';
                        break;
                    case 7:
                        buf2[tmp]='M';
                        break;
                    case 8:
                        buf2[tmp]='A';
                        break;
                    case 9:
                        buf2[tmp]=' ';
                        break;

                    default:
                        break;
                    }
                }
                disp = to_disp(buf);
                disp2 = to_disp(buf2);
                refresh_win(win_outils);
                print_map(win_carte,disp,disp2);
                print_outils(win_outils,selected_tool);
                wclear(win->content_window);
                wprintw(win->content_window,"%d,%d char selectionné %d \n type selection : %d",posX,posY,tmp,typeselection);
                refresh_win(win);
                refresh_win(win_carte);
                refresh_win(win_outils);
            }
            break;
            case KEY_DC :
            supprimer_octet(fd,tmp,offset,size);
            lseek(fd,offset,SEEK_SET);
            lire_buf(fd,buf,offset);
                wclear(win_carte->content_window);
                wclear(win_outils->content_window);
                disp = to_disp(buf);
                print_outils(win_outils,selected_tool);
                print_map(win_carte,disp,disp2);
                refresh_win(win);
                refresh_win(win_carte);
                refresh_win(win_outils);


            break;
            case 10 :
            wattron(win_outils->content_window,COLOR_PAIR(2));
            wattron(win_outils->content_window,A_STANDOUT);
            mvwprintw(win_outils->content_window,tmp/8,tmp%8," ");
            refresh_win(win_outils);
            tmpch = getch();
            mvwprintw(win_outils->content_window,tmp/8,tmp%8,"%c",tmpch);
            refresh_win(win_outils);
            while ((ch=getch())!=10)
            {
                tmpch = getch();
                mvwprintw(win_outils->content_window,tmp/8,tmp%8,"%c",tmpch);
                refresh_win(win_outils);
            }
            wattroff(win_outils->content_window,A_STANDOUT);
            wattroff(win_outils->content_window,COLOR_PAIR(2));

            buf[tmp]=tmpch;
            ecrire_buf(fd,buf,offset);
            wprintw(win->content_window,"\n ecriture");
            lire_buf(fd,buf,offset);
            wclear(win_carte->content_window);
            wclear(win_outils->content_window);
             disp = to_disp(buf);
             disp2 = to_disp(buf2);
                print_outils(win_outils,selected_tool);
                print_map(win_carte,disp,disp2);
                refresh_win(win);
                refresh_win(win_carte);
                refresh_win(win_outils);


            break;
            case KEY_UP :
            break;
            case KEY_DOWN :
            break;

        }


   }
close(fd);
ncurses_stopper();

return(EXIT_SUCCESS);
}