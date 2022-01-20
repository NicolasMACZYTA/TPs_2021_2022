#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
 
int main(int argc, char *argv[]){
    char buf[50];
    int size, fd, fd2;

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
        lseek(fd, 0, SEEK_SET);
        read(fd, buf, 10);
        
        fd2 = open("toto.bin", O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);
        if(fd2 == -1){
            perror("Erreur fichier "); exit(EXIT_FAILURE);
        }else{
            if(write(fd2, buf, strlen(buf)) == -1){
                perror("Erreur du write "); exit(EXIT_FAILURE);
            }
        }
        close(fd2);
    }
    close(fd);
    
    return EXIT_SUCCESS;
}