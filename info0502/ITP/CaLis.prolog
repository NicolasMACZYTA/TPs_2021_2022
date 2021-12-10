sommeFraction(N,S):-N>1, fraction(N,1,S).
fraction(0,R,S):-S=R.
fraction(N,R,S):-N>1, R is div(R,N), N1 is N-1, fraction(N1,R,S).
%pas beau

sommeVecteurs(0,0,0).
sommeVecteurs(V1,V2,VS):-R is V1+V2, VS=R.

truc([],[],[]).
truc([X],[X],[]).
truc([X,Y|L1],[X|L2],[Y|L3]):-truc(L1,L2,L3).
%ce predicat enleve la valeur X et Y de la liste L1, X de L2 et Y de L3 jusqu'a que toute les listes soit vides. truc([1,4,5,6],[1,5],[4,6]).

%un nom possible pour ce predicat serait suppressionListeDouble
