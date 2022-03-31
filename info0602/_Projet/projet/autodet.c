#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charfuncs.h"
#include "automate.h"

int main(int argc, char *argv[]){
    FILE* fin = NULL;
    FILE* fout = NULL;
    FILE* fvisu = NULL;
    char chaine[100] = "";
    char type[6] = "";
    char lStart[50] = "";
    char lEnd[50] = "";
    char lAlphabet[50] = "";
    char *check;
    char liens[10][20];
    int nbNodes=0, nbLiens=0;

    if(argc != 4){
        printf("[ERREUR] Il faut 3 arguments.\n");
        exit(EXIT_FAILURE);
    }
    if((check = strrchr(argv[1],'.')) != NULL ) {
        if(strcmp(check,".aut") != 0) {
            printf("[ERREUR] 1er fichier n'est pas un .aut\n");
            exit(EXIT_FAILURE);
        }
    }
    if((check = strrchr(argv[2],'.')) != NULL ) {
        if(strcmp(check,".aut") != 0) {
            printf("[ERREUR] 2em fichier n'est pas un .aut\n");
            exit(EXIT_FAILURE);
        }
    }
    if((check = strrchr(argv[3],'.')) != NULL ) {
        if(strcmp(check,".tex") != 0) {
            printf("[ERREUR] 3eme fichier n'est pas un .tex\n");
            exit(EXIT_FAILURE);
        }
    }
    check = "";

    fin = fopen(argv[1], "r+");
    fout = fopen(argv[2], "w+");
    fvisu = fopen(argv[3], "w+");

    //récupération type
    fscanf(fin, "%s", type);

    //test pour trouver le type
    if(strcmp(type,"AFN") == 0){
        printf("AFN\n");
    }else{
        printf("[ERREUR] Ceci n'est pas un AFN.\n");
        exit(EXIT_FAILURE);
    }

    templateCopy(fvisu);

    fprintf(fvisu,"\n\\noindent Le contenu du fichier .aut :\n\\begin{lstlisting}[mathescape,frame=single]");
    fprintf(fvisu,"\n%s",type);

    while (fscanf(fin,"%s", chaine) == 1){
        //Pour ajouter le contenu du fichier dans le .tex
        replaceChar(chaine,"ε","$\\epsilon$");//agrougrou
        fprintf(fvisu,"\n%s",chaine);
        //Nodes qui sont accepteur
        if(strcmp(type,"AFD") == 0 || strcmp(type,"AFN") == 0){
            if(strstr(chaine, "F=")!=0){
                strcpy(lEnd,chaine);
                delStr(lEnd,"{");
                delStr(lEnd,"}");
                delStr(lEnd,"F=");
                printf("Nodes accepteurs : %s\n",lEnd);
            }
            //Sauf pour les AFNPiles
        }
        //Nodes totals
        if(strstr(chaine, "Q=")!=0){
            check=strchr(chaine,'q');
            nbNodes = compteChar(check, 'q');
            printf("Le nombres de nodes : %d\n",nbNodes);
        }
        //L'alphabet utiliser
        if(strstr(chaine, "A=")!=0){
            strcpy(lAlphabet,chaine);
            delStr(lAlphabet,"{");
            delStr(lAlphabet,"}");
            delStr(lAlphabet,"A=");
            printf("L'alphabet : %s\n",lAlphabet);
        }
        //Node de départ
        if(strstr(chaine, "s=")!=0){
            strcpy(lStart,chaine);
            delStr(lStart,"s=");
            printf("La node de départ : %s\n",lStart);
        }
        //Les liens
        if(strstr(chaine, "(")!=0){
            strcpy(liens[nbLiens],chaine);
            delStr(liens[nbLiens]," ");
            printf("%s\n",liens[nbLiens]);
            nbLiens++;
        }
    }
    
    /*
    fprintf(fvisu,"\n\\end{lstlisting}\nCe qui donne l'automate suivant :\n\\begin{figure}[ht]\n  \\centering\n  \\begin{tikzpicture})\n");
    for(int i = 0; i<nbNodes; i++){
        char iC[10];
        sprintf(iC, "%d", i);
        fprintf(fvisu,"\\node[state");
        if(strstr(lStart, iC)!=0){
            fprintf(fvisu,", initial] (q%d) {$q_%d$};\n",i,i);
        }else if(strstr(lEnd, iC)!=0){
            fprintf(fvisu,", accepting, right of=q%d] (q%d) {$q_%d$};\n",i-1,i,i);
        }else{
            fprintf(fvisu,", right of=q%d] (q%d) {$q_%d$};\n",i-1,i,i);
        }
    }
    fprintf(fvisu,"\\draw");
    for(int i = 0; i<nbLiens; i++){
        fprintf(fvisu,"\n");
        if(liens[i][4] == '$'){
            if(compteChar(liens[i],liens[i][2]) == 2){
                fprintf(fvisu,"(q%c) edge[loop below] node{$\\epsilon$} (q%c)",liens[i][2],liens[i][16]);
            }else{
                if((abs((liens[i][2]-'0')-(liens[i][16]-'0')))==1){
                    fprintf(fvisu,"(q%c) edge[bend right, below] node{$\\epsilon$} (q%c)",liens[i][2],liens[i][16]);
                }else{
                    fprintf(fvisu,"(q%c) edge[bend left, above] node{$\\epsilon$} (q%c)",liens[i][2],liens[i][16]);
                }
            }
        }else{
            if(compteChar(liens[i],liens[i][2]) == 2){
                fprintf(fvisu,"(q%c) edge[loop below] node{%c} (q%c)",liens[i][2],liens[i][4],liens[i][7]);
            }else{
                if((abs((liens[i][2]-'0')-(liens[i][7]-'0')))==1){
                    fprintf(fvisu,"(q%c) edge[bend right, below] node{%c} (q%c)",liens[i][2],liens[i][4],liens[i][7]);
                }else{
                    fprintf(fvisu,"(q%c) edge[bend left, above] node{%c} (q%c)",liens[i][2],liens[i][4],liens[i][7]);
                }
            }
        }
    }
    fprintf(fvisu,";\n  \\end{tikzpicture}\n  \\caption{Automate}\n\\end{figure}\n\\end{document}");
    */

    fclose(fin);
    fclose(fout);
    fclose(fvisu);
    return 0;
}
