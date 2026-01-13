/*
 * SPI_Tx_Rx.c
 *
 *  Created on: 12-Jan-2026
 *      Author: rinos
 */
#include <stdint.h>
#include "GPIO_Driver.h"
#include "RCC_Driver.h"
#include "SYSCFG_Driver.h"
#include "EXTI_Driver.h"
#include "NVIC_Driver.h"
#include "USART_Driver.h"
#include "SPI_Driver.h"
#include <string.h>

/* SPI2 Pin config
 SPI2_MOSI-> PB15
 SPI2_MISO-> PB14
 SPI2_NSS-> PB12
 SPI2_SCLK -> PB13
 AF -> AF05
 */

// Command Codes
#define COMMAND_LED_CTRL		0x50
#define COMMAND_SENSOR_READ		0x51
#define COMMAND_LED_READ		0x52
#define COMMAND_PRINT			0x53
#define COMMAND_ID_READ			0x54

#define LED_ON					1
#define LED_OFF					0

// Arduino Analog pins

#define ANALOG_PIN0				0
#define ANALOG_PIN1				1
#define ANALOG_PIN2				2
#define ANALOG_PIN3				3
#define ANALOG_PIN4				4

// Arduino LED
#define LED_PIN					9

void delay() {
	for (uint32_t i = 0; i < 500000/2; i++)
		;
}

/* This function is used for initializing the GPIO Button */

GPIO_Pinconfig Pushbutton =
{
			.pin = 0,
			.otype = GPIO_OTYPE_PP,
			.mode = GPIO_MODE_INPUT,
			.ospeed = GPIO_OSPEED_HIGH,
			.pupdr = GPIO_NOPUPDR,
			.alternatefunc = 0
};

GPIO_Pinconfig LED =
{
		.pin = 12,
		.mode = GPIO_MODE_OUTPUT,
		.otype = GPIO_OTYPE_PP,
		.ospeed = GPIO_OSPEED_LOW,
		.pupdr = GPIO_NOPUPDR,
		.alternatefunc = 0
};

/* This function is used for initializing the values for SPI2 peripheral*/

SPI_Handle_T SPI2handle;
void SPI2_Init() {

	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.DFF = SPI_DFF_8_BIT;
	SPI2handle.SPIConfig.Speed = SPI_SCLK_SPEED_DIV128;
	SPI2handle.SPIConfig.CPOL = SPI_CPOL_1;
	SPI2handle.SPIConfig.CPHA = SPI_CPHA_1;
	SPI2handle.SPIConfig.SSM = SPI_SSM_HW;

	SPI_Init(&SPI2handle);
}
uint8_t SPI_verify_response(uint8_t ackbyte)
{
	if(ackbyte == 0xF5)
	{
		return 1;
	}
	return 0;
}

/* Main Function*/

