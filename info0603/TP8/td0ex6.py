from math import *
from random import *
import matplotlib.pyplot as plt
import numpy as np

def proba_anniversaire(n):
    """Donne la probabilité que deux personnes dans un groupe de n personnes aient la même date d'anniversaire"""
    res = 1
    for i in range(1,n+2):
        res = res * ((365-i)/365)
    return 1-res

if __name__ == "__main__":
    print(f"Pour 10 personnes, on a une probabilite de {round(proba_anniversaire(10),3)}")
    
    print(f"Pour 21 personnes, on a une probabilite de {round(proba_anniversaire(21),3)} ce qui depasse 50%")
    
    print(f"Pour 39 personnes, on a une probabilite de {round(proba_anniversaire(39),3)} ce qui depasse 90%")
    
    print(f"Pour 57 personnes, on a une probabilite de {round(proba_anniversaire(57),3)}")
    
