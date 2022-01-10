
from Binaire603 import *
class CompresseurParRepetition(object):# Ne pas toucher
    """Un codeur doit surcharger les méthodes __init__ __repr__ __str__
    binCode, binDecode et codeurTest
    renvoyant et recevant un Binaire603
    C'est une forme de classe abstraites    
    """
    def __init__(self ):
        pass

    def __str__(self):
        """Compresseur par répétition"""
        raise NotImplementedError# Ne pas toucher
    def __repr__(self):
        """Compresseur par répétition appel au constructeur
        CompresseurParRepetition()"""
        raise NotImplementedError# Ne pas toucher

    def binCode(self,monBinD:Binaire603)->Binaire603:
        """>>> CompresseurParRepetition().binCode(Binaire603([7,7,7,8,8,6,5,7,7,8]))
        Binaire603([3,7,2,8,1,6,1,5,2,7,1,8])"""
        n=1
        res=[]
        #for k,v in enumerate(self):

        for k in range(len(self)):
            if self(k)==self(k+1):
                n+=1
            else:
                res.append(n,self(k))
                n=1
        
        return res
                
        
        raise NotImplementedError# Ne pas toucher
    def binDecode(self,monBinC:Binaire603)->Binaire603:
        raise NotImplementedError# Ne pas toucher



if __name__ == "__main__":
    import doctest
    doctest.testmod()
    monCodeur=CompresseurParRepetition() #A modifier si repris dans une classe en héritant
    for k in range(5):
        monBin=Binaire603.exBin603(num=k,taille=25)
        print("Bin:",monBin)
        monBinCr=monCodeur.binCode(monBin)
        print("Bin Codée:",monBinCr)
        print("monBinCr décodé est égal à Monbin ?",monCodeur.binDecode(monBinCr)==monBin)


