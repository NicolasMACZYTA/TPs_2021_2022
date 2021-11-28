#ifndef PLUS_COURT_CHEMIN
#define PLUS_COURT_CHEMIN

#include "graphe.h"

int source_unique_initialisation(graphe_t*, sommet_t*);

int bellman_ford(graphe_t*,sommet_t*);

int relacher(sommet_t*, sommet_t*,int);

ensemble_t* dijkstra(graphe_t*, sommet_t*);

int afficher_pcc(graphe_t* );
#endif // !PLUS_COURT_CHEMIN