
#include "graphe.h"
#include "liste.h"
#include "file.h"
#include "pile.h"
#include "tri.h"
#include "file_priorites_min.h"
#include "ensemble.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int initialiser_arete(arete_t* a, sommet_t* origin, sommet_t* end, int poids){
    a->origin = origin;
    a->end = end;
    a->poids = poids;

    return 1;
}

int initialiser_graphe(graphe_t* g, char* filename){
    FILE *fichier;
    char buffer[20];
    int i, j, k=0, areteCpt = 0;
    
    if(g != NULL && (fichier = fopen(filename,"r")) ){

        fscanf(fichier,"%s",buffer);
        fscanf(fichier, "%d", &g->n_sommets);
        g->sommets = (sommet_t*)malloc(sizeof(sommet_t)*g->n_sommets);

        //init listes et matrices
        g->l_adj = (liste_t*) malloc(sizeof(liste_t)*(g->n_sommets));
        g->m_stockage = (int*)calloc((g->n_sommets)*(g->n_sommets), sizeof(int));
        g->m_adj = (int**)calloc(g->n_sommets, sizeof(int*));
        g->distance = (int*)calloc((g->n_sommets), sizeof(int));
        for ( i = 0; i < g->n_sommets; i++)
        {
            initialiser_liste(&(g->l_adj[i]));
            initialiser_sommet(&(g->sommets[i]),i);    
            g->m_adj[i] = &(g->m_stockage[i * (g->n_sommets)]);
        }
        
        fscanf(fichier,"%s",buffer);
        fscanf(fichier, "%d", &g->oriente);

        fscanf(fichier,"%s",buffer);
        fscanf(fichier, "%d", &g->value);

        fscanf(fichier,"%s",buffer);

        if(!g->oriente){
            if(!strcmp(buffer,"DEBUT_DEF_ARETES")){
                while (strcmp(buffer,"FIN_DEF_ARETES"))
                {
                    cellule_t *s1, *s2;
                    s1 = (cellule_t*)malloc(sizeof(cellule_t));
                    s2 = (cellule_t*)malloc(sizeof(cellule_t));
                    fscanf(fichier,"%s",buffer);

                    if(strcmp(buffer,"FIN_DEF_ARETES")){
                        areteCpt ++;
                        initialiser_cellule(s1,atoi(buffer));

                        fscanf(fichier,"%s",buffer);
                        initialiser_cellule(s2,atoi(buffer));
                        if(g->value){
                            fscanf(fichier,"%s",buffer);
                            s2->poids = atoi(buffer);
                        }    
                        inserer(&(g->l_adj[s1->id_sommet]),s2);
                        inserer(&(g->l_adj[s2->id_sommet]),s1);

                        g->m_adj[s1->id_sommet][s2->id_sommet] = g->value?atoi(buffer):1;
                        g->m_adj[s2->id_sommet][s1->id_sommet] = g->value?atoi(buffer):1;
                    }
                }
                
            }
        }else
        {
            if(!strcmp(buffer,"DEBUT_DEF_ARETES")){
                while (strcmp(buffer,"FIN_DEF_ARETES"))
                {
                    cellule_t *s1, *s2;
                    s1 = (cellule_t*)malloc(sizeof(cellule_t));
                    s2 = (cellule_t*)malloc(sizeof(cellule_t));
                    fscanf(fichier,"%s",buffer);

                    if(strcmp(buffer,"FIN_DEF_ARETES")){
                        areteCpt ++;
                        initialiser_cellule(s1,atoi(buffer));

                        fscanf(fichier,"%s",buffer);
                        initialiser_cellule(s2,atoi(buffer));
                        if(g->value){
                            fscanf(fichier,"%s",buffer);
                            s2->poids = atoi(buffer);
                        }
                        inserer(&(g->l_adj[s1->id_sommet]),s2);

                        g->m_adj[s1->id_sommet][s2->id_sommet] = g->value?atoi(buffer):1;
                    }
                }
                
            }
        }

        //Création du tableau d'aretes
        g->aretes = (arete_t*)malloc(sizeof(arete_t)*areteCpt);
        for(i = 0; i<g->n_sommets;i++) {
            for( j = 0; j<i ; j++){
                if(g->m_adj[i][j] != 0) {
                    initialiser_arete(&g->aretes[k], &g->sommets[j], &g->sommets[i], g->m_adj[i][j]);
                    k++;
                }
            }
        }
        g->nbAretes = k;
    }
    return 0;
}

