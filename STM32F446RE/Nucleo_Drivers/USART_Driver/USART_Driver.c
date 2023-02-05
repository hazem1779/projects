#include "USART_Driver.h"
  
/***** **** **** **** **** **** **** **** **** **** **** **** **** **** 
		DRIVER APIs IMPLEMENTATION 		
		NOTE: Every function has a documentation before its implementation*
***** **** **** **** **** **** **** **** **** **** **** **** **** ****/ 

/**
* @brief					- This Function is used to enable or disable clock for a USART peripheral.
* @parameter [pUSARTx]		- Address of USART peripheral, examble: USART1 address.
* @parameter [status]		- Enable or Disable Macros.	
* @returnType 				- None.
* @Notes					- None.
**/
void USART_Clk_Ctrl(USART_TypeDef *pUSARTx, uint8_t status)
{
	if (status == ENABLE)
	{
		if (pUSARTx == USART1)
		{
			USART1_CLOCK_ENABLE();
		}
		else if (pUSARTx == USART2)
		{
			USART2_CLOCK_ENABLE();
		}
		else if (pUSARTx == USART3)
		{
			USART3_CLOCK_ENABLE();			
		}
		else if (pUSARTx == UART4)
		{	
			UART4_CLOCK_ENABLE();
		}
		else if (pUSARTx == UART5)
		{
			UART5_CLOCK_ENABLE();
		}
		else if (pUSARTx == USART6)
		{
			USART6_CLOCK_ENABLE();
		}
	}
	else
	{
		if (pUSARTx == USART1)
		{
			USART1_CLOCK_DISABLE();
		}
		else if (pUSARTx == USART2)
		{
			USART2_CLOCK_DISABLE();
		}
		else if (pUSARTx == USART3)
		{
			USART3_CLOCK_DISABLE();			
		}
		else if (pUSARTx == UART4)
		{	
			UART4_CLOCK_DISABLE();
		}
		else if (pUSARTx == UART5)
		{
			UART5_CLOCK_DISABLE();
		}
		else if (pUSARTx == USART6)
		{
			USART6_CLOCK_DISABLE();
		}
	}
}


/**
* @brief					- Initialize USART peripheral.
* @parameter [USARThandle]	- Pointer to USART_handle_t structure.	
* @returnType 				- None.
* @Notes					- Bit definition macros are used from the header file   "stm32f446xx.h". 
							- User configurable macros are defined in "USART_Driver.h".
**/
void USART_Init(USART_handle_t *USARThandle)
{
	//Mode
	if (USARThandle->USARTConfig.Mode == ONLY_TX)
	{
		USARThandle->pUSARTx->CR1 |= USART_CR1_TE;
	}
	else if(USARThandle->USARTConfig.Mode == ONLY_RX)
	{
		USARThandle->pUSARTx->CR1 |= USART_CR1_RE;		
	}
	else if(USARThandle->USARTConfig.Mode == TX_RX)
	{
		USARThandle->pUSARTx->CR1 |= USART_CR1_TE | USART_CR1_RE;		
	}
	
	//Number of stops
	if (USARThandle->USARTConfig.NumOfStops == STOP_1)
	{
		USARThandle->pUSARTx->CR2 |= (STOP_1 << 12);
	}
	else if (USARThandle->USARTConfig.NumOfStops == STOP_0_5)
	{
		USARThandle->pUSARTx->CR2 |= (STOP_0_5 << 12);		
	}
	else if (USARThandle->USARTConfig.NumOfStops == STOP_2)
	{
		USARThandle->pUSARTx->CR2 |= (STOP_2 << 12);		
	}
	else if(USARThandle->USARTConfig.NumOfStops == STOP_1_5)
	{
		USARThandle->pUSARTx->CR2 |= (STOP_1_5 << 12);		
	}
	
	//Word Length
	if (USARThandle->USARTConfig.WordLength == ONE_START_9_DATA)
	{
		USARThandle->pUSARTx->CR1 |= USART_CR1_M;
	}
	else if (USARThandle->USARTConfig.WordLength == ONE_START_8_DATA)
	{
		USARThandle->pUSARTx->CR1 &= ~(USART_CR1_M);		
	}
	
	//Parity Control
	if (USARThandle->USARTConfig.ParityCtrl == PARITY_ENABLED)
	{
		USARThandle->pUSARTx->CR1 |= USART_CR1_PCE;
	}
	else if(USARThandle->USARTConfig.ParityCtrl == PARITY_DISABLED)
	{
		USARThandle->pUSARTx->CR1 &= ~(USART_CR1_PCE);		
	}
	
	//Parity Selection
	if (USARThandle->USARTConfig.ParitySelect == ODD_PARITY)
	{
		USARThandle->pUSARTx->CR1 |= USART_CR1_PS;
	}
	else if(USARThandle->USARTConfig.ParitySelect == EVEN_PARITY)
	{
		USARThandle->pUSARTx->CR1 &= ~(USART_CR1_PS);		
	}

	//Hardware FLow Control
	if (USARThandle->USARTConfig.HWFlowCtrl == HW_DISABLED)
	{
		USARThandle->pUSARTx->CR3 &= ~(USART_CR3_CTSE | USART_CR3_RTSE);		
	}
	else if (USARThandle->USARTConfig.HWFlowCtrl == CTS_ONLY)
	{
		USARThandle->pUSARTx->CR3 |= USART_CR3_CTSE;
	}
	else if (USARThandle->USARTConfig.HWFlowCtrl == RTS_ONLY)
	{
		USARThandle->pUSARTx->CR3 |= USART_CR3_RTSE;
	}
	else if (USARThandle->USARTConfig.HWFlowCtrl == CTS_RTS)
	{
		USARThandle->pUSARTx->CR3 |= (USART_CR3_CTSE | USART_CR3_RTSE);		
	}

	//Baud Rate
	USART_SetBaudRate(USARThandle->pUSARTx,USARThandle->USARTConfig.BaudRate);
}

