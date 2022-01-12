#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void* func1(void*arg){
    for (int i = 0;i<100;i++){
        fprintf(stderr,"%s\n",(char*)arg);
    }
    pthread_exit(arg);
}

void* func2(void*arg){
    for (int i = 0;i<100;i++){
        fprintf(stderr,"%s\n",(char*)arg);
    }
    pthread_exit(arg);
}

int main(void){

    pthread_t t1;
    pthread_t t2;

    pthread_create(&t1,NULL, func1,"hello1");
    pthread_create(&t2,NULL, func2,"hello2");

    char *s1, *s2;
    pthread_join(t1,(void**)&s1);
    pthread_join(t2,(void**)&s2);
    printf("%s %s\n",s1,s2);

    return 0;
}