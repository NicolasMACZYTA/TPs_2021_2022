#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv){
    int fd;
    if(0<open(argv[1],O_RDONLY)){
        printf("ce fichier existe déjà.\n");
        fd = open(argv[1], O_RDONLY);
        int size = lseek(fd, 0, SEEK_END);
        if(size>0){
            printf("il est de taille : %d octets\n",size);
        }
    }else{
        char* str=malloc(50*sizeof(char));

        printf("ce fichier n'existe pas.\n");
        printf("entrez une chaine de caractère pour l'écrire dans le fichier : ");
        scanf("%s",str);
        fd = open(argv[1],O_WRONLY | O_CREAT | O_APPEND);
        write(fd,str,strlen(str));
    }

    return EXIT_SUCCESS;
}