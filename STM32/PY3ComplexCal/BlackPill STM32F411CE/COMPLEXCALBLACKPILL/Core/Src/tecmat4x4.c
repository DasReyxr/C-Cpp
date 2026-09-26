#include "tecmat4x4.h"
#define ROWS 4
#define COLS 4
uint8_t keyHexa[ROWS][COLS]={
{'0','1','2','3'},
{'4','5','5','7'},
{'8','9','A','B'},
{'C','D','E','F'},
};

uint8_t keyPolling[ROWS][COLS]={
	{0XEE,0XDE,0XBE,0X7E},
	{0XED,0XDD,0XBD,0X7D},
	{0XEB,0XDB,0XBB,0X7B},
	{0XE7,0XD7,0XB7,0X77},
};



uint8_t rowPins[ROWS] = {0XE,0XD,0XB,0X7};

uint32_t gotKey(void){
	for(uint8_t i = 0; i<ROWS; i++){
		//limpia de lo que nos interesa
		GPIOD->ODR = (GPIOD->ODR & 0XF0) | rowPins[i];
		//LIMPIAMOS LAS COLUMNAS
		uint8_t key = GPIOD->IDR & 0XF0;
		for(uint8_t j = 0; j<COLS; j++){
		if(key != 0xF0){
			key |= (GPIOD->ODR & 0X0F);
		}
		for(uint8_t j = 0; j<COLS; j++){
		if(key == keyPolling[i][j])
			return keyHexa[i][j];
		}
			}
	}
		return 0x88;
}
