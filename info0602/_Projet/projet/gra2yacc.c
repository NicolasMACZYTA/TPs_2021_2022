#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charfuncs.h"

char* str_replace(char* string, const char* substr, const char* replacement);

int main(int argc, char *argv[]){
    FILE* fo = NULL;
    FILE* fn = NULL;
    FILE* fl = NULL;
    char chaine[100] = "";
    char lStart[50] = "";
    //char lAlphabet[50] = "";
    char lTerminaux[50] = "";
    char *check;
    char liens[10][20];
    char **liensFix;
    char tokens[50]="\0";
    liensFix=malloc(10*sizeof(char*));
    for(int i=0;i<10;i++){
        liensFix[i]=malloc(50*sizeof(char));
    }
    char alphabet[10][5];
    int nbSymb=0, nbLiens=0, nbA=0;
    char * tmp1=malloc(20*sizeof(char)); char * tmp2=malloc(20*sizeof(char));
    if(argc != 4){
        printf("[ERREUR] Il faut 3 arguments.\n");
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
    if((check = strrchr(argv[3],'.')) != NULL ) {
        if(strcmp(check,".l") != 0) {
            printf("[ERREUR] 3eme fichier n'est pas un .l\n");
            exit(EXIT_FAILURE);
        }
    }
    check = "";

    fo = fopen(argv[1], "r+");
    fn = fopen(argv[2], "w+");
    fl = fopen(argv[3], "w+");

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
            liens[nbLiens][(strlen(liens[nbLiens]))-2] = ';';
            liens[nbLiens][(strlen(liens[nbLiens]))-1] = '\0';

            replaceChar(liens[nbLiens],"->",":");
            //printf("%s\n",liens[nbLiens]);
            nbLiens++;
        }
    }

    for(int i = 0; i<nbLiens; i++){
        strcpy(liensFix[i],liens[i]);
    }

    for(int i = 0; i<nbLiens; i++){
        for(int j = 0; j<nbA; j++){
            for(int k = 0; k < strlen(liens[i]); k++){
                
                if(liens[i][k]==alphabet[j][0]){
                    if(liens[i][k]=='i'){
                        strcpy(tokens,"ID");
                    }
                }
            }
        }
        liensFix[i]=replaceSymbole(liens[i]);
    }
    printf("\n");
    

    //replaceChar(liensFix[i],"+","'+'");
    //replaceChar(liensFix[i],"*","'*'");
    //replaceChar(liensFix[i],"id","ID");

    for(int i = 0; i<3; i++){
        printf("%s\n",liensFix[i] );
    }

    /*if(strcmp(type,"AFNP") == 0){
        //ohbonvoilaquoi

        */
        fprintf(fn,"%c{\n#include <stdio.h>\n#include <stdlib.h>\nint yylex();\nvoid yyerror();\n%c}",37,37);
    /*
        
    
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
        
            fprintf(fn,"%ctoken %s\n",37,tokens);
        
        fprintf(fn,"\n%c%c\n",37,37);
        fprintf(fn,"S : %s\n",lStart);

        for(int i = 0; i<3; i++){
            fprintf(fn,"%s\n",liensFix[i] );
            fprintf(fn,"\n");
        }

        fprintf(fn,"\n%c%c\n",37,37);
        fprintf(fn,"void main()\n{\n    printf(\"\\nEnter C++ function definition to check: \\n\");\n    yyparse();\n }\n void yyerror()\n {\n  printf(\"\\nIncorrect function definition.\\n\");\n    exit(1);\n }");


        fprintf(fl,"%c{\n    #include <stdio.h>\n    #include \"y.tab.h\"\n%c}\n  \nalpha   \n    [A-Za-z_]\ndigit     \n  [0-9]\n%c%c\n[\\t \\n] ;\nvoid|bool|char|int|float|double           return TYPE;\n{alpha}({alpha}|{digit})                 return ID;\n              return yytext[0];\n%c%c\n int yywrap()\n{\n    return 1;\n}",37,37,37,37,37);

    fclose(fo);
    fclose(fn);
    fclose(fl);
    return 0;
}