
#include "conf.h"
#include <stm32f446xx.h>

// --------- Function ---------
uint8_t SPI_Send_Data(uint8_t);
void delay_ms(volatile uint32_t);

// ---------- Class ----------
// -------- Variables --------
// ----------- Main -----------
int main(void){
	config();
	while(1){
		//ledon
		GPIOA->BSRR|=(1<<(4+16));//CON CERO SELECCIONAMOS AL ESCLAVO
		SPI_Send_Data(LED_ON);
		GPIOA->BSRR|=(1<<(4));//CON 1 QUITAMOS LA SELECCION DEL ESCLAVO
		delay_ms(2000);
		//ledoff
		GPIOA->BSRR|=(1<<(4+16));//CON CERO SELECCIONAMOS AL ESCLAVO
		SPI_Send_Data(LED_OFF);
		GPIOA->BSRR|=(1<<(4));//CON 1 QUITAMOS LA SELECCION DEL ESCLAVO
		delay_ms(2000);
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
