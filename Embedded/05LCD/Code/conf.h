#ifndef CONF
#define CONF

#include <string.h>
#include <stm32f446xx.h>

extern void LCD_Init4B(void);
extern void LCD_WriteString(char*);
extern void LCD_ScrollLeft(uint8_t);
extern void LCD_ScrollRight(uint8_t);
extern void LCD_TEST(void);

extern void delay_ms(uint32_t);

extern void confRCC(void);
extern void confGPIO(void);
#endif