%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(const char *erreurMsg);
char res[64];
%}

%token ENTIER
%left '+'
%left '-'
%left '/'
%left '*'
%%

programme: expression '.' {
           printf(res, $1);
      }
      |
      ;



expression: ENTIER
      | '-' expression {
        $$ = -$2;
      }
      | expression '+' expression {
        $$ = $1 + $3;
      }
      | expression '-' expression {
        $$ = $1 - $3;
      }
      | expression '*' expression {
        $$ = $1 * $3;
      }
      | expression '/' expression{
        if($3 != 0){
          $$ = $1 / $3;
        }
        else {
          strcpy(res, "Erreur division par 0\0");
        }
      };

%%

int main(void) {
  strcpy(res, "=%d\0");
  yyparse();
  return EXIT_SUCCESS;
}
