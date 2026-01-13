/*
 * SPI_Driver.c
 *
 *  Created on: 02-Jan-2026
 *      Author: rinos
 */
#include "SPI_Driver.h"
#include "RCC_Driver.h"
#include "GPIO_Driver.h"

/* This function is used for initializing the peripherals of SPI driver */

void SPI_Init(SPI_Handle_T *pSPIhandle)
{
	// Enable Clock
	RCC_EnableSPI(pSPIhandle->pSPIx);
	uint32_t temp = 0;
	pSPIhandle->pSPIx->I2SCFGR &= ~(1U << 11);
	// Configure the bus type
	if(pSPIhandle->SPIConfig.BusConfig == SPI_BUS_CONFIG_FD )
	{
		temp &= ~(1<<15);
	}
	else if(pSPIhandle->SPIConfig.BusConfig == SPI_BUS_CONFIG_HD)
	{
		temp |=(1<<15);
	}
	else if(pSPIhandle->SPIConfig.BusConfig == SPI_BUS_CONFIG_SIMPLEX_RX_ONLY)
	{
		temp &= ~(1<<15);
		temp |=(1<<10);
	}
	// Set the Data Frame Format
	temp |=(pSPIhandle->SPIConfig.DFF<<11);
	//Set the CPOL pin
	temp |=(pSPIhandle->SPIConfig.CPOL<<1);
	//Set the CPHA pin
	temp |=(pSPIhandle->SPIConfig.CPHA<<0);
	// Configure the baud rate/ FCLK/ Speed
	temp |=(pSPIhandle->SPIConfig.Speed<<3);
	// Set the Slave management
	temp |=(pSPIhandle->SPIConfig.SSM<<9);
	pSPIhandle->pSPIx->CR1 = temp;
	// Set the Slave management (SSM)
	if (pSPIhandle->SPIConfig.SSM == SPI_SSM_SW)
	{
	    pSPIhandle->pSPIx->CR1 |= (1U << 9);  // SSM = 1
	    pSPIhandle->pSPIx->CR1 |= (1U << 8);  // SSI = 1  (IMPORTANT!)
	}
	else
	{
	    pSPIhandle->pSPIx->CR1 &= ~(1U << 9); // SSM = 0
	    pSPIhandle->pSPIx->CR2 |= (1U << 2 ); // SSOE=1
	}
	// Initiate Device Mode
	if(pSPIhandle->SPIConfig.DeviceMode == SPI_DEVICE_MODE_MASTER)
	{
		pSPIhandle->pSPIx->CR1 |= SPI_CR1_MSTR;
	}
	else
	{
		pSPIhandle->pSPIx->CR1 &= ~SPI_CR1_MSTR;
	}
	// Enable SPI
	pSPIhandle->pSPIx->CR1 |= SPI_CR1_SPE;
}

/* This function is used for deinitializing all the peripherals associated with SPIdriver */

void SPI_DeInit(SPI_Handle_T *pSPIhandle)
{
	// Disable Clock
	RCC_DisableSPI(pSPIhandle->pSPIx);
	pSPIhandle->pSPIx->CR1 &= ~SPI_CR1_SPE;

}

uint8_t SPI_GetFlagStatus(SPI_RegDef *pSPIx, uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	else
	{
		return FLAG_RESET;
	}

}
/* This function is used for transmitting the data from One device/port to another */

void SPI_Tx(SPI_RegDef *pSPIx, uint8_t *pTxbuffer, uint32_t len)
{
	while(len>0)
	{
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);
		//Set the DFF
		if(pSPIx->CR1 & SPI_CR1_DFF)
		{
			pSPIx->DR = *((uint16_t*) pTxbuffer);
			pTxbuffer+=2;
			len-=2;
		}
		else
		{
			pSPIx->DR = *pTxbuffer;
			pTxbuffer++;
			len--;
		}
	}

}

/* This function is used for Receiving the data */

void SPI_Rx(SPI_RegDef *pSPIx, uint8_t *pRxbuffer, uint32_t len)
{
	while(len>0)
	{
		while(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == FLAG_RESET);
		//Set the DFF
			if(pSPIx->CR1 & SPI_CR1_DFF)
			{
				*((uint16_t*) pRxbuffer) = pSPIx->DR;
				len-=2;
				(uint16_t*) pRxbuffer++;
			}
			else
			{
				*pRxbuffer = pSPIx->DR;
				len--;
				pRxbuffer++;
			}
		}
}

/* This function is used for configuring the interrupt */

void SPI_IRQInterruptConfig(uint8_t IRQn, uint8_t ENorDI)
{

}

/* This function is used for setting the priority of the interrupt */

