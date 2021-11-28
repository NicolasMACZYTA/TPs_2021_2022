#include "plus_court_chemin.h"

int source_unique_initialisation(graphe_t* g, sommet_t* s){
    int i = 0;

    for ( i = 0; i < g->n_sommets; i++){
        g->sommets[i].distance = 9999;
        g->sommets[i].pere = NULL;
    }
    s->distance = 0;
}

int bellman_ford(graphe_t* g, sommet_t* s){
    source_unique_initialisation(g,s);
    int i,j,k;
    for ( i = 0; i < g->n_sommets ; i++){
        for (j = 0; j < g->nbAretes; j++){
            relacher(g->aretes[j].origin, g->aretes[j].end, g->aretes[j].poids);
        }
    }
    for ( k = 0; k < g->nbAretes; k++){
        if(g->aretes[k].end->distance < g->aretes[k].origin->distance + g->aretes[k].poids){
            return 0;
        }
    }
    return 1;
}

int relacher(sommet_t* u, sommet_t* v, int poids){
    if(v->distance > (u->distance + poids) ){
        v->distance = u->distance + poids;
        v->pere = u;
    }
    return 1;
}

ensemble_t* dijkstra(graphe_t* g, sommet_t* s){
    int i = 0;
    file_t* f;
    ensemble_t* e,*ensemble_final;
    ensemble_cell_t* cell_ens;
    sommet_t* u;
    cellule_t* cell;

    f = (file_t*)malloc(sizeof(file_t));
    initialiser_file(&f,g->n_sommets);
    e = (ensemble_t*)malloc(sizeof(ensemble_t)*g->n_sommets);
    ensemble_final = (ensemble_t*)malloc(sizeof(ensemble_t));

    for ( i = 0; i < g->n_sommets; i++)
    {
        e[i] = *creer_ensemble(&g->sommets[i]);
        enfiler(f,&g->sommets[i]);
    }
    
    source_unique_initialisation(g,s);

    while(!file_vide(f)){
        u = defiler(f);
        if(ensemble_final->tete == NULL){
            ensemble_final = creer_ensemble(u);
        }
        union_ensemble(ensemble_final->tete,e[u->id_sommet].tete);
        cell = g->l_adj[u->id_sommet].tete;
        while (cell != NULL){
            relacher(u,&g->sommets[cell->id_sommet],cell->poids);
            cell = cell->suiv;
        }
    }

    return ensemble_final;
}

int afficher_pcc(graphe_t* g){
    int i;
    sommet_t* cell;

    for ( i = 0; i < g->n_sommets; i++)
    {
        cell = &g->sommets[i];
        while (cell)
        {
            printf("%d ->", cell->id_sommet);
            cell = cell->pere;
        }
            printf("\n");
    }
    
    return 1;
}