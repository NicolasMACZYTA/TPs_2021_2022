#ifndef SOMMET_H
#define SOMMET_H

#define INF 999

typedef enum couleur_type{BLANC, GRIS, NOIR}couleur_t;

typedef struct sommet_t{
    int id_sommet;
    couleur_t couleur;
    struct sommet_t* pere;
    int date_d;
    int date_f;
    int distance;
    int cle;
}sommet_t;

int initialiser_sommet(sommet_t* s, int id);

#endif // !SOMMET_H