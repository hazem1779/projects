#include "bsp.h"

int main()
{
	SPI2_INIT();
	Button_init();
	
	while(1)
	{
		while (Button_status());
		delay(200000);
		SPI2_TEST();	
	}
}
