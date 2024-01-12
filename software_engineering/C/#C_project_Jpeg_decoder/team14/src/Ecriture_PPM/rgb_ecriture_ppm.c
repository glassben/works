#include "../../include/module_matriciel.h"







uint8_t* saturation_rgb(int16_t R, int16_t G, int16_t B)
/*Tronque les valeurs de R, G et de B à des valeurs comprises entre 0 et 255.*/
{
    uint8_t* tab = calloc(3, sizeof(uint8_t));
    if (R > 255)
    {
        tab[0] = 255;
    }

    else if (R < 0)
    {
        tab[0] = 0;
    }

    else
    {
        tab[0] = (uint8_t)R;
    }


    if (G > 255)
    {
        tab[1] = 255;
    }

    else if (G < 0)
    {
        tab[1] = 0;
    }

    else
    {
        tab[1] = (uint8_t)G;
    }


    if (B > 255)
    {
        tab[2] = 255;
    }

    else if (B < 0)
    {
        tab[2] = 0;
    }

    else
    {
        tab[2] = (uint8_t)B;
    }

    return tab;
}










void rgb_printing(uint8_t Y, uint8_t Cb, uint8_t Cr, FILE* fichier)
/*Calcule les valeurs de R, G et de B en adéquation avec les valeurs de Y, Cb et de Cr.
  Ensuite, on utilise la fonction saturation_rgb pour restreindre les valeurs de R, G et de B à des valeurs comprises entre 0 et 255.
  Finalement, on écrit les valeurs de R, G et de B saturées dans le fichier avec fprintf (format P3)*/
{
    int16_t R = Y - 0.0009267 * (Cb - 128) + 1.4016868 * (Cr - 128);
    int16_t G = Y - 0.3436954 * (Cb - 128) - 0.7141690 * (Cr - 128);
    int16_t B = Y + 1.7721604 * (Cb - 128) + 0.0009902 * (Cr - 128);
    uint8_t *tab = saturation_rgb(R, G, B);
    fprintf(fichier, "%u %u %u\n", tab[0], tab[1], tab[2]);
}




void rgb_writing(uint8_t Y, uint8_t Cb, uint8_t Cr, FILE* fichier)
/*Calcule les valeurs de R, G et de B en adéquation avec les valeurs de Y, Cb et de Cr.
  Ensuite, on utilise la fonction saturation_rgb pour restreindre les valeurs de R, G et de B à des valeurs comprises entre 0 et 255.
  Finalement, on écrit les valeurs de R, G et de B saturées dans le fichier avec fwrite (format P6)*/
{   
    int16_t R = Y - 0.0009267 * (Cb - 128) + 1.4016868 * (Cr - 128);
    int16_t G = Y - 0.3436954 * (Cb - 128) - 0.7141690 * (Cr - 128);
    int16_t B = Y + 1.7721604 * (Cb - 128) + 0.0009902 * (Cr - 128);
    uint8_t *tab = saturation_rgb(R, G, B);
    fwrite(tab, 1, 3, fichier);
    free(tab);
}










