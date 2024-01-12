


extern void dequantification_unitaire(int16_t *x1, uint8_t *x2);
/*multiplie chaque composante du vecteur x1 par chaque composante respective du vecteur x2 qui sera une table de quantification*/


extern int dequantification_arrays(int16_t **vect_1, size_t len_1, uint8_t *x2);
/*déquantifie chaque vecteur à 64 éléments de vect_1 qui est donc un vecteur de vecteurs en utilisant x2 et la fonction ci-dessus*/


extern void dequantification_totale(struct data_1 *data);
/*déquantifie en place chaque vecteur à 64 éléments pour chaque vecteur de vecteurs de chaque composante du vecteur vect_fin_rle_et_qz*/

