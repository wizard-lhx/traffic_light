/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_ano_dt.h"
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

/* USER CODE BEGIN PV */
// 交通灯所有状态时间
uint8_t vertical_green_time = 15, vertical_yellow_time = 3, 
	horizontal_green_time = 15, horizontal_yellow_time = 3, 
	vertical_turn_left_green_time = 15, vertical_turn_left_yellow_time = 3, 
	horizontal_turn_left_green_time = 15, horizontal_turn_left_yellow_time = 3,
	people_time = 15;
// 数码管显示标志和显示数字
uint8_t vertical_display_num,horizontal_display_num,vertical_display_flag,horizontal_display_flag;
// 共阳极数码管字模
uint8_t num_table[11]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff};

extern uint8_t update_1000ms;
extern uint8_t update_10ms;

extern uint8_t vertical_time_sub;
extern uint8_t horizontal_time_sub;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void update_time(void)
{
	if(vertical_time_sub)
	{
		vertical_green_time -= vertical_time_sub;
		horizontal_green_time += vertical_time_sub;
		vertical_time_sub = 0;
	}
}
void update_led(void)
{
	static uint8_t led_state = 0;// 0是横向红灯（竖向绿灯）、1是横向红灯（竖向黄灯）、
	                             // 2是竖向红灯（横向绿灯）、3是竖向红灯（横向黄灯）、
	                             // 4是横向红灯（竖向左转绿灯）、5是横向红灯（竖向黄灯）、
	                             // 6是竖向红灯（横向左转绿灯）、7是竖向红灯（横向黄灯）、
	                             // 8是人行道绿灯

	static uint8_t count;
	update_time();
	led_state %= 9;
	switch(led_state)
	{
		case 0:
		{
			HAL_GPIO_WritePin(HORIZONTAL_R_GPIO_Port, HORIZONTAL_R_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(VERTICAL_R_GPIO_Port, VERTICAL_R_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PEOPLE_G_GPIO_Port, PEOPLE_G_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PEOPLE_R_GPIO_Port, PEOPLE_R_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(VERTICAL_G_GPIO_Port, VERTICAL_G_Pin, GPIO_PIN_RESET);
			count++;
			
			horizontal_display_flag = 1;
			if(vertical_green_time + vertical_yellow_time >= count)
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
			HAL_GPIO_TogglePin(VERTICAL_Y_GPIO_Port, VERTICAL_Y_Pin);
			HAL_GPIO_WritePin(VERTICAL_G_GPIO_Port, VERTICAL_G_Pin, GPIO_PIN_SET);
			count++;
			
			if(vertical_yellow_time >= count)
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
			HAL_GPIO_WritePin(HORIZONTAL_R_GPIO_Port, HORIZONTAL_R_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(VERTICAL_Y_GPIO_Port, VERTICAL_Y_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(HORIZONTAL_G_GPIO_Port, HORIZONTAL_G_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(VERTICAL_R_GPIO_Port, VERTICAL_R_Pin, GPIO_PIN_RESET);
			count++;
			
			vertical_display_flag = 1;
			if(horizontal_green_time + horizontal_yellow_time >= count)
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
			HAL_GPIO_TogglePin(HORIZONTAL_Y_GPIO_Port, HORIZONTAL_Y_Pin);
			HAL_GPIO_WritePin(HORIZONTAL_G_GPIO_Port, HORIZONTAL_G_Pin, GPIO_PIN_SET);
			count++;
			
			vertical_display_flag = 1;
			if(horizontal_yellow_time >= count)
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
			HAL_GPIO_WritePin(HORIZONTAL_Y_GPIO_Port, HORIZONTAL_Y_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(VERTICAL_R_GPIO_Port, VERTICAL_R_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(VERTICAL_LG_GPIO_Port, VERTICAL_LG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(HORIZONTAL_R_GPIO_Port, HORIZONTAL_R_Pin, GPIO_PIN_RESET);
			count++;
			
			horizontal_display_flag = 1;
			if(vertical_turn_left_green_time + vertical_turn_left_yellow_time >= count)
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
			HAL_GPIO_TogglePin(VERTICAL_Y_GPIO_Port, VERTICAL_Y_Pin);
			HAL_GPIO_WritePin(VERTICAL_LG_GPIO_Port, VERTICAL_LG_Pin, GPIO_PIN_SET);
			count++;
			
			if(vertical_turn_left_yellow_time >= count)
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
			HAL_GPIO_WritePin(VERTICAL_Y_GPIO_Port, VERTICAL_Y_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(HORIZONTAL_R_GPIO_Port, HORIZONTAL_R_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(HORIZONTAL_LG_GPIO_Port, HORIZONTAL_LG_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(VERTICAL_R_GPIO_Port, VERTICAL_R_Pin, GPIO_PIN_RESET);
			count++;
			
			vertical_display_flag = 1;
			if(horizontal_turn_left_green_time + horizontal_turn_left_yellow_time >= count)
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
			HAL_GPIO_TogglePin(HORIZONTAL_Y_GPIO_Port, HORIZONTAL_Y_Pin);
			HAL_GPIO_WritePin(HORIZONTAL_LG_GPIO_Port, HORIZONTAL_LG_Pin, GPIO_PIN_SET);
			count++;
			
			if(horizontal_turn_left_yellow_time >= count)
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
			HAL_GPIO_WritePin(HORIZONTAL_Y_GPIO_Port, HORIZONTAL_Y_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(HORIZONTAL_R_GPIO_Port, HORIZONTAL_R_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PEOPLE_R_GPIO_Port, PEOPLE_R_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PEOPLE_G_GPIO_Port, PEOPLE_G_Pin, GPIO_PIN_RESET);
			count++;
			
			vertical_display_flag = 1;
			horizontal_display_flag = 1;
			if(people_time >= count)
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
}
void update_digital_tube(void)
{
	// 数码管显示
	uint8_t ones,tens;
	if(horizontal_display_flag == 1)
	{
		ones = horizontal_display_num % 10;
		tens = horizontal_display_num / 10;
		if(HAL_GPIO_ReadPin(HORIZONTAL_ONES_GPIO_Port, HORIZONTAL_ONES_Pin))
		{
			// 消影
			for(uint8_t i = 0;i < 8;i++)
			{
				HAL_GPIO_WritePin(DIGITAL_TUBE_SEGMENT_GPIO_Port, DIGITAL_TUBE_SEGMENT_Pin << i, GPIO_PIN_SET);
			}
			// 位选
			HAL_GPIO_WritePin(HORIZONTAL_ONES_GPIO_Port, HORIZONTAL_ONES_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(HORIZONTAL_TENS_GPIO_Port, HORIZONTAL_TENS_Pin, GPIO_PIN_SET);
			// 段选
			for(uint8_t i = 0;i < 8;i++)
			{
				if((GPIO_PIN_0 << i) & num_table[tens])
				{
					HAL_GPIO_WritePin(DIGITAL_TUBE_SEGMENT_GPIO_Port, DIGITAL_TUBE_SEGMENT_Pin << i, GPIO_PIN_SET);
				}
				else
					HAL_GPIO_WritePin(DIGITAL_TUBE_SEGMENT_GPIO_Port, DIGITAL_TUBE_SEGMENT_Pin << i, GPIO_PIN_RESET);
			}
		}
		else
		{
			for(uint8_t i = 0;i < 8;i++)
			{
				HAL_GPIO_WritePin(DIGITAL_TUBE_SEGMENT_GPIO_Port, DIGITAL_TUBE_SEGMENT_Pin << i, GPIO_PIN_SET);
			}
			HAL_GPIO_WritePin(HORIZONTAL_TENS_GPIO_Port, HORIZONTAL_TENS_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(HORIZONTAL_ONES_GPIO_Port, HORIZONTAL_ONES_Pin, GPIO_PIN_SET);
			for(uint8_t i = 0;i < 8;i++)
			{
				if((GPIO_PIN_0 << i) & num_table[ones])
				{
					HAL_GPIO_WritePin(DIGITAL_TUBE_SEGMENT_GPIO_Port, DIGITAL_TUBE_SEGMENT_Pin << i, GPIO_PIN_SET);
				}
				else
					HAL_GPIO_WritePin(DIGITAL_TUBE_SEGMENT_GPIO_Port, DIGITAL_TUBE_SEGMENT_Pin << i, GPIO_PIN_RESET);
			}
		}
	}
	else // 灭灯
	{
		HAL_GPIO_WritePin(HORIZONTAL_ONES_GPIO_Port, HORIZONTAL_ONES_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HORIZONTAL_TENS_GPIO_Port, HORIZONTAL_TENS_Pin, GPIO_PIN_RESET);
	}
	// 竖直方向数码管
	if(vertical_display_flag == 1)
	{
		ones = vertical_display_num % 10;
		tens = vertical_display_num / 10;
		if(HAL_GPIO_ReadPin(VERTICAL_ONES_GPIO_Port, VERTICAL_ONES_Pin))
		{
			// 消影
			for(uint8_t i = 0;i < 8;i++)
			{
				HAL_GPIO_WritePin(DIGITAL_TUBE_SEGMENT_GPIO_Port, DIGITAL_TUBE_SEGMENT_Pin << i, GPIO_PIN_SET);
			}
			// 位选
			HAL_GPIO_WritePin(VERTICAL_ONES_GPIO_Port, VERTICAL_ONES_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(VERTICAL_TENS_GPIO_Port, VERTICAL_TENS_Pin, GPIO_PIN_SET);
			// 段选
			for(uint8_t i = 0;i < 8;i++)
			{
				if((GPIO_PIN_0 << i) & num_table[tens])
				{
					HAL_GPIO_WritePin(DIGITAL_TUBE_SEGMENT_GPIO_Port, DIGITAL_TUBE_SEGMENT_Pin << i, GPIO_PIN_SET);
				}
				else
					HAL_GPIO_WritePin(DIGITAL_TUBE_SEGMENT_GPIO_Port, DIGITAL_TUBE_SEGMENT_Pin << i, GPIO_PIN_RESET);
			}
		}
		else
		{
			for(uint8_t i = 0;i < 8;i++)
			{
				HAL_GPIO_WritePin(DIGITAL_TUBE_SEGMENT_GPIO_Port, DIGITAL_TUBE_SEGMENT_Pin << i, GPIO_PIN_SET);
			}
			HAL_GPIO_WritePin(VERTICAL_TENS_GPIO_Port, VERTICAL_TENS_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(VERTICAL_ONES_GPIO_Port, VERTICAL_ONES_Pin, GPIO_PIN_SET);
			for(uint8_t i = 0;i < 8;i++)
			{
				if((GPIO_PIN_0 << i) & num_table[ones])
				{
					HAL_GPIO_WritePin(DIGITAL_TUBE_SEGMENT_GPIO_Port, DIGITAL_TUBE_SEGMENT_Pin << i, GPIO_PIN_SET);
				}
				else
					HAL_GPIO_WritePin(DIGITAL_TUBE_SEGMENT_GPIO_Port, DIGITAL_TUBE_SEGMENT_Pin << i, GPIO_PIN_RESET);
			}
		}
	}
	else // 灭灯
	{
		HAL_GPIO_WritePin(VERTICAL_ONES_GPIO_Port, VERTICAL_ONES_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(VERTICAL_TENS_GPIO_Port, VERTICAL_TENS_Pin, GPIO_PIN_RESET);
	}
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart == &huart1)
	{
		ano_dt_rx_data_handle(Size);
	}
}
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
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	for(uint8_t i = 0;i < 8;i++)
	{
		HAL_GPIO_WritePin(HORIZONTAL_R_GPIO_Port, HORIZONTAL_R_Pin << i, GPIO_PIN_SET);
	}
	for(uint8_t i = 0;i < 8;i++)
	{
		HAL_GPIO_WritePin(DIGITAL_TUBE_SEGMENT_GPIO_Port, DIGITAL_TUBE_SEGMENT_Pin << i, GPIO_PIN_SET);
	}
	for(uint8_t i = 0;i < 4;i++)
	{
		HAL_GPIO_WritePin(HORIZONTAL_ONES_GPIO_Port, HORIZONTAL_ONES_Pin << i, GPIO_PIN_SET);
	}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if(update_1000ms)
		{
			update_led();
			update_1000ms = 0;
		}
		if(update_10ms)
		{
			update_digital_tube();
			update_10ms = 0;
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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

#ifdef  USE_FULL_ASSERT
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
