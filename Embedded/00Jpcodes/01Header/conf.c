/*
------ Orlando Reyes ------
--------- Auf Das ---------
---------- Config -----------
-------- 25/08/2025 --------
*/
// ------- Main Library -------

#include "conf.h"

// --------- Function ---------
	 
extern void confRCC(void){
	RCC->AHB1ENR |= (1 << 0) | (1 << 4); // A  E 	
}

void confGPIO(void){
	GPIOE->MODER |= (0x5555 << 16); // PE8 -> PE15 Output 
	GPIOA->PUPDR |= (0xA << 10); //PA5 y PA`6 como entrada PA5  + PA6 -
}

	 
/*No es necesario el static*/
void setClkHSE(void){
	RCC->CR |= (1 << 16) ; /*RCC_CR_HSEON*/
	while(RCC->CR & !RCC_CR_HSERDY);
	
}
