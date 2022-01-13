#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jan 13 16:39:28 2022

@author: nithrilh
"""

class Arbre(object):
    
    
    def __init__(self,freq,fg,fd,val):
        self.val = val
        self.freq = freq
        self.fg = fg
        self.fd = fd
    
    def isFeuille(self):
        if(self.fg == None & self.fd == None):
            return False
        else:
            return True
    
    def concatener(ag,ad):
        res = Arbre(ag.freq+ad.freq,ag,ad,None)
        return res

    