void ecriture_couleurs_ppm(struct data_1 *data)
/*Utilise chacune des trois composantes de vect_fin_upsampling de la structure data_1 pointée par data pour écrire au format P6 dans le fichier .ppm*/
{

    FILE *file = fopen("res.ppm", "w");


    fprintf(file, "P6\n");

    uint16_t *dimensions = data -> dim_image;

    fprintf(file, "%d %d\n", dimensions[1], dimensions[0]);

    fprintf(file, "255\n");

    uint16_t larg_image = dimensions[1];

    uint16_t long_image = dimensions[0];

    size_t p;
    size_t mcu;
    uint8_t ligne;
    uint8_t colonne;

    
    size_t long_hori;

    uint8_t h_Y = data -> param_sampling[0];
    uint8_t v_Y = data -> param_sampling[1];

    uint8_t ***vect_Y; 
    uint8_t ***vect_Cb;
    uint8_t ***vect_Cr;

    if (!(h_Y == 1 && v_Y == 1))
    {
        vect_Y = data -> vect_fin_upsampling[0];

        vect_Cb = data -> vect_fin_upsampling[1];

        vect_Cr = data -> vect_fin_upsampling[2];
    }

    else
    {
        vect_Y = data -> vect_fin_idct[0];

        vect_Cb = data -> vect_fin_idct[1];

        vect_Cr = data -> vect_fin_idct[2];
    }
    
    size_t dim_matrice[2] = {8*v_Y, 8*h_Y};

    size_t len_vect = data -> len_mcus;



    size_t reste_hori = larg_image % (8*h_Y);
    if (reste_hori == 0)
    {
        long_hori = (larg_image)/(8*h_Y);
    }

    else
    {
        long_hori = floor(larg_image/(8*h_Y)) + 1;
    }

    size_t reste_verti = long_image % (8*v_Y);


    size_t ind_section_ligne = 0;

    for (p = 0; p <= len_vect - 1;)
    {   
        if (ind_section_ligne + 8*v_Y <= long_image)
        {
            
        
            for (ligne = 0; ligne <= 8*v_Y - 1; ligne++)
            {
                for (mcu = p; mcu <= p + long_hori - 1; mcu++)
                {
                    if (mcu == p + long_hori - 1)
                    {
                        if (reste_hori != 0)
                        {
                            for (colonne = 0; colonne <= reste_hori - 1; colonne++)
                            {
                                rgb_writing(vect_Y[mcu][ligne][colonne],  vect_Cb[mcu][ligne][colonne], vect_Cr[mcu][ligne][colonne], file);
                            
                            }
                        }

                        else
                        {
                            for (colonne = 0; colonne <= 8*h_Y - 1; colonne++)
                            {
                                rgb_writing(vect_Y[mcu][ligne][colonne],  vect_Cb[mcu][ligne][colonne], vect_Cr[mcu][ligne][colonne], file);
                            }
                        }
                    }

                    else
                    {
                        for (colonne = 0; colonne <= 8*h_Y - 1; colonne++)
                        {
                            rgb_writing(vect_Y[mcu][ligne][colonne], vect_Cb[mcu][ligne][colonne], vect_Cr[mcu][ligne][colonne], file);
                        }
                    }
               
                }

            }

        }




        else
        {
            for (ligne = 0; ligne <= reste_verti - 1; ligne++)
            {
                for (mcu = p; mcu <= p + long_hori - 1; mcu++)
                {
                    if (mcu == p + long_hori - 1)
                    {
                        if (reste_hori != 0)
                        {
                            for (colonne = 0; colonne <= reste_hori - 1; colonne++)
                            {
                                rgb_writing(vect_Y[mcu][ligne][colonne],  vect_Cb[mcu][ligne][colonne], vect_Cr[mcu][ligne][colonne], file);
                            }
                        }

                        else
                        {
                            for (colonne = 0; colonne <= 8*h_Y - 1; colonne++)
                            {
                                rgb_writing(vect_Y[mcu][ligne][colonne],  vect_Cb[mcu][ligne][colonne], vect_Cr[mcu][ligne][colonne], file);
                            }
                        }
                    }

                    else
                    {
                        for (colonne = 0; colonne <= 8*h_Y - 1; colonne++)
                        {
                            rgb_writing(vect_Y[mcu][ligne][colonne],  vect_Cb[mcu][ligne][colonne], vect_Cr[mcu][ligne][colonne], file);
                        }
                    }
               
                }

            }
        }

        for (mcu = p; mcu <= p + long_hori - 1; mcu++)
        {
            free_matrice_entier_sansp_uint8(vect_Y[mcu], dim_matrice);
            free_matrice_entier_sansp_uint8(vect_Cb[mcu], dim_matrice);
            free_matrice_entier_sansp_uint8(vect_Cr[mcu], dim_matrice);
        }

        p += long_hori;
        ind_section_ligne += 8*v_Y;
        
    }

    free(vect_Y);
    free(vect_Cb);
    free(vect_Cr);

    fclose(file);
}
