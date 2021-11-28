#ifndef GRAPHE
#define GRAPHE

#include "liste.h"
#include "ensemble.h"
#include <stdlib.h>
#include <stdio.h>
#include "sommet.h"
#include "file.h"

typedef struct arete_type{
    int poids;
    sommet_t* origin;
    sommet_t* end;
}arete_t;

typedef struct graphe_t{
    int n_sommets;
    int oriente;
    int value;
    liste_t *l_adj;
    int **m_adj;
    int *m_stockage;
    sommet_t* sommets;
    arete_t* aretes;
    int nbAretes;
    int* distance;
}graphe_t;

int initialiser_arete(arete_t*, sommet_t*, sommet_t*, int);

int initialiser_graphe(graphe_t*, char *);

void afficher_graphe(graphe_t*);

int detruire_graphe(graphe_t*);

int parcours_largeur(graphe_t*, sommet_t*);

int afficher_chemin(graphe_t*, sommet_t*, sommet_t*);

int visiter_pp(graphe_t*, sommet_t*, int*);

int parcours_profondeur_recursif(graphe_t*);

int afficher_parcours_profondeur(graphe_t*);

int parcours_profondeur_iteratif(graphe_t*);

arete_t* generer_acpm_kruskal_tableau(graphe_t*);

ensemble_t* generer_acpm_kruskal_ensembles(graphe_t*);

int min(int*, int*, int);

int generer_acpm_prim_tableau(graphe_t*, int);

int generer_acpm_prim_file(graphe_t*, sommet_t*);

int afficher_acpm(graphe_t*);

int afficher_acpm_ensemble(ensemble_t* e);

int afficher_acpm_prim_tableau(graphe_t*);
#endif