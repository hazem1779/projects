#include <string.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "main.h"

#define TRUE 			1
#define FALSE			0
#define Pulse_1			4000
#define Pulse_2			2000
#define Pulse_3			1000
#define Pulse_4			500


void error_handler(void);


void UART2_init(void);
UART_HandleTypeDef huart2;

void SystemClock_Config(void);
RCC_OscInitTypeDef  osc_init;
RCC_ClkInitTypeDef  clk_init;



void Timer2_init(void);
TIM_HandleTypeDef htim2;
TIM_OC_InitTypeDef tim2_OC;


int main()
{
	HAL_Init();

	SystemClock_Config();

	UART2_init();

	Timer2_init();

	if (HAL_TIM_OC_Start_IT(&htim2,TIM_CHANNEL_1) != HAL_OK)
	{
		error_handler();
	}
	if (HAL_TIM_OC_Start_IT(&htim2,TIM_CHANNEL_2) != HAL_OK)
	{
		error_handler();
	}
	if (HAL_TIM_OC_Start_IT(&htim2,TIM_CHANNEL_3) != HAL_OK)
	{
		error_handler();
	}
	if (HAL_TIM_OC_Start_IT(&htim2,TIM_CHANNEL_4) != HAL_OK)
	{
		error_handler();
	}


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
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState		= RCC_HSE_BYPASS;
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


void Timer2_init(void)
{
	memset(&htim2,0,sizeof(htim2));

	htim2.Instance 		 	= TIM2;
	htim2.Init.Period    	= 0xFFFFFFFF;
	htim2.Init.Prescaler 	= 1;
	htim2.Init.CounterMode 	= TIM_COUNTERMODE_UP;
	if(HAL_TIM_OC_Init(&htim2) != HAL_OK)
	{
		error_handler();
	}

	tim2_OC.OCMode		= TIM_OCMODE_TOGGLE;
	tim2_OC.OCPolarity	= TIM_OCPOLARITY_HIGH;

	tim2_OC.Pulse		= Pulse_1;
	if(HAL_TIM_OC_ConfigChannel(&htim2, &tim2_OC, TIM_CHANNEL_1) != HAL_OK)
	{
		error_handler();
	}

	tim2_OC.Pulse		= Pulse_2;
	if(HAL_TIM_OC_ConfigChannel(&htim2, &tim2_OC, TIM_CHANNEL_2) != HAL_OK)
	{
		error_handler();
	}

	tim2_OC.Pulse		= Pulse_3;
	if(HAL_TIM_OC_ConfigChannel(&htim2, &tim2_OC, TIM_CHANNEL_3) != HAL_OK)
	{
		error_handler();
	}

	tim2_OC.Pulse		= Pulse_4;
	if(HAL_TIM_OC_ConfigChannel(&htim2, &tim2_OC, TIM_CHANNEL_4) != HAL_OK)
	{
		error_handler();
	}

}
uint32_t ccr_value;
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	switch(htim2.Channel)
	{
		case HAL_TIM_ACTIVE_CHANNEL_1:
			//TIM2->CCR1 = TIM2->CCR1 + Pulse_1;
			ccr_value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			__HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_1,ccr_value+Pulse_1);
			break;
		case HAL_TIM_ACTIVE_CHANNEL_2:
			//TIM2->CCR2 = TIM2->CCR2 + Pulse_2;
			ccr_value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
			__HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_2,ccr_value+Pulse_2);
			break;
		case HAL_TIM_ACTIVE_CHANNEL_3:
			//TIM2->CCR3 = TIM2->CCR3 + Pulse_3;
			ccr_value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
			__HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_3,ccr_value+Pulse_3);
			break;
		case HAL_TIM_ACTIVE_CHANNEL_4:
			//TIM2->CCR4 = TIM2->CCR4 + Pulse_4;
			ccr_value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
			__HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_4,ccr_value+Pulse_4);
			break;

		default:
			break;
	}
}




