/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// ��ͨ������״̬ʱ��
static uint8_t vertical_green_time = 15, vertical_yellow_time = 3, 
	horizontal_green_time = 15, horizontal_yellow_time = 3, 
	vertical_turn_left_green_time = 3, vertical_turn_left_yellow_time = 3, 
	horizontal_turn_left_green_time = 3, horizontal_turn_left_yellow_time = 3,
	people_time = 3;
// �������ʾ��־����ʾ����
uint8_t vertical_display_num,horizontal_display_num,vertical_display_flag,horizontal_display_flag;
// �������������ģ
uint8_t num_table[11]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff};

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */
	if(vertical_green_time > 10)
	{
		vertical_green_time++;
		horizontal_green_time--;
	}
  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief This function handles EXTI line1 interrupt.
  */
void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */
	if(horizontal_green_time > 10)
	{
		horizontal_green_time++;
		vertical_green_time--;
	}
  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */

  /* USER CODE END EXTI1_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
	static uint8_t led_state = 0;// 0�Ǻ����ƣ������̵ƣ���1�Ǻ����ƣ�����Ƶƣ���
	                             // 2�������ƣ������̵ƣ���3�������ƣ�����Ƶƣ���
	                             // 4�Ǻ����ƣ�������ת�̵ƣ���5�Ǻ����ƣ�����Ƶƣ���
	                             // 6�������ƣ�������ת�̵ƣ���7�������ƣ�����Ƶƣ���
	                             // 8�����е��̵�

	static uint8_t count;
	led_state %= 4;
	switch(led_state)
	{
		case 0:
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
			/*
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
			*/
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
			count++;
			
			horizontal_display_flag = 1;
			horizontal_display_num = vertical_green_time + vertical_yellow_time - count;
			if(count >= vertical_green_time)
			{
				led_state += 1;
				count = 0;
			}
		}
		break;
		case 1:
		{
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
			count++;
			
			horizontal_display_num = vertical_yellow_time - count;
			if(count >= vertical_yellow_time)
			{
				led_state += 1;
				count = 0;
				horizontal_display_flag = 0;
			}
		}
		break;
		case 2:
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
			count++;
			
			vertical_display_flag = 1;
			vertical_display_num = horizontal_green_time + horizontal_yellow_time - count;
			if(count >= horizontal_green_time)
			{
				led_state += 1;
				count = 0;
			}
		}
		break;
		case 3:
		{
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
			count++;
			
			vertical_display_flag = 1;
			vertical_display_num = horizontal_yellow_time - count;
			if(count >= horizontal_yellow_time)
			{
				led_state += 1;
				count = 0;
				vertical_display_flag = 0;
			}
		}
		break;
		case 4:
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
			count++;
			
			horizontal_display_flag = 1;
			horizontal_display_num = vertical_turn_left_green_time + vertical_turn_left_yellow_time - count;
			if(count >= vertical_turn_left_green_time)
			{
				led_state += 1;
				count = 0;
			}
		}
		break;
		case 5:
		{
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
			count++;
			
			horizontal_display_num = vertical_turn_left_yellow_time - count;
			if(count >= vertical_turn_left_yellow_time)
			{
				led_state += 1;
				count = 0;
				horizontal_display_flag = 0;
			}
		}
		break;
		case 6:
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
			count++;
			
			vertical_display_flag = 1;
			vertical_display_num = horizontal_turn_left_green_time + horizontal_turn_left_yellow_time - count;
			if(count >= horizontal_turn_left_green_time)
			{
				led_state += 1;
				count = 0;
			}
		}
		break;
		case 7:
		{
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
			count++;
			
			vertical_display_num = horizontal_turn_left_yellow_time - count;
			if(count >= horizontal_turn_left_yellow_time)
			{
				led_state += 1;
				count = 0;
				vertical_display_flag = 0;
			}
		}
		break;
		case 8:
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
			count++;
			
			vertical_display_flag = 1;
			horizontal_display_flag = 1;
			vertical_display_num = people_time - count;
			horizontal_display_num = vertical_display_num;
			if(count >= people_time)
			{
				led_state += 1;
				count = 0;
				vertical_display_flag = 0;
				horizontal_display_flag = 0;
			}
		}
		break;
		default: break;
	}
  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */
	
	// �������ʾ
	uint8_t ones,tens;
	if(horizontal_display_flag == 1)
	{
		ones = horizontal_display_num % 10;
		tens = horizontal_display_num / 10;
		if(HAL_GPIO_ReadPin(GPIOE, HORIZONTAL_ONES_Pin))
		{
			// ��Ӱ
			for(uint8_t i = 0;i < 8;i++)
			{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0 << i, GPIO_PIN_SET);
			}
			// λѡ
			HAL_GPIO_WritePin(GPIOE, HORIZONTAL_ONES_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE, HORIZONTAL_TENS_Pin, GPIO_PIN_SET);
			// ��ѡ
			for(uint8_t i = 0;i < 8;i++)
			{
				if((GPIO_PIN_0 << i) & num_table[tens])
				{
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0 << i, GPIO_PIN_SET);
				}
				else
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0 << i, GPIO_PIN_RESET);
			}
		}
		else
		{
			for(uint8_t i = 0;i < 8;i++)
			{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0 << i, GPIO_PIN_SET);
			}
			HAL_GPIO_WritePin(GPIOE, HORIZONTAL_TENS_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE, HORIZONTAL_ONES_Pin, GPIO_PIN_SET);
			for(uint8_t i = 0;i < 8;i++)
			{
				if((GPIO_PIN_0 << i) & num_table[ones])
				{
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0 << i, GPIO_PIN_SET);
				}
				else
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0 << i, GPIO_PIN_RESET);
			}
		}
	}
	else // ���
	{
		HAL_GPIO_WritePin(GPIOE, HORIZONTAL_ONES_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, HORIZONTAL_TENS_Pin, GPIO_PIN_RESET);
		for(uint8_t i = 0;i < 8;i++)
		{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0 << i, GPIO_PIN_SET);
		}
	}
	// ��ֱ���������
	if(vertical_display_flag == 1)
	{
		ones = vertical_display_num % 10;
		tens = vertical_display_num / 10;
		if(HAL_GPIO_ReadPin(GPIOE, VERTICAL_ONES_Pin))
		{
			// ��Ӱ
			for(uint8_t i = 0;i < 8;i++)
			{
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 << i, GPIO_PIN_SET);
			}
			// λѡ
			HAL_GPIO_WritePin(GPIOE, VERTICAL_ONES_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE, VERTICAL_TENS_Pin, GPIO_PIN_SET);
			// ��ѡ
			for(uint8_t i = 0;i < 8;i++)
			{
				if((GPIO_PIN_0 << i) & num_table[tens])
				{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 << i, GPIO_PIN_SET);
				}
				else
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 << i, GPIO_PIN_RESET);
			}
		}
		else
		{
			for(uint8_t i = 0;i < 8;i++)
			{
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 << i, GPIO_PIN_SET);
			}
			HAL_GPIO_WritePin(GPIOE, VERTICAL_TENS_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE, VERTICAL_ONES_Pin, GPIO_PIN_SET);
			for(uint8_t i = 0;i < 8;i++)
			{
				if((GPIO_PIN_0 << i) & num_table[ones])
				{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 << i, GPIO_PIN_SET);
				}
				else
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 << i, GPIO_PIN_RESET);
			}
		}
	}
	else // ���
	{
		HAL_GPIO_WritePin(GPIOE, VERTICAL_ONES_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, VERTICAL_TENS_Pin, GPIO_PIN_RESET);
		for(uint8_t i = 0;i < 8;i++)
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 << i, GPIO_PIN_SET);
		}
	}
	
  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
