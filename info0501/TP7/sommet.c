#include "sommet.h"
#include <stdlib.h>

int initialiser_sommet(sommet_t* s, int id){
    s->id_sommet = id;
    s->couleur = BLANC;
    s->distance = INF;
    s->pere = NULL;
    s->date_d = 0;
    s->date_f = INF;

    return 1;
}