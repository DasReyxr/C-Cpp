/*
--------- Auf Das  ---------
------- Filter IIR  -------
-------- 30/10/2025 --------

*/
// ------- Main Library -------
#include "conf.h"
#include <stm32f446xx.h>

// --------- Function ---------
void confRCC(void);
void confGPIO(void);
// ---------- Class ----------
// -------- Variables --------
// ----------- Main -----------
void conv(uint16_t*, const double*);
const double h[21] = {
    0,
    0.0008661866575345,
    -1.862664770708e-18,
    0.009379606223572,
    6.739184450067e-18,
    0.03185584403768,
    -1.276689426737e-17,
    0.08430039893725,
    1.764341394673e-17,
    0.310762760459,
    0.5003904280133,
    0.310762760459,
    1.764341394673e-17,
    -0.08430039893725,
    -1.276689426737e-17,
    0.03185584403768,
    6.739184450067e-18,
    -0.009379606223572,
    -1.862664770708e-18,
    0.0008661866575345,
    0
};
uint8_t i=0;
uint16_t smplVEC[21];
uint16_t out[21];
uint16_t out1[21];

int main(void){
    // Test: impulso
    for(int j = 0; j < 21; j++)
        smplVEC[j] = 0;
    smplVEC[0] = 1;


    while(1);
}


void TIM2_IRQHandler(void){
	if (TIM2->SR & (1<<0))
	{
		if(i<21){
			smplVEC[i]=ADC1->DR;
			i++;		
		}
		else{
			conv(smplVEC,h);
            i=0;
		}
		TIM2->SR &= ~(1<<0); // limpia UIF
	}
}

void conv(uint16_t *x, const double *h){
    for(uint8_t n = 0; n < 21; n++){
        out[n] = 0;  // limpia acumulador

        for(uint8_t k = 0; k < 21; k++){
            if(n >= k){
                out[n] += (uint16_t)(x[n - k] * h[k]);
            }
        }
    }
 
}