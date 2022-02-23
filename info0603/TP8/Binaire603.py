from math import log
from random import random,randint
from ElmtZnZ import *
class Binaire603(list):#Voir Object ?

    def __init__(self,lbin):
        "lbin est une liste de nombres entre 0 et 255 qui sont donc assumés comme des octets"
        super().__init__(lbin)
        valide=True
        for b in lbin:
            valide = valide and Binaire603.estOctet(b)
        assert valide,"Les éléments d'un Binaire603 doivent être des octets"
        self=lbin

    def sauvegardeDansFichier(self,nomFic):
        "Enregistre dans un fichier nommé nomFic"
        with open(nomFic,"wb") as f:
            for b in self:
                f.write(bytes([b]))

    def bin603DepuisFichier(nomFic,verbose=False):
        "renvoie un Binaire603 d'après les données d'un fichier"
        if verbose:print(f"lecture du fichier :{nomFic}")
        with open(nomFic,"rb") as f:
            data = f.read()
            if verbose:print(f"data est de type : {type(data)}")
            b=Binaire603(data)
            if verbose:print(f"data : {b}")
        return b

    def exBin603(taille=1000,num=0):
        """Exemples de cette classe avec pour num==
        0: 255 fois 255 puis 254 fois 254 etc...
        1: un octet de chaque
        2: 1000 octets aléatoires
        3: 254 13 puis 255 14
        4: 254 13 puis 255 14 puis 256 15
        5: et plus: 1000 fois un octet sur deux à 255
        """
        if num==0:
            data=[]
            for i in range(255,0,-1):
                data+=[i]*i
        elif num==1:
            data=[k for k in range(256)]
        elif num==2:
            data=[randint(0,255) for k in range(256)]
        elif num==3:
            data=[13]*254+[14]*255
        elif num==4:
            data=[13]*254+[14]*255+[15]*256
        else:
            data=[(k%2)*255 for k in range(256)]
        while len(data)<taille:
            data+=data
        return Binaire603(data[:taille])

    def estOctet(val):
        """Renvoie true si val est un entier et si il se trouve dans [0..255]
        >>> Binaire603.estOctet(255) and not(Binaire603.estOctet(256))
        True
        >>> not(Binaire603.estOctet(-1))and not(Binaire603.estOctet("coucou")) and not(Binaire603.estOctet([128,12]))
        True
        """
        return isinstance(val,int) and val>=0 and val <=255

    def ajouteOctet(self,data):
        """Ajoute un octet ou une liste d'octets tout en vérifiant la validité des données
        >>> a=Binaire603.exBin603(10,1)

        >>> a.ajouteOctet(10)

        >>> a==Binaire603.exBin603(11,1)
        True
        >>> a.ajouteOctet([11,12])

        >>> a==Binaire603.exBin603(13,1)
        True
        """
        if isinstance(data,list):
            for oc in data:
                assert Binaire603.estOctet(oc)
                self+=[oc]
        else:
            assert Binaire603.estOctet(data)
            self+=[data]
    def lisOctet(self,pos):
        """Lis un octet et incrémente pos
            Utilisation val,pos=monBin.lisOctet(pos) comme suit
            >>> a,pos = Binaire603.exBin603(10,1) ,5

            >>> val,pos = a.lisOctet(5)

            >>> val,pos
            (5, 6)
            """
        return self[pos],pos+1
    def __str__(self):
        "Renvoie une chaine de caractère permettant de visualiser Binaire603 self"
        s=f"{len(self)} octets :"
        if len(self)<=150 :
            for oc in self:
                s+=f" {oc:02x}"
        else:
            for oc in self[:100]:
                s+=" "+f"{oc:02x}"
            s+="........"
            for oc in self[-50:-1]:
                s+=" "+f"{oc:02x}"
        return s
    def __repr__(self):
        """Renvoie une chaine de caractère représentant TOUTES les données du Binaire603 self
        sous la forme d'un appel à son constructeur ex: Binaire603([ 0x57, 0x26, 0xfd]) """
        s="Binaire603(["
        for oc in self:
                s+=" "+f"0x{oc:02x}," # https://docs.python.org/fr/3/library/string.html
        return s[:-1]+ "])"
    def __eq__(self,other):
        """Renvoie True lorsque les octets sont égaux deux à deux
        >>> Binaire603([ 0xcb, 0xba])==Binaire603([ 0xcb, 0xba])
        True
        >>> Binaire603([ 0xcb, 0xba])==Binaire603([ 0xcb])
        False
        >>> Binaire603([ 0xcb, 0xba])==Binaire603([ 0xcb, 0xbb])
        False
        """
        #todo:  voir le super pour comparé les références
        if len(self)!=len(other): return False
        k,n = 0, len(self)
        res= True
        while res and k<n:
            res= (self[k]==other[k])
            k+=1
        return res

    def lFrequencesEtCles(self):
        """Renvoie la fréquence de chaque octet sous la forme d'une liste ex : lf[13]=0.1
        Ainsi que la liste des 256 octets triés dans l'ordre décroissant
        Voir : https://linuxhint.com/sort-lambda-python/
        >>> lf,lc=Binaire603.exBin603(2000,3).lFrequencesEtCles()

        >>> int(lf[13]*1000),lc[0]
        (507, 13)
        >>> Binaire603([8,8,8,8,7,7,7,6,6,6]).lFrequencesEtCles()
        ([0, 0, 0, 0, 0, 0, 0.30000000000000004, 0.30000000000000004, 0.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [8, 6, 7, 0, 1, 2, 3, 4, 5, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255])
        """
        n=len(self)
        lf=[0 for k in range(256)]
        lc = [h for h in range(256)]
        for i in self:
            lf[i]+=1/n
        lctrie = sorted(lc, key=lambda x: lf[x], reverse=True)
        
        return lf, lctrie

    def dFrequences(self):

        "Renvoie le dictionnaire des fréquences "
        df=dict()
        n=len(self )
        for oc in range(256):
            df[oc]=0
        for oc in self:
            df[oc]+=1/n
        return sorted(df,key = lambda x:df[x],reverse=True)

    def affFreq(self):
        "Affiche le Tableau des fréquences de la liste et son entropie"
        lf,lc=self.lFrequencesEtCles()
        e=self.entropie()
        print(f"{lf}\nLa liste précédente a une entropie de {e}")

    def entropie(self):
        """
        >>> monBin=Binaire603([6,6,6,6,6,6,6,6,5,5,5,5,5,5,7,7,7,7,8,9])
        >>> lf,lc = monBin.lFrequencesEtCles()
        >>> lc[0] #l'élément le plus fréquent
        6
        >>> lf[lc[1]]
        0.3
        >>> monBin.entropie()
        1.9464393446710155
        """
        lf,lc = self.lFrequencesEtCles()
        res = 0
        for i in lf:
            if i!=0:
                res+=(i*log2(i))
            
        return -res


    def ajouteLongueValeur(self,val):
        """Ajoute une valeur entière de taille qulconque de telle façon qu'elle
        puisse être récupérable par lisLongueValeur"""
        raise NotImplementedError
    def lisLongueValeur(self,pos):
        """Renvoie tout ce qu'il faut pour enregistrer/ajouter une valeur entière
        de taille qulconque"à la position pos
        Renvoie cette valeur et la nouvelle valeur de pos
        >>> monBin=Binaire603([12,13])
        >>> monBin.ajouteOctet(15)
        >>> monBin.ajouteLongueValeur(1000)
        >>> monBin.ajouteLongueValeur(100000)
        >>> pos=2
        >>> v0,pos=monBin.lisOctet(pos)
        >>> v1,pos=monBin.lisLongueValeur(pos)
        >>> v2,pos=monBin.lisLongueValeur(pos)
        >>> v0,v1,v2
        (15, 1000, 100000)
        """
        raise NotImplementedError

    def demo():
        for ext in ["txt","odt","pdf","py","odp","zip","jpg","png","pcx","bmp"]:

            print(f"L'entropie du fichier {'Exemple.'+ext} est de : {Binaire603.bin603DepuisFichier('Exemple.'+ext).entropie():1.3f}")

        for k in range(5):
            monBin=Binaire603.exBin603(num=k,taille=2000) #Bug de clé trop longue pour taille =100000
            print("Bin:",repr(monBin))
            monBin.affFreq()
if __name__ == "__main__":
    import doctest
    doctest.testmod()
    Binaire603.demo()