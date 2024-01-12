


extern float saturation_sans_conversion(float valeur);
/* saturation qui ne renvoit pas un uint8_t dans les cas non-extrêmes, pour ne pas perdre en précision */


extern void attribution(float res[], float ligne[]);
/* "stage 1" de l'algo de fast_idct on permute les coefficients */


extern void croisement(float entree[], float sortie[], int i, int j);
/* réalise l'opération de croisement de l'algo fast_idct*/


extern void croisement_etape4(int16_t entree[], float sortie[], int i, int j);
/* à cette étape l'entrée est encore un int16_t. On doit donc la transtyper. */


extern void rotation_inverse(float entree[], float sortie[], int i, int j, int mon_n, float k);
/* réalise l'opération de rotation inverse de l'algo fast_idct*/


extern void division_flottant(int16_t entree[], float sortie[], int i, float k);
/* "stage 4" pour l'idct sur lignes : division de l'entrée int16_t par un flottant. On transtype l'entrée. */


extern void division_flottant_sans_cast(float entree[], float sortie[], int i, float k);
/*"stage 4" pour l'idct sur colonnes: division de l'entrée déjà flottante par un flottant. */


extern float *fast_IDCT_ligne(int16_t * ligne_mcu);
/* applique fast_idct sur une ligne d'une matrice 8*8 de int16_t. Le résultat est un vecteur de flottant et on crée donc une fonction 
    similaire mais prenant en compte des flottants. Entre chaque "stage" de l'algo idct, on stocke des tableaux intermédiaires sur la pile : les valeurs
    contenues dans ces tableaux sont celles sur les lignes à l'étape correspondante:
    ligne_mcu: initialement, donc au début de l'étape 4
    sortie_temp_1 : entre 4 et 3
    sortie_temp_2: entre 3 et 2
    sortie_temp_3: entre 2 et 1
    sortie_temp_4: après étape 1 mais avant la réattribution
    resultat : après la réattribution, résultat définitif de l'idct */




extern void fast_IDCT_ligne_flottante(float * ligne_mcu);
/* applique idct sur une colonne (vue comme une ligne, et flottante) d'une matrice 8*8 */


extern float** fast_IDCT_MCU_ligne(int16_t ** mcu_basique);
/* applique l'idct sur toutes les lignes d'une matrice 8*8 */


extern void fast_IDCT_MCU_colonnes(float ** mcu_basique);
/* applique l'idct sur toutes les colonnes d'une matrice */


extern uint8_t** fast_IDCT_MCU(int16_t ** mcu_basique);
/* applique l'idct sur une matrice 8*8 entière*/


extern void fast_IDCT_vecteur_et_free(uint8_t *** vecteur, size_t taille_vecteur, int16_t ***vecteur_a_transfo);
/*opère fast_idct sur toutes les matrices 8*8 d'un vecteur de blocs "vecteur_a_transfo" en stockant les matrices
  résultantes dans "vecteur", étant également un vecteur de blocs. Après opérations, on free les blocs de
  "vecteur_a_transfo" et on free finalement "vecteur_a_transfo" lui-même.*/


extern void fast_IDCT(struct data_1 *flux);
/* opère fast_idct sur toutes les matrices 8*8 des composantes de vect_fin_idct dans le cas gris ou coloré */
