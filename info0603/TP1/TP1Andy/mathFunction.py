""">>> eDiviseurs(60)=={1, 2, 3, 4, 5, 6, 10, 12, 15, 20, 60, 30}
True
>>> eDiviseurs(1)==set({1}) and eDiviseurs(13)==set({1, 13})
True
>>> PGCD(360,304)
8
>>> PGCD(517,513)==1 and PGCD(513,517)==1
True
>>> bezout(360,304)
(11, -13, 8)
>>> bezout(1254,493)
(-149, 379, 1)
>>> bezout(513,517)
(129, -128, 1)
"""
def eDiviseurs(a):
    e=set()
    for i in range(1,a+1):
        if a%i == 0:
            e.add(i)
    return e
"""renvoie l'ensemble des diviseurs positifs de A"""



def demoVitesse():
    for p in range(5,20):
        for k in range(100):
            ld=eDiviseurs(10**p+k)
            if len(ld)<=3 or len(ld)>20:
                print(f"{p}:eDiviseurs(10**p+k)=={eDiviseurs(10**p+k)}")

def PGCD(a,b):
    r=-1
    if b>a:
        temp = a
        a=b
        b=temp
    while r!=0:
        r=a%b
        a=b
        b=r
    return a

def bezout(a,b):
    """"Recherche des q avant effectuation de bezout"""
    lQ=[0]
    r=-1
    if b>a:
        temp = a
        a=b
        b=temp
    while r!=0:
        lQ.append(a//b)
        r=a%b
        a=b
        b=r
    d=a
    "debut recherche u et v "
    lU=[1,0]
    lV=[0,1]
    for i in range(1,len(lQ)):
        lU.append(lU[i-1]-lU[i]*lQ[i])
        lV.append(lV[i-1]-lV[i]*lQ[i])
    return lU[i],lV[i],d
def estPremier(a):
    for i in range(a-1,2):
        if a%i==0:
            return False
    return True
        
    

    

    





if __name__ == "__main__":
    import doctest
    doctest.testmod()