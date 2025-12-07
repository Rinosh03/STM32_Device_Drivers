#include "GPIO_Driver.h"


/* This function is used for initializing the port and other parameters we have configured for GPIO */
void GPIO_Init(GPIO_RegDef *port, GPIO_Pinconfig *pinconfig)
{
	uint8_t pin = pinconfig->pin;
	port->MODER &= ~(0x3<<(2*pin));
	port->MODER |=((pinconfig->mode & 0x3)<<(2*pin));

	port->OTYPER &= ~(1<<pin);
	port->OTYPER |=((pinconfig->otype)<<pin);

	port->OSPEEDR &= ~(0x3<<(2*pin));
	port->OSPEEDR |=((pinconfig->ospeed & 0x3)<<(2*pin));

	port->PUPDR &= ~(0x3<<(2*pin));
	port->PUPDR |= ((pinconfig->pupdr & 0x3) <<(2*pin));

	if(pinconfig->mode == GPIO_MODE_ALT)
	{
	if(pin<=7)
	{
		port->AFRL &= ~(0xF<<(4*pin));
		port->AFRL |=((pinconfig->alternatefunc & 0xF)<<(4*pin));
	}
	else
	{
		port->AFRH &= ~(0xF<<(4*pin));
		port->AFRH |=((pinconfig->alternatefunc & 0xF)<<(4*pin));
	}
	}
}

/* This function is used for deinitializing the ports and other parameters we have configured for GPIO */
void GPIO_DeInit(GPIO_RegDef *port, GPIO_Pinconfig *pinconfig)
{
	uint8_t pin = pinconfig->pin;
	port->MODER &= ~(0x3<<(2*pin));

	port->OTYPER &= ~(1<<pin);

	port->OSPEEDR &= ~(0x3<<(2*pin));

	port->PUPDR &= ~(0x3<<(2*pin));

	if(pinconfig->mode == GPIO_MODE_ALT)
	{
	if(pin<=7)
	{
		port->AFRL &= ~(0xF<<(4*pin));
	}
	else
	{
		port->AFRH &= ~(0xF<<(4*pin));
	}
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


