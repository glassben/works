#include "./../../include/module_matriciel.h"







/*Les éléments des matrices des fonctions ci-dessous sont directement des valeurs et non des pointeurs.*/







float **init_matrice_sansp_float(size_t dim[2], float valeur_base)
/*Initialise une matrice dont les éléments sont directement des nombres flottants avec une valeur de base choisie.*/
{
    float **A = calloc(dim[0], sizeof(float *));

    size_t i;
    size_t j;
    for (i = 0; i <= dim[0] - 1; i++)
    {
        A[i] = calloc(dim[1], sizeof(float));
        if (valeur_base != 0)
        {
            for (j = 0; j <= dim[1] - 1; j++)
            {
                A[i][j] = valeur_base;
            }   
        }
    }

    return A;
    
}







int16_t **init_matrice_sansp_int16(size_t dim[2], int16_t valeur_base)
/*Initialise une matrice dont les éléments sont directement des nombres de type int16_t avec une valeur de base choisie.*/
{
    int16_t **A = calloc(dim[0], sizeof(int16_t *));

    size_t i;
    size_t j;
    for (i = 0; i <= dim[0] - 1; i++)
    {
        A[i] = calloc(dim[1], sizeof(int16_t));
        if (valeur_base != 0)
        {
            for (j = 0; j <= dim[1] - 1; j++)
            {
                A[i][j] = valeur_base;
            }   
        }
    }

    return A;
    
}






uint8_t **init_matrice_sansp_uint8(size_t dim[2], uint8_t valeur_base)
/*Initialise une matrice dont les éléments sont directement des nombres de type uint8_t avec une valeur de base choisie.*/
{
    uint8_t **A = calloc(dim[0], sizeof(uint8_t *));

    size_t i;
    size_t j;
    for (i = 0; i <= dim[0] - 1; i++)
    {
        A[i] = calloc(dim[1], sizeof(uint8_t));
        if (valeur_base != 0)
        {
            for (j = 0; j <= dim[1] - 1; j++)
            {
                A[i][j] = valeur_base;
            }   
        }
    }

    return A;
    
}

















void free_matrice_generale_sansp_float(float **A, size_t dim_A[2], int free_entier) 
/*free différentes structures de la matrice de nombres flottants selon choix (juste lignes ou tout)*/
{
    size_t i;

    for (i = 0; i <= dim_A[0] - 1; i++)
    {
        free(A[i]);
    }

    if (free_entier != 0)
    {
        free(A);
    }  

}






void free_matrice_entier_sansp_float(float **A, size_t dim_A[2])
/*free toute la matrice de nombres flottants*/
{
    free_matrice_generale_sansp_float(A, dim_A, 1);
}







void free_matrice_generale_sansp_int16(int16_t **A, size_t dim_A[2], int free_entier)
/*free différentes structures de la matrice de nombres en int16_t selon choix (juste lignes ou tout)*/
{
    size_t i;

    for (i = 0; i <= dim_A[0] - 1; i++)
    {
        free(A[i]);
    }

    if (free_entier != 0)
    {
        free(A);
    }  

}






void free_matrice_entier_sansp_int16(int16_t **A, size_t dim_A[2])
/*free toute la matrice de nombres en int16_t*/
{
    free_matrice_generale_sansp_int16(A, dim_A, 1);
}








void free_matrice_generale_sansp_uint8(uint8_t **A, size_t dim_A[2], int free_entier)
/*free différentes structures de la matrice de nombres en uint8_t selon choix (juste lignes ou tout)*/
{
    size_t i;

    for (i = 0; i <= dim_A[0] - 1; i++)
    {
        free(A[i]);
    }

    if (free_entier != 0)
    {
        free(A);
    }  

}





void free_matrice_entier_sansp_uint8(uint8_t **A, size_t dim_A[2])
/*free toute la matrice de nombres en uint8_t*/
{
    free_matrice_generale_sansp_uint8(A, dim_A, 1);
}











void print_matrice_sansp_float(float **A, size_t dim_A[2])
/*print sur la sortie standard la matrice de nombres flottants.*/
{
    size_t i;
    size_t j;
    for (i = 0; i <= dim_A[0] - 1; i++)
    {
        for (j = 0; j <= dim_A[1] - 1; j++)
        {
            printf("%f ", A[i][j]);
        }
        printf("\n");
    }
}






void print_matrice_sansp_int16(int16_t **A, size_t dim_A[2])
/*print sur la sortie standard la matrice de nombres en int16_t.*/
{
    size_t i;
    size_t j;
    for (i = 0; i <= dim_A[0] - 1; i++)
    {
        for (j = 0; j <= dim_A[1] - 1; j++)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}







void print_matrice_sansp_uint8(uint8_t **A, size_t dim_A[2])
/*print sur la sortie standard la matrice de nombres en uint8_t.*/
{
    size_t i;
    size_t j;
    for (i = 0; i <= dim_A[0] - 1; i++)
    {
        for (j = 0; j <= dim_A[1] - 1; j++)
        {
            printf("%u ", A[i][j]);
        }
        printf("\n");
    }
}
