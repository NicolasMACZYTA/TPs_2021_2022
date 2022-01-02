from math import *
from random import *
import matplotlib.pyplot as plt
import numpy as np
import doctest as dt

class ElmtZnZ(object):
    """On cherche a avoir
    a=ElmtZnZ(2,8)
    b=ElmtZnZ(8,7)
    print(axb)"""
    def __init__(self,a,n):
        """initialisation"""
        self.a=a
        self.n=n

    def __str__(self):
        """representation string"""
        return self.a+' ['+self.n+']'

    def __repr__(self):
        """representation string officiel"""
        return 'ElmtZnZ('+self.a+','+self.n+')'

    def __add__(self,other):
        """addition peut additionner avec un autre ElmtZnZ ou un entier"""

    def __radd__(self,other):
        """reverse addition"""

    def __mul__(self,other):
        """multiplication"""

    def __rmul__(self,other):
        """reverse multiplication"""

    def __floordiv__(self,other):
        """implements a//b"""

    def __neg__(self):
        """retourne negatif de lui même"""

    def __sub__(self,other):
        """soustraction"""

    def __rsub__(self,other):
        """reverse soustractionb"""
    
    def estInversible(self):
        """verifie si nombre est inversible"""

    def inverse(self):
        """inverse le nombre"""
    
if __name__ == "__main__":
    dt.testmod()