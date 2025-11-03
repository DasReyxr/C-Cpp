/*
------- Kevin Lara  -------
--------- Auf Das  ---------
----------- LCD  -----------
-------- 02/11/2025 --------
*/
// ------- Main Library -------
#include "conf.h"
// --------- Function ---------

// ---------- Class ----------
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
	 
	

