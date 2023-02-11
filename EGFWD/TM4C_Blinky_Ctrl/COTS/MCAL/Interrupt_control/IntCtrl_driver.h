#ifndef INTCTRL_DRIVER_H
#define INTCTRL_DRIVER_H


#include <stdint.h>

#define NVIC_EN(x)	*((volatile uint32_t *)(0xE000E100+(4*x)))

typedef enum
{
	//TBD
	GPIOF_IRQ	 = 30,
	WTIMER0B_IRQ = 95
	//TBD
}IRQ_Number;



void InterruptCtrl(IRQ_Number IRQ);


#endif