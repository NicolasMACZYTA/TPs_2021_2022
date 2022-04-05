from math import sqrt
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

def bezout(a,b):    #etre sur que premier
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
    
def estPremier(num):
    if num==2:
        return True
    if num%2==0 or num<=1:
        return False
    c=int(sqrt(num))+1
    
    for div in range(3, c, 2):
        if num % div==0:
            return False
    return True

class ElmtZnZ(object):
    """Elements ZnZ"""
    
    def __init__(self,a,n=2):
        """initialisation d'un ElmtZnZ"""
        if isinstance(a,ElmtZnZ):
            self.a,self.n=a.a,a.n
        else:
            self.a=a%n
            self.n=n

    def __str__(self):
        """representation string"""
        return f'{self.a} [{self.n}]'

    def __repr__(self):
        """representation string officiel"""
        return f"ElmtZnZ({self.a},{self.n})"

    def __eq__(self,other):
        """verifie si les deux elements sont identique
        >>> ElmtZnZ(7,8) == ElmtZnZ(2,8)
        False
        >>> ElmtZnZ(7,8) == 7
        True
        """
        if isinstance(other, ElmtZnZ):
            if(self.a == other.a and self.n == other.n):
                return True
            else:
                return False
        else:
            if(self.a == other):
                return True
            else:
                return False

    def __add__(self,other):
        """addition peut additionner avec un autre ElmtZnZ ou un entier
        >>> ElmtZnZ(7,8)+ElmtZnZ(2,8)
        ElmtZnZ(1,8)
        >>> ElmtZnZ(7,8)+3
        ElmtZnZ(2,8)
        """
        if isinstance(other, ElmtZnZ):
            assert self.n == other.n,f"modulos différents"
            return ElmtZnZ(self.a+other.a,self.n)
        else:
            return ElmtZnZ(self.a+other,self.n)

    def __radd__(self,other):
        """reverse addition
        >>> 3+ElmtZnZ(7,8)
        ElmtZnZ(2,8)
        """
        return self+other

    def __mul__(self,other):
        """multiplication
        >>> ElmtZnZ(7,8)*ElmtZnZ(2,8)
        ElmtZnZ(6,8)
        >>> ElmtZnZ(7,8)*3
        ElmtZnZ(5,8)
        """
        if isinstance(other, ElmtZnZ):
            assert self.n == other.n,f"modulos différents"
            return ElmtZnZ(self.a*other.a,self.n)
        else:
            return ElmtZnZ(self.a*other,self.n)

    def __rmul__(self,other):
        """reverse multiplication
        >>> 3*ElmtZnZ(7,8)
        ElmtZnZ(5,8)
        """
        return self*other

    def __floordiv__(self,other):
        """implements a//b
        >>> ElmtZnZ(7,8)//ElmtZnZ(2,8)
        ElmtZnZ(3,8)
        """
        if isinstance(other, ElmtZnZ):
            assert self.n == other.n,f"modulos différents"
            return ElmtZnZ(self.a//other.a,self.n)
        else:
            return ElmtZnZ(self.a//other,self.n)

    def __neg__(self):
        """retourne negatif de lui même
        >>> -ElmtZnZ(7,8)
        ElmtZnZ(1,8)
        """
        return ElmtZnZ(-self.a,self.n)

    def __sub__(self,other):
        """soustraction
        >>> ElmtZnZ(7,8)-ElmtZnZ(2,8)
        ElmtZnZ(5,8)
        >>> ElmtZnZ(7,8)-3
        ElmtZnZ(4,8)
        """
        if isinstance(other, ElmtZnZ):
            assert self.n == other.n,f"modulos différents"
            return ElmtZnZ(self.a-other.a,self.n)
        else:
            return ElmtZnZ(self.a-other,self.n)

    def __rsub__(self,other):
        """reverse soustraction
        >>> 3-ElmtZnZ(7,8)
        ElmtZnZ(4,8)
        """
        return self-other
    
    def __pow__(self,other):
        """permet de faire des puissance
        >>> ElmtZnZ(7,8)**2
        ElmtZnZ(1,8)"""
        return ElmtZnZ(pow(self.a,other,self.n),self.n)
        
        
    def valThChinois(self,other):
        """Theoreme chinois
        >>> ElmtZnZ(2,7).valThChinois(ElmtZnZ(3,10))
        ElmtZnZ(23,70)
        """
        v,u,d=bezout(self.n,other.n)
        c = self.a*other.n*u + other.a*self.n*v
        return ElmtZnZ(c,self.n*other.n)        
        
    def estInversible(self):
        """verifie si l'element est inversible
        >>> ElmtZnZ(2,8).estInversible()
        False
        >>> (ElmtZnZ(7,8)+ElmtZnZ(2,8)).estInversible()
        True
        >>> ElmtZnZ(3,8).estInversible()
        True
        """
        if PGCD(self.a,self.n)==1:
            return True
        else:
            return False

    def inverse(self):
        """inverse l'element
        >>> ElmtZnZ(3,256).inverse()
        ElmtZnZ(171,256)
        >>> ElmtZnZ(2,8).inverse()
        2 n'est pas inversible
        >>> ElmtZnZ(7,8).inverse()
        ElmtZnZ(7,8)
        >>> ElmtZnZ(13,8).inverse()
        ElmtZnZ(5,8)
        """
        if self.estInversible():
            m = pow(self.a, -1, self.n)
            return ElmtZnZ(m, self.n)
        else:
            print(f"{self.a} n'est pas inversible")
        
    def logDiscret(self,b):
        """Renvoie x tel que self.a**x==b(self.n) n doit etre premier
        >>> ElmtZnZ(2,13).logDiscret(8)
        3
        >>> ElmtZnZ(2,13).logDiscret(3)
        4
        >>> ElmtZnZ(2,14).logDiscret(2)
        14 n'est pas un nombre premier
        """
        if estPremier(self.n):
            s = 1
            for i in range(self.n):
                s = (s * self.a) % self.n
                if s == b:
                    return i + 1
        else:
            print(f"{self.n} n'est pas un nombre premier")
    
if __name__ == "__main__":
    dt.testmod()
