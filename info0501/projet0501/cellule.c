#include <stdlib.h>
#include "cellule.h"

int initialiser_cellule(cellule_t *c, int id_sommet){
    c->id_sommet = id_sommet;
    c->prec = NULL;
    c->suiv = NULL;

    return 1;
}

