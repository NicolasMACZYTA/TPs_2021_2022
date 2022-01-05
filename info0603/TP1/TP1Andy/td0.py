# -*- coding: utf-8 -*-
""">>> ex5()
"""

def ex5():
    lc=['a','b','c','d','e']
    n=0
    for c1 in lc:
        for c2 in lc:
            for c3 in lc:
                print (c1+c2+c3+" ")
                n+=1
    print(f" soit {n} listes de 3 éléments avec répétitions choisis parmi 5")

    n=0
    for c1 in lc:
        lc2=lc.copy()
        lc2.remove(c1)
        for c2 in lc2:
            lc3=lc2.copy()
            lc3.remove(c2)
            for c3 in lc3:
                print (c1+c2+c3+" ")
                n+=1
    print(f" soit {n} listes de 3 éléments sans répétitions choisis parmi 5")
    
    n=0
    for i1 in range(0,3):
        for i2 in range(i1+1,4):
            for i3 in range(i2+1,5):
                print (lc[i1]+lc[i2]+lc[i3]+" ")
                n+=1
    print(f" soit {n} ensembles de 3 éléments sans ordre et sans répétitions choisis parmi 5")



if __name__ == "__main__":
    import doctest
    doctest.testmod()