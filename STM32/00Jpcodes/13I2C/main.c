/*
--------- Auf Das  ---------
---------- UART  ----------
-------- 05/11/2025 --------

*/
// ------- Main Library -------
#include "conf.h"
#include <stm32f446xx.h>
#include "lcdi2c.h"

// --------- Function ---------
// ---------- Class ----------
// -------- Variables --------


// ----------- Main -----------



int main(void){
	config();
	LCD_Init();
	LCD_SendString("Hola");
	delay_ms(1000);
	LCD_ReturnHome();
	LCD_SendString("Ya C I2C");
	while (1)
	{	
	}
	
}
