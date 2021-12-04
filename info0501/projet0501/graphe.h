#ifndef GRAPHE_H
#define GRAPHE_H
#include "liste.h"
#include "sommet.h"

typedef struct arete_t{
    int poids;
    sommet_t* origine;
    sommet_t* fin;
}arete_t;

typedef struct graphe_t{

    int nb_sommets;
    int orienter;
    int valuer;
    int nb_aretes;
    int* m_stockage;
    int* distance;
    int** matriceAdjacence;
    liste_t* listeAdjacences;
	sommet_t* tSommet;
    arete_t* aretes;


}graphe_t;

void initialiserGraphe(graphe_t *g, char* nomFichier);
void afficherGraphe(graphe_t *g);
void detruireGraphe(graphe_t *g);

#endif