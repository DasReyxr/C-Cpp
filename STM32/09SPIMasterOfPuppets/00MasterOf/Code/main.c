/*
/*
------- Kevin Lara  -------
--------- Auf Das  ---------
---------- UART  ----------
-------- 12/11/2025 --------
In this practice two boards communicate: the master board sends a control command via 
SPI to the slave board to start a counter from 0 to 9, the slave prints each number on its 
UART terminal. When the count completes, the slave sends a finish command back to the 
master via SPI; the master then prints a message on its UART that the count cycle has 
finished, waits 3 seconds and sends the start command again. The slave keeps track of how 
many cycles it has executed.  


*/
// ------- Main Library -------
#include "conf.h"
#include "comusart.h"
#include <stm32f446xx.h>

// ---------- Class ----------
// -------- Variables --------
#define CON 6
#define CMD_START 0xA1
#define CMD_END   0xB1

const uint8_t string[CON] = "Yastaw";
// ----------- Main -----------
uint8_t SPI_Send_Data(uint8_t);
void delay_ms(volatile uint32_t);

int main(void){
	config();
  GPIOA->BSRR|=(1<<(4+16));//CON CERO SELECCIONAMOS AL ESCLAVO
  SPI_Send_Data(CMD_START);
  while(1){
    //ledon
	 SPI_Send_Data(0x01);
    //while(!(SPI1->SR & SPI_SR_RXNE));
    uint8_t aux = SPI1->DR;
    if(aux == CMD_END){
    GPIOA->BSRR|=(1<<(4));
    USART_SendString(string);
    USART_SendString("\n");
    USART_Sendchar(13);

    delay_ms(3000);
    GPIOA->BSRR|=(1<<(4+16));
	SPI_Send_Data(CMD_START);
    }

	}
  }


uint8_t SPI_Send_Data(uint8_t dataTX){
	while(!(SPI1->SR & SPI_SR_TXE));
	SPI1->DR = dataTX;
	while(!(SPI1->SR & SPI_SR_RXNE));
	uint8_t dataRX=SPI1->DR;
	while((SPI1->SR & SPI_SR_BSY));
	return dataRX;
}
void delay_ms(volatile uint32_t ms){
	while(ms--){
		for(volatile uint32_t i =0; i<1067;i++){
		}

	}

}
