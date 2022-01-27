import random as rand
from CodeurCA import *
from Binaire603 import *
class Permutation603(CodeurCA):# Ne pas toucher
    
    

    def __init__(self, lpermutation=[]):
        """
        >>> Permutation603([1,2,3,0])
        Permutation603([1, 2, 3, 0])"""
        
        self.lp=lpermutation
        self.li=lpermutation.copy()
        self.li.sort()
        

    def __pow__(self, n):
        """
        >>> Permutation603([1,2,3,0])**2
        Permutation603([2, 3, 0, 1])
        >>> Permutation603([1, 2, 3, 0])**4
        Permutation603([0, 1, 2, 3])
        >>> Permutation603([1, 2, 3, 0])**(-1)
        Permutation603([3, 0, 1, 2])"""
        
        for i in range(len(self.lp)):
            self.lp[i]=((self.lp[i]+n-1)%len(self.lp))
        return self
        
    def ordre(self): 
        """Renvoie l'ordre de la permutation
        >>> Permutation603([1,2,3,0]).ordre()
        4
        >>> Permutation603([1,0,2,3]).ordre()
        2"""
        c=0
        for i in range(len(self.lp)):
            if (self.lp[i]!=self.li[i]):
                c=c+1
        return c
            
    def permutAlea(n=6):
        """Renvoie une permutation aléatoire sans utiliser shuffle, seulement randint"""
        l=[]
        for i in range(0,n):
            l.append(i)
        res = Permutation603(l)
        
        for i in range(0,n):
            r=rand.randint(0,n-1)
            res.lp[i],res.lp[r]=res.lp[r],res.lp[i]
        return res
        
    
    def permutKieme(k,n=6):
        """Renvoie la kieme permutation de Sn ce qui permet d'associer des clés aux permutations
        >>> lr=[Permutation603.permutKieme(k,n=3) for k in range(6)]
        >>> le=[[0,1,2],[0,2,1],[1,0,2],[1,2,0],[2,1,0],[2,0,1]]
        >>> sum([1 if Permutation603(l) in lr else 0 for l in le])
        6"""
    def numPermutation(self):
        """Renvoie le numéro de la permutation
        >>> Permutation603.permutKieme(100,n=5).numPermutation()
        100"""


    def __str__(self):
        return f'Permutation603({self.lp})'
    def __repr__(self):
        return f'Permutation603({self.lp})'

    def binCode(self,monBinD:Binaire603)->Binaire603:
        pass
    def binDecode(self,monBinC:Binaire603)->Binaire603:
        pass



if __name__ == "__main__":
    import doctest
    doctest.testmod()
    monCodeur=Permutation603() #A modifier si repris dans une classe en héritant
    for k in range(5):
        monBin=Binaire603.exBin603(num=k,taille=25)
        print("Bin:",monBin)
        monBinCr=monCodeur.binCode(monBin)
        print("Bin Codée:",monBinCr)
        #print("monBinCr décodé est égal à Monbin ?",monCodeur.binDecode(monBinCr)==monBin)


