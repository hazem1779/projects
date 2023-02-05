#include "TM4C123.h"
#include "driver.h"

static uint32_t volatile highedge, lowedge, time;
static double distance_cm;
static const double __16MHZ_1ClOCK = 62.5e-9;
static const uint16_t MULTIPLIER = 5882;

void Timer0_init(void){
			
			/*clock gating for timer0 and portb*/
			SYSCTL->RCGCTIMER |= (1U << 0); 
			SYSCTL->RCGCGPIO  |= PORTB; 
			
			/*pin PB6(ECHO) as input*/
			GPIOB->DIR  &= ~ECHO;
			GPIOB->DEN  |= ECHO;
			
			/*alternate fuction for PB6 (ECHO)*/
			GPIOB->AFSEL |= ECHO;
			GPIOB->PCTL  &= ~0x0F000000U; //clear the pctl register for pb6 
			GPIOB->PCTL  |=  0x07000000U;	// configure the T0CCP0 (page 1351 in TM4C datasheet)
			
			/*TImer0 config*/
			TIMER0->CTL = 0x00; //disable timer before config
			TIMER0->CFG |= 0x04; // mode 16-bit
			TIMER0->TAMR |= 0x17; //edge-time, capture mode and up count 0b 0001 0111
			TIMER0->CTL |= 0x0C; //both edges (rising and falling)		
}	

void delay_microseconds(uint32_t delay){
			uint32_t i;
			SYSCTL->RCGCTIMER |= (1U << 1);
	    
			TIMER1->CTL = 0x00;
			TIMER1->CFG |= 0x04;
			
			TIMER1->TAMR |= 0x02; //periodic mode
			TIMER1->TAILR |= 16 - 1; //1 microsecond
			TIMER1->ICR |= 0x01; //clear the timeout status flag
	    
			TIMER1->CTL = 0x01;
			for (i = 0; i < delay; i++)
			{
					while((TIMER1->RIS & 0x01U)== 0U); //poll for timeout to happen
					TIMER1->ICR |= 0x01;
			}
}

void Ports_init(void){

		SYSCTL->RCGCGPIO |= PORTA;
		SYSCTL->RCGCGPIO |= PORTF;
		/*portA and portF trigger config*/
		GPIOA->DIR |= TRIGGER;
		GPIOA->DEN |= TRIGGER;
		GPIOF->DIR |= BLUE;
		GPIOF->DEN |= BLUE;		
}

double Measure_Distance(void){
		
		/*trigger the pulse and wait for 12 microseconds */
		GPIOA->DATA &= ~TRIGGER; //disable the trigger pin
		delay_microseconds(12);
		GPIOA->DATA |= TRIGGER; //enable the trigger pin		
		delay_microseconds(12);
		GPIOA->DATA &= ~TRIGGER;
		
		/*capture the rising edge (first edge)*/
		TIMER0->ICR |= (1U << 2); //write 1 to bit number 2 in ICR to clear the timer capture
		while((TIMER0->RIS & (1U << 2)) == 0); //poll till the rising-capture happens
		highedge = TIMER0->TAR; //TAR is a register to hold the time at which the rising-capture happened
		
		/*capture the falling eddge (second edge)*/
		TIMER0->ICR |= (1U << 2);	
		while((TIMER0->RIS & (1U << 2)) == 0);
		lowedge = TIMER0->TAR;
		
		/*calculate the distance*/
		time = highedge - lowedge;
		distance_cm = __16MHZ_1ClOCK * (double) time *(double) MULTIPLIER ;
		return distance_cm;
}
