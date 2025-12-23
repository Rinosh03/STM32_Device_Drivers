#ifndef RCC_DRIVER_H
#define RCC_DRIVER_H

#include "stm32f411xe.h"
#include "USART_Driver.h"

void RCC_EnableGPIO(GPIO_RegDef *port);
void RCC_DisableGPIO(GPIO_RegDef *port);
void RCC_EnableUSART(GPIO_RegDef *usartid);
void RCC_DisableUSART(GPIO_RegDef *usartid);



#endif
