#include "fichier.h"
#include "ihm_ncurses.h"
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
    char * res= malloc(600*sizeof(char));
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
    buf=malloc(129*sizeof(char));
    for(i=0;i<128;i++){
        buf[i]='\0';
    }
    lseek(fd,offset,SEEK_SET);
    if(0<read(fd, buf, 128)){
        buf[128]='\0';
    }else{
        ncurses_stopper();
        printf("erreur lecture ;\n");
        exit(EXIT_FAILURE);
    }
}
void ecrire_buf(int fd, char*buf, int offset){
    lseek(fd,offset,SEEK_SET);
    if(0<write(fd, buf, 128)){
        
    }else{
        ncurses_stopper();
        printf("erreur ecriture ;\n");
        exit(EXIT_FAILURE);
    }
}
void supprimer_octet(int fd, int selection, int offset,int size){
    int i=offset+selection;
    char * buf2 = malloc(129*sizeof(char));
    buf2[128]='\0';
    lseek(fd,offset+selection+1,SEEK_SET);
    while (i<size){
        lire_buf(fd,buf2,i+1);
        ecrire_buf(fd,buf2,i);
        i=i+128;
    }
    
    ftruncate(fd, size-1);
    free(buf2);
}