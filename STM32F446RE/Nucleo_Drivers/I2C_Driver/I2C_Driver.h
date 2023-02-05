/***********************************************************************
NOTES:
* 
*
***********************************************************************/
#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include "stm32f446xx.h"
#include <stdint.h>
#include <stddef.h>

/*
****   USER CONFIGURABLE MACROS ***
*/
#define ENABLE  			1U
#define DISABLE 			0U
#define SET					ENABLE
#define RESET				DISABLE

#define HSI					0U	
#define HSE					1U
#define PLL					2U	
#define PLLR				3U




/**
* @SCL
*/
#define SM_100KHz					100000U
#define FM_200KHz					200000U
#define FM_400KHz					400000U

/**
* @AckControl
*/
#define NoACK  			   	0U
#define ACK				   	1U


/**
* @FMDutyCycle
*/	
#define	Mode_2				0U
#define Mode_16_9			1U




/**
* @TxRxState
*/	
#define	I2C_READY				0U
#define I2C_BUSY_RX				1U
#define I2C_BUSY_TX				2U

/**
* @SR
*/
#define ENABLE_SR  			   		1U
#define DISABLE_SR				   	0U


/**
* @AppEventCallBack
*/	
#define	I2C_EV_TX_DONE				0
#define I2C_EV_STOPF				1	
#define I2C_EV_RX_DONE				2
#define I2C_ERROR_BERR  			3
#define I2C_ERROR_ARLO  			4
#define I2C_ERROR_AF    			5
#define I2C_ERROR_OVR   			6
#define I2C_ERROR_TIMEOUT 			7
#define I2C_EV_DataReq				8
#define I2C_EV_DataReceived			9
/*
****I2C PERIPHERAL CLOCK ENABLE & DISABLE MACROS  ***
*/

#define I2C1_CLOCK_ENABLE()			(RCC->APB1ENR |=  (1U << 21))
#define I2C2_CLOCK_ENABLE()			(RCC->APB1ENR |=  (1U << 22))
#define I2C3_CLOCK_ENABLE()			(RCC->APB1ENR |=  (1U << 23))

#define I2C1_CLOCK_DISABLE()		(RCC->APB1ENR &= ~(1U << 21))
#define I2C2_CLOCK_DISABLE()		(RCC->APB1ENR &= ~(1U << 22))
#define I2C3_CLOCK_DISABLE()		(RCC->APB1ENR &= ~(1U << 23))


/*
***I2C RESET MACROS***
*/

#define I2C1_RESET()				(RCC->APB1RSTR |=  (1U << 21))
#define I2C2_RESET()				(RCC->APB1RSTR |=  (1U << 22))
#define I2C3_RESET()				(RCC->APB1RSTR |=  (1U << 23))

#define I2C1_RESET_CLEAR()			(RCC->APB1RSTR &=  ~(1U << 21))
#define I2C2_RESET_CLEAR()			(RCC->APB1RSTR &=  ~(1U << 22))
#define I2C3_RESET_CLEAR()			(RCC->APB1RSTR &=  ~(1U << 23))
/*
**** I2C CONFIGURATION STRUCTURE ***
*/

typedef struct 
{
	I2C_TypeDef *pI2Cx;
	
	struct I2C_config_t
		{
			uint32_t SCLspeed;					// Refer to <@SCL>
			uint32_t AckControl;				// Refer to <@AckControl>
			uint32_t FMDutyCycle;				// Refer to <@FMDutyCycle>			
		}I2CConfig;
	uint32_t TxLen;								/* Store TxBuffer Length*/
	uint32_t RxLen;								/* Store RxBuffer Length*/
	uint8_t TxRxState;							// Refer to <@TxRxState>					
	uint32_t RxSize;								/* Store Rx Size*/
	uint8_t *pTxBuffer;							/* Store the address of TxBuffer*/
	uint8_t *pRxBuffer;							/* Store the address of RxBuffer*/		
	uint8_t SR;									/* Store repeated start value*/
	uint8_t DevAddr;							/* Store device address*/
		
}I2C_handle_t;
/*
**** DRIVER APIs PROTOTYPES ***
*/

/*  1- I2Cx clock control */
void I2C_CLK_CTRL(I2C_TypeDef *pI2Cx, uint8_t status);

/*  2- I2Cx init and de-init */
void I2C_Init(I2C_handle_t *I2Chandle);
void I2C_DeInit(I2C_TypeDef *pI2Cx);

	
/*  3- I2Cx Data send and receive */
void I2CMasterSend(I2C_handle_t *I2Chandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddress);
void I2CMasterReceive(I2C_handle_t *I2Chandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddress);

uint8_t I2CMasterSendIT(I2C_handle_t *I2Chandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddress, uint8_t SR);
uint8_t I2CMasterReceiveIT(I2C_handle_t *I2Chandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddress, uint8_t SR);

void I2CSlaveSend(I2C_TypeDef *pI2Cx, uint8_t data);
uint8_t I2CSlaveReceive(I2C_TypeDef *pI2Cx);

/*  4- IRQ configuration and ISR handling */
void I2C_IRQConfig(IRQn_Type IRQNumber, uint8_t status);
void I2C_IRQSetPriority(IRQn_Type IRQNumber, uint8_t IRQPrio);
void I2C_EV_IRQHandle(I2C_handle_t *I2Chandle);
void I2C_ER_IRQHandle(I2C_handle_t *I2Chandle);

/*	5- Other important APIs	*/

void I2C_ENABLE(I2C_TypeDef *pI2Cx);
void I2C_DISABLE(I2C_TypeDef *pI2Cx);
uint32_t RCC_GetPCLK1_HZ(void);
void SET_SWRST(I2C_TypeDef *pI2Cx);
void RESET_SWRST(I2C_TypeDef *pI2Cx);
void I2C_SendDone(I2C_handle_t *I2Chandle);
void I2C_ReceiveDone(I2C_handle_t *I2Chandle);
void I2C_GenStart(I2C_TypeDef *pI2Cx);
void I2C_GenStop(I2C_TypeDef *pI2Cx);
uint8_t GET_Status(I2C_TypeDef *pI2Cx, uint32_t FLAG);

__WEAK void I2C_AppEventCallBack(I2C_handle_t *I2Chandle, uint8_t EVENT);






#endif	//I2C_DRIVER_H
