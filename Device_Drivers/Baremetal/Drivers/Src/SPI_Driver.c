/*
 * SPI_Driver.c
 *
 *  Created on: 02-Jan-2026
 *      Author: rinos
 */
#include "SPI_Driver.h"
#include "RCC_Driver.h"
#include "GPIO_Driver.h"

static void SPI_Txe_IRQ_handling(SPI_Handle_T *pSPIhandle);
static void SPI_Rxe_IRQ_handling(SPI_Handle_T *pSPIhandle);
static void SPI_Error_IRQ_handling(SPI_Handle_T *pSPIhandle);

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

uint8_t SPI_Tx_IT(SPI_Handle_T *pSPIhandle, uint8_t *pTxbuffer, uint32_t len)
{
	uint8_t state;
	state=pSPIhandle->TxState;
	if(state !=SPI_BUSY_IN_TX)
	{
		// Initialize Txbuufer and len to SPIhandle
		pSPIhandle->pTxBuffer=pTxbuffer;
		pSPIhandle->TxLen=len;
		// Set Tx state to busy so that no other code can take over same SPI peripheral
		pSPIhandle->TxState = SPI_BUSY_IN_TX;
		// Enable TXEIE
		pSPIhandle->pSPIx->CR2 |=(SPI_CR2_TXEIE);
	}
	return state;
}
uint8_t SPI_Rx_IT(SPI_Handle_T *pSPIhandle, uint8_t *pRxbuffer, uint32_t len)
{
	uint8_t state;
	state=pSPIhandle->RxState;
	if(state !=SPI_BUSY_IN_RX)
	{
		// Initialize Rxbuffer and len to SPIhandle
		pSPIhandle->pRxBuffer=pRxbuffer;
		pSPIhandle->RxLen=len;
		// Set Rx state to busy so that no other code can take over same SPI peripheral
		pSPIhandle->RxState = SPI_BUSY_IN_RX;
		// Enable RXEIE
		pSPIhandle->pSPIx->CR2 |=(SPI_CR2_RXEIE);
	}
	return state;
}

/* This function is used for configuring the interrupt */

void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{

	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			//program ISER0 register
			*NVIC_ISER0 |= ( 1 << IRQNumber );

		}else if(IRQNumber > 31 && IRQNumber < 64 ) //32 to 63
		{
			//program ISER1 register
			*NVIC_ISER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
			//program ISER2 register //64 to 95
			*NVIC_ISER3 |= ( 1 << (IRQNumber % 64) );
		}
	}else
	{
		if(IRQNumber <= 31)
		{
			//program ICER0 register
			*NVIC_ICER0 |= ( 1 << IRQNumber );
		}else if(IRQNumber > 31 && IRQNumber < 64 )
		{
			//program ICER1 register
			*NVIC_ICER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 6 && IRQNumber < 96 )
		{
			//program ICER2 register
			*NVIC_ICER3 |= ( 1 << (IRQNumber % 64) );
		}
	}

}

/* This function is used for setting the priority of the interrupt */

void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority)
{
	//1. first lets find out the ipr register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section  = IRQNumber %4 ;

	uint8_t shift_amount = ( 8 * iprx_section) + ( 8 - NO_PR_BITS_IMPLEMENTED) ;

	*(  NVIC_PR_BASE_ADDR + iprx ) |=  ( IRQPriority << shift_amount );

}

/* This function handles the interrupt operation */

