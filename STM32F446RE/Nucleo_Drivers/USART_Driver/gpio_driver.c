
#include "gpio_driver.h"
/*****************************************************************************
* 					APIs Implementaions 
*****************************************************************************/

//  1- GPIOx clock control 
/****************
* @brief					- This Function is used to enable or disable clock for a GPIO port 
* @parameter [pGPIOx]		- Address of the port, examble: GPIOA address
* @parameter [status]		- Enable or Disable Macros	
* @returnType 				- None
* @Notes					- None
*********************/
void GPIO_CLK_CTRL(GPIO_TypeDef *pGPIOx, uint8_t status)
{
	if(status == SET)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();			
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();			
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();		
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();			
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();			
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();			
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();			
		}		
		
	}
	else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DIS();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DIS();			
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DIS();			
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DIS();		
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DIS();			
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DIS();			
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DIS();			
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DIS();			
		}		
	}
}

//  2- GPIOx init and de-init 
/****************
* @brief					- Initialize GPIO port and pin 
* @parameter [pGPIO_handle]	- The address to GPIO_handle structure 	
* @returnType 				- None
* @Notes					- None
*********************/
void GPIO_Init(GPIO_handle_t *pGPIO_handle)
{
		
	/*1. configure input or output mode */
	uint32_t temp = 0;
	/*non_interrupt mode*/
	if(pGPIO_handle->gpio_pin_config.pin_Mode <= GPIO_MODE_ANG)
	{
		temp = ((uint32_t)(pGPIO_handle->gpio_pin_config.pin_Mode) << (uint32_t)(2U * (pGPIO_handle->gpio_pin_config.pin_Num)));
		pGPIO_handle->pGPIOx->MODER &= ~(0x3U << (pGPIO_handle->gpio_pin_config.pin_Num));		
		pGPIO_handle->pGPIOx->MODER |= temp;
		temp = 0;
	}
	/*interrupt mode*/
	else{
		
		//configure rising or falling or both edges to generate the interrupt
		if(pGPIO_handle->gpio_pin_config.pin_Mode == RISING_EDGE)
		{
			EXTI->RTSR |= (1 << pGPIO_handle->gpio_pin_config.pin_Num);	
			EXTI->FTSR &= ~(1 << pGPIO_handle->gpio_pin_config.pin_Num);	
		}
		
		else if(pGPIO_handle->gpio_pin_config.pin_Mode == FALLING_EDGE)
		{
			EXTI->FTSR |=  (1 << pGPIO_handle->gpio_pin_config.pin_Num);
			EXTI->RTSR &= ~(1 << pGPIO_handle->gpio_pin_config.pin_Num);	
		}	
		
		else if(pGPIO_handle->gpio_pin_config.pin_Mode == RISING_FALLING)
		{
			EXTI->FTSR |=  (1 << pGPIO_handle->gpio_pin_config.pin_Num);
			EXTI->RTSR |=  (1 << pGPIO_handle->gpio_pin_config.pin_Num);			
		}
		
		
		//configure the port in SYSCFG_EXTICR 
		uint32_t temp1,temp2,PORTCODE;
		PORTCODE = GPIOX_TO_CODE(pGPIO_handle->pGPIOx);
		temp1 =(uint32_t)(pGPIO_handle->gpio_pin_config.pin_Num / 4U);
		temp2 =(uint32_t)(pGPIO_handle->gpio_pin_config.pin_Num % 4U);
		
		SYSCFG_PCLK_EN();
		
		SYSCFG->EXTICR[temp1] |=(uint32_t)(PORTCODE << (4U * temp2 ) );	

		//enable the interrupt delivery
		EXTI->IMR |=  (1 << pGPIO_handle->gpio_pin_config.pin_Num); 
	}
	
	/*2. configure pin_Speed*/
	temp =((uint32_t)(pGPIO_handle->gpio_pin_config.pin_Speed) << (uint32_t)(2U * (pGPIO_handle->gpio_pin_config.pin_Num)));
	pGPIO_handle->pGPIOx->OSPEEDR &= ~(0x3U << (pGPIO_handle->gpio_pin_config.pin_Num));
	pGPIO_handle->pGPIOx->OSPEEDR |= temp;
	temp = 0;
	
	
	/*3. configure output mode */
	temp =((uint32_t)(pGPIO_handle->gpio_pin_config.pin_OutputMode) << (uint32_t)((pGPIO_handle->gpio_pin_config.pin_Num)));
	pGPIO_handle->pGPIOx->OTYPER &= ~(0x1U << (pGPIO_handle->gpio_pin_config.pin_Num));
	pGPIO_handle->pGPIOx->OTYPER |= temp;
	temp = 0;
	
	
	/*4. configure pull-up or pull-down resistor*/
	temp =((uint32_t)(pGPIO_handle->gpio_pin_config.pin_PUPD) << (uint32_t)(2U * (pGPIO_handle->gpio_pin_config.pin_Num)));
	pGPIO_handle->pGPIOx->PUPDR &= ~(0x3U << (pGPIO_handle->gpio_pin_config.pin_Num));
	pGPIO_handle->pGPIOx->PUPDR |= temp;
	temp = 0;
	
	
	/*5. configure alterante functionality if needed*/
	if(pGPIO_handle->gpio_pin_config.pin_Mode == GPIO_MODE_ALTFUN)
	{
		uint32_t temp1, temp2;
		temp1 = pGPIO_handle->gpio_pin_config.pin_Num / 8U;
		temp2 = pGPIO_handle->gpio_pin_config.pin_Num % 8U;
		pGPIO_handle->pGPIOx->AFR[temp1] &= ~(uint32_t)(0xF << (4 * temp2)); 
		pGPIO_handle->pGPIOx->AFR[temp1] |= ( (uint32_t)(pGPIO_handle->gpio_pin_config.pin_AltFun) << (4 * temp2) );	
	}	
}

