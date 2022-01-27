from FBijOctetsCA import *

class FBijParDecallage(FBijOctetsCA):
    """Une classe de bijection par decallage"""
   
    def __init__(self,dec=1):
        """
        >>> FBijParDecallage(5)
        FBijDecalage(5)
        """
        self.dec = dec
        
    def __repr__(self):
        return f'FBijDecalage({self.dec})'
        
    def __call__(self,octet):
        """
        >>> P = FBijParDecallage(5)
        >>> P(5)
        10"""
        return (octet+self.dec)%256
    
    def valInv(self,octetC):
        """Renvoie l'antécédent de octet C
        >>> P = FBijParDecallage(5)
        >>> P.valInv(10)
        5"""
        return (octetC-self.dec)%256
    
        
if __name__ == "__main__":
    dt.testmod()
