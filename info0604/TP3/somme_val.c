#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define TAILLETAB 20
#define MAX_THREADS 5

int tab[TAILLETAB];
int somme=0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void* traiterTableau(void* arg){
    int* idTableau = (int*)arg;
    unsigned int seed = time(NULL)+*idTableau;;
    int i, idThread=*idTableau/4,somme_thread=0,statut;

    //INITIALISATION DES CASES DU TABLEAUX + ADDITION DE LA SOMME DU THREAD
    printf("**********\nTHREAD %d\n",idThread);
    for(i=*idTableau;i<*idTableau+4;i++){
        tab[i]=(rand_r(&seed)%5)+1;
        somme_thread+=tab[i];
        printf("indice %d : %d\nsomme = %d\n",i,tab[i],somme_thread);
    }

    free(arg);


    statut=pthread_mutex_lock(&mutex);
    if(statut != 0){
        perror("mutex lock\n");
        exit(EXIT_FAILURE);
    }

    somme+=somme_thread;

    statut=pthread_mutex_unlock(&mutex);
    if(statut != 0){
        perror("mutex unlock\n");
        exit(EXIT_FAILURE);
    }

    return NULL;

}


int main(int argc,char** argv){
    pthread_t threadTab[MAX_THREADS];
    int* idTableau;
    int i, statut;

    //initialisation du tableau de val
    for(i=0;i<MAX_THREADS;i++){
        idTableau = (int*)malloc(sizeof(int));
        *idTableau = i*4;
        statut = pthread_create(&threadTab[i],NULL,traiterTableau,(void*)idTableau);
        if(statut != 0){
            perror("initialisation Thread\n");
            exit(EXIT_FAILURE);
        }    
    }

    //attente des threads
    for(i=0;i<MAX_THREADS;i++){
        statut = pthread_join(threadTab[i],NULL);
        if(statut != 0){
            perror("erreur pthread_join\n");
            exit(EXIT_FAILURE);
        }
    }

    //AFFICHAGE DE LA SOMME
    printf("**********\nSomme Final = %d\n",somme);

    return(EXIT_SUCCESS);
}