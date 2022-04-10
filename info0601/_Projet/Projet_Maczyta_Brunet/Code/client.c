/*
 * client.c
 * Version 20161003
 * Written by Harry Wong (RedAndBlueEraser)
 */

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ncurses.h>
#include "fichier.h"
#include "ihm_ncurses.h"

#define SERVER_NAME_LEN_MAX 255
#define TAILLE_GRILLE 800
#define NB_MONSTRES 250

#define X_PLAYER 0
#define Y_PLAYER 1
#define PV 2
#define PV_MAX 3
#define NB_ARTEFACTS 4
#define NB_PIECE 5

int main(int argc, char *argv[]) {
    //char buf[TAILLE_GRILLE*2+1];
    int buf_monstre[4*NB_MONSTRES];
    char server_name[SERVER_NAME_LEN_MAX + 1] = { 0 };
    int server_port, socket_fd;
    struct hostent *server_host;
    struct sockaddr_in server_address;
    int player[6]={10,10,100,100,0,0};
    WIN *win;
    WIN *win_carte;
    char buf[TAILLE_GRILLE+1];
    char buf2[TAILLE_GRILLE+1];
    char * disp;
    char * disp2;
    int ch;

    ncurses_initialisation();
    ncurses_couleurs();
    curs_set(FALSE);
    ncurses_initsouris();

    win = initialiser_win(0,0,7,COLS,"Informations");
    afficher_win(win);
    refresh_win(win);


    win_carte= initialiser_win(0,7,22,42,"Carte");
    afficher_win(win_carte);
    refresh_win(win_carte);


    /* Get server name from command line arguments or stdin. */
    if (argc > 1) {
        strncpy(server_name, argv[1], SERVER_NAME_LEN_MAX);
    } else {
        printf("Enter Server Name: ");
        scanf("%s", server_name);
    }

    /* Get server port from command line arguments or stdin. */
    server_port = argc > 2 ? atoi(argv[2]) : 0;
    if (!server_port) {
        printf("Enter Port: ");
        scanf("%d", &server_port);
    }

    /* Get server host from server name. */
    server_host = gethostbyname(server_name);

    /* Initialise IPv4 server address with server host. */
    memset(&server_address, 0, sizeof server_address);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    memcpy(&server_address.sin_addr.s_addr, server_host->h_addr, server_host->h_length);

    /* Create TCP socket. */
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    /* Connect to socket with server address. */
    if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof server_address) == -1) {
		perror("connect");
        exit(1);
	}

    /* TODO: Put server interaction code here. For example, use
     * write(socket_fd,,) and read(socket_fd,,) to send and receive messages
     * with the client.
     */

    
        
        send(socket_fd,player,6*sizeof(int),0);
        recv(socket_fd,buf,800,0);
          recv(socket_fd,buf2,800,0);
          recv(socket_fd,buf_monstre,NB_MONSTRES*4*sizeof(int),0);
          recv(socket_fd,player,6*sizeof(int),0);


            printf("\nmonsttres : %d, %d\n",buf_monstre[0],buf_monstre[999]);


            disp=to_disp(buf);
            disp2=to_disp(buf2);
            print_map(win_carte,disp,disp2);
            refresh_win(win_carte);


      
            while((ch = getch()) != KEY_F(2)){
            

        switch(ch) {
            case KEY_MOUSE :
                disp = to_disp(buf);
                disp2 = to_disp(buf2);
                print_map(win_carte,disp,disp2);
                print_monstres(win_carte,NB_MONSTRES,buf_monstre);
                wclear(win->content_window);
                refresh_win(win);
                refresh_win(win_carte);
            break;
            case KEY_DC :

            break;
            case 10 :

            break;
            case KEY_UP :
            player[Y_PLAYER]=(player[Y_PLAYER]-1)%20;
            
            break;
            case KEY_DOWN :
            player[Y_PLAYER]=(player[Y_PLAYER]+1)%20;
            break;
            case KEY_LEFT :
            player[X_PLAYER]=(player[X_PLAYER]-1)%40;
            break;
            case KEY_RIGHT :
            player[X_PLAYER]=(player[X_PLAYER]+1)%40;
            break;

        }

            send(socket_fd,player,6*sizeof(int),0);
        recv(socket_fd,buf,800,0);
          recv(socket_fd,buf2,800,0);
          recv(socket_fd,buf_monstre,NB_MONSTRES*4*sizeof(int),0);
          recv(socket_fd,player,6*sizeof(int),0);
          disp = to_disp(buf);
                disp2 = to_disp(buf2);
                wclear(win->content_window);
                wprintw(win->content_window,"PV        : %d\n",player[PV]);
                wprintw(win->content_window,"PV MAX    : %d\n",player[PV_MAX]);
                wprintw(win->content_window,"ARTEFACTS : %d\n",player[NB_ARTEFACTS]);
                wprintw(win->content_window,"PIECES    : %d\n",player[NB_PIECE]);
                wprintw(win->content_window,"monstre 1 : %d %d %d",buf_monstre[0],buf_monstre[1],buf_monstre[2]);

                print_map(win_carte,disp,disp2);
                print_monstres(win_carte,NB_MONSTRES,buf_monstre);
                mvwprintw(win_carte->content_window,player[Y_PLAYER],player[X_PLAYER],"J");
                refresh_win(win);
                refresh_win(win_carte);

   }
          

    close(socket_fd);
    ncurses_stopper();
    return 0;
}