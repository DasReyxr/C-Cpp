#include "lcdi2c.h"
#include "i2c.h"
/*funciones propias o internas*/

static void LCD_SendCommand(uint8_t);
static void LCD_Write4Bits(uint8_t);
static void LCD_PulseEnable(uint8_t);

/*FUnciones propias*/

static void LCD_SendCommand(uint8_t data){
    uint8_t dataH=0x0F & data;
    uint8_t dataL=(data <<4) & 0XF0;
    LCD_Write4Bits(dataH|LCD_BACKLIGHT);
    LCD_Write4Bits(dataL|LCD_BACKLIGHT);
}
static void LCD_Write4Bits(uint8_t data){
    I2C_Write(ADDRS_LCD_I2C,data);
    LCD_PulseEnable(data);

}
static void LCD_PulseEnable(uint8_t data){
    I2C_Write(ADDRS_LCD_I2C,data|ENABLE_BIT);
    delay_ms(1);
    I2C_Write(ADDRS_LCD_I2C,data&~ENABLE_BIT);
}

void delay_ms(volatile uint32_t ms){
    for(volatile uint8_t i =0; 1<=ms;i++)
        for(volatile uint8_t j =0; 1<=ms;i++);
}

void LCD_Init(void){
    I2C_Write(ADDRS_LCD_I2C,LCD_BACKLIGHT);
    delay_ms(50);
    LCD_SendCommand(INTERFACE_8B);
    delay_ms(5);
    LCD_SendCommand(INTERFACE_8B);
    delay_ms(1);
    LCD_SendCommand(INTERFACE_8B);
    LCD_SendCommand(INTERFACE_4B);
    delay_ms(1);
    LCD_SendCommand(FUN_SET_4B);
    LCD_SendCommand(DISPLAY_OFF);
    LCD_SendCommand(CLEAR_DISPLAY);
    delay_ms(2);
    LCD_SendCommand(ENTRY_MODE);
    LCD_SendCommand(COMBINADO_FUNSET);

}

void LCD_Clear(void){
    LCD_SendCommand(CLEAR_DISPLAY);
        delay_ms(2);
}

void LCD_ReturnHome(void){
    LCD_SendCommand(RET_HOME);
        delay_ms(2);
}


void LCD_SendChar(char c){
     uint8_t dataH=0x0F & c;
    uint8_t dataL=(c <<4) & 0XF0;
    LCD_Write4Bits(dataH|REGISTER_SELECT|LCD_BACKLIGHT);
    LCD_Write4Bits(dataL|REGISTER_SELECT|LCD_BACKLIGHT);
}

void LCD_SendString(const char *str){
    while(*str){
        LCD_SendChar(*str++);
    }
    
}