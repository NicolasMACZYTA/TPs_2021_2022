#include "pile.h"

int initialiser_pile(pile_t* p, int size){
    if(0 < size){
        p->stockage=(sommet_t*)malloc(sizeof(sommet_t) * size);
        p->size = size;
        p->sommet = -1;
        return 1;
    }
    else{
        return 0;
    }
}

int detruire_pile(pile_t* p){
    free(p->stockage);
    p->stockage = NULL;
    p->size = 0;
    return 1;
}

int pile_vide(pile_t* p){
    return p->sommet == -1;
}

int pile_pleine(pile_t* p){
    return p->sommet == p->size;
}

sommet_t* sommet(pile_t* p){
    return &p->stockage[p->sommet];
}

int empiler(pile_t* p, sommet_t* s){
    if (!pile_pleine(p)){
        p->sommet ++;
        p->stockage[(p->sommet)] = *s;

        return 1;
    }
    else{
        return 0;
    }
    
}

sommet_t* depile(pile_t* p){
    if(!pile_vide(p)){
        p->sommet --;
        return &p->stockage[p->sommet];
    }
    else{
        return 0;
    }
}