#ifndef LISTE
#define LISTE
#include "cellule.h"

typedef struct liste_type{
    cellule_t *tete;
}liste_t;

int initialiser_liste(liste_t*);

int detruire_liste(liste_t*);

int afficher_liste(liste_t*);

int inserer(liste_t*, cellule_t*);

cellule_t* rechercher(liste_t*, int);

int supprimer(liste_t*, cellule_t**);


#endif