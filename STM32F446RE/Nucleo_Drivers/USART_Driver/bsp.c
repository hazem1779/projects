#include "bsp.h"

USART_handle_t USART2handle;
GPIO_handle_t  GPIOC_handle,GPIOAhandle;





void Button_init(void)
{
	GPIO_CLK_CTRL(GPIOC, SET);
	
	GPIOC_handle.pGPIOx = GPIOC;
	GPIOC_handle.gpio_pin_config.pin_Num 		= GPIO_PIN_NO_13;
	GPIOC_handle.gpio_pin_config.pin_Mode 		= GPIO_MODE_IN;
	GPIOC_handle.gpio_pin_config.pin_OutputMode = PUSH_PULL;	
	GPIOC_handle.gpio_pin_config.pin_PUPD		= PULL_UP;
	GPIOC_handle.gpio_pin_config.pin_Speed		= VERY_HIGH_SPEED;	 
	
	GPIO_Init(&GPIOC_handle);	
}

uint8_t Button_status(void)
{
	uint8_t status;
	status = GPIO_PinRead(GPIOC, 13);
	return status; //button pressed--> status is 0 (normal condition it reads)
}

void delay(uint32_t ticks)
{
	for (; ticks > 0; --ticks);
}



void USART2_GPIO_Init(void)
{
	GPIOAhandle.pGPIOx = GPIOA;
	GPIOAhandle.gpio_pin_config.pin_Mode 		= GPIO_MODE_ALTFUN;
	GPIOAhandle.gpio_pin_config.pin_AltFun		= AF7;	
	GPIOAhandle.gpio_pin_config.pin_OutputMode  = OPEN_DRAIN;
	GPIOAhandle.gpio_pin_config.pin_PUPD		= PULL_UP;	
	GPIOAhandle.gpio_pin_config.pin_Speed		= VERY_HIGH_SPEED;	 
	
	USART_Clk_Ctrl(USART2,ENABLE);
	GPIO_CLK_CTRL(GPIOA,ENABLE);
	
	//TX
	GPIOAhandle.gpio_pin_config.pin_Num 		= GPIO_PIN_NO_2;	
	GPIO_Init(&GPIOAhandle);	
	
	//RX
	GPIOAhandle.gpio_pin_config.pin_Num 		= GPIO_PIN_NO_3;
	GPIO_Init(&GPIOAhandle);
	
	/*//CTS
	GPIOAhandle.gpio_pin_config.pin_Num 		= GPIO_PIN_NO_0;
	GPIO_Init(&GPIOAhandle);	
	
	//RTS
	GPIOAhandle.gpio_pin_config.pin_Num 		= GPIO_PIN_NO_1;
	GPIO_Init(&GPIOAhandle);
	
	//CLK
	GPIOAhandle.gpio_pin_config.pin_Num 		= GPIO_PIN_NO_4;
	GPIO_Init(&GPIOAhandle); */	
}

void USART2_TEST_init(void)
{
	USART2handle.pUSARTx 			  	= USART2;
	USART2handle.USARTConfig.BaudRate 	= BR_9600;
	USART2handle.USARTConfig.HWFlowCtrl = HW_DISABLED;
	USART2handle.USARTConfig.Mode		= ONLY_TX;
	USART2handle.USARTConfig.NumOfStops = STOP_1;
	USART2handle.USARTConfig.ParityCtrl = PARITY_DISABLED;
	USART2handle.USARTConfig.WordLength = ONE_START_8_DATA;
	USART2_GPIO_Init();
	USART_Init(&USART2handle);
	USART_Peripheral(USART2,ENABLE);
	
}



