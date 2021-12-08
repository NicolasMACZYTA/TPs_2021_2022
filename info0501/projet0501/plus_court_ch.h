#ifndef PLUS_COURT_CH_H
#define PLUS_COURT_CH_H
#include "graphe.h"
#include "file.h"
#include "ensemble.h"
#include <limits.h>

void afficherChemin(graphe_t *g, sommet_t* s, sommet_t* v);
void sourceUniqueInitialisation(graphe_t *g, sommet_t *s);
int relacher(sommet_t* u, sommet_t* v, int poids);
int bellmandFord(graphe_t *g, int** w, sommet_t *s);
sommet_t* extraireMinTab(sommet_t** t, int taille);
ensemble_t* dijkstra(graphe_t* g, sommet_t* s);
int bellman_ford(graphe_t* g, sommet_t* s);
int afficher_pcc(graphe_t* g);

#endif