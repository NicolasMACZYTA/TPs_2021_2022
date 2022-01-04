from math import *
from random import *
import matplotlib.pyplot as plt
import numpy as np
import doctest as dt


    
#Sans aucune justification, proposer un ordre de grandeur de la probabilité que deux personnes de cette
#salle aient la même date d’anniversaire.

#Donner une représentation et/ou un code informatique calculant/estimant cette probabilité.

#A partir de combien de personnes présentent cette probabilité dépasse 0,5 ? 0,9 ?


# 1-p(n) = 365/365+365/364*365/363*...*(365-n+1)/365


def proba_anniversaire(n):
    res = 1
    for i in range(1,n+2):
        res = res * ((365-i)/365)
    return 1-res




    
if __name__ == "__main__":
    dt.testmod()
    