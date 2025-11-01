#include <stm32f446xx.h>
#include "conf.h"
//implementacion de funciones

extern void confRCC(void){
RCC->AHB1ENR |= (1<<3)|(1<<7)|(1<<0);	
	
}
extern void confGPIO(void){
//condiguramos del D0-D3 DEL PD COMO SALIDAS Y 7-4 COMO ENTRADAS
	GPIOA->MODER |= (0X55 << 0);
	//
	GPIOA->OSPEEDR |= (0XFF<<0);
	//
	GPIOA->PUPDR |= (0X55<<8);
	//HAY QUE CONFIGURAR SALIDAS PARA 7SEGMENTOS
	
	GPIOA->MODER |= (0X5555 << 0);
}
	