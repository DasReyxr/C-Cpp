#include <stm32f446xx.h>
#include "conf.h"
/*
PINOUT
PA4 -> DAC 1/1
PA0 -> ADC 1/0

Use TIM1 to generate complementary PWM outputs (main and complement) with dead
time to emulate the class-D half-bridge outputs. Modulate the PWM with an input audio 
signal (500 Hz 14 kHz). Sample the signal (either the raw PWM or the filtered output) with 
the ADC triggered by a timer at a sampling rate chosen according to the Nyquist criterion.  

*/


void confRCC(void){
    RCC->AHB1ENR |= (1 << 0) ; // A 

    RCC->APB1ENR |= (1<<0)|(1<<29); // TIM2 & DAC
    RCC->APB2ENR |= (1<<8); //  ADC
    
}

void confGPIO(void){
                /*   DAC       ADC*/
	GPIOA->MODER |= (3<<2*4) | (3<<0); 
    
}

void confTIMER(void)
{
    //------- TIM2 -------
    TIM2->PSC = 9;
    TIM2->ARR  =12;// 1.6M*(1/140K) FREC DE MUESTREO DE 140KHZ
    TIM2->CCER  |=(1<<0);//ACTIVAMOS CANAL1
    TIM2->CR1|=(1<<0);//activamos cuenta
	TIM2->DIER |= TIM_DIER_UIE; //interrupcion por desbordamiento
    
}



void confADC(void){
	/*EMPEZAMOS LA CONFIGURACIÓN DEL ADC1 CON LA CONVERSIÓN EN EL CANAL 13*/
	//ADC1->SQR3|=(13<<0);
	ADC1->CR2|=(3<<0);//ACTIVAMOS CONTINUOS CONV Y ADCON
    ADC1->CR2|=(1<<30);//INICIAMOS LA CONVERSIÓN
	ADC1->CR1|=(1<<8);//SACANMODE
	ADC1->SMPR2|=(2<<0); //ESTAMOS CONFIGURANDO 28 CICLOS DE MUESTREO
    
}


void confDAC(void){
	DAC->CR|=(1<<0);//HABILITO EL CHAN1 DEL DAC
	DAC->CR|=(7<<3);//HANILITO DISPARO POR SOFTWARE
	DAC->CR|=(1<<2);//HANILITO DAC POR EVENTO DE DISPARO
}

void confNVIC(void){
	NVIC_EnableIRQ(TIM2_IRQn);
	NVIC_SetPriority(TIM2_IRQn, 1);

}

void config(void){
    confRCC();
    confADC();
    confGPIO();
    confTIMER();
    confNVIC();
}

