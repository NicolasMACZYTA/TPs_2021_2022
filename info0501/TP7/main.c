#include "plus_court_chemin.h"

int main(int argc, char *argv[])
{
    graphe_t* g;
    ensemble_t* ensemble;
    g = (graphe_t*)malloc(sizeof(graphe_t));
    initialiser_graphe(g, argv[1]);

    bellman_ford(g,&g->sommets[0]);
    printf("Belman-ford chemin de chaque sommet:\n");
    afficher_pcc(g);
    ensemble = dijkstra(g,&g->sommets[0]);
    printf("\nEnsemble de Dijkstra:\n");

    afficher_acpm_ensemble(ensemble);
    
    return 0;
}
