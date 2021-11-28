#ifndef PILE_SOMMET

#define PILE_SOMMET

#include "graphe.h"

typedef struct pile_type{
    sommet_t* stockage;
    int sommet;
    int size;
}pile_t;

int initialiser_pile(pile_t*, int);

int detruire_pile(pile_t*);

int pile_vide(pile_t*);

int pile_pleine(pile_t*);

sommet_t* sommet(pile_t*);

int empiler(pile_t* , sommet_t*);

sommet_t* depile(pile_t*);

#endif