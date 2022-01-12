#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define SPIN 1000000000
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int compteur = 0;

void *thread_compteur(void *args){
    int i = 0, statut = 0;
    int *nbthread = args;

    statut = pthread_mutex_lock(&mutex);
    if(statut != 0){
        printf("Probleme lors de l'ouverture du mutex\n");
    }
    for(i = 0; i < SPIN/(*nbthread); i++){
        compteur++;
    }
    statut = pthread_mutex_unlock(&mutex);
    if(statut != 0){
        printf("Probleme lors de l'ouverture du mutex\n");
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	int statut = 0, i = 0, diffTemps = 0;
	time_t temps1, temps2;
    pthread_t threads(atoi(argv[1]));

	temps1 = time(NULL);
	for (i = 0; i < SPIN; i++)
		compteur++;
	temps2 = time(NULL);
	diffTemps = (int) temps2 - (int) temps1;
	printf("Valeur finale du compteur : %d\n", compteur);
	printf("Temps : %d secondes\n", diffTemps);

	return 0;
}