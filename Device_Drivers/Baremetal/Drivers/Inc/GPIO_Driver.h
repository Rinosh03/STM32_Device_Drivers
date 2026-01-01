#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H
#include "stm32f411xe.h"

typedef enum
{
	GPIO_MODE_INPUT = 0x00,
	GPIO_MODE_OUTPUT = 0x01,
	GPIO_MODE_ALT = 0x02,
	GPIO_MODE_ANALOG = 0x03
}GPIO_MODE_T;

typedef enum
{
	GPIO_OTYPE_PP = 0,
	GPIO_OTYPE_OD = 1
}GPIO_OTYPE_T;

typedef enum
{
	GPIO_OSPEED_LOW = 0x00,
	GPIO_OSPEED_MEDIUM = 0x01,
	GPIO_OSPEED_FAST = 0x02,
	GPIO_OSPEED_HIGH = 0x03
}GPIO_OSPEED_T;

typedef enum
{
	GPIO_NOPUPDR = 0x00,
	GPIO_PULL_UP = 0x01,
	GPIO_PULL_DOWN = 0x02,
	GPIO_RSVD = 0x03
}GPIO_PUPDR_T;

typedef struct
{
	uint8_t pin;
	GPIO_MODE_T mode;
	GPIO_OTYPE_T otype;
	GPIO_OSPEED_T ospeed;
	GPIO_PUPDR_T pupdr;
	uint8_t alternatefunc;
}GPIO_Pinconfig;

/* Function Declarations */

void GPIO_Init(GPIO_RegDef *port, GPIO_Pinconfig *pinconfig);
void GPIO_DeInit_Pin(GPIO_RegDef *port, GPIO_Pinconfig *pinconfig);
void GPIO_DeInit(GPIO_RegDef *port);

void GPIO_TogglePin(GPIO_RegDef *port, uint8_t pin);
void GPIO_SetPin(GPIO_RegDef *port, uint8_t pin);
uint32_t GPIO_ReadPin(GPIO_RegDef *port, uint8_t pin);
void GPIO_SetPort(GPIO_RegDef *port, uint32_t portval);
uint32_t GPIO_ReadPort(GPIO_RegDef *port);
void GPIO_Lock(GPIO_RegDef *port, uint8_t pin);

#endif
