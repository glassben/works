#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>



struct data_1
/*Structure qui nous sert de la fin du décodage RLE jusqu'à la fin de l'écriture dans le fichier pgm ou ppm.*/
{
   
    int16_t ***vect_fin_rle_et_qz;       /*Ce dernier peut-être vu de la manière suivante : int16_t **vect_fin_rle_et_qz[3]*/
                                         /*vecteur de vecteurs à 64 éléments pour Y ([0]), puis pour Cb ([1]), puis pour Cr([1]), renvoyé après le décodage et utilisé par la suite pour la quantification inverse*/



    int16_t ***vect_fin_zz[3];           /*vecteur de blocs pour Y ([0]), puis pour Cb ([1]), puis pour Cr([1]), cela après le dé-zig-zag pour chaque vecteur de 64 éléments.*/



    uint8_t ***vect_fin_idct_gris;       /*vecteur de blocs uniquement pour Y utilisé directement pour ecriture pgm dans le cas d'une image en niveaux de gris*/



    uint8_t ***vect_fin_idct[3];         /*vecteur de blocs pour Y ([0]), puis pour Cb ([1]), puis pour Cr([1]), cela après l'idct pour chaque bloc*/



    uint8_t ***vect_fin_upsampling[3];   /*vecteur de MCUS pour Y ([0]), puis pour Cb ([1]), puis pour Cr([1])*/

  

    size_t lens_composantes[3];          /*nombre total de blocs pour Y, puis pour Cb, puis pour Cr.*/

    bool couleurs;

    size_t len_mcus;                     /*nombre total de mcus pour chaque composante. Celui-ci est bien entendu le même pour chaque compossante*/

    uint16_t dim_image[2];               /*hauteur puis largeur*/
    uint8_t param_sampling[6];           /*h_Y puis v_Y,  puis h_Cb puis v_Cb,  puis h_Cr puis v_Cr*/
    uint8_t *tables_quantification[2];   /*la premiere pour Y et la deuxième pour les chrominances*/
};







/*Les éléments des matrices des fonctions ci-dessous sont directement des valeurs et non des pointeurs.*/




extern float **init_matrice_sansp_float(size_t dim[2], float valeur_base);
    /*Initialise une matrice dont les éléments sont directement des nombres flottants avec une valeur de base choisie.*/

extern int16_t **init_matrice_sansp_int16(size_t dim[2], int16_t valeur_base);    
    /*Initialise une matrice dont les éléments sont directement des nombres de type int16_t avec une valeur de base choisie.*/

extern uint8_t **init_matrice_sansp_uint8(size_t dim[2], uint8_t valeur_base);
    /*Initialise une matrice dont les éléments sont directement des nombres de type uint8_t avec une valeur de base choisie.*/











extern void free_matrice_generale_sansp_float(float **A, size_t dim_A[2], int free_entier);
    /*free différentes structures de la matrice de flottants selon choix (juste lignes ou tout)*/
   

extern void free_matrice_entier_sansp_float(float **A, size_t dim_A[2]);
    /*free toute la matrice de nombre flottants*/





extern void free_matrice_generale_sansp_int16(int16_t **A, size_t dim_A[2], int free_entier);
    /*free différentes structures de la matrice de nombres en int16_t selon choix (juste lignes ou tout)*/


extern void free_matrice_entier_sansp_int16(int16_t **A, size_t dim_A[2]);
    /*free toute la matrice de nombres en int16_t*/





extern void free_matrice_generale_sansp_uint8(uint8_t **A, size_t dim_A[2], int free_entier);
    /*free différentes structures de la matrice de nombres en uint8_t selon choix (juste lignes ou tout)*/


extern void free_matrice_entier_sansp_uint8(uint8_t **A, size_t dim_A[2]);
    /*free toute la matrice de nombres en uint8_t*/














extern void print_matrice_sansp_float(float **A, size_t dim_A[2]);
    /*print sur la sortie standard la matrice de nombres flottants.*/

extern void print_matrice_sansp_int16(int16_t **A, size_t dim_A[2]);
    /*print sur la sortie standard la matrice de nombres en int16_t.*/

extern void print_matrice_sansp_uint8(uint8_t **A, size_t dim_A[2]);
    /*print sur la sortie standard la matrice de nombres en uint8_t.*/
