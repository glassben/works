#! python3
import sys 
import approximate_pi2
import copy
import subprocess
VERT="0 0 255"
ROUGE="255 0 0"

taille= int(sys.argv[1])
nbr_de_point=int(sys.argv[2])
nbr_chiffre=int(sys.argv[3])

class Error(Exception):
    pass



if taille<100:
    raise Error('taille must be over 100')
if nbr_de_point<100:
    raise Error("nbr_de_point must be over 100")
if not 1<=nbr_chiffre<=5:
    raise Error("nbr_chiffre must be between 1 and 5")


(a,b)=approximate_pi2.approximation(nbr_de_point)

if nbr_chiffre+2<len(str(a)):
    nb=str(a)[0:nbr_chiffre+2]
else:
    nb=str(a)

def trace_moi_verticale(point_de_depart,M,longueur_trait_verticale,largeur_trait_verticale):
    for i in range(longueur_trait_verticale):
        for j in range(largeur_trait_verticale):
            M[point_de_depart[0]+i][point_de_depart[1]+j]="0 0 0"

def trace_moi_horizontale(point_de_depart,M,longueur_trait_horizontale,largeur_trait_horizontale):
    for i in range(longueur_trait_horizontale):
        for j in range(largeur_trait_horizontale):
            M[point_de_depart[0]+i][point_de_depart[1]+j]="0 0 0"

def trace_moi_pixel1(point_de_depart,L):
    return trace_moi_horizontale(point_de_depart,L,longueur_trait_horizontale,largeur_trait_horizontale)

def trace_moi_pixel2(point_de_depart,L):
    return trace_moi_verticale(point_de_depart,L,longueur_trait_verticale,largeur_trait_verticale)

def trace_moi_pixel3(point_de_depart,L):
    point1=[point_de_depart[0],point_de_depart[1]]
    point1[1]+=(largeur_trait_horizontale-longueur_trait_horizontale)
    return trace_moi_verticale(point1,L,longueur_trait_verticale,largeur_trait_verticale)

def trace_moi_pixel4(point_de_depart,L):
    point1=[point_de_depart[0],point_de_depart[1]]
    point1[0]+=(longueur_trait_verticale-largeur_trait_verticale)
    return trace_moi_horizontale(point1,L,longueur_trait_horizontale,largeur_trait_horizontale)

def trace_moi_pixel5(point_de_depart,L):
    point1=[point_de_depart[0],point_de_depart[1]]
    point1[0]+=(longueur_trait_verticale)
    return trace_moi_verticale(point1,L,longueur_trait_verticale,largeur_trait_verticale)

def trace_moi_pixel6(point_de_depart,L):
    point1=[point_de_depart[0],point_de_depart[1]]
    point1[0]+=(longueur_trait_verticale)
    point1[1]+=(largeur_trait_horizontale-longueur_trait_horizontale)
    return trace_moi_verticale(point1,L,longueur_trait_verticale,largeur_trait_verticale)

def trace_moi_pixel7(point_de_depart,L):
    point1=[point_de_depart[0],point_de_depart[1]]
    point1[0]+=(2*longueur_trait_verticale-largeur_trait_verticale)
    return trace_moi_horizontale(point1,L,longueur_trait_horizontale,largeur_trait_horizontale)


longueur_trait_verticale=int((taille/4))
largeur_trait_verticale=int((taille/(20*nbr_chiffre)))
longueur_trait_horizontale=(largeur_trait_verticale)
largeur_trait_horizontale=int((longueur_trait_verticale/4))
espace=longueur_trait_horizontale

