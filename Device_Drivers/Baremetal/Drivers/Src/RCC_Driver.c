#include "RCC_Driver.h"

void RCC_EnableGPIO(GPIO_RegDef *port)
{
    if (port == GPIOA)
    	{
        	RCC->AHB1ENR |= (1 << 0);
    	}
    else if (port == GPIOB)
    	{
    		RCC->AHB1ENR |= (1 << 1);
    	}
    else if (port == GPIOC)
    	{
        	RCC->AHB1ENR |= (1 << 2);
    	}
    else if (port == GPIOD)
    	{
        	RCC->AHB1ENR |= (1 << 3);
    	}
    else if (port == GPIOE)
    	{
        	RCC->AHB1ENR |= (1 << 4);
    	}
    else if (port == GPIOH)
    	{
        	RCC->AHB1ENR |= (1 << 7);
    	}
}

/* This function disables the clock of the GPIO port */

void RCC_DisableGPIO(GPIO_RegDef *port)
{
	 if (port == GPIOA)
	    {
	        RCC->AHB1ENR &= ~(1 << 0);
	    }
	    else if (port == GPIOB)
	    {
	        RCC->AHB1ENR &= ~(1 << 1);
	    }
	    else if (port == GPIOC)
	    {
	        RCC->AHB1ENR &= ~(1 << 2);
	    }
	    else if (port == GPIOD)
	    {
	        RCC->AHB1ENR &= ~(1 << 3);
	    }
	    else if (port == GPIOE)
	    {
	        RCC->AHB1ENR &= ~(1 << 4);
	    }
	    else if (port == GPIOH)
	    {
	        RCC->AHB1ENR &= ~(1 << 7);
	    }
}

/* This function Enables the clock for USART id*/
void RCC_EnableUSART(uint8_t usartid)
{
	if(usartid==USART1_ID)
	{
		RCC->APB2ENR |=(1<<4);
	}
	else if(usartid==USART2_ID)
	{
		RCC->APB1ENR |=(1<<17);
	}
	else if (usartid==USART6_ID)
	{
		RCC->APB2ENR |=(1<<5);
	}
}
/* This function disables the clock of USART id*/
void RCC_DisableUSART(uint8_t usartid)
{
	if(usartid==USART1_ID)
	{
		RCC->APB2ENR &=~(1<<4);
	}
	else if(usartid==USART2_ID)
	{
		RCC->APB1ENR &=~(1<<17);
	}
	else if (usartid==USART6_ID)
	{
		RCC->APB2ENR &=~(1<<5);
	}
}
void RCC_Config_HSE_SystemClock(void)
{
	RCC->CR |=(1<<16); // Enable HSE
	while(!(RCC->CR & (1<<17)));
	RCC->CFGR &= ~(0xF << 4); // HPRE = /1
	RCC->CFGR &= ~(0x7 << 10); // PPRE1 = /1
	RCC->CFGR &= ~(0x7 << 13); // PPRE2 = /1
	RCC->CFGR &=~(0b11<<0); //Clear Clock before switching
	RCC->CFGR |=(0b01<<0); // Switch clock to HSE
	while(!(RCC->CFGR & (0b01<<2)));
}

void RCC_EnableSPI(SPI_RegDef *pSPIx)
{
	if(pSPIx==SPI1)
	{
		RCC->APB2ENR |=(1<<12);
	}
	else if(pSPIx==SPI2)
	{
		RCC->APB1ENR |=(1<<14);
	}
	else if (pSPIx==SPI3)
	{
		RCC->APB1ENR |=(1<<15);
	}
	else if (pSPIx==SPI4)
	{
		RCC->APB2ENR |=(1<<13);
	}
	else if (pSPIx==SPI5)
	{
		RCC->APB2ENR |=(1<<20);
	}
}

void RCC_DisableSPI(SPI_RegDef *pSPIx)
{
	if(pSPIx==SPI1)
	{
		RCC->APB2ENR &= ~(1<<12);
	}
	else if(pSPIx==SPI2)
	{
		RCC->APB1ENR &= ~(1<<14);
	}
	else if (pSPIx==SPI3)
	{
		RCC->APB1ENR &= ~(1<<15);
	}
	else if (pSPIx==SPI4)
	{
		RCC->APB2ENR &= ~(1<<13);
	}
	else if (pSPIx==SPI5)
	{
		RCC->APB2ENR &= ~(1<<20);
	}
}
void RCC_EnableI2C(I2C_RegDef *pI2Cx)
{

}
void RCC_DisableI2C(I2C_RegDef *pI2Cx)
{

}
