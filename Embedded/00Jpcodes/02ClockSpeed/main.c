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
	/*setClkHSE();*/
	setClkPLL();
	confRCC(); /*Llamada de la funcion*/
	confGPIO();
	while(1){	
		GPIOA->ODR ^=(1<<5);
		for(uint32_t i =0; i < 500000; i++);
	}
}
