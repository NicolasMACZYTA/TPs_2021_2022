#include"graphe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void initialiserGraphe(graphe_t *g, char *nomFichier){
	FILE *fichier = NULL;
	char buffer[50]="";
	char debut[17]="";
	char fin[15]="";
	int i=0, j=0;
	int sommet1=0, sommet2=0, poids=0;
	//cellule_t *c;
	int valeur = 1;
	int count =0;
	
	fichier = fopen(nomFichier, "r+");
	if(fichier != NULL){
		//calcul nombre arete
		int l=0;
		int character_read;
    	while((character_read = fgetc(fichier)) !=EOF){

        if(character_read == '\n'){l++;}

    	}

    	l-=5;

		printf("\nnombre d'aretes %d\n",l);

		fseek(fichier, 0, SEEK_SET);// SEEK_SET : début du fichier
        fscanf(fichier,"%s",buffer);
		fscanf(fichier,"%d",&g->nb_sommets);
		
		// Allocation et initialisation de la matrice d'adjacence
		printf("Allocation memoire matrice, nombre de sommet = %d\n",g->nb_sommets);
		g->matriceAdjacence=malloc(sizeof(int*)*g->nb_sommets);
		for(i=0;i<g->nb_sommets;i++){
			g->matriceAdjacence[i]=malloc(sizeof(int)*g->nb_sommets);
			for(j=0;j<g->nb_sommets;j++){
				g->matriceAdjacence[i][j]=0;
			}
		}
		
		// Initialisation de la liste d'adjacence
		printf("allocation mémoire lAdjacence\n");
		g->listeAdjacences=malloc(sizeof(liste_t)*g->nb_sommets+1);
		g->tSommet=malloc(sizeof(sommet_t)*g->nb_sommets);
		g->aretes=malloc(sizeof(arete_t)*l);
		g->nb_aretes=l;

		for(i=0;i<g->nb_sommets;i++){
		    //liste_t l;
			//initialiser_liste(&l);
			initialiser_liste(&g->listeAdjacences[i]);
		}

		//fseek(fichier, 7, SEEK_CUR); // SEEK_CUR : position courante du curseur
        fscanf(fichier,"%s",buffer);
		fscanf(fichier,"%d",&g->orienter);

		//fseek(fichier, 6, SEEK_CUR);
        fscanf(fichier,"%s",buffer);
		fscanf(fichier,"%d",&g->valuer);

        fscanf(fichier,"%s",debut);


		// Lecture des arrêtes et mise à jour de la matrice d'adjacence
		printf("début du remplissage de la matrice d'adjacence\n");


		if(!strcmp(debut,"DEBUT_DEF_ARCS")){ //On verifi si il y a bien la ligne "DEBUT_DEF_ARETES"
			while(strcmp(fin,"FIN_DEF_ARCS")) {

				cellule_t *s1,*s2;
				s1 = (cellule_t*)malloc(sizeof(cellule_t));
				s2 = (cellule_t*)malloc(sizeof(cellule_t));
                fscanf(fichier, "%d %d", &sommet1, &sommet2);
                if ((sommet1 >= 1 && sommet1 <= g->nb_sommets) &&
                    (sommet2 >= 1 && sommet2 <= g->nb_sommets)) {//verification des valeurs
					
					initialiserCellule(s1,sommet1);
					initialiserCellule(s2,sommet2);
					
					
					if(g->valuer==1){//verif si graphe valuer
						fscanf(fichier, " %d", &valeur); // valeur est initialiser à 1 dans le cas ou le graph n'est pas valuer
						s2->poids=valeur;
					}
					inserer(&(g->listeAdjacences[s1->id_sommet-1]),s2);

                    g->matriceAdjacence[sommet1-1][sommet2-1] = valeur;
                    if (g->orienter == 0) {
                        g->matriceAdjacence[sommet2-1][sommet1-1] = valeur;
                    }
					g->aretes[count].origine=&g->tSommet[sommet1];
					g->aretes[count].fin=&g->tSommet[sommet2];
					g->aretes[count].poids=valeur;
					count++;
					
					
                }
                fgets(fin, 13, fichier);
			}
		}


		/*
		//Mise à jour de la liste d'adjacence
		printf("début du remplissage de la liste d'adjacence\n");


		for(i=0;i<g->nb_sommets;i++){
		    for(j=0;j<g->nb_sommets;j++){
		        if(g->matriceAdjacence[i][j] != 0){
					c=malloc(sizeof(cellule_t));
					initialiserCellule(c,j+1);
                    insererListe(&g->listeAdjacences[i], c);
		        }
		    }
			c=malloc(sizeof(cellule_t));
			initialiserCellule(c,i+1);
			insererListe(&g->listeAdjacences[i],c);
		}
		*/


		//initialisation du tableau de sommet
		printf("initialisation du tableau de sommets\n");
		for(i=0;i<g->nb_sommets;i++){
			g->tSommet[i].idSommet=g->listeAdjacences[i].tete->id_sommet;
			g->tSommet[i].cAsso=g->listeAdjacences[i].tete;
		}

		/*
		debug tableau aretes
		for(i=0;i<l;i++){
			printf("count : %d origine : %d fin : %d poids %d\n",i,g->aretes[i].origine->idSommet,g->aretes[i].fin->idSommet,g->aretes[i].poids);
		}*/
		
		rewind(fichier);//replace le curseur au début du fichier
		fclose(fichier);
	}
	else{
		printf("Impossible d'ouvrir le fichier.");
	}

}

void afficherGraphe(graphe_t *g){
	liste_t l;
	int i=0, j=0;
	
	if(g->nb_sommets!=-1){

		printf("Nombres de sommets : %d\n", g->nb_sommets);
		if(g->orienter==0){
			printf("Non oriente\n");
		}
		else{
			printf("Oriente\n");
		}

		if(g->valuer==0){
			printf("Non value\n");
		}
		else{
			printf("Value\n");
		}
		printf("Listes d'adjacences :\n\n");
		for(i=0;i<g->nb_sommets;i++){
			printf(" %d --> ", g->listeAdjacences[i].tete->id_sommet);
			l=g->listeAdjacences[i];
			l.tete=l.tete->suiv;
			afficher_liste(&l);
		}
		printf("\n");
		/*
		printf("Matrice d'adjacences :\n\n");
		for(i=0;i<g->nb_sommets;i++){
			for(j=0;j<g->nb_sommets;j++){
				printf(" %d ", g->matriceAdjacence[i][j]);
			}
			printf("\n");
		}
		*/
		printf("\n");

	}else{
		printf("Graphe vide\n");
	}
	


}
