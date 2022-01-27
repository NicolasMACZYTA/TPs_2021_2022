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
    pid_t *pid = malloc(sizeof(pid)*nbr);
    int i = 0, statut = 0;
    
    printf("Il y a %d fils.", nbr);

    for(i = 0; i<nbr; i++){
        if((pid[i]=fork())==0){
            if(getpid()!=getppid()){
                srand(time(NULL));
                printf("Fils%d : PID=%d, rand=%d\n", i+1, getpid(), rand());
                exit(EXIT_SUCCESS);
            }
        }else if(pid[i]<0){
            printf("Erreur creation processus %d", i);
            exit(EXIT_FAILURE);
        }else{
            if(wait(&statut)==-1){
                perror("Erreur attente fils");
                exit(EXIT_FAILURE);
            }
        }
    }

    return EXIT_SUCCESS;
}