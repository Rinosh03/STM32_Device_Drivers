#ifndef RCC_DRIVER_H
#define RCC_DRIVER_H

#include "stm32f411xe.h"
#include "USART_Driver.h"

void RCC_EnableGPIO(GPIO_RegDef *port);
void RCC_DisableGPIO(GPIO_RegDef *port);
void RCC_EnableUSART(uint8_t usartid);
void RCC_DisableUSART(uint8_t usartid);
void RCC_Config_HSE_SystemClock(void);
void RCC_EnableSPI(SPI_RegDef *pSPIx);
void RCC_DisableSPI(SPI_RegDef *pSPIx);
void RCC_EnableI2C(I2C_RegDef *pI2Cx);
void RCC_DisableI2C(I2C_RegDef *pI2Cx);



#endif
