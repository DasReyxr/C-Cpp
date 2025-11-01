/*
------ Orlando Reyes ------
--------- Auf Das ---------
----- Externat Interrupts -----
-------- 01/10/2025 --------
*/
// ------- Main Library -------
#include <stm32f4xx.h>
#include "conf.h"

const uint8_t sevenSeg[16]={
	0X40,0X79,0X24,0X30,0X19,0X12,0X02,0X78,
	0X00,0X18,0X08,0X03,0X46,0X21,0X06,0X0E
};

int main (void){
	confRCC();
	confGPIO();
	while(1){

	}
}

void EXTI0_IRQHandler(void){
    if(EXTI->PR & (1<<0)){ // Verificamos que la interrupcion provenga de la linea 0
        GPIOE->ODR ^= (1<<1); // Toggle del pin E0
        EXTI->PR |= (1<<0); // Limpiamos la bandera de la interrupcion
    }
}


/*
void EXTI15_10_IRQ_Handler(void){
    if(EXTI->PR & (1<<13)){
        GPIOA->ODR ^= (1<<5);
        EXTI->PR  = EXTI_PR_PR13;
    }
}
    */