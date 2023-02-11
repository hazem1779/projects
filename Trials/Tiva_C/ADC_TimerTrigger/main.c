#include "TM4C123.h"                    // Device header
#define PE3 (1U << 3)
static uint32_t volatile temp;
int main()
{
	/*------------- Enable clock for ADC0 and WTIMER0 --------------*/   
	 SYSCTL->RCGCADC |= 0x01; //ADC0
	 SYSCTL->RCGCWTIMER |= 0x01; //TIMER0
			
	 /*--------------------ADC0 INITIALIZATION -----------------*/
	  
	  ADC0->ACTSS &= ~(PE3);     //disable active sample sequencer ss3 before config
		ADC0->EMUX  &= ~(0xF000U); //enable the software trigger 		
		ADC0->EMUX  |= 0x5000;     //enable timer trigger
	  ADC0->SSMUX3 = 0; 				 //get input from channel 0
	  ADC0->SSCTL3 = 0x0E;       //Take Mcu temperature, set the flag at 1st sample
		ADC0->ACTSS |= (PE3);	

	 /*--------------------WTIMER INITIALIZATION -----------------*/
		WTIMER0->CTL =0; //disable before config
		WTIMER0->CFG = 0x04; //32-bit option
		WTIMER0->TAMR |= 0x02; //periodic timer
		WTIMER0->TAILR = 16000000 - 1; //load with one second
		WTIMER0->CTL |= 0x20; //timer trigger
		WTIMER0->CTL |= 0x01; //enable timer0

	 /*--------------------Wait for conversion to complete-----------------*/		

		while(1)
		{
				while((ADC0->RIS & PE3) == 0){} //wait for conversion to complete
				temp = 147U - (247U * ADC0->SSFIFO3)/4096U ;
				ADC0->ISC = 8U;     //clear the completion flag	
		}		
	 
}

