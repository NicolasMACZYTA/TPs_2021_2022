from math import *
from random import *
import matplotlib.pyplot as plt
import numpy as np
import doctest as dt

lval=['roi','dame','valet','as','10','9','8','7']
lcol=['trefle','carreau','coeur','pique']

def binomial(n,k):
    """Coeficient binomial
    >>> binomial(50,6)
    15890700
    >>> binomial(5,5)
    1
    >>> binomial(5,8)
    0"""
    if k < 0 or k > n:
        return 0

    if k == 0 or k == n:
        return 1

    nbr = 1
    for i in range(min(k, n - k)):
        nbr=nbr * (n - i) // (i + 1)

    return nbr

def cartes_nombretotalmains():
    """retourne le nombre total de mains possible de 5 cartes dans un paquet de 32 cartes
    >>> cartes_nombretotalmains()
    201376"""
    return binomial(32,5)
    
def cartes_quinteflush():
    """retourne le nombre de mains de 5 cartes qui se suivent et de même couleur
    >>> cartes_quinteflush()
    32"""
    return 0
    
def cartes_suite():
    """retourne le nombre de mains de 5 cartes  qui se suivent mais pas de même couleur
    >>> cartes_suite()
    4064"""
    return 0
    
def cartes_couleur():
    """retourne le nombre de mains de 5 cartes qui ne se suivent pas mais de même couleur
    >>> cartes_couleur()
    192"""
    return 0
    
def cartes_carrer():
    """retourne le nombre de mains de 5 cartes dont 4 sont de valeur identique
    >>> cartes_carrer()
    224"""
    return 0

def cartes_full():
    """retourne le nombre de mains de 5 cartes dont 3 sont de meme valeur ainsi que deux autre quelconques
    >>> cartes_full()
    1344"""
    return 0
    
def cartes_brelan():
    """retourne le nombre de mains de 5 cartes dont 3 identique ainsi que deux autre quelconques
    >>> cartes_brelan()
    12096"""
    return 0

def cartes_doublepaires():
    """retourne le nombre de mains de 5 cartes qui possédent deux paires
    >>> cartes_doublepaires()
    6"""
    return 0
    
def cartes_simplepaire():
    """retourne le nombre de mains possible de 5 cartes qui possédent seulement une paire
    >>> cartes_simplepaire()
    24192"""
    return 0
    
if __name__ == "__main__":
    dt.testmod()
    
    print(f"Il y a {cartes_nombretotalmains()} mains de 5 cartes possibles dans un jeu de 32 cartes.")
    print(f"Parmi ces mains, il est possible d'avoir:\n")
    print(f"{cartes_quinteflush()} mains avec une quinte flush.")
    print(f"{cartes_suite()} mains avec 5 cartes qui se suivent n'étant pas toutes de même couleur.")
    print(f"{cartes_couleur()} mains avec 5 cartes qui ne se suivent pas mais de même couleur.")
    print(f"{cartes_carrer()} mains de 4 cartes de même valeur.")
    print(f"{cartes_full()} mains avec 3 cartes de meme valeur et 2 autre quelconques.")
    print(f"{cartes_brelan()} mains avec 3 cartes identiques et 2 autre quelconques.")
    print(f"{cartes_doublepaires()} mains avec deux paires.")
    print(f"{cartes_simplepaire()} mains avec seulement une paire.")
