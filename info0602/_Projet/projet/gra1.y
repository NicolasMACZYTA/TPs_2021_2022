%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror();
%}%token ID

%%
S : E
E : E '+' T | T;

T : T '*' F | F;

F : ID | '(' E ')';


%%
void main()
{
    printf("\nEnter C++ function definition to check: \n");
    yyparse();
 }
 void yyerror()
 {
  printf("\nIncorrect function definition.\n");
    exit(1);
 }