/**
* @brief 	-Resetting the USARTx Peripheral and clearing the reset state
*/
void USART_Deinit(USART_TypeDef *pUSARTx)
{
	if (pUSARTx == USART1)
	{
		USART1_RESET();
		USART1_RESET_CLEAR();
	}
	else if (pUSARTx == USART2)
	{
		USART2_RESET();
		USART2_RESET_CLEAR();
	}
	else if (pUSARTx == USART3)
	{
		USART3_RESET();
		USART3_RESET_CLEAR();
	}
	else if (pUSARTx == USART6)
	{
		USART6_RESET();
		USART6_RESET_CLEAR();
	}
	else if (pUSARTx == UART4)
	{
		UART4_RESET();
		UART4_RESET_CLEAR();		
	}
	else if (pUSARTx == UART5)
	{
		UART5_RESET();
		UART5_RESET_CLEAR();		
	}
}



/**
* @brief					- API used to send data from a buffer
*/
void USART_SendData(USART_handle_t *USARThandle, uint8_t *pTxBuffer, uint32_t len)
{
	uint16_t *pData;
	for (int i=0; i < len; i++)
	{
		while (!(Get_FlagStatus(USARThandle->pUSARTx,USART_SR_TXE)));
		
		if (USARThandle->USARTConfig.Mode == ONE_START_9_DATA)
		{
			*pData = ( *((uint16_t  *) pTxBuffer) & 0x01FF);
			USARThandle->pUSARTx->DR = *pData;
			if(USARThandle->USARTConfig.ParityCtrl == PARITY_DISABLED)
			{
				pTxBuffer++;
				pTxBuffer++;
			}
			else
			{
				pTxBuffer++;
			}	
		}
		else if(USARThandle->USARTConfig.Mode == ONE_START_8_DATA)
		{
			USARThandle->pUSARTx->DR = *pTxBuffer;
			pTxBuffer++;
		}
	}
			
	//while(!Transmission_Done(USARThandle->pUSARTx));
	//Clear_FlagStatus(USARThandle->pUSARTx, USART_SR_TC);
	
}



/**
* @brief					- Enabling the IRQ or Disabling it. 
* @parameter[IRQNumber]		- IRQ number refered in the enum <IRQn_Type>.
* @parameter[status]		- Enable or Disable.	
* @returnType 				- None. 
* @Notes					- Only 3 register is needed for enabling or disabling 
							  because IRQs biggest number is 96..
**/
void USART_IRQConfig(IRQn_Type IRQNumber, uint8_t status)
{
	//ENABLING THE IRQ ON NVIC SIDE
	if(status == ENABLE)
	{
		if (IRQNumber <= 31)
		{
		NVIC->ISER[0] |= (1 << IRQNumber);
		}
		else if (IRQNumber > 31 && IRQNumber < 64)
		{
		NVIC->ISER[1] |= (1 << IRQNumber % 32);
		}
		else if (IRQNumber >= 64 && IRQNumber < 96)
		{
		NVIC->ISER[2] |= (1 << IRQNumber % 64);
		}	
	}
	//DISABLING THE IRQ ON NVIC SIDE
	else
	{
		if (IRQNumber <= 31)
		{
		NVIC->ICER[0] |= (1 << IRQNumber);
		}
		else if (IRQNumber > 31 && IRQNumber < 64)
		{
		NVIC->ICER[1] |= (1 << IRQNumber % 32);
		}
		else if (IRQNumber >= 64 && IRQNumber < 96)
		{
		NVIC->ICER[2] |= (1 << IRQNumber % 64);
		}				
	}				
}


/**
* @brief					- Setting the priority for the IRQ. 
* @parameter[IRQNumber]		- IRQ number refered in the enum <IRQn_Type>.
* @parameter[IRQPrio]		- Desired priority.	
* @returnType 				- None.
* @Notes					- Priority number should be implemented in the first 4 bits of the byte.
**/
void USART_IRQSetPriority(IRQn_Type IRQNumber, uint8_t IRQPrio)
{
	NVIC->IP[IRQNumber] |= (IRQPrio << __NVIC_PRIO_BITS);
}



