


extern float C(int p);
/* utile pour le calcul dans la somme */

extern uint8_t saturation_unitaire(float valeur);
/* traite les valeurs extrêmes des composantes et renvoit un uint8_t */

extern float* pre_calcule_cos(int x);

extern uint8_t transformation_spatiale_unitaire(int x, int y, int16_t **ancienne_image);
/* transforme un coefficient fréquentiel en coefficient spatial */

extern uint8_t **IDCT_MCU(int16_t ** mcu_basique);
/* opère la transformation idct sur une matrice 8*8*/

extern void IDCT_vecteur_et_free(uint8_t *** vecteur, size_t taille_vecteur, int16_t ***vecteur_a_transfo);
/*créé les matrices de coordonnées spatiales dans le nouveau vecteur avec en-tête initialisée en libérant au passage le vecteur de blocs de fréquences. */

extern void IDCT_gris(struct data_1 *flux);
/* opère idct sur toutes les matrices 8*8 de vect_fin_idct_gris*/

extern void IDCT_couleurs(struct data_1 *flux);
/* opère idct sur toutes les matrices 8*8 de chacune des 3 composantes de vect_fin_idct dans le cas coloré */
