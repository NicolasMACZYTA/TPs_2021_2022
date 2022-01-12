#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* hello1(void*data){
    int *value = &((mutex*)data)->val;
    char str[] = "hello world";
    int i=0;
    while(i<12){
        pthread_mutex_lock(&mutex);
        fprintf(stderr,"%c",str[i]);
        usleep(1000000);
        pthread_mutex_unlock(&mutex);
        i++;
    }
    fprintf(stderr,"\n");

    fprintf(stderr,"endl\n");

    pthread_exit(NULL);
}

int main(void){

    pthread_t t1;
    
    pthread_create(&t1,NULL,func,NULL);


    pthread_join(t1,NULL);
    return 0;
}