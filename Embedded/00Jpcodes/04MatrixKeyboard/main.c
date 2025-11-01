/*
------ Orlando Reyes ------
--------- Auf Das ---------
------- Matrix Keyb ---------
-------- 24/09/2025 --------
*/
// ------- Main Library -------
#include "tecmat4x4.h"
#include "conf.h"

const uint8_t sevenSeg[16]={
	0X40,0X79,0X24,0X30,0X19,0X12,0X02,0X78,
	0X00,0X18,0X08,0X03,0X46,0X21,0X06,0X0E
};

int main (void){
	confRCC();
	confGPIO();
	while(1){
	uint8_t keypress = gotKey();
		if(keypress != 0x88){
			if(keypress >= 0x30 && keypress <= 0x39){
			keypress-=0x30;
			GPIOF->ODR = keypress;
			}
			// Verificamos si se preciono el A-F
			else{
				keypress -= 0x37;
				GPIOA->ODR = sevenSeg[keypress] << 4; //~ sevenSeg[keypress] << 4
			}
		}
		else // Es el cuando no se preciono nada
			GPIOA-> ODR = (0x7F << 4);
	}
}