void afficher_graphe(graphe_t* g){
    int i = 0;
    int j = 0, k = 0;
    if(g != NULL){
        printf("Nombre de sommets: %d\n",g->n_sommets);
        if(!g->oriente){
            printf("Non oriente\n");
        }else
            printf("Oriente\n");

        if(!g->value){
            printf("Non value\n");
        }else
            printf("Value\n");
        
        printf("\nListes d'adjacences:\n");
        for ( i = 0; i < g->n_sommets; i++) {
            printf("%d -> ",i);
            afficher_liste(&(g->l_adj[i]));
        }

        printf("\nMatrice d'adjacences:\n");

        for ( j = 0; j < g->n_sommets; j++) {
            for ( k = 0; k < g->n_sommets; k++) {
                printf("%d ",g->m_adj[j][k]);
            }
            printf("\n");
        }

        printf("Aretes:\n");
        for(i = 0; i < g->nbAretes;i++) {
            printf("origin: %d end: %d poids: %d\n",g->aretes[i].origin->id_sommet, g->aretes[i].end->id_sommet, g->aretes[i].poids);
        }
    }
}

int detruire_graphe(graphe_t* g){
    int i;
    for ( i = 0; i < g->n_sommets; i++)
    {
        detruire_liste(&(g->l_adj[i]));
    }
    free (g->m_adj);
    free(g->m_stockage);

    (g->m_adj) = NULL;
    (g->m_stockage) = NULL;

    free(g);
    g = NULL;

    return 0;
}

int parcours_largeur(graphe_t* g, sommet_t* s){
    int i;
    file_t* f;
    sommet_t* u, *v;
    cellule_t* c;
    initialiser_file(&f,g->n_sommets);

    for (i = 0; i < g->n_sommets; i++)
    {
        g->sommets[i].distance = INF;
        g->sommets[i].couleur = BLANC;
    }
    s->couleur = GRIS;
    s->pere = NULL;
    s->distance = 0;

    enfiler(f, s);
    while(!file_vide(f)){
        u = defiler(f);
        c = g->l_adj[u->id_sommet].tete;
        while (c)
        {
            v = &(g->sommets[c->id_sommet]); //indice du sommet correspondant, si l'id est 3, le sommet est 3
            if(v->couleur == BLANC)
            {
                v->couleur = GRIS;
                v->pere = u;
                v->distance = u->distance +1;
                enfiler(f,v);
            }
            u->couleur = NOIR;
            c = c->suiv;
        }
    }

    return 1;
}

int afficher_chemin(graphe_t* g, sommet_t* s, sommet_t* v){
    if(v->id_sommet == s->id_sommet){
        printf("%d ", v->id_sommet);
    }else
    {
        if(v->pere == NULL){
            printf("\nil n'existe aucun chemin de S a V\n");
        }else
        {
            afficher_chemin(g,s,v->pere);
            printf("%d ",v->id_sommet);
        }
        
    }
    return 1;
}

int visiter_pp(graphe_t* g, sommet_t* s, int* date){
    cellule_t* c;
    (*date) ++;
    s->date_d = *date;
    s->couleur = GRIS;
    c = g->l_adj[s->id_sommet].tete;
    while(c != NULL){
        if(g->sommets[c->id_sommet].couleur == BLANC){
            g->sommets[c->id_sommet].pere = s;
            visiter_pp(g, &(g->sommets[c->id_sommet]), date);
        }
        c = c->suiv;
    }
    (*date) ++;
    s->date_f = *date;
    s->couleur = NOIR;

    return 1;
}

