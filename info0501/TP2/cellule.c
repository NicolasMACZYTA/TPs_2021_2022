#include "cellule.h"

void initCellule(cellule *cell, int id_sommet){
    cell->sommet = id_sommet;
    cell->precedent = NULL;
    cell->successeur = NULL;
}
