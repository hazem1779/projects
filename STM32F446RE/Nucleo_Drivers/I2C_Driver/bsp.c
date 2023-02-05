#include "bsp.h"
#include <string.h>

uint32_t tx,rx; //global variables to check event callbacks

#define SLAVE_ADDR   0x68
#define Master_address 0x61

static const I2C_handle_t EmptyStruct;
I2C_handle_t I2C1handle;
GPIO_handle_t GPIOB_handle,GPIOC_handle;

void Button_init(void)
{
	GPIO_CLK_CTRL(GPIOC, SET);
	
	GPIOC_handle.pGPIOx = GPIOC;
	GPIOC_handle.gpio_pin_config.pin_Num 		= GPIO_PIN_NO_13;
	GPIOC_handle.gpio_pin_config.pin_Mode 		= GPIO_MODE_IN;
	GPIOC_handle.gpio_pin_config.pin_OutputMode = PUSH_PULL;	
	GPIOC_handle.gpio_pin_config.pin_PUPD		= PULL_UP;
	GPIOC_handle.gpio_pin_config.pin_Speed		= VERY_HIGH_SPEED;	 
	
	GPIO_Init(&GPIOC_handle);	
}


void delay(uint32_t ticks)
{
	for (; ticks > 0; --ticks);
}

uint8_t Button_status(void)
{
	uint8_t status;
	status = GPIO_PinRead(GPIOC, 13);
	return !status; //button pressed--> status is 0 (normal condition it reads)
}


/*VERY IMPORTANT NOTE:*/

void I2C1_GPIO_init(void)
{

	GPIOB_handle.pGPIOx = GPIOB;
	GPIOB_handle.gpio_pin_config.pin_Mode 		= GPIO_MODE_ALTFUN;
	GPIOB_handle.gpio_pin_config.pin_AltFun		= AF4;	
	GPIOB_handle.gpio_pin_config.pin_OutputMode = OPEN_DRAIN;
	GPIOB_handle.gpio_pin_config.pin_PUPD		= PULL_UP;	
	GPIOB_handle.gpio_pin_config.pin_Speed		= VERY_HIGH_SPEED;	 

 /*************************************************************/
	/*IMPORTANT NOTES: Both Busy flag bug and SB bug (stated in the errata sheet of stm32fx boards)
		are fixed using the block after this comment
	1-Busy-Flag always set is fixed by reseting the peripheral
	2-SB Flag is not set is fixed by enabling I2C Clock first then GPIO clock and 
	enabling then disabling analog filter in between the clocking
  *************************************************************/
	#if 1
	I2C_CLK_CTRL(I2C1, ENABLE);
	I2C1_RESET();
	delay(10000);
	I2C1_RESET_CLEAR();
	I2C1->FLTR |= (1U << 4);
	I2C1->FLTR &= ~(1U << 4);
	GPIO_CLK_CTRL(GPIOB, ENABLE);
	#endif

	
	//SCL
	GPIOB_handle.gpio_pin_config.pin_Num 		= GPIO_PIN_NO_6;	
	GPIO_Init(&GPIOB_handle);	
	
	//SDA
	GPIOB_handle.gpio_pin_config.pin_Num 		= GPIO_PIN_NO_7;
	GPIO_Init(&GPIOB_handle);
}

void I2C1_master_TX_test(void)
{
	I2C1handle = EmptyStruct;
	
	I2C1handle.pI2Cx 				= I2C1;
	I2C1handle.I2CConfig.AckControl = ACK;
	I2C1handle.DevAddr 				= SLAVE_ADDR;
	I2C1handle.I2CConfig.SCLspeed 	= SM_100KHz;
	
	I2C_Init(&I2C1handle);
		
	uint8_t buffer[]= "STM32 MASTER I2C1 TEST!"; //data must be less than 32 bytes according to arduino wire library to happen in one transaction
	I2CMasterSend(&I2C1handle, buffer, strlen((const char*)buffer), SLAVE_ADDR);
}


