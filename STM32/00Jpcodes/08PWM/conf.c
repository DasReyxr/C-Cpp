#include <stm32f446xx.h>
#include "conf.h"

/*funciones imlementadas*/


void confRCC(void){
	RCC->AHB1ENR |= (1 << 0) | (1 << 4); // A  E 	
	RCC->APB1ENR |= (1<<2);//ACTIVAMOS CLK DEL TIM4
}

void confGPIO(void){
	
	GPIOE->MODER |= (0x5555 << 16); // PE8 -> PE15 Output 
	GPIOA->PUPDR |= (0xA << 10); //PA5 y PA6 como entrada PA5  + PA6 -
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
void confTIMER(void)
{
	//estos valores son para un periodo de 100ms
	TIM4->PSC = 0;
    TIM4->ARR = 0XFFFF; /* valor maximo de 2^16*/
    TIM4->CCMR1 |= (1<<0); /* Chanel 1 activated*/ 
	TIM4->CCER |= (1<<0) | (1<<3); /* Capture enabled */
    TIM4->SMCR |= (7<<0) | (5<<4); /* Trigger on TI1FP1, Edge rising, Filter = 0100 */


    TIM4->CR1 |=(0X81 <<0); //activamos la autorecarga en el buffer y el contador
	TIM4->DIER |= TIM_DIER_UIE; //interrupcion por desbordamiento

    TIM4->EGR |= TIM_EGR_UG; //actualizamos los registros
    TIM4->CR1 |= (1 << 0); //activamos el timer
}

void configNVIC(void){
	NVIC_EnableIRQ(TIM4_IRQn);
	NVIC_SetPriority(TIM4_IRQn, 1);

}