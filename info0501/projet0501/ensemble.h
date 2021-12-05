#ifndef ENSEMBLES
#define ENSEMBLES

#include "sommet.h"
#include <stdlib.h>

typedef struct ensemble_cell_type
{
    sommet_t* sommet;
    struct ensemble_cell_type* succ;
    struct ensemble_type* ensemble;
}ensemble_cell_t;

typedef struct ensemble_type{
    ensemble_cell_t* tete;
    ensemble_cell_t* queue;
}ensemble_t;

ensemble_t* creer_ensemble(sommet_t*);

ensemble_t* trouver_ensemble(ensemble_cell_t*);

void union_ensemble(ensemble_cell_t*, ensemble_cell_t*);

int afficher_ensemble(ensemble_t* e);

#endif 