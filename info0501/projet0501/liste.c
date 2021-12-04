#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

void initialiserListe(liste_t *l){
    l->tete=NULL;
}

void detruireListe(liste_t* l){
    if(l->tete!=NULL){
        while(l->tete!=NULL){
            if(l->tete->succ != NULL){
                l->tete=l->tete->succ;
                l->tete->pred=NULL;
            }else{
                l->tete=NULL;
            }
        }
    }
    
}

void insererListe(liste_t *l, cellule_t *c){
   c->succ=l->tete;
	if(l->tete!=NULL){
		l->tete->pred=c;
	}
	c->pred = NULL;
	l->tete = c;
}

void afficherListe(liste_t *l){
    cellule_t *c;
    if(l->tete==NULL){
        printf("Liste Vide\n");
    }else{
        c=malloc(sizeof(cellule_t));
        c=l->tete;
        while(c!=NULL){
            printf("%d ",c->idSommet);
            c=c->succ;
        }
        printf("\n");
        free(c);
    }
}

cellule_t* rechercher(liste_t *l, int sommet){
    cellule_t *c=l->tete;
    while( (c->idSommet != sommet) && (c->succ != NULL) ){
		c=c->succ;
	}
	if(c->idSommet != sommet){
		c = NULL;
	}
    return c;
}

void supprimerListe(liste_t *l, cellule_t *c){
    if(c->pred!=NULL){
		c->pred->succ = c->succ;
	}else{
		l->tete=c->succ;
	}
	if(c->succ != NULL){
		c->succ->pred=c->pred;
	}
}