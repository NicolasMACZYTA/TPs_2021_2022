#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
 
int main(int argc, char *argv[]){
    char buf[50];
    char *tmp;
    int fd1, fd2, fileread;

    if(buf == NULL){
        perror("Erreur d'allocation "); exit(EXIT_FAILURE);
    }

    printf("Quel est le nom du fichier a copier?\n");
    if(scanf("%49s", buf) == EOF){
        perror("Erreur du scanf "); exit(EXIT_FAILURE);
    }

    fd1 = open(buf, O_RDONLY | O_CREAT, S_IWUSR | S_IRUSR);
    if(fd1 == -1){
        perror("Erreur fichier "); exit(EXIT_FAILURE);
    }else{
        printf("Quel est le nom du fichier destination?\n");
        if(scanf("%49s", buf) == EOF){
            perror("Erreur du scanf "); exit(EXIT_FAILURE);
        }
        
        fd2 = open(buf, O_RDWR | O_CREAT | O_EXCL | O_APPEND, S_IWUSR | S_IRGRP | S_IROTH);
        if(fd2 == -1){
            perror("Erreur fichier "); exit(EXIT_FAILURE);
        }else{
            while(1){
                fileread = read(fd1, buf, sizeof(buf));
                if(fileread == -1){
                    perror("Erreur lecture "); exit(EXIT_FAILURE);
                }
                if(fileread == 0){break;}
                
                tmp = buf;
                while(tmp < buf + fileread){
                    fileread = write(fd2, tmp, (size_t)(buf+fileread - tmp));
                    if(fileread == -1){
                        perror("Erreur ecriture "); exit(EXIT_FAILURE);
                    }
                    tmp += fileread;
                }
            }
        }

        close(fd2);
        printf("Copie du fichier terminée.\n");
    }
    close(fd1);
    
    return EXIT_SUCCESS;
}