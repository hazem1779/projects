#include "I2C_Driver.h"
  
 /*
**** DRIVER APIs IMPLEMENTATION ***
*NOTE: Every function has a documentation before its implementation*
*/

//  1- I2Cx clock control //

/**
* @brief					- This Function is used to enable or disable clock for a I2C peripheral.
* @parameter [pI2Cx]		- Address of a I2C peripheral, examble: I2C1 address.
* @parameter [status]		- Enable or Disable Macros.	
* @returnType 				- None.
* @Notes					- None.
**/
 void I2C_CLK_CTRL(I2C_TypeDef *pI2Cx, uint8_t status)
{
	if (status == ENABLE)
	{
		if (pI2Cx == I2C1)
		{
			I2C1_CLOCK_ENABLE();
		}
		else if (pI2Cx == I2C2)
		{
			I2C2_CLOCK_ENABLE();
		}
		else if (pI2Cx == I2C3)
		{
			I2C3_CLOCK_ENABLE();			
		}
	}
	else
	{
		if (pI2Cx == I2C1)
		{
			I2C1_CLOCK_DISABLE();
		}
		else if (pI2Cx == I2C2)
		{
			I2C2_CLOCK_DISABLE();
		}
		else if (pI2Cx == I2C3)
		{
			I2C3_CLOCK_DISABLE();			
		}	
	}
}

//  2- I2Cx init and de-init //

/**
* @brief					- Initialize I2C peripheral.
* @parameter [I2Chandle]	- Pointer to I2C_handle_t structure.	
* @returnType 				- None.
* @Notes					- Bit definition macros are used from the header file   "stm32f446xx.h". 
							- User configurable macros are defined in "I2C_Driver.h".
**/
void I2C_Init(I2C_handle_t *I2Chandle)
{
	//CR1
	//I2Chandle->pI2Cx->CR1 |= (I2Chandle->I2CConfig.AckControl << I2C_CR1_ACK_Pos);	//ACK bit
	
	//CR2
	uint32_t Fpclk = RCC_GetPCLK1_HZ();
	uint32_t Fpclk_MHz = Fpclk / 1000000U;
	I2Chandle->pI2Cx->CR2 |= (Fpclk_MHz << I2C_CR2_FREQ_Pos) & (0x3FU);  //ABP1 frequency

	//CCR	
    I2Chandle->pI2Cx->CCR |= (I2Chandle->I2CConfig.FMDutyCycle << I2C_CCR_DUTY_Pos); //FM Duty Cycle
	
	/*Calculating and configuring CCR value*/
	uint32_t CCRVALUE,Fscl =0;
	Fscl = I2Chandle->I2CConfig.SCLspeed;
	if (Fscl <= SM_100KHz)	
	{
	    I2Chandle->pI2Cx->CCR &= ~(I2C_CCR_FS_Msk); 	
		CCRVALUE = (Fpclk / (2 * Fscl));
		I2Chandle->pI2Cx->CCR |= (CCRVALUE & 0xFFFU);
	}
	else if (Fscl <= FM_400KHz && Fscl > SM_100KHz)
	{
		I2Chandle->pI2Cx->CCR |= I2C_CCR_FS; 
		if (I2Chandle->I2CConfig.FMDutyCycle == Mode_2)	
		{
			CCRVALUE = (Fpclk / (3 * Fscl));
		    I2Chandle->pI2Cx->CCR |= (CCRVALUE & 0xFFFU);			
		}
		else 
		{
			CCRVALUE = (Fpclk / (25 * Fscl));
		    I2Chandle->pI2Cx->CCR |= (CCRVALUE & 0xFFFU);			
		}	
	}
	
	//OAR1 NOTE: only 7-bit addressing mode is used to test this driver
	I2Chandle->pI2Cx->OAR1 |= ((I2Chandle->DevAddr & 0x7FU ) << 1);
	I2Chandle->pI2Cx->OAR1 |= (1U << 14);
	
	//TRISE
	/************TODO***********/
	double Trise,Trise_max_MicroSec =0;
	
	if (Fscl <= SM_100KHz)	
	{
		Trise_max_MicroSec = 1; //in SM mode, Trise max is 1 microsecond
		Trise = (Trise_max_MicroSec * (double)Fpclk_MHz) + 1U;
	}
	else
	{
		Trise_max_MicroSec = 1; //in FM mode, Trise max is 0.3 microsecond
		Trise_max_MicroSec = 0.3;
		Trise = (Trise_max_MicroSec * (double)Fpclk_MHz) + 1U;		
	}
	I2Chandle->pI2Cx->TRISE = (((uint8_t)Trise) & 0x3F);
	
	
	I2C_ENABLE(I2Chandle->pI2Cx);
}

