%{
#include "y.tab.h" 

int yylex();
void yyerror(const char *erreurMsg);
%}

ENTIER -?[0-9]+
DECIMALE -?[0-9]+.[0-9]+
BOOL true|false
CHAR .
STRING [\"]{CHAR}*[\"]
%%

{ENTIER} {
    return ENTIER;
};

{DECIMALE} {
    return DECIMALE;
};

{BOOL} {
    return BOOL;
};

{STRING} {
    return STRING;
};

: {
    return AFFECTATEUR;
};

, {
    return SEPARATEUR;
};

\{ {
    return DEBUT_OBJ;
};


\} {
    return FIN_OBJ;
};

\[ {
    return DEBUT_ARRAY;
};

\] {
    return FIN_ARRAY;
};

%%

void yyerror(const char *erreurMsg) {
  fprintf(stderr, "\n Erreur '%s' sur '%s'.\n", erreurMsg, yytext);
  exit(EXIT_FAILURE);
}