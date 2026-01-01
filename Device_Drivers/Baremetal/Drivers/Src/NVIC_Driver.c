#include "NVIC_Driver.h"


void NVIC_EnableIRQ(uint8_t IRQn)
{
	uint8_t regindex = IRQn/32;
	uint8_t bitpos = IRQn%32;
	NVIC_ISERx_BASE[regindex] = (1<<bitpos);
}

void NVIC_DisableIRQ(uint8_t IRQn)
{
	uint8_t regindex = IRQn/32;
	uint8_t bitpos = IRQn%32;
	NVIC_ICERx_BASE[regindex] = (1<<bitpos);
}

void NVIC_SetPending(uint8_t IRQn)
{
	uint8_t regindex = IRQn/32;
	uint8_t bitpos = IRQn%32;
	NVIC_ISPRx_BASE[regindex] = (1<<bitpos);

}

void NVIC_ClearPending(uint8_t IRQn)
{
	uint8_t regindex = IRQn/32;
	uint8_t bitpos = IRQn%32;
	NVIC_ICPRx_BASE[regindex] = (1<<bitpos);
}

bool NVIC_ReadActive(uint8_t IRQn)
{
	uint8_t regindex = IRQn/32;
	uint8_t bitpos = IRQn%32;
	return(NVIC_IABRx_BASE[regindex] & (1<<bitpos))? 1:0;
}

void NVIC_SetPriority(uint8_t IRQn, uint8_t priorityval)
{
	NVIC_IPRx_BASE[IRQn] = (priorityval & 0x0F)<<4;
}
