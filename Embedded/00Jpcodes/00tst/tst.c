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