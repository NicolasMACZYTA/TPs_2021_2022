#ifndef TAS_H
#define TAS_H
#include "graphe.h"

int parent(int);

int gauche(int);

int droite(int);

int EntasserMax(arete_t*, int, int);

int ConstruireTasMax(arete_t*, int);

int DetruireTasMax(arete_t*);
#endif // !TAS_H