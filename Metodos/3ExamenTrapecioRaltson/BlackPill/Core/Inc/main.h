/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct{
  int option;
  float num_presicion;
} INIT;


typedef struct { 
    float *x; 
    float *y;
    int grado; 
} poli;

typedef struct {
    float val;
    float error;
    int it;
    char success;
} RESULT;


typedef struct {
    int max_it;
    float tol;
} LIMITS;

typedef struct{
    float pointEval;
    float *coefs;
    uint8_t size;
} NEWTONRESULT;

typedef struct {
    float C;
    float L;
    float x;
} RLCFunct;



typedef struct { 
    uint8_t size;
    float **matrix; 
    float *vector;
} GaussJordanResult;

typedef struct { 
    float lim_inferior; 
    float lim_superior;
    int num_subinterval; 
} params;

typedef struct { 
    float Integral;
    float *x;
    float *fx;
    float h;
    int num_subinterval;
} Result;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