int main(void)
{
	uint8_t dummy_write = 0xff;
	uint8_t dummy_read;
	uint8_t ackbyte;
	uint8_t args[2];
	RCC_EnableGPIO(GPIOA);
	GPIO_Init(GPIOA, &Pushbutton);
	RCC_EnableGPIO(GPIOD);
	GPIO_Init(GPIOD, &LED);
	SPI2_Init();
    SPI_GPIO_Config(&SPI2handle);
    while(1)
    {
	while(!(GPIO_ReadPin(GPIOA, 0)));
	delay();
	// 1. CMD_LED_CTRL
	uint8_t cmd_ctrl_code = COMMAND_LED_CTRL;
	// Send the Cmd_Ctrl to Arduino Rx and now arduino checks whether it's suitable or not
	SPI_Tx(SPI2, &cmd_ctrl_code, 1);
	// Since we sent this above one we need to clear EXNE in order to send furthur
	SPI_Rx(SPI2, &dummy_read, 1);
	// In order to know ACK/NACK send a dummy byte to get response from Rx
	SPI_Tx(SPI2, &dummy_write, 1);
	// Get the receiving ACK/NACK
	SPI_Rx(SPI2, &ackbyte, 1);
	SPI_verify_response(ackbyte);
	if(SPI_verify_response(ackbyte))
	{
		// Send the commands
		args[0] = LED_PIN;
		args[1] = LED_ON;
		SPI_Tx(SPI2, args, 2);
	}
	// 2. CMD_SENSOR_READ
	while(!(GPIO_ReadPin(GPIOA, 0)));
	delay();
	// 1. CMD_SENSOR_READ
	uint8_t cmd_analog_read_code = COMMAND_SENSOR_READ;
	// Send the Cmd_Ctrl to Arduino Rx and now arduino checks whether it's suitable or not
	SPI_Tx(SPI2, &cmd_analog_read_code, 1);
	// Since we sent this above one we need to clear RXNE in order to send further
	SPI_Rx(SPI2, &dummy_read, 1);
	// In order to know ACK/NACK send a dummy byte to get response from Rx
	SPI_Tx(SPI2, &dummy_write, 1);
	// Get the receiving ACK/NACK
	SPI_Rx(SPI2, &ackbyte, 1);
	SPI_verify_response(ackbyte);
	if(SPI_verify_response(ackbyte))
	{
		// Send the commands
		args[0] = ANALOG_PIN0;
		// Transmitting the values
		SPI_Tx(SPI2, args, 1);
		// Clear RXNE
		SPI_Rx(SPI2, &dummy_read, 1);
		// TX Dummy bits to fetch response from Slave
		SPI_Tx(SPI2, &dummy_write, 1);
		// Read the Analog pin data now
		uint8_t analog_read;
		SPI_Rx(SPI2, &analog_read, 1);
	}
	// 3. CMD_LED_READ
	while(!(GPIO_ReadPin(GPIOA, 0)));
	delay();
	uint8_t cmd_led_read = COMMAND_LED_READ;
	// Send the Cmd_Ctrl to Arduino Rx and now arduino checks whether it's suitable or not
	SPI_Tx(SPI2, &cmd_led_read, 1);
	// Since we sent this above one we need to clear RXNE in order to send further
	SPI_Rx(SPI2, &dummy_read, 1);
	// In order to know ACK/NACK send a dummy byte to get response from Rx
	SPI_Tx(SPI2, &dummy_write, 1);
	// Get the receiving ACK/NACK
	SPI_Rx(SPI2, &ackbyte, 1);
	SPI_verify_response(ackbyte);
	if(SPI_verify_response(ackbyte))
	{
		// Send the commands
		args[0] = LED_PIN;
		// Transmitting the values
		SPI_Tx(SPI2, args, 1);
		// Clear RXNE
		SPI_Rx(SPI2, &dummy_read, 1);
		// TX Dummy bits to fetch response from Slave
		SPI_Tx(SPI2, &dummy_write, 1);
		// Read the Analog pin data now
		uint8_t led_read;
		SPI_Rx(SPI2, &led_read, 1);
	}
	// 4. CMD_PRINT
	while(!(GPIO_ReadPin(GPIOA, 0)));
	delay();
	uint8_t cmd_print = COMMAND_PRINT;
	// Send the Cmd_Ctrl to Arduino Rx and now arduino checks whether it's suitable or not
	SPI_Tx(SPI2, &cmd_print, 1);
	// Since we sent this above one we need to clear RXNE in order to send further
	SPI_Rx(SPI2, &dummy_read, 1);
	// In order to know ACK/NACK send a dummy byte to get response from Rx
	SPI_Tx(SPI2, &dummy_write, 1);
	// Get the receiving ACK/NACK
	SPI_Rx(SPI2, &ackbyte, 1);
	uint8_t message[] = "Hello from STM32!";
	SPI_verify_response(ackbyte);
	if(SPI_verify_response(ackbyte))
	{
		args[0] = strlen((char*)message);
		SPI_Tx(SPI2, args, 1);
		SPI_Rx(SPI2, &dummy_read, 1);
		delay();
		for(uint32_t i=0;i<args[0]; i++)
		{
			SPI_Tx(SPI2, &message[i], 1);
			SPI_Rx(SPI2, &dummy_read, 1);
		}
	}
	// 5. CMD_ID_READ
	while(!(GPIO_ReadPin(GPIOA, 0)));
	delay();
	uint8_t cmd_id_print = COMMAND_ID_READ;
	// Send the Cmd_Ctrl to Arduino Rx and now arduino checks whether it's suitable or not
	SPI_Tx(SPI2, &cmd_id_print, 1);
	// Since we sent this above one we need to clear RXNE in order to send further
	SPI_Rx(SPI2, &dummy_read, 1);
	// In order to know ACK/NACK send a dummy byte to get response from Rx
	SPI_Tx(SPI2, &dummy_write, 1);
	// Get the receiving ACK/NACK
	SPI_Rx(SPI2, &ackbyte, 1);
	uint8_t ID[11];
	SPI_verify_response(ackbyte);
	if(SPI_verify_response(ackbyte))
	{
		for(uint32_t j=0; j<10; j++)
		{
			SPI_Tx(SPI2, &dummy_write, 1);
			SPI_Rx(SPI2, &ID[j], 1);
		}
		ID[10]='\0';
	}

	while(SPI2->SR & SPI_BSY_FLAG);
	SPI_DeInit(&SPI2handle);
	return 0;
}
}