void SPI_IRQHandling(SPI_Handle_T *pSPIhandle)
{
	// First lets check TXE
	uint8_t temp1, temp2;
	temp1 = pSPIhandle->pSPIx->SR & (SPI_SR_TXE);
	temp2 = pSPIhandle->pSPIx->CR2 & (SPI_CR2_TXEIE);
	if(temp1 && temp2)
	{
		SPI_Txe_IRQ_handling(pSPIhandle);
	}
	// Then RXNE
	temp1 = pSPIhandle->pSPIx->SR & (SPI_SR_RXNE);
	temp2 = pSPIhandle->pSPIx->CR2 & (SPI_CR2_RXEIE);
	if(temp1 && temp2)
	{
		SPI_Rxe_IRQ_handling(pSPIhandle);
	}

	// Then OVRRUN
	temp1 = pSPIhandle->pSPIx->SR & (SPI_SR_OVR);
	temp2 = pSPIhandle->pSPIx->CR2 & (SPI_CR2_ERRIE);
	if(temp1 && temp2)
	{
		SPI_Error_IRQ_handling(pSPIhandle);
	}

}

/* Interrupt helper functions */
static void SPI_Txe_IRQ_handling(SPI_Handle_T *pSPIhandle)
{
	if(pSPIhandle->pSPIx->CR1 & SPI_CR1_DFF)
	{
		pSPIhandle->pSPIx->DR = *((uint16_t*) pSPIhandle->pTxBuffer);
		pSPIhandle->pTxBuffer+=2;
		pSPIhandle->TxLen-=2;
	}
	else
	{
		pSPIhandle->pSPIx->DR = *pSPIhandle->pTxBuffer;
		pSPIhandle->pTxBuffer++;
		pSPIhandle->TxLen--;
	}
	if(! pSPIhandle->TxLen)
	{
		SPI_Close_TX(pSPIhandle);
		SPI_EventCallBack(pSPIhandle, SPI_EVENT_TX_CMPLT);
	}
}
static void SPI_Rxe_IRQ_handling(SPI_Handle_T *pSPIhandle)
{
	if(pSPIhandle->pSPIx->CR1 & SPI_CR1_DFF)
	{
		*((uint16_t*) pSPIhandle->pRxBuffer) = pSPIhandle->pSPIx->DR;
		pSPIhandle->RxLen-=2;
		(uint16_t*) pSPIhandle->pRxBuffer++;
	}
	else
	{
		*pSPIhandle->pRxBuffer = pSPIhandle->pSPIx->DR;
		pSPIhandle->RxLen--;
		pSPIhandle->pRxBuffer++;
	}
	if(! pSPIhandle->RxLen)
	{
		SPI_Close_Rx(pSPIhandle);
		SPI_EventCallBack(pSPIhandle, SPI_EVENT_RX_CMPLT);
	}
}
static void SPI_Error_IRQ_handling(SPI_Handle_T *pSPIhandle)
{
	uint8_t temp;
	// Clear OVR Flag
	if(pSPIhandle->TxState != SPI_BUSY_IN_TX)
	{
		temp=pSPIhandle->pSPIx->DR;
		temp=pSPIhandle->pSPIx->SR;
	}
		(void) temp;
		SPI_EventCallBack(pSPIhandle, SPI_EVENT_OVR_ERR);
	// Inform application

}
void SPI_ClearOVRFlag(SPI_RegDef *pSPIx)
{
	uint8_t temp;
	// Clear OVR Flag
	temp=pSPIx->DR;
	temp=pSPIx->SR;
	(void) temp; // to remove warning
}
void SPI_Close_TX(SPI_Handle_T *pSPIhandle)
{
	pSPIhandle->pSPIx->CR2 &= ~(SPI_CR2_TXEIE);
	pSPIhandle->pTxBuffer = NULL;
	pSPIhandle->TxLen = 0;
	pSPIhandle->TxState = SPI_READY;
}
void SPI_Close_Rx(SPI_Handle_T *pSPIhandle)
{
	pSPIhandle->pSPIx->SR &= ~(1<< SPI_SR_RXNE);
	pSPIhandle->RxLen = 0;
	pSPIhandle->RxState = SPI_READY;
	pSPIhandle->pRxBuffer = NULL;
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
void __weak SPI_EventCallBack(SPI_Handle_T *pSPIhandle, uint8_t app_ev)
{

	}
