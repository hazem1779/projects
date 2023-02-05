#include "IntCtrl_driver.h"

void InterruptCtrl(IRQ_Number IRQ)
{
	uint32_t temp1,temp2;
	temp1 =IRQ / 32;
	temp2 = IRQ % 32;
	NVIC_EN(temp1) |= (1U << temp2);
	NVIC_EN(temp1) |= (1U << temp2);
	
}