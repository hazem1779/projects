 #include "stm32f446xx.h"
 #include "spi_driver.h"
 
 static void spi_tx_interrupt_handle(SPI_handle_t *SPIhandle);
 static void spi_rx_interrupt_handle(SPI_handle_t *SPIhandle);
 static void spi_err_interrupt_handle(SPI_handle_t *SPIhandle);
 
/*
**** DRIVER APIs IMPLEMENTATION ***
*NOTE: Every function has a documentation before its implementation*
*/

//  1- SPIx clock control //

/**
* @brief					- This Function is used to enable or disable clock for a SPI peripheral.
* @parameter [pSPIx]		- Address of a SPI peripheral, examble: SPI1 address.
* @parameter [status]		- Enable or Disable Macros.	
* @returnType 				- None.
* @Notes					- None.
**/
void SPI_CLK_CTRL(SPI_TypeDef *pSPIx, uint8_t status)
{
	if (status == ENABLE)
	{
		if (pSPIx == SPI1)
		{
			SPI1_CLOCK_ENABLE();
		}
		else if (pSPIx == SPI2)
		{
			SPI2_CLOCK_ENABLE();
		}
		else if (pSPIx == SPI3)
		{
			SPI3_CLOCK_ENABLE();			
		}
		else if (pSPIx == SPI4)
		{
			SPI4_CLOCK_ENABLE();			
		}	
	}
	else
	{
		if (pSPIx == SPI1)
		{
			SPI1_CLOCK_DISABLE();
		}
		else if (pSPIx == SPI2)
		{
			SPI2_CLOCK_DISABLE();
		}
		else if (pSPIx == SPI3)
		{
			SPI3_CLOCK_DISABLE();			
		}
		else if (pSPIx == SPI4)
		{
			SPI4_CLOCK_DISABLE();			
		}			
	}

}

//  2- SPIx init and de-init //

/**
* @brief					- Initialize SPI peripheral.
* @parameter [SPIhandle]	- The address to SPI_handle_t structure.	
* @returnType 				- None.
* @Notes					- Bit definition macros are used from the header file   "stm32f446xx.h". 
							- User configurable macros are defined in "spi_driver.h".
**/
void SPI_Init(SPI_handle_t *SPIhandle)
{
	//SPI_CR1
	
	SPIhandle->pSPIx->CR1 = 0x00000000U; //clearing the register
	
	SPIhandle->pSPIx->CR1 |= (SPIhandle->SPIConfig.CPHA << SPI_CR1_CPHA_Pos); 
	SPIhandle->pSPIx->CR1 |= (SPIhandle->SPIConfig.CPOL << SPI_CR1_CPOL_Pos); 
	SPIhandle->pSPIx->CR1 |= (SPIhandle->SPIConfig.DeviceMode << SPI_CR1_MSTR_Pos); 
	SPIhandle->pSPIx->CR1 |= (SPIhandle->SPIConfig.BaudRate << SPI_CR1_BR_Pos); 
	SPIhandle->pSPIx->CR1 |= (SPIhandle->SPIConfig.SSM << SPI_CR1_SSM_Pos); 
	SPIhandle->pSPIx->CR1 |= (SPIhandle->SPIConfig.DFF << SPI_CR1_DFF_Pos);
	SPIhandle->pSPIx->CR1 |= (SPIhandle->SPIConfig.SSI << SPI_CR1_SSI_Pos);
	SPIhandle->pSPIx->CR2 |= (SPIhandle->SPIConfig.SSOE << SPI_CR2_SSOE_Pos);	
	
	if (SPIhandle->SPIConfig.BusConfig == FULL_DUPLEX)
	{
		SPIhandle->pSPIx->CR1 &= ~(1U << SPI_CR1_BIDIMODE_Pos); 			//2-line unidirectional
	}
	else if (SPIhandle->SPIConfig.BusConfig == HALF_DUPLEX)
	{
		SPIhandle->pSPIx->CR1 |= (1U << SPI_CR1_BIDIMODE_Pos);				//1-line bidirectional
	}
	else if (SPIhandle->SPIConfig.BusConfig == SIMPLEX_RXonly)
	{
		SPIhandle->pSPIx->CR1 &= ~(1U << SPI_CR1_BIDIMODE_Pos);				//Keep BIDIMODE clear
		SPIhandle->pSPIx->CR1 |=  (1U << SPI_CR1_RXONLY_Pos);				//RxOnly bit must be set to force the clock to be produced 
	}
	
}

