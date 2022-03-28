%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STACK_SIZE 256

int pile[STACK_SIZE];
int indice = 0;
int tmp;
%}

ENTIER -?[0-9]+
OPERANDE "+"|"-"|"*"|"/"
COMMANDE "="|"SWAP"|"CLEAR"
%%

{ENTIER} {
    pile[indice] = atoi(yytext);
    indice++;
};
{OPERANDE} {
    if(indice < 2) printf("Pas assez de valeur pour effectuer l'opération %s !", yytext);
    else{
        switch(*yytext){
            case '+':
                printf("%d + %d = %d", pile[indice - 2], pile[indice - 1], pile[indice - 2] + pile[indice - 1]);
                pile[indice - 2] = pile[indice - 2] + pile[indice - 1];
                indice --;
                break;
            case '-':
                printf("%d - %d = %d", pile[indice - 2], pile[indice - 1], pile[indice - 2] - pile[indice - 1]);
                pile[indice - 2] = pile[indice - 2] - pile[indice - 1];
                indice --;
                break;
            case '*':
                printf("%d * %d = %d", pile[indice - 2], pile[indice - 1], pile[indice - 2] * pile[indice - 1]);
                pile[indice - 2] = pile[indice - 2] * pile[indice - 1];
                indice --;
                break;
            case '/':
                if(pile[indice - 1] != 0){
                    printf("%d / %d = %d", pile[indice - 2], pile[indice - 1], pile[indice - 2] / pile[indice - 1]);
                    pile[indice - 2] = pile[indice - 2] / pile[indice - 1];
                    indice --;
                }
                else{
                    printf("Division par 0 !!!");
                }
                break;
        }
    }
};

{COMMANDE} {
    if(!strcmp(yytext, "=")){
        if(indice == 0) printf("La pile est vide.");
        else{
            printf("Contenu de la pile : ");
            for(int i = 0; i < indice; i++){
                printf("%d ", pile[i]);
            }
        } 
    }
    else if(!strcmp(yytext, "SWAP")){
        if(indice < 1) printf("Pas assez de valeur pour effectuer l'opération %s !", yytext);
        else{
            tmp = pile[indice - 1];
            pile[indice - 1] = pile[indice - 2];
            pile[indice - 2] = tmp;
        }
    }
    else{
        indice = 0;
    }
};

%%

int main() {
  yylex();
  return EXIT_SUCCESS;
}
