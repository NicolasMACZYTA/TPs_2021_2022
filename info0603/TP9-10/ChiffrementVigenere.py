from Binaire603 import Binaire603
from Texte603 import Texte603
import doctest as dt
from math import *
from random import *
import matplotlib.pyplot as plt

class ChiffrementVigenere(Texte603):
    """Texte603 n'hérite pas de str car c'est un type immutable
    ce qui complique l'initialisation
    Un Texte603 est formé de 256 caractères affichable directement sur l'écran'
    cad Que les caractères de contrôles ont été convertis en caractères affichables
    """
    def __init__(self, texte, cle):
        self.texte = texte
        self.cle = cle

    def __repr__(self):
        return f'ChiffrementVigenere("{self.texte},{self.cle}")'
    
    def enCode(self):
        """
        """
        p=0
        res=[]
        for c in Texte603(self.texte).toBinaire603():
            res.append[c+self.cle[p]]
            p=(1+p)%len(cle)
        
        return Texte603(res)
        
    def deCode(self):
        pass

if __name__ == "__main__":
    dt.testmod()
