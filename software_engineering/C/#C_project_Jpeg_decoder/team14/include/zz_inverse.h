



extern int16_t** zz_inverse_un_bloc(int16_t *array);
/*créé la matrice 8*8 dé-zig-zaguée associée au vecteur array à 64 éléments.
  Ce vecteur est "free" à la fin.*/



extern int16_t*** zz_inverse_vect_array_to_vect_bloc(int16_t **vect_array, size_t long_vect);
/*Crée le vecteur de blocs dé-zig-zagués et free "vect_array" à la fin, qui est un vecteur de vecteurs à 64 éléments.*/



extern int modif_vect_fin_zz(struct data_1 *data);
/*initialise chaque composante requise de vect_fin_zz dans la structure data_1 pointée par data en créant 
  dans le tas les vecteurs de blocs dé-zig-zagués provenant des vecteurs de vect_fin_rle_et_qz*/
