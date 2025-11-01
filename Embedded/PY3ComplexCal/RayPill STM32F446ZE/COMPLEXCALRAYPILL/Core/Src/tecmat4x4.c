#include "tecmat4x4.h"
#define ROWS 4
#define COLS 4
char *keyHexa[ROWS][COLS]={
{"7","8","9","D"},
{"4","5","6","-"},
{"1","2","3","T"},
{"#","0",".","="},
};

uint8_t keyPolling[ROWS][COLS]={
	{0XEE,0XDE,0XBE,0X7E},
	{0XED,0XDD,0XBD,0X7D},
	{0XEB,0XDB,0XBB,0X7B},
	{0XE7,0XD7,0XB7,0X77},
};



uint8_t rowPins[ROWS] = {0XE,0XD,0XB,0X7};

char* gotKey(void){
	for(uint8_t i = 0; i<ROWS; i++){
		//limpia de lo que nos interesa
		/*0x272727
		B15 B14 B13 B12 | B11 B10 B9 B8 | B7 B6 B5 B4 | B3 B2 B1 B0
		 0   0   1   1  |  1  1  0  0 |  X  X  X  X | X  X  X  X 
		 0   0   0   0  |  0  0  1  1 |  1  1  0  0 | 0  0  0  0
		 */
		GPIOB->ODR = (GPIOB->ODR & (0xF0<<6)) | (rowPins[i]<<6);
		//LIMPIAMOS LAS COLUMNAS
		uint16_t key = GPIOB->IDR & (0xF0<<6);
		for(uint8_t j = 0; j<COLS; j++){
		if(key != (0xF0<<6)){
			key |= (GPIOB->ODR & (0x0F<<6));
			key=key>>6;
		}
		for(uint8_t j = 0; j<COLS; j++){
		if(key == keyPolling[i][j])
			return keyHexa[i][j];
		}
			}
	}
		return "ñ";
}

extern void confRCC(void){
	RCC->AHB1ENR |= (1<<1);
}
extern void confGPIO(void){
	/*PB[6-9] Scan
	PB[10-13] Read*/

	GPIOB->MODER |= (0X55 << 6*2);//SCAN
	//
	GPIOB->PUPDR |= (0X55<<10*2);//READ

}
