#include "gpio_driver.h"
#include "bsb.h"

int main(void)
{
#if 0 //led test
	LED_init();
	while(1)
	{
		LED_Toggle();
		delay(500000U);
	}
#endif
#if 0 //Led and Button test (No Interrupt) 
	LED_init();
	Button_init();
	while(1)
	{
		if(!(Button_status()))
		{
			LED_ON();
		}
		else
		{
			LED_OFF();			
		}
	}		
#endif

	
}
