/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32h7xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "stm32h7xx_it.h"
#include <string.h>
#include <stdio.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/// Sekundy przed startem kiedy przeciecie fotokomórki będzie traktowane jako falstart
 #define GATE_ARMED_TIME 5
/// Tyle sekund po starcie jesli nie nastapilo przeciecie start uwazany jest za niewazny
 #define NO_START_DELAY 5
/// Czas przed uzbroejniem bramki w którym jesli nastapi przecięcie odliczanie zostaje przerwane
 #define GATE_READY_TIME 10

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

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

//uint8_t external_stop=1;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

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
  * @brief This function handles Pre-fetch fault, memory access fault.
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
/* STM32H7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32h7xx.s).                    */
/******************************************************************************/


/**
 * Wysyła podany czas poprzez socket tcp oraz zapisuje na karcie SD
 * \param time czas który zostanie wysłany
 * \param date o nazwie zależnej od daty zostanie stworzony plik na karcie SD
 */
void send_time(volatile RTC_TimeTypeDef* time, volatile RTC_DateTypeDef* date)
	{
		char time_string[14];
		uint8_t millis = (float) 1000*(1023-time->SubSeconds)/1024.0f;
		sprintf(time_string, "%.2d:%.2d:%.2d.%.3d,\n", time->Hours, time->Minutes, time->Seconds, millis);
		char data[30];
		sprintf(data, "AT+S.SOCKDW=0,0,%d\r%s", strlen(time_string), time_string);
		HAL_UART_Transmit(&huart6, (uint8_t*) data , strlen(data), 100);
		char data1[30];

		sprintf(data1, "AT+S.FSC=0:/%s,%d\r%s", date_string, strlen(time_string), time_string);
		HAL_UART_Transmit(&huart6, (uint8_t*) data1 , strlen(data1), 100);
	}

void UART4_IRQHandler(void)
{
  /* USER CODE BEGIN UART4_IRQn 0 */
	__HAL_RTC_WRITEPROTECTION_DISABLE(&hrtc);
	RTC->SHIFTR = RTC_SHIFTR_ADD1S | ((RTC->PRER & RTC_PRER_PREDIV_S_Msk) - (RTC->SSR & RTC_SSR_SS_Msk));
	gps_sync = IN_SYNC;
  /* USER CODE END UART4_IRQn 0 */
  HAL_UART_IRQHandler(&huart4);
  /* USER CODE BEGIN UART4_IRQn 1 */
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET); // Yellow LED
  /* USER CODE END UART4_IRQn 1 */
}

void USART6_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart6);
}

void RTC_WKUP_IRQHandler(void)
{
	// reseting wakeup flag must be done in software
	__HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hrtc, RTC_FLAG_WUTF);
	__HAL_RTC_EXTI_CLEAR_FLAG(RTC_EXTI_LINE_WAKEUPTIMER_EVENT);

	HAL_RTC_GetTime(&hrtc, (RTC_TimeTypeDef*) &time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, (RTC_DateTypeDef*) &date, RTC_FORMAT_BIN);

	if(starter_mode == AUTO_START)
	{
		counter--;
		TM1637_WriteTime(&display_clock, time.Hours, time.Minutes, TM1637_SEPARATOR_ON);
		TM1637_WriteTime(&display_counter, 00, counter, TM1637_SEPARATOR_ON);
		if(counter == GATE_ARMED_TIME)
		{
			start_state = GATE_CLOSED;
		}
		else if(counter == GATE_READY_TIME )
		{
			start_state = GATE_READY;
		}
		else if(counter == 0)
		{
			LED_GREEN_ON();
			start_time = time;
			if(start_state == FALSTART)
			{
				send_time(&start_time, &date);
				start_state = NO_START;
			} else {
				start_state = GATE_OPEN;
			}
			counter = counter_reload;
		}
		if(counter == counter_reload - NO_START_DELAY)
		{
			start_state = NO_START;
			LED_GREEN_OFF();
			LED_RED_OFF();
		}
	}
	else if(starter_mode == EXTERNAL)
	{
		if(counter > 0 )
		{
			counter--;
		}
		TM1637_WriteTime(&display_clock, time.Hours, time.Minutes, TM1637_SEPARATOR_ON);
		TM1637_WriteTime(&display_counter, 00, counter, TM1637_SEPARATOR_ON);
		if(counter == 0 && start_state == GATE_OPEN)
		{
			LED_GREEN_ON();
		}
	}
}

void EXTI3_IRQHandler(void)
{
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
	LED_YELLOW_TOGGLE();
	if(starter_mode == AUTO_START)
	{
		if(start_state == GATE_CLOSED)
		{
			//falstart
			LED_RED_ON();
			start_state = FALSTART;
		}
		else if (start_state == GATE_OPEN)
		{
			//valid start
			LED_GREEN_OFF();
			send_time(&start_time, &date);
			start_state = NO_START;
		}
		else if (start_state == GATE_READY)
		{
			LED_RED_ON();
			counter = counter_reload;
			start_state = NO_START;
		}
	}
	if(starter_mode == EXTERNAL)
	{
		if(start_state == GATE_OPEN)
		{
			HAL_RTC_GetTime(&hrtc, (RTC_TimeTypeDef*) &time, RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc, (RTC_DateTypeDef*) &date, RTC_FORMAT_BIN);
			send_time(&time, &date);
			LED_GREEN_OFF();
			start_state = NO_START;
		}
	}
}

void EXTI15_10_IRQHandler(void)
{
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
	if(starter_mode == EXTERNAL)
	{
		LED_GREEN_OFF();
		counter = counter_reload;
		start_state = GATE_OPEN;
	}
	else if(starter_mode == SETUP)
	{
		if(counter == 30) {
			counter = 60;
		}else if(counter == 60) {
			counter = 3;
		} else if(counter == 3) {
			counter = 30;
		}
		TM1637_WriteTime(&display_counter, 00, counter, TM1637_SEPARATOR_ON);
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
