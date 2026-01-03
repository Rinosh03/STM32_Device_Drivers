/*
 * main.c
 *
 *  Created on: 01-Jan-2026
 *      Author: rinos
 */


#include "stm32f4xx_hal.h"
#include <string.h>
void SysClock_Config(void);
void UART1_Init(void);
void error_handling();
UART_HandleTypeDef huart1;
char *message = "UUUUUUUUUUUUUUUUU\r\n";
volatile uint32_t checkpoint = 0;
int main()
{
	checkpoint = 1;
	HAL_Init();
	checkpoint = 2;
	SysClock_Config();
	checkpoint = 3;
	UART1_Init();
	checkpoint = 4;
	uint16_t message_length = strlen(message);
	while(1)
	{
		checkpoint = 5;
		HAL_UART_Transmit(&huart1, (uint8_t*)message, message_length, HAL_MAX_DELAY);
		HAL_Delay(1000);
	}
}

void SysClock_Config(void)
{

}

void UART1_Init(void)
{
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 9600 ;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		error_handling();
	}


}

void error_handling()
{
	while(1);
}

