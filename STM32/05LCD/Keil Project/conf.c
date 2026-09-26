#include "conf.h"
/*
PINOUT 
F0-F3 DATA
C0 RS
C2 E

*/
//implementacion de funciones
/*
0x30 Function set 4 bit mode
0x2C Function set 4 bit mode, 2 line, 5x8 dots
0x2C Function set 4 bit mode, 2 line, 5x8 dots
0x0F Display on, cursor on, blinking on
0x01 Clear display
0x06 Entry mode set, increment cursor, no shift
*/

uint8_t LCD_CONFIG[11] = {0x03, 0x02, 0X0C,0X02,0X0C,0X00,0x0F,0x00,0X01,0X00,0x06};


void LCD_Enable(void){
    GPIOC->ODR ^= (1<<2); // enciende ineibol
    delay_ms(5);
    GPIOC->ODR ^= (1<<2); // apaga ineibol
}

void LCD_Clear(void){
    GPIOC->ODR &= (0<<0); // apaga RS
 
    GPIOF->ODR = (0x00);
    LCD_Enable();   
    GPIOF->ODR = (0x01);
    LCD_Enable();

    LCD_Return();
    GPIOC->ODR |= (1<<0); // enciende RS


}

void LCD_Return(void){
    GPIOC->ODR &= (0<<0); // apaga RS
 
    GPIOF->ODR = (0x00);
    LCD_Enable();   
    GPIOF->ODR = (0x02);
    LCD_Enable();
    
    GPIOC->ODR |= (1<<0); // enciende RS

}

void LCD_TEST(void){
    char tst[9] = "Hola juan";
    LCD_Init4B();
    LCD_WriteString(tst);
}

void LCD_Init4B(void){
    delay_ms(50);
    GPIOC->ODR &= (1<<0); // apaga RS
    for(uint8_t i=0; i<11; i++){
        GPIOF->ODR = LCD_CONFIG[i];
        LCD_Enable();
    }
    GPIOC->ODR = (1<<0); // enciende RS        
    
}

void LCD_WriteString(char* str){
     GPIOC->ODR = (1<<0); // enciende RS
    for(uint8_t i=0; i<strlen(str);i++)
    {
        /*Higher nibble*/
        GPIOF->ODR = (str[i] & 0xF0) >> 4;   // high nibble
        LCD_Enable();


        /*Lower nibble*/
        GPIOF->ODR = (str[i] & 0x0F);        // low nibble
        LCD_Enable();


    }
}

void LCD_ScrollLeft(uint8_t scrolls){
    GPIOC->ODR &= (0<<0); // apaga RS
    for(uint8_t i=0; i<scrolls;i++){
    GPIOF->ODR = (0x01);
    LCD_Enable();
    GPIOF->ODR = (0x08);
    LCD_Enable();
    }
    GPIOC->ODR |= (1<<0); // enciende RS

}


void LCD_ScrollRight(uint8_t scrolls){
    GPIOC->ODR &= (0<<0); // apaga RS
    for(uint8_t i=0; i<scrolls;i++){
    GPIOF->ODR = (0x01);
    LCD_Enable();
    GPIOF->ODR = (0x0C);
    LCD_Enable();
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
