#include "file.h"

int initialiser_file(file * f, int taille){
    f->queue=0;
    f->tete=0;
    f->taille= taille;
    f->tab=malloc(taille*sizeof(cellule*));
}

int detruire_file(file * f){
    free(f->tab);
    free(f);
}

int file_vide(file * f){
    return (f->tete==f->queue);
}

int file_pleine(file * f){

    return (f->queue == (f->tete-1%f->taille));
}

int enfiler(file * f, cellule *c){
    if(!file_pleine(f)){
        if(f->queue<f->taille){
            f->queue++;
        }else{
            f->queue=0;
        }
        f->tab[f->queue]=c;
    }
return 1;
}

cellule * defiler(file * f){
    if(!file_vide(f)){
        
    }
}

