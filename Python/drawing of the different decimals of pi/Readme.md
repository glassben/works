English below 


Objectif: 
Créer un gif contenant l'évolution de l'estimation de pi par la méthode de Monte-Carlo,pour chaque dixième de points tirés. Les dimensions de l'image,le nombre de points de points à tirer et le nombre de décimales de chaque estimation de pi.

Contraintes:
-ne pas utiliser numpy 
-ne pas utiliser de modules externes qui fassent l'affichage des décimales à la main.
-utiliser subprocess ainsi qu'une commande bash pour générer le gif.

Choix d'implémentation:
-utilisation d'une fonction auxiliaire nommée approximate_pi2.py qui prend en argument d'entrée un nombre de point n et qui renvoie l'approximation de pi par la méthode de Gauss (on simule n fois 2 variables uniformes sur [-1,1] et on calcule la moyenne des points qui appartiennent au cercle de centre (0,0) et de rayon 1 que l'on multiplie par 4).
-utilisation de draw2.py qui prend en argument la taille de chaque image à partir desquels on réalise le gif, le nombre de points d'itération et le nombre de décimal de chaque approximation à afficher.
