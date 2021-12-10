paon(magnifique).
paon(beau).
paon(bof).
paon(horrible).

combinepaon(X,Y):-X\=magnifique,Y\=horrible,paon(X),paon(Y).
