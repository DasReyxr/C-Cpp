#ifndef LCDI2C_H
#define LCDI2C_H
// 0x27 or 0x3F
#define ADRS_LCD 0x27
// Module Pins PCF8574
#define LCD_RS              (1<<0) 
#define LCD_RW              (1<<1) 
#define LCD_EN              (1<<2) 
#define LCD_BL              (1<<3)
// Data LCD
#define LCD_D4              (1<<4)
#define LCD_D5              (1<<5)
#define LCD_D6              (1<<6)
#define LCD_D7              (1<<7)
// LCD Commands
#define LCD_CLR             (1<<0)
#define LCD_RET             (1<<1)
#define LCD_ENTRY_MODE      (1<<2)
#define LCD_DISPLAY_ON      (1<<3)
#define LCD_FUNCTION_SET    (1<<5)
// Entry Mode config 
#define LCD_EM_LEFT         (1<<1)
#define LCD_EM_RIGHT        (0<<1)
// Display Control Config
#define LCD_DIS_ON          (1<<3)
#define LCD_DIS_OFF         (1<<3)
// Cursor ON




extern void confRCC(void);
extern void confGPIO(void);
extern void confI2C(void);
extern void config(void);
#endif