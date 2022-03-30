#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>
#include"gameplay.h"
typedef struct grille{
  couple tab[20][40];
  pthread_mutex_t tabM[20][40];
}grille;
typedef struct monstre{
  cellule*m;
  pthread_t t;
}monstre;
grille map;
win carte;
int nbMonstre;
int nbArtefact;
hashtable h;

void init_grille(char*,win*);
void destruct_grille();
/*routine*/
void* deplacement(void*);
void* deplacement(void*arg){
  return NULL;
}
void init_grille(char*f,win*carte){
  int fd,i,j;
  off_t fsize,cur;
  truc tmptruc;
  cellule*tmp;
  nbMonstre=0;
  nbArtefact=0;
  for(i=0;i<20;i++){
    for(j=0;j<40;j++){
      if(pthread_mutex_init(&map.tabM[i][j],NULL)!=0){
	perror("init_grille():pthread_mutex_init()\n");
	exit(EXIT_FAILURE);
	map.tab[i][j].c=' ';
	map.tab[i][j].color=WG;
      }
    }
  }
  if((fd=open(f,O_RDONLY))==-1){
    ncurses_stop();
    perror("init_grille:open()\n");
    exit(EXIT_FAILURE);
  }
  if((fsize=lseek(fd,0,SEEK_END))==-1){
    ncurses_stop();
    perror("init_grille():lseek()\n");
    exit(EXIT_FAILURE);
  }
  if(lseek(fd,0,SEEK_SET)==-1){
    ncurses_stop();
    perror("init_grille():lseek()\n");
    exit(EXIT_FAILURE);
  }
  if(read(fd,map.tab,sizeof(couple)*20*40)==-1){
    ncurses_stop();
    perror("init_grille:read()\n");
    exit(EXIT_FAILURE);
  }
  init_hashtable(&h);
  /*move((*carte).px+(*carte).h+3,(*carte).py);*/
  while((cur=lseek(fd,0,SEEK_CUR))!=fsize){
    if(read(fd,&tmptruc.diff,sizeof(unsigned short)+sizeof(unsigned char)+sizeof(caracteristique))==-1){
      destruct_hashtable(&h);
      ncurses_stop();
      perror("init_grille():read()\n");
      exit(EXIT_FAILURE);
    }
    if((tmp=(cellule*)malloc(sizeof(cellule)))==NULL){
      destruct_hashtable(&h);
      ncurses_stop();
      perror("init_grille():malloc()\n");
      exit(EXIT_FAILURE);
    }
    init_cellule(tmp);
    init_truc(&(*tmp).t,tmptruc.diff);
    (*tmp).t.size=tmptruc.size;
    init_caracteristique(&(*tmp).t.attr,tmptruc.attr.pv,tmptruc.attr.armure,tmptruc.attr.force,tmptruc.attr.vitesseDeplacement,tmptruc.attr.vitesseFrappe);
    inserer_hashtable(&h,tmp);
    if(read(fd,(*tmp).t.nom,(*tmp).t.size)==-1){
      destruct_hashtable(&h);
      ncurses_stop();
      perror("init_grille():read()");
      exit(EXIT_FAILURE);
    }
    /*
    printw("%hd %d %d\n",(*tmp).t.diff,(*tmp).t.diff/40,(*tmp).t.diff%40);
    refresh();*/    
    if(map.tab[(*tmp).t.diff/40][(*tmp).t.diff%40].c=='M'){
      nbMonstre++;
    }else if(map.tab[(*tmp).t.diff/40][(*tmp).t.diff%40].c=='A'){
      nbArtefact++;
    } 
  }
  if(close(fd)==-1){
    destruct_hashtable(&h);
    ncurses_stop();
    perror("init_grille:close()\n");
    exit(EXIT_FAILURE);
  }
  for(i=0;i<20;i++){
    for(j=0;j<40;j++){
      wattron((*carte).f,COLOR_PAIR(map.tab[i][j].color));
      mvwaddch((*carte).f,i+1,j+1,map.tab[i][j].c);
      wattroff((*carte).f,COLOR_PAIR(map.tab[i][j].color));
    }
  }
  wrefresh((*carte).f);
  mvprintw((*carte).px+(*carte).h+3,(*carte).py,"%d %d",nbMonstre,nbArtefact);
  refresh();
}
void destruct_grille(){
  int i,j;
  destruct_hashtable(&h);
  nbArtefact=0;
  nbMonstre=0;
  for(i=0;i<20;i++){
    for(j=0;j<20;j++){
      if(pthread_mutex_destroy(&map.tabM[i][j])!=0){
	ncurses_stop();
	perror("destruct_grille():pthread_mutex_destroy()\n");
	exit(EXIT_FAILURE);
      }
    }
  }
}
int main(int argc,char*args[]){
  int i,j;
  if(argc!=2){
    fprintf(stderr,"%s map/<nom de fichier>\n",args[0]);
    exit(EXIT_FAILURE);
  }
  ncurses_init(1);
  create_win(&carte,(LINES-1-22)/2,(COLS-1-42)/2,22,42);
  init_grille(args[1],&carte);
  while(getch()!='q'){
  }
  destruct_grille();
  destruct_win(&carte);
  ncurses_stop();
  for(i=0;i<20;i++){
    for(j=0;j<40;j++){
      printf("[%d,%c]",map.tab[i][j].color,map.tab[i][j].c);
    }
    printf("\n");
  }
  printf("\n");
  return EXIT_SUCCESS;
}
