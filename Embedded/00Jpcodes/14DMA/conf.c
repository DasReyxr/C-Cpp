#include "conf.h"
#include <stm32f446xx.h>
void confRCC(void){
                /*    IOB,    IOA,   AF*/
    RCC->AHB1ENR |= (1<<0); // GPIOA ADC1 PA0
    RCC->APB2ENR|=(1<<7); //PRENDEMOS ADC1
    RCC->AHB1ENR|=(RCC_AHB1ENR_DMA2EN)//ENCENDEMOS DMA
}
void confGPIO(void){
	GPIOA->MODER |= (3<<0);//PA0ANALOGICAENTRADA
}

void confADC(void){
    ADC1->CR1|=(1<<8);//SCANMODE
    ADC1->SMPR2|=(2<<0); //ESTAMOS CONFIGURANDO 28 CICLOS DE MUESTREO
    ADC1->CR2|=(ADC_CR2_DMA)|(ADC_CR2_DDS);//ACTIVAMOS DMA Y PETICIONES CONTINUAS
	ADC1->CR2|=(3<<0);//ACTIVAMOS CONTINUOS CONV Y ADCON
}

void confTIMER(void)
{
    TIM1->PSC = 999;
    TIM1->CCMR1 |=(6<<4); // Enable PWM
    TIM1->CCER  |=(1<<0);//ACTIVAMOS CANAL1
    TIM1->ARR  =1599;
    TIM1->CR1|=(1<<0);//activamos cuenta
}

void config(void){
    confRCC();
    confGPIO();
    confADC();
    confTIMER();
    confDMA();
}

extern void confDMA(void){
    DMA2_Stream0->PAR=(uint32_t)&ADC1->DR;//fuente->registr0 del ADC
    DMA2_Stream0->M0AR=(uint32_t)adc_buffer[ADC_BUFFER_SIZE]; //GUARDAMOS EL DATO EN EL BUFFER RAM
    DMA2_Stream0->NDTR=ADC_BUFFER_SIZE;//CUANTOS DATOS VA A PASAR
    DMA2_Stream0->CR|=(DMA_SxCR_CIRC)|(DMA_SxCR_MINC);//MODO CIRCULAR ACTIVADO Y POSINCREMENTO AUTOMATICO DE LA MEMORIA
    DMA2_Stream0->CR|=(DMA_SxCR_MSIZE_1)|(DMA_SxCR_PSIZE_1);//TAMAÑO DE DATOS DE LECTURA DEL ADC
    DMA2_Stream0->CR&=~(0<<0);//CANAL 0 DEL DMA
    DMA2_Stream0->CR|=(DMA_SxCR_EN);//habilitamo DMA
}