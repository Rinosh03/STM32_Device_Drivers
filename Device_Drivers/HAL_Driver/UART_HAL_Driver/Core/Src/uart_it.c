/*
 * uart_it.c
 *
 *  Created on: 01-Jan-2026
 *      Author: rinos
 */

#include "main.h"
#include "stm32f4xx_hal.h"
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

