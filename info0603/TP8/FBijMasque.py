from FBijOctetsCA import *
import random as random

class FBijMasque(FBijOctetsCA):
    """Une classe abstraite de bijection de [0..255]"""
   
    def __init__(self,dec=1):
        self.dec = dec
        
    def __repr__(self):
        return f'FBijMasque({self.dec})'
        
    def __call__(self,octet):
        return (octet^self.dec)%256
    
    def valInv(self,octetC):
        """Renvoie l'antécédent de octet C"""
        return (octetC^self.dec)%256
        
if __name__ == "__main__":
    dt.testmod()
    for i in range(150):
        FBijMasque(i).affPlot()
