from math import *
from random import *
import matplotlib.pyplot as plt
import numpy as np
import doctest as dt
import itertools #A voir pour refaire manuellement?

def lliste_peltparmin(p,n):
    """Donne toutes les listes possibles de p elements parmi n
    >>> lliste_peltparmin(2,2)
    [[0, 0], [0, 1], [1, 0], [1, 1]]"""
    if p==0:
        rest = [[]]
    if p>0:
        rest = []
        llpnr=lliste_peltparmin(p-1,n)
        for l in llpnr:
            for i in range(n):
                rest.append(l+[i])
    
    return rest
                
def lensbl_peltparmin(p,n):
    """Donne tout les ensembles possibles de p elements parmi n
    >>> lensbl_peltparmin(2,4)
    [[0, 1], [0, 2], [0, 3], [1, 2], [1, 3], [2, 3]]"""
    
    rest = []
    for sset in itertools.combinations(range(n), p):
        tmp = []
        for l in range(p):
            tmp.append(sset[l])
        rest.append(tmp) #ça marche et franchement c'est cool
    
    return rest
                
def lliste_peltparmin_unique(p,n):
    """Donne tout les listes possibles de p elements parmi n sans redites
    >>> lliste_peltparmin_unique(2,3)
    [[0, 1], [0, 2], [1, 0], [1, 2], [2, 0], [2, 1]]"""
    rest = []
    for sset in itertools.permutations(range(n), p): #c'est presque de la triche...
        tmp = []
        for l in range(p):
            tmp.append(sset[l])
        rest.append(tmp)
    
    return rest
    
if __name__ == "__main__":
    dt.testmod()
    
    print("Iterateur de listes")
    for l in lliste_peltparmin(3,4):
        print(l)
        
    print("Iterateur d'ensembles")
    for l in lensbl_peltparmin(3,4):
        print(l)
        
    print("Iterateur de listes sans redites")
    for l in lliste_peltparmin_unique(3,4):
        print(l)
