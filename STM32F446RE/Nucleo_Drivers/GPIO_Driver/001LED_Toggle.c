#include "gpio_driver.h"
#include "bsb.h"

int main(void)
{
	while(1)
	{
		LED_Toggle();
		delay(500000);
	}
}
