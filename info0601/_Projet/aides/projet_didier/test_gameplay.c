#include"gameplay.h"
#include<stdio.h>
#include<stdlib.h>
#define LONGEUR 20
#define HAUTEUR 40
cases grille[LONGEUR][HAUTEUR];
int main(int argv,char*args[]){
  editeur e;
  int i,j;
  if(argv!=2){
    fprintf(stderr,"%s <nom de fichier>\n",args[0]);
    exit(EXIT_FAILURE);
  }
  for(i=0;i<LONGEUR;i++){
    for(j=0;j<HAUTEUR;j++){
      init_couple(&grille[i][j].id,WG,' ');
      init_caracteristique(&grille[i][j].attr,0,0,0,0,0);
      grille[i][j].size=0;
      grille[i][j].name=NULL;
    }
  }
  printf("sizeof(caracteristique)=%ld\nsizeof(couple)=%ld\nsizeof(cases)=%ld\nsizeof(unsigned char)=%ld\nsizeof(chtype)=%ld\nsizeof(char*)=%ld\nsizeof(win)=%ld\nsizeof(truc)=%ld\nsizeof(unsigned short)=%ld\n",sizeof(caracteristique),sizeof(couple),sizeof(cases),sizeof(unsigned char),sizeof(chtype),sizeof(char*),sizeof(win),sizeof(truc),sizeof(unsigned short));
  printf("40*20*sizeof(couple)=%ld\n",40*20*sizeof(couple));
  printf("sizeof(cellule)=%ld\n",sizeof(cellule));
  ncurses_init(0);
  create_editeur(&e);
  edit(&e,args[1]);
  destruct_editeur(&e);
  ncurses_stop();
  exit(EXIT_SUCCESS);
}
