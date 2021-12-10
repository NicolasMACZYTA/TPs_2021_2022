%1
estPremier(2).
estPremier(N):-A is N mod 2, A \== 0.


%2
baseTrinaire(0):-!.
baseTrinaire(1,1):-!.
baseTrinaire(N,X):-number(N), N>1, A is N mod 3, B is N//3, baseTrinaire(B,C), atom_concat(C, A, X),!.