/**
* @brief					- This API is used inside the ISR code to handle the USART interrupt request 	
* @parameter[USARThandle]	- USARThandle defined by the user.
* @returnType 				- None.
* @Notes					- None.
**/
void USART_IRQHandle(USART_handle_t *USARThandle)
{
	
}


/**
* @brief					- Getting the status of any given flag 
* @parameter[FLAG]			- Refer to <Bit definition for USART_SR register> in stm32f446xx.h file.
* @returnType 				- SET = 1 or RESET = 0
**/
uint8_t Get_FlagStatus(USART_TypeDef *pUSARTx, uint32_t FLAG)
{
	if (pUSARTx->SR & FLAG)
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}

/**
* @brief					- Clears the status of any given flag based on the stm32f446RE datasheet specs 
* @parameter[FLAG]			- Refer to <Bit definition for USART_SR register> in stm32f446xx.h file.
* @returnType 				- None.
**/
void Clear_FlagStatus(USART_TypeDef *pUSARTx, uint32_t FLAG)
{
	if (FLAG == USART_SR_PE)
	{
		//clear PE flag
	}
	if (FLAG == USART_SR_FE)
	{
		//clear FE flag
	}
	if (FLAG == USART_SR_NE)
	{
		//clear NE flag
	}
	if (FLAG == USART_SR_ORE)
	{
		//clear ORE flag
	}
	if (FLAG == USART_SR_IDLE)
	{
		//clear IDLE flag
	}
	if (FLAG == USART_SR_RXNE)
	{
		//clear RXNE flag
	}
	if (FLAG == USART_SR_TC)
	{
		//clear TC flag
		//cleared by writing zero to it
		pUSARTx->SR &= ~(USART_SR_TC);
	}
	if (FLAG == USART_SR_TXE)
	{
		//clear TXE flag
	}
	if (FLAG == USART_SR_LBD)
	{
		//clear LBD flag
	}
	if (FLAG == USART_SR_CTS)
	{
		//clear CTS flag
	}	
}

/***************** Other Important APIs*******************************/

void Usart_Enable(USART_TypeDef *pUSARTx)
{
	pUSARTx->CR1 |= (USART_CR1_UE);
}
void Usart_Disable(USART_TypeDef *pUSARTx)
{
	pUSARTx->CR1 &= ~(USART_CR1_UE);
}

uint8_t Transmission_Done(USART_TypeDef *pUSARTx)
{
	return (uint8_t)(pUSARTx->SR & USART_SR_TC);
}




void USART_SetBaudRate(USART_TypeDef *pUSARTx, uint32_t BaudRate)
{

	//Variable to hold the APB clock
	uint32_t PCLKx;

	uint32_t usartdiv;

	//variables to hold Mantissa and Fraction values
	uint32_t M_part,F_part;

  uint32_t tempreg=0;

  //Get the value of APB bus clock in to the variable PCLKx
  if(pUSARTx == USART1 || pUSARTx == USART6)
  {
	   //USART1 and USART6 are hanging on APB2 bus
	   PCLKx = RCC_GetPCLK1_HZ();
  }else
  {
	   PCLKx = RCC_GetPCLK2_HZ();
  }

  //Check for OVER8 configuration bit
  if(pUSARTx->CR1 & USART_CR1_OVER8)
  {
	   //OVER8 = 1 , over sampling by 8
	   usartdiv = ((25 * PCLKx) / (2 *BaudRate));
  }else
  {
	   //over sampling by 16
	   usartdiv = ((100 * PCLKx) / (16 *BaudRate));
  }

  //Calculate the Mantissa part
  M_part = usartdiv/100;

  //Place the Mantissa part in appropriate bit position . refer USART_BRR
  tempreg |= M_part << 4;

  //Extract the fraction part
  F_part = (usartdiv - (M_part * 100));

  //Calculate the final fractional
  if(pUSARTx->CR1 & ( USART_CR1_OVER8))
   {
	  //OVER8 = 1 , over sampling by 8
	  F_part = ((( F_part * 8)+ 50) / 100)& ((uint8_t)0x07);

   }else
   {
	   //over sampling by 16
	   F_part = ((( F_part * 16)+ 50) / 100) & ((uint8_t)0x0F);

   }

  //Place the fractional part in appropriate bit position . refer USART_BRR
  tempreg |= F_part;

  //copy the value of tempreg in to BRR register
  pUSARTx->BRR = tempreg;
}

void USART_Peripheral(USART_TypeDef *pUSARTx, uint8_t state)
{
	if(state == ENABLE)
	{
		pUSARTx->CR1 |= (1 << 13);
	}else
	{
		pUSARTx->CR1 &= ~(1 << 13);
	}

}

