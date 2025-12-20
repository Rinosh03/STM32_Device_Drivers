#include "EXTI_Driver.h"


void EXTI_Enable(uint8_t EXTI_line,EXTI_TRIGGER_T Trigger_Type)
{
	EXTI->IMR &=~(1<<EXTI_line);
	EXTI->IMR |=(1<<EXTI_line);
	switch(Trigger_Type)
	{
		case EXTI_RISING_EDGE_TRIGGER:
			EXTI->RTSR |= (1<<EXTI_line);
			EXTI->FTSR &= ~(1<<EXTI_line);
			break;
		case EXTI_FALLING_EDGE_TRIGGER:
			EXTI->FTSR |= (1<<EXTI_line);
			EXTI->FTSR &= ~(1<<EXTI_line);
			break;
		case EXTI_BOTH_EDGE_TRIGGER:
			EXTI->RTSR |=(1<<EXTI_line);
			EXTI->FTSR |=(1<<EXTI_line);
			break;
		default:
			break;
	}
}

void EXTI_EnableEvent(uint8_t EXTI_line)
{
	EXTI->EMR &= ~(1<<EXTI_line);
	EXTI->EMR |= (1<<EXTI_line);
}

void EXTI_SetPending(uint8_t EXTI_line)
{
	EXTI->PR |= (1<<EXTI_line);
}

bool EXTI_isPending(uint8_t EXTI_line)
{
	return (EXTI->PR & (1<<EXTI_line))? 1:0;
}