/**
* @brief					- This finction is used to reset the SPI peripheral.
* @parameter[pSPIx]			- Address of the SPI peripheral.
* @returnType 				- None.
* @Notes					- None.
**/
void SPI_DeInit(SPI_TypeDef *pSPIx)
{
	if (pSPIx == SPI1)
	{
		SPI1_RESET();
	}
	else if (pSPIx == SPI2)
	{
		SPI2_RESET();
	}
	else if (pSPIx == SPI3)
	{
		SPI3_RESET();			
	}
	else if (pSPIx == SPI4)
	{
		SPI4_RESET();			
	}	
}



//  3- Data send and receive //

/**
* @brief					- This finction is used to send data.
* @parameter[pSPIx]			- Address of the SPI peripheral.	
* @parameter[TxBuffer]		- Address of buffer from which the data will be sent.	
* @parameter[Len]			- Length of the data to be sent. 
* @returnType 				- None.
* @Notes					- This API is blocking (the functions waits until all bytes are transmitted).
**/

void SPI_Transmit(SPI_TypeDef *pSPIx, uint16_t *TxBuffer, uint32_t Len)
{
	uint32_t status = 0;
	uint8_t *pBYTE = ((uint8_t*)TxBuffer);
	
	status = GET_TXE(pSPIx);	
	while(!status);
	
	while(Len > 0)
	{		
		if(pSPIx->CR1 & SPI_CR1_DFF)
		{
			pSPIx->DR = *TxBuffer;
			--Len;
			--Len;
			++TxBuffer;
		}
		else
		{
			pSPIx->DR = *pBYTE;
			--Len;
			++pBYTE; //pBYTE pointing to next byte
		}
	}		
}

/**
* @brief					- This finction is used to receive data.
* @parameter[pSPIx]			- Address of the SPI peripheral.	
* @parameter[RxBuffer]		- Address of buffer to which the data will be read.
* @parameter[Len]			- Length(in bytes) of the data to be sent. 	
* @returnType 				- None.
* @Notes					- None.
**/
void SPI_Receive(SPI_TypeDef *pSPIx, uint16_t *RxBuffer, uint32_t Len)
{
	uint32_t status = 0;
	uint8_t *pBYTE = ((uint8_t*)RxBuffer);
	
	status = GET_RXNE(pSPIx);	
	while(!status);
	
	while(Len > 0)
	{		
		if(pSPIx->CR1 & SPI_CR1_DFF)
		{
			*RxBuffer =(uint16_t)pSPIx->DR ;
			--Len;
			--Len;
			++RxBuffer;
		}
		else
		{
			*pBYTE =(uint8_t) pSPIx->DR;
			--Len;
			++pBYTE; //pBYTE pointing to next byte
		}
	}			
}

uint32_t SPI_Transmit_IT(SPI_handle_t *SPIhandle, uint16_t *TxBuffer, uint32_t Len)
{
	uint32_t state = SPIhandle->Txstate;
	if (state != SPI_BUSY_TRANSMIT)	
	{
		//1.Save the TxBuffer address and length in some global variable
		SPIhandle->Txbuffer = TxBuffer;
		SPIhandle->Txlen = Len;
		
		//2.Mark the SPI state as busy so no other code
		//can take over the same spi peripheral until transmission ends
		SPIhandle->Txstate = SPI_BUSY_TRANSMIT;
		
		//3.Enable TXIE bit so an interrupt can be generated whenever TXE is set in SR
		SPIhandle->pSPIx->CR2 |= SPI_CR2_TXEIE;
		
		//4.Data transmission is handled by ISR code 
		SPI_IRQ_Handler(SPIhandle);	
	}
	return state;
}

