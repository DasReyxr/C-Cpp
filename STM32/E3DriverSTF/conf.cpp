#include "conf.h"

/*

 A3 CS OUT
 A4 DC OUT
 A5 SCK AFR
 A6 RES OUT
 A7 MOSI AFR
 
*/

void confRCC(void){
                 
    RCC->AHB1ENR |= (1<<0); // GPIOA SPI1
    RCC->APB2ENR |=(1<<12);//ENCENDEMOS SPI1
}
void confGPIO(void){
                /*    SCK    |     MOSI*/
	GPIOA->MODER |= (2<<(2*5)| 2<<(2*7)); 
	GPIOA->AFR[0]|= (5<<(4*5)| 5<<(4*7)); 
	
                  /*      CS    |     DC/X |    RESET */
    GPIOA->MODER |= (1<<(2*3))|(1<<(2*4))| (1<<(2*6));
    

}


void confSPI(void){
	// Baud rate: divide by 16 for 1MHz communication (16MHz / 16 = 1MHz)
	SPI1->CR1 |=(3<<3);//BR = 011 -> divide by 16
	
	// Master mode
	SPI1->CR1 |=(1<<2);//activamos modo maestro
	
	// Software NSS management
	SPI1->CR1 |=(1<<9);//ACTIVAMOS SS POR SOFTWARE SSM
	SPI1->CR1 |=(1<<8);//ACTIVAMOS EL SS INTERNO PARA FORZAR UNA HABILITACIÓN EN EL MAESTRO SSI
	//config the DFF
    //SPI1->CR1 |=(1<<11);//habilitamos trama de 16 bits 
	// Enable SPI
	SPI1->CR1 |=(1<<6);//PRENDEMOS EL SPI
}

void config(void){
    confRCC();
    confGPIO();
    confSPI();
}
