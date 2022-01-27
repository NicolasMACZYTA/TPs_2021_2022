import doctest as dt
import matplotlib.pyplot as plt

class FBijOctetsCA(object):
    """Une classe abstraite de bijection de [0..255]"""
   
    def __init__(self,dec=1):
        self.dec = dec
        
    def __repr__(self):
        return f'FBijOctets(dec)'
        
    def __call__(self,octet):
        return (octet+self.dec)%256
    
    def valInv(self,octetC):
        """Renvoie l'antécédent de octet C"""
        raise NotImplementedError
    def affPlot(self):
        lx=[k for k in range(256)]
        ly=[self(x) for x in lx]
        plt.plot(lx,ly,".")
        plt.title("graphique bijection")
        plt.show()
        
if __name__ == "__main__":
    dt.testmod()