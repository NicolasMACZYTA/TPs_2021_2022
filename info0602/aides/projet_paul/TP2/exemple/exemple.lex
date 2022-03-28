%{
#include <stdio.h>
#include <stdlib.h>

int numLigne = 1;
%}

CHIFFRE [0-9]

%%

{CHIFFRE} printf("Chiffre '%s'\n", yytext);
\n      numLigne++;
.       ;

%%

int main() {
  yylex();
  printf("Lignes %d\n", numLigne);
  return EXIT_SUCCESS;
}