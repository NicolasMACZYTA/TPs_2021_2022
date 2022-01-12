#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define SPIN 1000000000
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int compteur = 0;

void *thread_remise(void *args){
    int i = 0, statut = 0;
    int *nbthread = args;

    statut = pthread_mutex_lock(&mutex);
    if(statut != 0){
        printf("Probleme lors de l'ouverture du mutex\n");
    }
    
    if(compteur >= 9){
        compteur = 0;
    }

    statut = pthread_mutex_unlock(&mutex);
    if(statut != 0){
        printf("Probleme lors de l'ouverture du mutex\n");
    }

    pthread_exit(NULL);
}

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