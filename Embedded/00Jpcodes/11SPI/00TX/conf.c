
#include <stm32f446xx.h>
#include "conf.h"
/*
PINOUT
PA4 CS
PA5 SCLK
PA6 MISO
PA7 MOSI

*/


void confRCC(void){
    RCC->AHB1ENR |= (1 << 0) | (1 << 4); // A  E 

    RCC->APB1ENR |= (1 << 0); // TIM2 AD
    RCC->APB2ENR |= (1 << 1)  | (1<<8); // TIM1 ADC

    RCC->APB2ENR |= (1 << 12); // SPI1

}

void confGPIO(void){
    /* PA[7-5] as AF*/	
    GPIOA->MODER  |= (2<<2*5)|(2<<2*6)|(2<<2*7); 
    GPIOA->AFR[0] |= (5<<4*5)|(5<<4*6)|(5<<4*7); 
    /* PA4 as GPIO Output*/
    GPIOA->MODER  |= (1<<2*4);
    GPIOA->OSPEEDR|= (3<<2*4); 
}

void confSPI(void){
    /*
                SSM   | SSI    | BR 1 MHz| MSTR


    */
    SPI1->CR1|=(1<<9) | (1<<8)  | (3<<3) | (1<<2);
    SPI1->CR1|=(1<<6); // SPE 
/*
    CPOL <= 0 when clock in low
            1 when clock in high
    CPHA <= 0 sample in first edge
            1 sample in second edge
    we select 0,0
 */
    
}


void config(void){
    confRCC();
    confGPIO();
    confSPI();
}

