#ifndef LCDI2C_H
#define LCDI2C_H
#include <stm32f446xx.h>
//ALL ADDRESS
//DIRECCION DEL PCF8574
#define ADDRS_LCD_I2C 0x27
/*BITS DEL PCF8574 PARA EL LCD */
#define LCD_BACKLIGHT 0x08 //P3BIT
#define ENABLE_BIT 0x04//P2BIT
#define READ_WRITE_BIT 0x02//P1
#define REGISTER_SELECT 0X01//P0
/*COMANDOS PARA LA LCD*/
#define INTERFACE_8B 0x30
#define INTERFACE_4B 0X20
#define FUN_SET_4B 0x28
#define DISPLAY_OFF 0x08
#define CLEAR_DISPLAY 0X01
#define RET_HOME 0x02
#define ENTRY_MODE 0x06
#define COMBINADO_FUNSET 0x0C

/*FUNCTIONS*/
//init
extern void LCD_Init(void);
extern void LCD_Clear(void);
extern void LCD_ReturnHome(void);
/*Funciones para escritura*/
extern void LCD_SendChar(char);
extern void LCD_SendString(const char *str);
/*delay*/
extern void delay_ms(char);
#endif /* INC_LCDI2C_H_ */