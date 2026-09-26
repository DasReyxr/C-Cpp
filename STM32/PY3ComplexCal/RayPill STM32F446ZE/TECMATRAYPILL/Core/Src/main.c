#include <stm32f4xx.h>
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
	/*		if(keypress >= 0x30 && keypress <= 0x39){//VERIFICAMOS SI SE PRESIONO UN DIGITO DEL 0 AL 9
			uint16_t Val = keypress-0x30;
			}
			else{ 
			switch(keypress){
				case '#':
					arrowmode ^=1;
				break;
				case '=':
					level++;
					if(level > 1){
						level = 0;
					}
					break;
				break;
			}
			if(level == 0){
				size = Val;
			}
			else if(level == 1){
				aqi vamos a hacer como un wail
			}
			}
	*/
}}
