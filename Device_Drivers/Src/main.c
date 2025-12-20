#include <stdint.h>
#include "GPIO_Driver.h"
#include "RCC_Driver.h"

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
int main(void)
{
	RCC_EnableGPIO(GPIOD);
	GPIO_Init(GPIOD, &RedLED);
	while(1)
	{
	GPIO_TogglePin(GPIOD, 14);
	delay();
	}
}
