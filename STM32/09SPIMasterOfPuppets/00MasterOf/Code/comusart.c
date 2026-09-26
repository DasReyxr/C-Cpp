/*
PA2 TX
PA3 RX
*/

#include <stm32f446xx.h>
#include "comusart.h"


void USART_Sendchar(uint8_t ch){
    /* Wait until buffer is empty */
    while(!(USART2->SR & USART_SR_TXE));
    USART2->DR = ch; /* Esperamos a que se haya hecho una transmision completa*/
    while(!(USART2->SR & USART_SR_TC));
}
uint8_t USART_Receivechar(void){
   /* Wait until data is available */
    while(!(USART2->SR & USART_SR_RXNE));
    return (uint8_t)USART2->DR;

}
void USART_SendString(char* str){
    while(*str){
        USART_Sendchar(*str++);
    }
}
