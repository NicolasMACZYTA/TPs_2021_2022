#include "fichier.h"
#include "ihm_ncurses.h"
#include "monstre.h"
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


int ftruncate(int fd, off_t length);

char * hex_from_buf(char*buf){
    char * hex=malloc(1024*sizeof(char)); 
    string2hexString(buf,hex);

    /*printf("%s",hex);*/

    return hex;
}

void string2hexString(char* input, char* output)
{
    int loop=0;
    int i=0; 

    while(input[loop] != '\0')
    {
        sprintf((char*)(output+i)," %02X", input[loop]);
        loop+=1;
        i+=3;
    }
    /*insert NULL at the end of the output string*/
    output[i++] = '\0';
}

char * to_string(char*buf,int offset){
    char * res= malloc(800*sizeof(char));
    char * hex = hex_from_buf(buf);
    char *line = (char*)malloc(8*sizeof(char));
    int i=0,j=0;
    res[0]='\0';
        for(i=0; i<16;i++){
            strcat(res,"0");
            sprintf((char*)(line), "%07X", (offset)+(8*i));
            strcat(res, line);
            for(j =0;j<24;j++){
                res[((8*(i+1))+(24)*i)+j]=hex[(24*i)+j];
            }
    }
    res[513]='\0';
    return res;
}




char * to_disp(char*buf){
    char * res = malloc(strlen(buf)*sizeof(char));
    int i;
    for(i=0;i<=strlen(buf);i++){
        if(buf[i]=='\n'||buf[i]=='\r'){
            res[i]=' ';
        }else{
            res[i]=buf[i];
        }
    }
    return res;
}



void lire_buf(int fd, char*buf, int offset){
    int i;
    free(buf);
    buf=malloc(801*sizeof(char));
    for(i=0;i<800;i++){
        buf[i]='\0';
    }
    lseek(fd,offset,SEEK_SET);
    if(0<read(fd, buf, 800)){
        buf[800]='\0';
    }else{
        ncurses_stopper();
        printf("erreur lecture ;\n");
        exit(EXIT_FAILURE);
    }
}
void ecrire_buf(int fd, char*buf, int offset){
    lseek(fd,offset,SEEK_SET);
    if(0<write(fd, buf, 800)){
        
    }else{
        ncurses_stopper();
        printf("erreur ecriture ;\n");
        exit(EXIT_FAILURE);
    }
}
void supprimer_octet(int fd, int selection, int offset,int size){
    int i=offset+selection;
    char * buf2 = malloc(801*sizeof(char));
    buf2[800]='\0';
    lseek(fd,offset+selection+1,SEEK_SET);
    while (i<size){
        lire_buf(fd,buf2,i+1);
        ecrire_buf(fd,buf2,i);
        i=i+128;
    }
    
    ftruncate(fd, size-1);
    free(buf2);
}

int creer_fichier(char* nomfichier,int taille_grille, int nb_grilles, int nb_monstres){
    char buf[nb_grilles*taille_grille+1];
    int fd;
    int tab_monstre[nb_monstres*4];
     for(int i=0;i<nb_grilles*taille_grille;i++){
        buf[i]='h';
    }
    for(int j=0;j<nb_monstres*4;j++){
        tab_monstre[j]=0;
    }
    buf[nb_grilles*taille_grille]='\0';
    if(buf == NULL){
        perror("Erreur d'allocation "); return -1;
    }

    fd = open(nomfichier, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);
    if(fd == -1){
        perror("Erreur fichier "); return -1;
    }else{


        

        if(write(fd, buf, 1600) == -1){
            perror("Erreur du write "); return -1;
        }
        if(write(fd, tab_monstre, nb_monstres*4*(sizeof(int))) == -1){
            perror("Erreur du write "); return -1;
        }
    }
    close(fd);
    return fd;
}

int sauvegarder_carte(char* nomfichier, char* buf1,char*buf2,int *buf3,int taillegrille, int nbmonstres){
    int fd = open(nomfichier, O_WRONLY|O_TRUNC, S_IWUSR | S_IRUSR);
    if(fd == -1){
        perror("Erreur fichier "); return -1;
    }else{


        lseek(fd,0,SEEK_SET);

        if(write(fd, buf1, taillegrille) == -1){
            perror("Erreur du write "); return -1;
        }
        if(write(fd, buf2, taillegrille) == -1){
            perror("Erreur du write "); return -1;
        }
        if(write(fd, buf3, nbmonstres*4*(sizeof(int))) == -1){
            perror("Erreur du write "); return -1;
        }
    }
    close(fd);
    return 0;
}

