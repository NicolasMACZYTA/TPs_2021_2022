#include "fichier.h"
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

//Dimensions fenetre programme
#define NB_LIGNES_SIM		20
#define NB_COL_SIM			40

#define BACKLOG 10
#define TAILLE_GRILLE 800
#define NB_MONSTRES 250 //nb max de monstres
#define NB_PLAYERS 50 //nb max de joueurs

//Information du joueur
#define X_PLAYER 0
#define Y_PLAYER 1
#define PV 2
#define PV_MAX 3
#define NB_ARTEFACTS 4
#define NB_PIECE 5

//Identifiant des elements pouvant exister
#define VIDE				0
#define OBSTACLE			1
#define MONSTRE				2
#define ARTEFACT			3
#define TRESOR				4

//struct d'une case
typedef struct case_tag{
	int element; //contenu de la case
	pthread_t *monstre; //id thread
	pthread_mutex_t mutex; //permet de lock et unlock pour proteger case
}case_t;

typedef struct coord_tag{
	int y;
	int x;
}coord_t;

int player[6*NB_PLAYERS];

char * file_buf;
char buf[TAILLE_GRILLE+1];
char buf2[TAILLE_GRILLE+1];
int buf_monstre[4*NB_MONSTRES];

//monstre_t tab_monstre[NB_MONSTRES];

typedef struct pthread_arg_t{
    int new_socket_fd;
    struct sockaddr_in client_address;
    int njoueur;
}pthread_arg_t;

case_t grille[NB_LIGNES_SIM][NB_COL_SIM]; //grille de simulation
int nb_monstres; //nb de monstres dans la simulation
pthread_mutex_t mutex_nb_fourmis;
pthread_mutex_t mutex_refresh;
pthread_mutex_t mutex_player;

void modif_pv(int* player,int x, int y,int pv){
    pthread_mutex_lock(&mutex_player);
    for(int i=0;i<NB_PLAYERS;i++){
        if(player[6*i+PV]){
            if(player[6*i+X_PLAYER]==x && player[6*i+Y_PLAYER==y])
                player[6*i+PV]+=pv;
        }
    }
    pthread_mutex_unlock(&mutex_player);
}

void mourrir(coord_t * coord){
    for(int i=0;i<NB_PLAYERS;i++){
        if(player[6*i+PV]){
            if(player[6*i+X_PLAYER]==coord->x && player[6*i+Y_PLAYER==coord->y]){
                pthread_mutex_lock(&grille[coord->y][coord->x].mutex);
                grille[coord->y][coord->x].element = VIDE;
                pthread_mutex_unlock(&grille[coord->y][coord->x].mutex);
                pthread_exit(0);
            }
        }
    }
}

