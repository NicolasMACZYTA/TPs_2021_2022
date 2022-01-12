from math import *
from random import *
import matplotlib.pyplot as plt
import numpy as np
import doctest as dt

def llistepeltparmin(p,n):
    """Donne toutes les listes possibles de p elements parmi n
    >>> llistepeltparmin(2,2)
    [[0, 0], [0, 1], [1, 0], [1, 1]]"""
    if p==0:
        rest = [[]]
    if p>0:
        rest = []
        llpnr=llistepeltparmin(p-1,n)
        for l in llpnr:
            for i in range(n):
                rest.append(l+[i])
    
    return rest
    
if __name__ == "__main__":
    dt.testmod()
    listes=llistepeltparmin(3,4)
    print(f"{listes}")