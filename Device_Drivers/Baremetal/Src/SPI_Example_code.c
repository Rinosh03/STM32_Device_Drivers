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

/* This function is used for initializing the values for SPI2 peripheral*/

SPI_Handle_T SPI2handle;
void SPI2_Init() {

	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.DFF = SPI_DFF_8_BIT;
	SPI2handle.SPIConfig.Speed = SPI_SCLK_SPEED_DIV128;
	SPI2handle.SPIConfig.CPOL = SPI_CPOL_0;
	SPI2handle.SPIConfig.CPHA = SPI_CPHA_0;
	SPI2handle.SPIConfig.SSM = SPI_SSM_SW;

	SPI_Init(&SPI2handle);
}

/* Main Function*/

int main(void) {
	SPI2handle.pSPIx = SPI2;
	char user_data[] = "Hello world";
	SPI2_Init();
	SPI_GPIO_Config(&SPI2handle);
	SPI_Tx(SPI2, (uint8_t*) user_data, strlen(user_data));
	while (1)
		;
	return 0;

}
