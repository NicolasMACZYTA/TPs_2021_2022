%1
%identiquesDecal1D(L1,L2).

%2
estNombre(I,[I|_]):-number(I).
estNombre(I,[_|R]):-estNombre(I,R),number(I).

%3
truc([], [], []).
truc([X|L], [X|LA], LN) :- not(number(X)), truc(L, LA, LN).
truc([X|L], LA, [X|LN]) :- number(X), truc(L, LA, LN).