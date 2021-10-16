#include "file.h"
#include <stdlib.h>

int initialiser_file(file * f, int taille){
    f->queue=0;
    f->tete=0;
    f->taille= taille;
    f->tab=malloc(taille*sizeof(cellule*));
    return 1;
}

int detruire_file(file * f){
    free(f->tab);
    free(f);
    return 1;
}

int file_vide(file * f){
    return (f->tete==f->queue);
}

int file_pleine(file * f){

    return (f->queue == (f->tete-1%f->taille));
}

int enfiler(file * f, cellule *c){
    if(!file_pleine(f)){
        
        f->tab[f->queue]=c;
        if(f->queue<f->taille){
            f->queue++;
        }else{
            f->queue=0;
        }
    }
return 1;
}

cellule * defiler(file * f){
    cellule * res;
    if(f==NULL){
        return NULL;
    }
    if(!file_vide(f)){
        res = f->tab[f->tete];
        f->tete++;
        if(f->tete==f->taille){
            f->tete=0;
        }
    }
    else{
        printf("la file est vide \n");
    }
    return res;
}

