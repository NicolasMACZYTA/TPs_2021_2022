#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import copy
from random import *
from math import sqrt,log
from sympy import isprime
from ElmtZnZ import *
from CodeurCA import *
from Binaire603 import *
from Texte603 import *
import numpy as np
import matplotlib.pyplot as plt
import matplotlib

def generateurDeCle(p=0,q=0,d=0,verbose=False):
    """p et q doivent être premiers et e premier avec (p-1)*(q-1)
    Si ce n’est pas le cas on prends à la place le nombre premier suivant
    En cas de paramètre nul on prends des nombres au hasard
    >>> CodeurRSA32Bits.generateurDeCle(p=0x12345,q=0x43215,d=0xabcba)
    (703679, 7959681319, 20503911691)"""
    
    if not estPremier(p) :
        nbpremiersuivant(p)
    if not estPremier(q) :
        nbpremiersuivant(q)
    e = ElmtZnZ(ores,(p-1)(q-1))
    d = e**(-1)
    
    
    return e.a, d.a, p*q

class CodeurRSA(object):
    
    def __init__(self, n,e,d):
        
        assert ((ElmtZnZ(0x1234567,n)**d)**e) == 0x1234567
        
        self.n=n
        self.e=e
        self.d=d
    
    def binCode(self,monBinD:Binaire603,verbose=False)->Binaire603:
        """>>> CodeurRSA32Bits(703679, 7959681319, 20503911691).
        binCode(Binaire603([ 0x02, 0x03, 0x04, 0x05]))
        Binaire603([ 0x01, 0x04, 0x02, 0x5f, 0x6c, 0x4d, 0xba])"""
        bc=[]
        for b in monBinD:
            bc.append((EltmZnZ(b,self.n)**self.e).a)
        
            #regler avec chiffrement par bloc
            
    def binDeCode(self,monBinD:Binaire603,verbose=False)->Binaire603:
        """>>> CodeurRSA32Bits(703679, 7959681319, 20503911691).
        binCode(Binaire603([ 0x02, 0x03, 0x04, 0x05]))
        Binaire603([ 0x01, 0x04, 0x02, 0x5f, 0x6c, 0x4d, 0xba])"""
        bc=[]
        for b in monBinD:
            bc.append(EltmZnZ(b,self.n)**self.e.a)
        
            #regler avec chiffrement par bloc