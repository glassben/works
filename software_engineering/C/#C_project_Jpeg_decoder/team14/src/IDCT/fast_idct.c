#include "../../include/module_matriciel.h"
#define n (8)
#define pi (3.141592653589793)






// IDCT rapide


float saturation_sans_conversion(float valeur) {
    /* saturation qui ne renvoit pas un uint8_t dans les cas non-extrêmes, pour ne pas perdre en précision */
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
    return valeur;
}

}



void attribution(float res[], float ligne[]) {
    /* "stage 1" de l'algo de fast_idct on permute les coefficients */
    res[0] = ligne[0];
    res[1] = ligne[4];
    res[2] = ligne[2];
    res[3] = ligne[6];
    res[4] = ligne[7];
    res[5] = ligne[3];
    res[6] = ligne[5];
    res[7] = ligne[1];
}

void croisement(float entree[], float sortie[], int i, int j) {
    /* réalise l'opération de croisement de l'algo fast_idct*/
    sortie[i] = 0.5*(entree[i] + entree[j]);
    sortie[j] = 0.5*(entree[i] - entree[j]);
}

void croisement_etape4(int16_t entree[], float sortie[], int i, int j) {
    /* à cette étape l'entrée est encore un int16_t. On doit donc la transtyper. */
    sortie[i] = 0.5*(((float) entree[i]) + ((float) entree[j]));
    sortie[j] = 0.5*(((float) entree[i]) - ((float) entree[j]));
}

void rotation_inverse(float entree[], float sortie[], int i, int j, int mon_n, float k) {
    /* réalise l'opération de rotation inverse de l'algo fast_idct*/
    sortie[i] = (entree[i]/k)*cos(mon_n*pi/16) - (entree[j]/k)*sin(mon_n*pi/16);
    sortie[j] = (entree[j]/k)*cos(mon_n*pi/16) + (entree[i]/k)*sin(mon_n*pi/16);
}

void division_flottant(int16_t entree[], float sortie[], int i, float k) {
    /* "stage 4" pour l'idct sur lignes : division de l'entrée int16_t par un flottant. On transtype l'entrée. */
    sortie[i] = ((float) entree[i])/k;
}


void division_flottant_sans_cast(float entree[], float sortie[], int i, float k) {
    /*"stage 4" pour l'idct sur colonnes: division de l'entrée déjà flottante par un flottant. */
    sortie[i] = entree[i]/k;
}

float* fast_IDCT_ligne(int16_t * ligne_mcu, float* resultat) {
    /* applique fast_idct sur une ligne d'une matrice 8*8 de int16_t. Le résultat est un vecteur de flottant et on crée donc une fonction 
    similaire mais prenant en compte des flottants. Entre chaque "stage" de l'algo idct, on stocke des tableaux intermédiaires sur la pile : les valeurs
    contenues dans ces tableaux sont celles sur les lignes à l'étape correspondante:
    ligne_mcu: initialement, donc au début de l'étape 4
    sortie_temp_1 : entre 4 et 3
    sortie_temp_2: entre 3 et 2
    sortie_temp_3: entre 2 et 1
    sortie_temp_4: après étape 1 mais avant la réattribution
    resultat : après la réattribution, résultat définitif de l'idct */

    //etape 1 : croisements et multiplication par un réel
    float sortie_temp_1[8];
    division_flottant(ligne_mcu, sortie_temp_1, 3, sqrt(2));
    division_flottant(ligne_mcu, sortie_temp_1, 5, sqrt(2));
    croisement_etape4(ligne_mcu, sortie_temp_1, 1, 7);
    sortie_temp_1[2] = ligne_mcu[2];
    sortie_temp_1[4] = ligne_mcu[4];
    sortie_temp_1[6] = ligne_mcu[6];
    sortie_temp_1[0] = ligne_mcu[0];
    //etape 2 : croisements
    float sortie_temp_2[8];
    croisement(sortie_temp_1,sortie_temp_2, 0, 4);
    croisement(sortie_temp_1, sortie_temp_2, 7, 5);
    croisement(sortie_temp_1, sortie_temp_2, 1, 3);
    rotation_inverse(sortie_temp_1, sortie_temp_2, 2, 6, 6, sqrt(2));
    // etape 3 : croisements et rotations inverses 
    float sortie_temp_3[8];
    croisement(sortie_temp_2, sortie_temp_3, 4, 2);
    croisement(sortie_temp_2, sortie_temp_3, 0, 6);
    rotation_inverse(sortie_temp_2, sortie_temp_3, 3, 5, 1, 1);
    rotation_inverse(sortie_temp_2, sortie_temp_3, 7, 1, 3, 1);
    // etape 4 : croisements 
    float sortie_temp_4[8];
    croisement(sortie_temp_3, sortie_temp_4, 0, 1);
    croisement(sortie_temp_3, sortie_temp_4, 4, 5);
    croisement(sortie_temp_3, sortie_temp_4, 2, 3);
    croisement(sortie_temp_3, sortie_temp_4, 6, 7);
    // etape 5: attribuer les bons coeffs dans les bonnes cases
    attribution(resultat, sortie_temp_4);
    return resultat;

}


