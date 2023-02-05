#include "stm32f4xx.h"                  // Device header
#include <stdint.h>



/**********************************

NOTE: This code wil not be correctly executed unless there is an external oscillator attached 
to the stm32f4xx board because it does not have an external one only the RC internal oscillator

**********************************/

int main(void)
{
	while(1){
		RCC->CR |= (1 << 16); //switch to HSE
		while( !(RCC->CR & (1U << 17)) ); // wait till ready-bit is set
		RCC->CFGR &= ~(0x03U << 0); //clear [0:1]bits
		RCC->CFGR |= (0x01 << 0); //switch to HSE from HSI
	}
}
