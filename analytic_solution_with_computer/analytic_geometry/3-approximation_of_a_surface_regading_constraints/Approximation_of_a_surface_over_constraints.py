# ApproxTensorBezierSurfaceStudents.py



# explicit case : we look for a Bezier function 

#         RxR  -->  R

#        (x,y) --> h(x,y)

# Part1 : without any constraints

# Part2 : with constraints at each corner



import numpy as np

import matplotlib.pyplot as plt

from scipy.special import binom



"""

============================================================

functions

============================================================

"""

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



Question 1: Il faut avoir avoir suffisamment de contraintes pour pouvoir

déterminer une solution exacte ou approchée pour les alphas.

Il nous faut donc au moins N0 = n * m données.



Dans le cas N=N0, on a exactement le bon nombre d'équation pour trouver une solution exacte.

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

X = XX.flatten()

Y = YY.flatten()

Z = ZZ.flatten()



n = 6

m = 6



# Construction des lignes de A

lines = []

for k in range(NbPts):

    line = []

    for i in range(n + 1):

        for j in range(m + 1):

            line.append(Bernstein(n, i, X[k]) * Bernstein(m, j, Y[k]))

    lines.append(line)



A = np.array(lines)



# Calcul de R = transpose(A) * A

R = np.dot(np.transpose(A), A)



# Second membre: B = transpose(a) * Z

B = np.dot(np.transpose(A), Z)



# Resolution de Rx = B

alphas = np.linalg.solve(R, B)



# Calcul de l'approximation

alphas_matrix = alphas.reshape((n + 1, m + 1))



approximation_Z = SurfBezierExplicit(alphas_matrix, X, Y)



# Plot

x = np.linspace(0, 1, 200)

y = np.linspace(0, 1, 200)



xv, yv = np.meshgrid(x, y)



surf = ax.plot_surface(xv, yv, SurfBezierExplicit(alphas_matrix, xv, yv))




"""

Décommenter pour avoir la seconde partie

"""







"""=============================================================== 

PART 2

Least squares Approximation

by a tensor Bezier surface of bi-degree(n,m)

--> with constraints at each corner



Question 3: Il faut cette fois N1 = n * m - 4 puisque l'on a déjà 

4 contraines imposées par le sujet.

De même, lorsque N = N1 on a une solution exacte



Question 5: Le système linéaire à résoudre est de taille (n * m + 4, n * m + 4).



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



# Constraints

C = [z00, z01, z10, z11]

Xc = [0, 0, 1, 1]

Yc = [0, 1, 0, 1]



# F matrix: Overdefined problem

F = A.copy()

FtF = np.transpose(F) @ F



# A matrix: Exact constraints

lines = []





for k in range(4):

    line = []

    for i in range(n + 1):

        for j in range(m + 1):

            line.append(Bernstein(n, i, Xc[k]) * Bernstein(m, j, Yc[k]))

    lines.append(line)



A = np.array(lines)

At = np.transpose(A)





# Matrice par bloc

R = np.block([

    [FtF, At],

    [A, np.zeros((4, 4))],

])



# Second membre

M = np.block([np.transpose(F) @ Z, np.array(C)])



# Resolution

S = np.linalg.solve(R, M)



# On retire les multiplicateurs de lagrange

alphas = S[:-len(C)]

alphas_matrix = alphas.reshape((n + 1, m + 1))

print(alphas_matrix)
# Plot

x = np.linspace(0, 1, 200)

y = np.linspace(0, 1, 200)



xv, yv = np.meshgrid(x, y)



ax.plot_surface(xv, yv, SurfBezierExplicit(alphas_matrix, xv, yv))



