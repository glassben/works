


extern uint8_t* saturation_rgb(int16_t R, int16_t G, int16_t B);
/*Tronque les valeurs de R, G et de B à des valeurs comprises entre 0 et 255.*/






extern void rgb_printing(uint8_t Y, uint8_t Cb, uint8_t Cr, FILE* fichier);
/*Calcule les valeurs de R, G et de B en adéquation avec les valeurs de Y, Cb et de Cr.
  Ensuite, on utilise la fonction saturation_rgb pour restreindre les valeurs de R, G et de B à des valeurs comprises entre 0 et 255.
  Finalement, on écrit les valeurs de R, G et de B saturées dans le fichier avec fprintf (format P3)*/





extern void rgb_writing(uint8_t Y, uint8_t Cb, uint8_t Cr, FILE* fichier);
/*Calcule les valeurs de R, G et de B en adéquation avec les valeurs de Y, Cb et de Cr.
  Ensuite, on utilise la fonction saturation_rgb pour restreindre les valeurs de R, G et de B à des valeurs comprises entre 0 et 255.
  Finalement, on écrit les valeurs de R, G et de B saturées dans le fichier avec fwrite (format P6)*/




extern void ecriture_couleurs_ppm(struct data_1 *data);
/*Utilise chacune des trois composantes de vect_fin_upsampling de la structure data_1 pointée par data pour écrire au format P6 dans le fichier .ppm*/
