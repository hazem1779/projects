#ifndef BSP_H
#define BSP_H

#include "USART_Driver.h"
#include "gpio_driver.h"

void USART2_TEST_init(void);
void USART2_GPIO_Init(void);
void Button_init(void);
void delay(uint32_t ticks);
uint8_t Button_status(void);

extern USART_handle_t USART2handle;
extern GPIO_handle_t  GPIOAhandle;
#endif
