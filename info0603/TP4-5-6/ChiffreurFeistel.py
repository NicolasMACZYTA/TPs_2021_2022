from random import *
from Binaire603 import *
from CodeurCA import *
from Texte603 import *
from FBijFeistel import *


class ChiffreurFeistel(CodeurCA):# Ne pas toucher
    """Un codeur doit surcharger les méthodes __init__ __repr__ __str__
    binCode, binDecode et codeurTest
    renvoyant et recevant un Binaire603
    C'est une forme de classe abstraite"""
    def __init__(self, f, cle, nb_tours):
        self.fbij=FBijFeistel(f, cle, nb_tours)

    def __str__(self):
        return (f"Chiffreur de Feistel avec f={self.fbij}")
    
    def __repr__(self):
        return(f"ChiffreurFeistel({self.f}, {self.cle}, {self.nb_tours})")
    
    def binCode(self,monBinD:Binaire603)->Binaire603:
        """
        """
        assert isinstance(monBinD, Binaire603)
        
        retour=[]
        for elem in monBinD:
                retour.append(self.fbij(elem))

        return Binaire603(retour)
    
    def binDecode(self,monBinC:Binaire603)->Binaire603:
        """
        """
        assert isinstance(monBinC, Binaire603)
        retour=[]
        for elem in monBinC:
                retour.append(self.fbij.valInv(elem))

        return Binaire603(retour)
    
if __name__ == "__main__":
    import doctest
    doctest.testmod()
    #for k in range(1,17):
     #   FBijFeistel(f4b1, 113, k).afficheGraphique()
    bin=Texte603("dinosaure").toBinaire603()
    c=ChiffreurFeistel(f4b1, 0x0101, 2)
    binC=c.binCode(bin)
    print(Texte603(binC))
    binD=c.binDecode(binC)
    texte=Texte603("Ï7ƗƔċã#´Ɣ£").toBinaire603()
    print(Texte603(c.binDecode(texte)))
    print(Texte603(binD))
    