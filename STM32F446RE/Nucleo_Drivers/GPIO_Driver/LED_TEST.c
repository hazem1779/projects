#include "gpio_driver.h"
#include "bsb.h"

int main(void)
{
	LED_init();
	while(1)
	{
		LED_Toggle();
		delay(500000U);
	}
}
