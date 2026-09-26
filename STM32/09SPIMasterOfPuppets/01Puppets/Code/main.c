
#include "conf.h"
#include <stm32f4xx.h>

// ---------- Class ----------
// -------- Variables --------
// ----------- Main -----------

void delay_ms(volatile uint32_t);
int main(void){
	config();
	while(1){
		if(SPI1->SR & SPI_SR_RXNE){
			uint8_t aux = SPI1->DR;
			if(aux == LED_ON)
				GPIOC->BSRR = (1<<13);
				else if(aux ==LED_OFF)
					GPIOC->BSRR=(1<<(13+16));
		}
	}


}

