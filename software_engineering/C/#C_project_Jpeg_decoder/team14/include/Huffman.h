/*#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>*/





struct liste{
    struct arbre* element;
    struct liste* suiv;
};


struct arbre{
    uint8_t element;
    struct arbre* fils_gauche;
    struct arbre* fils_droit;
};


extern void affiche2(struct arbre* mon_arbre);

extern void affiche(struct liste* ma_liste);

extern struct liste* creer(struct arbre* elem);

extern int taille(struct liste* elem);

extern void free_mon_arbre(struct arbre* mon_arbre);

extern void free_ma_liste(struct liste* ma_liste);

extern struct arbre* recupere_element(struct liste** ma_liste);

extern struct liste * empile_element(struct liste* ma_liste,struct arbre* elem);

extern struct arbre* construit_arbre_bis(uint8_t* table);

extern int16_t exponentie(uint8_t nombre_a_exponentier,uint8_t exposant);

extern size_t* recupere_bit(uint8_t* fichier_considere,size_t* table_ou_on_est);

extern int16_t* lecture(uint8_t* fichier_considere,size_t* la_ou_je_suis_dans_le_bit,struct arbre* mon_arbre);

extern uint8_t lecture_sans_indice_de_magnetude(uint8_t* fichier_considere,size_t* la_ou_je_suis_dans_le_bit,struct arbre* mon_arbre);

extern int16_t decodage_classe_de_magnetude(int8_t ma_classe,int16_t l_indice_dans_la_classe_de_magnetude);

extern void decodage_RLE(uint8_t* composante_a_decoder, size_t* la_ou_je_suis_dans_le_bit, int16_t* table_a_completer, struct arbre* mon_arbre_AC);

extern int16_t decodage_DC_premiere_MCU(uint8_t* composante_a_decoder,size_t* la_ou_je_suis_dans_le_bit,struct arbre* mon_arbre_DC);

extern int16_t decodage_DC_suivant_MCU(uint8_t* composante_a_decoder,size_t* la_ou_je_suis_dans_le_bit,struct arbre* mon_arbre_DC,int16_t valeur_de_la_premiere_composante);

extern int16_t** decodage_complet(uint8_t* image_a_decoder,size_t nombre_de_cellule,size_t taille_de_l_image,uint8_t* table_de_Huffman_DC,uint8_t* table_de_Huffman_AC);

extern int16_t*** decodage_en_couleur_ordre_normale(uint8_t* image_a_decoder,size_t nombre_de_cellule,size_t* facteur_d_echantillonnage_luminence,size_t* facteur_d_echantillonnage_bleu,size_t* facteur_d_echantillonnage_rouge,uint8_t* table_de_Huffmann_luminance_DC,uint8_t* table_de_huffmann_luminance_AC,uint8_t* table_de_huffmann_chrominance_DC,uint8_t* table_de_huffmann_chrominance_AC);

extern void place_dans_le_vecteur(int16_t** vecteur_de_decodage_complet,struct data_1* mon_vecteur);

extern int16_t*** decodage_couleur_ordre_YRB(uint8_t* image_a_decoder,size_t nb_cellules_Y, size_t nb_cellules_Cb, size_t nb_cellules_Cr, size_t taille_de_l_image,size_t* facteur_d_echantillonnage_luminence,size_t* facteur_d_echantillonnage_bleu,size_t* facteur_d_echantillonnage_rouge,uint8_t* table_de_huffman_luminance_DC,uint8_t* table_de_huffman_luminance_AC,uint8_t* table_de_huffman_chrominance_DC,uint8_t* table_de_huffman_chrominance_AC);

extern int16_t*** decodage_en_couleur_ordre_BYR(uint8_t* image_a_decoder,size_t nb_cellules_Y, size_t nb_cellules_Cb, size_t nb_cellules_Cr, size_t taille_de_l_image,size_t* facteur_d_echantillonnage_luminence,size_t* facteur_d_echantillonnage_bleu,size_t* facteur_d_echantillonnage_rouge,uint8_t* table_de_huffman_luminance_DC,uint8_t* table_de_huffman_luminance_AC,uint8_t* table_de_huffman_chrominance_DC,uint8_t* table_de_huffman_chrominance_AC);


extern int16_t*** decodage_en_couleur_ordre_RYB(uint8_t* image_a_decoder,size_t nb_cellules_Y, size_t nb_cellules_Cb, size_t nb_cellules_Cr, size_t taille_de_l_image,size_t* facteur_d_echantillonnage_luminence,size_t* facteur_d_echantillonnage_bleu,size_t* facteur_d_echantillonnage_rouge,uint8_t* table_de_huffman_luminance_DC,uint8_t* table_de_huffman_luminance_AC,uint8_t* table_de_huffman_chrominance_DC,uint8_t* table_de_huffman_chrominance_AC);


extern int16_t*** decodage_en_couleur_ordre_RBY(uint8_t* image_a_decoder,size_t nb_cellules_Y, size_t nb_cellules_Cb, size_t nb_cellules_Cr, size_t taille_de_l_image,size_t* facteur_d_echantillonnage_luminence,size_t* facteur_d_echantillonnage_bleu,size_t* facteur_d_echantillonnage_rouge,uint8_t* table_de_huffmann_luminance_DC,uint8_t* table_de_huffman_luminance_AC,uint8_t* table_de_huffman_chrominance_DC,uint8_t* table_de_huffman_chrominance_AC);

extern int16_t*** decodage_en_couleur_ordre_BRY(uint8_t* image_a_decoder,size_t nb_cellules_Y, size_t nb_cellules_Cb, size_t nb_cellules_Cr, size_t taille_de_l_image,size_t* facteur_d_echantillonnage_luminence,size_t* facteur_d_echantillonnage_bleu,size_t* facteur_d_echantillonnage_rouge,uint8_t* table_de_huffman_luminance_DC,uint8_t* table_de_huffman_luminance_AC,uint8_t* table_de_huffman_chrominance_DC,uint8_t* table_de_huffman_chrominance_AC);

extern int16_t*** decodage_totale_couleur(char* fichier_considere,uint8_t* image_a_decoder,size_t nb_cellules_Y, size_t nb_cellules_Cb, size_t nb_cellules_Cr, size_t taille_de_l_image,size_t* facteur_d_echantillonnage_luminence,size_t* facteur_d_echantillonnage_bleu,size_t* facteur_d_echantillonnage_rouge,uint8_t* table_de_huffman_luminance_DC,uint8_t* table_de_huffman_luminance_AC,uint8_t* table_de_huffman_chrominance_DC,uint8_t* table_de_huffman_chrominance_AC);
