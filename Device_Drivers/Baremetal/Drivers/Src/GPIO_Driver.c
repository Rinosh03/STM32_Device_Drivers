#include "GPIO_Driver.h"


/* This function is used for initializing the port and other parameters we have configured for GPIO */
void GPIO_Init(GPIO_RegDef *port, GPIO_Pinconfig *pinconfig)
{
	uint8_t pin = pinconfig->pin;
	port->MODER &= ~(GPIO_MODER_BITMASK<<(GPIO_MODER_SHIFT_BITS*pin));
	port->MODER |=((pinconfig->mode & GPIO_MODER_BITMASK)<<(GPIO_MODER_SHIFT_BITS*pin));

	port->OTYPER &= ~(1<<pin);
	port->OTYPER |=((pinconfig->otype)<<pin);

	port->OSPEEDR &= ~(GPIO_OSPEEDR_BITMASK<<(GPIO_OSPEEDR_SHIFT_BITS*pin));
	port->OSPEEDR |=((pinconfig->ospeed & GPIO_OSPEEDR_BITMASK)<<(GPIO_OSPEEDR_SHIFT_BITS*pin));

	port->PUPDR &= ~(GPIO_PUPDR_BITMASK<<(GPIO_PUPDR_SHIFT_BITS*pin));
	port->PUPDR |= ((pinconfig->pupdr & GPIO_PUPDR_BITMASK) <<(GPIO_PUPDR_SHIFT_BITS*pin));

	if(pinconfig->mode == GPIO_MODE_ALT)
	{
	if(pin<=GPIO_AFRL_SIZE)
	{
		port->AFRL &= ~(GPIO_AFRL_BITMASK<<(GPIO_AFRL_SHIFT_BITS*pin));
		port->AFRL |=((pinconfig->alternatefunc & GPIO_AFRL_BITMASK)<<(GPIO_AFRL_SHIFT_BITS*pin));
	}
	else if(pin>GPIO_AFRL_SIZE || pin<=GPIO_AFRH_SIZE)
	{
		port->AFRH &= ~(GPIO_AFRH_BITMASK <<(GPIO_AFRH_SHIFT_BITS*(pin - GPIO_AFRL_SIZE)));
		port->AFRH |=((pinconfig->alternatefunc & GPIO_AFRH_BITMASK)<<(GPIO_AFRH_SHIFT_BITS*(pin - GPIO_AFRL_SIZE )));
	}
	}
}

/* This function is used for deinitializing the pin from the desired port  */
void GPIO_DeInit_Pin(GPIO_RegDef *port, GPIO_Pinconfig *pinconfig)
{
	uint8_t pin = pinconfig->pin;
	port->MODER &= ~(GPIO_MODER_BITMASK<<(GPIO_MODER_SHIFT_BITS*pin));

	port->OTYPER &= ~(1<<pin);

	port->OSPEEDR &= ~(GPIO_OSPEEDR_BITMASK<<(GPIO_OSPEEDR_SHIFT_BITS*pin));

	port->PUPDR &= ~(GPIO_PUPDR_BITMASK<<(GPIO_PUPDR_SHIFT_BITS*pin));

	if(pinconfig->mode == GPIO_MODE_ALT)
	{
	if(pin<=GPIO_AFRL_SIZE)
	{
		port->AFRL &= ~(GPIO_AFRL_BITMASK<<(GPIO_AFRL_SHIFT_BITS*pin));
	}
	else if(pin>GPIO_AFRL_SIZE || pin<=GPIO_AFRH_SIZE)
	{
		port->AFRH &= ~(GPIO_AFRH_BITMASK<<(GPIO_AFRH_SHIFT_BITS*pin));
	}
	}
}

/* This function is used for deninitializing the entire port */
void GPIO_DeInit(GPIO_RegDef *port)
{
	if (port == GPIOA)
	    	{
	        	RCC->AHB1RSTR |= (1 << 0);
	        	RCC->AHB1RSTR &= ~(1 << 0);
	    	}
	    else if (port == GPIOB)
	    	{
	    		RCC->AHB1RSTR |= (1 << 1);
	    		RCC->AHB1RSTR &= ~(1 << 1);
	    	}
	    else if (port == GPIOC)
	    	{
	        	RCC->AHB1RSTR |= (1 << 2);
	        	RCC->AHB1RSTR &= ~(1 << 2);
	    	}
	    else if (port == GPIOD)
	    	{
	        	RCC->AHB1RSTR |= (1 << 3);
	        	RCC->AHB1RSTR &= ~(1 << 3);
	    	}
	    else if (port == GPIOE)
	    	{
	        	RCC->AHB1RSTR |= (1 << 4);
	        	RCC->AHB1RSTR &= ~(1 << 4);
	    	}
	    else if (port == GPIOH)
	    	{
	        	RCC->AHB1RSTR |= (1 << 7);
	        	RCC->AHB1RSTR &= ~(1 << 7);
	    	}
}

/* This function is used for toggling particular pin in stm32f411vet6 using toggling function */
void GPIO_TogglePin(GPIO_RegDef *port, uint8_t pin)
{
	port->ODR ^= (1<<pin);
}

/* This function is used for writing/setting up a GPIO_pin */
void GPIO_SetPin(GPIO_RegDef *port, uint8_t pin)
{
	port->ODR |= (1<<pin);
}

/* This function is used for reading a GPIO_pin */
uint32_t GPIO_ReadPin(GPIO_RegDef *port, uint8_t pin)
{
	return(port->IDR & (1<<pin));
}

/* This function is used for writing/setting up a GPIO_port */
void GPIO_SetPort(GPIO_RegDef *port, uint32_t portval)
{
	port->ODR |= portval;
}

/*This function is used for reading a GPIO_Port */
uint32_t GPIO_ReadPort(GPIO_RegDef *port)
{
	return(port->IDR);
}

/* This function is used for locking up a GPIO port and pin */

void GPIO_Lock(GPIO_RegDef *port, uint8_t pin)
{

}


