
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define USART3_IRQ_NUM 39

int main(void)
{
   //manually set the pending state for usart3

	uint32_t *pISPR1 = (uint32_t *) 0XE000E204;
	*pISPR1 |= (1U << (USART3_IRQ_NUM % 32));

	// enable the IRQ number in NVIC (processor side)

	uint32_t *pISER1 =  (uint32_t *) 0xE000E104;
	*pISER1 |= (1U << (USART3_IRQ_NUM % 32));



}

//USART3 ISR

void USART3_IRQHandler(void)
{
	for(;;);
}
