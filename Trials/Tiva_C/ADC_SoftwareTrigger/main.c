#include "TM4C123.h"                    // Device header
#define PE3 (1U << 3)
 static unsigned int result;
 int main()
 {
	  /*--------------------*clock enable-----------------*/
		
	  SYSCTL->RCGCGPIO |= (1U << 4); //clock for PORTE
	  SYSCTL->RCGCADC  |= (0x01);    //enable clock for ADC0
	
	 /*--------------------PE3 INITIALIZATION -----------------*/ 
		
	  GPIOE->AFSEL |= (PE3); //enable alternate function for the pin PE3
		GPIOE->DEN  &= ~(PE3);  //disable digital function
		GPIOE->AMSEL |= (PE3); //enable analog function
		
	 /*--------------------ADC0 INITIALIZATION -----------------*/ 
		
	  ADC0->ACTSS &= ~(PE3);     //disable active sample sequencer ss3 before config
		ADC0->EMUX  &= ~(0xF000U); //enable the software trigger 		
		ADC0->SSMUX3 = 0x00;       //Get Input from channel 0
	  ADC0->SSCTL3 = 0x06;       //One sample at a time
		ADC0->ACTSS |= (PE3);	
	 
	 /*--------------------Start the conversion and Wait for it to complete-----------------*/		

		while(1)
		{
				ADC0->PSSI |= PE3; //start a conversion at ss3
				while((ADC0->RIS & PE3) == 0){} //wait for conversion to complete
				result = ADC0->SSFIFO3;
				ADC0->ISC = 8U;     //clear the completion flag	
				
		}		
	 
 }
