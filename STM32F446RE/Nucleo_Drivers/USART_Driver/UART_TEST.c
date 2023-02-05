#include "bsp.h"

int main()
{
	Button_init();
	USART2_TEST_init();
	while(1)
	{
		while(Button_status());
		delay(100000); //debouncing
		uint8_t msg[] = "usart hello!";
		USART_SendData(&USART2handle,msg, strlen((const char*)msg));
	}
}