/****************
* @brief					- This finction is used to reset the GPIO port
* @parameter[pGPIOx]		- Address of the port	
* @returnType 				- None
* @Notes					- None
*********************/
void GPIO_DeInit(GPIO_TypeDef *pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_RESET();
	}
	else if (pGPIOx == GPIOB)
	{
		GPIOB_RESET();
	}
	else if (pGPIOx == GPIOC)
	{
		GPIOC_RESET();
	}
	else if (pGPIOx == GPIOD)
	{
		GPIOD_RESET();
	}	
	else if (pGPIOx == GPIOE)
	{
		GPIOE_RESET();		
	}	
	else if (pGPIOx == GPIOF)
	{
		GPIOF_RESET();
	}	
	else if (pGPIOx == GPIOG)
	{
		GPIOG_RESET();
	}	
	else if (pGPIOx == GPIOH)
	{
		GPIOH_RESET();
	}		
}

//  3- Data Read, Write and Toggle 
/****************
* @brief					- This function is used to read from an input pin
* @parameter[pGPIOx]		- Address of the port 
* @parameter[PinNumber]		- Pin number	
* @returnType 				- Pin boolean status [0 or 1]
* @Notes					- None
*********************/
uint8_t GPIO_PinRead(GPIO_TypeDef *pGPIOx, uint8_t PinNumber)
{
	uint8_t status;
	status =(uint8_t)((pGPIOx->IDR >> PinNumber)& 0x00000001);
	return status;
}

/****************
* @brief					- This function is used to read the whole port pins
* @parameter[pGPIOx]		- Address of Port 	
* @returnType 				- All port pins status
* @Notes					- None
*********************/
uint16_t GPIO_PortRead(GPIO_TypeDef *pGPIOx)
{
	uint16_t status;
	status = (uint16_t)(pGPIOx->IDR);
	return status;
}


/****************
* @brief					- This functions is used to write a boolean value[0 or 1] to a specific pin 
* @parameter[pGPIOx]		- Address of Port 
* @parameter[PinNumber]		- Pin number
* @parameter[data]			- The value written to the pin
* @returnType 				- None
* @Notes					- None 
*********************/
void GPIO_PinWrite(GPIO_TypeDef *pGPIOx, uint8_t PinNumber, uint8_t data)
{
	if (data)
	{
		pGPIOx->ODR |= (uint32_t)(data << PinNumber);
	}
	else
	{
		pGPIOx->ODR &= ~(1U << PinNumber);
	}	
}



/****************
* @brief					-  
* @parameter[pGPIOx]		- 
* @parameter[status]		- 	
* @returnType 				- 
* @Notes					- 
*********************/
void GPIO_PinToggle(GPIO_TypeDef *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1U << PinNumber);
}

/****************
* @brief					- This is a function to write data to the whole port 
* @parameter[pGPIOx]		- Address of the port
* @parameter[data]			- Data to be written to the whole port	
* @returnType 				- None
* @Notes					- None
*********************/
void GPIO_PortWrite(GPIO_TypeDef *pGPIOx, uint16_t data)
{
	pGPIOx->ODR = data;
}


// 4- IRQ configuration and ISR handling
/****************
* @brief					- Enabling the IRQ or Disabling it 
* @parameter[IRQNumber]		- IRQ number refered in the enum <IRQn_Type>
* @parameter[status]		- Enable or Disable	
* @returnType 				- None	 
* @Notes					- Only 3 register is needed for enabling or disabling 
							  because IRQs biggest number is 96 
*********************/
void GPIO_IRQConfig(IRQn_Type IRQNumber, uint8_t status)
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

/****************
* @brief					- Setting the priority for the IRQ 
* @parameter[IRQNumber]		- IRQ number refered in the enum <IRQn_Type>
* @parameter[IRQPrio]		- Desired priority	
* @returnType 				- None 
* @Notes					- Priority number should be implemented in the first 4 bits of the byte
*********************/
void GPIO_IRQSetPriority(IRQn_Type IRQNumber, uint8_t IRQPrio)
{
	NVIC->IP[IRQNumber] |= (IRQPrio << __NVIC_PRIO_BITS);	 
}

/****************
* @brief					-  A function to clear the pending bit in EXTI
*********************/
void GPIO_IRQ_Handler(uint8_t PinNumber)
{
	if( EXTI->PR & (1 << PinNumber)) //if the interrupt is pended 
	{
		EXTI->PR |= (1 << PinNumber); //clear the pending bit
	}
}


