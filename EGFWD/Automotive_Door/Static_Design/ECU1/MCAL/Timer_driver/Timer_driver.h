#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H

#include "ECU1.h"
#include <stdint.h>



/******************TIMER APIs**************************/
void Timer_Init(Timer_handle_t *pTimer_handle);
void Timer_DeInit(Timer_TypeDef *pTIMERx);

void Timer_Set(uint32_t milliseconds);
uint32_t Timer_Get(void);

#endif