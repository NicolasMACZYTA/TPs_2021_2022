#include "ihm_ncurses.h"
#include "fichier.h"
#include <ncurses.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define TAILLE_GRILLE 800
#define NB_MONSTRES 250
#define NB_GRILLES 1

int main(int argc, char** argv){
    int nmonstre=0;
    int ch, posX, posY, fd, size, tmp=0, typeselection;
    int outil_choisi=1;
    int buf_monstre[4*NB_MONSTRES];
    char buf[TAILLE_GRILLE+1];
    char buf2[TAILLE_GRILLE+1];
    char * disp;
    char * disp2;
    //monstre_t tab_monstre[NB_MONSTRES];
    //char tmpch;
    //int offset=0;
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

    //win_carte = carte

    win_carte= initialiser_win(0,7,22,42,"Carte");
    afficher_win(win_carte);
    refresh_win(win_carte);

    win_outils= initialiser_win(42,7,22,18,"Outils");
    afficher_win(win_outils);
    refresh_win(win_outils);

    if(!(0<open(argv[1],O_RDONLY))){
        if(-1==(fd=creer_fichier(argv[1],TAILLE_GRILLE,NB_GRILLES*2,NB_MONSTRES))){
            perror("erreur de création du fichier");
            ncurses_stopper();
            return(EXIT_FAILURE);
        }
    }

    attron(A_STANDOUT);
    mvprintw(29, 0, "F2 pour quitter, entree pour editer, haut, bas pour changer de bloc de 128 octets");
    attroff(A_STANDOUT);
    print_win(win,argv[1]);
    fd = open(argv[1], O_RDWR);
    size = lseek(fd, 0, SEEK_END);
    wprintw(win->content_window, "\nest de taille : %d octets\n",size);
    //wprintw(win->content_window,"cliquez sur l'octet que vous voulez modifier.\n appuyez sur entrée pour éditer,\n ou suppr. pour supprimmer un octet");
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

    lseek(fd, 1600,SEEK_SET);
    if(!(0<read(fd, buf_monstre, NB_MONSTRES*4*sizeof(int)))){
        ncurses_stopper();
        return(EXIT_FAILURE);
    }

    wprintw(win->content_window, "\nmonstre 1 : %d et 250 %d\n",buf_monstre[0],buf_monstre[999]);
    refresh_win(win);
    print_outils(win_outils,outil_choisi);
    refresh_win(win_outils);
    disp = to_disp((char*)buf);
    disp2 = to_disp((char*)buf2);
    print_map(win_carte,disp,disp2);
    print_monstres(win_carte,NB_MONSTRES,buf_monstre);
    refresh_win(win_carte);
    while((ch = getch()) != KEY_F(2)){
        switch(ch){
            case KEY_MOUSE:
                if(souris_getpos(&posX, &posY) == OK){
                    wclear(win_carte->content_window);
                    wclear(win_outils->content_window);
                    tmp = selection(posX,posY,&typeselection,&outil_choisi);   /*a changer*/
                    if(typeselection==0){
                        switch(outil_choisi){
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
                            buf2[tmp]='h';
                            buf_monstre[4*nmonstre]=tmp%40;
                            buf_monstre[4*nmonstre+1]=tmp/40;
                            buf_monstre[4*nmonstre+2]=1;
                            nmonstre++;
                            break;

                        case 8:
                            buf2[tmp]='A';
                            break;

                        case 9:
                            buf2[tmp]='h';
                            break;

                        default:
                            break;
                        }
                    }
                    disp = to_disp(buf);
                    disp2 = to_disp(buf2);
                    refresh_win(win_outils);
                    print_map(win_carte,disp,disp2);
                    print_monstres(win_carte,NB_MONSTRES,buf_monstre);
                    print_outils(win_outils,outil_choisi);
                    wclear(win->content_window);
                    wprintw(win->content_window,"%d,%d char selectionné %d \n type selection : %d",posX,posY,tmp,typeselection);
                    refresh_win(win);
                    refresh_win(win_carte);
                    refresh_win(win_outils);
                }
                break;

            case KEY_DC :
                break;

            case 10 :
                break;

            case KEY_UP :
                break;

            case KEY_DOWN :
                break;
        }
    }

    close(fd);
    sauvegarder_carte(argv[1],buf,buf2,buf_monstre,TAILLE_GRILLE,NB_MONSTRES);
    ncurses_stopper();

    return(EXIT_SUCCESS);
}