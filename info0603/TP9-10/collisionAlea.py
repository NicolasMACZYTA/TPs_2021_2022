#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Feb  9 16:35:46 2022
"""

import random as rand

def collisionAlea(nbit=4, N=2**20):
    """nbit est le nombre de bits de la clef
    N est le nombres de mots.
    """
    rand.seed()
    el = set()
    nbcol=0
    n=2**nbit
    for i in range(N):
        s = len(el)
        el.add(rand.randint(0,n))
        if(s==len(el)):
            nbcol+=1
        
    print(f'collisions : {nbcol}')
    return nbcol
    
if __name__ == "__main__":
    import doctest
    doctest.testmod()
    collisionAlea()