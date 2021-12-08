#include "file.h"
#include "sommet.h"

#include <stdio.h>

int initialiser_file(file_t** f, int taille){
    *f = (file_t*)malloc(sizeof(file_t));
    (*f)->stockage = (sommet_t*)malloc(sizeof(sommet_t)*(taille+1));
    (*f)->size = taille;
    (*f)->tete = 0;
    (*f)->queue = 0;
    return 1;
}

int detruire_file(file_t* f){
    free(f->stockage);
    f->size = 0;
    f->tete = 0;
    f->queue = 0;
    return 1;
}

int file_vide(file_t* f){
    if(f->tete == f->queue){
        return 1;
    }
    else{
        return 0;
    }
}

int file_pleine(file_t* f){
    if(f->queue == (f->size)-1){
        if(f->tete == 0){
            return 1;
        }else
        {
            return 0;
        }
    }
    else{
        if(f->queue + 1 == f->tete){
            return 1;
        }else{
            return 0;
        }
    }
}

int enfiler(file_t *f, sommet_t *s){
    if(!file_pleine(f)){
        f->stockage[f->queue] = *s;
        if(f->queue == f->size-1){
            f->queue = 0;
        }
        else{
            f->queue = f->queue +1;
        }
        return 1;
    }
    else{
        return 0;
    }
}

sommet_t* defiler(file_t *f){
    if(!file_vide(f)){
        sommet_t* res = &f->stockage[f->tete];
        
        if(f->tete == f->size - 1){
            f->tete = 0;
        }
        else{
            f->tete = f->tete + 1;
        }
        return res;
    }
    else{
        return NULL;
    }

}
void afficher_file(file_t* f){
    int tmp = f->tete;
    while (tmp != f->queue)
    {
        printf("%d ", f->stockage[tmp].idSommet );
        if(tmp == f->size - 1){
            tmp = 0;
        }else{
            tmp++;
        }
    }
    printf("\n");
}
sommet_t* extraire_min(file_t* f){
    int i = 0,j;
    sommet_t* res = &f->stockage[i];
    for(i = 0; i< f->size; i++){
        if(&f->stockage[i] != NULL && f->stockage[i].idSommet < res->idSommet){
            res = &f->stockage[i];
            j=i;
        }
    }
    initialiser_sommet(&f->stockage[j],9999);
    return res;
}