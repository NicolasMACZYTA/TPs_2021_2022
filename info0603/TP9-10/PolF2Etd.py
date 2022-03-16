#!/usr/bin/env python
# -*- coding: utf-8 -*-
import copy
from random import *
from math import sqrt,log
from sympy import isprime
from arithmetiqueDansZ import *
import numpy as np
import matplotlib.pyplot as plt
import matplotlib


#Les méthodes magiques : https://blog.finxter.com/python-dunder-methods-cheat-sheet/

class PolF2(object):
    "Polynôme dans F2"
    def __init__(self,x):
        """
        Défini par une liste d' ElmntZnZ
        >>> PolF2([ElmtZnZ(1,2),0,1,0,1])
        PolF2(0b10101)
        >>> print(PolF2(0b10101))
        X⁴+X²+1
        >>> PolF2(0b1000110010) #Entier -> Polynome dans F2
        PolF2(0b1000110010)
        >>> PolF2(0)
        PolF2(0b0)
        """
        self.lcoef=[]
        if isinstance(x,list):
            for e in x:
                self.lcoef.append(ElmtZnZ(e,2))
        elif  isinstance(x,PolF2):
            self.lcoef=(x.lcoef).copy()
        else:
            if x==0:
                self.lcoef=[ElmtZnZ(0,2)]
            else:
                val=x
                while val>0:
                    self.lcoef.append(ElmtZnZ(val%2,2))
                    val=val//2
        while len(self.lcoef)>1 and self.lcoef[-1].a==0:
            self.lcoef.pop() #On enlève les coefficients de plus haut degré qui sont nuls

    def __hash__(self):
        """
        >>> PolF2(0b100011).__hash__()
        35
        """
        return int(self)


    def __str__(self):
        """
        >>> print(PolF2(0b110010))
        X⁵+X⁴+X
        >>> print(PolF2(2**16))
        X¹⁶
        >>> print(PolF2([ElmtZnZ(0,2), ElmtZnZ(1,2), ElmtZnZ(1,2)]))
        X²+X
        """
        if len(self.lcoef)==1:
            return f"+{self.lcoef[0].a}"
        else:
            if self.lcoef[0]==0:
                res=""
            else:
                res="+1"
        for k,c in enumerate(self.lcoef[1:]):
            if c==1:
                res="+X"+strExp(k+1)+res
        return res[1:]
    def __repr__(self):
        """
        """
