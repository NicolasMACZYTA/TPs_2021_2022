affiche1E2([]).
affiche1E2([X]):-write(X).
affiche1E2([X,_|L]):-write(X), affiche1E2(L).

compte([],C,C).
compte([_|L],C,R):-C1 is C+1, compte(L,C1,R).
compte(L,R):-compte(L,0,R).

compte2([],0).
compte2([_|L],R):-compte2(L,RS),R is RS+1.

number(X).  /* not(number(X)). ou \+number(X) pour faire le contraire */

somme([],0).
somme([X|L],R):-somme(L,RS), R is RS+X.

somme2([],0).
somme2([X|L],R):-number(X), somme2(L,RS), R is RS+X.
somme2(X|L):-\+number(X), somme2(L,R).

%appartient(_,[]):-fail.
appartient(X,[X|_]).
appartient(X,[Y|L]):-X\=Y, appartient(X,L).



