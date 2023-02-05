#include "DIO_driver.h"

/********************************************************************
**			GLOBAL VARIABLES									**						
*******************************************************************/
uint8_t captured;
uint8_t	BUSY_ON = 1;
uint8_t	BUSY_OFF = 0;
extern uint8_t on_times;
extern uint8_t off_times;

/********************************************************************/
/*APIs IMPLMENTATION*/

void GPIO_CLOCK_ENABLE(GPIO_Struct *GPIOx)
{
	if (GPIOx == GPIOA_APB | GPIOx == GPIOA_AHB)
	{
		 GPIOA_Clock_Enable();
	}
	else if(GPIOx == GPIOB_APB | GPIOx == GPIOB_AHB) 
	{
		GPIOB_Clock_Enable();
	}
	else if(GPIOx == GPIOC_APB | GPIOx == GPIOC_AHB) 
	{
		GPIOC_Clock_Enable();
	}
	else if(GPIOx == GPIOD_APB | GPIOx == GPIOD_AHB) 
	{
		GPIOD_Clock_Enable();
	}
	else if(GPIOx == GPIOE_APB | GPIOx == GPIOE_AHB) 
	{
		GPIOE_Clock_Enable();
	}
	else if(GPIOx == GPIOF_APB | GPIOx == GPIOF_AHB) 
	{
		GPIOF_Clock_Enable();
	}
}


/********************************************************************/
void GPIO_Port_init(const GPIO_Handle_Struct *GPIOxHandle)
{
	
	for (int i =0; i < PINS_USED; i++)
	{
		uint8_t dir 	= GPIOxHandle[i].PortPinDirection ;
		uint8_t pin_num = GPIOxHandle[i].PortPinNum;
		uint8_t mode    = GPIOxHandle[i].PortPinMode;
		uint8_t resist	= GPIOxHandle[i].PortPinInternalAttach;
		uint8_t current	= GPIOxHandle[i].PortPinOutputCurrent;
		
		//1. Enable the clock to the port
		GPIO_CLOCK_ENABLE(GPIOxHandle[i].GPIOx);
		
		
		/*Special case: Unlocking Pins PF0 and PD7*/
		if(GPIOxHandle[i].GPIOx == GPIOF_APB && pin_num == PIN_0 || GPIOxHandle[i].GPIOx == GPIOD_APB && pin_num == PIN_7)
		{
			GPIOxHandle[i].GPIOx->LOCK = LOCK_KEY;
			if(GPIOxHandle[i].GPIOx == GPIOF_APB && pin_num == PIN_0)
			{
				GPIOxHandle[i].GPIOx->CR |= (1U <<0);
			}
			else
			{
				GPIOxHandle[i].GPIOx->CR |= (1U <<7);
			}
		}
		
		//2. Set the direction of the GPIO port pins
		if (dir == PORT_PIN_INPUT)
		{
			clear_bit(GPIOxHandle[i].GPIOx->DIR, pin_num);
		}
		else if (dir == PORT_PIN_OUTPUT)
		{
			set_bit(GPIOxHandle[i].GPIOx->DIR, pin_num);
		}
		
		
		//3. Configure the Mode
		if (mode == PORT_PIN_DEN)
		{
			set_bit(GPIOxHandle[i].GPIOx->DEN, pin_num);
		}
		else if (mode == PORT_PIN_ALTFUN)
		{
			set_bit(GPIOxHandle[i].GPIOx->AFSEL,pin_num);
			if (dir == PORT_PIN_TIMER)
			{
				GPIOxHandle[i].GPIOx->PCTL |= (0x07 << (4 *pin_num));
			}
		}
		
		
		//4. Configure PUR or PDR or NO_PUPD
		if (resist == PORT_PIN_NO_PUPD)
		{
			clear_bit(GPIOxHandle[i].GPIOx->PUR, pin_num);
			clear_bit(GPIOxHandle[i].GPIOx->PDR, pin_num);
		}
		else if(resist == PORT_PIN_PUR)
		{
			set_bit(GPIOxHandle[i].GPIOx->PUR, pin_num);
		}
		else if(resist == PORT_PIN_PUD)
		{
			set_bit(GPIOxHandle[i].GPIOx->PDR, pin_num);
		}
		
		
		//5. Configure the current (2mA or 4mA or 8mA)
		if (current == PORT_PIN_2_mA)
		{
			set_bit(GPIOxHandle[i].GPIOx->DR2R,pin_num);	
		}
		else if (current == PORT_PIN_4_mA)
		{
			set_bit(GPIOxHandle[i].GPIOx->DR4R,pin_num);		
		}
		else if (current == PORT_PIN_8_mA)
		{
			set_bit(GPIOxHandle[i].GPIOx->DR8R,pin_num);		
		}	
	}
}


/********************************************************************/
void Enable_Interrupts(uint8_t Pin)
{
	set_bit(GPIOF_APB->IM,Pin);
}
	
/********************************************************************/

void BUTTON_COUNTER_ISR(void)
{
	if (GPIOF_APB->RIS == 0x1)
	{
		set_bit(GPIOF_APB->ICR,0);
		if(BUSY_ON)
		{
			BUSY_ON = 0;
			BUSY_OFF++;
		}
		else
		{
			BUSY_OFF = 0;
			BUSY_ON	 = 0;
			captured = 1;	
			clear_bit(GPIOF_APB->IM,0);
			clear_bit(GPIOF_APB->IM,4);
		}
	}
	if(GPIOF_APB->RIS == 0x10 && BUSY_ON)
	{
		on_times++;
		set_bit(GPIOF_APB->ICR,4);
	}
	if(GPIOF_APB->RIS == 0x10 && BUSY_OFF)
	{
		off_times++;
		set_bit(GPIOF_APB->ICR,4);
	}

}






