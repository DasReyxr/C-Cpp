/*
------ Orlando Reyes ------
--------- Auf Das ---------
---------- Config -----------
-------- 25/08/2025 --------
*/
// ------- Main Library -------

#include "conf.h"

// --------- Function ---------

void confRCC(void){
	/*Encendemos el clk en PA*/
	RCC->AHB1ENR |= (1 << 0);
}

void confGPIO(void){
  GPIOA->MODER |= (0x5555  << 0); /* (15 << 0) */
	GPIOA->PUPDR |= (0xA0000 <<0);
}

void setClkHSE(void){
	/*Activamos el reloj HSE y esperamos que este listo*/
	RCC->CR |= (1 << 16);
	while(!(RCC->CR & RCC_CR_HSERDY));
	
	/*Las velocidades de, AHB, APB1 y APB2 se deben de modificar 
	si es que cambio a la frecuencia de trabajomas alta*/
	RCC->CFGR |= (1 << 0); /*RCC_CFGR_P*/
	
	/*Activamos el HSE como reloj principal y esperamos que este listo*/
	while(!(RCC->CFGR & (1 << 2)));
	SystemCoreClockUpdate();
}

void setClkPLL(void){
  /*Activamos el reloj HSE y esperamos que este listo*/
	RCC->CR |= (1 << 16);
	while(!(RCC->CR & RCC_CR_HSERDY));
	
	/*Activamos el prefetch del FLASH (latencia entre lectura
	de la CPU y la memoria) y cmabiamos a 2 wait states */
	
	FLASH-> ACR |= (1 << 8);
	FLASH-> ACR |= (2 << 0);
	
	RCC->CR |= (1 << 24);
	while(!(RCC->CR & RCC_CR_PLLRDY));
	
	/*Cambiamos la velocidad del APB1 ya que no puede trabajar 
	a mas de  45 MHz*/
	RCC->CFGR |= (4<<10);
	
	RCC->PLLCFGR = (360 << RCC_PLLCFGR_PLLN_Pos) |
								 (8 << RCC_PLLCFGR_PLLM_Pos)   |
								 (4 << RCC_PLLCFGR_PLLP_Pos)   |
								 (1 << RCC_PLLCFGR_PLLSRC_Pos);
	
	/*Activamos el PLL como reloj principal y esperamos que este listo*/
	RCC->CFGR |= (2 << 0);
	while(!(RCC->CFGR & (2 << 2)));
	SystemCoreClockUpdate();
}