int parcours_profondeur_recursif(graphe_t* g){
    int i,date = 0;
    for(i = 0; i < g->n_sommets; i++){
        g->sommets[i].couleur = BLANC;
        g->sommets[i].pere = NULL;
    }
    for(i = 0; i < g->n_sommets; i++){
        if(g->sommets[i].couleur == BLANC){
            visiter_pp(g, &(g->sommets[i]), &date);
        }
    }

    return 1;
}

int afficher_parcours_profondeur(graphe_t* g){
    int i;

    for(i = 0; i < g->n_sommets; i++){
        printf("Sommet : %d, date debut : %d, date fin : %d,pere :", g->sommets[i].id_sommet, g->sommets[i].date_d, g->sommets[i].date_f);
        if(g->sommets[i].pere){
            printf("%d\n", g->sommets[i].pere->id_sommet);
        }
        else{
            printf("-1\n");
        }
    }
    return 1;
}

int parcours_profondeur_iteratif(graphe_t* g){
    int i;
    pile_t* p;
    sommet_t* v = NULL;
    cellule_t* c;

    p = (pile_t*)malloc(sizeof(pile_t));

    for(i = 0; i < g->n_sommets; i++){
        g->sommets[i].couleur = BLANC;
        g->sommets[i].pere = NULL;
    }
    initialiser_pile(p, g->n_sommets);

    for(i = 0; i < g->n_sommets; i++){
        if(g->sommets[i].couleur == BLANC){
            g->sommets[i].couleur = GRIS;
            empiler(p,&(g->sommets[i]));
            while (!pile_vide(p))
            {
                v = depile(p);
                //printf("%d ",v->id_sommet);
                c = g->l_adj[v->id_sommet].tete;
                while(c != NULL){
                    if(g->sommets[c->id_sommet].couleur == BLANC){
                        g->sommets[c->id_sommet].couleur = GRIS;
                        g->sommets[c->id_sommet].pere = v;
                        empiler(p,&(g->sommets[c->id_sommet]));
                    }
                    c = c->suiv;
                }
            }
            if(v)   
                v->couleur = NOIR;
        }
    }
    return 1;
}

arete_t* generer_acpm_kruskal_tableau(graphe_t* g){
    int* cc = (int*)malloc(sizeof(int)*g->nbAretes);
    arete_t* e = (arete_t*)malloc(sizeof(arete_t)*(g->n_sommets - 1));
    int i, j=0, k, icc;
    TriInsertion(g->aretes, g->nbAretes);
    for(i=0; i<g->nbAretes; i++){
        cc[i] = i;
    }

    for(i=0; i<g->nbAretes; i++){
        if(cc[g->aretes[i].origin->id_sommet] != cc[g->aretes[i].end->id_sommet]){
            e[j] = g->aretes[i];
            icc = cc[g->aretes[i].end->id_sommet];
            for(k = 0; k<g->n_sommets;k++){
                if(cc[k] == icc){
                    cc[k] = cc[g->aretes[i].origin->id_sommet];
                }
            }
        }
    }
    return e;
}

ensemble_t* generer_acpm_kruskal_ensembles(graphe_t* g){
    int i,poids = 0;
    ensemble_t* ensembles = (ensemble_t*)malloc(sizeof(ensemble_t)*g->n_sommets); 
    for(i = 0; i < g->n_sommets; i++){
       ensembles[i] = *creer_ensemble(&g->sommets[i]);
    }
    TriParTas(g->aretes,g->nbAretes);
    printf("\nAretes avec Ensemble pour acpm:\n");
    for(i = 0; i < g->nbAretes; i++){
        if(trouver_ensemble(ensembles[g->aretes[i].origin->id_sommet].tete) != trouver_ensemble(ensembles[g->aretes[i].end->id_sommet].tete)){
            union_ensemble(ensembles[g->aretes[i].origin->id_sommet].tete,ensembles[g->aretes[i].end->id_sommet].tete);
            poids += g->aretes[i].poids;
            //afficher arete
            printf("%d : %d -> %d, poids : %d\n",i, g->aretes[i].origin->id_sommet, g->aretes[i].end->id_sommet, g->aretes[i].poids);
        }
    }
    printf("Poids minimal: %d\n\n",poids);
    return ensembles;
}

