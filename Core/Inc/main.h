/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

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
#define LATCH_Pin GPIO_PIN_6
#define LATCH_GPIO_Port GPIOA
#define MASTER_RESET_Pin GPIO_PIN_0
#define MASTER_RESET_GPIO_Port GPIOB
#define OUTPUT_ENABLE_Pin GPIO_PIN_1
#define OUTPUT_ENABLE_GPIO_Port GPIOB
#define TRIG_Pin GPIO_PIN_2
#define TRIG_GPIO_Port GPIOB
#define INC_Pin GPIO_PIN_10
#define INC_GPIO_Port GPIOB
#define DEC_Pin GPIO_PIN_11
#define DEC_GPIO_Port GPIOB
#define NEXT_Pin GPIO_PIN_12
#define NEXT_GPIO_Port GPIOB
#define PREV_Pin GPIO_PIN_13
#define PREV_GPIO_Port GPIOB
#define SETBTN_Pin GPIO_PIN_14
#define SETBTN_GPIO_Port GPIOB
#define RSTBTN_Pin GPIO_PIN_15
#define RSTBTN_GPIO_Port GPIOB
#define ACTIVITY_INDICATOR_Pin GPIO_PIN_15
#define ACTIVITY_INDICATOR_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
