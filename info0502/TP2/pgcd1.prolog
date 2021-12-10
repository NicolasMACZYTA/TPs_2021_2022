pgcd(X,Y,R):-X<Y,pgcd(Y,X,R).
pgcd(X,Y,R):-Reste is X mod Y,Reste==0,R=Y.
pgcd(X,Y,R):-Reste is X mod Y,Reste\==0,pgcd(Y,Reste,R).