pgcd(X,Y,R):-number(X),number(Y),X<Y,pgcd(Y,X,R).
pgcd(X,Y,R):-number(X),number(Y),Reste is X mod Y,Reste==0,R=Y.
pgcd(X,Y,R):-number(X),number(Y),Reste is X mod Y,Reste\==0,pgcd(Y,Reste,R).