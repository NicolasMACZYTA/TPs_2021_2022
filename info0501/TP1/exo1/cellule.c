#include "cellule.h"
#include <stdlib.h>

int initCellule(cellule *cell, int id_sommet){
    cell->sommet=id_sommet;
    cell->prec=NULL;
    cell->suiv=NULL;
}