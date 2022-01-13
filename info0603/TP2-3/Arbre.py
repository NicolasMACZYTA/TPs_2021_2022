#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jan 13 16:39:28 2022

@author: nithrilh
"""

class Arbre(object):
    
    def __init__(self,freq,val = '',fg = None,fd = None):
        """Arbre(frequence, valeur, filsgauche, filsdroit)
        >>> Arbre(0.2, 'A')
        Arbre(0.2,A,None,None)
        """
        self.val = val
        self.freq = freq
        self.fg = fg
        self.fd = fd
        
    def __repr__(self):
        return f'Arbre({self.freq},{self.val},{self.fd},{self.fg})'
    
    def isFeuille(self):
        if(self.fg == None & self.fd == None):
            return True
        else:
            return False
    
    def concatener(ag,ad):
        res = Arbre(ag.freq+ad.freq,val=ag.val+ad.val,fg=ag,fd=ad)
        return res

    