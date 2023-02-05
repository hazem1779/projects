#include<string.h>
#include "stm32f4xx_hal.h"
#include "main.h"

void SystemClockConfig(void);
void UART2_init(void);
void error_handler(void);
uint8_t convert_to_caps(uint8_t small);

UART_HandleTypeDef huart2;

char *buffer = "This is me\r\n";

int main()
{
	HAL_Init();
	SystemClockConfig();

	UART2_init();
	if(HAL_UART_Transmit(&huart2,(uint8_t *)buffer,strlen(buffer),HAL_MAX_DELAY) != HAL_OK)
	{
		error_handler();
	}

	uint8_t data;
	uint8_t count= 0;
	uint8_t data_buffer[100];
	while(1)
	{
		(void)HAL_UART_Receive(&huart2,&data,1,HAL_MAX_DELAY);
		if (data == '\r'){
			break;
		}
		else
		{
			data_buffer[count++]=convert_to_caps(data);
		}
	}
	data_buffer[count++]='\r';
	(void)HAL_UART_Transmit(&huart2,(uint8_t *)data_buffer,count,HAL_MAX_DELAY);

	while(1)
	{
		;
	}

	return 0;
}

void SystemClockConfig(void)
{

}
void error_handler(void)
{
	while(1);
}

void UART2_init(void)
{
	huart2.Instance 		= USART2;
	huart2.Init.BaudRate 	= 115200;
	huart2.Init.WordLength 	= UART_WORDLENGTH_8B;
	huart2.Init.HwFlowCtl 	= UART_HWCONTROL_NONE;
	huart2.Init.Mode		= UART_MODE_TX_RX;
	huart2.Init.OverSampling= UART_OVERSAMPLING_16;
	huart2.Init.StopBits	= UART_STOPBITS_1;
	huart2.Init.Parity		= UART_PARITY_NONE;



	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		error_handler();
	}

}

uint8_t convert_to_caps(uint8_t small)
{
	if(small >= 'a' && small <= 'z'){
		return small-32;
	}
	else
	{
		return small;
	}
}

