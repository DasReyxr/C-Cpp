#include "stm32f4xx.h"
#include "ComplexGJ.h"
#include <stdint.h>
#include <stdio.h>
// Pinout
/*
TFT Screen
A[3-7]

Keypad
PB[6-9] Scan
PB[12-15] Read

*/

int main(void) {
    CONF_Keypad();

    int n = 3;
    cplx A[N_MAX][N_MAX] = {0};
    cplx b[N_MAX] = {0};
    cplx x[N_MAX] = {0};

    // Ingresion de datos por Key 4x4
    printf("\nEnter the order of matrix: ");
    scanf("%d", &N_MAX);
    
    printf("\nEnter the elements of augmented matrix row-wise (real imag):\n\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j <= n; j++) {
            // LCD
            printf("A[%d][%d] (real imag): ", i, j);
            
            scanf("%lf %lf", &real, &imag);
            A[i][j] = real + imag * I;
        }
    }
    
    
    A[0][0] = (cplx){15,10}; A[0][1] = (cplx){4.8,-7}; A[0][2] = (cplx){5,8};
    A[1][0] = (cplx){-3,0}; A[1][1] = (cplx){0,-4};  A[1][2] = (cplx){-2,2};
    A[2][0] = (cplx){2,0}; A[2][1] = (cplx){0,0};  A[2][2] = (cplx){1,-1};
    
    b[0] = (cplx){1,0};
    b[1] = (cplx){0,1};
    b[2] = (cplx){-1,2};

    int jaloone = solve_complex_system(n, A, b, x);

    float real0 = x[0].r;
    float real1 = x[1].r;
    float real2 = x[2].r;

    float im0 = x[0].i;
    float im1 = x[1].i;
    float im2 = x[2].i;

    char buf_real[8], buf_imag[8];
    int idx = 0;

    float real = x[0].r;
    float imag = x[0].i;

    idx = 0;
    ftoa_for_oled(real, buf_real, &idx, 3);
    buf_real[idx] = '\0';  

    idx = 0;
    ftoa_for_oled(imag, buf_imag, &idx, 3);
    buf_imag[idx] = '\0';  

    // Now buf_real and buf_imag are ready to be drawn on OLED
    // OLED_DrawString(x_coord_real, y_coord, buf_real);
    // OLED_DrawString(x_coord_imag, y_coord, buf_imag);
    // p

    while (1){
    

        
    }
}