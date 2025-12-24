#ifndef STM32F411xE_H
#define STM32F411xE_H
#include "stdint.h"
/* CPU Macros addresses definition */

#define FLASH_MEMORY_BASE_ADDR				0x08000000U
#define FLASH_MEMORY_END_ADDR				0x0807FFFFU
#define SYSMEM_BASE_ADDR					0x1FFF0000U
#define SYSMEM_END_ADDR						0x1FFF7A0FU
#define OPTBYTES_BASE_ADDR					0x1FFFC000U
#define OPTBYTES_END_ADDR					0x1FFFC007U
#define SRAM_BASE_ADDR						0x20000000U
#define SRAM_END_ADDR						0x20020000U

/* Peripherals Base Address Definition */

#define APB1_PERIPH_BASE_ADDR				0x40000000U
#define APB2_PERIPH_BASE_ADDR				0x40010000U
#define AHB1_PERIPH_BASE_ADDR				0x40020000U
#define AHB2_PERIPH_BASE_ADDR				0x50000000U


/* RCC Base Address Definition */

#define RCC_BASE_ADDR						(AHB1_PERIPH_BASE_ADDR + 0x3800U)

/* Floating Point Unit Base Address Definition */

#define FPU_BASE_ADDR 						0xE000 ED00U

/* GPIO Base Addresses Definitions */

#define GPIOA_BASE_ADDR						(AHB1_PERIPH_BASE_ADDR + 0x0000U)
#define GPIOB_BASE_ADDR						(AHB1_PERIPH_BASE_ADDR + 0x0400U)
#define GPIOC_BASE_ADDR						(AHB1_PERIPH_BASE_ADDR + 0x0800U)
#define GPIOD_BASE_ADDR						(AHB1_PERIPH_BASE_ADDR + 0x0C00U)
#define GPIOE_BASE_ADDR						(AHB1_PERIPH_BASE_ADDR + 0x1000U)
#define GPIOH_BASE_ADDR						(AHB1_PERIPH_BASE_ADDR + 0x1C00U)

/* EXTI Base addresses Definitions */

#define EXTI_BASE_ADDR						(APB2_PERIPH_BASE_ADDR + 0x3C00U)

/* SYSCFG Base addresses Definitions */

#define SYSCFG_BASE_ADDR					(APB2_PERIPH_BASE_ADDR + 0x3800U)

/* NVIC Base addresses Definitions */

#define NVIC_BASE_ADDR						0xE000E100U

/* Defining NVIC Registers Base address Macro with pointer to volatile 32 bit integer */

#define NVIC_ISERx_BASE_ADDR				0xE000E100U
#define NVIC_ICERx_BASE_ADDR				0XE000E180U
#define NVIC_ISPRx_BASE_ADDR				0XE000E200U
#define NVIC_ICPRx_BASE_ADDR				0XE000E280U
#define NVIC_IABRx_BASE_ADDR				0xE000E300U
#define NVIC_IPRx_BASE_ADDR					0xE000E400U

/* UART Base addresses Definitions */

#define USART1_BASE_ADDR					0x40011000U
#define USART2_BASE_ADDR					0x40004400U
#define USART6_BASE_ADDR					0x40011400U

/* RCC Registers Definition */

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t RESERVED1;
	volatile uint32_t RESERVED2;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t RESERVED3;
	volatile uint32_t RESRVED4;
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t RESERVED5;
	volatile uint32_t RESERVED6;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t RESERVED7;
	volatile uint32_t RESERVED8;
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t RESERVED9;
	volatile uint32_t RESERVED10;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t RESERVED11;
	volatile uint32_t RESERVED12;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t RESERVED13;
	volatile uint32_t RESERVED14;
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t RESERVED15;
	volatile uint32_t DCKCFGR;
}RCC_RegDef;


/* GPIO Registers Definition */

typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
}GPIO_RegDef;

/* SYSCGF Registers Definition */

typedef struct
{
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[4];
	volatile uint32_t RESERVED[2];
	volatile uint32_t CMPCR;
}SYSCFG_RegDef;

/* EXTI Register Definitions */

typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_RegDef;

/* USART Register Definitions */

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_RegDef;

/* Defining RCC Macro with pointer to base address */

#define RCC 								((RCC_RegDef*)RCC_BASE_ADDR)

/* FPU/SCB Related Macros */

#define FPU_CPACR_ADDR						(*(volatile uint32_t*)(0xE000ED88U))


/* Defining GPIO Macros with Pointer to Base Address */

#define GPIOA 								((GPIO_RegDef*)GPIOA_BASE_ADDR)
#define GPIOB								((GPIO_RegDef*)GPIOB_BASE_ADDR)
#define GPIOC								((GPIO_RegDef*)GPIOC_BASE_ADDR)
#define GPIOD								((GPIO_RegDef*)GPIOD_BASE_ADDR)
#define GPIOE								((GPIO_RegDef*)GPIOE_BASE_ADDR)
#define GPIOH								((GPIO_RegDef*)GPIOH_BASE_ADDR)

/* Defining SYSCFG Macro with pointer to base address */

