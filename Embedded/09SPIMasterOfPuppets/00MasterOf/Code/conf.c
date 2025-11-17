/*
PINOUT
PA4 CS
PA5 SCLK
PA6 MISO
PA7 MOSI

*/
#include "conf.h"

void confRCC(void){
                /*    IOB,    IOA,   AF*/
    RCC->AHB1ENR |= (1<<0); // GPIOA SPI1
    RCC->APB2ENR |=(1<<12);//ENCENDEMOS SPI1
	RCC->APB1ENR |=(1<<17);//ENCENDEMOS USART2
}
void confGPIO(void){
	GPIOA->MODER |= (2<<(2*5)|2<<(2*6)|2<<(2*7));//ALTERNATE FUNCTION DEL PA5,PA6 Y PA7
	GPIOA->AFR[0]|=(5<<(4*5)|5<<(4*6)|5<<(4*7));//PARTE BAJA DEL AFR Y PONEMOS EL AF5 DEL SPI
	/*haniñitacion por hardware quiere deir que es habilitación manual*/
	GPIOA->MODER |= (1<<(2*4));
	GPIOA->OSPEEDR|=(3<<(2*4));
	//USART CONF
	GPIOA->MODER |= (2<<(2*2)|2<<(2*3));//ALTERNATE FUNCTION DEL PA2TX y PA3RX
	GPIOA->AFR[0]|=(7<<(4*2)|7<<(4*3));//PARTE BAJA DEL AFR Y PONEMOS EL AF7 DEL USART
}


void confSPI(void){

	SPI1->CR1 |=(3<<3);//seleccionamos un baudrate a frec de reloj de 1mhz
	SPI1->CR1 |=(1<<2);//activamos modo maestro
	SPI1->CR1 |=(1<<9);//ACTIVAMOS SS POR SOFTWARE SSM
	SPI1->CR1 |=(1<<8);//ACTIVAMOS EL SS INTERNO PARA FORZAR UNNA HABILITACIÓN EN EL MAESTRO SSI
	SPI1->CR1 |=(1<<6);//PRENDEMOS EL SPI
}

void confUSART(void){//esta configurado a traa de 8 bits con 1 bit de parada sin paridad
	USART2->CR1|=(1<<15)//8 OVERSAMPLING
				|(1<<3) //ENABLE TX
				|(1<<2) //ENABLE RX
				|(1<<13)//ENABLE USART
				;
	USART2->BRR=0xD06;//configuramos velocidad el baudrate de 9600baudios
}


void config(void){
    confRCC();
    confGPIO();
    confSPI();
    confUSART();
}
