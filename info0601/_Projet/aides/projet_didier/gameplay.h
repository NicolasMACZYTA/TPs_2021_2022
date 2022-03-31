#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include<locale.h>
#include<ncurses.h>
#define WG 1
#define WY 2
#define WR 3
#define EAU 4
#define DG 5
#define DY 6
#define DR 7
#define DW 8
#define WD 9
typedef struct caracteristique{
  unsigned char pv;
  unsigned char armure;
  unsigned char force;
  unsigned char vitesseDeplacement;
  unsigned char vitesseFrappe;
}caracteristique;
typedef struct couple{
  char c;
  unsigned char color;
}couple;
typedef struct cases{
  char *name;
  couple id;
  caracteristique attr;
  unsigned char size;
}cases;
typedef struct win{
  WINDOW *f;
  unsigned char px;
  unsigned char py;
  unsigned char h;
  unsigned char l;
}win;
typedef struct button{
  couple img;
  char nom[12];
  unsigned char px;
  unsigned char py;
}button;
/*structure propre au projet , non general...*/
typedef struct editeur{
  win map;
  win info;
  win tool;
  couple pinceau;
  button ancre[8];
}editeur;
typedef struct truc{
  char nom[24];
  unsigned short diff;
  unsigned char size;
  caracteristique attr;
}truc;
typedef struct cellule{
  struct cellule* pres;
  struct cellule* succ;
  truc t;
}cellule;
typedef struct liste{
  cellule*tete;
}liste;
typedef struct hashtable{
  liste tab[20];
}hashtable;
/*fonction truc*/
void init_truc(truc*,unsigned short);
/*fonction cellule*/
void init_cellule(cellule*);
/*fonction liste*/
void init_liste(liste*);
void inserer_liste(liste*,cellule*);
void supprimer_liste(liste*,cellule*);
cellule* rechercher_liste(liste*,unsigned short);
void destruct_liste(liste*);
/*fonction hashtable*/
void init_hashtable(hashtable*);
void inserer_hashtable(hashtable*,cellule*);
cellule* rechercher_hashtable(hashtable*,unsigned short);
void supprimer_hashtable(hashtable*,cellule*);
void destruct_hashtable(hashtable*);
/*fonction ncurses*/
void ncurses_init(int);
void ncurses_stop();
/*fonction couple*/
void init_couple(couple*,unsigned char,char);
/*fonction button*/
void int_button(button*,unsigned char,unsigned char,unsigned char,char,char[12]);
/*fonction caracteristique*/
void init_caracteristique(caracteristique*,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char);
/*fonction win*/
void create_win(win*,unsigned char,unsigned char,unsigned char,unsigned char);
void destruct_win(win*);
/*fonction editeur*/
void create_editeur(editeur*);
void edit(editeur*,char*);
void destruct_editeur(editeur*);
#endif
