import random as rand
from CodeurCA import *
from Binaire603 import *
class Permutation603(CodeurCA):# Ne pas toucher
    
    

    def __init__(self, lpermutation=[1,2,3,4,5,6,7,8,
 9,
 10,
 11,
 12,
 13,
 14,
 15,
 16,
 17,
 18,
 19,
 20,
 21,
 22,
 23,
 24,
 25,
 26,
 27,
 28,
 29,
 30,
 31,
 32,
 33,
 34,
 35,
 36,
 37,
 38,
 39,
 40,
 41,
 42,
 43,
 44,
 45,
 46,
 47,
 48,
 49,
 50,
 51,
 52,
 53,
 54,
 55,
 56,
 57,
 58,
 59,
 60,
 61,
 62,
 63,
 64,
 65,
 66,
 67,
 68,
 69,
 70,
 71,
 72,
 73,
 74,
 75,
 76,
 77,
 78,
 79,
 80,
 81,
 82,
 83,
 84,
 85,
 86,
 87,
 88,
 89,
 90,
 91,
 92,
 93,
 94,
 95,
 96,
 97,
 98,
 99,
 100,
 101,
 102,
 103,
 104,
 105,
 106,
 107,
 108,
 109,
 110,
 111,
 112,
 113,
 114,
 115,
 116,
 117,
 118,
 119,
 120,
 121,
 122,
 123,
 124,
 125,
 126,
 127,
 128,
 129,
 130,
 131,
 132,
 133,
 134,
 135,
 136,
 137,
 138,
 139,
 140,
 141,
 142,
 143,
 144,
 145,
 146,
 147,
 148,
 149,
 150,
 151,
 152,
 153,
 154,
 155,
 156,
 157,
 158,
 159,
 160,
 161,
 162,
 163,
 164,
 165,
 166,
 167,
 168,
 169,
 170,
 171,
 172,
 173,
 174,
 175,
 176,
 177,
 178,
 179,
 180,
 181,
 182,
 183,
 184,
 185,
 186,
 187,
 188,
 189,
 190,
 191,
 192,
 193,
 194,
 195,
 196,
 197,
 198,
 199,
 200,
 201,
 202,
 203,
 204,
 205,
 206,
 207,
 208,
 209,
 210,
 211,
 212,
 213,
 214,
 215,
 216,
 217,
 218,
 219,
 220,
 221,
 222,
 223,
 224,
 225,
 226,
 227,
 228,
 229,
 230,
 231,
 232,
 233,
 234,
 235,
 236,
 237,
 238,
 239,
 240,
 241,
 242,
 243,
 244,
 245,
 246,
 247,
 248,
 249,
 250,
 251,
 252,
 253,
 254,
 255,
 0]):
        """
        >>> Permutation603([1,2,3,0])
        Permutation603([1, 2, 3, 0])"""
        
        self.lp=lpermutation
        self.li=lpermutation.copy()
        self.li.sort()
        

    def __pow__(self, n):
        """
        >>> Permutation603([1,2,3,0])**2
        Permutation603([2, 3, 0, 1])
        >>> Permutation603([1, 2, 3, 0])**4
        Permutation603([0, 1, 2, 3])
        >>> Permutation603([1, 2, 3, 0])**(-1)
        Permutation603([3, 0, 1, 2])"""
        
        for i in range(len(self.lp)):
            self.lp[i]=((self.lp[i]+n-1)%len(self.lp))
        return self
        
    def ordre(self): 
        """Renvoie l'ordre de la permutation
        >>> Permutation603([1,2,3,0]).ordre()
        4
        >>> Permutation603([1,0,2,3]).ordre()
        2"""
        c=0
        for i in range(len(self.lp)):
            if (self.lp[i]!=self.li[i]):
                c=c+1
        return c
            
    def permutAlea(n=6):
        """Renvoie une permutation aléatoire sans utiliser shuffle, seulement randint"""
        l=[]
        for i in range(0,n):
            l.append(i)
        res = Permutation603(l)
        
        for i in range(0,n):
            r=rand.randint(0,n-1)
            res.lp[i],res.lp[r]=res.lp[r],res.lp[i]
        return res
        
    
    def permutKieme(k,n=6):
        """Renvoie la kieme permutation de Sn ce qui permet d'associer des clés aux permutations
        >>> lr=[Permutation603.permutKieme(k,n=3) for k in range(6)]
        >>> le=[[0,1,2],[0,2,1],[1,0,2],[1,2,0],[2,1,0],[2,0,1]]
        >>> sum([1 if Permutation603(l) in lr else 0 for l in le])
        6"""
        pass
    def numPermutation(self):
        """Renvoie le numéro de la permutation
        >>> Permutation603.permutKieme(100,n=5).numPermutation()
        100"""
        pass


    def __str__(self):
        return f'Permutation603({self.lp})'
    def __repr__(self):
        return f'Permutation603({self.lp})'

    def binCode(self,monBinD:Binaire603)->Binaire603:
        lb=[(self.lp[b]) for b in monBinD]
        
        return Binaire603(lb)
        
    def binDecode(self,monBinC:Binaire603)->Binaire603:
        lb=[(self.lp.index(b)) for b in monBinC]
        
        return Binaire603(lb)



if __name__ == "__main__":
    import doctest
    doctest.testmod()
    monCodeur=Permutation603() #A modifier si repris dans une classe en héritant
    for k in range(5):
        monBin=Binaire603.exBin603(num=k,taille=25)
        print("Bin:",monBin)
        monBinCr=monCodeur.binCode(monBin)
        print("Bin Codée:",monBinCr)
        print("monBinCr décodé est égal à Monbin ?",monCodeur.binDecode(monBinCr)==monBin)


