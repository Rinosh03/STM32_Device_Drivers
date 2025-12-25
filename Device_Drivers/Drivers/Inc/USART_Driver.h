#ifndef USART_DRIVER_H_
#define USART_DRIVER_H_

#include "stdint.h"
#include "stm32f411xe.h"

#define USART_Periphclockfreq 8000000U

typedef enum
{
	USART1_ID,
	USART2_ID,
	USART6_ID
}USART_ID_T;

typedef enum
{
	USART_WORDLENGTH_8B,
	USART_WORDLENGTH_9B
}USART_WORDLENGTH_T;

typedef enum
{
	USART_PARITY_NONE,
	USART_PARITY_EVEN,
	USART_PARITY_ODD
}USART_PARITY_T;

typedef enum
{
	USART_STOPBIT_0_5,
	USART_STOPBIT_1,
	USART_STOPBIT_1_5,
	USART_STOPBIT_2
}USART_STOPBITS_T;

typedef struct
{
	USART_ID_T usartid;
	uint32_t baudrate;
	USART_WORDLENGTH_T wordlength;
	USART_PARITY_T parity;
	USART_STOPBITS_T stopbits;
	uint8_t oversampling;
	USART_RegDef *USARTInstance;
}USART_Struct_T;

void USART_Init(USART_Struct_T *usartconfig);
void USART_DeInit(USART_Struct_T *usartconfig);
void USART_Transmit(USART_Struct_T *usartconfig, uint8_t *data, uint8_t length);
void USART_Receive(USART_Struct_T *usartconfig, uint8_t *data, uint8_t length);
/* Support functions */
void USART_Enable(USART_Struct_T *usartconfig);
void USART_Disable(USART_Struct_T *usartconfig);
void USART_ConfigureGPIO(USART_ID_T usartid);


#endif /* USART_DRIVER_H_ */
