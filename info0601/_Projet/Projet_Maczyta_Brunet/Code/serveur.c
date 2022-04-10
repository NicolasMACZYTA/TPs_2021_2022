/*
 * server.c
 * Version 20161003
 * Written by Harry Wong (RedAndBlueEraser)
 */

#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <fcntl.h>

#include "fichier.h"
#include "monstre.h"

#define NB_LIGNES_SIM		20				/* Dimensions des fenetres du programme */
#define NB_COL_SIM			40

#define BACKLOG 10
#define TAILLE_GRILLE 800
#define NB_MONSTRES 250
#define NB_PLAYERS 50

#define X_PLAYER 0
#define Y_PLAYER 1
#define PV 2
#define PV_MAX 3
#define NB_ARTEFACTS 4
#define NB_PIECE 5

#define VIDE				0				/* Identifiants des elements pouvant etre */
#define OBSTACLE			1				/* places sur la grille de simulation */
#define FOURMI				2

typedef struct case_tag {					/* Description d'une case sur la grille de simulation */
	int element;							/* Ce qui est present sur la case */
	pthread_t *fourmi;						/* Identifiant du thread de la fourmi presente sur la case */
	pthread_mutex_t mutex;					/* Protection de la case */
} case_t;

typedef struct coord_tag {					/* Coordonnees d'une case sur la grille de simulation*/
	int y;
	int x;
} coord_t;

int player[6*NB_PLAYERS];

char * file_buf;
char buf[TAILLE_GRILLE+1];
char buf2[TAILLE_GRILLE+1];
int buf_monstre[4*NB_MONSTRES];

//monstre_t tab_monstre[NB_MONSTRES];



typedef struct pthread_arg_t {
    int new_socket_fd;
    struct sockaddr_in client_address;
    int njoueur;
    /* TODO: Put arguments passed to threads here. See lines 116 and 139. */
} pthread_arg_t;

case_t grille[NB_LIGNES_SIM][NB_COL_SIM];	/* Grille de simulation */
int nb_fourmis;								/* Nombre de fourmis de la simulation*/
pthread_mutex_t mutex_nb_fourmis;
pthread_mutex_t mutex_refresh;


