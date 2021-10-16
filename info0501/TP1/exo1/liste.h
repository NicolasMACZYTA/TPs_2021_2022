#ifndef LISTE_H
#define LISTE_H

#include "cellule.h"

typedef struct liste{
    cellule* tete;
}liste;

liste * initialiser_liste();
int detruire_liste(liste* l);
int inserer(liste*l,cellule* c);
cellule * rechercher(liste*l, int val);
int supprimer(cellule * cell);

#endif