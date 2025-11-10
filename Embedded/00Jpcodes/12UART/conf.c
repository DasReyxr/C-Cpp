1
#include <stm32f446xx.h>
#include "conf.h"
/*
PINOUT
PA2 USART TX
PA3 USART RX
*/


void confRCC(void){
    RCC->AHB1ENR |= (1<<17) |(1 << 0) | (1 << 4); // Usart 2 A  E 


    RCC->APB1ENR |= (1 << 0); // TIM2 AD
    RCC->APB2ENR |= (1 << 1)  | (1<<8); // TIM1 ADC

    RCC->APB2ENR |= (1 << 12); // SPI1

}

void confGPIO(void){


    /* PA[7-5] as AF*/	
    GPIOA->MODER  |= (3<<2*2)|(3<<2*3); 
    GPIOA->AFR[0] |= (7<<4*2)|(7<<4*3);
}

void confUSART(void){
    /*
        8 bits
        no parity
        1 stop bit
        baudrate 9600
    */
    
    /*             OS by8 | USART |  TXE   | RXE     */
    USART2->CR1 |= (1<<15)|(1<<13)| (1<<3) | (1<<2) ; 
    USART2->BRR = 0xD06; // 16MHz/(9600*8) = 208.33 = D06

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

