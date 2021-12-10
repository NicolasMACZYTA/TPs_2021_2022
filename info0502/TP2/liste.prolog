/* la syntax d'une liste est [X|L], avec X element de la liste et L la liste */
    /* X=a L=[b,c] */
    /* [a,b,c] */

    /* X=T L=[Y,Z] */
    /* [T,Y,Z] */

    /* X=2 L=[1,2] */
    /* [2,1,2] */

    /* X="toto" L=[titi,tata] */
    /* [toto,titi,tata] */

    /* X=[[0,1],[1,2]] L=[[a,b,c,]] */
    /* [[[0,1],[1,2]],[A,b,c]] */

    /* ["toto",X,a,1] */
    /* X="toto" L=[X,a,1] */

/* Quand on ecrit ca [a,b,c] */
/* prolog il voit [a|b|c|[]] */

affiche([]).
affiche([X|L]):-write(X), affiche(L). /*Les writes se font a la descente de la recursion*/

afficheR([]).
afficheR([X|L]):-afficheR(L), write(X). /*Les writes se font a la remonter de la recursion*/

affichePosI([]).
affichePosI([X]):-write(X).
affichePosI([X,_|L]):-write(X), affichePosI(L).

affichePosP([]).
affichePosP([_]).
affichePosP([_,Y|L]):-write(Y), affichePosP(L).

/* Compte le nombre d'elements dans une liste */
compte([],0).
compte([_|L],R):-compte(L,RN),R is RN+1.

compteD(L,T):-compteD(L,0,T).
compteD([],C,C).
compteD([_|L],C,T):-C1 is C+1, compteD(L,C1,T).

/* pour savoir si c'est un nombre ou pas */
/* number(X). */ /* not(number(X)). ou \+number(X) pour faire le contraire */

/* somme avec seulement des nombres */
somme([],0).
somme([X|L],S):-number(X), somme(L,SSL), S is SSL+X.
somme([X|L],S):-not(number(X)), somme(L,S).

appartientliste(_,[])-fail. /* arrive bout de liste, on peut aussi ne pas le mettre */
appartientliste(X,[X|_]). /* Si on le trouve X directement, gg */
appartientliste(X,[Y|L]):-X\=Y,appartientliste(X,L).

miniD([X|L],M):-miniD(L,X,M).
miniD([],X,X).
miniD([X|L],Y,M):-X<Y, miniD(L,X,M). /* si le min courant (X) est plus petit que Y alors on le prend */
miniD([X|L],Y,M):-X>Y, miniD(L,Y,M). /* si le min courant (X) est plus grand, on garde Y */

miniR([X],X). /* quand je suis sur le dernier element, c forcément lui le min */
miniR([X|L],X):-miniR(L,MSL),X<MSL. /* si je calcul le mini de R sur L et X < min de sous liste alors on remonte x */
miniR([X|L],MSL):-miniR(L,MSL),X>=MSL.

/* on appel avec miniD([1,3,-5],M). */
/* Si on ecrit [X|L] = [1,2,3] prolog va prndre en comtpe que X = 1 et L = [2,3] */


cc([],L,L).
cc([X|L1],L2,[X|L3]);-cc(L1,L2,L3).

supX(X,L1,L2).
supX(_,[],[]).
supX(X,[X|L1],L1):-supX(X,L1,L2).
supX(X,[Y|L1],[Y|L2]):-X\=Y, supX(X,L1,L2).

trieListe([],[]).
trieListe(L1,[M|L3]):-miniD(L1,M), supX(M,L1,L2), trieListe(L2,L3).

