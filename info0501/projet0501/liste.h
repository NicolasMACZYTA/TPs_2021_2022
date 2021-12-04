#ifndef LISTE_H
#define LISTE_H
#include "cellule.h"

typedef struct liste_t{
    cellule_t* tete;
}liste_t;

void initialiserListe(liste_t *l);
void detruireListe(liste_t *l);
void insererListe(liste_t *l, cellule_t *c);
void afficherListe(liste_t *l);
cellule_t* rechercher(liste_t *l, int sommet);
void supprimerListe(liste_t *l, cellule_t *c);


#endif