/**
* @brief					- This finction is used to reset the I2C peripheral.
* @parameter[pI2Cx]			- Address of the I2C peripheral.
* @returnType 				- None.
* @Notes					- None.
**/
void I2C_DeInit(I2C_TypeDef *pI2Cx)
{
	if (pI2Cx == I2C1)
	{
		I2C1_RESET();
		I2C1_RESET_CLEAR();
	}
	else if (pI2Cx == I2C2)
	{
		I2C2_RESET();
		I2C2_RESET_CLEAR();
	}
	else if (pI2Cx == I2C3)
	{
		I2C3_RESET();
		I2C3_RESET_CLEAR();		
	}
}

// 3-1 Master send data API
/**
* @brief					- This finction is used to send data using the device as master
* @parameter[I2Chandle]		- Pointer to I2C_handle_t structure.
* @parameter[pTxBuffer]		- Buffer for the users to enter desired data to be sent
* @parameter[Len]			- Length of the data being sent in bytes	 
* @parameter[SlaveAddress]	- Specific slave address 
* @returnType 				- None.
* @Notes					- SCL is stretched to LOW when any of the flags is set and it is only 							back to its previous state by clearing the flags.
**/


/*********helper functions*********/

static void I2C_WriteMode_Address(I2C_TypeDef *pI2Cx, uint8_t SlaveAddr);
static void I2C_ReadMode_Address(I2C_TypeDef *pI2Cx, uint8_t SlaveAddr);
static void I2C_ClearADDR(I2C_handle_t *I2Chandle);
/**********************************/


void I2CMasterSend(I2C_handle_t *I2Chandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddress)
{
	uint32_t dummy = 0;
	/*GENERATE THE START CONDITION*/	
	I2C_GenStart(I2Chandle->pI2Cx); 
	while(! GET_Status(I2Chandle->pI2Cx, I2C_SR1_SB));
	dummy = I2Chandle->pI2Cx->SR1; //clears SB
	I2Chandle->pI2Cx->CR1 |= (I2Chandle->I2CConfig.AckControl << I2C_CR1_ACK_Pos);	//ACK bit	

	/*WRITE SLAVE ADDDRESS IN DR WITH 8th BIT SET TO 0 (WRITE MODE)*/
	I2C_WriteMode_Address(I2Chandle->pI2Cx,I2Chandle->DevAddr);		
	
	/*WAIT UNTIL ADDR FLAG IS SET THEN CLEARED BY READING SR1 FOLLOWED BY SR2*/
	while(!GET_Status(I2Chandle->pI2Cx, I2C_SR1_ADDR));	
	dummy = I2Chandle->pI2Cx->SR1 | I2Chandle->pI2Cx->SR2;
	
	/*SEND DATA UNTIL LEN IS 0*/
	while(Len > 0)
	{
		while(! GET_Status(I2Chandle->pI2Cx, I2C_SR1_TXE));	//CHECK THE DR REGISTER TO START SENDING THE DATA
		I2Chandle->pI2Cx->DR = *pTxBuffer;
		pTxBuffer++;
		Len--;		
	}
	/*SEND THE STOP BIT TO CLOSE THE COMMUNICATION */
	while( !( (I2Chandle->pI2Cx->SR1 & I2C_SR1_TXE) && (I2Chandle->pI2Cx->SR1 &  I2C_SR1_BTF) ) );	//wait until both flags are set
	I2C_GenStop(I2Chandle->pI2Cx); //Automatically clears BTF flag 
}


// 3-2 Master Receive data API

