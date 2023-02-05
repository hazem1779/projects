#ifndef USART_DRIVER_H
#define USART_DRIVER_H

#include "stm32f446xx.h"
#include "RCC_CLOCK.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

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
*@Mode
*/
#define ONLY_TX				0U
#define ONLY_RX				1U
#define TX_RX				2U


/**
*@BaudRate
*/
#define BR_1200				1200U
#define BR_2400				2400U
#define BR_4800				4800U
#define BR_9600				9600U
#define BR_19200			19200U
#define BR_38400			38400U
#define BR_57600			57600U
#define BR_115200			115200U
#define BR_230400			230400U
#define BR_460800			460800U
#define BR_921600			921600U
#define BR_2M				2000000U
#define BR_3M				30000000U

/**
*@NumOfStops Note: The 0.5 Stop bit and 1.5 Stop bit are not available for UART4 & UART5.
*/

#define STOP_1		0U
#define STOP_0_5	1U
#define	STOP_2		2U
#define	STOP_1_5	3U



/**
*@WordLength
*/
#define ONE_START_8_DATA	0U
#define ONE_START_9_DATA	1U


/**
*@ParityCtrl
*/
#define PARITY_DISABLED		0U
#define PARITY_ENABLED		1U


/**
*@ParitySelect
*/
#define EVEN_PARITY			0U
#define	ODD_PARITY			1U


/**
*@HWFlowCtrl
*/
#define HW_DISABLED		0U
#define CTS_ONLY		1U
#define	RTS_ONLY   		2U
#define CTS_RTS			3U

/**
*@StatusFlags NOTE: Refer to section <Bit definition for USART_SR register> in stm32f446xx.h file***
*/


/*
****USART & UART PERIPHERAL CLOCK ENABLE & DISABLE MACROS  ***
*/

#define USART1_CLOCK_ENABLE()			(RCC->APB2ENR |=  (1U << 4))
#define USART6_CLOCK_ENABLE()			(RCC->APB2ENR |=  (1U << 5))

#define USART2_CLOCK_ENABLE()			(RCC->APB1ENR |=  (1U << 17))
#define USART3_CLOCK_ENABLE()			(RCC->APB1ENR |=  (1U << 18))
#define UART4_CLOCK_ENABLE()			(RCC->APB1ENR |=  (1U << 19))
#define UART5_CLOCK_ENABLE()			(RCC->APB1ENR |=  (1U << 20))



#define USART1_CLOCK_DISABLE()			(RCC->APB2ENR &=  ~(1U << 4))
#define USART6_CLOCK_DISABLE()			(RCC->APB2ENR &=  ~(1U << 5))

#define USART2_CLOCK_DISABLE()			(RCC->APB1ENR &=  ~(1U << 17))
#define USART3_CLOCK_DISABLE()			(RCC->APB1ENR &=  ~(1U << 18))
#define UART4_CLOCK_DISABLE()			(RCC->APB1ENR &=  ~(1U << 19))
#define UART5_CLOCK_DISABLE()			(RCC->APB1ENR &=  ~(1U << 20))


/*
***USART & UART RESET & RESET_CLEAR MACROS***
*/

#define USART1_RESET()			(RCC->APB2RSTR |=  (1U << 4))
#define USART6_RESET()			(RCC->APB2RSTR |=  (1U << 5))

#define USART2_RESET()			(RCC->APB1RSTR |=  (1U << 17))
#define USART3_RESET()			(RCC->APB1RSTR |=  (1U << 18))
#define UART4_RESET()			(RCC->APB1RSTR |=  (1U << 19))
#define UART5_RESET()			(RCC->APB1RSTR |=  (1U << 20))



#define USART1_RESET_CLEAR()			(RCC->APB2RSTR &=  ~(1U << 4))
#define USART6_RESET_CLEAR()			(RCC->APB2RSTR &=  ~(1U << 5))

#define USART2_RESET_CLEAR()			(RCC->APB1RSTR &=  ~(1U << 17))
#define USART3_RESET_CLEAR()			(RCC->APB1RSTR &=  ~(1U << 18))
#define UART4_RESET_CLEAR()				(RCC->APB1RSTR &=  ~(1U << 19))
#define UART5_RESET_CLEAR()				(RCC->APB1RSTR &=  ~(1U << 20))

/*
**** USART & UART CONFIGURATION STRUCTURE ***
*/

typedef struct 
{
	USART_TypeDef *pUSARTx;
	
	struct USART_config_t
		{
			uint8_t Mode;					//Refer to <@Mode>
			uint32_t BaudRate;				//Refer to <@BaudRate>
			uint8_t NumOfStops;				//Refer to <@NumOfStops>
			uint8_t WordLength;				//Refer to <@WordLength>
			uint8_t ParityCtrl;				//Refer to <@ParityCtrl>
			uint8_t ParitySelect;			//Refer to <@ParitySelect>			
			uint8_t HWFlowCtrl;				//Refer to <@HWFlowCtrl>
		}USARTConfig;
	
}USART_handle_t;


/*
**** DRIVER APIs PROTOTYPES ***
*/


/* USARTx clock control */
void USART_Clk_Ctrl(USART_TypeDef *pUSARTx, uint8_t status);
/*************************************************************************/


/* USARTx init and de-init */
void USART_Init(USART_handle_t *USARThandle);
void USART_Deinit(USART_TypeDef *pUSARTx);
/*************************************************************************/


/* USARTx Transmit and Receive APIs */
void USART_SendData(USART_handle_t *USARThandle, uint8_t *pTxBuffer, uint32_t len);
void USART_ReceiveData(USART_handle_t *USARThandle, uint8_t *pRxBuffer, uint32_t len);
uint8_t USART_SendDataIT (USART_handle_t *USARThandle, uint8_t *pTxBuffer, uint32_t len);
uint8_t USART_ReceiveDataIT(USART_handle_t *USARThandle, uint8_t *pTxBuffer, uint32_t len);
/*************************************************************************/

/* IRQ configuration and ISR handling */
void USART_IRQConfig(IRQn_Type IRQNumber, uint8_t status);
void USART_IRQSetPriority(IRQn_Type IRQNumber, uint8_t IRQPrio);
void USART_IRQHandle(USART_handle_t *USARThandle);
/*************************************************************************/




/* Other important APIs	*/

uint8_t Get_FlagStatus(USART_TypeDef *pUSARTx, uint32_t FLAG);
void Clear_FlagStatus(USART_TypeDef *pUSARTx, uint32_t FLAG);
void Usart_Enable(USART_TypeDef *pUSARTx);
void Usart_Disable(USART_TypeDef *pUSARTx);
uint8_t Transmission_Done(USART_TypeDef *pUSARTx);
void USART_SetBaudRate(USART_TypeDef *pUSARTx, uint32_t BaudRate);
void USART_Peripheral(USART_TypeDef *pUSARTx, uint8_t state);
/*************************************************************************/



#endif //USART_DRIVER_H