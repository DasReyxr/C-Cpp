#include "conf.h"
/* PINOUT
PB8 SCL
PB9 SDA
*/
void confRCC(void){

    RCC->AHB1ENR |= (1<<1); // GPIOB
    RCC->APB1ENR |=(1<<21);//ENCENDEMOS I2C1
}
void confGPIO(void){
	GPIOB->MODER |=(2<<(2*8))|(2<<(2*9));// ALTERNATE FUNCTION PB8(SCL) Y PB9(SDA)
	GPIOB->AFR[1] |=(4<<(4*8))|(4<<(4*9));//ALTENATE FUNCION AF4 EN PB8 Y PB9
	GPIOB->OTYPER|=(1<<6)|(1<<7);
}


void confI2C(void){//esta configurado a traa de 8 bits con 1 bit de parada sin paridad
	I2C1->CR2 |=(16<<0);//16mhz de frecuencia del 12c
	I2C1->CCR|=(80<<0);//estamos configurando una frecuencia de scl de fast mode
	I2C1->TRISE|=(17<<0);//TRISETIME (1000ns/62.5ns)+1=17
	I2C1->CR1|=(1<<0);//12CEN
	I2C1->CR1|=I2C_CR1_ACK;
}

void config(void){
    confRCC();
    confGPIO();
    confI2C();
}