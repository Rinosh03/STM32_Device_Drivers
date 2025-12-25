/*
 * USART.c
 *
 *  Created on: 22-Dec-2025
 *      Author: rinos
 */
#include "USART_Driver.h"
#include "GPIO_Driver.h"
#include "RCC_Driver.h"


void USART_Init(USART_Struct_T *usartconfig)
{
	float UsartDiv, fraction; uint8_t over8val; uint32_t Mantissa;
	USART_RegDef *pUsart;
	pUsart = usartconfig->USARTInstance;
	USART_ConfigureGPIO(usartconfig->usartid);
	/* Enable Clock for USART1*/
	RCC_EnableUSART(usartconfig->usartid);
	/* Set the wordlength */
	if(usartconfig->wordlength == USART_WORDLENGTH_8B)
		{
			pUsart->CR1 &= ~USARTx_CR1_M;
		}
	else
		{
			pUsart->CR1 |= USARTx_CR1_M;
		}
	/* Set the stop bits*/
	//Clearing the stopbits
	pUsart->CR2 &= ~USARTx_STOPBIT_1_5;
	if(usartconfig->stopbits == USART_STOPBIT_0_5)
	{
		pUsart->CR2 |= USARTx_STOPBIT_0_5;
	}
	else if(usartconfig->stopbits == USART_STOPBIT_1)
	{
		pUsart->CR2 |= USARTx_STOPBIT_1;
	}
	else if(usartconfig->stopbits == USART_STOPBIT_1_5)
	{
		pUsart->CR2 |= USARTx_STOPBIT_1_5;
	}
	else if(usartconfig->stopbits == USART_STOPBIT_2)
	{
		pUsart->CR2 |= USARTx_STOPBIT_2;
	}
	/* Enable/Disable Parity*/
	if(usartconfig->parity !=USART_PARITY_NONE)
	{
		/* Enable parity*/
		pUsart->CR1 |= (1<<10);
		/* Set the Parity */
		if(usartconfig->parity==USART_PARITY_EVEN)
		{
			pUsart->CR1 &= ~USARTx_CR1_PS;
		}
		else if(usartconfig->parity==USART_PARITY_ODD)
		{
			pUsart->CR1 |= USARTx_CR1_PS;
		}
	}

	/* Set the oversampling Flag OVER8*/
	if(usartconfig->oversampling == 8)
	{
		pUsart->CR1 |= USARTx_CR1_OVER8;
		over8val = 1;
	}
	else if(usartconfig->oversampling == 16)
	{
		pUsart->CR1 &= ~USARTx_CR1_OVER8;
		over8val = 0;
	}
	/* Set the Baudrate */
	/*Baudrate formula, UsartDiv= Fclk / (8 * (2 - OVER8) * Baudrate) */
	UsartDiv = ((float)USART_Periphclockfreq / (float)(8 * (2 - over8val) * usartconfig->baudrate));
	Mantissa = (uint32_t)UsartDiv;
	fraction = UsartDiv - Mantissa;
	if(over8val == 1)
	{
		pUsart->BRR = (Mantissa<<4) | (uint8_t)(fraction * 8 +0.5f);
	}
	else
	{
		pUsart->BRR = (Mantissa<<4) | (uint8_t)(fraction * 16 +0.5f);
	}
	/* Enable USART Tx and Rx */
	/* Enable USART */
	pUsart->CR1 |=(USARTx_CR1_UE) | (USARTx_CR1_TE) | (USARTx_CR1_RE);
}

void USART_DeInit(USART_Struct_T *usartconfig)
{
	if(usartconfig->usartid == USART1_ID)
	{

		RCC_DisableUSART(USART1_ID);

	}
	else if (usartconfig->usartid == USART2_ID)
	{

		RCC_DisableUSART(USART2_ID);

	}
	else if (usartconfig->usartid == USART6_ID)
	{

		RCC_DisableUSART(USART6_ID);
	}
	usartconfig->USARTInstance->CR1 &= ~(USARTx_CR1_UE);
}

void USART_Transmit(USART_Struct_T *usartconfig, uint8_t *data, uint8_t length)
{
	USART_RegDef *pUsart;
	pUsart = usartconfig->USARTInstance;

	if(!usartconfig || !pUsart || !data || !length)
		return;

	for(uint32_t i=0; i<length; i++)
	{
		while(!(pUsart->SR & USARTx_SR_TXE));
		pUsart->DR = data[i] & 0xff;
	}
	while(!(pUsart->SR & USARTx_SR_TC));
}

void USART_Receive(USART_Struct_T *usartconfig, uint8_t *data, uint8_t length)
{
	USART_RegDef *pUsart;
	pUsart = usartconfig->USARTInstance;

	if(!usartconfig || !pUsart || !data || !length)
		return;

	for(uint32_t i=0; i<length; i++)
	{
		while(!(pUsart->SR & USARTx_SR_RXNE));
		data[i] = pUsart->DR &0xFF;
	}
}

void USART_Enable(USART_Struct_T *usartconfig)
{
	USART_RegDef *pUsart;
	pUsart = usartconfig->USARTInstance;

	if(!usartconfig || !pUsart)
	return;

	pUsart->CR1 |= USARTx_CR1_UE;
}

void USART_Disable(USART_Struct_T *usartconfig)
{
	USART_RegDef *pUsart;
	pUsart = usartconfig->USARTInstance;

	if(!usartconfig || !pUsart)
	return;

	pUsart->CR1 &= ~(USARTx_CR1_UE);
}

void USART_ConfigureGPIO(USART_ID_T usartid)
{
	GPIO_Pinconfig GPIOUSARTPINCONFIG =
	{
			.pin=0,
			.mode= GPIO_MODE_ALT,
			.ospeed=GPIO_OSPEED_LOW,
			.otype=GPIO_OTYPE_PP,
			.pupdr=GPIO_NOPUPDR,
			.alternatefunc=0
	};
	/* PA9->UART1_TX, PA10->USART1_RX ; AF->7*/
	if(usartid==USART1_ID)
	{
		RCC_EnableGPIO(GPIOA);
		GPIOUSARTPINCONFIG.pin=9;
		GPIOUSARTPINCONFIG.alternatefunc=7;
		GPIO_Init(GPIOA, &GPIOUSARTPINCONFIG);

		GPIOUSARTPINCONFIG.pin=10;
		GPIO_Init(GPIOA, &GPIOUSARTPINCONFIG);
	}
	/* PA2-> USART2_TX, PA3->USART2_RX; AF->07*/
	else if (usartid==USART2_ID)
	{
		RCC_EnableGPIO(GPIOA);
		GPIOUSARTPINCONFIG.pin= 2;
		GPIOUSARTPINCONFIG.alternatefunc=7;
		GPIO_Init(GPIOA, &GPIOUSARTPINCONFIG);

		GPIOUSARTPINCONFIG.pin=3;
		GPIO_Init(GPIOA, &GPIOUSARTPINCONFIG);
	}
	/* PA11->USART6_TX, PA12->USART6_RX ; AF->08*/
	else if (usartid==USART6_ID)
	{
		RCC_EnableGPIO(GPIOA);
		GPIOUSARTPINCONFIG.pin=11;
		GPIOUSARTPINCONFIG.alternatefunc=8;
		GPIO_Init(GPIOA, &GPIOUSARTPINCONFIG);

		GPIOUSARTPINCONFIG.pin=12;
		GPIO_Init(GPIOA, &GPIOUSARTPINCONFIG);
	}
	else
	{

	}
}
