from FBijOctetsCA import *

class FBijParDecallage(object):
    """Une classe de bijection par decallage"""
   
    def __init__(self,dec=1):
        raise NotImplementedError
        
    def __repr__(self):
        raise NotImplementedError
        
    def __call__(self,octet):
        raise NotImplementedError
    
    def valInv(self,octetC):
        """Renvoie l'antécédent de octet C"""
        raise NotImplementedError
        
