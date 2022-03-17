import math as math
from random import *
import matplotlib.pyplot as plt
import numpy as np
import doctest as dt
import random as rand

def LuhmCheck(idCarte):
    """Algorithme de Luhm pour savoir si un numéro de carte est correcte
    >>> LuhmCheck(4532015112830366)
    True
    >>> LuhmCheck(6011514433546201)
    True
    >>> LuhmCheck(4970101234567890)
    False"""
    
    nbNombre, nombres, somme = int(math.log10(idCarte))+1, [int(d) for d in str(idCarte)], 0
    
    #Récupere un nombre sur deux dans deux variables.
    nombreImpair, nombrePair = nombres[-1::-2], nombres[-2::-2]
    
    somme += sum(nombreImpair)
    for n in nombrePair:
        somme += sum((int(d) for d in str(n*2)))
    
    return ((somme%10) == 0)

if __name__ == "__main__":
    dt.testmod()
