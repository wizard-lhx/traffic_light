/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define HORIZONTAL_R_Pin GPIO_PIN_0
#define HORIZONTAL_R_GPIO_Port GPIOA
#define HORIZONTAL_Y_Pin GPIO_PIN_1
#define HORIZONTAL_Y_GPIO_Port GPIOA
#define HORIZONTAL_G_Pin GPIO_PIN_2
#define HORIZONTAL_G_GPIO_Port GPIOA
#define VERTICAL_R_Pin GPIO_PIN_3
#define VERTICAL_R_GPIO_Port GPIOA
#define VERTICAL_Y_Pin GPIO_PIN_4
#define VERTICAL_Y_GPIO_Port GPIOA
#define VERTICAL_G_Pin GPIO_PIN_5
#define VERTICAL_G_GPIO_Port GPIOA
#define HORIZONTAL_LG_Pin GPIO_PIN_6
#define HORIZONTAL_LG_GPIO_Port GPIOA
#define VERTICAL_LG_Pin GPIO_PIN_7
#define VERTICAL_LG_GPIO_Port GPIOA
#define DIGITAL_TUBE_SEGMENT_Pin GPIO_PIN_0
#define DIGITAL_TUBE_SEGMENT_GPIO_Port GPIOB
#define VERTICAL_TENS_Pin GPIO_PIN_10
#define VERTICAL_TENS_GPIO_Port GPIOB
#define VERTICAL_ONES_Pin GPIO_PIN_11
#define VERTICAL_ONES_GPIO_Port GPIOB
#define HORIZONTAL_TENS_Pin GPIO_PIN_12
#define HORIZONTAL_TENS_GPIO_Port GPIOB
#define HORIZONTAL_ONES_Pin GPIO_PIN_13
#define HORIZONTAL_ONES_GPIO_Port GPIOB
#define PEOPLE_R_Pin GPIO_PIN_8
#define PEOPLE_R_GPIO_Port GPIOA
#define PEOPLE_G_Pin GPIO_PIN_11
#define PEOPLE_G_GPIO_Port GPIOA
#define VERTICAL_SET_Pin GPIO_PIN_8
#define VERTICAL_SET_GPIO_Port GPIOB
#define VERTICAL_SET_EXTI_IRQn EXTI9_5_IRQn
#define HORIZONTAL_SET_Pin GPIO_PIN_9
#define HORIZONTAL_SET_GPIO_Port GPIOB
#define HORIZONTAL_SET_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
