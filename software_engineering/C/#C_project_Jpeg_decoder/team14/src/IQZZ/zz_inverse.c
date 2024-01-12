#include "./../../include/module_matriciel.h"






int16_t** zz_inverse_un_bloc(int16_t *array)
/*créé la matrice 8*8 dé-zig-zaguée associée au vecteur array à 64 éléments.
  Ce vecteur est "free" à la fin.*/
{
    size_t dim_bloc[2] = {8, 8};

    int16_t **bloc = init_matrice_sansp_int16(dim_bloc, 0);

    bloc[0][0] = array[0];
    bloc[0][1] = array[1];
    bloc[1][0] = array[2];
    bloc[2][0] = array[3];
    bloc[1][1] = array[4];
    bloc[0][2] = array[5];
    bloc[0][3] = array[6];
    bloc[1][2] = array[7];

    bloc[2][1] = array[8];
    bloc[3][0] = array[9];
    bloc[4][0] = array[10];
    bloc[3][1] = array[11];
    bloc[2][2] = array[12];
    bloc[1][3] = array[13];
    bloc[0][4] = array[14];
    bloc[0][5] = array[15];

    bloc[1][4] = array[16];
    bloc[2][3] = array[17];
    bloc[3][2] = array[18];
    bloc[4][1] = array[19];
    bloc[5][0] = array[20];
    bloc[6][0] = array[21];
    bloc[5][1] = array[22];
    bloc[4][2] = array[23];

    bloc[3][3] = array[24];
    bloc[2][4] = array[25];
    bloc[1][5] = array[26];
    bloc[0][6] = array[27];
    bloc[0][7] = array[28];
    bloc[1][6] = array[29];
    bloc[2][5] = array[30];
    bloc[3][4] = array[31];

    bloc[4][3] = array[32];
    bloc[5][2] = array[33];
    bloc[6][1] = array[34];
    bloc[7][0] = array[35];
    bloc[7][1] = array[36];
    bloc[6][2] = array[37];
    bloc[5][3] = array[38];
    bloc[4][4] = array[39];

    bloc[3][5] = array[40];
    bloc[2][6] = array[41];
    bloc[1][7] = array[42];
    bloc[2][7] = array[43];
    bloc[3][6] = array[44];
    bloc[4][5] = array[45];
    bloc[5][4] = array[46];
    bloc[6][3] = array[47];

    bloc[7][2] = array[48];
    bloc[7][3] = array[49];
    bloc[6][4] = array[50];
    bloc[5][5] = array[51];
    bloc[4][6] = array[52];
    bloc[3][7] = array[53];
    bloc[4][7] = array[54];
    bloc[5][6] = array[55];

    bloc[6][5] = array[56];
    bloc[7][4] = array[57];
    bloc[7][5] = array[58];
    bloc[6][6] = array[59];
    bloc[5][7] = array[60];
    bloc[6][7] = array[61];
    bloc[7][6] = array[62];
    bloc[7][7] = array[63];

    free(array);


    return bloc;


}





int16_t*** zz_inverse_vect_array_to_vect_bloc(int16_t **vect_array, size_t long_vect)
/*Crée le vecteur de blocs dé-zig-zagués et free "vect_array" à la fin, qui est un vecteur de vecteurs à 64 éléments.*/
{
    int16_t ***vect_bloc = calloc(long_vect, sizeof(int16_t **));
    size_t i;


    for (i = 0; i <= long_vect - 1; i++)
    {
        vect_bloc[i] = zz_inverse_un_bloc(vect_array[i]);      
    }

    free(vect_array);

    return vect_bloc;
}








int modif_vect_fin_zz(struct data_1 *data)
/*initialise chaque composante requise de vect_fin_zz dans la structure data_1 pointée par data en créant 
  dans le tas les vecteurs de blocs dé-zig-zagués provenant des vecteurs de vect_fin_rle_et_qz*/
{

    if (data -> couleurs == false)
    {
        (data -> vect_fin_zz)[0] = zz_inverse_vect_array_to_vect_bloc(data -> vect_fin_rle_et_qz[0], data -> lens_composantes[0]);
        free(data -> vect_fin_rle_et_qz);
    }

    else
    {
        (data -> vect_fin_zz)[0] = zz_inverse_vect_array_to_vect_bloc(data -> vect_fin_rle_et_qz[0], data -> lens_composantes[0]);
        (data -> vect_fin_zz)[1] = zz_inverse_vect_array_to_vect_bloc(data -> vect_fin_rle_et_qz[1], data -> lens_composantes[1]);
        (data -> vect_fin_zz)[2] = zz_inverse_vect_array_to_vect_bloc(data -> vect_fin_rle_et_qz[2], data -> lens_composantes[2]);
        free(data -> vect_fin_rle_et_qz);
    }

    return EXIT_SUCCESS;
}
