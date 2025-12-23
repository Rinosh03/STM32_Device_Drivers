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
void RCC_EnableUSART(USART_Struct_T *usartconfig)
{
	if(usartconfig->usartid==USART1_ID)
	{
		RCC->APB2RSTR |=(1<<4);
	}
	else if(usartconfig->usartid==USART2_ID)
	{
		RCC->APB1RSTR |=(1<<17);
	}
	else if (usartconfig->usartid==USART6_ID)
	{
		RCC->APB2RSTR |=(1<<5);
	}
}
/* This function disables the clock of USART id*/
void RCC_DisableUSART(USART_Struct_T *usartconfig)
{
	if(usartconfig->usartid==USART1_ID)
	{
		RCC->APB2RSTR &=~(1<<4);
	}
	else if(usartconfig->usartid==USART2_ID)
	{
		RCC->APB1RSTR &=~(1<<17);
	}
	else if (usartconfig->usartid==USART6_ID)
	{
		RCC->APB2RSTR &=~(1<<5);
	}
}

