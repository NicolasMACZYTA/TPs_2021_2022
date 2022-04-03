#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charfuncs.h"

char* str_replace(char* string, const char* substr, const char* replacement);

int main(int argc, char *argv[]){
    FILE* fo = NULL;
    FILE* fn = NULL;
    char chaine[100] = "";
    char type[6] = "";
    char lStart[50] = "";
    char lEnd[50] = "";
    char lAlphabet[50] = "";
    char lTerminaux[50] = "";
    char *check;
    char liens[10][20];
    int nbNodes=0, nbLiens=0;

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
    fscanf(fo, "%s", type);

    //test pour trouver le type
    if(strcmp(type,"GRAMMAIRE") == 0){
        printf("GRAMMAIRE\n");
    }else{
        printf("[ERREUR] Je connais pas.\n");
        exit(EXIT_FAILURE);
    }

    templateCopy(fn);

    fprintf(fn,"\n\\noindent Le contenu du fichier .aut :\n\\begin{lstlisting}[mathescape,frame=single]");
    fprintf(fn,"\n%s",type);

    if(strcmp(type,"AFNP") == 0){
        printf("Nodes accepteurs : Pile vide\n");
    }
    while (fscanf(fo,"%s", chaine) == 1){
        //Pour ajouter le contenu du fichier dans le .tex
        replaceChar(chaine,"ε","$\\epsilon$");//agrougrou
        fprintf(fn,"\n%s",chaine);
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
        if(strstr(chaine, "N=")!=0){
            check=strchr(chaine,',');
            nbNodes = compteChar(check, ',')+1;
            printf("Le nombres de nodes : %d\n",nbNodes);
        }


        //L'alphabet utiliser
        if(strstr(chaine, "T=")!=0){
            strcpy(lTerminaux,chaine);
            delStr(lTerminaux,"{");
            delStr(lTerminaux,"}");
            delStr(lTerminaux,"T=");
            printf("les symboles terminaux : %s\n",lTerminaux);
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
        if(strstr(chaine, "S=")!=0){
            strcpy(lStart,chaine);
            delStr(lStart,"S=");
            printf("La node de départ : %s\n",lStart);
        }
        //Les liens
        if(strstr(chaine, "(")!=0){
            strcpy(liens[nbLiens],chaine);
            //str_replace(liens[nbLiens],"->",": ");
            printf("%s\n",liens[nbLiens]);
            nbLiens++;
        }
    }

    if(strcmp(type,"AFNP") == 0){
        //ohbonvoilaquoi
        fprintf(fn,"\n\\end{lstlisting}\n\nDans le cours, nous n'avons pas vu la représentation sous forme de graphe d'un automate à pile.\n\\end{document}");
    }else{
        fprintf(fn,"\n\\end{lstlisting}\nCe qui donne l'automate suivant :\n\\begin{figure}[ht]\n  \\centering\n  \\begin{tikzpicture})\n");
        for(int i = 0; i<nbNodes; i++){
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
    }

    fclose(fo);
    fclose(fn);
    return 0;
}

char* str_replace(char* string, const char* substr, const char* replacement) {
	char* tok = NULL;
	char* newstr = NULL;
	char* oldstr = NULL;
	int   oldstr_len = 0;
	int   substr_len = 0;
	int   replacement_len = 0;

	newstr = strdup(string);
	substr_len = strlen(substr);
	replacement_len = strlen(replacement);

	if (substr == NULL || replacement == NULL) {
		return newstr;
	}

	while ((tok = strstr(newstr, substr))) {
		oldstr = newstr;
		oldstr_len = strlen(oldstr);
		newstr = (char*)malloc(sizeof(char) * (oldstr_len - substr_len + replacement_len + 1));

		if (newstr == NULL) {
			free(oldstr);
			return NULL;
		}

		memcpy(newstr, oldstr, tok - oldstr);
		memcpy(newstr + (tok - oldstr), replacement, replacement_len);
		memcpy(newstr + (tok - oldstr) + replacement_len, tok + substr_len, oldstr_len - substr_len - (tok - oldstr));
		memset(newstr + oldstr_len - substr_len + replacement_len, 0, 1);

		//free(oldstr);
	}

	//free(string);

	return newstr;
}