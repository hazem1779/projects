#include "TM4C123.h"                    // Device header

#define RED (1U << 1)

void timer1_oneshot(unsigned int milli_delay);

int main()
{
	SYSCTL->RCGCGPIO |= 0x20; //enable clock for PORTF
	GPIOF->DIR   |= RED; 
	GPIOF->DEN   |= RED;
	while(1)
	{
			GPIOF->DATA ^= RED;
			timer1_oneshot(4U);
	}		
}
void timer1_oneshot(unsigned int milli_delay)
{
	
		SYSCTL->RCGCTIMER |= 0x01;
		TIMER0->CTL |= 0x00;  //Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared)
		TIMER0->CFG |= 0x04;  //Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000
		TIMER0->TAMR |= 0x01; //Write a value of 0x1 for One-Shot mode.
		TIMER0->TAILR |= ((16000U*milli_delay) - 1U) ; //Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).
		TIMER0->ICR |= 0x01; //clear the status register
		TIMER0->CTL |= 0x01;  //Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.
		

		while((TIMER0->RIS & 0x01) == 0); // wait for timeout flag to set
}
