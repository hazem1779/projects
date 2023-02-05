#include "bsb.h"
#include "gpio_driver.h"
#include <stdint.h>
	

void LED_init(void)
{
	GPIO_CLK_CTRL(GPIOA, SET);
	
	GPIO_handle_t GPIOA_handle;
	GPIOA_handle.pGPIOx = GPIOA;
	GPIOA_handle.gpio_pin_config.pin_Num 		= GPIO_PIN_NO_5;
	GPIOA_handle.gpio_pin_config.pin_Mode 		= GPIO_MODE_OUT;
	GPIOA_handle.gpio_pin_config.pin_OutputMode = PUSH_PULL;	
	GPIOA_handle.gpio_pin_config.pin_PUPD		= NO_PUPD;
	GPIOA_handle.gpio_pin_config.pin_Speed		= LOW_SPEED;	 
	
	GPIO_Init(&GPIOA_handle);
}	
void LED_Toggle(void)
{	
	GPIO_PinToggle(GPIOA, 5);
}

void delay(uint32_t ticks)
{
	for (; ticks > 0; --ticks);
}

void Button_init(void)
{
	GPIO_CLK_CTRL(GPIOC, SET);
	
	GPIO_handle_t GPIOC_handle;
	GPIOC_handle.pGPIOx = GPIOC;
	GPIOC_handle.gpio_pin_config.pin_Num 		= GPIO_PIN_NO_13;
	GPIOC_handle.gpio_pin_config.pin_Mode 		= GPIO_MODE_IN;
	GPIOC_handle.gpio_pin_config.pin_OutputMode = PUSH_PULL;	
	GPIOC_handle.gpio_pin_config.pin_PUPD		= PULL_UP;
	GPIOC_handle.gpio_pin_config.pin_Speed		= VERY_HIGH_SPEED;	 
	
	GPIO_Init(&GPIOC_handle);	
}


void Button_init_Interrupt(void)
{
	GPIO_CLK_CTRL(GPIOC, SET);
	
	GPIO_handle_t GPIOC_handle;
	GPIOC_handle.pGPIOx = GPIOC;
	GPIOC_handle.gpio_pin_config.pin_Num 		= GPIO_PIN_NO_13;
	GPIOC_handle.gpio_pin_config.pin_Mode 		= FALLING_EDGE;
	GPIOC_handle.gpio_pin_config.pin_OutputMode = PUSH_PULL;	
	GPIOC_handle.gpio_pin_config.pin_PUPD		= PULL_UP;
	GPIOC_handle.gpio_pin_config.pin_Speed		= VERY_HIGH_SPEED;	 
	
	GPIO_Init(&GPIOC_handle);
	GPIO_IRQConfig(EXTI15_10_IRQn,ENABLE);
	GPIO_IRQSetPriority(EXTI15_10_IRQn,0);
}

void LED_ON(void)
{
	GPIO_PinWrite(GPIOA, 5, ENABLE);
}
void LED_OFF(void)
{
	GPIO_PinWrite(GPIOA, 5, DISABLE);	
}
	
uint8_t Button_status(void)
{
	uint8_t status;
	status = GPIO_PinRead(GPIOC, 13);
	return !status; //button pressed--> status is 0 (normal condition it read)
}
