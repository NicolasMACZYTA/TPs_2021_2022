""">>> a=ElmtZnZ(7,8)
    >>> b=ElmtZnZ(2,8)
    >>> a==b
    False
    >>> a+b
    ElmtZnZ(1,8)
    >>> a+3
    ElmtZnZ(2,8)
    >>> 3+a
    ElmtZnZ(2,8)
    >>> a*b
    ElmtZnZ(6,8)
    >>> 3*a
    ElmtZnZ(5,8)
    >>> a*3
    ElmtZnZ(5,8)
    >>> a//b
    ElmtZnZ(3,8)
    >>> -a
    ElmtZnZ(1,8)
    >>> a-b
    ElmtZnZ(5,8)
    >>> a-3
    ElmtZnZ(4,8)
    >>> 3-a
    ElmtZnZ(4,8)
    >>> ElmtZnZ(2,7).valThChinois(ElmtZnZ(3,10))
    ElmtZnZ(23,70)
    >>> b.estInversible()
    False
    >>> (a+b).estInversible()
    True
    >>> ElmtZnZ(3,8).estInversible()
    True
    >>> b.inverse()
    '2 n est pas inversible'
    >>> a.inverse()
    ElmtZnZ(7,8)
    >>> a**2
    ElmtZnZ(1,8)
    >>> ElmtZnZ(2,13).logDiscret(8)
    3
    >>> ElmtZnZ(2,13).logDiscret(3)
    4

    
"""
import mathFunction
class ElmtZnZ(object):

    def __init__(self,a,n):
        self.a=a%n
        self.n=n
        
    def __str__(self):
        return f'{self.a} [{self.n}]'
    def __repr__(self):
        return f"ElmtZnZ({self.a},{self.n})"
    def __eq__(self,other):
        if(self.a==other.a and self.n==other.n):
            return True
        else :
            return False
    def __add__(self,other):
        if isinstance(other, ElmtZnZ):
            assert self.n==other.n,f"modulos différents"
            return ElmtZnZ(self.a+other.a,self.n)
        else:
            return ElmtZnZ(self.a+other,self.n)
    def __radd__(self,other):
        return self+other
    def __mul__(self,other):
        if isinstance(other, ElmtZnZ):
            assert self.n==other.n,f"modulos différents"
            return ElmtZnZ(self.a*other.a,self.n)
        else:
            return ElmtZnZ(self.a*other, self.n)
    def __rmul__(self,other):
        return self*other
    def __floordiv__(self,other):
        if isinstance(other,ElmtZnZ):
            assert self.n==other.n,f"modulos différents"
            return ElmtZnZ(self.a//other.a,self.n)
        else:
            return ElmtZnZ(self.a//other,self.n)
    def __neg__(self):
        return ElmtZnZ(-self.a, self.n)
    def __sub__(self,other):
        if isinstance(other,ElmtZnZ):
            assert self.n == other.n,f"modulos différents"
            return ElmtZnZ(self.a-other.a, self.n)
        else:
            return ElmtZnZ(self.a-other,self.n)
    def __rsub__(self,other):
        return self-other
    def valThChinois(self,other):
        """Vu que théorème chinois est lié aux équation modulaire,
        on considère que nous est passé 2 objets ElmtZnZ"""
        tBezout = mathFunction.bezout(self.n, other.n)
        c=self.a*other.n*tBezout[0]+other.a*self.n*tBezout[1]
        return ElmtZnZ(c,self.n*other.n)
    def estInversible(self):
        estInv=False
        for i in range(1,self.n):
            if (self.a*i)%self.n==1:
                estInv=True
        return estInv
        
    def inverse(self):
        for i in range(1,self.n):
            if (self.a*i)%self.n==1:
                return ElmtZnZ(i,self.n)
        return f'{self.a} n est pas inversible'
    
    def __pow__(self,pui):
        """On considère que l'utilisateur rentre forcément un entier"""
        return ElmtZnZ(self.a**pui,self.n)
    def logDiscret(self,b):
        if mathFunction.estPremier(self.n)==True:
            x=0
            while (self.a**x)%self.n != b:
                x=x+1
            return x
        else :
            return f'{self.n} non premier'
    
        
        
        
if __name__ == "__main__":
    import doctest
    doctest.testmod()
