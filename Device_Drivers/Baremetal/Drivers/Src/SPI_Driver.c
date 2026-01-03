/*
 * SPI_Driver.c
 *
 *  Created on: 02-Jan-2026
 *      Author: rinos
 */
#include "SPI_Driver.h"
#include "RCC_Driver.h"

/* This function is used for initializing the peripherals of SPI driver */

void SPI_Init(SPI_Handle_T *pSPIhandle)
{
	// Enable Clock
	RCC_EnableSPI(pSPIhandle->pSPIx);
	// Initiate Device Mode
	pSPIhandle->pSPIx->CR1 |=(pSPIhandle->SPIConfig.DeviceMode<<2);
	// Configure the bus type
	if(pSPIhandle->SPIConfig.BusConfig == SPI_BUS_CONFIG_FD )
	{
		pSPIhandle->pSPIx->CR1 &= ~(1<<15);
	}
	else if(pSPIhandle->SPIConfig.BusConfig == SPI_BUS_CONFIG_HD)
	{
		pSPIhandle->pSPIx->CR1 |=(1<<15);
	}
	else if(pSPIhandle->SPIConfig.BusConfig == SPI_BUS_CONFIG_SIMPLEX_RX_ONLY)
	{
		pSPIhandle->pSPIx->CR1 &= ~(1<<15);
		pSPIhandle->pSPIx->CR1 |=(1<<10);
	}
	// Set the Data Frame Format
	pSPIhandle->pSPIx->CR1 |=(pSPIhandle->SPIConfig.DFF<<11);
	//Set the CPOL pin
	pSPIhandle->pSPIx->CR1 |=(pSPIhandle->SPIConfig.CPOL<<1);
	//Set the CPHA pin
	pSPIhandle->pSPIx->CR1 |=(pSPIhandle->SPIConfig.CPHA<<0);
	// Configure the baud rate/ FCLK/ Speed
	pSPIhandle->pSPIx->CR1 |=(pSPIhandle->SPIConfig.Speed<<3);
	// Set the Slave management
	pSPIhandle->pSPIx->CR1 |=(pSPIhandle->SPIConfig.SSM<<9);
	// Enable SPI
	pSPIhandle->pSPIx->CR1 |= (1<<6);
}

/* This function is used for deinitializing all the peripherals associated with SPIdriver */

void SPI_DeInit(SPI_Handle_T *pSPIhandle)
{
	// Disable Clock
	RCC_DisableSPI(pSPIhandle->pSPIx);
	pSPIhandle->pSPIx->CR1 &= ~(1<<6);

}

/* This function is used for transmitting the data from One device/port to another */

void SPI_Tx(SPI_RegDef *pSPIx, uint8_t *pTxbuffer, uint32_t len)
{
	while(len>0)
	{
		while(!(pSPIx->SR & SPI_SR_TXE));
		//Set the DFF
		if(pSPIx->CR1 & SPI_CR1_DFF)
		{
			pSPIx->DR = *((uint16_t*) pTxbuffer);
			len--;
			len--;
		}
		else
		{
			pSPIx->DR = *pTxbuffer;
			len--;
		}
	}

}

/* This function is used for Receiving the data */

void SPI_Rx(SPI_RegDef *pSPIx, uint8_t *pTxbuffer, uint32_t len)
{

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

