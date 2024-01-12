#!/usr/bin/env python3
"""
compute sizes of all connected components.
sort and display.
"""
import time
from timeit import timeit
from sys import argv

from geo.point import Point


def load_instance(filename):
    """
    loads .pts file.
    returns distance limit and points.
    """
    with open(filename, "r") as instance_file:
        lines = iter(instance_file)
        distance = float(next(lines))
        points = [Point([float(f) for f in l.split(",")]) for l in lines]

    return distance, points


def print_components_sizes(distance, points):
    """
    affichage des tailles triees de chaque composante
    connexe"""
    
    
    indice=0
    dico={}
    while len(points)!=0:
        dico[indice]=[points[0]]
        exploration(points,points[0],distance,dico,indice)
        for x in dico[indice]:
            del(points[points.index(x)])
        indice+=1
    print(sorted([len(dico[j]) for j in range(indice)],reverse=True))
    
            
                
                
def exploration(points,point,distance,dico,i):
    current=point
    for x in points:
        if current.distance_to(x)<=distance and x not in dico[i]:
            dico[i].append(x)
            exploration(points,x,distance,dico,i)
         
        
    


def main():
    """
    ne pas modifier: on charge une instance et on affiche les tailles
    """
    for instance in argv[1:]:
        distance, points = load_instance(instance)
        print_components_sizes(distance, points)
main()