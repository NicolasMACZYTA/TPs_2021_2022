#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){

    if(0<open(argv[1],O_RDONLY)){
        printf("ce fichier existe.\n");
        int fd = open(argv[1], O_RDONLY);
        int size = lseek(fd, 0, SEEK_END);
        printf("il est de taille : %d octets\n",size);
    }else{
        printf("ce fichier n'existe pas.\n");
    }

    

    return EXIT_SUCCESS;
}