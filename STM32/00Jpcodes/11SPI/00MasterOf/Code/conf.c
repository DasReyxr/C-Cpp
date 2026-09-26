#include "conf.h"

/*
PINOUT
PA4 NSS
PA5 SCLK
PA6 MISO
PA7 MOSI

*/

void confRCC(void){
                /*    IOB,    IOA,   AF*/
    RCC->AHB1ENR |= (1<<0); // GPIOA SPI1
    RCC->APB2ENR |=(1<<12);//ENCENDEMOS SPI1
}
void confGPIO(void){
	GPIOA->MODER |= (2<<(2*5)|2<<(2*6)|2<<(2*7));//ALTERNATE FUNCTION DEL PA5,PA6 Y PA7
	GPIOA->AFR[0]|=(5<<(4*5)|5<<(4*6)|5<<(4*7));//PARTE BAJA DEL AFR Y PONEMOS EL AF5 DEL SPI
	/*haniñitacion por hardware quiere deir que es habilitación manual*/
	GPIOA->MODER |= (1<<(2*4));
	GPIOA->OSPEEDR|=(3<<(2*4));
	GPIOA->BSRR=(1<<4);
}


void confSPI(void){
	// Baud rate: divide by 16 for 1MHz communication (16MHz / 16 = 1MHz)
	SPI1->CR1 |=(3<<3);//BR = 011 -> divide by 16
	
	// Master mode
	SPI1->CR1 |=(1<<2);//activamos modo maestro
	
	// Software NSS management
	SPI1->CR1 |=(1<<9);//ACTIVAMOS SS POR SOFTWARE SSM
	SPI1->CR1 |=(1<<8);//ACTIVAMOS EL SS INTERNO PARA FORZAR UNA HABILITACIÓN EN EL MAESTRO SSI
	
	// Frame format: 8-bit, MSB first (defaults are fine)
	// CPOL = 0, CPHA = 0 (mode 0)
	
	// Enable SPI
	SPI1->CR1 |=(1<<6);//PRENDEMOS EL SPI
}

void config(void){
    confRCC();
    confGPIO();
    confSPI();
}
