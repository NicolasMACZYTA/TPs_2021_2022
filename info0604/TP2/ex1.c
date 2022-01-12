#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int compteur = 0;

void *thread_affichage(void *args){
    int statut = 0;

    while(1){
        printf("Thread affichage\n");
        statut = pthread_mutex_lock(&mutex);
        if(statut != 0){
            printf("Erreur ouverture du mutex\n");
        }
        
        if(compteur%2 == 0){//faire la verification du paire dans le compteur et il appelle l'affichage
            printf("Compteur est a : %d\n",compteur);
        }

        statut = pthread_mutex_unlock(&mutex);
        if(statut != 0){
            printf("Erreur fermeture du mutex\n");
        }

        sleep(1); //Dors une seconde
    }

    pthread_exit(NULL);
}

void *thread_remise(void *args){
    int statut = 0;

    while(1){
        statut = pthread_mutex_lock(&mutex);
        if(statut != 0){
            printf("Erreur ouverture du mutex\n");
        }
        
        if(compteur >= 10){
            compteur = 0;
        }

        statut = pthread_mutex_unlock(&mutex);
        if(statut != 0){
            printf("Erreur fermeture du mutex\n");
        }

    }

    pthread_exit(NULL);
}

void *thread_compteur(void *args){
    int statut = 0;

    while(1){
        statut = pthread_mutex_lock(&mutex);
        if(statut != 0){
            printf("Erreur ouverture du mutex\n");
        }
        
        compteur++;

        statut = pthread_mutex_unlock(&mutex);
        if(statut != 0){
            printf("Erreur fermeture du mutex\n");
        }

        sleep(2);//fait une microsieste de deux secondes
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	int statut = 0, i = 0;
    pthread_t threads[3];

    //creation des threads
    statut = pthread_create(&threads[i], NULL, thread_compteur, NULL);
    if(statut != 0){
        printf("Erreur creation thread compteur : %d\n", i);
    }
    statut = pthread_create(&threads[i], NULL, thread_affichage, NULL);
    if(statut != 0){
        printf("Erreur creation thread affichage : %d\n", i);
    }
    statut = pthread_create(&threads[i], NULL, thread_remise, NULL);
    if(statut != 0){
        printf("Erreur creation thread remise : %d\n", i);
    }

    //attente de la fin des threads
    for(i=1; i<3; i++){
        statut = pthread_join(&threads[i], NULL);
        if(statut != 0){
            printf("Erreur attente thread numero : %d\n", i);
        }
    }

	return EXIT_SUCCESS;
}