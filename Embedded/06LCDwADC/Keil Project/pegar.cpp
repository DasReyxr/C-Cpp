#include <stm32f446xx.h>
#include "conf.h"
uint16_t contPulses(uint16_t);
int main(void){
confRCC();
	confGPIO();
	confTIMER();
	//confNVIC();
	uint16_t lastCount = TIM4->CNT;
	while(1){
		lastCount=contPulses(lastCount);
	}
}

uint16_t contPulses(uint16_t tempCount){
uint16_t curCount = TIM4->CNT;
if (curCount != tempCount ){
	GPIOA->ODR^=(1<<5);
	tempCount =curCount;
}
return tempCount;
}
