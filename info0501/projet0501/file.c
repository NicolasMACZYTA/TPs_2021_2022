#include "file.h"

void initialiserFile(file_t* f,int capacite){
    if(capacite != -1){
        f->taille=capacite;
    }
    f->tab=malloc(sizeof(sommet_t*)*f->taille);
    for(int i=0;i<f->taille;i++){
        f->tab[i]=malloc(sizeof(sommet_t));
        f->tab[i]->idSommet=-1;
        f->tab[i]->cAsso=NULL;
    }
    f->tete=0;
    f->queue=0;
}

void detruireFile(file_t *f){
    for(int i=0;i<f->taille;i++){
        f->tab[i]->cAsso=NULL;
        f->tab[i]->pere=NULL;
        f->tab[i]->idSommet=-1;
    }
}

int filePleine(file_t *f){
    int toRet = 0;
    if(f->queue==f->taille-1){
        toRet = 1;
    }
    return toRet;
}
int fileVide(file_t *f){
    int toRet =0;
    if(f->queue==f->tete){
        toRet = 1;
    }
    return toRet;
}

void enfiler(file_t *f,sommet_t *s){
    f->tab[f->queue]=s;
    if(f->queue==f->taille-1){
        f->queue=0;
    }else{
        f->queue++;
    }
}

sommet_t* defiler(file_t *f){
    sommet_t *s=f->tab[f->tete];
    if(f->tete==f->taille-1){
        f->tete=0;
    }else{
        f->tete++;
    }
    return s;

}