#ifndef ALGO_H
#define ALGO_H
#include "graphe.h"
#include "file.h"
#include <limits.h>

void afficherChemin(graphe_t *g, sommet_t* s, sommet_t* v);
void sourceUniqueInitialisation(graphe_t *g, sommet_t *s);
void relacher(sommet_t *u, sommet_t *v, int** w);
int bellmandFord(graphe_t *g, int** w, sommet_t *s);
sommet_t* extraireMinTab(sommet_t** t, int taille);
void dijskstaTab(graphe_t *g,int** w, sommet_t *s);

#endif