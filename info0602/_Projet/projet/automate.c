#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automate.h"

int init_automate(automate_t* a, char *type) {
    strcpy(a->type,"");
    strcpy(a->nodeStart,"");
    strcpy(a->nodeEnd,"");
    strcpy(a->alphabet,"");
    a->liens->nbLiens=0;
    a->nbNodes=0;

    return 0;
}

cellule_t *initialiser_cellule(char chaine){
    cellule_t *c = malloc(sizeof(cellule_t));
    if(c != NULL){
        strcpy(c->lien,chaine);
        c->succ = NULL;
        c->pred = NULL;
    }

    return c;
}

int initialiser_liste(liste_t* l){
    l->head = NULL;
    l->nbLiens = 0;

    return 0;
}

void detruire_liste(liste_t* l){
    while(l->head != NULL){
        supprimer(l, l->head);
    }
}

void insere(liste_t* l, cellule_t* c){
    c->succ = l->head;
    if(l->head != NULL){
        l->head->pred = c;
    }
    l->head = c;
    c->pred = NULL;
}

void afficher_liste(liste_t* l){
    if (l == NULL){
        printf("Liste non existante\n");
        exit(0);
    }else if (l->head == NULL){
        printf("Liste vide.\n");
        exit(0);
    }

    cellule_t* current = l->head;
    while(current != NULL){
        printf("%s \n", current->lien);
        current=current->succ;
    }
    printf("\n");
    printf("Il y a %d liens.\n\n",l->nbLiens);
}

void supprimer(liste_t* l, cellule_t* c){
    if(c->pred != NULL){
        c->pred->succ = c->succ;
    }else{
        l->head = c->succ;
    }
    if(c->succ != NULL){
        c->succ->pred = c->pred;
    }
}

int ajout_lien(liste_t* l, char chaine){
    if (!l->head) {
        l->head = initialiser_cellule(chaine);
        l->nbLiens = 1;
        return 0;
    }

    cellule_t* temp = l->head;
    while(temp->succ != NULL){
        if(strcmp(temp->lien, chaine) == 0){
            return 0;
        }else{
            temp = temp->succ;
        }
    }

    cellule_t* nMot = initialiser_cellule(chaine);
    insere(l, nMot);
    l->nbLiens++;

    return 0;
}

cellule_t *rechercherlien(liste_t *l, char *mot){
    cellule_t *x;
    x = l->head;
    while(x != NULL && x->lien != mot){
        x = x->succ;
    }

    return x;
}