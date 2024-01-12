#include "../../include/module_matriciel.h"











uint8_t*** duplication_upsampling_unitaire(uint8_t ***vect_blocs, size_t indice_bloc, uint8_t facteur_sampling_hori, uint8_t facteur_sampling_verti, uint8_t h_Y, uint8_t v_Y)
/*duplique/sur-échantillonne les matrices pour Cb et Cr*/
/*renvoie un vecteur de 4 matrices.*/
/*entrées : vecteur de blocs 8*8  ;  indice de départ de "prélèvement" dans ce vecteur ; les facteurs d'échantillonnage de la chrominance en question ; ceux de Y.*/
/*sorties : vecteur de 4 éléments : les éléments sont soient des matrices, soient des pointeurs égaux à NULL. Il y a h_Y*v_Y matrices créées dans ce vecteur.
  Il peut donc très bien y avoir 4 matrices dans ce vecteur, ou seulement 2, ou seulement 1.*/
{

    uint8_t h_C = facteur_sampling_hori;
    uint8_t v_C = facteur_sampling_verti;

    uint8_t dupliq_horizontale = h_Y/facteur_sampling_hori;
    uint8_t dupliq_verticale = v_Y/facteur_sampling_verti;

    uint8_t ***array_blocs_a_creer = calloc(4, sizeof(uint8_t **));
    size_t dim_bloc[2] = {8, 8};

    if (h_Y == 2 && v_Y == 2)
    {
        for (uint8_t i = 0; i <= h_Y*v_Y - 1; i++)
        {
            array_blocs_a_creer[i] = init_matrice_sansp_uint8(dim_bloc, 0);
        }
    }

    else if (h_Y == 1 && v_Y == 2)
    {
        array_blocs_a_creer[0] = init_matrice_sansp_uint8(dim_bloc, 0);
        array_blocs_a_creer[2] = init_matrice_sansp_uint8(dim_bloc, 0);
    }

    else if (h_Y == 2 && v_Y == 1)
    {
        array_blocs_a_creer[0] = init_matrice_sansp_uint8(dim_bloc, 0);
        array_blocs_a_creer[1] = init_matrice_sansp_uint8(dim_bloc, 0);
    }

    else
    {
        array_blocs_a_creer[0] = init_matrice_sansp_uint8(dim_bloc, 0);
    }



    uint8_t k_lig;
    uint8_t k_col;
    uint8_t ligne;
    uint8_t colonne;
    size_t bloc;

    uint8_t ligne_a_dupliq;
    uint8_t colonne_a_dupliq;

    uint8_t numero_bloc_a_creer;

    uint8_t ligne_array;
    uint8_t colonne_array;


    for (bloc = indice_bloc; bloc <= indice_bloc + facteur_sampling_hori*facteur_sampling_verti - 1; bloc++)
    {
        
        for (k_lig = 0; k_lig <= dupliq_verticale - 1; k_lig++)
        {

            for (k_col = 0; k_col <= dupliq_horizontale - 1; k_col++)
            {


                for (colonne = (k_col*(8/dupliq_horizontale)) % 8; colonne <= ((k_col+1)*(8/dupliq_horizontale) - 1) % 8; colonne++)
                {
                    for (ligne = (k_lig*(8/dupliq_verticale)) % 8; ligne <= ((k_lig+1)*(8/dupliq_verticale) - 1) % 8; ligne++)
                    {
                        for (colonne_a_dupliq = 0; colonne_a_dupliq <= dupliq_horizontale - 1; colonne_a_dupliq++)
                        {

                            for (ligne_a_dupliq = 0; ligne_a_dupliq <= dupliq_verticale - 1; ligne_a_dupliq++)
                            {

                                float deuxieme_terme = (3.0/(2.0*v_C))*k_lig + ((2.0*h_C)/3.0)*k_col;

                                if (deuxieme_terme != (uint8_t)deuxieme_terme)
                                {
                                    deuxieme_terme = floor(deuxieme_terme + 1);
                                }
                                

                                numero_bloc_a_creer = (bloc - indice_bloc)*v_C + (uint8_t)deuxieme_terme;                                

                                ligne_array = (dupliq_verticale*ligne + ligne_a_dupliq)%8;

                                colonne_array = (dupliq_horizontale*colonne + colonne_a_dupliq)%8;

                                array_blocs_a_creer[numero_bloc_a_creer][ligne_array][colonne_array] = vect_blocs[bloc][ligne][colonne];


                            }
                        }



                    }
                }

            }
        }

        free_matrice_entier_sansp_uint8(vect_blocs[bloc], dim_bloc);

        

    }
    
    return array_blocs_a_creer;


}









