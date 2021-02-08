/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gps.h"
#include "ssd1306.h"
#include "fonts.h"
#include "menu.h"
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
uint8_t MessageLength;
uint8_t Message[64];
uint8_t button_state[4] = {0,0,0,0};
uint8_t data_display = 0;
uint8_t sec_status;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */



/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
I2C_HandleTypeDef hi2c1;
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
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  GPS_Init();
  ssd1306_Init(&hi2c1);
  menu_show(current_menu->name, hi2c1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  button_check();
	  screen_refresh();
//		HAL_UART_Transmit(DEBUG_USART, "DATA\r\n", 6, 100);
//		MessageLength = sprintf((char*)Message, "sec: %i",GPS_data.UTC_Sec);
//		HAL_UART_Transmit(DEBUG_USART, Message, MessageLength, 100);
//		HAL_UART_Transmit(DEBUG_USART, "\r\n", 2, 100);
//		HAL_UART_Transmit(DEBUG_USART, &GPS_data.ew, 1, 100);
//		HAL_UART_Transmit(DEBUG_USART, &GPS_data.ns, 1, 100);
//		HAL_UART_Transmit(DEBUG_USART, "\r\n", 2, 100);
//		HAL_UART_Transmit(DEBUG_USART, "END\r\n", 5, 100);
//		HAL_Delay(1000);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_USART3
                              |RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == GPS_USART)
	{
		GPS_CallBack();
	}
}

uint8_t debounce_button(uint16_t GPIO_Pin)
{
	HAL_Delay(50);
	if(!HAL_GPIO_ReadPin (GPIOA, GPIO_Pin))
		return 1;
	else
		return 0;
}

void release_button(uint16_t GPIO_Pin, uint8_t *state)
{
	if (*state && HAL_GPIO_ReadPin(GPIOA, GPIO_Pin))
	{
		*state = 0;
	}
}

void screen_refresh(void)
{
	if (data_display && (sec_status == GPS_data.UTC_Sec))
	{
		menu_show("***** ***", hi2c1);
	}
}

void button_check(void)
{
	if(!button_state[0] && !HAL_GPIO_ReadPin(GPIOA, button_child_Pin))
	{
		sec_status = GPS_data.UTC_Sec;
		button_state[0] = 1;
		if(debounce_button(button_child_Pin))
		{
			if (current_menu->menu_f)
			{
				data_display = 1;
				menu_show(current_menu->menu_f(), hi2c1);
			}
			else
			{
				menu_sw_child();
				menu_show(current_menu->name, hi2c1);
			}
		}
	}
	if(!button_state[1] && !HAL_GPIO_ReadPin(GPIOA, button_parrent_Pin))
	{
		button_state[1] = 1;
		if(debounce_button(button_parrent_Pin))
		{
			if (data_display)
			{
				data_display = 0;
				menu_show(current_menu->name, hi2c1);
			}
			else
			{
				menu_sw_parent();
				menu_show(current_menu->name, hi2c1);
			}
		}
	}
	if(!button_state[2] && !HAL_GPIO_ReadPin(GPIOA, button_next_Pin))
	{
		button_state[2] = 1;
		if(debounce_button(button_next_Pin))
		{
			menu_sw_next();
			menu_show(current_menu->name, hi2c1);
		}
	}
	if(!button_state[3] && !HAL_GPIO_ReadPin(GPIOA, button_previous_Pin))
	{
		button_state[3] = 1;
		if(debounce_button(button_previous_Pin))
		{
			menu_sw_previous();
			menu_show(current_menu->name, hi2c1);
		}
	}

	release_button(button_child_Pin, &button_state[0]);
	release_button(button_parrent_Pin, &button_state[1]);
	release_button(button_next_Pin, &button_state[2]);
	release_button(button_previous_Pin, &button_state[3]);
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
