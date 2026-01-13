/*
 * SPI_2_EX.c
 *
 *  Created on: 11-Jan-2026
 *      Author: rinos
 */

#include <stdint.h>
#include "GPIO_Driver.h"
#include "RCC_Driver.h"
#include "SYSCFG_Driver.h"
#include "EXTI_Driver.h"
#include "NVIC_Driver.h"
#include "USART_Driver.h"
#include "SPI_Driver.h"
#include <string.h>

/* SPI2 Pin config
 SPI2_MOSI-> PB15
 SPI2_MISO-> PB14
 SPI2_NSS-> PB12
 SPI2_SCLK -> PB13
 AF -> AF05
 */

void delay() {
	for (uint32_t i = 0; i < 1777777; i++)
		;
}

/* This function is used for initializing the GPIO Button */

GPIO_Pinconfig Pushbutton =
{
			.pin = 0,
			.otype = GPIO_OTYPE_PP,
			.mode = GPIO_MODE_INPUT,
			.ospeed = GPIO_OSPEED_HIGH,
			.pupdr = GPIO_PULL_UP,
			.alternatefunc = 0,
};

/* This function is used for initializing the values for SPI2 peripheral*/

SPI_Handle_T SPI2handle;
void SPI2_Init() {

	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.DFF = SPI_DFF_8_BIT;
	SPI2handle.SPIConfig.Speed = SPI_SCLK_SPEED_DIV128;
	SPI2handle.SPIConfig.CPOL = SPI_CPOL_1;
	SPI2handle.SPIConfig.CPHA = SPI_CPHA_1;
	SPI2handle.SPIConfig.SSM = SPI_SSM_HW;

	SPI_Init(&SPI2handle);
}

/* Main Function*/

int main(void)
{
	SPI2handle.pSPIx = SPI2;
	char user_data[] = "ABCD";
	RCC_EnableGPIO(GPIOA);
	GPIO_Init(GPIOA, &Pushbutton);
	while(1)
	{
		while(!(GPIO_ReadPin(GPIOA, 0)));
		delay();
		SPI2_Init();
		SPI_GPIO_Config(&SPI2handle);
		uint8_t data_len=strlen(user_data);
		SPI_Tx(SPI2, &data_len, 1);
		SPI_Tx(SPI2, (uint8_t*) user_data, strlen(user_data));
		while(SPI2->SR & SPI_BSY_FLAG);
		SPI_DeInit(&SPI2handle);
	}
	return 0;

}

