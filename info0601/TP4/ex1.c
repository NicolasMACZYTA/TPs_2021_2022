#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <locale.h>
#include <time.h>

int main(int argc, char *argv[]){
    int nbr = atoi(argv[1]);
    pid_t pid[nbr];
    int i = 0;
    printf("Il y a %d fils.", nbr);

    for(i = 0; i<nbr; i++){
        if(fork()==0){

        }else
    }
}