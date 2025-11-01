/*
 * A3 CS
 * A4 DC
 * A5 SCK
 * A6 RES
 * A7 MOSI
 * */
#include "conf.h"
#include "stm32f4xx_hal.h"
#include "tecmat4x4.h"

/* USER CODE BEGIN Includes */
/* vim: set ai et ts=4 sw=4: */
#include <string.h>
#include "st7735.h"
#include "fonts.h"
//#include "testimg.h"



/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/


void init() {
    ST7735_Init();

    //const char ready[] = "Ready!\r\n";
    //HAL_UART_Transmit(&huart2, (uint8_t*)ready, sizeof(ready)-1, HAL_MAX_DELAY);
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_SPI1_Init();
  confRCC();
  confGPIO();
  init();
  ST7735_FillScreen(ST7735_BLACK);

  char *keypress = NULL;
  uint8_t level = 0 ;
  while (1){
  keypress=gotKey();

  /*Pantallas
  0 -> Ingreso tamano sistema
  1 -> Ingreso coeficientes
  2 -> Resultados
  */
  switch (level){
    case 0:
      ST7735_WriteString(0, 0, "INGRESA EL TAMANO DEL SISTEMA:", Font_7x10, ST7735_WHITE, ST7735_BLACK);
      break;
    case 1:
      ST7735_WriteString(0, 0, "qieresemenia:", Font_7x10, ST7735_WHITE, ST7735_BLACK);
      break;  
    case 2:
      ST7735_WriteString(0, 0, "yawe:", Font_7x10, ST7735_WHITE, ST7735_BLACK);
      break;  

  }

  if((*keypress!= 'ñ') && (*keypress=='=')){
      if(level<3){
        level++;
        ST7735_FillScreen(ST7735_BLACK);
      }
      else if(level==2)
        level=2;
  }
}
}
