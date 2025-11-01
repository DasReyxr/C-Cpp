/*
--------- Auf Das  ---------
------- ADC w PWM  -------
-------- 30/10/2025 --------

*/
// ------- Main Library -------
#include "conf.h"
#include <stm32f446xx.h>

// --------- Function ---------
void confRCC(void);
void confGPIO(void);
void delay_ms(volatile uint32_t ms);
uint8_t SPI_Send(uint8_t);
// ---------- Class ----------
// -------- Variables --------

// ----------- Main -----------

int main(void){
	config();

	while(1){
		GPIOA->BSRR |= (1<<4+16); // CS LOW
		SPI_Send(LED_ON);	
		GPIOA->BSRR |= (1<<4); // CS HIGH
		delay_ms(2000);

		GPIOA->BSRR |= (1<<4+16); // CS LOW
		SPI_Send(LED_OFF);	
		GPIOA->BSRR |= (1<<4); // CS HIGH
		delay_ms(2000);


	}
}
	 
	

uint8_t SPI_Send(uint8_t dataTX){
	while(!(SPI1->SR & SPI_SR_TXE)); 
	SPI1->DR = dataTX; 
	while(!(SPI1->SR & SPI_SR_RXNE)); 
	uint8_t dataRX = SPI1->DR;
	while(SPI1->SR & SPI_SR_BSY); 
	return dataRX;
 
}

void delay_ms(volatile uint32_t ms){
	while(ms--){
		for(volatile uint32_t i = 0; i < 16000; i++)
		__NOP();
		
	}
}