#include <stm32f446xx.h>
#include "conf.h"

void confRCC(void){
	RCC->AHB1ENR |= (1 << 0); // A  E 	
}

void confGPIO(void){
	
	GPIOA->MODER |= (5 << 10); // PA5 Y PA6 Output 
	GPIOA->OSPEEDR |= (3 << 10);
}

void setClkPLL(void)
{
	RCC->CR |=(1 << 16);
	while(!(RCC->CR & RCC_CR_HSERDY));
	/*Acivamos el prefetch del FLASH y cambiamos la latencia entre lectura de la CPU y la memoria a 2 waitstates*/
	FLASH->ACR |= (1<<8) ;
	FLASH->ACR |= (5<<0);
	/*Cambiamos la velicidad del apb1 ya que no puede trabajar a mas de 45MHZ y la de apb2 que no trabaja a mas 90*/
	RCC->CFGR |= (5<<10);
	RCC->CFGR |= (4<<13);
	RCC->PLLCFGR |=(1 << RCC_PLLCFGR_PLLSRC_Pos);
	RCC->PLLCFGR |= (360 << RCC_PLLCFGR_PLLN_Pos) | 
									(8 << RCC_PLLCFGR_PLLM_Pos) | 
									(0 << RCC_PLLCFGR_PLLP_Pos) ;
	/*LAS VELOCIDADES DEL AHB, EL APB1,APB2 DEBEN MODIFICARSE SI CAMBIO LA FRECUENCIA A LA MAS ALTA*/
	RCC->CR |=(1 << 24);
	RCC->CFGR |= (2 << 0);
	SystemCoreClockUpdate();
}

