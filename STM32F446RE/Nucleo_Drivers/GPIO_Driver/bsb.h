#ifndef BSB_H
#define BSB_H

#include <stdint.h>
#include "gpio_driver.h"

void LED_init(void);
void LED_Toggle(void);
void delay(uint32_t ticks);
void Button_init(void);
void Button_init_Interrupt(void);
void LED_ON(void);
void LED_OFF(void);
uint8_t Button_status(void);

#endif // BSB_H

