
#include <stdint.h>


#define NVIC_ISPR0 *((uint32_t *)(0XE000E200))
#define NVIC_ISER0 *((uint32_t *)(0xE000E100))

#define NVIC_IPR7  *((uint32_t *)(0xE000E41C)) //0xE000E400 + (4*7)
#define SCB_AIRCR  *((uint32_t *)(0xE000ED0C))

#define TIM2_IRQ_NUM   		(28U)
#define I2CEVENT_IRQ_NUM	(31U)
#define VECTKEY 	((0x5FA) << (16))


int main(void)
{

#if 0
	//No priorities or sub_prio configurations
#endif



#if 0
	//set different priorities to the two of them

	/*TIM2 is less urgent ====>> higher priority value*/
	NVIC_IPR7 &= ~(0x7U << 5);
	NVIC_IPR7 |=  (0x7U << 5);

	/*I2C is more urgent ====>> less priority value*/
	NVIC_IPR7 &= ~(0x7U << 29);
	NVIC_IPR7 |=  (0x1U << 29);

#endif


#if 0
	//set the same  priorities but different sub_prio

	/*setting the priority grouping bits to 0x05 */
	SCB_AIRCR = (0x5FA << 16 | 0x5 << 8);

	/* TIM2 same priority higher value in sub_prio ==> less urgent*/
	NVIC_IPR7 &= ~(0x07U << 5);
	NVIC_IPR7 |=  (0x07U << 5);
	/* I2C same priority less value in sub_prio ==> more urgent*/
	NVIC_IPR7 &= ~(0x7U  << 29);
	NVIC_IPR7 |=  (0x06U << 29);


#endif


#if 0
	//set the same  priorities same sub_prio

	/*setting the priority grouping bits to 0x05 */
	SCB_AIRCR = (0x5FA << 16 | 0x5 << 8);

	/* TIM2 same priority same sub_prio but the IRQ=28 ==> more urgent*/
	NVIC_IPR7 &= ~(0x07U << 5);
	NVIC_IPR7 |=  (0x07U << 5);

	/* I2C same priority same sub_prio but the IRQ=31 ==> less urgent*/
	NVIC_IPR7 &= ~(0x7U  << 29);
	NVIC_IPR7 |=  (0x07U << 29);


#endif


	//pend both interrupts

	NVIC_ISPR0 |= (1 << TIM2_IRQ_NUM);
	NVIC_ISPR0 |= (1 << I2CEVENT_IRQ_NUM);

	//enable both interrupts
	NVIC_ISER0 |= (1 << TIM2_IRQ_NUM);
	NVIC_ISER0 |= (1 << I2CEVENT_IRQ_NUM);

	//halt
	for(;;);

}

void TIM2_IRQHandler(void)
{
	int x = 12;
}

void I2C1_EV_IRQHandler(void)
{
	int y = 15;
}
