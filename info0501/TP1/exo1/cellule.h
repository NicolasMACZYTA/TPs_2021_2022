#ifndef CELLULE_H
#define CELLULE_H


typedef struct cellule{
    int sommet;
    cellule* suiv;
    cellule* prec;
}cellule;

int initCellule(cellule *cell, int id_sommet);

#endif