econome('A').
econome('B').
econome('C').

energivore('E').
energivore('F').
energivore('G').

%1
economeEnergivore(X,Y):-econome(X),energivore(Y).

%2
duoEnergivore(X,Y):-X\=Y,energivore(X),energivore(Y).