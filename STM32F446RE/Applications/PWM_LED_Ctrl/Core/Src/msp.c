#include "stm32f4xx_hal.h"

#define AF7_USART2  	0x07U

GPIO_InitTypeDef GPIOA_H;
void HAL_MspInit(void)
{
	//1. Set the priority grouping.
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	//2. Enable required system exceptions.
	SCB->SHCSR |= (1 << 16 | 1 << 17 | 1 << 18); //enable MEMFAULT BUSFAULT USGFAULT
	//3. Configure the priority for system exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);
	HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);
	HAL_NVIC_SetPriority(BusFault_IRQn,0,0);

}
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	//1. enable clock for USART2
	__HAL_RCC_USART2_CLK_ENABLE();

	//2.   configure the GPIO peripheral

	//2.1. configure the clock for the corresponding GPIO peripheral
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//2.2. configure pins USART2_Tx and USART2_Rx

	//USART2_TX
	GPIOA_H.Pin 	= GPIO_PIN_2;
	GPIOA_H.Mode	= GPIO_MODE_AF_PP;
	GPIOA_H.Speed	= GPIO_SPEED_FREQ_LOW;
	GPIOA_H.Pull	= GPIO_PULLUP;
	GPIOA_H.Alternate = AF7_USART2;
	HAL_GPIO_Init(GPIOA,&GPIOA_H);

	//USART2_RX
	GPIOA_H.Pin 	= GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA,&GPIOA_H);

	//3. NVIC settings
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn,15,0);
}




 void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
		//1. enable clock for TIMER2
		__HAL_RCC_TIM2_CLK_ENABLE();
		//2.   configure the GPIO peripheral

		//2.1. configure the clock for the corresponding GPIO peripheral
		__HAL_RCC_GPIOA_CLK_ENABLE();

		//2.2. configure pins PA5
		GPIOA_H.Mode	= GPIO_MODE_AF_PP;
		GPIOA_H.Pull	= GPIO_PULLUP;
		GPIOA_H.Alternate = GPIO_AF1_TIM2;
		GPIOA_H.Pin 	= GPIO_PIN_5 ;
		HAL_GPIO_Init(GPIOA,&GPIOA_H);


		//3. NVIC settings
		HAL_NVIC_EnableIRQ(TIM2_IRQn);
}