void I2C1_master_RX_test(void)
{
	I2C1handle = EmptyStruct;

	I2C1handle.pI2Cx = I2C1;
	I2C1handle.I2CConfig.AckControl = ACK;
	I2C1handle.DevAddr = SLAVE_ADDR;
	I2C1handle.I2CConfig.SCLspeed = SM_100KHz;
	
	I2C_Init(&I2C1handle);
		
	// Master sends command 0x51 to get length (1 byte) of information sent by slave
	// Master sends command 0x52 to get length of information sent by slave
	uint8_t command = 0x51; 
	uint8_t len;

	uint8_t Rxbuffer[32];
	
	I2CMasterSend(&I2C1handle, &command, 1, SLAVE_ADDR);
	I2CMasterReceive(&I2C1handle, &len, 1, SLAVE_ADDR);
	
	command = 0x52;
	I2CMasterSend(&I2C1handle, &command, sizeof(command), SLAVE_ADDR);
	I2CMasterReceive(&I2C1handle, Rxbuffer, len, SLAVE_ADDR);	
}

void I2C1_master_RX_test_IT(void)
 {
	I2C1handle = EmptyStruct;
	
	 //I2C peripheral configurations
	I2C1handle.pI2Cx = I2C1;
	I2C1handle.I2CConfig.AckControl = ACK;
	I2C1handle.DevAddr = SLAVE_ADDR;
	I2C1handle.I2CConfig.SCLspeed = SM_100KHz;
	
	
	I2C_Init(&I2C1handle);

	//I2C IRQ configuration
	I2C_IRQConfig(I2C1_EV_IRQn,ENABLE);
	I2C_IRQConfig(I2C1_ER_IRQn,ENABLE);
		
	// Master sends command 0x51 to get length (1 byte) of information sent by slave
	// Master sends command 0x52 to get length of information sent by slave
	uint8_t command = 0x51; 
	uint8_t len;

	uint8_t Rxbuffer[32];
	
	
	while(I2CMasterSendIT(&I2C1handle, &command, 1, SLAVE_ADDR,ENABLE_SR) != I2C_READY);
	I2C_SendDone(&I2C1handle);
	
	while(I2CMasterReceiveIT(&I2C1handle, &len, 1, SLAVE_ADDR,ENABLE_SR)  != I2C_READY);
	I2C_ReceiveDone(&I2C1handle);
	
	command = 0x52;
	while(I2CMasterSendIT(&I2C1handle, &command, 1, SLAVE_ADDR,ENABLE_SR) != I2C_READY);
	I2C_SendDone(&I2C1handle);
	
	while(I2CMasterReceiveIT(&I2C1handle, Rxbuffer, len, SLAVE_ADDR,DISABLE_SR)  != I2C_READY);	
	I2C_ReceiveDone(&I2C1handle);
}
 

void I2C1_EV_IRQHandler(void)
{
	I2C_EV_IRQHandle(&I2C1handle);
}

void I2C1_ER_IRQHandler(void)
{
	I2C_ER_IRQHandle(&I2C1handle);
}

void I2C_AppEventCallBack(I2C_handle_t *I2Chandle, uint8_t EVENT)
{
	if (EVENT == I2C_EV_TX_DONE)
	{
		tx = 1;
	}
	if (EVENT == I2C_EV_STOPF)
	{
		while(1);
	}
	if (EVENT == I2C_EV_RX_DONE)
	{
		rx = 1;
	}
	if (EVENT == I2C_ERROR_BERR)
	{
		while(1);
	}
	if (EVENT == I2C_ERROR_ARLO)
	{
		while(1);
	}
	if (EVENT == I2C_ERROR_AF)
	{
		I2C_SendDone(I2Chandle);
		I2C_GenStop(I2Chandle->pI2Cx);
		while(1);
	}
	if (EVENT == I2C_ERROR_OVR)
	{
		while(1);
	}
	if (EVENT == I2C_ERROR_TIMEOUT)
	{
		while(1);
	}	
}
