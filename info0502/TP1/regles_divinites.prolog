:-include('divinites').

enfant(X,Y):-fruit_de(X,Y).
enfant(X,Y):-fruit_de(X,Y,_).
enfant(X,Y):-fruit_de(X,_,Y).

parent(X,Y):-enfant(Y,X). /*X est parent de Y si Y est enfant de X*/
pere(X,Y):-enfant(Y,X),male(X). /*X est pere de Y si Y est enfant de X et X est male*/

mere(X,Y):-enfant(Y,X),femelle(X).
grandpere(X,Y):-pere(X,P),enfant(Y,P). /*X est grandpere de Y si X est pere de P et Y est enfant de P*/
grandmere(X,Y):-mere(X,P),parent(P,Y).
frere(X,Y):-parent(X,P),parent(Y,P),male(X),X\=Y.
%frere(X,Y):-male(X),pere(P,X),pere(P,Y),mere(M,X),mere(M,Y),X\=Y.
soeur(X,Y):-parent(X,P),parent(Y,P),femelle(X),X\=Y.
%soeur(X,Y):-femelle(X),pere(P,X),pere(P,Y),mere(M,X),mere(M,Y),X\=Y.
tante(X,Y):-soeur(X,P),parent(P,X).
%oncle(X,Y):-soeur(X,Z),enfant(Y,Z).
oncle(X,Y):-frere(X,P),parent(P,X).
%oncle(X,Y):-frere(X,Z),enfant(Y,Z).
filsde(X,Y):-enfant(X,Y),male(X).
fillede(X,Y):-enfant(X,Y),femelle(X).

cousin(X,Y):-filsde(X,O),oncle(O,Y).
cousin(X,Y):-filsde(X,T),tante(T,Y).
cousine(X,Y):-fillede(X,O),oncle(O,Y).
cousine(X,Y):-fillede(X,T),tante(T,Y).

ancetre(X,Y):-parent(X,Y).
ancetre(X,Y):-parent(A,Y),ancetre(X,A).

famille(X,Y):-pere(X,Y),print(X),print("est le pere de "),print(Y).