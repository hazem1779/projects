#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim6;

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

