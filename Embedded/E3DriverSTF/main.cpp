/*
------- Kevin Lara  -------
--------- Auf Das  ---------
----------- TFT  -----------
-------- 02/11/2025 --------
*/
// ------- Main Library -------
#include "TFT_ST7735.h"
#include "conf.h"
// --------- Function ---------

// ---------- Class ----------
TFT_ST7735 Screen1;
// -------- Variables --------
// ----------- Main -----------

int main(void){
	config();
	Screen1.INIT_FN();
    Screen1.DrawPixel(10, 10, 0xF800);  // Red pixel at (10,10)

	while(1){

		
	}
}
