/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rtc.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "APP/button.h"
#include "APP/system.h"
#include "APP/display.h"
#include "APP/timer.h"
#include "APP/animation.h"
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

const std::array<uint8_t, hex_codes_count> display_manager::hex_codes { 0x3F,
		0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00 };

std::array<uint8_t, display_size> display_manager::displayed_codes{
	0x00, 0x00, 0x00, 0x00
};

std::array<std::shared_ptr<push_button>, interface_size> button_manager::keyboard {
		std::make_shared<hold_push_button>(TRIG_GPIO_Port, TRIG_Pin,
				system_manager::TRIG_Callback, system_manager::RST_Callback), std::make_shared<push_button>(
				SETBTN_GPIO_Port, SETBTN_Pin, system_manager::SET_Callback),
		std::make_shared<push_button>(RSTBTN_GPIO_Port, RSTBTN_Pin,
				system_manager::RST_Callback), std::make_shared<push_button>(
				NEXT_GPIO_Port, NEXT_Pin, system_manager::NEXT_Callback),
		std::make_shared<push_button>(PREV_GPIO_Port, PREV_Pin,
				system_manager::PREV_Callback), std::make_shared<
				hold_push_button>(INC_GPIO_Port, INC_Pin,
				system_manager::INC_Callback),
		std::make_shared<hold_push_button>(DEC_GPIO_Port, DEC_Pin,
				system_manager::DEC_Callback) };

system_state system_manager::state { system_state::halt_state };

bool button_manager::button_longer_pressed{ false };

bool display_manager::interrupt_flag{ false };

bool time_manager::sync{ false };
uint8_t time_manager::currently_set{ 0 };

uint8_t time_manager::minutes { 0 };
uint8_t time_manager::seconds { 0 };
uint32_t time_manager::seconds_elapsed { 0 };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
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
	MX_RTC_Init();
	MX_SPI1_Init();
	/* USER CODE BEGIN 2 */
//  static uint32_t timer = 0;
//  static uint8_t i = 0;
//  HAL_GPIO_WritePin(OUTPUT_ENABLE_GPIO_Port, OUTPUT_ENABLE_Pin, GPIO_PIN_RESET);
//  HAL_GPIO_WritePin(MASTER_RESET_GPIO_Port, MASTER_RESET_Pin, GPIO_PIN_SET);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		system_manager::main();
		button_manager::main();
		display_manager::main();
		time_manager::main();
		animation_manager::main();
		HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
//	if(HAL_GetTick() - timer > 500){
//		HAL_GPIO_TogglePin(ACTIVITY_INDICATOR_GPIO_Port, ACTIVITY_INDICATOR_Pin);
//		i = (i + 1) % 10;
////		timer = HAL_GetTick();
////	}
////
//	if(!HAL_GPIO_ReadPin(INC_GPIO_Port, INC_Pin)){
//		asm("nop");
//	}
//
//	if(!HAL_GPIO_ReadPin(DEC_GPIO_Port, DEC_Pin)){
//			asm("nop");
//	}
//
//	if(!HAL_GPIO_ReadPin(NEXT_GPIO_Port, NEXT_Pin)){
//			asm("nop");
//	}
//
//	if(!HAL_GPIO_ReadPin(PREV_GPIO_Port, PREV_Pin)){
//			asm("nop");
//	}
//
//	if(!HAL_GPIO_ReadPin(RSTBTN_GPIO_Port, RSTBTN_Pin)){
//			asm("nop");
//		}
//
//	if(!HAL_GPIO_ReadPin(SETBTN_GPIO_Port, SETBTN_Pin)){
//			asm("nop");
//	}
//
//	if(!HAL_GPIO_ReadPin(TRIG_GPIO_Port, TRIG_Pin)){
//				asm("nop");
//		}
//	uint8_t test_table[4] = { display_hex_codes[2], display_hex_codes[1], display_hex_codes[3], display_hex_codes[7] };
//	HAL_SPI_Transmit(&hspi1, test_table, 4, HAL_MAX_DELAY);
//
//	HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, GPIO_PIN_SET);
//
//	HAL_Delay(1);
//
//	HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, GPIO_PIN_RESET);
//
//	HAL_Delay(1);

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI
			| RCC_OSCILLATORTYPE_LSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
	PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