uint8_t** fusion_matrice_Y(uint8_t **array_matrices[4], uint8_t dim_en_blocs[2])
/*fusionne pour Y, soit 2 matrices 8*8 en 2*1, soit 2 matrices en 1*2, soit 4 matrices en 4*4, cela de gauche à droite puis de haut en bas*/
{
    size_t dim_res[2] = {8*dim_en_blocs[0], 8*dim_en_blocs[1]};

    size_t dim_bloc[2] = {8, 8};

    uint8_t **res = init_matrice_sansp_uint8(dim_res, 0);


    size_t ligne;
    size_t colonne;
    size_t bloc;

    if (dim_en_blocs[0] == 2 && dim_en_blocs[1] == 2)
    {

        for (bloc = 0; bloc <= 1; bloc++)
        {
            for (ligne = 0; ligne <= 7; ligne++)
            {
                for (colonne = bloc*8; colonne <= 8 + bloc*8 - 1; colonne++)
                {
                    res[ligne][colonne] = array_matrices[bloc][ligne%8][colonne%8];
                }
            }

            free_matrice_entier_sansp_uint8(array_matrices[bloc], dim_bloc);
        }


        for (bloc = 2; bloc <= 3; bloc++)
        {
            for (ligne = 8; ligne <= 15; ligne++)
            {
                for (colonne = (bloc-2)*8; colonne <= 8 + (bloc-2)*8 - 1; colonne++)
                {
                    res[ligne][colonne] = array_matrices[bloc][ligne%8][colonne%8];
                }
            }

            free_matrice_entier_sansp_uint8(array_matrices[bloc], dim_bloc);
        } 

        return res;
    }




    else if (dim_en_blocs[0] == 2 && dim_en_blocs[1] == 1)
    {

        for (ligne = 0; ligne <= 7; ligne++)
        {
            for (colonne = 0; colonne <= 7; colonne++)
            {
                res[ligne][colonne] = array_matrices[0][ligne][colonne];
            }
        }

        for (ligne = 8; ligne <= 15; ligne++)
        {
            for (colonne = 0; colonne <= 7; colonne++)
            {
                res[ligne][colonne] = array_matrices[2][ligne%8][colonne];
            }
        }

        free_matrice_entier_sansp_uint8(array_matrices[0], dim_bloc);
        free_matrice_entier_sansp_uint8(array_matrices[2], dim_bloc);

        return res;
    
    }


    else if (dim_en_blocs[0] == 1 && dim_en_blocs[1] == 2)
    {

        for (ligne = 0; ligne <= 7; ligne++)
        {
            for (colonne = 0; colonne <= 7; colonne++)
            {
                res[ligne][colonne] = array_matrices[0][ligne][colonne];
            }
        }

        for (ligne = 0; ligne <= 7; ligne++)
        {
            for (colonne = 8; colonne <= 15; colonne++)
            {
                res[ligne][colonne] = array_matrices[1][ligne][colonne%8];
            }
        }

        free_matrice_entier_sansp_uint8(array_matrices[0], dim_bloc);
        free_matrice_entier_sansp_uint8(array_matrices[1], dim_bloc);

        return res;
    
    }

    else
    {
        printf("erreur de dimensions\n");
        return NULL;
    }



}




