void fast_IDCT_ligne_flottante(float * ligne_mcu) {
/* applique idct sur une colonne (vue comme une ligne, et flottante) d'une matrice 8*8 */
    //etape 1 : croisements et multiplication par un réel
    float sortie_temp_1[8];
    division_flottant_sans_cast(ligne_mcu, sortie_temp_1, 3, sqrt(2));
    division_flottant_sans_cast(ligne_mcu, sortie_temp_1, 5, sqrt(2));
    croisement(ligne_mcu, sortie_temp_1, 1, 7);
    sortie_temp_1[2] = ligne_mcu[2];
    sortie_temp_1[4] = ligne_mcu[4];
    sortie_temp_1[6] = ligne_mcu[6];
    sortie_temp_1[0] = ligne_mcu[0];
    //etape 2 : croisements
    float sortie_temp_2[8];
    croisement(sortie_temp_1,sortie_temp_2, 0, 4);
    croisement(sortie_temp_1, sortie_temp_2, 7, 5);
    croisement(sortie_temp_1, sortie_temp_2, 1, 3);
    rotation_inverse(sortie_temp_1, sortie_temp_2, 2, 6, 6, sqrt(2));
    // etape 3
    float sortie_temp_3[8];
    croisement(sortie_temp_2, sortie_temp_3, 4, 2);
    croisement(sortie_temp_2, sortie_temp_3, 0, 6);
    rotation_inverse(sortie_temp_2, sortie_temp_3, 3, 5, 1, 1);
    rotation_inverse(sortie_temp_2, sortie_temp_3, 7, 1, 3, 1);
    // etape 4
    float sortie_temp_4[8];
    croisement(sortie_temp_3, sortie_temp_4, 0, 1);
    croisement(sortie_temp_3, sortie_temp_4, 4, 5);
    croisement(sortie_temp_3, sortie_temp_4, 2, 3);
    croisement(sortie_temp_3, sortie_temp_4, 6, 7);
    // saturation des coeffs 
    for (int16_t i = 0; i < 8; i++) {
        sortie_temp_4[i] = n*sortie_temp_4[i] + 128;
        sortie_temp_4[i] = saturation_sans_conversion(sortie_temp_4[i]);
    }
    // etape 5: attribuer les bons coeffs dans les bonnes cases
    attribution(ligne_mcu, sortie_temp_4);
    
}



float** fast_IDCT_MCU_ligne(int16_t ** mcu_basique) {
    /* applique l'idct sur toutes les lignes d'une matrice 8*8 */
    size_t dim_bloc[2] = {8, 8};
    float** resultat = init_matrice_sansp_float(dim_bloc, 1);
    for (int16_t i = 0; i < 8; i++) {
        // on fait la fast_idct sur les 8 lignes de la matrice 
        resultat[i] = fast_IDCT_ligne(mcu_basique[i], resultat[i]);
    }


    return resultat;


}


