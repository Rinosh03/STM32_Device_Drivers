#include <stdint.h>
#include "GPIO_Driver.h"
#include "RCC_Driver.h"
#include "SYSCFG_Driver.h"
#include "EXTI_Driver.h"
#include "NVIC_Driver.h"
#include "USART_Driver.h"
uint8_t Rxbuff[10];
USART_Struct_T usart2config =
{
		.baudrate=9600,
		.oversampling=8,
		.parity=USART_PARITY_NONE,
		.stopbits=USART_STOPBIT_1,
		.usartid=USART2_ID,
		.wordlength=USART_WORDLENGTH_8B,
		.USARTInstance=USART2
};
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
void usart_tx_rx_basic(void)
{
	const char *transmit_data = "Hello from USART2!";
	//Enable FPU
	FPU_CPACR_ADDR |= (0xF << 20);

	// Enable HSE Clock (8MHz) and configure the USART Periph clock to the same 8 MHz
	RCC_Config_HSE_SystemClock();
	USART_Init(&usart2config);
	USART_Transmit(&usart2config, (uint8_t*)transmit_data , 19);
	while(1)
	{
		USART_Receive(&usart2config, (uint8_t*)Rxbuff, 1);
		USART_Transmit(&usart2config, (uint8_t*)Rxbuff , 1);
	}
}
int main(void)
{
	/* uncomment to enable push button interrupt code */
	//interrupt_pushbutton();
	/* Uncomment to enbale USART_tx_rx_basic code */
	 usart_tx_rx_basic();

}

void EXTI0_IRQHandler()
{
	if(EXTI_isPending(0)==1)
	{
		GPIO_TogglePin(GPIOD, 14);
		EXTI_ClearPending(0);
	}
}
