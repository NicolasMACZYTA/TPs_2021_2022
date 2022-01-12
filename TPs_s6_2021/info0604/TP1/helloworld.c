#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct thread_args{
    long tid;
    int nbthreads;
}thread_args;

void *PrintHello(void *args){
    thread_args * _args = (thread_args *)args;
    printf("Hello world ! du thread %ld, de %d\n",_args->tid, _args->nbthreads);
    pthread_exit(NULL);

}

int main(int argc, char *argv[]){
    pthread_t threads[atoi(argv[1])];
    thread_args *args[atoi(argv[1])];
    long i;
    for(i=1;i<atoi(argv[1])+1;i++){
        args[i]= malloc(sizeof(thread_args));
        args[i]->tid=i;
        args[i]->nbthreads=atoi(argv[1]);
        pthread_create(&threads[i],NULL,PrintHello,(void *)args[i]);
    }
    pthread_exit(NULL);

    
    for(i=0;i<atoi(argv[1]);i++){
        free(args[i]);
    }
    return EXIT_SUCCESS;
}