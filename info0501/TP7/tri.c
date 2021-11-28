#include "tri.h"
#include "tas.h"

int TriInsertion(arete_t* t, int longueur){
    int i,j;
    arete_t cle;

    for ( j = 1; j < longueur; j++)
    {
        cle = t[j];
        i=j-1;
        while (i > -1 && t[i].poids > cle.poids)
        {
            t[i+1] = t[i];
            i = i -1;
        }
        t[i+1] = cle;
    }
    return 1;
}

int TriParTas(arete_t* t, int taille){
    int i, length = taille;
    arete_t a;
    ConstruireTasMax(t,length);
    for ( i = length-1; i >= 1; i--)
    {
        a = t[i];
        t[i] = t[0];
        t[0] = a;
        taille--;
        EntasserMax(t,taille,0);
    }
    return 1;
}