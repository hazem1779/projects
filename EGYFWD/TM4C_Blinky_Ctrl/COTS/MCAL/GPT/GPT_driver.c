#include "LEDConfig.h"

uint32_t CHECK_FLAG = 0;
uint8_t on_times;
uint8_t off_times;
uint8_t Ttotal_Sec;
uint8_t confirm;
uint8_t ON_FLAG ;
uint8_t OFF_FLAG;
double Load_Val, Match_Val;
const double Tclk	= 6.25e-8;


/**
@Important Notes:
**/
void GPT_Init_ModePWM(void)
{
	//0. Enable Clock for Timer0 block Wide-Timer only as a test
	set_bit (RCGCWTIMER,0);
	
	//1. Ensure the timer is disabled (the TnEN bit is cleared) before making any changes.
	clear_bit(WTIMER_0->GPTMCTL,8);
	
	//2. Write the GPTM Configuration (GPTMCFG) register with a value of 0x0000.0004.
	set_bit(WTIMER_0->GPTMCFG,2);
	
	//3. In the GPTM Timer Mode (GPTMTnMR) register, set the TnAMS bit(3rd) to 0x1, the TnCMR bit(2nd) to 
	//0x0, and the TnMR field(0 and 1) to 0x2.
	set_bit(WTIMER_0->GPTMTBMR,3); 								//set the TnAMS bit(3rd)
	clear_bit(WTIMER_0->GPTMTBMR,2);							//the TnCMR bit(2nd) to 0x0
	WTIMER_0->GPTMTBMR |= (0x2U << 0);							//the TnMR field(0 and 1) to 0x2.
	
	//4. Configure the output state of the PWM signal (whether or not it is inverted) in the TnPWML field (14th)
	//of the GPTM Control (GPTMCTL) register.
	clear_bit(WTIMER_0->GPTMCTL,14);							//Output is unaffected.
	
	//5. If a prescaler is to be used, write the prescale value to the GPTM Timer n Prescale Register
	//(GPTMTnPR).
	/*************TBD******************/
	
	//6. If PWM interrupts are used, configure the interrupt condition in the TnEVENT field in the
	//GPTMCTL register and enable the interrupts by setting the TnPWMIE bit in the GPTMTnMR
	//register.
	WTIMER_0->GPTMCTL |= (0x3U << 10); 							//Both Edges trigger interrupts
	set_bit(WTIMER_0->GPTMTBMR,9);								//Enable the interrupts by setting the TnPWMIE bit (9th) in the GPTMTnMR		
	set_bit(WTIMER_0->GPTMIMR,10);								//Enable The interrupt on CBEIM
	
	
	
	//7. Load the timer start value into the GPTM Timer n Interval Load (GPTMTnILR) register.
	Ttotal_Sec = on_times + off_times;
	Load_Val = (double) Ttotal_Sec / Tclk;
	WTIMER_0->GPTMTBILR = (uint32_t) Load_Val;					//Register is loaded with total time (Assuming System Clock is used Fclk)
	
	//8. Load the GPTM Timer n Match (GPTMTnMATCHR) register with the match value.
	Load_Val = (double) off_times / Tclk;
	WTIMER_0->GPTMTBMATCHR = (uint32_t) Load_Val;
	
	//9. Set the TnEN bit in the GPTM Control (GPTMCTL) register to enable the timer and begin
	//generation of the output PWM signal.
	set_bit(WTIMER_0->GPTMCTL,8);
	while(!(WTIMER_0->GPTMRIS & (1U << 10)));					//Poll until CBERIS is set
	
}

/******************************************************/


void clear_RIS(void)
{
	set_bit(WTIMER_0->GPTMICR,10);
}



void PWM_ISR(void)
{
	CHECK_FLAG++;
	CHECK_FLAG = CHECK_FLAG % 2;
	if (CHECK_FLAG)
	{
		Dio_WriteChannel(GPIOF_APB,PIN_1,PORT_PIN_HIGH);
		
	}
	else 
	{
		Dio_WriteChannel(GPIOF_APB,PIN_1,PORT_PIN_LOW);
	}
	clear_RIS();
}
