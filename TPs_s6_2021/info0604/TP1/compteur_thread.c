#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int SPIN = 4000;

int compteur = 0;

void *PrintHello(void *args){
    for(int i=0;i<SPIN;i++){
        compteur++;
    }
    pthread_exit(NULL);

}

int main(int argc, char *argv[]){
    printf(compteur);
    printf("\n");
    pthread_t threads[atoi(argv[1])];
    int rc;
    int i;
    for(i=1;i<atoi(argv[1])+1;i++){
        pthread_create(&threads[i],NULL,PrintHello,NULL);
    }

    printf("valeure finale de SPIN : %d",compteur);
    pthread_exit(NULL);

    
    return EXIT_SUCCESS;
}