void *routine_fourmi(void *arg) {
	coord_t *coord = (coord_t *) arg;
	//pts de vie
	int r;

	while (1) {		
		/*Que feront les fourmis ?!?!?!*/
		r = rand() % 4; // Entre 0 et 3
		switch(r){
			case 0:
				//wprintw(fen_msg, "<-\n");
				//wrefresh(fen_msg);
				if(coord->y > 0 && coord->y < NB_LIGNES_SIM + 1 && coord->x - 1 > 0 && coord->x - 1 < NB_COL_SIM + 1){
					pthread_mutex_lock(&grille[coord->y][coord->x].mutex);
					pthread_mutex_lock(&grille[coord->y][coord->x - 1].mutex);
					if(grille[coord->y][coord->x - 1].element == VIDE){									
						grille[coord->y][coord->x - 1].element = FOURMI;
						grille[coord->y][coord->x].element = VIDE;
						//mvwprintw(fen_sim, coord->y, coord->x, " ");
						//mvwprintw(fen_sim, coord->y, coord->x - 1, "@");
						coord->y = coord->y;
						coord->x = coord->x - 1;
					}
					pthread_mutex_unlock(&grille[coord->y][coord->x].mutex);
					pthread_mutex_unlock(&grille[coord->y][coord->x + 1].mutex);
				}
				break;
			case 1:
				//wprintw(fen_msg, "->\n");
				//wrefresh(fen_msg);
				if(coord->y > 0 && coord->y < NB_LIGNES_SIM + 1 && coord->x + 1 > 0 && coord->x + 1 < NB_COL_SIM + 1){
					pthread_mutex_lock(&grille[coord->y][coord->x].mutex);
					pthread_mutex_lock(&grille[coord->y][coord->x + 1].mutex);
					if(grille[coord->y][coord->x + 1].element == VIDE){									
						grille[coord->y][coord->x + 1].element = FOURMI;
						grille[coord->y][coord->x].element = VIDE;
						//mvwprintw(fen_sim, coord->y, coord->x, " ");
						//mvwprintw(fen_sim, coord->y, coord->x + 1, "@");
						coord->y = coord->y;
						coord->x = coord->x + 1;
					}
					pthread_mutex_unlock(&grille[coord->y][coord->x].mutex);
					pthread_mutex_unlock(&grille[coord->y][coord->x - 1].mutex);
				}
				break;
			case 2:
				//wprintw(fen_msg, "^\n");
				//wrefresh(fen_msg);
				if(coord->y - 1 > 0 && coord->y - 1 < NB_LIGNES_SIM + 1 && coord->x > 0 && coord->x < NB_COL_SIM + 1){
					pthread_mutex_lock(&grille[coord->y][coord->x].mutex);
					pthread_mutex_lock(&grille[coord->y - 1][coord->x].mutex);
					if(grille[coord->y - 1][coord->x].element == VIDE){									
						grille[coord->y - 1][coord->x].element = FOURMI;
						grille[coord->y][coord->x].element = VIDE;
						//mvwprintw(fen_sim, coord->y, coord->x, " ");
						//mvwprintw(fen_sim, coord->y - 1, coord->x, "@");
						coord->y = coord->y - 1;
						coord->x = coord->x;
					}
					pthread_mutex_unlock(&grille[coord->y][coord->x].mutex);
					pthread_mutex_unlock(&grille[coord->y + 1 ][coord->x].mutex);
				}
				break;
			case 3:
				//wprintw(fen_msg, "v\n");
				//wrefresh(fen_msg);
				if(coord->y + 1 > 0 && coord->y + 1 < NB_LIGNES_SIM + 1 && coord->x > 0 && coord->x < NB_COL_SIM + 1){
					pthread_mutex_lock(&grille[coord->y][coord->x].mutex);
					pthread_mutex_lock(&grille[coord->y + 1][coord->x].mutex);
					if(grille[coord->y + 1][coord->x].element == VIDE){									
						grille[coord->y + 1][coord->x].element = FOURMI;
						grille[coord->y][coord->x].element = VIDE;
						//mvwprintw(fen_sim, coord->y, coord->x, " ");
						//mvwprintw(fen_sim, coord->y + 1, coord->x, "@");
						coord->y = coord->y + 1;
						coord->x = coord->x;
					}
					pthread_mutex_unlock(&grille[coord->y][coord->x].mutex);
					pthread_mutex_unlock(&grille[coord->y - 1 ][coord->x].mutex);
				}
				break;
		}
		//pthread_mutex_lock(&mutex_refresh);
		//wrefresh(fen_sim);
        //ecrire monstres
		//pthread_mutex_unlock(&mutex_refresh);
		sleep(1);
	}
	
	free(coord);
	return NULL;
}

void simulation_initialiser() {
	int i, j;
	
	nb_fourmis = 0;							/* Au depart il n'y a aucune fourmi dans la simulation */
	pthread_mutex_init(&mutex_nb_fourmis, NULL);
    pthread_mutex_init(&mutex_refresh,NULL);
	
	for (i = 0; i < NB_LIGNES_SIM; i++) {	/* Initialisation des cases de la simulation */
		for (j = 0; j < NB_COL_SIM; j++) {
			grille[i][j].element = VIDE;
			grille[i][j].fourmi = NULL;
			pthread_mutex_init(&grille[i][j].mutex, NULL);
		}
	}
}

void monstre_refresh(){
    //pthread_mutex_lock(&mutex_refresh);
    int nmonstre=0;
    for(int i=0;i<NB_COL_SIM;i++){
        for(int j=0;j<NB_LIGNES_SIM;j++){
            if(grille[j][i].element==FOURMI){
                buf_monstre[4*nmonstre+2]=1;
                buf_monstre[4*nmonstre]=i;
                buf_monstre[4*nmonstre+1]=j;
                nmonstre++;
            }
        }
    }
    for(int i=nmonstre;i<NB_MONSTRES;i++){
        buf_monstre[4*i+2]=0;
    }
    //pthread_mutex_unlock(&mutex_refresh);
}

