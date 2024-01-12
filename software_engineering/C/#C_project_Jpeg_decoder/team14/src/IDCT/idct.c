#include "../../include/module_matriciel.h"
#define n (8)
#define pi (3.141592653589793)


float C(int p) {
    /* utile pour le calcul dans la somme */
    return ((p == 0) ? (1/sqrt(2)) : (1));
}


uint8_t saturation_unitaire(float valeur) {
/* traite les valeurs extrêmes des composantes et renvoit un uint8_t */
if (valeur < 0)
{
    return 0;
}

if (valeur > 255)
{
    return 255;
}

else 
{
    return (uint8_t) valeur;
}

}


float* pre_calcule_cos(int x) {
    float* tab = calloc(8, sizeof(float));
    for (uint8_t i = 0; i < 8; i++) {
        tab[i] = cos((2*x+1)*i*pi/(2*n));
    }
    return tab;
}


uint8_t transformation_spatiale_unitaire(int x, int y, int16_t **ancienne_image) {
    /* transforme un coefficient fréquentiel en coefficient spatial */
    float somme = 0;
    size_t tabdim[] = {8 , 8};
    float** tableau = calloc(8, sizeof(float*));
    for (uint8_t x = 0; x < 8; x++) {
        tableau[x] = pre_calcule_cos(x);
    }
    for (int  i = 0; i < n; i++ ) {
        for (int j = 0; j < n; j++ ) {
            somme += C(i)*C(j)*tableau[x][i]*tableau[y][j]*ancienne_image[i][j];
        }
    }

    free_matrice_entier_sansp_float(tableau, tabdim);
    somme = somme/sqrt(2*n);
    somme += 128;
    return saturation_unitaire(somme);

}


uint8_t **IDCT_MCU(int16_t ** mcu_basique) {
    /* opère la transformation idct sur une matrice 8*8*/
    size_t ligne;
    size_t colonne;

    uint8_t **mcu_transforme = calloc(8, sizeof(uint8_t*));

    for (ligne = 0; ligne <= 7; ligne ++)
    {
        mcu_transforme[ligne] = calloc(8, sizeof(uint8_t));
        for (colonne = 0; colonne <= 7; colonne++)
        {
            mcu_transforme[ligne][colonne] = transformation_spatiale_unitaire(ligne, colonne, mcu_basique);
        }
    }

    return mcu_transforme;
}


void IDCT_vecteur_et_free(uint8_t *** vecteur, size_t taille_vecteur, int16_t ***vecteur_a_transfo) {
    /*créé les matrices de coordonnées spatiales dans le nouveau vecteur avec en-tête initialisée en libérant au passage le vecteur de blocs de fréquences. */

    size_t dim_bloc[2] = {8, 8};

    for (size_t bloc = 0; bloc < taille_vecteur; bloc++) 
    {
        vecteur[bloc] = init_matrice_sansp_uint8(dim_bloc, 0);
        vecteur[bloc] = IDCT_MCU(vecteur_a_transfo[bloc]);
        free_matrice_entier_sansp_int16(vecteur_a_transfo[bloc], dim_bloc);
    }

    free(vecteur_a_transfo);
}

 void IDCT_gris(struct data_1 *flux) {
    /* opère idct sur toutes les matrices 8*8 de vect_fin_idct_gris*/
    
    
    if (flux->couleurs == false) {
    flux -> vect_fin_idct_gris = calloc(flux -> lens_composantes[0], sizeof(uint8_t**));
    IDCT_vecteur_et_free(flux -> vect_fin_idct_gris, flux -> lens_composantes[0], flux -> vect_fin_zz[0]);
}
 }


void IDCT_couleurs(struct data_1 *flux) 
/* opère idct sur toutes les matrices 8*8 de chacune des 3 composantes de vect_fin_idct dans le cas coloré */
{
    flux -> vect_fin_idct[0] = calloc(flux -> lens_composantes[0], sizeof(uint8_t**));
    flux -> vect_fin_idct[1] = calloc(flux -> lens_composantes[1], sizeof(uint8_t**));
    flux -> vect_fin_idct[2] = calloc(flux -> lens_composantes[2], sizeof(uint8_t**));

    IDCT_vecteur_et_free(flux -> vect_fin_idct[0], flux -> lens_composantes[0], flux -> vect_fin_zz[0]);
    IDCT_vecteur_et_free(flux -> vect_fin_idct[1], flux -> lens_composantes[1], flux -> vect_fin_zz[1]);
    IDCT_vecteur_et_free(flux -> vect_fin_idct[2], flux -> lens_composantes[2], flux -> vect_fin_zz[2]);
    

}
