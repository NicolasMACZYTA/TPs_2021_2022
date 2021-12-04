#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include "file.h"
#include "algo.h"


int main(int argc, char* argv[]){
    graphe_t g;
    int val,algo;
    char* nomFichier;
    printf("10 000 = %d\n",10000);
    initialiserGraphe(&g,argv[1]);
    printf("graphe initialiser\n");
    printf("De quel sommet voulez-vous voir le plus court chemin ? : ");
    scanf("%d",&val);

    /*
    if(bellmandFord(&g,g.matriceAdjacence,&g.tSommet[val-1])){
        printf("bellmand-ford:\n");
        for(int i=0;i<g.nb_sommets;i++){
           afficherChemin(&g,&g.tSommet[val-1],&g.tSommet[i]);
           printf("\n\n");
        }
    }else{
        printf("ca marche pas :(\n");
    }*/


    dijskstaTab(&g,g.matriceAdjacence,&g.tSommet[val-1]);
    printf("DIJSKTRA TABLEAU\n");
    for(int i=0;i<g.nb_sommets;i++){
        afficherChemin(&g,&g.tSommet[val-1],&g.tSommet[i]);
        printf("\n\n");
    }
    return 0;
}


