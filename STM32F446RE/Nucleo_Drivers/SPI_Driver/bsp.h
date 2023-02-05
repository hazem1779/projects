#ifndef BSP_H
#define BSP_H

#include "gpio_driver.h"
#include "spi_driver.h"

void Button_init(void);
void delay(uint32_t ticks);
void Init_SPI2_PINS(void);
void SPI2_TEST(void);
void SPI2_INIT(void);
uint8_t Button_status(void);


#endif //BSP_H
