#ifndef CELLULE
#define CELLULE

typedef struct cellule_type{
    int id_sommet;
    int poids;
    struct cellule_type *suiv;
    struct cellule_type *prec;
}cellule_t;

int initialiser_cellule(cellule_t *c, int id_sommet);

#endif