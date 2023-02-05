#ifndef SYSTICK_DRIVER_H
#define SYSTICK_DRIVER_H

#include <stdint.h>

#define Systick_CTRL				*((volatile uint32_t *)0xE000E010)
#define Systick_LOAD				*((volatile uint32_t *)0xE000E014)
#define Systick_CURRENT				*((volatile uint32_t *)0xE000E018)
	
#define Second				(160000000U-1U)

void Systick_Callback(void);
#endif