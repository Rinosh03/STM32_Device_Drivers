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
	USART_ConfigureGPIO(usartconfig->usartid);

	if(usartid==USART1_ID)
	{
	/* Enable Clock for USART1*/
		RCC_EnableUSART(USART1_ID);
	/* Set the wordlength */
		if(usartconfig->wordlength == USART_WORDLENGTH_8B)
		{
			USART1->CR1 &=~(USARTx_CR1_M);
		}
		else
		{
			USART1->CR1 |=(USARTx_CR1_M);
		}

	/* Set the stop bits*/
		//Clearing the stopbits
		USART1->CR2 &=~(USARTx_STOPBIT_1_5);
		if(usartconfig->stopbits == USART_STOPBIT_0_5)
		{
			USART1->CR2 |=(USARTx_STOPBIT_0_5);
		}
		else if(usartconfig->stopbits == USART_STOPBIT_1)
		{
			USART1->CR2 |=(USARTx_STOPBIT_1);
		}
		else if(usartconfig->stopbits == USART_STOPBIT_1_5)
		{
			USART1->CR2 |=(USARTx_STOPBIT_1_5);
		}
		else if(usartconfig->stopbits == USART_STOPBIT_2)
		{
			USART1->CR2 |=(USARTx_STOPBIT_2);
		}

	/* Set the Parity */
		if(usartconfig->parity==USART_PARITY_EVEN)
		{
			USART1->CR1 |=(USARTx_CR1_PS);
		}
		else
		{
			USART1->CR1 &=~(USARTx_CR1_PS);
		}

	/* Set the oversampling Flag OVER8*/
		if(usartconfig->oversampling == 8)
		{
			USART1->CR1 |=(USARTx_CR1_OVER8);
			over8val = 1;
		}
		else if(usartconfig->oversampling == 16)
		{
			USART1->CR1 &=~(USARTx_CR1_OVER8);
			over8val = 0;
		}

	/* Set the Baudrate */
	/*Baudrate formula, UsartDiv= Fclk / (8 * (2 - OVER8) * Baudrate) */
		UsartDiv = USART_Periphclockfreq / (8 * (2 - over8val) * usartconfig->baudrate);
		Mantissa = (uint32_t)UsartDiv;
		fraction = UsartDiv - Mantissa;
		if(over8val=1)
		{
			USART1->BRR = (Mantissa<<4) | (fraction * 8 +0.5f);
		}
		else
		{
			USART1->BRR = (Mantissa<<4) | (fraction * 16 +0.5f);

		}
	/* Enable USART Tx and Rx */
	/* Enable USART */
		USART1->CR1 |=(USARTx_CR1_UE) | (USARTx_CR1_TE) | (USARTx_CR1_RE);
	}
	else if (usartid==USART2_ID)
	{
		/* Enable Clock for USART1*/
		RCC_EnableUSART(USART2_ID);
		/* Set the wordlength */
		if(usartconfig->wordlength == USART_WORDLENGTH_8B)
		{
			USART2->CR1 &=~(USARTx_CR1_M);
		}
		else
		{
			USART2->CR1 |=(USARTx_CR1_M);
		}

	/* Set the stop bits*/
	//Clearing the stopbits
		USART1->CR2 &=~(USARTx_STOPBIT_1_5);
		if(usartconfig->stopbits == USART_STOPBIT_0_5)
		{
			USART2->CR2 |=(USARTx_STOPBIT_0_5);
		}
		else if(usartconfig->stopbits == USART_STOPBIT_1)
		{
			USART2->CR2 |=(USARTx_STOPBIT_1);
		}
		else if(usartconfig->stopbits == USART_STOPBIT_1_5)
		{
			USART2->CR2 |=(USARTx_STOPBIT_1_5);
		}
		else if(usartconfig->stopbits == USART_STOPBIT_2)
		{
			USART2->CR2 |=(USARTx_STOPBIT_2);
		}

	/* Set the Parity */
		if(usartconfig->parity==USART_PARITY_EVEN)
		{
			USART2->CR1 |=(USARTx_CR1_PS);
		}
		else
		{
			USART2->CR1 &=~(USARTx_CR1_PS);
		}
	/* Set the oversampling Flag OVER8*/
		if(usartconfig->oversampling == 8)
		{
			USART2->CR1 |=(USARTx_CR1_OVER8);
			over8val = 1;
		}
		else if(usartconfig->oversampling == 16)
		{
			USART2->CR1 &=~(USARTx_CR1_OVER8);
			over8val = 0;
		}
	/* Set the Baudrate */
	/*Baudrate formula, UsartDiv= Fclk / (8 * (2 - OVER8) * Baudrate) */
		UsartDiv = USART_Periphclockfreq / (8 * (2 - over8val) * usartconfig->baudrate);
		Mantissa = (uint32_t)UsartDiv;
		fraction = UsartDiv - Mantissa;
		if(over8val=1)
		{
			USART2->BRR = (Mantissa<<4) | (fraction * 8 +0.5f);
		}
		else
		{
			USART2->BRR = (Mantissa<<4) | (fraction * 16 +0.5f);
		}
	/* Enable USART Tx and Rx */
	/* Enable USART */
			USART2->CR1 |=(USARTx_CR1_UE) | (USARTx_CR1_TE) | (USARTx_CR1_RE);
	}
	else if (usartid=USART6_ID)
	{
	/* Enable Clock for USART1*/
		RCC_EnableUSART(USART6_ID);
	/* Set the wordlength */
		if(usartconfig->wordlength == USART_WORDLENGTH_8B)
		{
			USART6->CR1 &=~(USARTx_CR1_M);
		}
			else
		{
			USART6->CR1 |=(USARTx_CR1_M);
		}
	/* Set the stop bits*/
	//Clearing the stopbits
			USART6->CR2 &=~(USARTx_STOPBIT_1_5);
		if(usartconfig->stopbits == USART_STOPBIT_0_5)
		{
			USART6->CR2 |=(USARTx_STOPBIT_0_5);
		}
		else if(usartconfig->stopbits == USART_STOPBIT_1)
		{
			USART6->CR2 |=(USARTx_STOPBIT_1);
		}
		else if(usartconfig->stopbits == USART_STOPBIT_1_5)
		{
			USART6->CR2 |=(USARTx_STOPBIT_1_5);
		}
			else if(usartconfig->stopbits == USART_STOPBIT_2)
		{
			USART6->CR2 |=(USARTx_STOPBIT_2);
		}

	/* Set the Parity */
		if(usartconfig->parity==USART_PARITY_EVEN)
		{
			USART6->CR1 |=(USARTx_CR1_PS);
		}
		else
		{
			USART6->CR1 &=~(USARTx_CR1_PS);
		}
	/* Set the oversampling Flag OVER8*/
		if(usartconfig->oversampling == 8)
		{
			USART6->CR1 |=(USARTx_CR1_OVER8);
			over8val = 1;
		}
		else if(usartconfig->oversampling == 16)
		{
			USART6->CR1 &=~(USARTx_CR1_OVER8);
			over8val = 0;
		}
	/* Set the Baudrate */
	/*Baudrate formula, UsartDiv= Fclk / (8 * (2 - OVER8) * Baudrate) */
			UsartDiv = USART_Periphclockfreq / (8 * (2 - over8val) * usartconfig->baudrate);
			Mantissa = (uint32_t)UsartDiv;
			fraction = UsartDiv - Mantissa;
		if(over8val=1)
		{
			USART6->BRR = (Mantissa<<4) | (fraction * 8 +0.5f);
		}
		else
		{
			USART6->BRR = (Mantissa<<4) | (fraction * 16 +0.5f);
		}
	/* Enable USART Tx and Rx */
	/* Enable USART */
			USART6->CR1 |=(USARTx_CR1_UE) | (USARTx_CR1_TE) | (USARTx_CR1_RE);
	}
	else
	{

	}
}

