from CodeurCA import *
from Binaire603 import *
from Texte603 import *
class ChiffrementParDecalage(CodeurCA):# Ne pas toucher
    """Un codeur doit surcharger les méthodes __init__ __repr__ __str__
    binCode, binDecode et codeurTest
    renvoyant et recevant un Binaire603
    C'est une forme de classe abstraites"""
    def __init__(self,dec):
        """initialisation du chiffrement par decalage"""
        self.dec = dec

    def __str__(self):
        return "Chiffreur par Decalage"
    
    def __repr__(self):
        return f'ChiffrementParDecalage()'

    def binCode(self,monBinD:Binaire603)->Binaire603:
        """
        >>> ChiffrementParDecalage(2).binCode(Binaire603([1,2,3,4,255]))
        Binaire603([ 0x03, 0x04, 0x05, 0x06, 0x01])
        >>> Texte603(ChiffrementParDecalage(1).binCode(Texte603("Bonjour").toBinaire603()))
        Texte603("Cpokpvs")
        """
        lb=[(b+self.dec)%256 for b in monBinD]
        
        return Binaire603(lb)
        
        
    def binDecode(self,monBinC:Binaire603)->Binaire603:
        """
        >>> ChiffrementParDecalage(2).binDecode(Binaire603([1,2,3,4,255]))
        Binaire603([ 0xff, 0x00, 0x01, 0x02, 0xfd])
        """
        lb=[(b-self.dec)%256 for b in monBinC]
        
        return Binaire603(lb)
        

if __name__ == "__main__":
    import doctest
    doctest.testmod()
    monCodeur=ChiffrementParDecalage(2) #A modifier si repris dans une classe en héritant
    for k in range(5):
        monBin=Binaire603.exBin603(num=k,taille=25)
        print("Bin:",monBin)
        monBinCr=monCodeur.binCode(monBin)
        print("Bin Codée:",monBinCr)
        print("monBinCr décodé est égal à Monbin ?",monCodeur.binDecode(monBinCr)==monBin)


