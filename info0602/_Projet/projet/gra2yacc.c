#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charfuncs.h"

char* str_replace(char* string, const char* substr, const char* replacement);

int main(int argc, char *argv[]){
    FILE* fo = NULL;
    FILE* fn = NULL;
    char chaine[100] = "";
    char lStart[50] = "";
    char lAlphabet[50] = "";
    char lTerminaux[50] = "";
    char *check;
    char liens[10][20];
    char liensFix[10][50];
    char alphabet[10][5];
    int nbSymb=0, nbLiens=0, nbA=0;

    if(argc != 3){
        printf("[ERREUR] Il faut 2 arguments.\n");
        exit(EXIT_FAILURE);
    }
    if((check = strrchr(argv[1],'.')) != NULL ) {
        if(strcmp(check,".gra") != 0) {
            printf("[ERREUR] 1er fichier n'est pas un .gra\n");
            exit(EXIT_FAILURE);
        }
    }
    if((check = strrchr(argv[2],'.')) != NULL ) {
        if(strcmp(check,".y") != 0) {
            printf("[ERREUR] 2eme fichier n'est pas un .y\n");
            exit(EXIT_FAILURE);
        }
    }
    check = "";

    fo = fopen(argv[1], "r+");
    fn = fopen(argv[2], "w+");

    //récupération type
    fscanf(fo, "%s", chaine);

    //test pour trouver le type
    if(strcmp(chaine,"GRAMMAIRE") == 0){
        printf("GRAMMAIRE\n");
    }else{
        printf("[ERREUR] Je connais pas.\n");
        exit(EXIT_FAILURE);
    }

    //templateCopy(fn);

    //fprintf(fn,"\n\\noindent Le contenu du fichier .aut :\n\\begin{lstlisting}[mathescape,frame=single]");
    //fprintf(fn,"\n%s",type);

    while(fgets(chaine, 100, fo) != NULL){
        //Pour ajouter le contenu du fichier dans le .y

        //Symboles
        if(strstr(chaine, "N=")!=0){
            check=strchr(chaine,',');
            nbSymb = compteChar(check, ',')+1;
            printf("Le nombres de symboles : %d\n",nbSymb);
        }

        //L'alphabet utiliser
        if(strstr(chaine, "T=")!=0){
            strcpy(lTerminaux,chaine);
            delStr(lTerminaux,"{");
            delStr(lTerminaux,"}");
            delStr(lTerminaux,"T=");
            printf("Les symboles terminaux : %s\n",lTerminaux);
            const char *delim = ",\n";
            char *s = lTerminaux;
            size_t n = 0, len;
            //ouverture de la porte des etoiles non programmer
            for(s = strtok (s, delim); s && n < 10; s = strtok (NULL, delim)){
                if ((len = strlen (s)) < 5){
                    strcpy(alphabet[n++], s);
                    nbA++;
                }else{
                    printf("[ERREUR] Un charactere de l'alphabet est trop grand.\n");
                    exit(EXIT_FAILURE);
                }
            }
        }

        //Node de départ
        if(strstr(chaine, "S=")!=0){
            strcpy(lStart,chaine);
            delStr(lStart,"S=");
            printf("La node de départ : %s\n",lStart);
        }

        //Les liens
        if(strstr(chaine, "(")!=0 && strstr(chaine, "{")==0){
            strcpy(liens[nbLiens],chaine);
            printf("%s",liens[nbLiens]);
            if(liens[nbLiens][0] == ' '){
                memmove(liens[nbLiens], liens[nbLiens]+3, strlen(liens[nbLiens]));//J'aime pas les (
            }
            liens[nbLiens][(strlen(liens[nbLiens]))-3] = '\0';
            replaceChar(liens[nbLiens],"->",":");
            //printf("%s\n",liens[nbLiens]);
            nbLiens++;
        }
    }

    for(int i = 0; i<nbLiens; i++){
        strcpy(liensFix[i],liens[i]);/
    }

    for(int i = 0; i<nbLiens; i++){
        for(int j = 0; j<nbA; j++){
            for(int k = 0; k < strlen(liens[i]); k++){
                //liens[i][k] //char liste
                //alphabet[j] //char alphabet
                if(liens[i][k]==alphabet[j][0]){
                    if(liens[i][k]=='+'){
                        replaceChar(liensFix[i],"+","'+'");
                    }else if(liens[i][k]=='*'){
                        replaceChar(liensFix[i],"*","'*'");
                    }else if(liens[i][k]=='i'){
                        replaceChar(liensFix[i],"id","ID");
                    }
                }
            }
        }
    }
    printf("\n");
    

    //replaceChar(liensFix[i],"+","'+'");
    //replaceChar(liensFix[i],"*","'*'");
    //replaceChar(liensFix[i],"id","ID");

    for(int i = 0; i<3; i++){
        printf("%s\n",liensFix[i]);
    }

    /*if(strcmp(type,"AFNP") == 0){
        //ohbonvoilaquoi
        fprintf(fn,"\n\\end{lstlisting}\n\nDans le cours, nous n'avons pas vu la représentation sous forme de graphe d'un automate à pile.\n\\end{document}");
    }else{
        fprintf(fn,"\n\\end{lstlisting}\nCe qui donne l'automate suivant :\n\\begin{figure}[ht]\n  \\centering\n  \\begin{tikzpicture})\n");
        for(int i = 0; i<nbSymb; i++){
            char iC[10];
            sprintf(iC, "%d", i);
            fprintf(fn,"\\node[state");
            if(strstr(lStart, iC)!=0){
                fprintf(fn,", initial] (q%d) {$q_%d$};\n",i,i);
            }else if(strstr(lEnd, iC)!=0){
                fprintf(fn,", accepting, right of=q%d] (q%d) {$q_%d$};\n",i-1,i,i);
            }else{
                fprintf(fn,", right of=q%d] (q%d) {$q_%d$};\n",i-1,i,i);
            }
        }
        fprintf(fn,"\\draw");
        for(int i = 0; i<nbLiens; i++){
            fprintf(fn,"\n");
            if(liens[i][4] == '$'){
                if(compteChar(liens[i],liens[i][2]) == 2){
                    fprintf(fn,"(q%c) edge[loop below] node{$\\epsilon$} (q%c)",liens[i][2],liens[i][16]);
                }else{
                    if((abs((liens[i][2]-'0')-(liens[i][16]-'0')))==1){
                        fprintf(fn,"(q%c) edge[bend right, below] node{$\\epsilon$} (q%c)",liens[i][2],liens[i][16]);
                    }else{
                        fprintf(fn,"(q%c) edge[bend left, above] node{$\\epsilon$} (q%c)",liens[i][2],liens[i][16]);
                    }
                }
            }else{
                if(compteChar(liens[i],liens[i][2]) == 2){
                    fprintf(fn,"(q%c) edge[loop below] node{%c} (q%c)",liens[i][2],liens[i][4],liens[i][7]);
                }else{
                    if((abs((liens[i][2]-'0')-(liens[i][7]-'0')))==1){
                        fprintf(fn,"(q%c) edge[bend right, below] node{%c} (q%c)",liens[i][2],liens[i][4],liens[i][7]);
                    }else{
                        fprintf(fn,"(q%c) edge[bend left, above] node{%c} (q%c)",liens[i][2],liens[i][4],liens[i][7]);
                    }
                }
            }
        }
        fprintf(fn,";\n  \\end{tikzpicture}\n  \\caption{Automate}\n\\end{figure}\n\\end{document}");
    }*/

    fclose(fo);
    fclose(fn);
    return 0;
}