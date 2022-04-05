from FBijOctetsCA import *
import random as rand

class FBijFeistel(FBijOctetsCA):
    """Une classe de chiffrement par blocs"""
   
    def __init__(self,f,cle,nbtours=2):
        """Avec cle la cle de cryptage pour encoder decoder
        >>> FBijFeistel(f4b1,0x0101)
        FBijDecalage(5)
        """
        self.f = f
        self.cle = cle
        self.nbtours = nbtours
        self.lk=[]
        rand.seed(self.cle)
        self.lk=[rand.randint(0,15) for t in range(self.nbtours)]
        
    def __repr__(self):
        return f'FBijeistel({self.nbtours})'
        
    def __call__(self,octet):
        """
        >>> P = FBijFeistel(5)
        >>> P(5)
        10"""
        l, r = octet//16, octet%16
        for i in range(self.nbtours):
            l,r = r,(self.f(r,self.lk[i]))^l
            
            
        return l*16+r
    
    def valInv(self,octetC):
        """Renvoie l'antécédent de octet C
        >>> P = FBijFeistel(5)
        >>> P.valInv(10)
        5"""
        l, r = octetC//16, octetC%16
        for i in range(self.nbtours-1,-1,-1):
            
            r,l=l,r^self.f(l, self.lk[i])
            
        return l*16+r
    
    def affPlot(self):
        lx=[k for k in range(256)]
        ly=[self(x) for x in lx]
        plt.plot(lx,ly,".")
        plt.title(f'{self}')
        plt.show()
    
def f4b1(v4b,k):
    return ((v4b+2)^k)%16
    #il faudrait augmenter la taille de la clef
        
if __name__ == "__main__":
    dt.testmod()
    for i in range(1,17):
        FBijFeistel(f4b1,5,i).affPlot()
