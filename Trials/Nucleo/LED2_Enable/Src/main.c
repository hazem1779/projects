#include <stdint.h>

#define RCC_AHB1ENR (*((volatile uint32_t*) 0x40023830))
#define GPIOA_MODE  (*((volatile uint32_t*) 0x40020000))
#define GPIOA_ODR   (*((volatile uint32_t*) 0x40020014))
#define GPIOA_IDR   (*((volatile uint32_t*) 0x40020010))

#define PORTA_CLOCK_EN (1U)

#define PA5_Clear  ((0x01U << 10) | (0x01U << 11)) //0b 11 << 10 ==> 1100 0000 0000
#define PA5_Output (0x01U << 10)

#define PA6_input  ((0x01U << 12) | (0x01U << 13))

#define PA5 (1U << 5)
#define PA6 (1U << 6)

void delay(uint64_t ticks);

int main(void)
{
/*----------Enable clock for GPIOA Port------------------*/
	RCC_AHB1ENR |=  PORTA_CLOCK_EN;

/*-------GPIOA Port Pin 5 as 01: General purpose output mode------*/

	//clearing 2-bits of PA5
	GPIOA_MODE  &= ~(PA5_Clear);

	//setting PA5 as 01: General purpose output mode
	GPIOA_MODE	|=  PA5_Output;

	//setting PA6 as 00: Input (reset state)
	GPIOA_MODE &= ~(PA6_input);

	while(1){
		//read the status of input pin PA6
		uint32_t readback = GPIOA_IDR & PA6;
		if(readback == PA6){
			//LED_ON
			GPIOA_ODR  |=  PA5;
		}
		else{
			//LED_OFF
			GPIOA_ODR  &=  ~(PA5);
		}
	}
}