/* Thread routine to serve connection to client. */
void *pthread_routine(void *arg);

/* Signal handler to handle SIGTERM and SIGINT signals. */
void signal_handler(int signal_number);

int main(int argc, char *argv[]) {
    int fd;
    int njoueur=0;
    coord_t *coord;

    

    simulation_initialiser();
    if(!(0<(fd=open(argv[2],O_RDONLY)))){
        perror("erreur de lecture du fichier");
            return(EXIT_FAILURE);
    }

    if(0<read(fd, buf, TAILLE_GRILLE)){

            buf[TAILLE_GRILLE]='\0';
            
        }else{
            return(EXIT_FAILURE);
        }
    if(0<read(fd, buf2, TAILLE_GRILLE)){

            buf2[TAILLE_GRILLE]='\0';
            
        }else{
            return(EXIT_FAILURE);
        }
        lseek(fd, 1600,SEEK_SET);
        
        if(!(0<read(fd, buf_monstre, NB_MONSTRES*4*sizeof(int)))){
            
            return(EXIT_FAILURE);
        }

        for(int i=0;i<NB_MONSTRES;i++){
            
            
            if(buf_monstre[4*i+2]){
                coord = (coord_t *) malloc(sizeof(coord_t));
                //pthread_mutex_lock(&grille[buf_monstre[4*i+1]][buf_monstre[4*i]].mutex);
                coord->x=buf_monstre[4*i];
                coord->y=buf_monstre[4*i+1];
                grille[coord->y][coord->x].fourmi = (pthread_t *) malloc(sizeof(pthread_t));
                
                grille[coord->y][coord->x].element = FOURMI;
                pthread_create(grille[coord->y][coord->x].fourmi, NULL, routine_fourmi, (void *) coord);
                pthread_mutex_lock(&mutex_nb_fourmis);
				nb_fourmis++;
                pthread_mutex_unlock(&mutex_nb_fourmis);
                //pthread_mutex_unlock(&grille[buf_monstre[4*i+1]][buf_monstre[4*i]].mutex);
            }
            
        }


    if(0<open(argv[2],O_RDONLY)){
        
        fd = open(argv[2], O_RDWR);
        lseek(fd, 0, SEEK_END);
        lseek(fd, 0, SEEK_SET);
        
        if(0<read(fd, buf, TAILLE_GRILLE)){
            
            buf[TAILLE_GRILLE]='\0';


        }else{
            return(EXIT_FAILURE);
        }
        

    }else{
        return(EXIT_FAILURE);
    }

    int port, socket_fd, new_socket_fd;
    struct sockaddr_in address;
    pthread_attr_t pthread_attr;
    pthread_arg_t *pthread_arg;
    pthread_t pthread;
    socklen_t client_address_len;

    /* Get port from command line arguments or stdin. */
    port = argc > 1 ? atoi(argv[1]) : 0;
    if (!port) {
        printf("Enter Port: ");
        scanf("%d", &port);
    }

    /* Initialise IPv4 address. */
    memset(&address, 0, sizeof address);
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    /* Create TCP socket. */
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    /* Bind address to socket. */
    if (bind(socket_fd, (struct sockaddr *)&address, sizeof address) == -1) {
        perror("bind");
        exit(1);
    }

    /* Listen on socket. */
    if (listen(socket_fd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    /* Assign signal handlers to signals. */
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        perror("signal");
        exit(1);
    }
    if (signal(SIGTERM, signal_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    /* Initialise pthread attribute to create detached threads. */
    if (pthread_attr_init(&pthread_attr) != 0) {
        perror("pthread_attr_init");
        exit(1);
    }
    if (pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_DETACHED) != 0) {
        perror("pthread_attr_setdetachstate");
        exit(1);
    }









    while (1) {
        /* Create pthread argument for each connection to client. */
        /* TODO: malloc'ing before accepting a connection causes only one small
         * memory when the program exits. It can be safely ignored.
         */
        pthread_arg = (pthread_arg_t *)malloc(sizeof *pthread_arg);
        if (!pthread_arg) {
            perror("malloc");
            continue;
        }

        /* Accept connection to client. */
        client_address_len = sizeof pthread_arg->client_address;
        
        new_socket_fd = accept(socket_fd, (struct sockaddr *)&pthread_arg->client_address, &client_address_len);
        if (new_socket_fd == -1) {
            perror("accept");
            free(pthread_arg);
            continue;
        }

        /* Initialise pthread argument. */
        pthread_arg->new_socket_fd = new_socket_fd;
        /* TODO: Initialise arguments passed to threads here. See lines 22 and
         * 139.
         */
        pthread_arg->njoueur=njoueur;
        

        /* Create thread to serve connection to client. */
        if (pthread_create(&pthread, &pthread_attr, pthread_routine, (void *)pthread_arg) != 0) {
            perror("pthread_create");
            free(pthread_arg);
            continue;
        }
        njoueur++;

    }

    /* close(socket_fd);
     * TODO: If you really want to close the socket, you would do it in
     * signal_handler(), meaning socket_fd would need to be a global variable.
     */
    return 0;
}

void *pthread_routine(void *arg) {
    int n,njoueur;
    int joueur_client[6];
    //char client_message[2000];
    pthread_arg_t *pthread_arg = (pthread_arg_t *)arg;
    int new_socket_fd = pthread_arg->new_socket_fd;
    njoueur = pthread_arg->njoueur;
    //struct sockaddr_in client_address = pthread_arg->client_address;
    /* TODO: Get arguments passed to threads here. See lines 22 and 116. */

    free(arg);

    /* TODO: Put client interaction code here. For example, use
     * write(new_socket_fd,,) and read(new_socket_fd,,) to send and receive
     * messages with the client.
     */

        recv(new_socket_fd,player,6*NB_PLAYERS*sizeof(int),0);
        send(new_socket_fd,&njoueur,1*sizeof(int),0);
        send(new_socket_fd,buf,strlen(buf),0);
        send(new_socket_fd,buf2,strlen(buf2),0);
        send(new_socket_fd,buf_monstre,NB_MONSTRES*4*sizeof(int),0);
        player[6*njoueur+X_PLAYER]=10;
        player[6*njoueur+Y_PLAYER]=10;
        player[6*njoueur+PV]=100;
        player[6*njoueur+PV_MAX]=100;
        player[6*njoueur+NB_ARTEFACTS]=0;
        player[6*njoueur+NB_PIECE]=0;
        send(new_socket_fd,player,6*NB_PLAYERS*sizeof(int),0);


     while((n=recv(new_socket_fd,joueur_client,6*sizeof(int),0))>0)
      {
        player[6*njoueur+X_PLAYER]=joueur_client[X_PLAYER];
        player[6*njoueur+Y_PLAYER]=joueur_client[Y_PLAYER];
        player[6*njoueur+PV]=joueur_client[PV];
        player[6*njoueur+PV_MAX]=joueur_client[PV_MAX];
        player[6*njoueur+NB_ARTEFACTS]=joueur_client[NB_ARTEFACTS];
        player[6*njoueur+NB_PIECE]=joueur_client[NB_PIECE];
        for(int i=0;i<NB_PLAYERS*6;i++){

        printf("%d",player[i]);
        }
        printf("\n");
        monstre_refresh();
        send(new_socket_fd,&njoueur,1*sizeof(int),0);
        send(new_socket_fd,buf,strlen(buf),0);
        send(new_socket_fd,buf2,strlen(buf2),0);
        send(new_socket_fd,buf_monstre,NB_MONSTRES*4*sizeof(int),0);
        send(new_socket_fd,player,6*NB_PLAYERS*sizeof(int),0);
      }
    close(new_socket_fd);
    player[6*njoueur+PV]=0;
    return NULL;
}

void signal_handler(int signal_number) {
    /* TODO: Put exit cleanup code here. */
    exit(0);
}