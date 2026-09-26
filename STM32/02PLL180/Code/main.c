#include <stm32f446xx.h>
#include "conf.h"
void delay_ms(uint32_t delay);

int main (void){
	setClkPLL();
	confRCC(); 
	confGPIO();
	uint32_t delay_val = 10;
	uint32_t clk = SystemCoreClock;
	while(1){
	GPIOA->ODR ^= (1 << 5);
	delay_ms(delay_val);
}
}

void delay_ms(uint32_t delay){
	for(uint32_t i=0;i<delay;i++){
	for(uint32_t j=0;j<11500;j++);
	}
}