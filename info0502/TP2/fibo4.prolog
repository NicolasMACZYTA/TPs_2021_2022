:-dynamic fibo/2. /*Permet au fibo/2 de changer la base de faits*/
fibo(0,0).
fibo(1,1).
fibo(N,R):-N>1, N1 is N-1, fibo(N1,R1), N2 is N-2, fibo(N2,R2), R is R1+R2, asserta(fibo(N,R)).
fiboI(N,I,U,V,R).
fiboI(0,0).
fiboI(1,1).
fiboI(N,R):-N>1, fiboI(N,0,1,R).
fiboI(N,_,V,V).
fiboI(N,U,V,R):N>1, N1 is N-1, W is U+V, fiboI(N,V,W,R).