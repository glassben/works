#include "./../../include/module_matriciel.h"
#include <string.h>

void ecriture_gris_pgm(struct data_1 *data)
/*Utilise l'élément vect_fin_idct_gris de la structure data_1 pointée par data pour écrire au format P5 dans le fichier .pgm*/
{

    FILE *file = fopen("res.pgm", "w");

    fprintf(file, "P5\n");

    uint16_t *dimensions = data -> dim_image;

    fprintf(file, "%d %d\n", dimensions[1], dimensions[0]);

    fprintf(file, "255\n");

    size_t larg_image = dimensions[1];

    size_t long_image = dimensions[0];

    size_t p;
    size_t bloc;
    uint8_t ligne;
    uint8_t colonne;

    size_t dim_bloc[2] = {8, 8};
    

    size_t long_hori;
   

    size_t len_vect = data -> lens_composantes[0];

    uint8_t ***vect_blocs = data -> vect_fin_idct_gris;

    size_t reste_hori = larg_image % 8;
    if (reste_hori == 0)
    {
        long_hori = (larg_image)/8;
    }

    else
    {
        long_hori = floor(larg_image/8) + 1;
    }

    size_t reste_verti = long_image % 8;

    size_t ind_section_ligne = 0;


    for (p = 0; p <= len_vect - 1;)
    {   
        if (ind_section_ligne + 8 <= long_image)
        {
            
        
            for (ligne = 0; ligne <= 7; ligne++)
            {
                for (bloc = p; bloc <= p + long_hori - 1; bloc++)
                {
                    if (bloc == p + long_hori - 1)
                    {
                        if (reste_hori != 0)
                        {
                            for (colonne = 0; colonne <= reste_hori - 1; colonne++)
                            {
                                fwrite(&vect_blocs[bloc][ligne][colonne], 1, 1, file);
                            }
                        }

                        else
                        {
                            for (colonne = 0; colonne <= 7; colonne++)
                            {
                                fwrite(&vect_blocs[bloc][ligne][colonne], 1, 1, file);
                            }
                        }
                    }

                    else
                    {
                        for (colonne = 0; colonne <= 7; colonne++)
                        {
                            fwrite(&vect_blocs[bloc][ligne][colonne], 1, 1, file);
                        }
                    }
               
                }

            }
            
        }


        else
        {
            for (ligne = 0; ligne <= reste_verti - 1; ligne++)
            {
                for (bloc = p; bloc <= p + long_hori - 1; bloc++)
                {
                    if (bloc == p + long_hori - 1)
                    {
                        if (reste_hori != 0)
                        {
                            for (colonne = 0; colonne <= reste_hori - 1; colonne++)
                            {
                                fwrite(&vect_blocs[bloc][ligne][colonne], 1, 1, file);
                            }
                        }

                        else
                        {
                            for (colonne = 0; colonne <= 7; colonne++)
                            {
                                fwrite(&vect_blocs[bloc][ligne][colonne], 1, 1, file);
                            }
                        }
                    }

                    else
                    {
                        for (colonne = 0; colonne <= 7; colonne++)
                        {
                            fwrite(&vect_blocs[bloc][ligne][colonne], 1, 1, file);
                        }
                    }
               
                }

               
            }
        }



        for (bloc = p; bloc <= p + long_hori - 1; bloc++)
        {
            free_matrice_entier_sansp_uint8(vect_blocs[bloc], dim_bloc);
        }

        p += long_hori;
        ind_section_ligne += 8;
        
    }

    free(vect_blocs);

    fclose(file);

}
