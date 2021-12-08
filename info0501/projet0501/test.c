#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include "file.h"
#include "plus_court_ch.h"


int main(int argc, char* argv[]){
    graphe_t *g;
    ensemble_t *ensemble;
    int val,val2;
    int i;
    g = malloc(sizeof(graphe_t));
    //ensemble = malloc(sizeof(ensemble_t*));
    printf("10 000 = %d\n",10000);
    initialiserGraphe(g,argv[1]);

    printf("graphe initialiser\n");
    afficherGraphe(g);
    /*
    printf("De quel sommet voulez-vous voir le plus court chemin ? : ");
    scanf("%d",&val);
    printf("deuxieme sommet ? : ");
    scanf("%d",&val2);
    */

    //bellman_ford(g,&g->tSommet[0]);
    

    //afficher_pcc(g);
    //afficherGraphe(g);


    bellman_ford(g,&g->tSommet[0]);
    afficher_pcc(g);
    //dijskstaTab(&g,g.matriceAdjacence,&g.tSommet[val-1]);
    
    /*for(i=0;i<g.nb_sommets;i++){
        afficherChemin(&g,&g.tSommet[val-1],&g.tSommet[i]);
        printf("\n\n");
    }*/
    //afficherChemin(g,&g->tSommet[val],&g->tSommet[val2]);

    ensemble = dijkstra(g,&g->tSommet[0]);

    printf("dijkstra :\n");
    //afficher_ensemble(ensemble);



    return 0;
}


