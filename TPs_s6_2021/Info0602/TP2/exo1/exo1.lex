/* 
lex ./ex1.lex
gcc ./lex.yy.c -o ex1 -ll
*/

%{
    #include <stdio.h>
    #include <stdlib.h>

    #include "pile.h"

    int a, b, tmpa, tmpb;
    pile* p;
%}

CHIFFRE  [0-9]
ENTIER   (\-)?{CHIFFRE}+
OPERANDE (\-|\+|\*|\/)

/* Pour accepter les réels : REEL {ENTIER}(\.({ENTIER})+)?
   (pas de modification pour les opérandes, elles auront les mêmes effets) */

%%

{ENTIER} empiler(p, atoi(yytext));

{OPERANDE} {
    b = depiler(p), a = depiler(p);
    switch(yytext[0]) {
        case '-': empiler(p, a-b); break;
        case '+': empiler(p, a+b); break;
        case '*': empiler(p, a*b); break;
        case '/': empiler(p, a/b); break;
    }
}

\n {
    if(p->pos > 0)
        fprintf(stderr, "Pile non vide (pos:%d)\n", p->pos);
    else if(p->pos == 0)
        printf("\n\rRésultat :  %d\n", p->tab[0]);
    vider_pile(p);
}

= afficher_pile(p);
CLEAR vider_pile(p);
SWAP {
    if(p->pos > 0) {
        tmpb = depiler(p);
        tmpa = depiler(p);
        empiler(p, tmpb);
        empiler(p, tmpa);
    }
}

%%

int main() {
    p = initialiser(10);
    yylex();
    return EXIT_SUCCESS;
}