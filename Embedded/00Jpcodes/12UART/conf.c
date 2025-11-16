#include "conf.h"

void confRCC(void){

	RCC->AHB1ENR |= (1<<0); // GPIOA
    RCC->APB1ENR |=(1<<17);//ENCENDEMOS USART2
}
void confGPIO(void){
	/*                 PA2TX PA3RX*/
	GPIOA->MODER |= (2<<(2*2)|2<<(2*3));//ALTERNATE FUNCTION DEL PA2 y PA3
	GPIOA->AFR[0]|=(7<<(4*2)|7<<(4*3));//PARTE BAJA DEL AFR Y PONEMOS EL AF7 DEL USART
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
    confUSART();
}
