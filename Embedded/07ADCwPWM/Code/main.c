/*
--------- Auf Das  ---------
------- ADC w PWM  -------
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

int main(void){
	config();

	while(1);
}
	 
	


void TIM2_IRQHandler(void){
	while (TIM2->SR & (1<<0))
	{
		TIM1->CCR1 = (ADC1->DR)<<4; // Ajusta el ciclo de trabajo del PWM según el valor leído por el ADC
        TIM2->SR &= ~(1<<0);	
	}
}
