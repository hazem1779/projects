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
TIM_IC_InitTypeDef tim2_Ic;
uint32_t capture_diff = 0;
double tim2_clck,timer2_res,input_signal_period,input_signal_freq;
uint32_t capture_difference[2] = {0,0};
uint32_t count = 1;
uint32_t is_capture_done = FALSE;

int main()
{
	char buffer[100];
	HAL_Init();

	SystemClock_Config();

	UART2_init();

	Timer2_init();
	HAL_TIM_IC_Start_IT(&htim2,TIM_CHANNEL_1);



	while(1)
	{
		if (is_capture_done)
		{
			if(capture_difference[1] > capture_difference[0])
			{
				capture_diff = capture_difference[1] - capture_difference[0];
			}
			else
			{
				capture_diff = (0xFFFFFFFF - capture_difference[0]) + capture_difference[1];
			}


			tim2_clck = ((HAL_RCC_GetPCLK1Freq() * 1) / (htim2.Init.Prescaler + 1));
			timer2_res = 1 / tim2_clck;
			input_signal_period = capture_diff * timer2_res;
			input_signal_freq = 1 / input_signal_period;
			sprintf(buffer,"the frequency of the input signal is %f\r",input_signal_freq);

			HAL_UART_Transmit(&huart2,(uint8_t *)buffer,sizeof(buffer),HAL_MAX_DELAY);
			is_capture_done = FALSE;
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
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE ;
	osc_init.HSEState		= RCC_HSE_BYPASS;
	osc_init.HSIState		= RCC_HSI_OFF;
	osc_init.LSEState		= RCC_LSE_ON;
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
	HAL_RCC_MCOConfig(RCC_MCO1,RCC_MCO1SOURCE_LSE,RCC_MCODIV_1);
}


void Timer2_init(void)
{
	memset(&htim2,0,sizeof(htim2));

	htim2.Instance 		 	= TIM2;
	htim2.Init.Period    	= 0xFFFFFFFF;
	htim2.Init.Prescaler 	= 1;
	htim2.Init.CounterMode 	= TIM_COUNTERMODE_UP;

	htim2.Channel	=  HAL_TIM_ACTIVE_CHANNEL_1;
	if(HAL_TIM_IC_Init(&htim2) != HAL_OK)
	{
		error_handler();
	}

	tim2_Ic.ICPolarity	= TIM_ICPOLARITY_RISING;
	tim2_Ic.ICSelection = TIM_ICSELECTION_DIRECTTI;
	tim2_Ic.ICFilter 	= 0;
	tim2_Ic.ICPrescaler = TIM_ICPSC_DIV1;

	if(HAL_TIM_IC_ConfigChannel(&htim2, &tim2_Ic, TIM_CHANNEL_1) != HAL_OK)
	{
		error_handler();
	}
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(! is_capture_done )
	{
		if (count == 1)
		{

			capture_difference[0] = __HAL_TIM_GET_COMPARE(htim,TIM_CHANNEL_1);
			++count;
		}
		else if(count == 2)
		{
			capture_difference[1] = __HAL_TIM_GET_COMPARE(htim,TIM_CHANNEL_1);
			count = 1;
			is_capture_done = TRUE;
		}
	}
}