#define SYSCFG								((SYSCFG_RegDef*)SYSCFG_BASE_ADDR)

/* Defining EXTI Macro with pointer to base address */

#define EXTI								((EXTI_RegDef*)EXTI_BASE_ADDR)

/* NVIC Register Definition */

#define NVIC_ISERx_BASE						((volatile uint32_t*)NVIC_ISERx_BASE_ADDR)
#define NVIC_ICERx_BASE						((volatile uint32_t*)NVIC_ICERx_BASE_ADDR)
#define NVIC_ISPRx_BASE						((volatile uint32_t*)NVIC_ISPRx_BASE_ADDR)
#define NVIC_ICPRx_BASE						((volatile uint32_t*)NVIC_ICPRx_BASE_ADDR)
#define NVIC_IABRx_BASE						((volatile uint32_t*)NVIC_IABRx_BASE_ADDR)
#define NVIC_IPRx_BASE						((volatile uint8_t*)NVIC_ICPRx_BASE_ADDR)

/* USART Macros definition with macros base addresses pointing towards their register structure */

#define USART1								((USART_RegDef*)USART1_BASE_ADDR)
#define USART2								((USART_RegDef*)USART2_BASE_ADDR)
#define USART6								((USART_RegDef*)USART6_BASE_ADDR)

/* Other Macros used in GPIO */
#define GPIO_MODER_BITMASK					0x3
#define GPIO_OSPEEDR_BITMASK				0x3
#define GPIO_PUPDR_BITMASK 					0x3
#define GPIO_AFRL_BITMASK					0xF
#define GPIO_AFRH_BITMASK					0xF
#define GPIO_MODER_SHIFT_BITS				0x2
#define GPIO_OSPEEDR_SHIFT_BITS				0x2
#define GPIO_PUPDR_SHIFT_BITS				0x2
#define GPIO_AFRL_SHIFT_BITS				0x4
#define GPIO_AFRH_SHIFT_BITS				0x4
#define GPIO_AFRL_SIZE						0x7
#define GPIO_AFRH_SIZE						0xF

/* EXTI Interrupt  Numbers */

#define EXTI0_IRQn							6
#define EXTI1_IRQn							7
#define EXTI2_IRQn							8
#define EXTI3_IRQn							9
#define EXTI4_IRQn							10
#define EXTI9_5_IRQn						23
#define EXTI0_15_IRQn						40

/* USARTx_SR Related Macros */

#define USARTx_SR_TXE						(1<<7)
#define USARTx_SR_TC						(1<<6)
#define USARTx_SR_RXNE						(1<<5)
#define USARTx_SR_IDLE						(1<<4)
#define USARTx_SR_ORE						(1<<3)
#define USARTx_SR_NF						(1<<2)
#define USARTx_SR_FE						(1<<1)
#define USARTx_SR_PE						(1<<0)

/* USARTx_CR1 Related Macros */

#define USARTx_CR1_OVER8					(1<<15)
#define USARTx_CR1_UE						(1<<13)
#define USARTx_CR1_M						(1<<12)
#define USARTx_CR1_WAKE						(1<<11)
#define USARTx_CR1_PCE						(1<<10)
#define USARTx_CR1_PS						(1<<9)
#define USARTx_CR1_PEIE						(1<<8)
#define USARTx_CR1_TXEIE					(1<<7)
#define USARTx_CR1_TCIE						(1<<6)
#define USARTx_CR1_RXNEIE					(1<<5)
#define USARTx_CR1_IDLEIE					(1<<4)
#define USARTx_CR1_TE						(1<<3)
#define USARTx_CR1_RE						(1<<2)
#define USARTx_CR1_RWU						(1<<1)
#define USARTx_CR1_SBK						(1<<0)

/* USARTx_CR2 Related Macros */

#define USARTx_CR2_LINEN					(1<<14)
#define USARTx_STOPBIT_1					(0b00<<12)
#define USARTx_STOPBIT_0_5					(0b01<<12)
#define USARTx_STOPBIT_2					(0b10<<12)
#define USARTx_STOPBIT_1_5					(0b11<<12)
#define USARTx_CR2_CLKEN					(1<<11)
#define USARTx_CR2_CPOL						(1<<10)
#define USARTx_CR2_CPHA						(1<<9)
#define USARTx_CR2_LBCL						(1<<8)
#define USARTx_CR2_LBDIE					(1<<6)
#define USARTx_CR2_LBDL						(1<<5)

/*USARTx_CR3 Related Macros */

#define USARTx_CR3_ONEBIT					(1<<11)
#define USARTx_CR3_CTSIE					(1<<10)
#define USARTx_CR3_CTSE						(1<<9)
#define USARTx_CR3_RTSE						(1<<8)
#define USARTx_CR3_DMAT						(1<<7)
#define USARTx_CR3_DMAR						(1<<6)
#define USARTx_CR3_SCEN						(1<<5)
#define USARTx_CR3_NACK						(1<<4)
#define USARTx_CR3_HDSEL					(1<<3)
#define USARTx_CR3_IRLP						(1<<2)
#define USARTx_CR3_IREN						(1<<1)
#define USARTx_CR3_EIE						(1<<0)





#endif