void fast_IDCT_MCU_colonnes(float ** mcu_basique) {
    /* applique l'idct sur toutes les colonnes d'une matrice */
    float* temp = calloc(8, sizeof(float));
    for (int i = 0; i <8; i++) {
        temp[0] = mcu_basique[0][i];
        temp[1] = mcu_basique[1][i];
        temp[2] = mcu_basique[2][i];
        temp[3] = mcu_basique[3][i];
        temp[4] = mcu_basique[4][i];
        temp[5] = mcu_basique[5][i];
        temp[6] = mcu_basique[6][i];
        temp[7] = mcu_basique[7][i];
        fast_IDCT_ligne_flottante(temp);
        mcu_basique[0][i] = temp[0];
        mcu_basique[1][i] = temp[1];
        mcu_basique[2][i] = temp[2];
        mcu_basique[3][i] = temp[3];
        mcu_basique[4][i] = temp[4];
        mcu_basique[5][i] = temp[5];
        mcu_basique[6][i] = temp[6];
        mcu_basique[7][i] = temp[7];

    }
    free(temp);
}




uint8_t** fast_IDCT_MCU(int16_t ** mcu_basique) {
    /* applique l'idct sur une matrice 8*8 entière*/
    size_t mon_tab[2] = {8, 8};
    uint8_t ** res = init_matrice_sansp_uint8(mon_tab, 0);  
    float** temp = fast_IDCT_MCU_ligne(mcu_basique);
    fast_IDCT_MCU_colonnes(temp);
    for (int16_t i =0; i < 8; i++) {
        for (int16_t j = 0; j<8; j++) {
            res[i][j] = (uint8_t) temp[i][j];

        }
    }
    free_matrice_entier_sansp_float(temp, mon_tab);
    return res;
}


void fast_IDCT_vecteur_et_free(uint8_t *** vecteur, size_t taille_vecteur, int16_t ***vecteur_a_transfo) {
    /*opère fast_idct sur toutes les matrices 8*8 d'un vecteur de blocs "vecteur_a_transfo" en stockant les matrices
      résultantes dans "vecteur", étant également un vecteur de blocs. Après opérations, on free les blocs de
      "vecteur_a_transfo" et on free finalement "vecteur_a_transfo" lui-même.*/

    size_t dim_bloc[2] = {8, 8};

    for (size_t bloc = 0; bloc < taille_vecteur; bloc++) 
    {
        vecteur[bloc] = fast_IDCT_MCU(vecteur_a_transfo[bloc]);
        free_matrice_entier_sansp_int16(vecteur_a_transfo[bloc], dim_bloc);
    }
    free(vecteur_a_transfo);
}


void fast_IDCT(struct data_1 *flux) {
    /* opère fast_idct sur toutes les matrices 8*8 des composantes de vect_fin_idct dans le cas gris ou coloré */

    if (flux -> couleurs == false)
    {
        flux -> vect_fin_idct_gris = calloc(flux -> lens_composantes[0], sizeof(uint8_t**));
        fast_IDCT_vecteur_et_free(flux -> vect_fin_idct_gris, flux -> lens_composantes[0], flux -> vect_fin_zz[0]);
    }
    

    else
    {
        flux -> vect_fin_idct[0] = calloc(flux -> lens_composantes[0], sizeof(uint8_t**));
        fast_IDCT_vecteur_et_free(flux -> vect_fin_idct[0], flux -> lens_composantes[0], flux -> vect_fin_zz[0]);

        flux -> vect_fin_idct[1] = calloc(flux -> lens_composantes[1], sizeof(uint8_t**));
        fast_IDCT_vecteur_et_free(flux -> vect_fin_idct[1], flux -> lens_composantes[1], flux -> vect_fin_zz[1]);

        flux -> vect_fin_idct[2] = calloc(flux -> lens_composantes[2], sizeof(uint8_t**));
        fast_IDCT_vecteur_et_free(flux -> vect_fin_idct[2], flux -> lens_composantes[2], flux -> vect_fin_zz[2]);
        
    }




}
