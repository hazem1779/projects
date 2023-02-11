#include "TM4C123.h"                    // Device header
#include "driver.h"                     // US sensor driver

static double distance_in_cm;

int main()
{
	Ports_init();
	Timer0_init();
	
	while(1)
	{
			distance_in_cm = Measure_Distance();
			if (distance_in_cm < 15) {
					GPIOF->DATA |= BLUE;
			}
			else {
					GPIOF->DATA &= ~BLUE;
			}
	}
	
}
