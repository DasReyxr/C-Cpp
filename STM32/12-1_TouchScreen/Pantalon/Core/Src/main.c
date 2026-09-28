/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ILI9341_Driver.h"
#include "Touch.h"
#include "display.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void delay_ms(volatile uint32_t ms){
	while(ms--){
		for(volatile uint32_t i =0; i<6000;i++){
		}}
}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi3;

/* USER CODE BEGIN PV */
uint8_t state = 0;
uint16_t Xp;
uint16_t Yp;
char touch_text[24];
volatile uint32_t startup_stage;
 uint16_t paint_color = WHITE;
 uint16_t brush_size = 15;
 
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
 uint16_t rec_espacio = 5;
 uint16_t recArea = 30; 
 

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  startup_stage = 1;
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  startup_stage = 2;
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  startup_stage = 3;
  MX_GPIO_Init();
  startup_stage = 4;
  MX_SPI1_Init();
  startup_stage = 5;
  MX_SPI3_Init();
  /* USER CODE BEGIN 2 */
  startup_stage = 6;
  LCD_ILI9341_Init();
  TP_Init();
  startup_stage = 7;
  LCD_ILI9341_Rotate(0);
  HAL_Delay(500);
  startup_stage = 8;
  LCD_ILI9341_Fill(WHITE);
  startup_stage = 9;

  uint16_t BLACK_MARGIN_X_L    = 0;                        uint16_t  BLACK_MARGIN_X_H   = recArea;
  uint16_t RED_MARGIN_X_L      = (recArea+rec_espacio)   ; uint16_t RED_MARGIN_X_H      = (recArea)*2+rec_espacio;
  uint16_t BLUE_MARGIN_X_L     = (recArea+rec_espacio)*2 ; uint16_t BLUE_MARGIN_X_H     = (recArea)*3+rec_espacio*2;
  uint16_t GREEN_MARGIN_X_L    = (recArea+rec_espacio)*3 ; uint16_t GREEN_MARGIN_X_H    = (recArea)*4+rec_espacio*3;
  uint16_t PURPLE_MARGIN_X_L   = (recArea+rec_espacio)*4 ; uint16_t PURPLE_MARGIN_X_H   = (recArea)*5+rec_espacio*4;
  uint16_t MAROON_MARGIN_X_L   = (recArea+rec_espacio)*5 ; uint16_t MAROON_MARGIN_X_H   = (recArea)*6+rec_espacio*5;
  uint16_t ERASE_MARGIN_X_L    = (recArea+rec_espacio)*6 ; uint16_t ERASE_MARGIN_X_H    = (recArea)*7+rec_espacio*6;
 
  uint16_t ERASE2_MARGIN_X_L   = (recArea+rec_espacio)*7 ; uint16_t ERASE2_MARGIN_X_H   = (recArea)*8+rec_espacio*7;
 
  //                              0  0   30           30   
  LCD_ILI9341_DrawFilledRectangle(BLACK_MARGIN_X_L, 0, BLACK_MARGIN_X_H,(recArea), BLACK);
  
  //                                 35                 0     65                    30
  LCD_ILI9341_DrawFilledRectangle(RED_MARGIN_X_L  , 0, RED_MARGIN_X_H ,(recArea), RED);
  //                                    70                 0     100                    30        
  LCD_ILI9341_DrawFilledRectangle(BLUE_MARGIN_X_L, 0, BLUE_MARGIN_X_H,(recArea), BLUE);
  
  LCD_ILI9341_DrawFilledRectangle(GREEN_MARGIN_X_L, 0, GREEN_MARGIN_X_H,(recArea), GREEN);

  LCD_ILI9341_DrawFilledRectangle(PURPLE_MARGIN_X_L, 0, PURPLE_MARGIN_X_H,(recArea), PURPLE);

  LCD_ILI9341_DrawFilledRectangle(MAROON_MARGIN_X_L, 0, MAROON_MARGIN_X_H,(recArea), MAROON);
  LCD_ILI9341_DrawFilledRectangle(ERASE_MARGIN_X_L, 0, ERASE_MARGIN_X_H,(recArea)/2, RED);
  LCD_ILI9341_DrawFilledRectangle(ERASE_MARGIN_X_L, recArea/2, ERASE_MARGIN_X_H,(recArea),BLUE);
  
  LCD_ILI9341_DrawFilledRectangle(ERASE2_MARGIN_X_L, 0, ERASE2_MARGIN_X_H,(recArea)/2, BLUE);
  LCD_ILI9341_DrawFilledRectangle(ERASE2_MARGIN_X_L, recArea/2, ERASE2_MARGIN_X_H,(recArea),RED);

  

    // LCD_ILI9341_Puts(28, 64, "IE UAA", 2, BLACK, WHITE);

   
    // LCD_ILI9341_DrawCircle(Xp, Yp, 5, RED, 0);
    // LCD_ILI9341_Puts(180, 160, "PAINT", 2, GREEN, WHITE);

  // LCD_ILI9341_DrawFilledRectangle(0, 0, 120, 18, WHITE);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    
     if(TP_GetState())
     {
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET); //encender LED
    Yp=240-TP_Read_X(); //solo TP_Read_X() para invertir X
    Xp=TP_Read_Y(); //solo TP_Read_Y() para invertir Y
  
    if (Yp < recArea) {
      if (Xp >= BLACK_MARGIN_X_L && Xp <= BLACK_MARGIN_X_H) {
        paint_color = BLACK;
      } else if (Xp >= RED_MARGIN_X_L && Xp <= RED_MARGIN_X_H) {
        paint_color = RED;
      } else if (Xp >= BLUE_MARGIN_X_L && Xp <= BLUE_MARGIN_X_H) {
        paint_color = BLUE;
      } else if (Xp >= GREEN_MARGIN_X_L && Xp <= GREEN_MARGIN_X_H) {
        paint_color = GREEN;
      } else if (Xp >= PURPLE_MARGIN_X_L && Xp <= PURPLE_MARGIN_X_H) {
        paint_color = PURPLE;
      } else if (Xp >= MAROON_MARGIN_X_L && Xp <= MAROON_MARGIN_X_H) {
        paint_color = MAROON;
      }
        else if (Xp >= ERASE_MARGIN_X_L && Xp <= ERASE_MARGIN_X_H) {
          paint_color = WHITE;
        }
        else if (Xp >= ERASE2_MARGIN_X_L && Xp <= ERASE2_MARGIN_X_H) {
          LCD_ILI9341_DrawFilledRectangle(0,recArea,320,320,WHITE);

        }
    } 
    else{
          LCD_ILI9341_DrawCircle(Xp, Yp, brush_size, paint_color, brush_size);

    }
    }
     //Para hacer lineas finas se debe obtener el promedio de puntos
     //Para dibujar coordenadas
     /*
    LCD_ILI9341_DrawFilledRectangle(230,10,310,70,ILI9341_COLOR_WHITE); //borrar anteriores
     snprintf(buffer, 15, "%d", Xp);
    // LCD_ILI9341_Puts(230, 10, buffer, &LCD_Font_16x26, ILI9341_COLOR_RED,
    // ILI9341_COLOR_BLUE);
    // snprintf(buffer, 15, "%d", Yp);
    // LCD_ILI9341_Puts(230, 40, buffer, &LCD_Font_16x26, ILI9341_COLOR_GREEN,
    // ILI9341_COLOR_BLUE);
    // HAL_Delay(100);
    // */
    
  }
    // HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET); //apagar LED

  


  
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

   __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LCD_LED_Pin|T_CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : LED1_Pin LED2_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_LED_Pin T_CS_Pin */
  GPIO_InitStruct.Pin = LCD_LED_Pin|T_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = T_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(T_IRQ_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */


  /* Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, DC_Pin | CS_Pin | RESET_Pin, GPIO_PIN_SET);

  /* Configure LCD control pins: PD2 (CS), PD4 (RESET), PD5 (DC), PD6 (LED) */
  GPIO_InitStruct.Pin = DC_Pin | CS_Pin | RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
