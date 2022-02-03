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
        self.cle = rand.seed(cle)
        self.nbtours = nbtours
        
    def __repr__(self):
        return f'FBijeistel({self.nbtours})'
        
    def __call__(self,octet):
        """
        >>> P = FBijFeistel(5)
        >>> P(5)
        10"""
        l, r = octet//16, octet%16
        rand.seed(self.cle)
        for tour in range(self.nbtours):
            
            l,r = r,(self.f(r,rand.randint(0,15)))^l
           
            
        return l*16+r
    
    def valInv(self,octetC):
        """Renvoie l'antécédent de octet C
        >>> P = FBijFeistel(5)
        >>> P.valInv(10)
        5"""
        pass
    
def f4b1(v4b,k):
    return ((v4b+2)^k)%16
        
if __name__ == "__main__":
    dt.testmod()
    for i in range(1,17):
        FBijFeistel(f4b1,5,i).affPlot()
