#include "conf.h"

void confRCC(void){
                /*    IOB,    IOA,   AF*/
    RCC->AHB1ENR |= (1<<0); // GPIOA SPI1
    RCC->APB2ENR |=(1<<12);//ENCENDEMOS SPI1
}
void confGPIO(void){
	GPIOA->MODER |= (2<<(2*4)|2<<(2*5)|2<<(2*6)|2<<(2*7));//ALTERNATE FUNCTION DEL PA5,PA6 Y PA7
	GPIOA->AFR[0]|=(5<<(4*4)|5<<(4*5)|5<<(4*6)|5<<(4*7));//PARTE BAJA DEL AFR Y PONEMOS EL AF5 DEL SPI
	/*haniLitacion por hardware quiere decir que es habilitación manual*/
	//GPIOA->MODER |= (1<<(2*4));
	//GPIOA->OSPEEDR|=(3<<(2*4));
	GPIOC->MODER |=(1<<2*13);
}


void confSPI(void){
/*
	SPI1->CR1 |=(3<<3);//seleccionamos un baudrate a frec de reloj de 1mhz
	SPI1->CR1 |=(1<<2);//activamos modo maestro
	SPI1->CR1 |=(1<<9);//ACTIVAMOS SS POR SOFTWARE SSM
	SPI1->CR1 |=(1<<8);//ACTIVAMOS EL SS INTERNO PARA FORZAR UNNA HABILITACIÓN EN EL MAESTRO SSI
	*/
	SPI1->CR1 |=(1<<6);//PRENDEMOS EL SPI
}

void config(void){
    confRCC();
    confGPIO();
    confSPI();
}
