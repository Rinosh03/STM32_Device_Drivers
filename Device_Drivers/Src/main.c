#include <stdint.h>
#include "GPIO_Driver.h"
#include "RCC_Driver.h"
#include "SYSCFG_Driver.h"
#include "EXTI_Driver.h"
#include "NVIC_Driver.h"

GPIO_Pinconfig Pushbutton =
{
		.pin = 0,
		.mode = GPIO_MODE_INPUT,
		.ospeed = GPIO_OSPEED_LOW,
		.pupdr = GPIO_NOPUPDR,
		.otype = GPIO_OTYPE_PP,
		.alternatefunc = 0
};

GPIO_Pinconfig RedLED =
{
		.pin = 14,
		.mode = GPIO_MODE_OUTPUT,
		.ospeed = GPIO_OSPEED_LOW,
		.pupdr = GPIO_NOPUPDR,
		.otype = GPIO_OTYPE_PP,
		.alternatefunc = 0
};

void delay()
{
	for(uint32_t i=0; i<1777777; i++);
}

void interrupt_pushbutton()
{
	RCC_EnableGPIO(GPIOA);
	RCC_EnableGPIO(GPIOD);

	GPIO_Init(GPIOA, &Pushbutton);
	GPIO_Init(GPIOD, &RedLED);

	SYSCFG_Set_EXTI(0, 0);

	EXTI_Enable(0, EXTI_RISING_EDGE_TRIGGER);

	NVIC_EnableIRQ(EXTI0_IRQn);
}

int main(void)
{
	/* uncomment to enable push button interrupt code */
	//void interrupt_pushbutton();
}

void EXTI0_IRQHandler()
{
	if(EXTI_isPending(0)==1)
	{
		GPIO_TogglePin(GPIOD, 14);
		EXTI_ClearPending(0);
	}
}
