#include "gpio_driver.h"
#include "bsb.h"

int main()
{
	LED_init();
	Button_init();
	while(1)
	{
		if((Button_status()))
		{
			LED_ON();
		}
		else
		{
			LED_OFF();			
		}
	}		
}
