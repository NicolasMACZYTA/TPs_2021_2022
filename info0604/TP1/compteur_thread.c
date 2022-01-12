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

    for(i = 0; i < SPIN/(*nbthread); i++){
        statut = pthread_mutex_lock(&mutex);
        if(statut != 0){
            printf("Probleme lors de l'ouverture du mutex\n");
        }

        compteur++;

        statut = pthread_mutex_unlock(&mutex);
        if(statut != 0){
            printf("Probleme lors de l'ouverture du mutex\n");
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	int statut = 0, i = 0, diffTemps = 0;
	time_t temps1, temps2;
    pthread_t threads[atoi(argv[1])];
    int nbthread = atoi(argv[1]);

	temps1 = time(NULL);
    //creation des threads
    for(i=1; i<atoi(argv[1])+1; i++){
        statut = pthread_create(&threads[i], NULL, thread_compteur, &nbthread);
        if(statut != 0){
            printf("Probleme lors de la creation du thread numero : %d\n", i);
        }
    }

    //attente de la fin des threads
    for(i=1; i<atoi(argv[1])+1; i++){
        statut = pthread_join(&threads[i], NULL);
        if(statut != 0){
            printf("Probleme lors du join du thread numero : %d\n", i);
        }
    }


	temps2 = time(NULL);
	diffTemps = (int) temps2 - (int) temps1;
	printf("Valeur finale du compteur : %d\n", compteur);
	printf("Temps : %d secondes\n", diffTemps);

	return 0;
}