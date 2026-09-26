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
#include <string.h>
#include <stdarg.h>
#include "ili9341.h"
#include "ili9341_touch.h"
#include "fonts.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
void init() {
    ILI9341_Unselect();
    ILI9341_TouchUnselect();
    ILI9341_Init();
}

void test_code();
void paint_code();
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

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  init();
  ILI9341_FillScreen(ILI9341_BLACK);
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//    test_code();
    paint_code();
    
  }
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ILI9341_CS_GPIO_Port, ILI9341_CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RST_Pin|D_C_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ILI9341_CS_Pin RST_Pin D_C_Pin */
  GPIO_InitStruct.Pin = ILI9341_CS_Pin|RST_Pin|D_C_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* Touch CS */
  GPIO_InitStruct.Pin = ILI9341_TOUCH_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(ILI9341_TOUCH_CS_GPIO_Port, &GPIO_InitStruct);

  HAL_GPIO_WritePin(ILI9341_TOUCH_CS_GPIO_Port,
                    ILI9341_TOUCH_CS_Pin,
                    GPIO_PIN_SET);

  /* Touch IRQ */
  GPIO_InitStruct.Pin = ILI9341_TOUCH_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;      // prueba primero con PULLUP
  HAL_GPIO_Init(ILI9341_TOUCH_IRQ_GPIO_Port, &GPIO_InitStruct);
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void test_code(){
  uint16_t touchX, touchY;
  uint16_t lastX = 0, lastY = 0; 

  while(1){
    if (ILI9341_TouchPressed())
    {
        if (ILI9341_TouchGetCoordinates(&touchX, &touchY))
        {
        // Borra el punto anterior (opcional)
        ILI9341_FillCircle(lastX, lastY, 4, ILI9341_BLACK);

        // Dibuja el nuevo
        ILI9341_FillCircle(touchX, touchY, 4, ILI9341_RED);

        lastX = touchX;
        lastY = touchY;
    }}
}
}
void paint_code() {
  
  uint16_t touchX;
  uint16_t touchY;
  uint16_t lastX = 0;
  uint16_t lastY = 0;

  uint16_t width = 29; uint16_t height = 28;
  uint16_t RED_X = 234; uint16_t RED_Y = 21;
  uint16_t BLUE_X = 234; uint16_t BLUE_Y = 66;
  uint16_t GREEN_X = 275; uint16_t GREEN_Y = 21;
  uint16_t CYAN_X = 276; uint16_t CYAN_Y = 66;
  uint16_t MAGENTA_X = 234; uint16_t MAGENTA_Y = 111;
  uint16_t YELLOW_X = 275; uint16_t YELLOW_Y = 111;
  uint16_t INC_X = 232; uint16_t INC_Y = 192; 
  uint16_t DEC_X = 277; uint16_t DEC_Y = 192;
  uint16_t FRAME_X = 4; uint16_t FRAME_Y = 4; uint16_t FRAME_width = 222;
  uint16_t size = 4;
  uint16_t color;


 ILI9341_FillRectangle(RED_X, RED_Y, width, height, ILI9341_RED);
  ILI9341_FillRectangle(BLUE_X, BLUE_Y, width, height, ILI9341_BLUE);
  ILI9341_FillRectangle(GREEN_X, GREEN_Y, width, height, ILI9341_GREEN);
  ILI9341_FillRectangle(CYAN_X, CYAN_Y, width, height, ILI9341_CYAN);
  ILI9341_FillRectangle(MAGENTA_X, MAGENTA_Y, width, height, ILI9341_MAGENTA);
  ILI9341_FillRectangle(YELLOW_X, YELLOW_Y, width, height, ILI9341_YELLOW);
  ILI9341_FillRectangle(231, 158, 79, 28, ILI9341_RED);
  ILI9341_FillRectangle(282, 158, 29, 28, ILI9341_BLUE);
  ILI9341_WriteString(230, 168, "Gorrador", Font_11x18, ILI9341_WHITE, ILI9341_BLACK);
  
  ILI9341_FillRectangle(INC_X, INC_Y, width, height, 0xFC00);
  ILI9341_FillRectangle(DEC_X, DEC_Y, width, height, 0xFC00);

  ILI9341_FillRectangle(INC_X, INC_Y+width/2, width, 1, 0xFFFF);
  ILI9341_FillRectangle((INC_X+height/2), INC_Y, 1, height, 0xFFFF);
  ILI9341_FillRectangle(DEC_X, DEC_Y+width/2, width, 1, 0xFFFF);
  

  while(1){


    if (ILI9341_TouchPressed())
    {
        if (ILI9341_TouchGetCoordinates(&touchX, &touchY))
        {
          if(touchX >= RED_X && touchX <= RED_X + width &&
             touchY >= RED_Y && touchY <= RED_Y + height) {
              color =(ILI9341_RED);
          } else if(touchX >= BLUE_X && touchX <= BLUE_X + width &&
                    touchY >= BLUE_Y && touchY <= BLUE_Y + height) {
              color =(ILI9341_BLUE);
          } else if(touchX >= GREEN_X && touchX <= GREEN_X + width &&
                    touchY >= GREEN_Y && touchY <= GREEN_Y + height) {
              color =(ILI9341_GREEN);
          } else if(touchX >= CYAN_X && touchX <= CYAN_X + width &&
                    touchY >= CYAN_Y && touchY <= CYAN_Y + height) {
              color =(ILI9341_CYAN);
          } else if(touchX >= MAGENTA_X && touchX <= MAGENTA_X + width &&
                    touchY >= MAGENTA_Y && touchY <= MAGENTA_Y + height) {
              color =(ILI9341_MAGENTA);
          } else if(touchX >= YELLOW_X && touchX <= YELLOW_X + width &&
                    touchY >= YELLOW_Y && touchY <= YELLOW_Y + height) {
              color =(ILI9341_YELLOW);
          } else if(touchX >= 231 && touchX <= 231 + 79 &&
                    touchY >= 158 && touchY <= 158 + 28) {
              color =(ILI9341_BLACK);
          } 
          else if(touchX >= INC_X && touchX <= INC_X + width &&
                    touchY >= INC_Y && touchY <= INC_Y + height) {
              if(size < 40)
                    size++;
              else
                    size = 40;
          } 
          else if(touchX >= DEC_X && touchX <= DEC_X + width &&
                    touchY >= DEC_Y && touchY <= DEC_Y + height) {
              if(size > 1)
                    size--;
              else
                    size = 1;
          }

          if(touchX >= FRAME_X && touchX <= FRAME_X + FRAME_width &&
             touchY >= FRAME_Y && touchY <= FRAME_Y + FRAME_width) {
              ILI9341_FillCircle(touchX, touchY, size, color);
          }

        lastX = touchX;
        lastY = touchY;
    }
}


  }

   
}
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
