#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Feb  9 16:35:46 2022
"""

import random as rand

def collisionAlea(nbit=4, N=2**20):
    """
    Parameters
    ----------
    nbit : TYPE, optional
        nbit de la clef, The default is 4.
    N : TYPE, optional
        nombre de mot, The default is 2**20.

    Returns
    -------
    nbcol : TYPE
        DESCRIPTION.

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