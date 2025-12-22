#ifndef EXTI_DRIVER_H
#define EXTI_DRIVER_H

#include "stm32f411xe.h"
#include "stdint.h"
#include <stdbool.h>
typedef enum
{
	EXTI_RISING_EDGE_TRIGGER,
	EXTI_FALLING_EDGE_TRIGGER,
	EXTI_BOTH_EDGE_TRIGGER
}EXTI_TRIGGER_T;



void EXTI_Enable(uint8_t EXTI_line,EXTI_TRIGGER_T Trigger_Type);
void EXTI_EnableEvent(uint8_t EXTI_line, EXTI_TRIGGER_T Trigger_Type);
void EXTI_ClearPending(uint8_t EXTI_line);
bool EXTI_isPending(uint8_t EXTI_line);










#endif
