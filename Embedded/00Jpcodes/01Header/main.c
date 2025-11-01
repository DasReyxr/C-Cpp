/*
------ Orlando Reyes ------
--------- Auf Das ---------
----------- Heather -----------
-------- 25/08/2025 --------
*/
// ------- Main Library -------
#include "conf.h"

// ---------- Class ----------
// -------- Variables --------
// ----------- Main -----------

int main(void){
	setClkHSE();
	confRCC(); /*Llamada de la funcion*/
	confGPIO();
	while(1){
	GPIOA->ODR ^= ( 1 << 6);
//	GPIOA->ODR ^= GPIO_ODR_OD5;
	for(unsigned int i = 0; i < 500000; i++);
}}
