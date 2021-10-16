#ifndef FILE_H
#define FILE_H

#include "cellule.h"

typedef struct file{
    int tete;
    int queue;
    int taille;
    cellule ** tab;
}file;

int initialiser_file(file * f, int taille);
int detruire_file(file * f);
int file_vide(file * f);
int file_pleine(file * f);
int enfiler(file * f, cellule *c);
cellule * defiler(file * f);

#endif