#include "SYSCFG_DRIVER.h"

void SYSCFG_Set_EXTI(uint8_t EXTI_line, uint8_t EXTI_lineval)
{
	uint8_t RegIndex;
	uint8_t bitpos;
	RegIndex = EXTI_line/4;
	bitpos = (EXTI_line%4) * 4;
	SYSCFG->EXTICR[RegIndex] &=~(0xF<<bitpos);
	SYSCFG->EXTICR[RegIndex] |=((EXTI_lineval&0x0F)<<bitpos);
}
