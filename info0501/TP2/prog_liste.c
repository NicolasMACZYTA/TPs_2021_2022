#include <stdio.h>
#include <stdlib.h>
#include "cellule.h"
#include "liste.h"
#include "graphe.h"
#include "file.h"

//main test pour graphes
int main(int argc, char *argv[]){
  graphe *g = malloc(sizeof(graphe));
  file *f = malloc(sizeof(file));
  cellule *c = malloc(sizeof(cellule));
  cellule *c2;
  initCellule(c,2);
  
  printf("\ninitialisation du graphe ...\n");
  initialiser_graphe(g,argv[1]);
  printf("initialisation du graphe ... terminé \n");

  printf("afficher graphe : \n");
  afficher_graphe(g);
  printf("fin de l'affichage du graphe\n");

  printf("détruction graphe ...\n");
  detruire_graphe(g);
  printf("fin de la destruction du graphe...\n");
  printf("Vérification de la destruction : \n");
  afficher_graphe(g);
  printf("initialisation file : \n");
  initialiser_file(f,10);
  printf("enfiler : \n");
  enfiler(f,c);
  printf("enfiler : \n");
  enfiler(f,c);
  printf("affichage tete : %d\n",f->tab[f->tete]->sommet);
  printf("defiler : \n");
  c2 = (cellule*)defiler(f);
  printf("valeur defilee %d : \n",c2->sommet);
  
  printf("FIN\n");
  c2 = (cellule*)defiler(f);
  printf("valeur defilee %d : \n",c2->sommet);
  c2=defiler(f);

  return 0;
}

