#ifndef LEDCONFIG_H
#define LEDCONFIG_H

#include "DIO_driver.h"
#include "GPT_driver.h"
#include "IntCtrl_driver.h"
#include "SysTick_driver.h"
#define PINS_USED		4

extern const GPIO_Handle_Struct Config_Array[PINS_USED] ;
void blinky_RED(void);

#endif		//LEDCONFIG_H