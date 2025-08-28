/*
------ Orlando Reyes ------
--------- Auf Das ---------
----------- Test -----------
-------- 18/08/2025 --------
*/
// ------- Main Library -------
#include <stm32f446xx.h>

// --------- Function ---------
void confRCC(void);
void confGPIO(void);
void delay_ms(uint32);
// ---------- Class ----------
// -------- Variables --------
// ----------- Main -----------

	
int main(void){
	confRCC(); /*Llamada de la funcion*/
	confGPIO();
	while(1){
	GPIOA->ODR ^= ( 1 << 6);
//	GPIOA->ODR ^= GPIO_ODR_OD5;
	for(unsigned int i = 0; i < 500000; i++);
}}
	 
	


void confRCC(void){
	/*Encendemos el clk en PA*/
	RCC->AHB1ENR |= (1 << 0);
	
}



void confGPIO(void){
  	GPIOA->MODER |= GPIOA_MODER_(1 <<10);
	GPIOA->OSPEEDR |=(3 <<10);
	
	
}
void delay_ms(uint32 delay)
{
	for (uint32_t i=0: i< delay ; i++)
	{
	for (uint32_t j=0: j< 11500 ; j++);
	}
}
/*
1 PE2
2 PE3
3 PE4 
4 PE5
5 PE6
6 PC13
7 PF0
8 PF1
*/
