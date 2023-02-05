
#ifndef BSP_H_
#define BSP_H_

#include <stdint.h>
#include "I2C_Driver.h"
#include "gpio_driver.h"


extern I2C_handle_t I2C1handle ;
extern GPIO_handle_t GPIOB_handle,GPIOC_handle;

void Button_init(void);
uint8_t Button_status(void);
void I2C1_master_TX_test(void);
void I2C1_master_RX_test(void);
void delay(uint32_t ticks);
void I2C1_master_RX_test_IT(void);
void I2C1_GPIO_init(void);


#endif