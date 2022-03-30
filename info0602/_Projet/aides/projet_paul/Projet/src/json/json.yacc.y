%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "json.h"

#define YYSTYPE char*

int yylex();
void yyerror(const char *erreurMsg);

/* Déclaration de l'objet "principal" */
json_object_t* current_object;
int is_res_created = 0;

%}

%token ENTIER
%token DECIMALE
%token BOOL
%token CHAR
%token STRING

%left DEBUT_OBJ
%left FIN_OBJ
%left DEBUT_ARRAY
%left FIN_ARRAY
%left AFFECTATEUR
%left SEPARATEUR

%%

OBJET: DEBUT_OBJ MEMBRES FIN_OBJ{
    json_object_t* tmp;
    //tmp->pere = current_object;
    //json_add_object(current_object, $$);

};

ARRAY: DEBUT_ARRAY VALEURS FIN_ARRAY 
    | DEBUT_ARRAY MEMBRES FIN_ARRAY
    | DEBUT_ARRAY VALEUR FIN_ARRAY 
    | DEBUT_ARRAY MEMBRE FIN_ARRAY
    ;

MEMBRES: MEMBRES SEPARATEUR MEMBRE
    | MEMBRE SEPARATEUR MEMBRE
    | MEMBRE
    ;

MEMBRE: CHAMP
    |   ARRAY
    |   OBJET
    ;

CHAMP: STRING AFFECTATEUR VALEUR {
        printf("test %s",$$);
        //$$ = json_create_field($1, atoi($3));
    }
    | STRING AFFECTATEUR ARRAY
    | STRING AFFECTATEUR OBJET
    ;

VALEURS: VALEURS SEPARATEUR VALEUR
    | VALEUR SEPARATEUR VALEUR
    ;

VALEUR: ENTIER{
        printf("test 1 : %s", yylval);
        $$ = yylval;
    }
    | DECIMALE{
        $$ = yylval;
    }
    | BOOL{
        if(strcmp(yylval,"false"))
            $$ = "true";
        else{
            $$ = "false";
        }
    }
    | STRING{
        $$ = yylval;
    }
    ;
%%

int main() {
  yyparse();
  //json_afficher(current_object);
  return EXIT_SUCCESS;
}