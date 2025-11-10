#ifndef COMUSART_H
#define COMUSART_H

#include <stm32f446xx.h>
//typedef unsigned char uint8_t;

void USART_Sendchar(uint8_t);
uint8_t USART_Receivechar(void);
void USART_SendString(char*);
#endif