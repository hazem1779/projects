#include "DIO_driver.h"


uint8_t Dio_ReadChannel  (GPIO_Struct *GPIOx, uint8_t PortPinNum)
{
	uint8_t status;
	status =(uint8_t)((GPIOx->DATA >> PortPinNum)& 0x00000001);
	return status;
}


void  Dio_WriteChannel (GPIO_Struct *GPIOx, uint8_t PortPinNum, uint8_t level)
{
	if(level)
	{
		set_bit(GPIOx->DATA,PortPinNum);
	}
	else
	{
		clear_bit(GPIOx->DATA,PortPinNum);
	}		
}


void Dio_FlipChannel  (GPIO_Struct *GPIOx, uint8_t PortPinNum)
{
	toggle_bit(GPIOx->DATA,PortPinNum);
}


uint16_t Dio_ReadPort(GPIO_Struct *GPIOx)
{
	return (GPIOx->DATA & 0xFF);
}

void Dio_WritePort(GPIO_Struct *GPIOx , uint16_t data)
{
	GPIOx->DATA = data;
}

