#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"
#include "cellule.h"

#define MAX 27

void initialiser_liste(Liste *l){
    l->tete = NULL;
    l->precedant = NULL;
    l->taille = 0;
}

void initialiser_liste_fichier(Liste *l, char* nomFichier){
    initialiser_liste(l);
    FILE* f = NULL;
    char chaine[MAX] = "";

    f = fopen(nomFichier, "r+");
    if(f == NULL){
        printf("[ERREUR] Impossible d'ouvrir le fichier.");
        return;
    }

    fscanf(f, "%s", chaine);

    while(strcmp(chaine, "FIN_FICHIER") != 0){
        if(strlen(chaine) < MAX){
            Cellule *c = malloc(sizeof(Cellule));
            initCellule(c, chaine);
            inserer(l, c);
            l->taille = l->taille + 1; 
        }
        fscanf(f, "%s", chaine);
    }
    fclose(f);
}

void inserer(Liste *l, Cellule *c){
    if(l->taille == 0){
        c->successeur = l->tete;
        if(l->tete != NULL){
            l->tete->precedant = c;
        }
        l->tete = c;
        c->precedant = NULL;
        l->taille = l->taille + 1;
        printf("\tPremiere insertion dans la liste avec le mot : %s.\n", c->chaine);
    }
    else{
            c->successeur = l->tete;
            if(l->tete != NULL){
                l->tete->precedant = c;
            }
            l->tete = c;
            c->precedant = NULL;
            l->taille = l->taille + 1;
    }
    printf("Liste : \t");
    afficher_liste(l);
}

void afficher_liste(Liste *l){
    Cellule *c = malloc(sizeof(Cellule));
    if(l->tete!=NULL){
        c = l->tete;
        while(c!=NULL){
            printf(" %s" ,c->chaine);
            c = c->successeur;
        }
    }
    else{
        printf("Erreur ! La liste que vous essayez d'afficher est vide\n");
    }
    printf("\n");
}

Cellule* rechercher(Liste *l, char chaine[27]){
    Cellule *c = malloc(sizeof(Cellule));
    int numeroCellule = -1;
    

    if(l->tete != NULL){
        c = l->tete;
        numeroCellule = 0;
        while ((c != NULL) && (strcmp(c->chaine, chaine))) 
        {
            printf("\n\tCellule recherchée : %s ; \n\tCellule de tête : %s\n", chaine, c->chaine);
            numeroCellule = numeroCellule + 1;
            c = c->successeur;
        }
        numeroCellule = numeroCellule + 1;
    }
    else{
        char chaineNULL[] = "null";
        Cellule *cNULL = malloc(sizeof(Cellule));
        initCellule(cNULL, chaineNULL);
    }
    printf("numéro de la cellule de la recherche : %d\n", numeroCellule);
    return c;
}

void supprimer(Liste *l, char chaine[27]){
    Cellule *cell = malloc(sizeof(Cellule));
    cell = rechercher(l, chaine);
    if(cell == NULL){
        char chaineNULL[] = "null";
        Cellule *cNULL = malloc(sizeof(Cellule));
        initCellule(cNULL, chaineNULL);
        cell = cNULL;
    }
    printf("\nChaine a supprimer : \t%s\n", chaine);
    printf("\nChaine trouvée : \t%s\n", cell->chaine);

    if(strcmp(cell->chaine, chaine) == 0){
        cell->precedant->successeur = cell->successeur;
        cell->successeur->precedant = cell->precedant;
        cell->precedant = NULL;
        cell->successeur = NULL;
        l->taille = l->taille - 1;
        printf("Cellule supprimee\n");
    }
    else
    {
        printf("Le mot \"%s\" n'est pas dans la liste.\n", chaine);
    }
}