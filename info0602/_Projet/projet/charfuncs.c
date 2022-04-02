#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charfuncs.h"

//fonction pour supprimer char dans string
void delStr(char *string, char *sub) {
    char *match;
    int len = strlen(sub);
    while((match = strstr(string, sub))){
        *match = '\0';
        strcat(string, match+len);
    }
}

//fonction pour compter nombre de fois un charactere à été trouver
int compteChar(char str[], char ch){
	int nb;
	nb = 0;
  	for(int i = 0; i <= strlen(str); i++){
  		if(str[i] == ch){
  			nb++;
 		}
	}
	return nb;
}

//replace char par string
char *replaceChar(char *str, char *a, char *b){ 
    int len  = strlen(str); 
    int lena = strlen(a), lenb = strlen(b); 
    for(char* p = str; (p = strstr(p, a)); ++p){ 
        if (lena != lenb){
            memmove(p+lenb, p+lena, len - (p - str) + lenb); 
        }
        memcpy(p, b, lenb); 
    } 

    return str;
}

//car c'est plus simple
void templateCopy(FILE* f){ 
    FILE* ftemp = NULL;
    char ch;
    ftemp = fopen("template.tem", "r+");
    if(ftemp == NULL){
        printf("[ERREUR] Le fichier template.txt est manquant.\n");//ohno
        exit(EXIT_FAILURE);
    }
    while((ch = fgetc(ftemp) ) != EOF){
        fputc(ch, f);
    }
    fclose(ftemp);
}