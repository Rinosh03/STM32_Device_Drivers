/*
 * SPI_Driver.h
 *
 *  Created on: 02-Jan-2026
 *      Author: rinos
 */

#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_
#include "stm32f411xe.h"

typedef struct
{
	uint32_t DeviceMode;
	uint32_t BusConfig;
	uint32_t DFF;
	uint32_t CPOL;
	uint32_t CPHA;
	uint32_t SSM;
	uint32_t Speed;
}SPI_Config_T;

typedef struct
{
	SPI_RegDef *pSPIx;
	SPI_Config_T SPIConfig;
	uint8_t *pTxBuffer;
	uint8_t *pRxBuffer;
	uint32_t TxLen;
	uint32_t RxLen;
	uint8_t TxState;
	uint8_t RxState;
}SPI_Handle_T;

/************************************SPI Configurations***********************************************/
/*
 *
 * @DeviceMode
 **/
#define SPI_DEVICE_MODE_MASTER			1
#define SPI_DEVICE_MODE_SLAVE			0

/*
 *
 *
 * @BusConfig
 */

#define SPI_BUS_CONFIG_FD				1
#define SPI_BUS_CONFIG_HD				2
#define SPI_BUS_CONFIG_SIMPLEX_RX_ONLY	3

/*
 *
 *
 * @DFF
 */
#define SPI_DFF_8_BIT			0
#define SPI_DFF_16_BIT			1

/*
 *
 *
 * @CPOL
 */
#define SPI_CPOL_0				0
#define SPI_CPOL_1				1

/*
 *
 * @CPHA
 */
#define SPI_CPHA_0				0
#define SPI_CPHA_1				1

/*
 *
 * @SSM
 */
#define SPI_SSM_HW				0
#define SPI_SSM_SW				1

/*
 *
 *
 * @Speed
 */
#define SPI_SCLK_SPEED_DIV2			0
#define SPI_SCLK_SPEED_DIV4			1
#define SPI_SCLK_SPEED_DIV8			2
#define SPI_SCLK_SPEED_DIV16		3
#define SPI_SCLK_SPEED_DIV32		4
#define SPI_SCLK_SPEED_DIV64		5
#define SPI_SCLK_SPEED_DIV128		6
#define SPI_SCLK_SPEED_DIV256		7
#define ENABLE						1

/*
 *
 * @Flag status indicator
 */
#define SPI_TXE_FLAG				(1U<<1)
#define SPI_RXNE_FLAG				(1U<<0)
#define SPI_BSY_FLAG				(1U<<7)

/*
 *
 * Possible states
 */
#define SPI_READY					0
#define SPI_BUSY_IN_RX				1
#define SPI_BUSY_IN_TX				2

/*
 *
 * Possible SPI Event states
 */
#define SPI_EVENT_TX_CMPLT				1
#define SPI_EVENT_RX_CMPLT				2
#define SPI_EVENT_OVR_ERR				3
/***************************** APIs supported by SPI ************************************************/

void SPI_Init(SPI_Handle_T *pSPIhandle);
void SPI_DeInit(SPI_Handle_T *pSPIhandle);
void SPI_Tx(SPI_RegDef *pSPIx, uint8_t *pTxbuffer, uint32_t len);
void SPI_Rx(SPI_RegDef *pSPIx, uint8_t *pTxbuffer, uint32_t len);
uint8_t SPI_Tx_IT(SPI_Handle_T *pSPIhandle, uint8_t *pTxbuffer, uint32_t len);
uint8_t SPI_Rx_IT(SPI_Handle_T *pSPIhandle, uint8_t *pRxbuffer, uint32_t len);
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_T *pSPIhandle);
void SPI_GPIO_Config(SPI_Handle_T *pSPIhandle);
void SPI_ClearOVRFlag(SPI_RegDef *pSPIx);
void SPI_Close_TX(SPI_Handle_T *pSPIhandle);
void SPI_Close_Rx(SPI_Handle_T *pSPIhandle);
void SPI_EventCallBack(SPI_Handle_T *pSPIhandle, uint8_t app_ev);
#endif /* SPI_DRIVER_H_ */
