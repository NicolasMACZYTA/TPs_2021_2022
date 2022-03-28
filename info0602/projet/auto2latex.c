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
    int nbNodes;

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
        if(strstr(chaine, "Q=")!=0){
            check=strchr(chaine,'q');
            while (check!=NULL) {
                nbNodes++;
                check=strchr(check+1,'q');
            }
            printf("Le nombres de nodes : %d\n",nbNodes);
        }
        if(strstr(chaine, "A=")!=0){
            strcpy(lAlphabet,chaine);
            delStr(lAlphabet,"A=");
            delStr(lAlphabet,"{");
            delStr(lAlphabet,"}");
            printf("L'alphabet : %s\n",lAlphabet);
        }
        if(strstr(chaine, "s=")!=0){
            strcpy(lStart,chaine);
            delStr(lStart,"s=");
            printf("Les nodes départ : %s\n",lStart);
        }
        if(strstr(chaine, "F=")!=0){
            strcpy(lEnd,chaine);
            delStr(lEnd,"F=");
            delStr(lEnd,"{");
            delStr(lEnd,"}");
            printf("Nodes accepteurs : %s\n",lEnd);
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

    //fprintf(fptr, "%s", sentence);

    fclose(fo);
    fclose(fn);
    return 0;


/*
    //récupération orienté
    fscanf(fo, "%s", chaine);
    fscanf(fo, "%d", &oriente);

    //récupération value
    fscanf(fo, "%s", chaine);
    fscanf(fo, "%d", &value);

    //récupération "DEBUT_DEF_ARETES"
    fscanf(fo, "%s", chaine);
    fscanf(fo, "%s", chaine);

  if(oriente != 0){
    while(strcmp(chaine, "FIN_DEF_ARETES") != 0){
      cellule *c = malloc(sizeof(cellule));
      fscanf(fo, "%s", char_sommet);
      initCellule(c, atoi(char_sommet));
      j = atoi(chaine);
      inserer(&g->l_adj[j], c);
      fscanf(fo, "%s", chaine);
    }
  }
  else{
    while(strcmp(chaine, "FIN_DEF_ARETES") != 0){
      cellule *c = malloc(sizeof(cellule));
      cellule *c2 = malloc(sizeof(cellule));
      fscanf(fo, "%s", char_sommet);
      initCellule(c, atoi(char_sommet));
      j = atoi(chaine);
      inserer(&g->l_adj[j], c);
      initCellule(c2, atoi(chaine));
      j = atoi(char_sommet);
      inserer(&g->l_adj[j], c2);
      fscanf(fo, "%s", chaine);
    }
  }

  g->nbSommet = sommet;
  g->oriente = oriente;
  g->value = value;
  fclose(fo);

  //Remplissage de la matrice
  for(int i=0; i<sommet ; i++){
    for(int j=0; j<sommet; j++){
      if(rechercher(&g->l_adj[i], j)){
        g->m_adj[i][j] = 1;
      }
      else{
        g->m_adj[i][j] = 0;
      }
    }
  }*/
}
