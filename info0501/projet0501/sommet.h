#ifndef SOMMET_H
#define SOMMET_H
#include "cellule.h"
#include "COULEUR.h"


typedef struct sommet_t{
    cellule_t* cAsso;
    int idSommet;
    int distance;
    struct sommet_t *pere;
    COULEUR_T couleur;
    int debut;
    int fin;
}sommet_t;

#endif