class Arbre(object):
    
    def __init__(self,freq,val = '',fg = None,fd = None):
        """Arbre(frequence, valeur, filsgauche, filsdroit)
        >>> Arbre(0.2, 'A')
        Arbre(0.2,A,None,None)
        """
        self.val = val
        self.freq = freq
        self.fg = fg
        self.fd = fd
        
    def __repr__(self):
        if(self.isFeuille()): #verifier si val
            return f'({self.val}, {self.freq})'
        elif(self.fd==None and self.fg!=None):
            return f'(({self.fd}), {self.val}, {self.freq})'
        elif(self.fd!=None and self.fg==None):
            return f'(({self.fg}), {self.val}, {self.freq})'
        else:
            return f'(({self.fg}, {self.fd}), {self.val}, {self.freq})'
    
    def isFeuille(self):
        if(self.fg == None and self.fd == None):
            return True
        else:
            return False
    
    
    def concatener(ag,ad):
        res = Arbre(ag.freq+ad.freq,None,fg=ag,fd=ad)
        return res

    
