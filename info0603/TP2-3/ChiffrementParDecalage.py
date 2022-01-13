from CodeurCA import *
from Binaire603 import *
class ChiffrementParDecalage(CodeurCA):# Ne pas toucher
    """Un codeur doit surcharger les méthodes __init__ __repr__ __str__
    binCode, binDecode et codeurTest
    renvoyant et recevant un Binaire603
    C'est une forme de classe abstraites"""
    def __init__(self ):
        raise NotImplementedError # Ne pas toucher

    def __str__(self):
        raise NotImplementedError# Ne pas toucher
    def __repr__(self):
        raise NotImplementedError# Ne pas toucher

    def binCode(self,monBinD:Binaire603)->Binaire603:
        """
        >>> ChiffrementParDecalage(2).binCode(Binaire603([1,2,3,4,255]))
        Binaire603([0x03, 0x04, 0x05, 0x06, 0x01])
        """
        lf,lc = monBin.lFrequencesEtCles()
        
    def binDecode(self,monBinC:Binaire603)->Binaire603:
        """
        >>> ChiffrementParDecalage(2).binDecode(Binaire603([1,2,3,4,255]))
        Binaire603([0xff, 0x00, 0x001, 0x02, 0xfd])
        """

if __name__ == "__main__":
    import doctest
    doctest.testmod()
    monCodeur=ChiffrementParDecalage() #A modifier si repris dans une classe en héritant
    for k in range(5):
        monBin=Binaire603.exBin603(num=k,taille=25)
        print("Bin:",monBin)
        monBinCr=monCodeur.binCode(monBin)
        print("Bin Codée:",monBinCr)
        print("monBinCr décodé est égal à Monbin ?",monCodeur.binDecode(monBinCr)==monBin)


