:-dynamic fibo/2. /*Permet au fibo/2 de changer la base de faits*/
fibo(0,0).
fibo(1,1).
fibo(N,R):-N>1, N1 is N-1, fibo(N1,R1), N2 is N-2, fibo(N2,R2), R is R1+R2, asserta(fibo(N,R)).
fiboI(N,I,U,V,R).
fiboI(0,0).
fiboI(1,1).
fiboI(N,R):-N>1, fiboI(N,1,0,1,R).
fiboI(N,N,_,V,V).
fiboI(N,I,U,V,R):I<N, W is U+V, I1 is I+1, fiboI(N,I1,V,W,R).