void I2CMasterReceive(I2C_handle_t *I2Chandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddress)
{
	uint32_t dummy = 0;
	
	/*GENERATE THE START CONDITION*/	
	I2C_GenStart(I2Chandle->pI2Cx); 
	while(! GET_Status(I2Chandle->pI2Cx, I2C_SR1_SB));
	dummy = I2Chandle->pI2Cx->SR1; //clears SB
	
	/*WRITE SLAVE ADDDRESS IN DR WITH 8th BIT SET TO 1 (READ MODE)*/
	I2Chandle->pI2Cx->CR1 |= (I2Chandle->I2CConfig.AckControl << I2C_CR1_ACK_Pos);	//ACK bit after the address byte (slave ACKs)	
	I2C_ReadMode_Address(I2Chandle->pI2Cx,I2Chandle->DevAddr);	
	
	/*Length of data being received is 1 byte*/
	if(Len == 1)
	{
	
		/*WAIT UNTIL ADDR FLAG IS SET*/
		while(!GET_Status(I2Chandle->pI2Cx, I2C_SR1_ADDR));	
		
		/*DISABLE ACKING*/
		I2Chandle->pI2Cx->CR1 &= ~(I2C_CR1_ACK);
		
		/*CLEAR ADDR*/	
		dummy = I2Chandle->pI2Cx->SR1 | I2Chandle->pI2Cx->SR2;
		
		/*WAIT UNTIL RXNE = 1 */
		while(!GET_Status(I2Chandle->pI2Cx, I2C_SR1_RXNE));	
		
		/*GENERATE A STOP*/
		I2C_GenStop(I2Chandle->pI2Cx);
		
		/* READ DATA IN DR*/
		*pRxBuffer = (uint8_t) I2Chandle->pI2Cx->DR;
	}
	
	/*Length of data being received is more than 1 byte*/
	if(Len > 1)
	{
		/*CLEAR ADDR TO START RECEIVING*/	
		dummy = I2Chandle->pI2Cx->SR1 | I2Chandle->pI2Cx->SR2;
		
		/*read data until length becomes zero*/
		for(uint32_t i = Len; i > 0; i--)
		{
			/*WAIT UNTIL RXNE = 1*/
			while(!GET_Status(I2Chandle->pI2Cx, I2C_SR1_RXNE));	
			
			if (i == 2) //last 2 bytes
			{
				/*DISABLE ACKING*/
				I2Chandle->pI2Cx->CR1 &= ~(I2C_CR1_ACK);
				
				/*GENERATE A STOP*/
				I2C_GenStop(I2Chandle->pI2Cx);	
			}
			else
			{	
				*pRxBuffer = (uint8_t) I2Chandle->pI2Cx->DR; 
				pRxBuffer++;	
			}
		}
	}
	//Configuring Acking for the previous status
	if (I2Chandle->I2CConfig.AckControl)
	{
	I2Chandle->pI2Cx->CR1 |= (I2Chandle->I2CConfig.AckControl << I2C_CR1_ACK_Pos);		
	}
}

//3-3 Master send data API (Non-Blocking using interrupts)
uint8_t I2CMasterSendIT(I2C_handle_t *I2Chandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddress, uint8_t SR)
{
	uint8_t state = I2Chandle->TxRxState;
	if ((state != I2C_BUSY_RX)&&(state != I2C_BUSY_TX))
	{
		I2Chandle->pTxBuffer = pTxBuffer;
		I2Chandle->TxRxState = I2C_BUSY_TX;	
		I2Chandle->TxLen 	 = Len;
		I2Chandle->SR		 = SR;
		I2Chandle->DevAddr	 = SlaveAddress;
		
		/*generate start*/
		I2C_GenStart(I2Chandle->pI2Cx);
		
		/*enable IT bits*/
		I2Chandle->pI2Cx->CR2 |= I2C_CR2_ITEVTEN;
		I2Chandle->pI2Cx->CR2 |= I2C_CR2_ITBUFEN;		
		I2Chandle->pI2Cx->CR2 |= I2C_CR2_ITERREN;		
	}
	return state;
}

