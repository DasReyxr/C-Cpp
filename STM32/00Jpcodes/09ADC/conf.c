#include <stm32f446xx.h>
#include "conf.h"

uint16_t contPulses(void);
int main(void){
    confRCC();
	confGPIO();
	confTIMER();
    uint16_t lastCount =  TIM4->CNT;
	while(1){
    lastCount = contPulses(lastCount);

    }
}

uint16_t contPulses(uint16_t lastCount){
}