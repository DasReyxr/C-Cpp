#include <stm32f446xx.h>
#include "conf.h"

int main(void){
    confRCC();
	confGPIO();
	confTIMER();
	configNVIC();
	while(1){

}

void TIM4_IRQHandler(void){
	while (TIM4->SR & TIM_SR_UIF)
	{
		GPIOA->ODR ^= GPIO_ODR_OD5;     
        TIM4->SR &= ~TIM_SR_UIF;

	}
	}
}