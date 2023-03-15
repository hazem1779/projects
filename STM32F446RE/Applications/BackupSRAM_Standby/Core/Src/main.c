#include <string.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "main.h"

void error_handler(void);


void UART2_init(void);
UART_HandleTypeDef huart2;

void SystemClock_Config(void);
RCC_OscInitTypeDef  osc_init;
RCC_ClkInitTypeDef  clk_init;


void write_BackupSRAM(void);


int main()
{
	HAL_Init();

	SystemClock_Config();

	UART2_init();

	write_BackupSRAM();

	while(1)
	{

	}

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
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState		= RCC_HSE_BYPASS;	//8MHz clock
	osc_init.HSIState		= RCC_HSI_OFF;
	osc_init.LSEState		= RCC_LSE_OFF;
	osc_init.LSIState		= RCC_LSI_OFF;
	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK)
	{
		error_handler();
	}

	clk_init.ClockType	   	= (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	clk_init.SYSCLKSource  	= RCC_SYSCLKSOURCE_HSE;
	clk_init.AHBCLKDivider 	= RCC_SYSCLK_DIV1;
	clk_init.APB1CLKDivider	= RCC_HCLK_DIV1;
	clk_init.APB2CLKDivider	= RCC_HCLK_DIV1;

	if(HAL_RCC_ClockConfig(&clk_init, FLASH_ACR_LATENCY_0WS)!= HAL_OK)
	{
		error_handler();
	}

	//configure PA8 as MCO1
	//HAL_RCC_MCOConfig(RCC_MCO1,RCC_MCO1SOURCE_LSE,RCC_MCODIV_1);
}

void write_BackupSRAM(void)
{
	//1. Turn on the clock for Backup SRAM and power controller
	__HAL_RCC_BKPSRAM_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();

	//2. Enable Write access to Backup Domain
	HAL_PWR_EnableBkUpAccess();
	uint32_t *pBKSRAM = (uint32_t *)BKPSRAM_BASE;
	char buffer[] = "Hello";
	uint32_t length = strlen(buffer) + 1;
	for(uint32_t i =0; i < length; i++)
	{
		pBKSRAM[i] = (uint32_t) buffer[i];
	}

	HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);
	HAL_PWREx_EnableBkUpReg();
	HAL_PWR_EnterSTANDBYMode();
}





