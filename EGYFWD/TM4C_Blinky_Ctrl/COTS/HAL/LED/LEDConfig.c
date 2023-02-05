#include "LEDConfig.h"
extern uint8_t captured;
const GPIO_Handle_Struct Config_Array[PINS_USED] =
{
	{GPIOF_APB, PORT_PIN_DEN, PORT_PIN_OUTPUT, PORT_PIN_NO_PUPD, PORT_PIN_8_mA, PIN_1},    	//RED LED
	{GPIOF_APB, PORT_PIN_DEN, PORT_PIN_INPUT , PORT_PIN_PUR, PORT_PIN_8_mA, PIN_0},		   	//SW2
	{GPIOF_APB, PORT_PIN_DEN, PORT_PIN_INPUT , PORT_PIN_PUR, PORT_PIN_8_mA, PIN_4},   		//SW1
	{GPIOC_APB, PORT_PIN_ALTFUN, PORT_PIN_TIMER, PORT_PIN_NO_PUPD, PORT_PIN_8_mA, PIN_5}	//WTimer0 on PC5 pin 
};

void blinky_RED(void)
{
	
	#if 1
	Systick_CTRL = (1U << 0 | 1U << 1 | 1U << 2);	//bit 0 to enable bit 1 to fire interrupt bit 2 to use system clock
	Systick_LOAD = 16000000U - 1U;
	#endif
	
	InterruptCtrl(GPIOF_IRQ);
	InterruptCtrl(WTIMER0B_IRQ);
	GPIO_Port_init(Config_Array);
	Enable_Interrupts(PIN_0);
	Enable_Interrupts(PIN_4);
	while(!captured);
	GPT_Init_ModePWM();
}

void WTIMER0B_Handler(void)
{
	PWM_ISR();							//API used from GPT_driver.c
}

void GPIOF_Handler(void)
{
	BUTTON_COUNTER_ISR();				//API used from GPIO_driver.c
}

void SysTick_Handler (void)				
{
	Systick_Callback();					//API used from SysTick_driver.c
}

