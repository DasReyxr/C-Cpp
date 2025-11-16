1
#include <stm32f446xx.h>
#include "conf.h"
/*
PINOUT
PA2 USART TX
PA3 USART RX
*/


void confRCC(void){
    RCC->AHB1ENR |= (1<<21) |(1 << 1); // I2C B   


}

void confGPIO(void){


    /* PA[7-5] as AF*/	
    //                   SCL | SDA
    GPIOB->MODER |= (2<<2*6)|(2<<2*7);
    GPIOB->AFR[0]|= (4<<4*6)|(4<<4*7); 
}

void confI2C(void){
    /*
        8 bits
        no parity
        1 stop bit
        baudrate 9600
    */
    
    I2C1->CR2 = 16; // 16MHz
    I2C1->CCR = 80; // 16M/2*100kHz 
    I2C1->TRISE = 17; // 1us*16M 1000ns/62.5ns + 1
    I2C1->CR1 = (1<<0); // PE
}


void config(void){
    confRCC();
    confGPIO();
    confI2C();
}