uint32_t SPI_Receive_IT(SPI_handle_t *SPIhandle, uint16_t *RxBuffer, uint32_t Len)
{
	uint32_t state = SPIhandle->Rxstate;
	if (state != SPI_BUSY_RECEIVE)
	{
		//1.Save the RxBuffer address and length in some global variable
		SPIhandle->Rxbuffer = RxBuffer;
		SPIhandle->Rxlen = Len;
		
		//2.Mark the SPI state as busy so no other code
		//can take over the same spi peripheral until Receiving ends
		SPIhandle->Rxstate = SPI_BUSY_RECEIVE;
		
		//3.Enable RXNEIE bit so an interrupt can be generated whenever TXE is set in SR
		SPIhandle->pSPIx->CR2 |= SPI_CR2_RXNEIE;
		
		//4.Data transmission is handled by ISR code 
		SPI_IRQ_Handler(SPIhandle);
	}	
	return state;	
}


//  4- IRQ configuration and ISR handling //

/**
* @brief					- Enabling the IRQ or Disabling it. 
* @parameter[IRQNumber]		- IRQ number refered in the enum <IRQn_Type>.
* @parameter[status]		- Enable or Disable.	
* @returnType 				- None. 
* @Notes					- Only 3 register is needed for enabling or disabling 
							  because IRQs biggest number is 96..
**/
void SPI_IRQConfig(IRQn_Type IRQNumber, uint8_t status)
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
void SPI_IRQSetPriority(IRQn_Type IRQNumber, uint8_t IRQPrio)
{
	NVIC->IP[IRQNumber] |= (IRQPrio << __NVIC_PRIO_BITS);	
}


/**
* @brief					- Handling the interrupts
* @parameter[SPIhandle]		- The address to SPI_handle_t structure.	
* @returnType 				- None.	 
* @Notes					- None.
**/
void SPI_IRQ_Handler(SPI_handle_t *SPIhandle)
{
	uint32_t temp1, temp2;
	
	//1.check if the TXE is set
	temp1= (SPIhandle->pSPIx->SR & (SPI_SR_TXE));
	temp2= (SPIhandle->pSPIx->CR2 & (SPI_CR2_TXEIE));
	if(temp1 && temp2)
	{
		spi_tx_interrupt_handle(SPIhandle);
	}
	//2.check if the RXNE is set
	temp1=(SPIhandle->pSPIx->SR & (SPI_SR_RXNE));
	temp2=(SPIhandle->pSPIx->CR2 & (SPI_CR2_RXNEIE));
	if(temp1 && temp2)
	{
		spi_rx_interrupt_handle(SPIhandle);		
	}
	
	//3.check if the OVR is set
	temp1=(SPIhandle->pSPIx->SR & (SPI_SR_OVR));
	temp2=(SPIhandle->pSPIx->CR2 & (SPI_CR2_ERRIE));
	if(temp1 && temp2)
	{
		spi_err_interrupt_handle(SPIhandle);		
	}
}

//	5- Other important APIs	//

//spi_enable
void SPI_ENABLE(SPI_TypeDef *pSPIx)
{
	pSPIx->CR1 |= (1U << 6);	
}
//spi_disable
void SPI_DISABLE(SPI_TypeDef *pSPIx)
{
	pSPIx->CR1 &= ~(1U << 6);	
}

//spi_busy
uint8_t SPI_Busy(SPI_TypeDef *pSPIx)
{
	return (pSPIx->SR & SPI_SR_BSY);
}
//get RXNE status
uint8_t GET_RXNE(SPI_TypeDef *pSPIx)
{
		return (pSPIx->SR & SPI_SR_RXNE);
}

