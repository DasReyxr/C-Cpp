/*
------- Kevin Lara  -------
--------- Auf Das  ---------
----------- LCD  -----------
-------- 02/10/2025 --------
*/
// ------- Main Library -------
#include "conf.h"

// --------- Function ---------
void confRCC(void);
void confGPIO(void);
void delay_ms(uint32_t delay);
// ---------- Class ----------
// -------- Variables --------
// ----------- Main -----------

int main(void){
	confRCC(); 
	confGPIO();
    char str1[] = "HOLA DAS";
	LCD_Init4B();
	LCD_WriteString(str1);
	delay_ms(50);
	//LCD_Return();

	while(1){
		LCD_ScrollRight(15);
		delay_ms(50);
		LCD_ScrollLeft(15);
		delay_ms(50);
	}
}
	 
	

