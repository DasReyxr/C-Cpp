#include <stm32f4xx.h>
#include "conf.h"
//implementacion de funciones

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
