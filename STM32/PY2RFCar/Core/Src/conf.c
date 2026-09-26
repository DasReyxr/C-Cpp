#include "conf.h"
/*
PINOUT
PA0 PWM2Ch1
PA1 PWM2Ch2

M1 Left
M2 Right

PA3 M1 Front
PA4 M1 Back

PA5 M2 Front
PA6 M2 Back

PB4 PWM SERVOMOTOR

*/
#define LeftFront 3
#define LeftBack 4
#define RightFront 5
#define RightBack 6
#define PI	3.14159265358979

/*--- Clase Carro ----*/
void CAR_Speed(uint16_t speed){
    if(speed>100)speed=100;
    TIM2->CCR1= (65535*speed)/100; //DUTYCYCLE 50% CHANEL1
    TIM2->CCR2= (65535*speed)/100; //DUTYCYCLE 50% CHANEL2
}

void CAR_Front(void){
    GPIOA->ODR &=(0<<RightBack)|(0<<LeftBack);
    GPIOA->ODR |=(1<<RightFront)|(1<<LeftFront);
}
void CAR_Back(void){
    GPIOA->ODR &=(0<<RightFront)|(0<<LeftFront);
    GPIOA->ODR |=(1<<RightBack)|(1<<LeftBack);
}

void CAR_Direction(float angle){
    uint8_t mangol =200 + (uint8_t)(80*angle+40*PI)/PI;
    TIM3->CCR1= mangol; 
}

/*----- Configuration -----*/
void confRCC(void){
    RCC->AHB1ENR |= (1<<0) |(1<<1); // GPIOA GPIOB
    RCC->APB1ENR |= (1<<0); //TIM2
    RCC->APB1ENR |= (1<<1); //TIM3
}
void confGPIO(void){
    GPIOA->MODER |=(10<<0);
                  /* CH1      CH2*/
    GPIOA->AFR[0] |=(1<<0) |(1<<4);

    //PB4 AF2 TIM3 CH1
    GPIOB->MODER |=(3<<8);
    GPIOB->AFR[0] |=(2<<4*4); 
}

void confTIMER(void)
{
    TIM2->CR1 &=(0<<0);
    TIM2->PSC = 1;
                /* CH1      CH2*/
    TIM2->CCMR1 |=(6<<4)|(6<<12); // Enable PWM
    //TIM2->CCMR1 |=(1<<3)|(1<<11); // Preload
    TIM2->CCER  |=(1<<0) |(1<<4);

    TIM2->ARR  =65535; /*8.2 mS*/

    TIM2->CCR1= 32768;//DUTYCYCLE 50% CHANEL1
    TIM2->CCR2 =32768;//pwm duty cycle 50% CHANEL 2


	/*CH1    CH2*/
    TIM3->CR1 &=(0<<0);
    
    TIM3->PSC = 99;
                /* CH1*/
    TIM3->CCMR1 |=(6<<4); // Enable PWM
    TIM3->CCER  |=(1<<0);
    /*
    1.25 - 1.75 ms
    Servo
    2 ms 90
    1 ms -90

    20 ms  50hz PERIOD
    */ 
    TIM3->ARR  =3200; /*16k/50*/
    
    TIM3->CCR1= 240;//3200*1.5/20 => 240  7.5% 0° 
    
    /*
    Valor minimo 200 -45
    Valor maximo 280 +45
    */
    
    }


void delay_ms(uint32_t delay){
	for(uint32_t i=0;i<delay;i++){
	for(uint32_t j=0;j<11500;j++);

	}

}


void config(void){
    confRCC();
    confGPIO();
    confTIMER();
}
