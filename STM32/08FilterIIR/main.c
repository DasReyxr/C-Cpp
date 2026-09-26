/*
--------- Auf Das  ---------
------- Filter FIR  -------
-------- 30/10/2025 --------

*/
// ------- Main Library -------
#include "conf.h"
#include <stm32f446xx.h>
#include <math.h>

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
#define samples 200
#define out_len (samples*2 - 1)  
uint16_t smplVEC[samples]={0};
uint16_t out[out_len]={0};
uint8_t state=0;
uint8_t j=0;
int main(void){
    config();

    while(1);
}

/*

conv(smplVEC, h);            
0 Data Capture and Convolve
1 Data Output
*/


void TIM2_IRQHandler(void){
    if (TIM2->SR & (1<<0))
	{
        if (i < samples) {
            while(!(ADC1->SR & ADC_SR_EOC));
            smplVEC[i] = ADC1->DR;
         
        } else {
            conv(smplVEC, h);
             i = 0;
        }
           i++;

        TIM2->SR &= ~(1<<0); // limpia UIF
        }

}




void conv(uint16_t *x,const double *h)
{
    const uint8_t Lx = samples;   
    const uint8_t Lh = 21;        
    const uint8_t Ly = Lx;        
    for (uint8_t n = 0; n < Ly; n++) {

        double acc = 0.0;

        for (uint8_t k = 0; k < Lx; k++) {

            int hk = n - k;

            if (hk >= 0 && hk < Lh) {
                acc += (double)x[k] * h[hk];
            }
        }

        if (acc < 0.0)  acc = 0.0;
        if (acc > 4095.0) acc = 4095.0;
        
        DAC->DHR12R1 = (uint16_t)lrint(acc);
        DAC->SWTRIGR |= (1<<0);

    }
}

/*


*/