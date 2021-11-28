#include "tas.h"

int parent(int i){
    return (i/2);
}

int gauche(int i){
    return (i*2 +1);
}

int droite(int i){
    return (i*2 +2);
}

int EntasserMax(arete_t* tab, int taille, int i){
    int g, d, max;
    arete_t arete;
    g = gauche(i);
    d = droite(i);
    
    if(g < taille && tab[g].poids > tab[i].poids){
        max = g;
    }else{
        max = i;
    }
    if(d < taille && tab[d].poids > tab[max].poids){
        max = d;
    }
    if(max != i){
        arete = tab[i];
        tab[i] = tab[max];
        tab[max] = arete;
        EntasserMax(tab,taille,max);
    }
    return 1;
}

int ConstruireTasMax(arete_t* t, int taille){
    int i;
    for ( i = taille/2; i >= 0; i--)    {
        EntasserMax(t,taille,i);
    }
    return 1;
}

int DetruireTas(arete_t* tas){
    free(tas);
    tas = NULL;
}
