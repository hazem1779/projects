#include "bsp.h"
#include <string.h>

void Init_SPI2_PINS(void)
{
	GPIO_CLK_CTRL(GPIOB,ENABLE);
	
	GPIO_handle_t GPIOB_handle;
	GPIOB_handle.pGPIOx = GPIOB;
	GPIOB_handle.gpio_pin_config.pin_Num 		= GPIO_PIN_NO_13; 	//clck pin
	GPIOB_handle.gpio_pin_config.pin_Mode 		= GPIO_MODE_ALTFUN;
	GPIOB_handle.gpio_pin_config.pin_AltFun		= AF5;
	GPIOB_handle.gpio_pin_config.pin_OutputMode = PUSH_PULL;
	GPIOB_handle.gpio_pin_config.pin_PUPD 		= PULL_UP;
	GPIOB_handle.gpio_pin_config.pin_Speed 		= VERY_HIGH_SPEED;
	GPIO_Init(&GPIOB_handle);
	
	//mosi
	GPIOB_handle.gpio_pin_config.pin_Num 		= GPIO_PIN_NO_15;
	GPIO_Init(&GPIOB_handle);
	
	//nss
	GPIOB_handle.gpio_pin_config.pin_Num 		= GPIO_PIN_NO_12;
	GPIO_Init(&GPIOB_handle);
	
	//miso
	GPIOB_handle.gpio_pin_config.pin_Num 		= GPIO_PIN_NO_14;
	GPIO_Init(&GPIOB_handle);
}

void SPI2_INIT(void)

{
	Init_SPI2_PINS();
	
	SPI_CLK_CTRL(SPI2, ENABLE);	
	
	SPI_handle_t SPI2_handle;
	
	SPI2_handle.pSPIx = SPI2;
	SPI2_handle.SPIConfig.BaudRate   = CLOCK_PRESCALAR_8;
	SPI2_handle.SPIConfig.BusConfig  = FULL_DUPLEX;
	SPI2_handle.SPIConfig.CPHA 		 = CPHA_LEADING;
	SPI2_handle.SPIConfig.CPOL		 = CPOL_LOW_IDLE;
	SPI2_handle.SPIConfig.DeviceMode = MASTER; 
	SPI2_handle.SPIConfig.DFF 		 = DFF_8bit;
	SPI2_handle.SPIConfig.SSM		 = SSM_DISABLE;
	SPI2_handle.SPIConfig.SSOE		 = SSOE_ENABLE;	
	
	SPI_Init(&SPI2_handle);	
 	
}



void Button_init(void)
{
	GPIO_CLK_CTRL(GPIOC, SET);
	
	GPIO_handle_t GPIOC_handle;
	GPIOC_handle.pGPIOx = GPIOC;
	GPIOC_handle.gpio_pin_config.pin_Num 		= GPIO_PIN_NO_13;
	GPIOC_handle.gpio_pin_config.pin_Mode 		= GPIO_MODE_IN;
	GPIOC_handle.gpio_pin_config.pin_OutputMode = PUSH_PULL;	
	GPIOC_handle.gpio_pin_config.pin_PUPD		= PULL_UP;
	GPIOC_handle.gpio_pin_config.pin_Speed		= VERY_HIGH_SPEED;	 
	
	GPIO_Init(&GPIOC_handle);	
}

uint8_t Button_status(void)
{
	uint8_t status;
	status = GPIO_PinRead(GPIOC, 13);
	return status; //button pressed--> status is 0 
}


void delay(uint32_t ticks)
{
	for (; ticks > 0; --ticks);
}
void SPI2_TEST(void)
{
	SPI_ENABLE(SPI2);
	
	char message[] = "hello world!";
	uint16_t dataLen =(uint16_t) strlen(message);
	SPI_Transmit(SPI2,&dataLen,1);
	
	uint16_t *TxBuffer = (uint16_t *) message;
	SPI_Transmit(SPI2, TxBuffer, strlen(message));
	
	while (SPI_Busy(SPI2));
	
	SPI_DISABLE(SPI2);
}

