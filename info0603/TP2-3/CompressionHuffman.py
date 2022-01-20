from CodeurCA import *
from Arbre import *
from Binaire603 import *
class CompresseurHuffman(CodeurCA):# Ne pas toucher
    """Un codeur doit surcharger les méthodes __init__ __repr__ __str__
    binCode, binDecode et codeurTest
    renvoyant et recevant un Binaire603
    C'est une forme de classe abstraites"""
    def __init__(self):
        raise NotImplementedError # Ne pas toucher
    def __str__(self):
        raise NotImplementedError# Ne pas toucher
    def __repr__(self):
        raise NotImplementedError# Ne pas toucher

    def dicoHuffmanDepuisArbre(arbre):
        """Renvoie les dictionnaires associant les étiquettes à leur codage d'Huffman(format txt)
        >>> CompresseurHuffman.arbreDepuisListePoderee([("B",0.3),("L",0.2),("E",O.2),("I",0.1),("A",0.1),("T",0.1),("S",0.1),("N",0.1)])
        >>> CompresseurHuffman.dicoHuffmanDepuisArbre(a) ({’000’: ’E’, ’0010’: ’S’, ’0011’: ’N’, ’0100’: ’A’, ’0101’: ’T’, ’011’: ’I’, ’10’: ’B’, ’11’: ’L’}, {’E’: ’000’, ’S’: ’0010’, ’N’: ’0011’, ’A’: ’0100’, ’T’: ’0101’, ’I’: ’011’, ’B’: ’10’, ’L’: ’11’})
        >>> CompresseurHuffman.construireDicoH(arbre1,d)
        >>> print(d)
        ’0’: ’A’, ’10’: ’B’, ’11’: ’C’
        """
        
    def arbreDepuisListePonderee(lp):
        """Transforme la liste de couple (Etiquette,Entropie) en un tuple modélisant un arbre.
        Un arbre pondéré est un tuple de la forme (Etiquette,pondération) ou (Arbre,pondération)
        >>> CompresseurHuffman.arbreDepuisListePonderee([("A",0.2),("B",0.3),("C",0.4)])
        ((((('B', 0.3), ('A', 0.2)), 0.5), ('C', 0.4)), 0.9)
        """
        lpc=[]
        for i in lp:
            atmp = Arbre(i[1], i[0], None, None)
            lpc.append(atmp)
            
        
        while len(lpc)>1:
            lpc.sort(key=lambda x:x.freq, reverse=True)
            lpc = lpc[:-2]+ [Arbre.concatener(lpc[-2],lpc[-1])]
        
        return lpc[0]
        
    
    def codageHuffman(monBin,verbose=False):
        """Renvoie les dictionnaire associant les clés d’Huffman aux valeurs d’octets"
        >>> CompresseurHuffman.codageHuffman(Binaire603([5,5,5,5,5,5,5,5,6,6,6,7,7,9]))
        (’00’: 6, ’01’: 5, ’10’: 7, ’11’: 9, 6: ’00’, 5: ’01’, 7: ’10’, 9: ’11’)
        """
        lf,lc = monBin.lFrequencesEtCles()
    
    def binCode(self,monBin,verbose=False):
        """renvoie une chaine Binaire codée par Huffman"""
        
    def binDecode(self,monBin,verbose=False):
       """renvoie une chaine Binaire decodée par Huffman
       >>> monCodeur=CompresseurHuffman()
       
       >>> monBin=Binaire603([6,6,6,6,6,5,5,5,5,6,6,6,7,8,9,8,8])
       >>> monBinC=monCodeur.binCode(monBin)
       >>> monBin==monCodeur.binDecode(monBinC)
       True
       """

if __name__ == "__main__":
    import doctest
    doctest.testmod()
    monCodeur=CompresseurHuffman() #A modifier si repris dans une classe en héritant
    for k in range(5):
        monBin=Binaire603.exBin603(num=k,taille=25)
        print("Bin:",monBin)
        monBinCr=monCodeur.binCode(monBin)
        print("Bin Codée:",monBinCr)
        print("monBinCr décodé est égal à Monbin ?",monCodeur.binDecode(monBinCr)==monBin)


