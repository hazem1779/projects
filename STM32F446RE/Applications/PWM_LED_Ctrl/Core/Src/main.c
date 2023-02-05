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



void Timer2_init(void);
TIM_HandleTypeDef htim2;
TIM_OC_InitTypeDef tim2_PWM;


int main()
{
	uint16_t brightness = 0;
	HAL_Init();

	SystemClock_Config();

	UART2_init();

	Timer2_init();

	if (HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1) != HAL_OK)
	{
		error_handler();
	}

	while(1)
	{
		while(brightness < htim2.Init.Period)
		{
			brightness+=10;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,brightness);
			HAL_Delay(1);
		}
		while (brightness > 0)
		{
			brightness-=10;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,brightness);
			HAL_Delay(1);
		}

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

}


void Timer2_init(void)
{
	memset(&htim2,0,sizeof(htim2));

	htim2.Instance 		 	= TIM2;
	htim2.Channel			= HAL_TIM_ACTIVE_CHANNEL_1;
	htim2.Init.Prescaler 	= 0;
	htim2.Init.Period    	= 8000-1;	//HSE = 8 Mhz, Tim_clck = (8Mhz/(pre+1)) 1ms period
	htim2.Init.CounterMode 	= TIM_COUNTERMODE_UP;
	if(HAL_TIM_PWM_Init(&htim2) != HAL_OK)
	{
		error_handler();
	}

	memset(&tim2_PWM,0,sizeof(tim2_PWM));
	tim2_PWM.OCMode		= TIM_OCMODE_PWM1;
	tim2_PWM.OCPolarity	= TIM_OCPOLARITY_HIGH;
	tim2_PWM.Pulse		= 0;
	if(HAL_TIM_PWM_ConfigChannel(&htim2, &tim2_PWM, TIM_CHANNEL_1) != HAL_OK)
	{
		error_handler();
	}

}



