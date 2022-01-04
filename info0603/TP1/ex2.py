from math import *
from random import *
import matplotlib.pyplot as plt
import numpy as np
import doctest as dt

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
    """Renvoie (v,u,d) tel que a.u+b.v=d avec d=PGCD(a,b)
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

class ElmtZnZ(object):
    """>>> a=ElmtZnZ(7,8)
    >>> b=ElmtZnZ(2,8)
    >>> a==b
    False
    >>> a+b
    ElmtZnZ(1,8)
    >>> a+3
    ElmtZnZ(2,8)
    >>> 3+a
    ElmtZnZ(2,8)
    >>> a*b
    ElmtZnZ(6,8)
    >>> 3*a
    ElmtZnZ(5,8)
    >>> a*3
    ElmtZnZ(5,8)
    >>> a//b
    ElmtZnZ(3,8)
    >>> -a
    ElmtZnZ(1,8)
    >>> a-b
    ElmtZnZ(5,8)
    >>> a-3
    ElmtZnZ(4,8)
    >>> 3-a
    ElmtZnZ(4,8)
    >>> ElmtZnZ(2,7).valThChinois(ElmtZnZ(3,10))
    ElmtZnZ(23,70)
    >>> b.estInversible()
    False
    >>> (a+b).estInversible()
    True
    >>> ElmtZnZ(3,8).estInversible()
    True
    >>> b.inverse()
    2 n'est pas inversible
    >>> a.inverse()
    ElmtZnZ(7,8)
    >>> a**2
    ElmtZnZ(1,8)
    >>> ElmtZnZ(2,13).logDiscret(8)
    3
    >>> ElmtZnZ(2,13).logDiscret(3)
    4"""
    
    def __init__(self,a,n):
        """initialisation d'un ElmtZnZ"""
        self.a=a%n
        self.n=n

    def __str__(self):
        """representation string"""
        return f'{self.a} [{self.n}]'

    def __repr__(self):
        """representation string officiel"""
        return f"ElmtZnZ({self.a},{self.n})"

    def __eq__(self,other):
        """verifie si les deux elements sont identique"""
        if(self.a == other.a and self.n == other.n):
            return True
        else:
            return False

    def __add__(self,other):
        """addition peut additionner avec un autre ElmtZnZ ou un entier"""
        if isinstance(other, ElmtZnZ):
            assert self.n == other.n,f"modulos différents"
            return ElmtZnZ(self.a+other.a,self.n)
        else:
            return ElmtZnZ(self.a+other,self.n)

    def __radd__(self,other):
        """reverse addition"""
        return self+other

    def __mul__(self,other):
        """multiplication"""
        if isinstance(other, ElmtZnZ):
            assert self.n == other.n,f"modulos différents"
            return ElmtZnZ(self.a*other.a,self.n)
        else:
            return ElmtZnZ(self.a*other,self.n)

    def __rmul__(self,other):
        """reverse multiplication"""
        return self*other

    def __floordiv__(self,other):
        """implements a//b"""
        if isinstance(other, ElmtZnZ):
            assert self.n == other.n,f"modulos différents"
            return ElmtZnZ(self.a//other.a,self.n)
        else:
            return ElmtZnZ(self.a//other,self.n)

    def __neg__(self):
        """retourne negatif de lui même"""
        return ElmtZnZ(-self.a,self.n)

    def __sub__(self,other):
        """soustraction"""
        if isinstance(other, ElmtZnZ):
            assert self.n == other.n,f"modulos différents"
            return ElmtZnZ(self.a-other.a,self.n)
        else:
            return ElmtZnZ(self.a-other,self.n)

    def __rsub__(self,other):
        """reverse soustraction"""
        return self-other
    
    def __pow__(self,other):
        """permet de faire des puissance"""
        
    def valThChinois(self,other):
        """Theoreme chinois"""
        v,u,d=bezout(self.n,other.n)
        c = self.a*other.n*u + other.a*self.n*v
        return ElmtZnZ(c,self.n*other.n)        
        
    def estInversible(self):
        """verifie si l'element est inversible"""
        if PGCD(self.a,self.n)==1:
            return True
        else:
            return False

    def inverse(self):
        """inverse l'element"""
        if self.estInversible():
            for x in range(1, self.n):
               if (((self.a%self.n) * (x%self.n)) % self.n == 1):
                   return ElmtZnZ(x,self.n)
               return ElmtZnZ(self.a,self.n)
        else:
            print(f"{self.a} n'est pas inversible")
        
    def logDiscret(self,b):
        """Renvoie x tel que self.a**x==b(self.n) n doit etre premier"""
    
if __name__ == "__main__":
    dt.testmod()