//3-3 Master receive data API (Non-Blocking using interrupts)
uint8_t I2CMasterReceiveIT(I2C_handle_t *I2Chandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddress, uint8_t SR)
{
	uint8_t state = I2Chandle->TxRxState;
	if ((state != I2C_BUSY_RX)&&(state != I2C_BUSY_TX))
	{
		I2Chandle->pRxBuffer = pRxBuffer;
		I2Chandle->TxRxState = I2C_BUSY_RX;	
		I2Chandle->RxLen 	 = Len;
		I2Chandle->RxSize	 = Len;	
		I2Chandle->SR		 = SR;
		I2Chandle->DevAddr	 = SlaveAddress;
		
		/*generate start*/
		I2C_GenStart(I2Chandle->pI2Cx);
		
		/*enable IT bits*/
		I2Chandle->pI2Cx->CR2 |= I2C_CR2_ITEVTEN;
		I2Chandle->pI2Cx->CR2 |= I2C_CR2_ITBUFEN;		
		I2Chandle->pI2Cx->CR2 |= I2C_CR2_ITERREN;		
	}
	return state;
}

//  3-4 Slave Send Data API
void I2CSlaveSend(I2C_TypeDef *pI2Cx, uint8_t data)
{
	pI2Cx->DR = data;
}


