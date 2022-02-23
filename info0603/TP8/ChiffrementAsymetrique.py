from random import *
import matplotlib.pyplot as plt
import numpy as np
import doctest as dt
from ElmtZnZ import *

class ChiffrementAsymetrique(object):
    """ChiffrementAsymetrique"""
    
    def estPremierOuPseudoPremierDansLaBase(n=2,a):
        """Teste la pseudo-primalité d'un entier n en base a
        c.a.d si a**(n-1)=1[n]
        >>> estPremierOuPseudoPremierDansLaBase(121,3)
        True
        >>> estPremierOuPseudoPremierDansLaBase(121,2)
        False
        """
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
        
    def lNombresDePoulet(nbits=16):
        """Renvoie la liste des nombres de Poulet inférieurs à 2**nbits
        cad pseudopremier en base 2 Voir suite A001567 de l'OEIS
        >>> lNombresDePoulet(10)
        [341, 561, 645]
        """
    
    def lbasesDeTestsDePrimalite(nbits=32, verbose=True):
        """Renvoie la liste des bases à testés selon la valeur du nombre premier à tester
        >>> lbasesDeTestsDePrimalite(10)
        [(341, [2, 3]), (1105, [2, 3, 5])]
        """

if __name__ == "__main__":
    dt.testmod()