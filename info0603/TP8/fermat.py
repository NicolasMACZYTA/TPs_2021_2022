from math import sqrt
from random import *
import matplotlib.pyplot as plt
import numpy as np
import doctest as dt
from ElmtZnZ import *



def estPremierOuPseudoPremierDansLaBase(n,a):
    """ Teste la pseudo-primalité d'un entier n en base a
    c.a.d si a**(n-1)=1[n] Voir Cours Alain Ninet
    >>> estPremierOuPseudoPremierDansLaBase(121,3)
    True
    >>> estPremierOuPseudoPremierDansLaBase(121,2)
    False"""
    k,r=n-1,0
    
    while((k%2!=0)):
        k,r=k//2,r+1
        
    ap = ElmtZnZ(a,n)**k
        
    if ((ap-1 == 0) or (ap+1 == 0)):
        return True
    
    while(r>1):
        ap,r=ap*ap,r-1
        if (ap+1 == 0):
            return True
    
    return False

if __name__ == "__main__":
    dt.testmod()