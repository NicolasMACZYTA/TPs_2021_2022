#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
 
int main(int argc, char *argv[]){
    char buf[50];
    int n=0, fd;

    if(buf == NULL){
        perror("Erreur d'allocation "); exit(EXIT_FAILURE);
    }

    printf("Veuillez entrer un entier\n");
    if(scanf("%d", &n) == EOF){
        perror("Erreur du scanf "); exit(EXIT_FAILURE);
    }

    fd = open("toto.bin", O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);
    if(fd == -1){
        perror("Erreur fichier "); exit(EXIT_FAILURE);
    }else{
        if(write(fd, &n, sizeof(int)) == -1){
            perror("Erreur du write "); exit(EXIT_FAILURE);
        }

        printf("Veuillez entrer une chaine de charactères\n");
        if(scanf("%49s", buf) == EOF){
            perror("Erreur du scanf "); exit(EXIT_FAILURE);
        }

        if(write(fd, buf, strlen(buf)) == -1){
            perror("Erreur du write "); exit(EXIT_FAILURE);
        }
    }
    close(fd);
    
    return EXIT_SUCCESS;
}