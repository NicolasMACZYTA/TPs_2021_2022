#include <stdlib.h>
#include <stdio.h>

#include "liste.h"

int initialiser_liste(liste_t* liste){
    liste->tete = NULL;

    return 0;
}

int detruire_liste(liste_t* liste){
    while(liste->tete){
        supprimer(liste, &(liste->tete));
    }
    return 0;
}

int afficher_liste(liste_t* liste){
    cellule_t* c;
    if(liste){
        c = liste->tete;
        while(c){
            printf("%d ",c->id_sommet);
            c = c->suiv;
        }   

    }
    else{
        printf("Cette liste est vide");
    }
    printf("\n");
    return 0;
}

int inserer(liste_t* liste, cellule_t* c){
    c->suiv = liste->tete;
    if(liste->tete){
        liste->tete->prec = c;
    }
    liste->tete = c;
    c->prec = NULL;
    return 0;
}

cellule_t* rechercher(liste_t* liste, int val){
    cellule_t *c = liste->tete;
    while(c && c->id_sommet != val){
        c = c->suiv;
    }
    return c;
}

int supprimer(liste_t* liste, cellule_t** c){
    if((*c)->suiv){
        (*c)->suiv->prec = (*c)->prec;
    }
    
    if((*c)->prec){
        (*c)->prec->suiv = (*c)->suiv;
    }
    else{
        liste->tete = (*c)->suiv;
        if(liste->tete){
            liste->tete->prec = NULL;
        }
    }
    free(*c);
    *c = NULL;
    return 0;
}




