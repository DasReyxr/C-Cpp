#include <conf.h>
uint16_t convADC();
#define pwm100 15999
int main (void){
	config();
	ADC1->CR2|=ADC_CR2_SWSTART;
	uint16_t ADCDATA;
	while(1){
		ADCDATA = convADC();
		//TIM1->CCR1 = ADCDATA;
		DAC->DHR12R1 = ADC1->DR;
		DAC->SWTRIGR|=(1<<0);
	}
}
uint16_t convADC(){
	while(!(ADC1->SR & ADC_SR_EOC));
	uint32_t ADCDATA = ADC1->DR;
	ADCDATA *=PWM100;
	ADCDATA>>=12;
	ADC->SR &=~ADC_SR_EOC;
	return ADCDATA;
}
