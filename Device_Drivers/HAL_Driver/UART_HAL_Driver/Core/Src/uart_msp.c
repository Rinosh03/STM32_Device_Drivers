/*
 * uart_msp.c
 *
 *  Created on: 01-Jan-2026
 *      Author: rinos
 */
#include "stm32f4xx_hal.h"
void HAL_UART_MspInit(UART_HandleTypeDef *huart);
void HAL_MspInit(void)
{
	// Set up the priority grouping

	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	// Enable the Exceptions

	SCB->SHCSR |=(0x7<<16);

	// Configure the priority

	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	__HAL_RCC_USART1_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef gpio_uart1;
	//Enable clock of both UART & GPIO

	// Configure the pins

	gpio_uart1.Pin = GPIO_PIN_9 ;
	gpio_uart1.Mode = GPIO_MODE_AF_PP;
	gpio_uart1.Pull = GPIO_NOPULL;
	gpio_uart1.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart1.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOA, &gpio_uart1);
	gpio_uart1.Pin = GPIO_PIN_10 ;
	HAL_GPIO_Init(GPIOA, &gpio_uart1);

	// Enable IRQ and set up priority
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	HAL_NVIC_SetPriority(USART1_IRQn, 15, 0);
}
