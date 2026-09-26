#include "conf.h"
/*
PINOUT 
F0-F3 DATA
C0 RS
C2 E

*/
//implementacion de funciones

uint8_t LCD_CONFIG[12] = {0x03, 0x03, 0x03, 0x02, 0X02,0X08,0X00,0x0C,0x00,0X01,0X00,0x06};
/*0x00,0xC0,0x00,0x10,0x00,0x60
*/



void LCD_TEST(void){
    char tst[9] = "Hola juan";
    LCD_Init4B();
    LCD_WriteString(tst);
}

void LCD_Init4B(void){
    delay_ms(15);
    GPIOC->ODR &= (1<<0); // enciende RS
    for(uint8_t i=0; i<11; i++){
        GPIOF->ODR = LCD_CONFIG[i];
        GPIOC->ODR ^= (1<<2); // enciende ineibol
        delay_ms(5);
        GPIOC->ODR ^= (1<<2); // apaga ineibol
    }
    GPIOC->ODR |= (1<<0); // enciende RS        
    
}

void LCD_WriteString(char* str){

    for(uint8_t i=0; i<strlen(str);i++)
    {
        /*Higher nibble*/
        GPIOF->ODR = (str[i] & 0xF0) >> 4;   // high nibble
        GPIOC->ODR ^= (1<<2); // enciende ineibol
        delay_ms(5);
        GPIOC->ODR ^= (1<<2); // apaga ineibol

        /*Lower nibble*/
        GPIOF->ODR = (str[i] & 0x0F);        // low nibble
        GPIOC->ODR ^= (1<<2); // enciende ineibol
        delay_ms(5);
        GPIOC->ODR ^= (1<<2); // apaga ineibol

    }
}

void LCD_ScrollLeft(uint8_t scrolls){
    GPIOC->ODR &= (1<<0); // enciende RS
    for(uint8_t i=0; i<scrolls;i++){
    GPIOF->ODR |= (0x01);
    GPIOC->ODR ^= (1<<2); // enciende ineibol
    delay_ms(5);
    GPIOC->ODR ^= (1<<2); // apaga ineibol
    GPIOF->ODR |= (0x08);
    GPIOC->ODR ^= (1<<2); // enciende ineibol
    delay_ms(5);
    GPIOC->ODR ^= (1<<2); // apaga ineibol
    }
    GPIOC->ODR |= (1<<0); // enciende RS

}


void LCD_ScrollRight(uint8_t scrolls){
    GPIOC->ODR &= (1<<0); // enciende RS
    for(uint8_t i=0; i<scrolls;i++){
    GPIOF->ODR |= (0x01);
    GPIOC->ODR ^= (1<<2); // enciende ineibol
    delay_ms(5);
    GPIOC->ODR ^= (1<<2); // apaga ineibol
    GPIOF->ODR |= (0x0C);
    GPIOC->ODR ^= (1<<2); // enciende ineibol
    delay_ms(5);
    GPIOC->ODR ^= (1<<2); // apaga ineibol    
    }
    GPIOC->ODR |= (1<<0); // enciende RS

}

void confRCC(void){
    RCC->AHB1ENR |= (1<<5)|(1<<2); // GPIOA Y GPIOE

}
void confGPIO(void){
/*
A5 Out Push Pull
*/
    GPIOF->MODER |= (0X55<<0);
    GPIOF->OSPEEDR |= (0XFF<<0);

    /*Se configura el PE0 como entrada y PULL UP Externo*/
    GPIOC->MODER |= (0X11<<0);
}




void delay_ms(uint32_t delay){
	for(uint32_t i=0;i<delay;i++){
	for(uint32_t j=0;j<11500;j++);

	}

}
