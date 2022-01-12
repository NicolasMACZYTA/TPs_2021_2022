#include "pile.h"
#include <stdio.h>
#include <stdlib.h>

pile* initialiser(int taille){
    pile *p = malloc(sizeof(pile));
    p->pos=-1;
    p->size=taille;
    p->tab=malloc(taille*sizeof(int));
    return p;
}
int pile_vide(pile*p){
    if(p->pos==-1){
        return 1;
    }else{
        return 0;
    }
}
int pile_pleine(pile*p){
    if(p->pos==p->size-1){
        return 1;
    }else{
        return 0;
    }
}
void empiler(pile*p,int value){
    if(pile_pleine(p)){
        printf("impossible d'empiler, pile pleine !\n");
    }else{
        p->pos++;
        p->tab[p->pos]=value;
    }
}
int depiler(pile*p){
    if(pile_vide(p)){
        printf("impossible de dépiler, pile vide !\n");
    }else{
        p->pos--;
        return p->tab[p->pos+1];
    }
}

void afficher_pile(pile*p){
    int i;
    
    printf("affichage pile:\n");
    if(pile_vide){
        printf("pile vide.\n");
    }else{
        for(i=0;i<p->pos;i++){
        printf("%d\n",p->tab[i]);
    }
    }
}

void vider_pile(pile*p){
    p->pos= -1;
}