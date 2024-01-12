#include "../include/module_matriciel.h"
#include "../include/idct.h"
#include "../include/divise.h"
#include "../include/ecriture_pgm.h"
#include "../include/Huffman.h"
#include "../include/quantification_inverse.h"
#include "../include/zz_inverse.h"
#include "../include/Upsampling.h"
#include "../include/rgb_ecriture_ppm.h"
#include "../include/fast_idct.h"
#include "../include/idct.h"




int main(int argc, char **argv)
{
    if (argc!=2){
        printf("you need to provide one unic image,try again");
        return EXIT_FAILURE;
    }
    char* fichier_considere = argv[1];
    est_un_jpeg(fichier_considere);
    size_t longueur = recupere_longueur_image(fichier_considere);
    uint8_t* table_de_Huffman_AC=recupere_huffman_AC(fichier_considere);
    uint8_t* table_de_Huffman_DC=recupere_huffman_DC(fichier_considere);
    uint8_t* mon_image =recupere_composante(fichier_considere,longueur);


    struct data_1 *data = calloc(1, sizeof(struct data_1));

    recupere_dimension_et_couleur(fichier_considere, data);

    if (data -> couleurs == false)
    {

        data -> vect_fin_rle_et_qz = calloc(1, sizeof(int16_t**));
        size_t nb_cellules;
        if (data -> dim_image[0] % 8  == 0 && data -> dim_image[1] % 8 == 0)
        {
            nb_cellules = (data -> dim_image[0]/8)*(data -> dim_image[1]/8);
        }
        
        else if (data -> dim_image[0] % 8  != 0 && data -> dim_image[1] % 8 ==0)
        {
            nb_cellules = floor(data -> dim_image[0]/8 + 1)*(data -> dim_image[1]/8);
        }

        else if (data -> dim_image[0] % 8  == 0 && data -> dim_image[1] % 8 !=0)
        {
            nb_cellules = (data -> dim_image[0]/8)*floor(data -> dim_image[1]/8 + 1);
        }
        else
        {
            nb_cellules = floor((data -> dim_image[0]/8) + 1)* floor((data -> dim_image[1])/8 + 1);
        }

        data -> lens_composantes[0] = nb_cellules;
        int16_t** table_a_completer = decodage_complet(mon_image, nb_cellules, longueur, table_de_Huffman_DC, table_de_Huffman_AC);
        data -> vect_fin_rle_et_qz[0] = table_a_completer;
        uint8_t* table_de_quantification_luminance=recupere_quantification_luminance(fichier_considere);
        data -> tables_quantification[0] = table_de_quantification_luminance;



        dequantification_totale(data);


        modif_vect_fin_zz(data);

        fast_IDCT(data);

        ecriture_gris_pgm(data);

        free(table_de_quantification_luminance);


    }




    else
    {   
        uint8_t h_Y = data -> param_sampling[0];
        uint8_t v_Y = data -> param_sampling[1];

        uint8_t h_Cb = data -> param_sampling[2];
        uint8_t v_Cb = data -> param_sampling[3];

        uint8_t h_Cr = data -> param_sampling[4];
        uint8_t v_Cr = data -> param_sampling[5];


        uint8_t *table_Huffman_AC_chrominance = recupere_huffman_AC_chrominance(fichier_considere);
        uint8_t *table_Huffman_DC_chrominance = recupere_huffman_DC_chrominance(fichier_considere);
        uint8_t* table_de_quantification_luminance =recupere_quantification_luminance(fichier_considere);
        uint8_t* table_de_quantification_chrominance=recupere_quantification_chrominance(fichier_considere);
        data -> tables_quantification[0] = table_de_quantification_luminance;
        data -> tables_quantification[1] = table_de_quantification_chrominance;
        



        size_t nb_blocs_Y;
        if (data -> dim_image[0] % (8*v_Y)  == 0 && data -> dim_image[1] % (8*h_Y) == 0)
        {
            nb_blocs_Y = (data -> dim_image[0]/8)*(data -> dim_image[1]/8);
        }
        
        else if (data -> dim_image[0] % (8*v_Y)  != 0 && data -> dim_image[1] % (8*h_Y) == 0)
        {
            nb_blocs_Y = floor(data -> dim_image[0]/(8*v_Y) + 1)*v_Y*(data -> dim_image[1]/8);
        }

        else if (data -> dim_image[0] % (8*v_Y)  == 0 && data -> dim_image[1] % (8*h_Y) !=0)
        {
            nb_blocs_Y = (data -> dim_image[0]/8)*floor(data -> dim_image[1]/(8*h_Y) + 1)*h_Y;
        }
        else
        {
            nb_blocs_Y = floor(data -> dim_image[0]/(8*v_Y) + 1)*v_Y*floor(data -> dim_image[1]/(8*h_Y) + 1)*h_Y;
        }


        data -> lens_composantes[0] = nb_blocs_Y;

        size_t nb_blocs_Cb = nb_blocs_Y*((float)(h_Cb*v_Cb)/(float)(h_Y*v_Y));

        size_t nb_blocs_Cr = nb_blocs_Y*((float)(h_Cr*v_Cr)/(float)(h_Y*v_Y));

        data -> lens_composantes[1] = nb_blocs_Cb;
        data -> lens_composantes[2] = nb_blocs_Cr;


        data -> len_mcus = nb_blocs_Y/(h_Y*v_Y);


        size_t Y[2] = {h_Y, v_Y};
        size_t Cb[2] = {h_Cb, v_Cb};
        size_t Cr[2] = {h_Cr, v_Cr};

        data -> vect_fin_rle_et_qz = decodage_totale_couleur(fichier_considere,mon_image, nb_blocs_Y, nb_blocs_Cb, nb_blocs_Cr, longueur, Y, Cb, Cr, table_de_Huffman_DC, table_de_Huffman_AC, table_Huffman_DC_chrominance, table_Huffman_AC_chrominance);

        dequantification_totale(data);

        modif_vect_fin_zz(data);


        fast_IDCT(data);


        if (!(h_Y == 1 && v_Y == 1))
        {
            creation_mcus_data(data);

        }

       
        ecriture_couleurs_ppm(data);
        free(table_Huffman_AC_chrominance);
        free(table_Huffman_DC_chrominance);
        free(table_de_quantification_luminance);
        free(table_de_quantification_chrominance);
        

    }
    
    free(mon_image);
    free(table_de_Huffman_AC);
    free(table_de_Huffman_DC);

    free(data);

    return EXIT_SUCCESS;
}
