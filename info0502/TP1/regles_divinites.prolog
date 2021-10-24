:-include('divinites').

enfant(X,Y):-fruit_de(X,Y).
enfant(X,Y):-fruit_de(X,Y,_).
enfant(X,Y):-fruit_de(X,_,Y).

parent(X,Y):-enfant(Y,X). /*X est parent de Y si Y est enfant de X*/
pere(X,Y):-enfant(Y,X),male(X). /*X est pere de Y si Y est enfant de X et X est male*/

mere(X,Y):-enfant(Y,X),femelle(X).
grandpere(X,Y):-pere(X,P),enfant(Y,P).
grandmere(X,Y):-mere(X,P),parent(P,Y).
frere(X,Y):-parent(X,P),parent(Y,P),male(X),X\=Y.
soeur(X,Y):-parent(X,P),parent(Y,P),femelle(X),X\=Y.
tante(X,Y):-soeur(X,P),parent(P,X).
oncle(X,Y):-frere(X,P),parent(P,X).
filsde(X,Y):-enfant(X,Y),male(X).
fillede(X,Y):-enfant(X,Y),femelle(X).

cousin(X,Y):-filsde(X,O),oncle(O,Y).
cousin(X,Y):-filsde(X,T),tante(T,Y).
cousine(X,Y):-fillede(X,O),oncle(O,Y).
cousine(X,Y):-fillede(X,T),tante(T,Y).

ancetre(X,Y):-parent(X,Y).
ancetre(X,Y):-parent(A,Y),ancetre(X,A).