//get TXE status
uint8_t GET_TXE(SPI_TypeDef *pSPIx)
{
		return (pSPIx->SR & SPI_SR_TXE);
}

//application callback fuctions
__WEAK void SPI_AppEventCallBack(SPI_handle_t *SPIhandle, uint8_t EVENT)
{
	SPIhandle = NULL;
	(void)EVENT;
}
//other APIs
void SPI_CloseTransmission(SPI_handle_t *SPIhandle)
{
	SPIhandle->pSPIx->CR2 &= ~(SPI_CR2_TXEIE);
	SPIhandle->Txbuffer = NULL;
	SPIhandle->Txlen = 0;
	SPIhandle->Txstate = SPI_READY;
}
void SPI_CloseReceiption(SPI_handle_t *SPIhandle)
{
	SPIhandle->pSPIx->CR2 &= ~(SPI_CR2_RXNEIE);
	SPIhandle->Rxbuffer = NULL;
	SPIhandle->Rxlen = 0;
	SPIhandle->Rxstate = SPI_READY;	
}
void SPI_OVRclear(SPI_handle_t *SPIhandle)
{
	uint32_t temp;
	temp = SPIhandle->pSPIx->DR;
	temp = SPIhandle->pSPIx->SR;
}

/*private fuctions to this file*/
 static void spi_tx_interrupt_handle(SPI_handle_t *SPIhandle)
 {
	uint32_t status = 0;
	uint8_t *pBYTE = ((uint8_t*)SPIhandle->Txbuffer);
	
	status = GET_TXE(SPIhandle->pSPIx);	
	while(!status);
	
	while(SPIhandle->Txlen > 0)
	{		
		if(SPIhandle->pSPIx->CR1 & SPI_CR1_DFF)
		{
			SPIhandle->pSPIx->DR = *(SPIhandle->Txbuffer);
			--(SPIhandle->Txlen);
			--(SPIhandle->Txlen);
			++(SPIhandle->Txbuffer);
		}
		else
		{
			SPIhandle->pSPIx->DR = *pBYTE;
			--(SPIhandle->Txlen);
			++pBYTE; //pBYTE pointing to next byte
		}
	}
	
	if(!SPIhandle->Txlen)
	{
		//close the transmission 
		SPI_CloseTransmission(SPIhandle);
		//inform the application
		SPI_AppEventCallBack(SPIhandle, SPI_Transmit_EVENT);
	}	
 }
 static void spi_rx_interrupt_handle(SPI_handle_t *SPIhandle)
 {
	uint32_t status = 0;
	uint8_t *pBYTE = ((uint8_t*)SPIhandle->Rxbuffer);
	
	status = GET_RXNE(SPIhandle->pSPIx);	
	while(!status);
	
	while(SPIhandle->Rxlen > 0)
	{		
		if(SPIhandle->pSPIx->CR1 & SPI_CR1_DFF)
		{
			*(SPIhandle->Rxbuffer) =(uint16_t)(SPIhandle->pSPIx->DR);
			--(SPIhandle->Rxlen);
			--(SPIhandle->Rxlen);
			++(SPIhandle->Rxbuffer);
		}
		else
		{
			*pBYTE =(uint8_t) (SPIhandle->pSPIx->DR);
			--(SPIhandle->Rxlen);
			++pBYTE; //pBYTE pointing to next byte
		}
	}
	if(!SPIhandle->Rxlen)
	{
		//close the receiption
		SPI_CloseReceiption(SPIhandle);
		//inform the application
		SPI_AppEventCallBack(SPIhandle, SPI_Receive_EVENT);
	}
 }
 static void spi_err_interrupt_handle(SPI_handle_t *SPIhandle)
 {
	//1. clear the OVR bit
	SPI_OVRclear(SPIhandle);	 
	//2.inform the application
	SPI_AppEventCallBack(SPIhandle, SPI_OVR_EVENT);	 
 }
