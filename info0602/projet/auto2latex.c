#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

//fonction pour supprimer le non nécessaire
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

int main(int argc, char *argv[]){
    FILE* fo = NULL;
    FILE* fn = NULL;
    FILE* ftemp = NULL;
    char chaine[MAX] = "";
    char type[6] = "";
    char lStart[50] = "";
    char lEnd[50] = "";
    char lAlphabet[50] = "";
    char *check;
    char ch;
    char liens[10][20];
    int nbNodes, nbLiens=0;

    if(argc != 3){
        printf("[ERREUR] Il faut 2 fichiers.\n");
        return 0;
    }
    if((check = strrchr(argv[1],'.')) != NULL ) {
        if(strcmp(check,".aut") != 0) {
            printf("[ERREUR] 1er fichier n'est pas un .aut\n");
            return 0;
        }
    }
    if((check = strrchr(argv[2],'.')) != NULL ) {
        if(strcmp(check,".tex") != 0) {
            printf("[ERREUR] 2eme fichier n'est pas un .tex\n");
            return 0;
        }
    }
    check = "";

    fo = fopen(argv[1], "r+");
    fn = fopen(argv[2], "w+");

    if(fo == NULL){
        printf("[ERREUR] Impossible d'ouvrir le fichier.\n");
        return 0;
    }

    //récupération type
    fscanf(fo, "%s", type);

    //test pour trouver le type
    if(strcmp(type,"AFD") == 0){
        printf("AFD !\n");
    }else if(strcmp(type,"AFN") == 0){
        printf("AFN !\n");
    }else if(strcmp(type,"AFNP") == 0){
        printf("AFNP !\n");
    }else{
        printf("[ERREUR] Je connais pas.\n");
        return 0;
    }

    while (fscanf(fo,"%s", chaine) == 1){
        //Nodes qui sont accepteur
        if(strcmp(type,"AFD") == 0 || strcmp(type,"AFN") == 0){
            if(strstr(chaine, "F=")!=0){
                strcpy(lEnd,chaine);
                delStr(lEnd,"F=");
                delStr(lEnd,"{");
                delStr(lEnd,"}");
                printf("Nodes accepteurs : %s\n",lEnd);
            }
        //Sauf pour les AFNPiles
        }else{
            printf("Nodes accepteurs : Pile vide\n");
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
            delStr(lAlphabet,"A=");
            delStr(lAlphabet,"{");
            delStr(lAlphabet,"}");
            printf("L'alphabet : %s\n",lAlphabet);
        }
        //Node de départ
        if(strstr(chaine, "s=")!=0){
            strcpy(lStart,chaine);
            delStr(lStart,"s=");
            printf("La node de départ : %s\n",lStart);
        }
        if(strstr(chaine, "(")!=0){
            strcpy(liens[nbLiens],chaine);
            delStr(liens[nbLiens]," ");
            printf("%s\n",liens[nbLiens]);
            nbLiens++;
        }
    }
    
    ftemp = fopen("template.txt", "r+");
    if(ftemp == NULL){
        printf("[ERREUR] Le fichier template.txt est manquant.\n");
        return 0;
    }
    while((ch = fgetc(ftemp) ) != EOF){
        fputc(ch, fn);
    }
    fclose(ftemp);

    fprintf(fn,"\n\\noindent Le fichier \\texttt{%s} :\n\\begin{lstlisting}[mathescape,frame=single]\n",argv[1]);
    fseek(fo, 0, SEEK_SET);
    while((ch = fgetc(fo) ) != EOF){
        fputc(ch, fn);
    }
    fprintf(fn,"\n\\end{lstlisting}\nCe qui donne l'automate suivant :\n\\begin{figure}[ht]\n  \\centering\n  \\begin{tikzpicture})\n");
    for(int i = 0; i<nbNodes; i++){
        char iC[3];
        sprintf(iC, "%d", i);
        fprintf(fn,"\\node[state");
        if(strstr(lStart, iC)!=0){
            fprintf(fn,", initial] (q%d) {$q_%d$};\n",i,i);
        }else if(strstr(lEnd, iC)!=0){
            fprintf(fn,", accepting] (q%d) {$q_%d$};\n",i,i);
        }else{
            fprintf(fn,"] (q%d) {$q_%d$};\n",i,i);
        }
    }
    fprintf(fn,"\\draw\n");
    for(int i = 0; i<nbLiens; i++){
        if(compteChar(liens[i],liens[i][2]) == 2){
            printf("DOUBLE\n");
            fprintf(fn,"(q%c) edge[loop below] node{%c} (q%c)\n",liens[i][2],liens[i][4],liens[i][7]);
        }else{
            printf("SOLO\n");
            if(i%2 == 0){
                fprintf(fn,"(q%c) edge[below] node{%c} (q%c)\n",liens[i][2],liens[i][4],liens[i][7]);
            }else{
                fprintf(fn,"(q%c) edge[above] node{%c} (q%c)\n",liens[i][2],liens[i][4],liens[i][7]);
            }
        }
    }
    fprintf(fn,"  \\end{tikzpicture}\n  \\caption{Fichier \texttt{%s}}\n\\end{figure}",argv[1]);

    fclose(fo);
    fclose(fn);
    return 0;
}
