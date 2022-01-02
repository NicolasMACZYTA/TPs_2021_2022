from math import *
from random import *
import matplotlib.pyplot as plt
import numpy as np

def afficher_troislettre():
    """Affichage des listes de trois lettres 
    ordonee avec repetition"""
    for c1 in ['A','B','C','D','E']:
        for c2 in ['A','B','C','D','E']:
            for c3 in ['A','B','C','D','E']:
                print(f'{c1}{c2}{c3}')

def afficher_troislettredistinct():
    """Affichage des listes de trois lettres 
    ordonee sans repetition"""
    for c1 in ['A','B','C','D','E']:
        for c2 in ['A','B','C','D','E']:
            if c1!=c2:
                for c3 in ['A','B','C','D','E']:
                    if c1!=c3 and c2!=c3:
                        print(f'{c1}{c2}{c3}')

#afficher_troislettre()
afficher_troislettredistinct()