void SPI_IRQPriorityConfig(uint8_t IRQn, uint32_t IRQPriority)
{

}

/* This function handles the interrupt operation */

void SPI_IRQHandling(SPI_Handle_T *pSPIhandle)
{

}

/* This function is used for configuring GPIO pins for SPI */
void SPI_GPIO_Config(SPI_Handle_T *pSPId)
{
	GPIO_Pinconfig SPI_GPIO_Config =
	{
			.mode = GPIO_MODE_ALT,
			.otype = GPIO_OTYPE_PP,
			.ospeed = GPIO_OSPEED_FAST,
			.pupdr = GPIO_PULL_UP,
			.alternatefunc = 0
	};
	if(pSPId->pSPIx == SPI1 ) // MOSI-> PA7 MISO-> PA6 NSS-> PA4 SCLK->PA5; AF->05
	{
		RCC_EnableGPIO(GPIOA);
		SPI_GPIO_Config.pin = 7; //MOSI
		SPI_GPIO_Config.alternatefunc = 5;
		GPIO_Init(GPIOA, &SPI_GPIO_Config);
		SPI_GPIO_Config.pin = 6;
		GPIO_Init(GPIOA, &SPI_GPIO_Config);
		SPI_GPIO_Config.pin = 4;
		GPIO_Init(GPIOA, &SPI_GPIO_Config);
		SPI_GPIO_Config.pin = 5;
		GPIO_Init(GPIOA, &SPI_GPIO_Config);

	}
	else if(pSPId->pSPIx == SPI2 ) //MOSI-> PB15, MISO-> PB14, NSS-> PB12, SCLK -> PB13; AF->05
	{
		RCC_EnableGPIO(GPIOB);
		SPI_GPIO_Config.pin = 15;
		SPI_GPIO_Config.alternatefunc = 5;
		GPIO_Init(GPIOB, &SPI_GPIO_Config);
		SPI_GPIO_Config.pin = 14;
		GPIO_Init(GPIOB, &SPI_GPIO_Config);
		SPI_GPIO_Config.pin = 12;
		GPIO_Init(GPIOB, &SPI_GPIO_Config);
		SPI_GPIO_Config.pin = 13;
		GPIO_Init(GPIOB, &SPI_GPIO_Config);
	}
	else if(pSPId->pSPIx == SPI3 ) //MOSI-> PB5, MISO-> PB4, NSS-> PA15, SCLK -> PB3; AF->06
	{
		RCC_EnableGPIO(GPIOB);
		RCC_EnableGPIO(GPIOA);
		SPI_GPIO_Config.pin = 5; //MOSI
		SPI_GPIO_Config.alternatefunc = 6;
		GPIO_Init(GPIOB, &SPI_GPIO_Config);
		SPI_GPIO_Config.pin = 4;
		GPIO_Init(GPIOB, &SPI_GPIO_Config);
		SPI_GPIO_Config.pin = 15;
		GPIO_Init(GPIOA, &SPI_GPIO_Config);
		SPI_GPIO_Config.pin = 3;
		GPIO_Init(GPIOB, &SPI_GPIO_Config);
	}
	else if(pSPId->pSPIx == SPI4 ) //MOSI-> PE6, MISO-> PE5, NSS-> PE4, SCLK -> PE2; AF->05
	{
		RCC_EnableGPIO(GPIOE);
		SPI_GPIO_Config.pin = 6;
		SPI_GPIO_Config.alternatefunc = 5;
		GPIO_Init(GPIOE, &SPI_GPIO_Config);
		SPI_GPIO_Config.pin = 5;
		GPIO_Init(GPIOE, &SPI_GPIO_Config);
		SPI_GPIO_Config.pin = 4;
		GPIO_Init(GPIOE, &SPI_GPIO_Config);
		SPI_GPIO_Config.pin = 2;
		GPIO_Init(GPIOE, &SPI_GPIO_Config);
	}
	else if(pSPId->pSPIx == SPI5 ) //MOSI-> PE14, MISO-> PE13, NSS-> PE11, SCLK -> PE12; AF->06
	{
		RCC_EnableGPIO(GPIOE);
		SPI_GPIO_Config.pin = 14;
		SPI_GPIO_Config.alternatefunc = 6;
		GPIO_Init(GPIOE, &SPI_GPIO_Config);
		SPI_GPIO_Config.pin = 13;
		GPIO_Init(GPIOE, &SPI_GPIO_Config);
		SPI_GPIO_Config.pin = 11;
		GPIO_Init(GPIOE, &SPI_GPIO_Config);
		SPI_GPIO_Config.pin = 12;
		GPIO_Init(GPIOE, &SPI_GPIO_Config);
	}
}
