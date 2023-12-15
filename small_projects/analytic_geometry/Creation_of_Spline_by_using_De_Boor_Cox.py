# ApproxTensorBezierSurfaceStudents.py

# explicit case : we look for a Bezier function 
#         RxR  -->  R
#        (x,y) --> h(x,y)
# Part1 : without any constraints
# Part2 : with constraints at each corner

import numpy as np
import matplotlib.pyplot as plt
from scipy.special import binom

## Exercice 1
## le nombre minimum d'equation est n*m puisqu'on a une équation du type :
## A*X=Z donc il faut au moins qu'on ait le même nombre d'equation que celui d'inconnue qui représente X (les ai,j qui sont au nombre de n*m)
## Donc la largeur de la matrice A doit être égale à la largeur de la matrice Z qui est d'au minimum (n+1)*(m+1)(la largeur de la matrice X)

"""============================================================
functions
============================================================"""
def Bernstein(n, k, x):
    coeff = binom(n, k)
    return coeff * x**k * (1 - x)**(n - k)

# Evaluation of a tensor product polynomial expressed in Bernstein basis
# defined by a matrix of coefficients : CPz
# for values xc, yc
def SurfBezierExplicit(CPz,xc,yc):
    Nx,Ny = np.shape(CPz)
    Degx = Nx - 1
    Degy = Ny - 1
    z = 0.
    for i in range(Degx+1):
        for j in range(Degy+1):
            z += CPz[i,j] * Bernstein(Degx, i, xc) * Bernstein(Degy, j, yc)
    return z

"""=============================================================== 
PART 1
Least squares Approximation
by a tensor Bezier surface of bi-degree(n,m)
--> without any constraint
==============================================================="""
#plt.close()

#---------------------------------------------------
# WE IMPORT scattered data from 3 files :
# XX, YY, ZZ are 3 matrices with the same shape (30,28)
#---------------------------------------------------
XX = np.loadtxt('dataSailX.txt')
YY = np.loadtxt('dataSailY.txt')
ZZ = np.loadtxt('dataSailZ.txt')
n1, n2 = np.shape(XX)
NbPts = n1*n2

#---------------------------------------------------
# Display
#---------------------------------------------------
# We open a 3D figure :
fig = plt.figure()
ax = plt.axes(projection='3d')
ax.set_xlabel('x axis')
ax.set_ylabel('y axis')
ax.set_zlabel('z axis')
ax.set_title('3D data to be approximated')
ax.view_init(35, -40)

# and plot the scattered data
ax.scatter(XX, YY, ZZ, c='red', marker='.', s=10)

"""--------------------------------------------------------
LINEAR SYSTEM FOR LS APPROXIMATION
by a tensor product Bezier surface of degree n,m 
under constraints at corners
"""
m=6 #on choisit arbitrairement m et n tel que (m+1)*(n+1) soit inférieur ou égale à Nbpt
n=6

H=np.zeros((NbPts,(m+1)*(n+1))) #On crée une matrice H qui va contenir les Hi(x_u)Hj(x_u)
for u in range(NbPts):
    v=0
    for i in range(n+1):
        for j in range(m+1):
            H[u,j+v]=Bernstein(n,i,XX[u//n2,u%n2])*Bernstein(m,j,YY[u//n2,u%n2])
        v+=m+1



Z=ZZ.flatten() #On crée un vecteur colonne à partir de la matrice Z

Hprime=np.dot(np.transpose(H),H) #On créé la matrice H^t*H pour permettre d'obtenir une matrice carrée positive

B=np.dot(np.transpose(H),Z) #on crée la matrice H^t*Z qui est le résultat de la multiplication de H^t à droite de l'équation précédent

coeff=np.linalg.solve(Hprime,B) #on calcule la solution de l'équation H^t*HX=H^t*Z 

coeff=coeff.reshape((n+1,m+1)) #on redimensionne coeff de telle sorte qu'on ait la matrice (alphai,j) c



x = np.linspace(0, 1, 200) #on crée 200 points compris entre [0,1]

y = np.linspace(0, 1, 200) #on crée 200 points compris entre [0,1]

xv, yv = np.meshgrid(x, y)  #on crée un ensemble de [x,y]

ax.plot_surface(xv, yv, SurfBezierExplicit(coeff, xv, yv)) #on crée une surface reliants les (x,y,H(x,y))

plt.plot()

"""=============================================================== 
PART 2
Least squares Approximation
by a tensor Bezier surface of bi-degree(n,m)
--> with constraints at each corner
==============================================================="""
# Constraints at corners
z00 = -0.6
z01 = 0.5
z10 = 0.7
z11 = -0.7
# display
ax.scatter(0, 0, z00, c='red', marker='.', s=200)
ax.scatter(0, 1, z01, c='red', marker='.', s=200)
ax.scatter(1, 0, z10, c='red', marker='.', s=200)
ax.scatter(1, 1, z11, c='red', marker='.', s=200)

## Ici on ajoute une matrice de contrainte C  de longueur 4 , il faudra donc une valeur de N égale à m*n + 4. dans le cas où on a N=N1, on aura pas assez d'information pour en déduire une bonne approximation de h.

A=np.zeros((4,(n+1)*(m+1)))

L=[z00,z01,z10,z11]
Xc = [0, 0, 1, 1]
Yc = [0, 1, 0, 1]
for u in range(4):
    v=0
    for i in range(n+1):
        for j in range(m+1):
            A[u,j+v]=Bernstein(n,i,Xc[u])*Bernstein(m,j,Yc[u])
        v+=m+1



A_transpose=np.transpose(A)


M=np.zeros(((n+1)*(m+1)+4,(n+1)*(m+1)+4))

for i in range((n+1)*(m+1)):
    for j in range((n+1)*(m+1)):
        M[i,j]=Hprime[i,j]

for i in range((n+1)*(m+1)):
    for j in range((n+1)*(m+1),(n+1)*(m+1)+4):
        M[i,j]=A_transpose[i,j-(n+1)*(m+1)]

for i in range((n+1)*(m+1),(n+1)*(m+1)+4):
    for j in range(((n+1)*(m+1))):
        M[i,j]=A[i-(n+1)*(m+1),j]





RES=np.zeros(((n+1)*(m+1)+4,1))
for i in range((n+1)*(m+1)):
    RES[i]=B[i]

for j in range((n+1)*(m+1),(n+1)*(m+1)+4):
    RES[j]=L[j-(n+1)*(m+1)]

X=np.linalg.solve(M,RES)

coeff2=X[:(n+1)*(m+1)]
coeff2=coeff2.reshape((n+1,m+1))

x = np.linspace(0, 1, 200)

y = np.linspace(0, 1, 200)



xv, yv = np.meshgrid(x, y)


ax.plot_surface(xv,yv,SurfBezierExplicit(coeff2, xv, yv))
