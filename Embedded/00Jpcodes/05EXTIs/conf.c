#include <stm32f446xx.h>
#include "conf.h"
//implementacion de funciones

void confRCC(void){
    RCC->AHB1ENR |= (1<<0)|(1<<4); // GPIOA Y GPIOE
    RCC->APB2ENR |= (1<<14); // SYSCFG	

}
void confGPIO(void){
/*
A5 Out Push Pull
*/
    GPIOA->MODER |= (1<<10);
    GPIOA->OSPEEDR |= (3<<10);

    /*Se configura el PE0 como entrada y PULL UP Externo*/
    GPIOE->PUPDR |= (1<<0);
}


void confSYSCfG(void){
    SYSCFG->EXTICR[0] |= (4<<0);// EXTI0 PE0
    
}
void confEXTI(void){
    EXTI->IMR |= (1<<0); // Interrupcion en linea 0
    EXTI->FTSR |= (1<<0); // Flanco de bajada
}

void confNVIC(void){
    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_SetPriority(EXTI0_IRQn, 1);
    /*NVIC_SetPriorityGrouping()*/
}