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
	/* 🔴 END-OF-PROGRAM / MAIN LOOP INDICATION */
	while(1)
	{
	    GPIOD->ODR ^= (1U << 14);   // Toggle LED
	    delay(1000000);
	 }
}


static void usart1_init_8mhz_9600(void)
{
    // 1) Clocks
    RCC->AHB1ENR |= (1U << 0);   // GPIOAEN
    RCC->APB2ENR |= (1U << 4);   // USART1EN

    // 2) PA9 = AF7 (USART1_TX)
    // MODER9 = 10 (AF)
    GPIOA->MODER &= ~(3U<<(15*2));
    GPIOA->MODER |=  (2U<<(15*2));

    // Optional: high speed
    GPIOA->OSPEEDR |= (3U << (9*2));

    // AFRH for pin 9 => AFRH[7:4]
    GPIOA->AFRH &= ~(0xFU<<(4*(15-8)));
    GPIOA->AFRH |=  (7U<<(4*(15-8)));

    // 3) USART config: 8N1, oversampling 16
    USART1->CR1 = 0;           // reset CR1
    USART1->CR2 = 0;           // 1 stop bit
    USART1->CR3 = 0;

    // Baud rate: PCLK2 = 8 MHz, baud = 9600, OVER8=0
    // USARTDIV = 8,000,000 / (16*9600) = 52.0833
    // Mantissa=52, Fraction=0.0833*16=1.333 -> 1
    USART1->BRR = (52U << 4) | (1U);

    USART1->CR1 |= (1U << 3);  // TE
    USART1->CR1 |= (1U << 13); // UE
}
static void usart1_send_string(const char *s)
{
    while(*s)
    {
        while(!(USART1->SR & (1U << 7))) {}  // TXE
        USART1->DR = (uint8_t)*s++;
    }
    while(!(USART1->SR & (1U << 6))) {}      // TC
}
int main(void)
{
	// LED PD14 blink (optional)
	    RCC->AHB1ENR |= (1U<<3);
	    GPIOD->MODER &= ~(3U<<(14*2));
	    GPIOD->MODER |=  (1U<<(14*2));

	    for(int i=0;i<3;i++){ GPIOD->ODR ^= (1U<<14); delay(800000); }
	    RCC_Config_HSE_SystemClock();
	    usart1_init_8mhz_9600();
	    while(1)
	    {
	    	usart1_send_string("Hello from USART1!\r\n");
	    }
}








	//----------------------------------------------------xxxxxxxxx----------------------------------------------------
	//RCC->AHB1ENR |= (1U << 3);   // GPIODEN

	/* 2️⃣ Configure PD14 as output */
	/*GPIOD->MODER &= ~(3U << (14 * 2));
	GPIOD->MODER |=  (1U << (14 * 2));   // Output mode

	GPIOD->OTYPER &= ~(1U << 14);         // Push-pull
	GPIOD->OSPEEDR &= ~(3U << (14 * 2));  // Low speed
	GPIOD->PUPDR &= ~(3U << (14 * 2));    // No pull */
	/* 🔴 START-OF-PROGRAM INDICATION */
	/*for(int i = 0; i < 3; i++)
	{
		GPIOD->ODR |=  (1U << 14);  // LED ON
		delay(500000);
		GPIOD->ODR &= ~(1U << 14);  // LED OFF
		delay(500000);
	}*/

	/* uncomment to enable push button interrupt code */
	//interrupt_pushbutton();
	/* Uncomment to enbale USART_tx_rx_basic code */
	 //usart_tx_rx_basic();
	  //RCC->AHB1ENR |= (1u << 0);
	  //RCC->APB2ENR |= (1u << 4); // USART1 enable
	  // RCC->APB1ENR |= (1u << 17); // USART2 enable

	  // USART1
	  /*GPIOA->MODER &= ~(3U << (9*2));
	  GPIOA->MODER |=  (2U << (9*2));
	  GPIOA->OSPEEDR |= (0b1111 << 18);

	  // USART2
	  // GPIOA->MODER |= (0b1010 << 4);
	  // GPIOA->OSPEEDR |= (0b1111 << 4);

	  // USART1
	  GPIOA->AFRH &= ~(0xFU << (4*(9-8)));     // clear nibble
	  GPIOA->AFRH |=  (7U   << (4*(9-8)));

	  // USART2
	  // GPIOA->AFRL |= (0b0111 << 8);
	  // GPIOA->AFRL |= (0b0111 << 12);
	  USART1->CR1 = 0;           // reset CR1
	  USART1->CR2 = 0;           // 1 stop bit
	  USART1->CR3 = 0;*/
	  // Configure this according to your clock configuration.
	  //const uint32_t apb2_clock = 8000000;

	  // Configure this to the desired baudrate.
	  //const uint32_t baudrate = 9600;

	  //const uint32_t bittime = (apb2_clock + baudrate / 2) / baudrate;

	  /* USART1
	  USART1->BRR = bittime;
	  USART1->CR1 &= ~USARTx_CR1_M;
	  USART1->CR1 &= ~(0x3u << 12);
	  USART1->CR1 |= (1u << 3);
	  USART1->CR1 |= (1u << 2);
	  USART1->CR1 &= ~(1u << 10);
	  USART1->CR3 &= ~(1u << 9);
	  USART1->CR3 &= ~(1u << 8);
	  USART1->CR1 |= (1u << 13);

	  // USART2
	  // USART2->BRR = bittime;
	  // USART2->CR1 &= ~USART_CR1_M;
	  // USART2->CR1 &= ~(0x3u << 12);
	  // USART2->CR1 |= (1u << 3);
	  // USART2->CR1 |= (1u << 2);
	  // USART2->CR1 &= ~(1u << 10);
	  // USART2->CR3 &= ~(1u << 9);
	  // USART2->CR3 &= ~(1u << 8);
	  // USART2->CR1 |= (1u << 13);

	  const char* text = "Hello from usart.\r\n";
	  while (*text)
	  {
	    // USART1
	    while (!(USART1->SR & USARTx_SR_TXE));
	    (void) USART1->SR;
	    USART1->DR = *text;

	    // USART2
	    // while (!(USART2->SR & USART_SR_TxE));
	    // (void) USART2->SR;
	    // USART2->DR = *text;

	    ++text;
	  }*/

	  /* 🔴 END-OF-PROGRAM / MAIN LOOP INDICATION */
	  /*while(1)
	  {
	      GPIOD->ODR ^= (1U << 14);   // Toggle LED
	      delay(1000000);
	  }*/

void EXTI0_IRQHandler()
{
	if(EXTI_isPending(0)==1)
	{
		GPIO_TogglePin(GPIOD, 14);
		EXTI_ClearPending(0);
	}
}
