#include "conf.h"

void confRCC(void){
                /*    IOB,    IOA,   AF*/
    RCC->AHB1ENR |= (1<<0); // GPIOA ADC1 PA0
    RCC->APB2ENR|=(1<<7); //PRENDEMOS ADC1
    RCC->APB2ENR |= (1<<0); //TIM1
    RCC->APB1ENR|=(1<<29);
}
void confGPIO(void){
	GPIOA->MODER |= (3<<0);//PA0ANALOGICAENTRADA
	GPIOA->MODER|=(3<<2*4);//PA4 CH1 DEL DAC
}

void confADC(void){
	/*EMPEZAMOS LA CONFIGURACIÓN DEL ADC1 CON LA CONVERSIÓN EN EL CANAL 13*/
	ADC1->SQR3|=(13<<0);
	ADC1->CR2|=(3<<0);//ACTIVAMOS CONTINUOS CONV Y ADCON
	ADC1->CR1|=(1<<8);//SACANMODE
	ADC1->SMPR2|=(2<<0); //ESTAMOS CONFIGURANDO 28 CICLOS DE MUESTREO
}

void confTIMER(void)
{
    TIM1->PSC = 999;
    TIM1->CCMR1 |=(6<<4); // Enable PWM
    TIM1->CCER  |=(1<<0);//ACTIVAMOS CANAL1
    TIM1->ARR  =1599;
    /*TIM1->BDTR|=(16<<0);//RETRASO EN LA SALIDA DEL PWM COMPLEMENTARIO
    TIM1->BDTR|=(1<<15);//activamos la salida del canal complementario*/
    TIM1->CR1|=(1<<0);//activamos cuenta
}

void config(void){
    confRCC();
    confGPIO();
    confADC();
    confTIMER();
}

void confDAC(void){
	DAC->CR|=(1<<0);//HABILITO EL CHAN1 DEL DAC
	DAC->CR|=(7<<3);//HANILITO DISPARO POR SOFTWARE
	DAC->CR|=(1<<2);//HANILITO DAC POR EVENTO DE DISPARO
}
