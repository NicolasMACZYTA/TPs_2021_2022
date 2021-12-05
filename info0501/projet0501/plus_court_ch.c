#include "plus_court_ch.h"

void afficherChemin(graphe_t *g, sommet_t* s, sommet_t* v){
    if(v==s){
        printf("%d ",s->idSommet);
    }else{
        if(v->pere==NULL){
            printf("erreur : aucun chemin entre %d et %d",s->idSommet,v->idSommet);
        }else{
            afficherChemin(g,s,v->pere);
            printf("%d ",v->idSommet);
        }
    }
}


//BELLMAND-FORD
void sourceUniqueInitialisation(graphe_t *g, sommet_t *s){
    int i;
    for(i=0;i<g->nb_sommets;i++){
        g->tSommet[i].distance=9999999;
        g->tSommet[i].pere=NULL;
    }
    s->distance=0;
}

int bellmandFord(graphe_t *g, int** w, sommet_t *s){
    int i,j,k;
    sourceUniqueInitialisation(g,s);

    for(i=0; i<g->nb_sommets; i++){
        for(j=0; j<g->nb_aretes; j++){
            relacher(g->aretes[j].origine, g->aretes[j].fin,g->aretes[j].poids);
        }
    }
    
    for(k=0; k<g->nb_aretes;k++){
        if(g->aretes[k].fin->distance<g->aretes[k].origine->distance+g->aretes[k].poids){
            return 0;
        }
    }

    return 1;
}

sommet_t* extraireMinTab(sommet_t** t, int taille){
    sommet_t *temp;
    sommet_t *min;
    int iSommet,i;
    min=t[0];
    iSommet = 0;
        for(i=1; i<taille;i++){
        if(min->distance>t[i]->distance){
            min=t[i];
            iSommet = i;
        }
    }
    
    if(i!=taille-1){
        temp = t[taille-1];
        t[taille-1]=t[iSommet];
        t[iSommet]=temp;
        
    }
    
    return t[taille-1];
}
/*
void dijskstaTab(graphe_t *g,int** w, sommet_t *s){
    sommet_t **tab = malloc(sizeof(sommet_t*)*g->nb_sommets);
    sommet_t *u;
    sommet_t *v;
    liste_t l;
    sourceUniqueInitialisation(g,s);
    for(int i=0;i<g->nb_sommets;i++){
        tab[i]=&g->tSommet[i];
    }
    

    for(int i=0;i<g->nb_sommets;i++){
        u=extraireMinTab(tab,g->nb_sommets-i);
        l=g->listeAdjacences[u->idSommet-1];
        v=&g->tSommet[u->idSommet-1];
        do{
            if(u!=v){
                relacher(u,v,w);
            }
            
            l.tete=l.tete->succ;
            if(l.tete!=NULL){
                v=&g->tSommet[l.tete->idSommet-1];
            }
        }while(l.tete!=NULL);
    }
}
*/
ensemble_t* dijkstra(graphe_t* g, sommet_t* s){
    int i = 0;
    file_t* f;
    ensemble_t* e,*ensemble_final;
    ensemble_cell_t* cell_ens;
    sommet_t* u;
    cellule_t* cell;

    f = (file_t*)malloc(sizeof(file_t));
    initialiserFile(f,g->nb_sommets);
    e = (ensemble_t*)malloc(sizeof(ensemble_t)*g->nb_sommets);
    ensemble_final = (ensemble_t*)malloc(sizeof(ensemble_t));

    for ( i = 0; i < g->nb_sommets; i++)
    {
        e[i] = *creer_ensemble(&g->tSommet[i]);
        enfiler(f,&g->tSommet[i]);
    }
    
    sourceUniqueInitialisation(g,s);

    while(!fileVide(f)){
        u = defiler(f);
        if(ensemble_final->tete == NULL){
            ensemble_final = creer_ensemble(u);
        }
        union_ensemble(ensemble_final->tete,e[u->idSommet].tete);
        cell = g->listeAdjacences[u->idSommet].tete;
        while (cell != NULL){
            relacher(u,&g->tSommet[cell->id_sommet],cell->poids);
            cell = cell->suiv;
        }
    }

    return ensemble_final;
}

int bellman_ford(graphe_t* g, sommet_t* s){
    sourceUniqueInitialisation(g,s);
    int i,j,k;
    for ( i = 0; i < g->nb_sommets ; i++){
        for (j = 0; j < g->nb_aretes; j++){
            relacher(g->aretes[j].origine, g->aretes[j].fin, g->aretes[j].poids);
        }
    }
    for ( k = 0; k < g->nb_aretes; k++){
        if(g->aretes[k].fin->distance < g->aretes[k].origine->distance + g->aretes[k].poids){
            return 0;
        }
    }
    return 1;
}

int relacher(sommet_t* u, sommet_t* v, int poids){
    if(v->distance > (u->distance + poids) ){
        v->distance = u->distance + poids;
        v->pere = u;
    }
    return 1;
}

int afficher_pcc(graphe_t* g){
    int i;
    sommet_t* cell;

    for ( i = 0; i < g->nb_sommets; i++)
    {
        cell = &g->tSommet[i];
        while (cell)
        {
            printf("%d ->", cell->idSommet);
            cell = cell->pere;
        }
            printf("\n");
    }
    
    return 1;
}

