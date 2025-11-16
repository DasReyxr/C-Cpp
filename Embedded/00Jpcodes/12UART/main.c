/*
--------- Auf Das  ---------
---------- UART  ----------
-------- 05/11/2025 --------

*/
// ------- Main Library -------
#include "conf.h"
#include "comusart.h"
#include <stm32f446xx.h>

#define CON 10
const uint8_t string[CON] = "Hola";
// --------- Function ---------
// ---------- Class ----------
// -------- Variables --------


// ----------- Main -----------

int main(void){
	config();	

	uint8_t auxChar;
	while(1){
		auxChar =USART_Receivechar();
		USART_Sendchar(auxChar);
	}
}
	 
	
