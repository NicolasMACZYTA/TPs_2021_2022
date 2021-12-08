#ifndef FILE_t

#define FILE_t

#include "graphe.h"

#include <stdlib.h>

typedef struct file_type{
    sommet_t* stockage;
    int tete;
    int queue;
    int size;
}file_t;


int initialiser_file(file_t** f, int taille);

int detruire_file(file_t* f);

int file_vide(file_t* f);

int file_pleine(file_t* f);

int enfiler(file_t* f, sommet_t* s);

sommet_t* defiler(file_t* f);

void afficher_file(file_t* f);

sommet_t* extraire_min(file_t* f);
#endif