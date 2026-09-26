#include "conf.h"
/*
PINOUT 
F0-F3 DATA
C0 RS
C2 E
B6 Input Capture

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
    char tst[] = "Hola juan";
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


/* 
    n/100
    n/10 - 10*val100
    n-100*val100-10*val10
*/
void LCD_WriteINT(uint16_t int_val){
    char val100 =  (int_val/100);
    char val10 = (int_val/10 - val100*10);
    char val1 = (int_val - val100*100 - val10*10);
    
    val100  +=0x30;
    val10  +=0x30;
    val1 +=0x30;
    char stra[] = {val100, val10, val1,'\0'};
    LCD_WriteString(stra);
}


void confRCC(void){
    RCC->AHB1ENR |= (1<<5)|(1<<2)|(1<<1);; // GPIOA Y GPIOE Y GPIOB
    RCC->APB1ENR |= (1<<2)|(1<<1); //TIM4 Y TIM3
}
void confGPIO(void){
/*
B5 TIM3 CH2
B6 AF2 Input Capture

C0 RS Out Push Pull
C2 E  Out Push Pull
F0-F3 Data Out Push Pull
*/
    GPIOF->MODER |= (0X55<<0);
    GPIOF->OSPEEDR |= (0XFF<<0);

    /*Se configura el PE0 como entrada y PULL UP Externo*/
    GPIOC->MODER |= (0X11<<0);
    
    GPIOA->MODER |= ( 1<< 10); // PA5 Output 

    GPIOB->MODER |= ( 2<< 12); // PB6 INPUT
	GPIOB->PUPDR |= ( 2<< 12); //PULLDOWN EN PB6
	GPIOB->AFR[0] |=(2<<24);//CARGAMOS LA FUCNION ESPECIAL DEL TIM4

	GPIOB->AFR[0] |=(2<<20);//CARGAMOS LA FUCNION ESPECIAL DEL TIM3 

}

void confTIMER(void)
{
    TIM3->CR1 |= (1<<0); 
	TIM3->ARR = 15999;
	TIM3->PSC = 999;

    //estos valores son para un periodo de 100ms
	TIM4->ARR = 0XFFFF;
	TIM4->PSC =1;
	TIM4->CCMR1 |=(1<<0);//HABILITAMOS EL CANAL 1 EN MODO INPUTCAPTURE Y LO RELACIONAMOS TI1
	TIM4->CCMR1 |=(3<<4);//ACTIVAMOS FILTRO PARA EL INPUTCAPTURE N=8
	//TIM4->CCER&=~((1<<1)|(1<<3));
	TIM4->CR1 |=(0X81 <<0); //activamos la autorecarga en el buffer y el contador
	//TIM4->DIER |= TIM_DIER_UIE;
	TIM4->CCER |= (1<<0);
	TIM4->SMCR |= (7<<0)|(5<<4);
	TIM4->EGR |= (1<<0);

    

}


void delay_ms(uint32_t delay){
	for(uint32_t i=0;i<delay;i++){
	for(uint32_t j=0;j<11500;j++);

	}

}

uint16_t contPulses(uint16_t tempCount){
    uint16_t curCount = TIM4->CNT;
    if (curCount != tempCount ){
        tempCount =curCount;
    }
    return tempCount;
}



void config(void){
    confRCC();
    confGPIO();
    confTIMER();
    

}
