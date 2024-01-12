


extern uint8_t*** duplication_upsampling_unitaire(uint8_t ***vect_blocs, size_t indice_bloc, uint8_t facteur_sampling_hori, uint8_t facteur_sampling_verti, uint8_t h_Y, uint8_t v_Y);
/*duplique/sur-échantillonne les matrices pour Cb et Cr*/
/*renvoie un vecteur de 4 matrices.*/
/*entrées : vecteur de blocs 8*8  ;  indice de départ de "prélèvement" dans ce vecteur ; les facteurs d'échantillonnage de la chrominance en question ; ceux de Y.*/
/*sorties : vecteur de 4 éléments : les éléments sont soient des matrices, soient des pointeurs égaux à NULL. Il y a h_Y*v_Y matrices créées dans ce vecteur.
  Il peut donc très bien y avoir 4 matrices dans ce vecteur, ou seulement 2, ou seulement 1.*/





extern uint8_t** fusion_matrice_Y(uint8_t **array_matrices[4], uint8_t dim_en_blocs[2]);
/*fusionne pour Y, soit 2 matrices 8*8 en 2*1, soit 2 matrices en 1*2, soit 4 matrices en 4*4, cela de gauche à droite puis de haut en bas*/





extern uint8_t** fusion_matrice_chrominance(uint8_t **array_matrices[4], uint8_t dim_en_blocs[2]);
/*fusionne pour les chrominances soit 2 matrices 8*8 en 2*1, soit 2 matrices en 1*2, soit 4 matrices en 4*4, cela de gauche à droite puis de haut en bas*/





extern uint8_t** upsampling_et_fusion_unitaire_chrominance(uint8_t ***vect_blocs, size_t indice_bloc, uint8_t facteur_sampling_hori, uint8_t facteur_sampling_verti, uint8_t h_Y, uint8_t v_Y);
/*entrées : vecteur de blocs pour une chrominance ; indice de départ de "prélèvement" dans vect_blocs  ;  facteurs d'échantillonnage pour la chrominance considérée  ;  facteurs d'échantillonnage pour Y*/
/*sorties : matrice "fusionnée" faisant soit 8*16, soit 16*8, soit 16*16*/





extern uint8_t** creation_mcu_Y(uint8_t ***vect_blocs, size_t indice_bloc, uint8_t h_Y, uint8_t v_Y);
/*On prend un paquet de blocs dans le vecteur de blocs de Y en partant de l'indice "indice_bloc" dans le 
  vecteur et on les fusionne pour renvoyer une matrice de taille 8*16, 16*8, 16*16.*/
  




extern void creation_mcus_data(struct data_1 *data);
/*On initialise chaque composante de vect_fin_upsampling appartenant à une structure data_1 pointée par le pointeur data.
  Ensuite, on créé les MCUs qui seront les éléments de vect_fin_upsampling[i] pour i allant de 0 à 2, cela grâce aux fonctions ci-dessus.
  En dernier lieu, on "free" chaque composante de vect_fin_idct et ses éléments qui auront été utilisés pour le sur-échantillonnage et la création des MCUs.*/
