#include <ncurses.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "ihm_ncurses.h"
#include "fichier.h"

int main(int argc, char** argv){
    int ch, posX, posY, fd, size, tmp=0, typeselection;
    char * buf=malloc(129*sizeof(char));
    char * disp;
    char * disp2;
    char tmpch;
    int offset=0;
    WIN *win;
    WIN *win2;
    WIN *win3;
    
    ncurses_initialisation();
    ncurses_couleurs();
    curs_set(FALSE);
    ncurses_initsouris();

    win = initialiser_win(0,0,7,COLS,"Informations");
    afficher_win(win);
    refresh_win(win);

    win2= initialiser_win(0,7,22,42,"Hexadecimal");
    afficher_win(win2);
    refresh_win(win2);

    win3= initialiser_win(42,7,18,10,"char");
    afficher_win(win3);
    refresh_win(win3);

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
        
        if(0<read(fd, buf, 128)){
            buf[128]='\0';
            disp2 = to_disp(buf);
            print_win(win3,disp2);
            refresh_win(win3);
            disp = to_string(buf,offset);
            print_win(win2,disp);
            refresh_win(win2);
        }else{
            ncurses_stopper();
            return(EXIT_FAILURE);
        }

    }else{
        ncurses_stopper();
        return(EXIT_FAILURE);
    }

   while((ch = getch()) != KEY_F(2)){

        switch(ch) {
            case KEY_MOUSE :
            if(souris_getpos(&posX, &posY) == OK){
                wclear(win2->content_window);
                wclear(win3->content_window);
                print_win(win3,disp2);
                refresh_win(win3);
                print_win(win2,disp);

                tmp = selection(posX,posY,&typeselection);   /*a changer*/

                wclear(win->content_window);
                wprintw(win->content_window,"%d,%d char selectionné %d \n cliquez sur l'octet que vous voulez modifier.\n appuyez sur entrée pour éditer,\n ou suppr. pour supprimmer un octet",posX,posY,tmp);
                afficher_selection(tmp,win2,win3,buf,typeselection);
                refresh_win(win);
                refresh_win(win2);
                refresh_win(win3);
            }
            break;
            case KEY_DC :
            supprimer_octet(fd,tmp,offset,size);
            lseek(fd,offset,SEEK_SET);
            lire_buf(fd,buf,offset);
                wclear(win2->content_window);
                wclear(win3->content_window);
                disp = to_string(buf,offset);
                disp2 = to_disp(buf);
                print_win(win3,disp2);
                print_win(win2,disp);
                refresh_win(win);
                refresh_win(win2);
                refresh_win(win3);


            break;
            case 10 :
            wattron(win3->content_window,COLOR_PAIR(2));
            wattron(win3->content_window,A_STANDOUT);
            mvwprintw(win3->content_window,tmp/8,tmp%8," ");
            refresh_win(win3);
            tmpch = getch();
            mvwprintw(win3->content_window,tmp/8,tmp%8,"%c",tmpch);
            refresh_win(win3);
            while ((ch=getch())!=10)
            {
                tmpch = getch();
                mvwprintw(win3->content_window,tmp/8,tmp%8,"%c",tmpch);
                refresh_win(win3);
            }
            wattroff(win3->content_window,A_STANDOUT);
            wattroff(win3->content_window,COLOR_PAIR(2));

            buf[tmp]=tmpch;
            ecrire_buf(fd,buf,offset);
            wprintw(win->content_window,"\n ecriture");
            lire_buf(fd,buf,offset);
            wclear(win2->content_window);
            wclear(win3->content_window);
             disp = to_string(buf,offset);
                disp2 = to_disp(buf);
                print_win(win3,disp2);
                print_win(win2,disp);
                refresh_win(win);
                refresh_win(win2);
                refresh_win(win3);


            break;
            case KEY_UP :
            wprintw(win->content_window,"UP");
            if(offset-128>=0){
                offset=offset-128;
                lire_buf(fd,buf,offset);
                wclear(win2->content_window);
                wclear(win3->content_window);
                disp = to_string(buf,offset);
                disp2 = to_disp(buf);
                print_win(win3,disp2);
                print_win(win2,disp);
                refresh_win(win);
                refresh_win(win2);
                refresh_win(win3);
            }
            break;
            case KEY_DOWN :
            wprintw(win->content_window,"DOWN");
            if((offset+128)<size){
                offset=offset+128;
                lire_buf(fd,buf,offset);
                wclear(win2->content_window);
                wclear(win3->content_window);
                disp = to_string(buf,offset);
                disp2 = to_disp(buf);
                print_win(win3,disp2);
                print_win(win2,disp);
                refresh_win(win);
                refresh_win(win2);
                refresh_win(win3);
            }
            break;

        }


   }
close(fd);
ncurses_stopper();

return(EXIT_SUCCESS);
}