uint8_t** fusion_matrice_chrominance(uint8_t ***array_matrices, uint8_t dim_en_blocs[2])
/*fusionne pour les chrominances soit 2 matrices 8*8 en 2*1, soit 2 matrices en 1*2, soit 4 matrices en 4*4, cela de gauche à droite puis de haut en bas*/
{
    size_t dim_res[2] = {8*dim_en_blocs[0], 8*dim_en_blocs[1]};

    size_t dim_bloc[2] = {8, 8};

    uint8_t **res = init_matrice_sansp_uint8(dim_res, 0);

    size_t ligne;
    size_t colonne;
    size_t bloc;

    if (dim_en_blocs[0] == 2 && dim_en_blocs[1] == 2)
    {

        for (bloc = 0; bloc <= 1; bloc++)
        {
            for (ligne = 0; ligne <= 7; ligne++)
            {
                for (colonne = bloc*8; colonne <= 8 + bloc*8 - 1; colonne++)
                {
                    res[ligne][colonne] = array_matrices[bloc][ligne%8][colonne%8];
                }
            }

            free_matrice_entier_sansp_uint8(array_matrices[bloc], dim_bloc);
        }


        for (bloc = 2; bloc <= 3; bloc++)
        {
            for (ligne = 8; ligne <= 15; ligne++)
            {
                for (colonne = (bloc-2)*8; colonne <= 8 + (bloc-2)*8 - 1; colonne++)
                {
                    res[ligne][colonne] = array_matrices[bloc][ligne%8][colonne%8];
                }
            }

            free_matrice_entier_sansp_uint8(array_matrices[bloc], dim_bloc);
        } 

        free(array_matrices);

        return res;
    }




    else if (dim_en_blocs[0] == 2 && dim_en_blocs[1] == 1)
    {

        for (ligne = 0; ligne <= 7; ligne++)
        {
            for (colonne = 0; colonne <= 7; colonne++)
            {
                res[ligne][colonne] = array_matrices[0][ligne][colonne];
            }
        }

        for (ligne = 8; ligne <= 15; ligne++)
        {
            for (colonne = 0; colonne <= 7; colonne++)
            {
                res[ligne][colonne] = array_matrices[2][ligne%8][colonne];
            }
        }

        free_matrice_entier_sansp_uint8(array_matrices[0], dim_bloc);
        free_matrice_entier_sansp_uint8(array_matrices[2], dim_bloc);
        free(array_matrices);

        return res;
    
    }


    else if (dim_en_blocs[0] == 1 && dim_en_blocs[1] == 2)
    {

        for (ligne = 0; ligne <= 7; ligne++)
        {
            for (colonne = 0; colonne <= 7; colonne++)
            {
                res[ligne][colonne] = array_matrices[0][ligne][colonne];
            }
        }

        for (ligne = 0; ligne <= 7; ligne++)
        {
            for (colonne = 8; colonne <= 15; colonne++)
            {
                res[ligne][colonne] = array_matrices[1][ligne][colonne%8];
            }
        }

        free_matrice_entier_sansp_uint8(array_matrices[0], dim_bloc);
        free_matrice_entier_sansp_uint8(array_matrices[1], dim_bloc);
        free(array_matrices);

        return res;
    
    }

    else
    {
        printf("erreur de dimensions\n");
        return NULL;
    }



}












uint8_t** upsampling_et_fusion_unitaire_chrominance(uint8_t ***vect_blocs, size_t indice_bloc, uint8_t facteur_sampling_hori, uint8_t facteur_sampling_verti, uint8_t h_Y, uint8_t v_Y)
/*entrées : vecteur de blocs pour une chrominance ; indice de départ de "prélèvement" dans vect_blocs  ;  facteurs d'échantillonnage pour la chrominance considérée  ;  facteurs d'échantillonnage pour Y*/
/*sorties : matrice "fusionnée" faisant soit 8*16, soit 16*8, soit 16*16*/
{
    if (!(h_Y == 1 && v_Y == 1))
    {
        uint8_t ***vect_mcu = duplication_upsampling_unitaire(vect_blocs, indice_bloc, facteur_sampling_hori, facteur_sampling_verti, h_Y, v_Y);

        uint8_t dim_en_blocs[2] = {v_Y, h_Y};

        return fusion_matrice_chrominance(vect_mcu, dim_en_blocs);
    }

    else
    {
        printf("Erreur : pas de sur-échantillonnage nécessaire\n");
        return NULL;
    }

}