def trace_point(point_de_depart,M,lettre):
    if lettre=='0':
        trace_moi_pixel1(point_de_depart,M)
        trace_moi_pixel2(point_de_depart,M)
        trace_moi_pixel3(point_de_depart,M)
        trace_moi_pixel5(point_de_depart,M)
        trace_moi_pixel6(point_de_depart,M)
        trace_moi_pixel7(point_de_depart,M)
        point_de_depart[1]+=(largeur_trait_horizontale+espace)
        return point_de_depart
    elif lettre=='1':
        trace_moi_pixel3(point_de_depart,M)
        trace_moi_pixel6(point_de_depart,M)
        point_de_depart[1]+=(largeur_trait_horizontale+espace)
        return point_de_depart
    elif lettre=='2':
        trace_moi_pixel1(point_de_depart,M)
        trace_moi_pixel3(point_de_depart,M)
        trace_moi_pixel4(point_de_depart,M)
        trace_moi_pixel5(point_de_depart,M)
        trace_moi_pixel7(point_de_depart,M)
        point_de_depart[1]+=(largeur_trait_horizontale+espace)
        return point_de_depart
    elif lettre=='3':
        trace_moi_pixel1(point_de_depart,M)
        trace_moi_pixel3(point_de_depart,M)
        trace_moi_pixel4(point_de_depart,M)
        trace_moi_pixel6(point_de_depart,M)
        trace_moi_pixel7(point_de_depart,M)
        point_de_depart[1]+=(largeur_trait_horizontale+espace)
        return point_de_depart
    elif lettre=='4':
        trace_moi_pixel2(point_de_depart,M)
        trace_moi_pixel3(point_de_depart,M)
        trace_moi_pixel4(point_de_depart,M)
        trace_moi_pixel6(point_de_depart,M)
        point_de_depart[1]+=(largeur_trait_horizontale+espace)
        return point_de_depart
    elif lettre=='5':
        trace_moi_pixel1(point_de_depart,M)
        trace_moi_pixel2(point_de_depart,M)
        trace_moi_pixel4(point_de_depart,M)
        trace_moi_pixel6(point_de_depart,M)
        trace_moi_pixel7(point_de_depart,M)
        point_de_depart[1]+=(largeur_trait_horizontale+espace)
        return point_de_depart
    elif lettre=='6':
        trace_moi_pixel1(point_de_depart,M)
        trace_moi_pixel2(point_de_depart,M)
        trace_moi_pixel4(point_de_depart,M)
        trace_moi_pixel5(point_de_depart,M)
        trace_moi_pixel6(point_de_depart,M)
        trace_moi_pixel7(point_de_depart,M)
        point_de_depart[1]+=(largeur_trait_horizontale+espace)
        return point_de_depart
    elif lettre=='7':
        trace_moi_pixel1(point_de_depart,M)
        trace_moi_pixel3(point_de_depart,M)
        trace_moi_pixel6(point_de_depart,M)
        point_de_depart[1]+=(largeur_trait_horizontale+espace)
        return point_de_depart
    elif lettre=='8':
        trace_moi_pixel1(point_de_depart,M)
        trace_moi_pixel2(point_de_depart,M)
        trace_moi_pixel3(point_de_depart,M)
        trace_moi_pixel4(point_de_depart,M)
        trace_moi_pixel5(point_de_depart,M)
        trace_moi_pixel6(point_de_depart,M)
        trace_moi_pixel7(point_de_depart,M)
        point_de_depart[1]+=(largeur_trait_horizontale+espace)
        return point_de_depart
    elif lettre=='9':
        trace_moi_pixel1(point_de_depart,M)
        trace_moi_pixel2(point_de_depart,M)
        trace_moi_pixel3(point_de_depart,M)
        trace_moi_pixel4(point_de_depart,M)
        trace_moi_pixel6(point_de_depart,M)
        trace_moi_pixel7(point_de_depart,M)
        point_de_depart[1]+=(largeur_trait_horizontale+espace)
        return point_de_depart
    else:
        point1=[point_de_depart[0],point_de_depart[1]]
        point1[0]+=(2*longueur_trait_verticale-largeur_trait_verticale)
        trace_moi_verticale(point1,L,largeur_trait_verticale,largeur_trait_verticale)
        point_de_depart[1]+=(largeur_trait_verticale+espace)
        return point_de_depart
        
        
    
M=[["255 255 255" for i in range(taille)]for i in range(taille)]
ma_constante=0.0
for k in range(10):
    for j in range(int(k*(nbr_de_point/10)),int((k+1)*(nbr_de_point/10))):
        if b[j][0]**2+b[j][1]**2<=1:
            M[int(((b[j][0]+1)*(taille)/2))][int(((b[j][1]+1)*(taille))/2)]=VERT
            ma_constante+=1.0
        else:
            M[int(((b[j][0]+1)*(taille))/2)][int(((b[j][1]+1)*(taille))/2)]=ROUGE
    L=copy.deepcopy(M)
    ma_constante_finale=4*ma_constante/((k+1)*(nbr_de_point/10.0))
    ma_constante_finale=f"{ma_constante_finale}"[0]+"."+f"{ma_constante_finale}"[2:len(nb)]
    point_de_depart=[int((taille-1)/6),int((taille-1)/6)]
    for u in range(len(ma_constante_finale)):
        trace_point(point_de_depart,L,ma_constante_finale[u])
    fichier=open(f"img{k}_"+nb[0]+'-'+nb[2:len(nb)]+".ppm","w")
    fichier.write("P3\n")
    fichier.write(f"{taille} {taille}\n")
    fichier.write("255\n")
    for i in range(taille):
        for v in range(taille):
            fichier.write(" ")
            fichier.write(L[i][v])
            fichier.write(" ")
        fichier.write("\n")
    fichier.close()


cmd=f'convert img*.ppm -delay 50 img_with_{nbr_chiffre}_decimals.gif'
subprocess.run(cmd,shell=True,check=True)
subprocess.run('rm img*.ppm',shell=True,check=True)




