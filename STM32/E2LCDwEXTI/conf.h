#ifndef CONF_H
#define CONF_H

#include <string.h>
#include <stm32f446xx.h>

extern void LCD_Init4B(void);
extern void LCD_TEST(void);
extern void LCD_Clear(void);
extern void LCD_Return(void);
extern void LCD_Enable(void);
extern void LCD_WriteINT(uint16_t);

extern void LCD_WriteString(char *);
extern void LCD_ScrollLeft(uint8_t);
extern void LCD_ScrollRight(uint8_t);


extern void delay_ms(uint32_t);
extern uint16_t contPulses(uint16_t);
extern void config(void);
extern void confRCC(void);
extern void confGPIO(void);
extern void confTIMER(void);
#endif