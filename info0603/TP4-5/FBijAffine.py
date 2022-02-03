#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from FBijOctetsCA import *
from ElmtZnZ import *

class FBijAffine(FBijOctetsCA):
    """Une classe de bijection par decallage"""
   
    def __init__(self,a,b):
        """
        >>> FBijAffine(5,2)
        FBijAffine(5x+2)
        """
        self.a = a
        self.b = b
        
    def __repr__(self):
        return f'FBijAffine({self.a}x+{self.b})'
        
    def __call__(self,octet):
        """
        >>> P = FBijAffine(5,2)
        >>> P(5)
        27"""
        return (octet*self.a+self.b)%256
    
    def valInv(self,octetC):
        """Renvoie l'antécédent de octet C
        >>> P = FBijAffine(5,2)
        >>> P.valInv(10)
        5"""
        eres = ElmtZnZ(octetC-self.b,256).inverse()
        res=eres.a
        return res
    
        
if __name__ == "__main__":
    dt.testmod()
