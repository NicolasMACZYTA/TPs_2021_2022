#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charfuncs.h"
#include "automate.h"

int main(int argc, char *argv[]){
    FILE* f = NULL;
    char chaine[100] = "";
    char liens[10][20];
    int nbLiens=0;
    int first=1;
    int final=3;
    static int ll=0,rl=0;
    char d;
    char *check;

    
    if(argc != 2){
        printf("[ERREUR] Il faut un fichier.\n");
        exit(EXIT_FAILURE);
    }
    if((check = strrchr(argv[1],'.')) != NULL ) {
        if(strcmp(check,".gra") != 0) {
            printf("[ERREUR] 1er fichier n'est pas un .gra\n");
            exit(EXIT_FAILURE);
        }
    }
    check = "";

    f = fopen(argv[1], "r+");
    fscanf(f, "%s", chaine);

    //while(fscanf(f,"%s", chaine) == 1){
    while(fgets(chaine, 100, f) != NULL){
        //Les liens
        if(strstr(chaine, "(")!=0 && strstr(chaine, "{")==0){
            strcpy(liens[nbLiens],chaine);
            printf("%s",liens[nbLiens]);
            delStr(liens[nbLiens]," ");
            delStr(liens[nbLiens],"'");
            if (liens[nbLiens][0] == '('){
                memmove(liens[nbLiens], liens[nbLiens]+1, strlen(liens[nbLiens]));//J'aime pas les (
            }
            replaceChar(liens[nbLiens],"->","=");
            printf("%s",liens[nbLiens]);
            nbLiens++;
        }
    }
    printf("Il y a %d liens\n",nbLiens);

    for(int k=0; k<nbLiens; k++){
        int i=0, checktype=0;
        char delim[] = "=";
        char c;
        int type=-1;
        char *lhs = strtok(liens[k], delim);
        char *rhs= strtok(NULL, delim);
        while(1){
            for(i=0; i<strlen(lhs) ;i++){
                c = lhs[i];
                if(isupper(c)){
                    checktype++;
                }
            }
            if(checktype>=1){
                type++;
                break;
            }
        }
        if(strlen(lhs)<=strlen(rhs) && type>-1){
            if(rhs[0] == '0'){
                d = lhs[0];
            }
            int type1=1;
            if(!first){
                for(int j=0; j<strlen(rhs); j++){
                    if(rhs[j]==d){
                        type1=0;
                        break;
                    }
                }
            }
            first = 0;
            if(type1){
                type++;
            }
        }

        if(strlen(lhs)==1 && type>0){
            type++;
        }
        
        if(isupper(rhs[0]) && type>1 && rl==0 ){
            checktype = 0;
            for(i=1; i<strlen(rhs); i++){
                c = rhs[i];
                if(isupper(c)){
                    checktype++;
                }
            }
            if (checktype==0){
                ll = 1;
                type++;
            }
        }else if(isupper(rhs[strlen(rhs)-1]) && type>1 && ll==0){
            checktype=0;
            for (i=0; i<strlen(rhs)-1; i++){
                c = rhs[i];
                if(isupper(c)){
                    checktype++;
                }
            }
            if(checktype==0){
                rl=1;
                type++;
            }
        }else if(type>1){
            while(1){
                checktype = 0;
                for(i=0; i<strlen(rhs); i++){
                    c = rhs[i];
                    if(isupper(c)){
                        checktype++;
                    }
                }
                if(checktype==0){
                    type++;
                    break;
                }
                break;
            }
        }
        if(final > type){
            final = type;
        }
    }

    printf("\nLa grammaire est de type %d : ",final);
    switch(final){
        case 0:
            printf("pas de restrictions\n");
            break;
        case 1:
            printf("grammaire contextuelle\n");
            break;
        case 2:
            printf("grammaire hors-contexte\n");
            break;
        case 3:
            printf("grammaire reguliere\n");
            break;
        default:
            printf("c'est pas normal\n");
            break;
    }

    return 0;
}