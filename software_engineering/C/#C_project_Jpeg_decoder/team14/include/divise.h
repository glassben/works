/*#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>*/


extern void est_un_jpeg(char* fichier_considere);

extern size_t calcule_longueur_premiere_table_de_huffman(char* fichier_considere);

extern size_t calcule_longueur_seconde_table_de_huffman(char* fichier_considere);

extern size_t calcule_longueur_troisième_table_Huffman(char* fichier_considere);

extern size_t calcule_longueur_quatrième_table_Huffman(char* fichier_considere);

extern uint8_t* recupere_huffman_AC(char* fichier_considere);

extern uint8_t* recupere_huffman_DC(char* fichier_considere);

extern uint8_t* recupere_quantification_luminance(char* fichier_considere);

extern uint8_t* recupere_quantification_chrominance(char* fichier_considere);

extern uint8_t* recupere_information_sur_limage(char* fichier_considere);

extern uint8_t* recupere_composante(char* fichier_considere,size_t nbr_d_octet);

extern uint8_t* recupere_huffman_DC_chrominance(char* fichier_considere);

extern uint8_t* recupere_huffman_AC_chrominance(char* fichier_considere);


extern int recupere_longueur_image(char* fichier_considere);

extern size_t* recupere_hauteur_et_longueur_pixel(char* fichier_considere,size_t dim_image[2]);

extern void recupere_dimension_et_couleur(char* fichier_considere,struct data_1* vecteur);

extern uint8_t* recupere_SOS(char* fichier_considere);

