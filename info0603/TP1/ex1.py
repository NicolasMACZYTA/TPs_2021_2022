from math import *
from random import *
import matplotlib.pyplot as plt
import numpy as np
import doctest as dt

def eDiviseurs(a):
    """renvoie l'ensemble des diviseurs positifs de A
    >>> eDiviseurs(60)
    {1, 2, 3, 4, 5, 6, 10, 12, 15, 20, 60, 30}
    >>> eDiviseurs(1)==set([1]) and eDiviseurs(13)==set([1, 13])
    True"""
    eD=set()
    for i in range(1,a+1):
        if a%i==0:
            eD.add(i)
    return eD

def demoVitesse():
    for p in range(5,20):
        for k in range(100):
            ld=eDiviseurs(10**p+k)
            if len(ld)<=3 or len(ld)>20:
                print(f"{p}:eDiviseurs(10**p+k)=={eDiviseurs(10**p+k)}")

def PGCD(a,b):
    """Renvoie le PGCD entre deux nombres
    >>> PGCD(360,304)
    8
    >>> PGCD(517,513)==1 and PGCD(513,517)==1
    True"""
    if b==0:
        return a
    else:
        n = a%b
        return PGCD(b,n)

def bezout(a,b):
    """Renvoie (u,v,d) tel que a.u+b.v=d avec d=PGCD(a,b)
    >>> bezout(360,304)
    (11, -13, 8)
    >>> bezout(1254,493)
    (-149, 379, 1)
    >>> bezout(513,517)
    (129, -128, 1)"""
    if b==0:
        return 1,0,PGCD(a,b)
    else:
        u,v,d = bezout(b, a%b)
        return v,u - (a//b)*v, d

def chFacteursPremiers(n):
    """renvoie une chaine de caractère donnant la décomposition en
    facteurs premiers de n
    >>> chFacteursPremiers(120)
    '2^3 x 3 x 5'
    >>> chFacteursPremiers(3600)
    '2 x 3^2 x 5^2'
    >>> chFacteursPremiers(1)
    '1'
    >>> chFacteursPremiers(2)
    '2'
    >>> chFacteursPremiers(21)
    '3 x 7'"""


if __name__ == "__main__":
    dt.testmod()
    print("\nTest des diviseurs d'un nombre:")
    print(f'Les diviseurs de 15 sont: {eDiviseurs(15)}')

    print("\nDonne le PGCD entre deux nombre")
    print(f'Le PGCD entre 666 et 867: {PGCD(666,867)}')

    print("\nDonne bezout")
    print(f'Le bezout de 360 et 304: {bezout(360,304)}')

