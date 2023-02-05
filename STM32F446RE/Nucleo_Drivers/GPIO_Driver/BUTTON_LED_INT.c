#include "gpio_driver.h"
#include "bsb.h"

int main (void)
{
	LED_init();
	Button_init_Interrupt();
	while(1){
	}
}

void EXTI15_10_IRQHandler(void)
{
	delay(200000);
    GPIO_IRQ_Handler(GPIO_PIN_NO_13);	
	LED_Toggle();
}