int min(int* d, int* couvert, int taille){
    int i = 0, res = 1000;
    for(i =0; i< taille; i++){
        if(d[i] < res && couvert[i]==0){
            res = d[i];
        }
    }
    return res;
}

int generer_acpm_prim_tableau(graphe_t* g, int start){
    int i, j, u, poids = 0;
    //acpm = (arete_t*)malloc(sizeof(arete_t)*(g->n_sommets - 1));
    cellule_t* c;

    int* pere = (int *)malloc(sizeof(int)*g->n_sommets);
    int* couvert = (int *)malloc(sizeof(int)*g->n_sommets);

    for(i = 0; i < g->n_sommets; i++){
        g->distance[i] = 999;
        g->sommets[i].pere = NULL;
        couvert[i] = 0;
    }
    g->distance[start] = 0;
    for(i = 0; i < g->n_sommets - 1; i++){
        u = min(g->distance,couvert, g->n_sommets);
        couvert[u] = 1;
        c = g->l_adj[u].tete;
        while(c != NULL){
            if(c->poids < g->distance[c->id_sommet] && !couvert[c->id_sommet]){
                //printf("poids = %d", c->poids);
                g->distance[c->id_sommet] = c->poids;
                //printf("distance = %d\n", g->distance[c->id_sommet]);
                g->sommets[c->id_sommet].pere = &g->sommets[u];
            }

            c = c->suiv;
        }
    }

    for(i = 0; i < g->n_sommets; i++){
        if(g->sommets[i].pere){
            printf("%d,", g->sommets[i].pere->id_sommet);
        }
        else{
            printf("-1");
        }
        printf(" poids: %d\n",g->distance[i]);
    }
    return 1;
}

int afficher_acpm(graphe_t* g){
    int i = 0, poidsMin = 0;
    printf("\nArbre couvrant de point minimal définit par les arrêtes : \n");
    for(i=0; i < g->nbAretes; i++){
        printf("%d : %d -> %d, poids : %d\n",i, g->aretes[i].origin->id_sommet, g->aretes[i].end->id_sommet, g->aretes[i].poids);
        poidsMin += g->aretes[i].poids;
    }
    printf("Poids minimal couvrant = %d\n", poidsMin);
}

int afficher_acpm_ensemble(ensemble_t* e){
    ensemble_cell_t* cell = e->tete;

    printf("\n\nEnsemble de l'arbre couvrant de poids minimal:\nensemble :");
    while (cell != NULL)
    {
        printf(" -> %d",cell->sommet->id_sommet);
        cell = cell->succ;
    }
    return 1;
}

int afficher_acpm_prim_tableau(graphe_t* g){
    int i;

    for(i = 0; i < g->n_sommets; i++){
        printf("Sommet : %d, pere :", g->sommets[i].id_sommet);
        if(g->sommets[i].pere){
            printf("%d,", g->sommets[i].pere->id_sommet);
        }
        else{
            printf("-1");
        }
        printf(" poids: %d\n",g->distance[i]);
    }
    return 1;
}

int appartient(file_t* f, sommet_t* sommet){
    int i;

    for ( i = 0; i < f->size; i++)
    {
        if(&f->stockage[i] != NULL && f->stockage[i].id_sommet == sommet->id_sommet){
            //(f->stockage+i) = NULL;
            return 1;
        }
    }
    return 0;
}

int generer_acpm_prim_file(graphe_t* g, sommet_t* r){
    int i;
    file_t* f = (file_t*)malloc(sizeof(file_t));
    sommet_t* u;
    cellule_t* c;
    for(i = 0; i < g->n_sommets; i++){
        g->sommets[i].pere = NULL;
        g->sommets[i].cle = 999;
    }
    r->cle = 0;
    f->stockage = g->sommets;
    while(!file_vide(f)){
        u = extraire_min(f);
        c = g->l_adj[u->id_sommet].tete;
        while(c != NULL){
            if(appartient(f, &g->sommets[c->id_sommet]) && c->poids < g->sommets[c->id_sommet].cle){
                g->sommets[c->id_sommet].pere = &g->sommets[u->id_sommet];
            }

            c = c->suiv;
        }
    }
}
