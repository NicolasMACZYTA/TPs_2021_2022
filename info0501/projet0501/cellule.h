#ifndef CELLULE_H
#define CELLULE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule_t{
    int idSommet;
    struct cellule_t *succ;
    struct cellule_t *pred;
}cellule_t;

void initialiserCellule(cellule_t *c, int idSommet);


#endif