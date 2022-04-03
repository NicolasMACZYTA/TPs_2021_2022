#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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

char *replaceSymbole(char *str){
    char * res=malloc(126*sizeof(char));
    int i = 0, j = 0;
    for(i=0;i<strlen(str);)
    {
        if(str[i]=='+'||str[i]=='*'){
            res[j]='\'';
            j++;
            res[j]=str[i];
            j++;
            res[j]='\'';
            j++;
            i++;
        
        }else if(str[i]=='i'&&str[i+1]=='d'){
            res[j]='I';
            j++;
            i++;
            res[j]='D';
            i++;
            j++;
        }else{
            res[j]=str[i];
            i++;
            j++;
        }
    }
    

    return res;
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

char** str_split(char* a_str, const char a_delim){
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp){
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result){
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token){
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}