#include <stm32f446xx.h>
#include "conf.h"

int main(void){
confRCC();
	confGPIO();
	confTIMER();
	
	while(1){
	if (TIM4->CNT==15999)
	{
		GPIOA->ODR ^= GPIO_ODR_OD5;
	}
	}
}