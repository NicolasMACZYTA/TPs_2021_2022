hanoi(0,_,_,_). /*on prend comme depart 0*/
hanoi(N,A,B,C):-N>0, N1 is N-1, hanoi(N1,A,C,B), format("~a vers ~a ~c",[A,C]), hanoi(N1,B,A,C).
hanoi(N):-hanoi(N,"Tour A", "Tour B", "Tour C"). /*Juste pour l'affichage.*/


hanoiC(0,_,_,_,0). /*on prend comme depart 0*/
hanoiC(N,A,B,C,R):-N>0, N1 is N-1, hanoiC(N1,A,C,B,R1), hanoiC(N1,B,A,C,R2), R is R1+R2+1.
hanoiC(N,R):-hanoiC(N,_,_,_R).