//  3-5 Slave Receive Data API
uint8_t I2CSlaveReceive(I2C_TypeDef *pI2Cx)
{
	return (uint8_t)pI2Cx->DR;
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
void I2C_IRQConfig(IRQn_Type IRQNumber, uint8_t status)
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
void I2C_IRQSetPriority(IRQn_Type IRQNumber, uint8_t IRQPrio)
{
	NVIC->IP[IRQNumber] |= (IRQPrio << __NVIC_PRIO_BITS);	
}

/**
* @brief					- Two functions to handle IRQ Events and Errors 
**/
void I2C_EV_IRQHandle(I2C_handle_t *I2Chandle)
{
	uint32_t temp1,temp2,temp3,dummy;
	
	/*0. Check if the ENABLE CONTROL BIT is enabled*/
	temp1 = (I2Chandle->pI2Cx->CR2 & I2C_CR2_ITEVTEN);
	temp2 = (I2Chandle->pI2Cx->CR2 & I2C_CR2_ITBUFEN);
	
	/*1. Handle the interrupt if SB flag is set*/
	temp3 = (I2Chandle->pI2Cx->SR1 & I2C_SR1_SB);
	if (temp1 && temp3)
	{
		//SB flag 
		//NOTE: SB is only set in Master mode
		//Execute the address phase part
		if (I2Chandle->TxRxState == I2C_BUSY_TX)
		{
			I2C_WriteMode_Address(I2Chandle->pI2Cx,I2Chandle->DevAddr);
		}
		else if (I2Chandle->TxRxState == I2C_BUSY_RX)
		{
			I2C_ReadMode_Address(I2Chandle->pI2Cx,I2Chandle->DevAddr);	
		}
	}
	
	/*2. Handle the interrupt if ADDR flag is set*/
	temp3 = (I2Chandle->pI2Cx->SR1 & I2C_SR1_ADDR);
	if (temp1 && temp3)
	{
		//ADDR flag is set
		//Clear ADDR flag
		//dummy = I2Chandle->pI2Cx->SR1 | I2Chandle->pI2Cx->SR2;
		I2C_ClearADDR(I2Chandle);
	}
	
	/*3. Handle the interrupt if BTF flag is set*/
	temp3 = (I2Chandle->pI2Cx->SR1 & I2C_SR1_BTF);
	if (temp1 && temp3)
	{
		//BTF flag is set

		if (I2Chandle->TxRxState == I2C_BUSY_TX)
		{
			
			//Check the Application state then close communication 
			if(( (I2Chandle->pI2Cx->SR1 & I2C_SR1_TXE) && (I2Chandle->pI2Cx->SR1 &  I2C_SR1_BTF) ) )
			{
				if(I2Chandle->TxLen == 0)
				{
					//wait until both flags are set
					I2C_GenStop(I2Chandle->pI2Cx); //Automatically clears BTF flag
					
					//Reset I2C structure elements
					I2C_SendDone(I2Chandle);
					
					//Notify the application
					I2C_AppEventCallBack(I2Chandle,I2C_EV_TX_DONE);
				}
			}
		}
		else if (I2Chandle->TxRxState == I2C_BUSY_RX)
		{
			;
		}

	}
	
	/*4. Handle the interrupt if STOPF flag is set*/
	/*NOTE: STOP flag is only set by slave*/

	temp3 = (I2Chandle->pI2Cx->SR1 & I2C_SR1_STOPF);
	if (temp1 && temp3)
	{
		//STOPF flag is set
		//Clear the STOPF "Cleared by software reading the SR1 register (temp3) followed by a write in the CR1 register"
		I2Chandle->pI2Cx->CR1 |= 0x00U; 
		//Notify the application
		I2C_AppEventCallBack(I2Chandle,I2C_EV_STOPF);
	}
	
	/*5. Handle the interrupt if TXE flag is set*/
	temp3 = (I2Chandle->pI2Cx->SR1 & I2C_SR1_TXE);
	if (temp1 && temp2 && temp3)
	{
		//TXE flag is set
		//DO the data transmission
		if (I2Chandle->TxRxState == I2C_BUSY_TX)
		{
			if(I2Chandle->pI2Cx->SR2 & I2C_SR2_MSL) //check master mode in SR2
			{
				if(I2Chandle->TxLen > 0)
				{
					//1.Load data in DR
					I2Chandle->pI2Cx->DR = *(I2Chandle->pTxBuffer);
					//2.Decrease TxLen
					--(I2Chandle->TxLen);
					//3.Increase TxBuffer address
					++(I2Chandle->pTxBuffer);
				}				
			}else if (I2Chandle->pI2Cx->SR2 & I2C_SR2_TRA) //slave mode
			{
				I2C_AppEventCallBack(I2Chandle,I2C_EV_DataReq);
			}
		}
	}
	
	/*6. Handle the interrupt if RXNE flag is set*/
	temp3 = (I2Chandle->pI2Cx->SR1 & I2C_SR1_RXNE);
	if (temp1 && temp2 && temp3)
	{
		//RXNE flag is set
		//Receive the data
		if(I2Chandle->pI2Cx->SR2 & I2C_SR2_MSL) //check master mode in SR2		
		{
			if (I2Chandle->TxRxState == I2C_BUSY_RX)
			{
				if(I2Chandle->RxSize == 1)
				{
					*(I2Chandle->pRxBuffer) = I2Chandle->pI2Cx->DR;
					--(I2Chandle->RxLen);
				}
				else if(I2Chandle->RxSize > 1)
				{
					if (I2Chandle->RxSize == 2)
					{
						//disable acking
						I2Chandle->pI2Cx->CR1 &= ~(I2C_CR1_ACK);
						//read DR
						*(I2Chandle->pRxBuffer) = I2Chandle->pI2Cx->DR;
						++(I2Chandle->pRxBuffer);
						--(I2Chandle->RxLen);
					}
				}
				else if (I2Chandle->RxSize == 0)
				{
					//Close I2C data reception and notify the application
					//1. generate stop
					I2C_GenStop(I2Chandle->pI2Cx);
					//2. close I2C rx
					I2C_ReceiveDone(I2Chandle);
					//3. notify the application
					I2C_AppEventCallBack(I2Chandle,I2C_EV_RX_DONE);
				}	
			}		
		}else if (I2Chandle->pI2Cx->SR2 & I2C_SR2_TRA) //slave mode
		{
			I2C_AppEventCallBack(I2Chandle,I2C_EV_DataReceived);
		}
		
	}		
	
}

void I2C_ER_IRQHandle(I2C_handle_t *I2Chandle)
{
	uint32_t temp1,temp2;

    //Know the status of  ITERREN control bit in the CR2
	temp2 = (I2Chandle->pI2Cx->CR2) &  I2C_CR2_ITERREN;


/***********************Check for Bus error************************************/ 
	temp1 = (I2Chandle->pI2Cx->SR1) & I2C_SR1_BERR;
	if(temp1  && temp2 )
	{
		//This is Bus error
		
		//Implement the code to clear the bus error flag 
		I2Chandle->pI2Cx->SR1 &= ~( I2C_SR1_BERR);
		
		//Implement the code to notify the application about the error 
	   I2C_AppEventCallBack(I2Chandle,I2C_ERROR_BERR);
	}

/***********************Check for arbitration lost error************************************/ 
	temp1 = (I2Chandle->pI2Cx->SR1) & (I2C_SR1_ARLO);
	if(temp1  && temp2)
	{
		//This is arbitration lost error
		
		//Implement the code to clear the arbitration lost error flag
		I2Chandle->pI2Cx->SR1 &= ~(I2C_SR1_ARLO);		
		//Implement the code to notify the application about the error 
	   I2C_AppEventCallBack(I2Chandle,I2C_ERROR_ARLO);	   
	}

/***********************Check for ACK failure  error************************************/ 

	temp1 = (I2Chandle->pI2Cx->SR1) & (I2C_SR1_AF);
	if(temp1  && temp2)
	{
		//This is ACK failure error
		
	    //Implement the code to clear the ACK failure error flag
		I2Chandle->pI2Cx->SR1 &= ~(I2C_SR1_AF);
		//Implement the code to notify the application about the error 
	    I2C_AppEventCallBack(I2Chandle,I2C_ERROR_AF);		
	}

/***********************Check for Overrun/underrun error************************************/
	temp1 = (I2Chandle->pI2Cx->SR1) & (I2C_SR1_OVR);
	if(temp1  && temp2)
	{
		//This is Overrun/underrun
		
	    //Implement the code to clear the Overrun/underrun error flag
		I2Chandle->pI2Cx->SR1 &= ~(I2C_SR1_OVR);
		//Implement the code to notify the application about the error
	    I2C_AppEventCallBack(I2Chandle,I2C_ERROR_OVR);				
	}

/***********************Check for Time out error************************************/
	temp1 = (I2Chandle->pI2Cx->SR1) & (I2C_SR1_TIMEOUT);
	if(temp1  && temp2)
	{
		//This is Time out error
		
	    //Implement the code to clear the Time out error flag
		I2Chandle->pI2Cx->SR1 &= ~(I2C_SR1_TIMEOUT);		
		//Implement the code to notify the application about the error
		I2C_AppEventCallBack(I2Chandle,I2C_ERROR_TIMEOUT);		
	}
}

//Other helper functions 
/*I2C_enable*/
void I2C_ENABLE(I2C_TypeDef *pI2Cx)
{
	pI2Cx->CR1 |= (1U << 0);	
}
/*I2C_disable*/
void I2C_DISABLE(I2C_TypeDef *pI2Cx)
{
	pI2Cx->CR1 &= ~(1U << 0);	
}

uint32_t get_ClockFreq(void);
uint32_t get_ClockFreq(void)
{
	uint32_t CLOCKsrc;
	uint32_t CLOCK =0;
	
	CLOCKsrc  = (RCC->CFGR >> 2) & (0x3U); 	//Extract bits 2 and 3 to know which clock source is used	
	

	if (CLOCKsrc == HSI)
	{
		CLOCK = 16000000U; //internal oscillator 
	}
	else if(CLOCKsrc == HSE)
	{
		//TODO
		CLOCK=0;
	}
	else if(CLOCKsrc == PLL)
	{
		CLOCK=0;
		//TODO
	}
	else if (CLOCKsrc == PLLR)
	{
		CLOCK=0;
		//TODO
	}	
	return CLOCK;
}

uint32_t get_AHPPrescalar(void);
uint32_t get_AHPPrescalar(void)
{
	uint32_t Pre =0;
	uint32_t AHPPre = (RCC->CFGR >> 4) & (0xFU);
	if (AHPPre == 8)
	{
		Pre = 2;	
	}
	else if (AHPPre == 9)
	{
		Pre = 4;	
	}
	else if (AHPPre == 10)
	{
		Pre = 8;		
	}
	else if (AHPPre == 11)
	{
		Pre = 16;		
	}
	else if (AHPPre == 12)
	{
		Pre = 64;		
	}
	else if (AHPPre == 13)
	{
		Pre = 128;		
	}
	else if (AHPPre == 14)
	{
		Pre = 256;		
	}
	else if (AHPPre == 15)
	{
		Pre = 512;		
	}
	else 
	{
		Pre = 1;		
	}
	return Pre;	
}

uint32_t get_ABP1Prescalar(void);
uint32_t get_ABP1Prescalar(void)
{
	uint32_t Pre =0;
	uint32_t ABPPre = (RCC->CFGR >> 10) & (0x7U);
	if (ABPPre == 4)
	{
		Pre = 2;	
	}
	else if (ABPPre == 5)
	{
		Pre = 4;	
	}
	else if (ABPPre == 6)
	{
		Pre = 8;		
	}
	else if (ABPPre == 7)
	{
		Pre = 16;		
	}
	else 
	{
		Pre = 1;		
	}
	return Pre;	
}

uint32_t RCC_GetPCLK1_HZ(void)
{
	uint32_t freq, CLOCK, AHPPre, APBPre;
	
	CLOCK 	  = get_ClockFreq();	
	AHPPre 	  = get_AHPPrescalar();
	APBPre    = get_ABP1Prescalar(); 	
	
	
	
	freq = (CLOCK/AHPPre)/APBPre;
	return freq;	
}

void I2C_GenStart(I2C_TypeDef *pI2Cx)
{
	pI2Cx->CR1 |=  I2C_CR1_START;	
}
void I2C_GenStop(I2C_TypeDef *pI2Cx)
{
	pI2Cx->CR1 |= I2C_CR1_STOP;
}
uint8_t GET_Status(I2C_TypeDef *pI2Cx, uint32_t FLAG)
{
	if (pI2Cx->SR1 & FLAG)
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}

void SET_SWRST(I2C_TypeDef *pI2Cx)
{
	pI2Cx->CR1 |= (1U << 15);
}	
void RESET_SWRST(I2C_TypeDef *pI2Cx)
	
{
	pI2Cx->CR1 &= ~(1U << 15);
}

static void I2C_WriteMode_Address(I2C_TypeDef *pI2Cx, uint8_t SlaveAddr)
{
	SlaveAddr = (uint8_t)(SlaveAddr << 1);	//Take the first 7 bits and clear the space for R/W bit	
	SlaveAddr &= ~(0x01U);					//RESET the 1st bit to 0 to indicate the Write mode	
	pI2Cx->DR = SlaveAddr;
}

static void I2C_ReadMode_Address(I2C_TypeDef *pI2Cx, uint8_t SlaveAddr)
{
	SlaveAddr = (uint8_t)(SlaveAddr << 1);	//Take the first 7 bits and clear the space for R/W bit	
	SlaveAddr |= 1;							//SET the 1st bit to 1 to indicate the Read mode		
	pI2Cx->DR = SlaveAddr;	
}

static void I2C_ClearADDR(I2C_handle_t *I2Chandle)
{
	uint32_t dummy;
	if(I2Chandle->pI2Cx->SR2 & I2C_SR2_MSL) //check master mode in SR2
	{
		if (I2Chandle->TxRxState == I2C_BUSY_RX) //check receive mode
		{
			//disable acking
			I2Chandle->pI2Cx->CR1 &= ~(I2C_CR1_ACK);
			//clear ADDR flag
			dummy = I2Chandle->pI2Cx->SR1 | I2Chandle->pI2Cx->SR2;
		}
		else
		{
			dummy = I2Chandle->pI2Cx->SR1 | I2Chandle->pI2Cx->SR2;
		}
	}
	else //SLave mode
	{
		dummy = I2Chandle->pI2Cx->SR1 | I2Chandle->pI2Cx->SR2;
	}	
	
}
void I2C_SendDone(I2C_handle_t *I2Chandle)
{
	I2Chandle->pI2Cx->CR2 &= ~(I2C_CR2_ITBUFEN);
	I2Chandle->pI2Cx->CR2 &= ~(I2C_CR2_ITEVTEN);
	
	I2Chandle->TxRxState = I2C_READY;
	I2Chandle->TxLen  = 0;
	I2Chandle->pTxBuffer = NULL;
	if(I2Chandle->I2CConfig.AckControl == ACK) 
	{
		I2Chandle->pI2Cx->CR1 |= (I2C_CR1_ACK);
	}	
}
void I2C_ReceiveDone(I2C_handle_t *I2Chandle)
{
	I2Chandle->pI2Cx->CR2 &= ~(I2C_CR2_ITBUFEN);
	I2Chandle->pI2Cx->CR2 &= ~(I2C_CR2_ITEVTEN);
	
	I2Chandle->TxRxState = I2C_READY;
	I2Chandle->RxLen  = 0;
	I2Chandle->RxSize = 0;
	I2Chandle->pRxBuffer = NULL;
	if(I2Chandle->I2CConfig.AckControl == ACK)
	{
		I2Chandle->pI2Cx->CR1 |= (I2C_CR1_ACK);
	}
	
}

//application callback fuctions
__WEAK void I2C_AppEventCallBack(I2C_handle_t *I2Chandle, uint8_t EVENT)
{
	I2Chandle = NULL;
	(void)EVENT;
}