void *routine_monstre(void *arg) {
	coord_t *coord = (coord_t *) arg;
	//pts de vie
	int r;

	while (1) {		
		r = rand() % 4; // Entre 0 et 3 pour la direction
		switch(r){
			case 0:
				if(coord->y > 0 && coord->y < NB_LIGNES_SIM + 1 && coord->x - 1 > 0 && coord->x - 1 < NB_COL_SIM + 1){
					pthread_mutex_lock(&grille[coord->y][coord->x].mutex);
					pthread_mutex_lock(&grille[coord->y][coord->x - 1].mutex);
					if(grille[coord->y][coord->x - 1].element == VIDE){									
						grille[coord->y][coord->x - 1].element = MONSTRE;
						grille[coord->y][coord->x].element = VIDE;
						coord->y = coord->y;
						coord->x = coord->x - 1;
                        modif_pv(player,coord->x,coord->y,-5);
					}
					pthread_mutex_unlock(&grille[coord->y][coord->x].mutex);
					pthread_mutex_unlock(&grille[coord->y][coord->x + 1].mutex);
				}
				break;

			case 1:
				if(coord->y > 0 && coord->y < NB_LIGNES_SIM + 1 && coord->x + 1 > 0 && coord->x + 1 < NB_COL_SIM + 1){
					pthread_mutex_lock(&grille[coord->y][coord->x].mutex);
					pthread_mutex_lock(&grille[coord->y][coord->x + 1].mutex);
					if(grille[coord->y][coord->x + 1].element == VIDE){									
						grille[coord->y][coord->x + 1].element = MONSTRE;
						grille[coord->y][coord->x].element = VIDE;
						coord->y = coord->y;
						coord->x = coord->x + 1;
                        modif_pv(player,coord->x,coord->y,-5);
					}
					pthread_mutex_unlock(&grille[coord->y][coord->x].mutex);
					pthread_mutex_unlock(&grille[coord->y][coord->x - 1].mutex);
				}
				break;

			case 2:
				if(coord->y - 1 > 0 && coord->y - 1 < NB_LIGNES_SIM + 1 && coord->x > 0 && coord->x < NB_COL_SIM + 1){
					pthread_mutex_lock(&grille[coord->y][coord->x].mutex);
					pthread_mutex_lock(&grille[coord->y - 1][coord->x].mutex);
					if(grille[coord->y - 1][coord->x].element == VIDE){									
						grille[coord->y - 1][coord->x].element = MONSTRE;
						grille[coord->y][coord->x].element = VIDE;
						coord->y = coord->y - 1;
						coord->x = coord->x;
                        modif_pv(player,coord->x,coord->y,-5);
					}
					pthread_mutex_unlock(&grille[coord->y][coord->x].mutex);
					pthread_mutex_unlock(&grille[coord->y + 1 ][coord->x].mutex);
				}
				break;

			case 3:
				if(coord->y + 1 > 0 && coord->y + 1 < NB_LIGNES_SIM + 1 && coord->x > 0 && coord->x < NB_COL_SIM + 1){
					pthread_mutex_lock(&grille[coord->y][coord->x].mutex);
					pthread_mutex_lock(&grille[coord->y + 1][coord->x].mutex);
					if(grille[coord->y + 1][coord->x].element == VIDE){									
						grille[coord->y + 1][coord->x].element = MONSTRE;
						grille[coord->y][coord->x].element = VIDE;
						coord->y = coord->y + 1;
						coord->x = coord->x;
                        modif_pv(player,coord->x,coord->y,-5);
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
        mourrir(coord);
		sleep(1);
	}
	
	free(coord);
	return NULL;
}

void simulation_initialiser() {
	int i, j;
	
	nb_monstres = 0; //aucun monstre au debut de simulation
	pthread_mutex_init(&mutex_nb_fourmis, NULL);
    pthread_mutex_init(&mutex_refresh,NULL);
	
	for (i = 0; i < NB_LIGNES_SIM; i++){ //Initialisation des cases de la simulation
		for (j = 0; j < NB_COL_SIM; j++){
			grille[i][j].element = VIDE;
			grille[i][j].monstre = NULL;
			pthread_mutex_init(&grille[i][j].mutex, NULL);
		}
	}
}

void monstre_refresh(){
    //pthread_mutex_lock(&mutex_refresh);
    int nmonstre=0;

    for(int i=0;i<NB_COL_SIM;i++){
        for(int j=0;j<NB_LIGNES_SIM;j++){
            if(grille[j][i].element==MONSTRE){
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

//routine de thread pour la connection au client
void *pthread_routine(void *arg);

//signal handler
void signal_handler(int signal_number);

int main(int argc, char *argv[]) {
    int fd;
    int njoueur=0;
    coord_t *coord;

    simulation_initialiser();
    pthread_mutex_init(&mutex_player,NULL);
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
            pthread_mutex_lock(&grille[buf_monstre[4*i+1]][buf_monstre[4*i]].mutex);
            coord->x=buf_monstre[4*i];
            coord->y=buf_monstre[4*i+1];
            grille[coord->y][coord->x].monstre = (pthread_t *) malloc(sizeof(pthread_t));
            grille[coord->y][coord->x].element = MONSTRE;
            pthread_create(grille[coord->y][coord->x].monstre, NULL, routine_monstre, (void *) coord);
            pthread_mutex_lock(&mutex_nb_fourmis);
            nb_monstres++;
            pthread_mutex_unlock(&mutex_nb_fourmis);
            pthread_mutex_unlock(&grille[buf_monstre[4*i+1]][buf_monstre[4*i]].mutex);
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

    //Verifie si il y a bien deux arguments
    if(argc != 2){
        printf("[ERREUR] Il faut un port.\nExemple: ./serveur 3000\n");
        exit(EXIT_FAILURE);
    }
    port = argc > 1 ? atoi(argv[1]) : 0;

    memset(&address, 0, sizeof address);
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    if (bind(socket_fd, (struct sockaddr *)&address, sizeof address) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(socket_fd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    if (pthread_attr_init(&pthread_attr) != 0) {
        perror("pthread_attr_init");
        exit(1);
    }
    
    if (pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_DETACHED) != 0) {
        perror("pthread_attr_setdetachstate");
        exit(1);
    }









    while (1) {
        pthread_arg = (pthread_arg_t *)malloc(sizeof *pthread_arg);
        if (!pthread_arg) {
            perror("malloc");
            continue;
        }

        client_address_len = sizeof pthread_arg->client_address;
        
        new_socket_fd = accept(socket_fd, (struct sockaddr *)&pthread_arg->client_address, &client_address_len);
        if (new_socket_fd == -1) {
            perror("accept");
            free(pthread_arg);
            continue;
        }
        pthread_arg->new_socket_fd = new_socket_fd;
        pthread_arg->njoueur=njoueur;
        
        if (pthread_create(&pthread, &pthread_attr, pthread_routine, (void *)pthread_arg) != 0) {
            perror("pthread_create");
            free(pthread_arg);
            continue;
        }
        njoueur++;

    }
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

    free(arg);

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