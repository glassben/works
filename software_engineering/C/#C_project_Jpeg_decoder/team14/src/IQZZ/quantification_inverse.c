#include "../../include/module_matriciel.h"




void dequantification_unitaire(int16_t *x1, uint8_t *x2)
/*multiplie chaque composante du vecteur x1 par chaque composante respective du vecteur x2 qui sera une table de quantification*/
{
    size_t i;
    for (i = 0; i <= 63; i++)
    {
        x1[i] = x1[i]*x2[i];
    }

}








int dequantification_arrays(int16_t **vect_1, size_t len_1, uint8_t *x2)
/*déquantifie chaque vecteur à 64 éléments de vect_1 qui est donc un vecteur de vecteurs en utilisant x2 et la fonction ci-dessus*/
{
    size_t i;
    for (i = 0; i <= len_1 - 1; i++)
    {
        dequantification_unitaire(vect_1[i], x2);
    }

    

    return EXIT_SUCCESS;
}







void dequantification_totale(struct data_1 *data)
/*déquantifie en place chaque vecteur à 64 éléments pour chaque vecteur de vecteurs de chaque composante du vecteur vect_fin_rle_et_qz*/
{
    
    uint8_t *table_actuelle = (data -> tables_quantification)[0];

    dequantification_arrays(data -> vect_fin_rle_et_qz[0], data -> lens_composantes[0], table_actuelle);
    
    table_actuelle = (data -> tables_quantification)[1];
    if (data -> couleurs == true)
    {

        dequantification_arrays(data -> vect_fin_rle_et_qz[1], data -> lens_composantes[1], table_actuelle);

        dequantification_arrays(data -> vect_fin_rle_et_qz[2], data -> lens_composantes[2], table_actuelle);

    }


}
