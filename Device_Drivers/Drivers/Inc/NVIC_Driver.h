#ifndef NVIC_DRIVER_H
#define NVIC_DRIVER_H

#include "stm32f411xe.h"
#include "stdint.h"
#include <stdbool.h>

void NVIC_EnableIRQ(uint8_t IRQn);
void NVIC_DisableIRQ(uint8_t IRQn);
void NVIC_SetPending(uint8_t IRQn);
void NVIC_ClearPending(uint8_t IRQn);
bool NVIC_ReadActive(uint8_t IRQn);
void NVIC_SetPriority(uint8_t IRQn, uint8_t priorityval);

#endif
