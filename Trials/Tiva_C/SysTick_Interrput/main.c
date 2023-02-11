#include "TM4C123.h"                    // Device header
int main()
{
		SYSCTL->RCGCGPIO |=0x20;
		GPIOF->DIR |= 0x0E;
		GPIOF->DEN |= 0x0E;
	
		NVIC_DisableIRQ;
		SysTick->LOAD = (16000000 - 1);
		SysTick->CTRL = 7; //enable, use interrupt, use system clock
		NVIC_EnableIRQ;
		
	  while(1){}
}

void SysTick_Handler(){
		GPIOF->DATA ^= (1U << 2);
}