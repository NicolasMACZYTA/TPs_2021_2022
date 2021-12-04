#ifndef FILE_H
#define FILE_H
#include "sommet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    typedef struct file_t{
        sommet_t** tab;
        int queue;
        int tete;
        int taille;
    }file_t;

    void initialiserFile(file_t* f,int capacite);
    void detruireFile(file_t* f);
    int filePleine(file_t *f);
    int fileVide(file_t *f);
    void enfiler(file_t *f, sommet_t *s);
    sommet_t* defiler(file_t *f);


#endif