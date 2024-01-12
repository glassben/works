#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>


float * YCbCR_vers_RGB(float * pixel_YCbCr) {
    /* convertit les pixels YCbCr en RGB */
    float* pixel_RGB = calloc(3, sizeof(float));
    pixel_RGB[0] = pixel_YCbCr[0] - 0.0009267*(pixel_YCbCr[1] - 128) + 1.4016868*(pixel_YCbCr[2] - 128);
    pixel_RGB[1]  = pixel_YCbCr[0] - 0.3436954*(pixel_YCbCr[1] - 128) - 0.7141690*(pixel_YCbCr[2] - 128);
    pixel_RGB[2]  = pixel_YCbCr[0] + 1.7721604*(pixel_YCbCr[1] - 128) + 0.0009902*(pixel_YCbCr[2] - 128);
    return pixel_RGB;

}

float *** conversion_matrices(float *** tableau,  size_t taille_tableau) {
    /* tableau contient 3 matrices correspondant aux 3 composantes YCbCr */
    float *** tab_RGB = malloc(taille_tableau);
    float pixel_YCbCr[taille_tableau];
    for (int i = 0; i <= 7; i++){
            for (int j = 0; j <= 7; j++){
                pixel_YCbCr[0] = tableau[0][i][j];
                pixel_YCbCr[1] = tableau[1][i][j];
                pixel_YCbCr[2] = tableau[2][i][j];
                /* un triplet YCbCr */
                tab_RGB[0][i][j] = YCbCR_vers_RGB(pixel_YCbCr)[0];
                /* composante R */
                tab_RGB[1][i][j] = YCbCR_vers_RGB(pixel_YCbCr)[1];
                /* composante G */
                tab_RGB[2][i][j] = YCbCR_vers_RGB(pixel_YCbCr)[2];
                /* composante B */

            }
        }
    return tab_RGB;
}
