%{
#include "y.tab.h" 

int yylex();
void yyerror(const char *erreurMsg);
%}

ENTIER -?[0-9]+
BOOL true|false
CHAR [a-Z|1-9|-|_]
STRING {CHAR}*
TYPE [entier|bool]
%%

{ENTIER} {
    return ENTIER;
};

{BOOL} {
    return BOOL;
};

{STRING} {
    return STRING;
};

= {
    return AFFECTATEUR;
};

: {
    return TYPE_SETTER
}

, {
    return SEPARATEUR;
};

\( {
    return PAREN_OUVRANT;
};


\) {
    return PAREN_FERMANT;
};

proc {
    return PROC;
}

fonc {
    return FONC;
}

si {
    return SI;
}

sinon {
    return SINON;
}

finsi {
    return FINSI;
}

tantque {
    return TANTQUE;
}

fintantque {
    return FINTANTQUE;
}



%%

void yyerror(const char *erreurMsg) {
  fprintf(stderr, "\n Erreur '%s' sur '%s'.\n", erreurMsg, yytext);
  exit(EXIT_FAILURE);
}