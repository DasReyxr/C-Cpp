#include <stm32f4xx.h>
#include "conf.h"
//implementacion de funciones


extern void confGPIO(void){
/*
PB[6-9] Scan
PB[12-15] Read
*/
	GPIOB->MODER |= (0X55 << 0);
	//
	GPIOA->OSPEEDR |= (0XFF<<0);
	//
	GPIOA->PUPDR |= (0X55<<8);
	//HAY QUE CONFIGURAR SALIDAS PARA 7SEGMENTOS

	GPIOB->MODER |= (0X5555 << 0);
}

