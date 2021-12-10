/*Trés limiter car stackdump au dessus de 31*/

fibo(0,0).
fibo(1,1).
fibo(N,R):-N>1, N1 is N-1, fibo(N1,R1), N2 is N-2, fibo(N2,R2), R is R1+R2.
