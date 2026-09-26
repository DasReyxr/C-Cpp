#include <stm32f446xx.h>
#include "conf.h"
/*
PINOUT
PA8 -> PWM 1/1 
PA7 -> PWM 1/1 Complementario
PA0 -> ADC IN0

Use TIM1 to generate complementary PWM outputs (main and complement) with dead
time to emulate the class-D half-bridge outputs. Modulate the PWM with an input audio 
signal (500 Hz–14 kHz). Sample the signal (either the raw PWM or the filtered output) with 
the ADC triggered by a timer at a sampling rate chosen according to the Nyquist criterion.  

*/


void confRCC(void){
    RCC->AHB1ENR |= (1 << 0) | (1 << 4); // A  E 	
    RCC->APB2ENR |= (1<<1); 
}

void confGPIO(void){
	
	GPIOE->MODER |= (0x5555 << 16); // PE8 -> PE15 Output 
	GPIOA->PUPDR |= (0xA << 10); //PA5 y PA6 como entrada PA5  + PA6 -
}

void confTIMER(void)
{
	//estos valores son para un periodo de 100ms
	TIM4->PSC = 0;
    TIM4->ARR = 0XFFFF; /* valor maximo de 2^16*/
    TIM4->CCMR1 |= (1<<0); /* Chanel 1 activated*/ 
	TIM4->CCER |= (1<<0) | (1<<3); /* Capture enabled */
    TIM4->SMCR |= (7<<0) | (5<<4); /* Trigger on TI1FP1, Edge rising, Filter = 0100 */


    TIM4->CR1 |=(0X81 <<0); //activamos la autorecarga en el buffer y el contador
	TIM4->DIER |= TIM_DIER_UIE; //interrupcion por desbordamiento

    TIM4->EGR |= TIM_EGR_UG; //actualizamos los registros
    TIM4->CR1 |= (1 << 0); //activamos el timer
}

void configNVIC(void){
	NVIC_EnableIRQ(TIM4_IRQn);
	NVIC_SetPriority(TIM4_IRQn, 1);

}

void config(void){
    confRCC();
    confGPIO();
    confTIMER();
    configNVIC();
}