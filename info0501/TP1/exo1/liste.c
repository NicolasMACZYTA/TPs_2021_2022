#include "liste.h"
#include <stdlib.h>

liste * initialiser_liste(){
    liste * l=(liste*)malloc(sizeof(liste));
    l->tete=NULL;
    return l;
}

int detruire_liste(liste* l){
    cellule * cell= l->tete;
    while(cell->suiv!=NULL){

    }
}

int inserer(liste* l,cellule* c){
    cellule * cell=l->tete;
    while(cell->suiv!=NULL){
        cell=cell->suiv;
    }
    cell->suiv=c;
}

cellule * rechercher(liste*l, int val){
    cellule * cell=l->tete;
    if(l->tete!=NULL){
    cell = l->tete;
    while((cell != NULL) && (cell->sommet != val)){
      cell = cell->suiv;
    }
  }
  return cell;
}

int supprimer(cellule * cell){

}