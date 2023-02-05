#include <stdint.h>
#include "main.h"

void delay(uint64_t ticks);

int main(void)
{

	RCC_AHB1ENR_t volatile *const RCC_AHB1ENR_R = (RCC_AHB1ENR_t *)0x40023830;
	RCC_AHB1ENR_R->gpioa_en = 1U;



	GPIOx_MODE_t volatile *const GPIOA_MODE_R = (GPIOx_MODE_t*)0x40020000;
	GPIOA_MODE_R->pin_5 = 1U;

	GPIOx_ODR_t volatile *const GPIOA_ODR_R   =  (GPIOx_ODR_t *)0x40020014;

	while(1){
		GPIOA_ODR_R->pin_5 = 1U;
		delay(2*500000);
		GPIOA_ODR_R->pin_5 = 0U;
		delay(2*500000);
	}
}