##        s=""
##        for c in self.lcoef:
##            s+=c.__repr__()+","
##        s=s[:-1]
        #return f"PolF2({self.lcoef})"
        return f"PolF2(0b{int(self):b})"

    def degre(self):
        """
        >>> PolF2(0b100011).degre()
        5
        """
        return len(self.lcoef)-1
    def sommeCoef(self):
        """
        >>> PolF2(0b100011).sommeCoef()
        3
        """
        s=0
        for c in self.lcoef:
            if c==1:s+=1
        return s
    def distanceHamming(self,other):
        """
        >>> PolF2(0b100011).distanceHamming(PolF2(0b1100011))
        1
        """
        pass

    def __add__(self,other):
        """
        >>> PolF2(0b100011)+PolF2(0b1100011)
        PolF2(0b1000000)
        >>> print(PolF2(0b1100011)+ PolF2(0b100011))
        X⁶
        >>> PolF2([ElmtZnZ(0,2), ElmtZnZ(0,2), ElmtZnZ(1,2)])+PolF2([ElmtZnZ(1,2), ElmtZnZ(1,2)])
        PolF2(0b111)
        """
        pres = PolF2()
        if(self.degre()>other.degre()):
            pmax,pmin = self,other
        else:
            pmin,pmax = self,other
        
        for i in range(pmax.degre()-pmin.degre()):
            pres.lcoef.append(pmax.lcoef[i])
        for i in range(pmax.degre()-pmin.degre()+1,pmax.degre()):
            pres.lcoef.append(pmax[i+pmax.degre()-pmin.degre()]+pmin[i])
        
        return pres
    
    
    def monome(k):
        """ X**k
        >>> print(PolF2.monome(5)+PolF2.monome(4)+PolF2.monome(1)+PolF2.monome(0))
        X⁵+X⁴+X+1
        """
        return PolF2(2**(k))
    
    
    def mulmonome(self,k):
        for i in range(k):
            self.lcoef.append(ElmtZnZ(0,2))
        return self
    
    
    def __mul__(self,other):
        """
        >>> print(PolF2.monome(2)*PolF2.monome(1))
        X³
        >>> PolF2(0b1100011)*PolF2(0b100011)
        PolF2(0b110011000101)
        >>> print(PolF2([ElmtZnZ(0,2), ElmtZnZ(0,2), ElmtZnZ(1,2)])*PolF2([ElmtZnZ(1,2), ElmtZnZ(1,2)]))
        X³+X²
        """
        pres=PolF2()
        for i in range(self.degre()):
            if self.lcoef[i].x==1:
                pres = pres + other.mulmonome(other.degre()-i)
        return pres

    def estNul(self):
        return self.degre()==0 and self.lcoef[0]==0

    def __eq__(self,other):
        """
        >>> PolF2.monome(7)+PolF2.monome(3)+PolF2.monome(1)==0
        False
        """
        if isinstance(other,int) or isinstance(other,ElmtZnZ):
            return self.degre()==0 and self.lcoef[0]==other

        return (self-other).estNul()
    def __neg__(self):
        """
        """
        pass
    def __sub__(self,other):
        """
        >>> PolF2(0b100011)-PolF2(0b100011)==0
        True
        """
        return self+other
    
    
    def __mod__(self,other):
        """
        >>> PolF2(0b11000101)%PolF2(0b11000)
        PolF2(0b101)
        """
        
        #self = q.other +r 
        
        q,r = PolF2(0),PolF2(self)
        
        while(r.degre()>=other.degre()):
            
            k=r.degre()-other.degre()
            r=r-other.mulmonome(k)
            q=q+PolF2.monome(k)
            
        return r
            
    def __floordiv__(self,other):
        """
        >>> PolF2(0b11000101)//PolF2(0b11000)
        PolF2(0b1000)
        """
        pass

    def __int__(self):
        """
        >>> int(PolF2([ElmtZnZ(1,2), ElmtZnZ(0,2), ElmtZnZ(1,2)]))
        5
        """
        res=0
        for c in reversed(self.lcoef):
            res=res*2+c.a
        return res

if __name__ == "__main__":
    p=PolF2(0b100011)+PolF2(0b1100011)
    print(f"({PolF2(0b100011)})+({PolF2(0b1100011)})={PolF2(0b100011)+PolF2(0b1100011)} : {PolF2(0b100011)+PolF2(0b1100011)==PolF2(0b1000000)}")
    print(f"({PolF2(0b100001)})*({PolF2(0b1100011)})={PolF2(0b100001)*PolF2(0b1100011)}")
    print(f"({PolF2(0b1100011)})-({PolF2(0b1000011)})={PolF2(0b1100011)-PolF2(0b1000011)}")
    print(f"({PolF2(0b100001)})*({PolF2(0b0001010)})+({PolF2(0b0000011)})={PolF2(0b100001)*PolF2(0b0001010)+PolF2(0b0000011)}")
    print(f"({PolF2(0b1100011)})//({PolF2(0b101)})={PolF2(0b1100011)//PolF2(0b101)}")
    print(f"({PolF2(0b1100011)})%({PolF2(0b101)})={PolF2(0b100011)%PolF2(0b101)}")
    print(f"({PolF2(0b1100011)})=({PolF2(0b1100011)//PolF2(0b101)})*({PolF2(0b101)})+({PolF2(0b1100011)%PolF2(0b101)})")
    print(f"({PolF2(0b100011)})=({PolF2(0b100011)//PolF2(0b1001)})*({PolF2(0b1001)})+({PolF2(0b100011)%PolF2(0b1001)})")

    import doctest
    doctest.testmod()
