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

	if(usartconfig->usartid==USART1_ID)
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

		/* Enable/Disable Parity*/
		if(usartconfig->parity !=USART_PARITY_NONE)
		{
		/* Enable parity*/
			USART1->CR1 |=(1<<10);
			/* Set the Parity */
			USART1->CR1 &=~(USARTx_CR1_PS);
			if(usartconfig->parity==USART_PARITY_EVEN)
			{
				USART1->CR1 &=~(USARTx_CR1_PS);
			}
			else if(usartconfig->parity==USART_PARITY_ODD)
				{
					USART1->CR1 |=(USARTx_CR1_PS);
				}
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
		UsartDiv = ((float)USART_Periphclockfreq / (float)(8 * (2 - over8val) * usartconfig->baudrate));
		Mantissa = (uint32_t)UsartDiv;
		fraction = UsartDiv - Mantissa;
		if(over8val == 1)
		{
			USART1->BRR = (Mantissa<<4) | (uint8_t)(fraction * 8 +0.5f);
		}
		else
		{
			USART1->BRR = (Mantissa<<4) | (uint8_t)(fraction * 16 +0.5f);

		}
	/* Enable USART Tx and Rx */
	/* Enable USART */
		USART1->CR1 |=(USARTx_CR1_UE) | (USARTx_CR1_TE) | (USARTx_CR1_RE);
	}
	else if (usartconfig->usartid==USART2_ID)
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
		USART2->CR2 &=~(USARTx_STOPBIT_1_5);
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

		/* Enable/Disable Parity*/
		if(usartconfig->parity !=USART_PARITY_NONE)
		{
			/* Enable parity*/
			USART2->CR1 |=(1<<10);

		/* Set the Parity */
			USART2->CR1 &=~(USARTx_CR1_PS);
		if(usartconfig->parity==USART_PARITY_EVEN)
		{
			USART2->CR1 &=~(USARTx_CR1_PS);
		}
		else if(usartconfig->parity==USART_PARITY_ODD)
		{
			USART2->CR1 |=(USARTx_CR1_PS);
		}
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
		UsartDiv = ((float)USART_Periphclockfreq / ((float)8 * (2 - over8val) * usartconfig->baudrate));
		Mantissa = (uint32_t)UsartDiv;
		fraction = UsartDiv - Mantissa;
		if(over8val == 1)
		{
			USART2->BRR = (Mantissa<<4) | (uint8_t)(fraction * 8 +0.5f);
		}
		else
		{
			USART2->BRR = (Mantissa<<4) | (uint8_t)(fraction * 16 +0.5f);
		}
	/* Enable USART Tx and Rx */
	/* Enable USART */
			USART2->CR1 |=(USARTx_CR1_UE) | (USARTx_CR1_TE) | (USARTx_CR1_RE);
	}
	else if (usartconfig->usartid == USART6_ID)
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

		/* Enable/Disable Parity*/
		if(usartconfig->parity !=USART_PARITY_NONE)
		{
			/* Enable parity*/
			USART6->CR1 |=(1<<10);
			/* Set the Parity */
			USART6->CR1 &=~(USARTx_CR1_PS);
			if(usartconfig->parity==USART_PARITY_EVEN)
			{
				USART6->CR1 &=~(USARTx_CR1_PS);
			}
			else if(usartconfig->parity==USART_PARITY_ODD)
			{
				USART6->CR1 |=(USARTx_CR1_PS);
			}
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
			UsartDiv = ((float)USART_Periphclockfreq / ((float)8 * (2 - over8val) * usartconfig->baudrate));
			Mantissa = (uint32_t)UsartDiv;
			fraction = UsartDiv - Mantissa;
		if(over8val == 1)
		{
			USART6->BRR = (Mantissa<<4) | (uint8_t)(fraction * 8 +0.5f);
		}
		else
		{
			USART6->BRR = (Mantissa<<4) | (uint8_t)(fraction * 16 +0.5f);
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
	if(usartid == USART1_ID)
	{
		USART1->CR1 &=~(USARTx_CR1_UE);
		RCC_DisableUSART(USART1_ID);

	}
	else if (usartid == USART2_ID)
	{
		USART2->CR1 &=~(USARTx_CR1_UE);
		RCC_DisableUSART(USART2_ID);

	}
	else if (usartid == USART6_ID)
	{
		USART6->CR1 &=~(USARTx_CR1_UE);
		RCC_DisableUSART(USART6_ID);
	}

}

void USART_Transmit(USART_ID_T usartid, uint8_t *data, uint8_t length)
{
	if(usartid==USART1_ID)
	{
		for(uint32_t i=0; i<length; i++)
		{
			while(!(USART1->SR & USARTx_SR_TXE));
			USART1->DR = data[i] & 0xff;
		}
		while(!(USART1->SR & USARTx_SR_TC));
	}
	else if(usartid==USART2_ID)
	{
		for(uint32_t i=0; i<length; i++)
		{
			while(!(USART2->SR & USARTx_SR_TXE));
			USART2->DR = data[i] & 0xff;

		}
		while(!(USART2->SR & USARTx_SR_TC));
	}
	else if(usartid==USART6_ID)
	{
		for(uint32_t i=0; i<length; i++)
		{
			while(!(USART6->SR & USARTx_SR_TXE));
			USART6->DR = data[i] & 0xFF;
		}
		while(!(USART6->SR & USARTx_SR_TC));
	}
}

void USART_Receive(USART_ID_T usartid, uint8_t *data, uint8_t length)
{
	if(usartid == USART1_ID)
	{
		for(uint32_t i=0; i<length; i++)
		{
			while(!(USART1->SR & USARTx_SR_RXNE));
			data[i] = USART1->DR &0xFF;
		}

	}
	else if (usartid == USART2_ID)
	{
		for(uint32_t i=0; i<length; i++)
		{
			while(!(USART2->SR & USARTx_SR_RXNE));
			data[i] = USART2->DR &0xFF;
		}

	}
	else if (usartid == USART6_ID)
	{
		for(uint32_t i=0; i<length; i++)
		{
			while(!(USART6->SR & USARTx_SR_RXNE));
			data[i] = USART6->DR &0xFF;
		}
	}

}

void USART_Enable(USART_ID_T usartid)
{
	if(usartid == USART1_ID)
	{
		USART1->CR1 |=(USARTx_CR1_UE);
	}
	else if (usartid == USART2_ID)
	{
		USART2->CR1 |=(USARTx_CR1_UE);
	}
	else if (usartid == USART6_ID)
	{
		USART6->CR1 |=(USARTx_CR1_UE);
	}

}

void USART_Disable(USART_ID_T usartid)
{
	if(usartid == USART1_ID)
	{
		USART1->CR1 &= ~(USARTx_CR1_UE);

	}
	else if (usartid == USART2_ID)
	{
		USART2->CR1 &= ~(USARTx_CR1_UE);
	}
	else if (usartid == USART6_ID)
	{
		USART6->CR1 &= ~(USARTx_CR1_UE);
	}
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
}
