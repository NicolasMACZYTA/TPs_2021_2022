#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct thread_type{
    long id;
    int nb;
}thread_t;

void *bonjour(void *args){
    thread_t *_args = (thread_t*)args;
    printf("Hello world ! du thread %ld de %d !\n",_args->id,_args->nb);
    pthread_exit(NULL);
}

int main(int argc, char*argv[]){
    pthread_t threads[atoi(argv[1])];
    thread_t *args[atoi(argv[1])];
    long i;
    for(i=1; i<atoi(argv[1])+1; i++){
        args[i]=malloc(sizeof(thread_t));
        args[i]->id=i;
        args[i]->nb=atoi(argv[1]);
        pthread_create(&threads[i],NULL,bonjour,(void *)args[i]);
    }
    pthread_exit(NULL);

    for(i=0; i<atoi(argv[1]); i++){
        free(args[i]);
    }

    return EXIT_SUCCESS;
}