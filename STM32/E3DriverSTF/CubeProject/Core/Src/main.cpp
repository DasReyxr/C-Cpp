/*
------- Kevin Lara  -------
--------- Auf Das  ---------
----------- LCD  -----------
-------- 02/11/2025 --------
*/
// ------- Main Library -------
#include "TFTST7735.h"

// --------- Function ---------

// ---------- Class ----------
TFT_ST7735 Screen1;
// -------- Variables --------
// ----------- Main -----------

int main(void){
	confRCC(); 
	confGPIO();
    char str1[] = "Hola DAS";
	LCD_Init4B();
	LCD_WriteString(str1);
	while(1){
    }
}
	 
	

