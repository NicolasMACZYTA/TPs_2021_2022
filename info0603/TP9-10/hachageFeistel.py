#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Feb  9 17:10:00 2022

"""

from random import *
from Binaire603 import *
from CodeurCA import *
from Texte603 import *
from FBijFeistel import *
import matplotlib.pyplot as plt


class HachageFeistel(CodeurCA):# Ne pas toucher
    """Un codeur doit surcharger les méthodes __init__ __repr__ __str__
    binCode, binDecode et codeurTest
    renvoyant et recevant un Binaire603
    C'est une forme de classe abstraite"""
    def __init__(self, f=f4b1, cle=0x0101, nb_tours=2):
        self.fbij=FBijFeistel(f, cle, nb_tours)

    def __str__(self):
        return (f"Chiffreur de Feistel avec f={self.fbij}")
    
    def __repr__(self):
        return(f"ChiffreurFeistel({self.fbij})")
    
    def binCode(self,monBinD:Binaire603)->Binaire603:
        """
        """
        assert isinstance(monBinD, Binaire603)
        
        retour=[]
        for elem in monBinD:
                retour.append(self.fbij(elem))

        return Binaire603(retour)
    
    def binDecode(self,monBinC:Binaire603)->Binaire603:
        """
        """
        assert isinstance(monBinC, Binaire603)
        retour=[]
        for elem in monBinC:
                retour.append(self.fbij.valInv(elem))

        return Binaire603(retour)
    
    def collisionAlea(self,nbit=16, N=2**20):
        """
        Parameters
        ----------
        nbit : TYPE, optional
            nbit de la clef, The default is 16.
        N : TYPE, optional
            nombre de mot, The default is 2**20.
    
        Returns
        -------
        nbcol : TYPE
            DESCRIPTION.
    
        """
        el = []
        nbcol=0
        n=nbit
        for i in range(N):
            s = len(el)
            tmp=self.binCode(Binaire603.exBin603(nbit//8,2))
            if(tmp not in el):
                el.append(tmp)
            else:
                nbcol+=1
            
        #print(f'collisions : {nbcol}')
        return nbcol
        
    def afficheGraphiqueCollision(self,nbit):
        lx = [k for k in range(256)]
        ly = [self.collisionAlea(nbit,x*10) for x in lx]
        plt.plot(lx,ly,".")
        plt.title('collision feistel')
        plt.show()
        
if __name__ == "__main__":
    import doctest
    doctest.testmod()
    #for k in range(1,17):
    #   FBijFeistel(f4b1, 113, k).afficheGraphique()
    Hacheur = HachageFeistel()
     
    