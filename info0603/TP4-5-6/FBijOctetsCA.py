class FBijOctetsCA(object):
    """Une classe abstraite de bijectioe de [0..255]"""
   
    def __init__(self,dec=1):
        self.dec = dec
        
    def __repr__(self):
        return f'FBijOctets(dec)'
        
    def __call__(self,octet):
        return (octet+self.dec)%256
    
    def valInv(self,octetC):
        """Renvoie l'antécédent de octet C"""
        raise NotImplementedError
        
