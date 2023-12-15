#!usr/env/bin python3 
import random as rd 
import sys 

nb=sys.argv[1]
nb=int(nb)

def approximation(nb):
    res=0
    L=[]
    for i in range(0,nb):
        a=rd.uniform(-1,1)
        b=rd.uniform(-1,1)
        L.append([a,b])
        if a**2+b**2<=1:
            res+=1
    return (4*res/nb,L)

if __name__=="__main__":
    print(approximation(nb)[0])

