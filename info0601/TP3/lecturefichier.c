#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
 
int main(int argc, char *argv[]){
    char buf[50];
    int size, fd;

    if(buf == NULL){
        perror("Erreur d'allocation "); exit(EXIT_FAILURE);
    }

    printf("Quel est le nom du fichier?\n");
    if(scanf("%49s", buf) == EOF){
        perror("Erreur du scanf "); exit(EXIT_FAILURE);
    }

    fd = open(buf, O_RDONLY, S_IWUSR | S_IRUSR);
    if(fd == -1){
        perror("Le fichier n'existe pas "); exit(EXIT_FAILURE);
    }else{
        size = lseek(fd, 0, SEEK_END);
        printf("Le ficher %s existe. Sa taille est : %d\n", buf, size);
    }
    close(fd);
    
    return EXIT_SUCCESS;
}