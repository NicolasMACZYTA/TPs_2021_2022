#ifndef AUTOMATE_H
#define AUTOMATE_H

typedef struct cellule_type{
    char lien[20];
    struct cellule_type *pred;
    struct cellule_type *succ;
}cellule_t;

typedef struct liste_type{
    cellule_t *head;
    int nbLiens;
}liste_t;

typedef struct automate_type{
    char nodeStart[10];
    char nodeEnd[50];
    char alphabet[50];
    char type[6];
    struct liste_type *liens;
    int nbNodes;
}automate_t;

int init_automate(automate_t *a, char *t);

cellule_t *initialiser_cellule(char chaine);

int initialiser_liste(liste_t* l);
void detruire_liste(liste_t* l);
void insere(liste_t* l, cellule_t* c);
void afficher_liste(liste_t* l);
void supprimer(liste_t* l, cellule_t* c);
cellule_t *rechercherlien(liste_t *l, char *mot);
int ajout_lien(liste_t *l, char chaine);

#endif /* AUTOMATE_H */