#include <ncurses.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>

#include "ihm_ncurses.h"
#include "fichier.h"

#define TAILLE_GRILLE 800
#define SERVER_NAME_LEN_MAX 255
#define SERVER_NAME "127.0.0.1"
#define SERVER_PORT 3000

char buf[TAILLE_GRILLE+1];
char buf2[TAILLE_GRILLE+1];
char * disp;
char * disp2;
WIN *win;
WIN *win_carte;
WIN *win_outils;

void * routine_tcp(){
    char server_name[SERVER_NAME_LEN_MAX + 1] = { 0 };
    int server_port, socket_fd;
    struct hostent *server_host;
    struct sockaddr_in server_address;
    /*char client_message[2000];*/

    /* Get server name from command line arguments or stdin. */
        strncpy(server_name, SERVER_NAME, SERVER_NAME_LEN_MAX);

    /* Get server port from command line arguments or stdin. */
    server_port = SERVER_PORT;

    /* Get server host from server name. */
    server_host = gethostbyname(server_name);

    /* Initialise IPv4 server address with server host. */
    memset(&server_address, 0, sizeof server_address);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    memcpy(&server_address.sin_addr.s_addr, server_host->h_addr_list, server_host->h_length);

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
    
    
        while(1)
      {
          send(socket_fd,"11",3,0);
          recv(socket_fd,buf,801,0);
          print_win(win,"reception carte");
          refresh_win(win);
          disp = to_disp(buf);
        
      }
    
    


    close(socket_fd);
    return 0;
}



int main(int argc, char** argv){

    int ch, posX, posY, tmp=0, typeselection;
    int selected_tool=1;
    

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
            case KEY_UP :
            break;
            case KEY_DOWN :
            break;

        }


   }
ncurses_stopper();

return(EXIT_SUCCESS);
}