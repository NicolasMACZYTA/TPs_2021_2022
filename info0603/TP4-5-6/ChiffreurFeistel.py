#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Feb  3 18:10:52 2022

@author: nithrilh
"""

from CodeurCA import *
from Binaire603 import *
from Texte603 import *
from ElmtZnZ import *
class ChiffrementAffine(CodeurCA):# Ne pas toucher
    """Un codeur doit surcharger les méthodes __init__ __repr__ __str__
    binCode, binDecode et codeurTest
    renvoyant et recevant un Binaire603
    C'est une forme de classe abstraites"""
    def __init__(self,a=3,b=5):
        """initialisation du chiffrement affine"""
        self.a = ElmtZnZ(a,256)
        assert self.a.estInversible()
        self.b = b
        
    def __str__(self):
        return "Chiffreur Affine"
    
    def __repr__(self):
        return f'ChiffrementAffine()'

    def binCode(self,monBinD:Binaire603)->Binaire603:
        """
        >>> ChiffrementAffine(3,1).binCode(Binaire603([ 1,10,150]))
        Binaire603([ 0x04, 0x1f, 0xc3])
        """
        bc=FBijFeistel(f4b1,5,16)(monBinD)
            
        return Binaire603(bc)
        
    def binDecode(self,monBinC:Binaire603)->Binaire603:
        """
        >>> ChiffrementAffine(3,1).binDecode(Binaire603([ 0x04, 0x1f, 0xc3]))
        Binaire603([1,10,150])
        """
        ld=[((bd-self.b)*self.a.inverse().a)%256 for bd in monBinC]
        
        return ld


if __name__ == "__main__":
    import doctest
    doctest.testmod()
    monCodeur=ChiffrementAffine(3,5) #A modifier si repris dans une classe en héritant
    for k in range(5):
        monBin=Binaire603.exBin603(num=k,taille=25)
        print("Bin:",monBin)
        monBinCr=monCodeur.binCode(monBin)
        print("Bin Codée:",monBinCr)
        print("monBinCr décodé est égal à Monbin ?",monCodeur.binDecode(monBinCr)==monBin)


