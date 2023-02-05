#include <string.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "main.h"

#define TRUE 			1
#define FAlSE			0

void error_handler(void);


void UART2_init(void);
UART_HandleTypeDef huart2;

RCC_OscInitTypeDef  osc_init;
RCC_ClkInitTypeDef  clk_init;


void SystemClock_Config(void);


int main()
{
	HAL_Init();

	SystemClock_Config();

	UART2_init();

	char buffer[100];

	/*print the SYSCLCK*/
	sprintf(buffer, "SYSCLCK =%ld HZ\r\n",HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2,(uint8_t *)buffer,strlen(buffer),HAL_MAX_DELAY);

	/*print the HCLK*/
	sprintf(buffer, "HCLK  =%ld HZ\r\n",HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2,(uint8_t *)buffer,strlen(buffer),HAL_MAX_DELAY);

	/*print the P1CLK*/
	sprintf(buffer, "P1CLK =%ld HZ\r\n",HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2,(uint8_t *)buffer,strlen(buffer),HAL_MAX_DELAY);

	/*print the P2CLK*/
	sprintf(buffer, "P2CLK =%ld HZ\r\n",HAL_RCC_GetPCLK2Freq());
	HAL_UART_Transmit(&huart2,(uint8_t *)buffer,strlen(buffer),HAL_MAX_DELAY);


	while(1);


	return 0;
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

void SystemClock_Config(void)
{
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	osc_init.HSEState		= RCC_HSE_OFF;
	osc_init.HSIState		= RCC_HSI_ON;
	osc_init.LSEState		= RCC_LSE_OFF;
	osc_init.LSIState		= RCC_LSI_OFF;
	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK)
	{
		error_handler();
	}

	clk_init.ClockType	   	= (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	clk_init.SYSCLKSource  	= RCC_SYSCLKSOURCE_HSI;
	clk_init.AHBCLKDivider 	= RCC_SYSCLK_DIV1;
	clk_init.APB1CLKDivider	= RCC_HCLK_DIV2;
	clk_init.APB2CLKDivider	= RCC_HCLK_DIV2;

	if(HAL_RCC_ClockConfig(&clk_init, FLASH_ACR_LATENCY_0WS)!= HAL_OK)
	{
		error_handler();
	}
}

