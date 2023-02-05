/***********************************************************************
NOTES:
* 
*
***********************************************************************/
#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include "stm32f446xx.h"
#include <stdint.h>
#include <stddef.h>

/*
****   USER CONFIGURABLE MACROS ***
*/

#define ENABLE  				1U
#define DISABLE 				0U
#define SET						ENABLE
#define RESET					DISABLE
#define SPI_READY				0U
#define SPI_BUSY_TRANSMIT		1U
#define SPI_BUSY_RECEIVE		2U
#define SPI_Transmit_EVENT		1	
#define SPI_Receive_EVENT		2
#define SPI_OVR_EVENT			3

/**
* @DeviceMode
*/
#define SLAVE 					0U
#define MASTER					1U

/**
* @BusConfig
*/
#define FULL_DUPLEX				1U		
#define HALF_DUPLEX				2U
#define SIMPLEX_RXonly			3U

/**
* @BaudRate
*/
#define CLOCK_PRESCALAR_2		0
#define CLOCK_PRESCALAR_4		1
#define CLOCK_PRESCALAR_8		2
#define CLOCK_PRESCALAR_16		3
#define CLOCK_PRESCALAR_32		4
#define CLOCK_PRESCALAR_64		5
#define CLOCK_PRESCALAR_128		6	
#define CLOCK_PRESCALAR_256		7

/**
* @CPOL
*/
#define CPOL_LOW_IDLE			0U
#define CPOL_HIGH_IDLE			1U

/**
* @CPHA
*/
#define CPHA_LEADING 			0U	
#define CPHA_TRAILING			1U

/**
* @SSM
*/
#define SSM_ENABLE			1U
#define SSM_DISABLE			0U


/**
* @SSI
*/
#define SSI_ENABLE			1U
#define SSI_DISABLE			0U

/**
* @SSOE
*/
#define SSOE_ENABLE			1U
#define SSOE_DISABLE		0U

/**
* @DFF
*/
#define DFF_8bit				0U
#define DFF_16bit				1U


/*
****SPI PERIPHERAL CLOCK ENABLE & DISABLE MACROS  ***
*/

#define SPI1_CLOCK_ENABLE()			(RCC->APB2ENR |=  (1U << 12))
#define SPI2_CLOCK_ENABLE()			(RCC->APB1ENR |=  (1U << 14))
#define SPI3_CLOCK_ENABLE()			(RCC->APB1ENR |=  (1U << 15))
#define SPI4_CLOCK_ENABLE()			(RCC->APB2ENR |=  (1U << 13))

#define SPI1_CLOCK_DISABLE()		(RCC->APB2ENR &= ~(1U << 12))
#define SPI2_CLOCK_DISABLE()		(RCC->APB1ENR &= ~(1U << 14))
#define SPI3_CLOCK_DISABLE()		(RCC->APB1ENR &= ~(1U << 15))
#define SPI4_CLOCK_DISABLE()		(RCC->APB2ENR &= ~(1U << 13))


/*
***SPI RESET MACROS***
*/

#define SPI1_RESET()				(RCC->APB2RSTR |=  (1U << 12))
#define SPI2_RESET()				(RCC->APB1RSTR |=  (1U << 14))
#define SPI3_RESET()				(RCC->APB1RSTR |=  (1U << 15))
#define SPI4_RESET()				(RCC->APB2RSTR |=  (1U << 13))

/*
**** SPI CONIGURATION STRUCTURE ***
*/

typedef struct 
{
	SPI_TypeDef *pSPIx;
	
	struct SPi_config_t
		{
			uint32_t DeviceMode; // Refer to <@DeviceMode>
			uint32_t BusConfig;  // Refer to <@BusConfig>
			uint32_t BaudRate;   // Refer to <@BaudRate>
			uint32_t DFF;        // Refer to <@DFF>
			uint32_t CPOL;       // Refer to <@CPOL>
			uint32_t CPHA;       // Refer to <@CPHA>
			uint32_t SSM;	     // Refer to <@SSM>
			uint32_t SSI;	     // Refer to <@SSI>
			uint32_t SSOE;	     // Refer to <@SSOE>
		}SPIConfig;
	
	uint16_t *Txbuffer; 		// store the address of Txbuffer
	uint16_t *Rxbuffer;			// store the address of Rxbuffer
	uint32_t Txlen;				// store the length of Txbuffer
	uint32_t Rxlen;				// store the length of Rxbuffer
	uint32_t Txstate;			// store the state of Txbuffer
	uint32_t Rxstate;			// store the state of Rxbuffer
		
}SPI_handle_t;

/*
**** DRIVER APIs PROTOTYPES ***
*/

/*  1- SPIx clock control */
void SPI_CLK_CTRL(SPI_TypeDef *pSPIx, uint8_t status);

/*  2- SPIx init and de-init */
void SPI_Init(SPI_handle_t *SPIhandle);
void SPI_DeInit(SPI_TypeDef *pSPIx);

	
/*  3- SPIx Data send and receive */
void SPI_Transmit(SPI_TypeDef *pSPIx, uint16_t *TxBuffer, uint32_t Len);
void SPI_Receive(SPI_TypeDef *pSPIx, uint16_t *RxBuffer, uint32_t Len);

uint32_t SPI_Transmit_IT(SPI_handle_t *SPIhandle, uint16_t *TxBuffer, uint32_t Len);
uint32_t SPI_Receive_IT(SPI_handle_t *SPIhandle, uint16_t *RxBuffer, uint32_t Len);

/*  4- IRQ configuration and ISR handling */
void SPI_IRQConfig(IRQn_Type IRQNumber, uint8_t status);
void SPI_IRQSetPriority(IRQn_Type IRQNumber, uint8_t IRQPrio);
void SPI_IRQ_Handler(SPI_handle_t *SPIhandle);

/*	5- Other important APIs	*/

void SPI_ENABLE(SPI_TypeDef *pSPIx);
void SPI_DISABLE(SPI_TypeDef *pSPIx);
uint8_t SPI_Busy(SPI_TypeDef *pSPIx);
uint8_t GET_RXNE(SPI_TypeDef *pSPIx);
uint8_t GET_TXE(SPI_TypeDef *pSPIx); 
void SPI_CloseTransmission(SPI_handle_t *SPIhandle);
void SPI_CloseReceiption(SPI_handle_t *SPIhandle);
void SPI_OVRclear(SPI_handle_t *SPIhandle);
__WEAK void SPI_AppEventCallBack(SPI_handle_t *SPIhandle, uint8_t EVENT);

#endif //SPI_DRIVER_H 
