#include "bsp.h"

int main(void)
{
	Button_init();
	I2C1_GPIO_init();
	while(1)
	{
		while(!Button_status());
		delay(200000); //debouncing
		I2C1_master_TX_test();			
	}
}
