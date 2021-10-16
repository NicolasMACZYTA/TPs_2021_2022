#ifndef CELLULE_H
#define CELLULE_H

#include <stdio.h>

typedef struct cellule cellule;
struct cellule
{
    int sommet;
    char couleur;
    cellule *precedent;
    cellule *successeur;
};

void initCellule(cellule *cell, int id_sommet);

#endif //CELLULE_H