uint8_t** creation_mcu_Y(uint8_t ***vect_blocs, size_t indice_bloc, uint8_t h_Y, uint8_t v_Y)
/*On prend un paquet de blocs dans le vecteur de blocs de Y en partant de l'indice "indice_bloc" dans le 
  vecteur et on les fusionne pour renvoyer une matrice de taille 8*16, 16*8, 16*16.*/
{

    uint8_t **array_Y[4];
    uint8_t dim_en_blocs[2] = {v_Y, h_Y};
    
    if (h_Y == 2 && v_Y == 2)
    {
        array_Y[0] = vect_blocs[indice_bloc];
        array_Y[1] = vect_blocs[indice_bloc + 1];
        array_Y[2] = vect_blocs[indice_bloc + 2];
        array_Y[3] = vect_blocs[indice_bloc + 3];
        return fusion_matrice_Y(array_Y, dim_en_blocs);

        
    }

    else if (h_Y == 1 && v_Y == 2)
    {
        array_Y[0] = vect_blocs[indice_bloc];
        array_Y[2] = vect_blocs[indice_bloc + 1];
        return fusion_matrice_Y(array_Y, dim_en_blocs);
    }

    else if (h_Y == 2 && v_Y == 1)
    {
        array_Y[0] = vect_blocs[indice_bloc];
        array_Y[1] = vect_blocs[indice_bloc + 1];
        return fusion_matrice_Y(array_Y, dim_en_blocs);
    }

    else
    {
        printf("Erreur : pas de sur-échantillonnage nécessaire\n");
        return NULL;
    }

}














void creation_mcus_data(struct data_1 *data)
/*On initialise chaque composante de vect_fin_upsampling appartenant à une structure data_1 pointée par le pointeur data.
  Ensuite, on créé les MCUs qui seront les éléments de vect_fin_upsampling[i] pour i allant de 0 à 2, cela grâce aux fonctions ci-dessus.
  En dernier lieu, on "free" chaque composante de vect_fin_idct et ses éléments qui auront été utilisés pour le sur-échantillonnage et la création des MCUs.*/
{
    data -> vect_fin_upsampling[0] = calloc(data -> len_mcus, sizeof(uint8_t **));
    data -> vect_fin_upsampling[1] = calloc(data -> len_mcus, sizeof(uint8_t **));
    data -> vect_fin_upsampling[2] = calloc(data -> len_mcus, sizeof(uint8_t **));

    size_t mcu;

    uint8_t h_Y = data -> param_sampling[0];
    uint8_t v_Y = data -> param_sampling[1];

    uint8_t h_Cb = data -> param_sampling[2];
    uint8_t v_Cb = data -> param_sampling[3];

    uint8_t h_Cr = data -> param_sampling[4];
    uint8_t v_Cr = data -> param_sampling[5];


    for (mcu = 0; mcu <= (data -> len_mcus - 1); mcu++)
    {
        data -> vect_fin_upsampling[0][mcu] = creation_mcu_Y(data -> vect_fin_idct[0], mcu*(h_Y*v_Y), h_Y, v_Y);
    }

    free(data -> vect_fin_idct[0]);


    for (mcu = 0; mcu <= (data -> len_mcus - 1); mcu++)
    {
        data -> vect_fin_upsampling[1][mcu] = upsampling_et_fusion_unitaire_chrominance(data -> vect_fin_idct[1], mcu*(h_Cb*v_Cb), h_Cb, v_Cb, h_Y, v_Y);
    }

    free(data -> vect_fin_idct[1]);

    for (mcu = 0; mcu <= (data -> len_mcus - 1); mcu++)
    {
        data -> vect_fin_upsampling[2][mcu] = upsampling_et_fusion_unitaire_chrominance(data -> vect_fin_idct[2], mcu*(h_Cr*v_Cr), h_Cr, v_Cr, h_Y, v_Y);
    }

    free(data -> vect_fin_idct[2]);

}
