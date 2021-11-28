#include "ensemble.h"

ensemble_t* creer_ensemble(sommet_t* s){
    ensemble_t* res = (ensemble_t*)malloc(sizeof(ensemble_t));
    ensemble_cell_t* e1 = (ensemble_cell_t*)malloc(sizeof(ensemble_cell_t));
    e1->sommet = s;
    e1->ensemble = res;
    e1->succ = NULL;
    res->tete = e1;
    res->queue = e1;
    return res;
}

ensemble_t* trouver_ensemble(ensemble_cell_t* e){
    return e->ensemble;
}

ensemble_t* union_ensemble(ensemble_cell_t* x, ensemble_cell_t* y){
    ensemble_cell_t* z = y->ensemble->tete;
    x->ensemble->queue->succ = y->ensemble->tete;
    x->ensemble->queue = y->ensemble->queue;
    while(z != NULL){
        z->ensemble = x->ensemble;
        z = z->succ;
    }
}