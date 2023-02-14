#include <string.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "main.h"

#define TRUE 			1
#define FALSE			0


void error_handler(void);


void UART2_init(void);
UART_HandleTypeDef huart2;

void SystemClock_Config(void);
RCC_OscInitTypeDef  osc_init;
RCC_ClkInitTypeDef  clk_init;



void Timer6_init(void);
TIM_HandleTypeDef htim6;


int main()
{
	HAL_Init();

	SystemClock_Config();

	UART2_init();

	Timer6_init();

	//SCB->SCR |= (1U << 1);
	HAL_PWR_EnableSleepOnExit();

	//start with TIm6 SR = 0
	TIM6->SR = 0;

	HAL_TIM_Base_Start_IT(&htim6);

	while(1)
	{
		//__WFI();
	}


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


void Timer6_init(void)
{
	memset(&htim6,0,sizeof(htim6));

	htim6.Instance 		 	= TIM6;
	htim6.Init.Period    	= 0x9C40; //10ms on 4 MHz timer clock
	htim6.Init.Prescaler 	= 1;
	htim6.Init.CounterMode 	= TIM_COUNTERMODE_UP;
	if(HAL_TIM_Base_Init(&htim6) != HAL_OK)
	{
		error_handler();
	}
}

char * message = "This is timer 6\r\n";
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(HAL_UART_Transmit(&huart2,(uint8_t *)message, strlen(message),HAL_MAX_DELAY) != HAL_OK)
		{
			error_handler();
		}
}