void USART_DeInit(USART_ID_T usartid)
{

}

void USART_Transmit(USART_ID_T usartid, uint8_t *data, uint8_t length)
{

}

void USART_Receive(USART_ID_T usartid, uint8_t *data, uint8_t length)
{

}

void USART_Enable(USART_ID_T usartid)
{

}

void USART_Disable(USART_ID_T usartid)
{

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
		GPIOUSARTPINCONFIG.pin=9;
		GPIOUSARTPINCONFIG.alternatefunc=7;
		GPIO_Init(GPIOA, &GPIOUSARTPINCONFIG);

		GPIOUSARTPINCONFIG.pin=10;
		GPIO_Init(GPIOA, &GPIOUSARTPINCONFIG);
		RCC_EnableGPIO(GPIOA);
	}
	/* PA2-> USART2_TX, PA3->USART2_RX; AF->07*/
	else if (usartid==USART2_ID)
	{
		GPIOUSARTPINCONFIG.pin= 2;
		GPIOUSARTPINCONFIG.alternatefunc=7;
		GPIO_Init(GPIOA, &GPIOUSARTPINCONFIG);

		GPIOUSARTPINCONFIG.pin=3;
		GPIO_Init(GPIOA, &GPIOUSARTPINCONFIG);
		RCC_EnableGPIO(GPIOA);
	}
	/* PA11->USART6_TX, PA12->USART6_RX ; AF->08*/
	else if (usartid==USART6_ID)
	{
		GPIOUSARTPINCONFIG.pin=11;
		GPIOUSARTPINCONFIG.alternatefunc=8;
		GPIO_Init(GPIOA, &GPIOUSARTPINCONFIG);

		GPIOUSARTPINCONFIG.pin=12;
		GPIO_Init(GPIOA, &GPIOUSARTPINCONFIG);
		RCC_EnableGPIO(GPIOA);
	}
}
