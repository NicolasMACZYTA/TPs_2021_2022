from math import *
from random import *
import matplotlib.pyplot as plt
import numpy as np

lchar=['A','B','C','D','E']

def afficher_listetroislettre():
    """affiche les listes de trois lettres
    avec tirage successif avec remise"""
    
    nbrl=0
    for c1 in lchar:
        for c2 in lchar:
            for c3 in lchar:
                nbrl+=1
                print(f"{c1}{c2}{c3}")
    print(f"{nbrl} listes de 3 éléments avec ordre et avec répétitions choisis parmi 5\n")
    return nbrl

def afficher_listetroislettresuccessif():
    """affiche des listes de trois lettres
    avec tirage successif sans remise"""
    
    nbrl=0
    for c1 in lchar:
        for c2 in lchar:
            if c1!=c2:
                for c3 in lchar:
                    if c1!=c3 and c2!=c3:
                        nbrl+=1
                        print(f"{c1}{c2}{c3}")
    print(f"{nbrl} listes de 3 éléments avec ordre et sans répétitions choisis parmi 5\n")

def afficher_listetroislettresimultane():
    """affiche des listes de trois lettres
    avec tirage simultané"""
    
    nbrl=0
    for i in range(0,3):
        for j in range(i+1,4):
            for k in range(j+1,5):
                nbrl+=1
                print(f"{lchar[i]}{lchar[j]}{lchar[k]}")
    print(f"{nbrl} listes de 3 éléments sans ordre et sans répétitions choisis parmi 5\n")

    
if __name__ == "__main__":
    afficher_listetroislettre()

    afficher_listetroislettresuccessif()

    afficher_listetroislettresimultane()
