#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define M	6
#define N	6

int **matrice;
int *vecteur;
int *vecResultat;

void afficherMatrice(int** matrice, int m, int n) {
	int i, j;
	printf("Matrice_____\n");
	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++)
			printf("%d ", matrice[i][j]);
		printf("\n");
	}
	printf("____________\n");
}

void afficherVecteur(int* vecteur, int taille) {
	int i;
	printf("Vecteur******\n");
	for (i = 0; i < taille; i++)
		printf("%d ", vecteur[i]);
	printf("\n");
	printf("*************\n");
}

int main(int argc, char *argv[]) {
	int i, j;

	srand(time(NULL));

	matrice = (int **) malloc(sizeof(int *) * M);
	vecteur = (int *) malloc(sizeof(int) * N);
	for (i = 0; i < M; i++) {
		matrice[i] = (int *) malloc(sizeof(int) * N);
		for (j = 0; j < N; j++)
			matrice[i][j] = (rand() % 5) + 1;
	}
	for (i = 0; i < N; i++)
		vecteur[i] = (rand() % 5) + 1;

	vecResultat = (int *) malloc(sizeof(int) * M);
	for (i = 0; i < M; i++)
		vecResultat[i] = -1;	

	afficherMatrice(matrice, M, N);
	afficherVecteur(vecteur, N);

	for (i = 0; i < M; i++)	{
		vecResultat[i] = 0;
		for (j = 0; j < N; j++)
			vecResultat[i] = vecResultat[i] + matrice[i][j] * vecteur[j];
	}

	afficherVecteur(vecResultat, M);

	free(vecteur);
	free(vecResultat);
	for (i = 0; i < M; i++)
		free(matrice[i]);
	free(matrice);

	return 0;
}
