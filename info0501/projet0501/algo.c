#include "algo.h"

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
    sommet_t *v;
    for(int i=0;i<g->nb_sommets;i++){
        v=&g->tSommet[i];
        v->distance=999999999;
        v->pere=NULL;
    }
    s->distance=0;
}

void relacher(sommet_t *u, sommet_t *v, int** w){
    if(v->distance > u->distance+w[u->idSommet-1][v->idSommet-1]){
        v->distance=u->distance+w[u->idSommet-1][v->idSommet-1];
        v->pere=u;
    }
}

int bellmandFord(graphe_t *g, int** w, sommet_t *s){
    sommet_t *u;
    sommet_t *v;
    sourceUniqueInitialisation(g,s);
    for(int i=0; i<g->nb_sommets-1;i++){
        for(int j=0;j<g->nb_sommets;j++){
            for(int k=0;k<g->nb_sommets;k++){
                if(j!=k && w[j][k]!=0){
                    u=&g->tSommet[j];
                    v=&g->tSommet[k];
                    relacher(u,v,w);
                }
            }
        }
    }
    for(int i=0;i<g->nb_sommets;i++){
        for(int j=0;j<g->nb_sommets;j++){
            if(i!=j && w[i][j]!=0){
                u=&g->tSommet[i];
                v=&g->tSommet[j];
                if(v->distance > u->distance+w[u->idSommet-1][v->idSommet-1]){
                    return 0;
                }
            }
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


