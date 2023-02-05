#include <stdint.h>
#include "main.h"
#include <stdio.h>

void delay(uint64_t ticks);

int main(void)
{

	RCC_AHB1ENR_t   volatile *const RCC_AHB1ENR_R     =  (RCC_AHB1ENR_t *)0x40023830;
	RCC_AHB1ENR_R->gpioc_en = 1U;


	GPIOx_MODE_t    volatile *const GPIOC_MODE_R      =  (GPIOx_MODE_t*)0x40020800;
	GPIOx_ODR_t     volatile *const GPIOC_ODR_R       =  (GPIOx_ODR_t *)0x40020814;
	GPIOx_IDR_t     volatile *const GPIOC_IDR_R       =  (GPIOx_IDR_t *)0x40020810;
	GPIOx_PUPDR_t   volatile *const GPIOC_PUPDR_R     =  (GPIOx_PUPDR_t *)0x4002080C;

/*----------------GPIOC_MODE CONFIGURE--------------*/

	//Columns are implemented as inputs
	GPIOC_MODE_R->pin_2  =	0;
	GPIOC_MODE_R->pin_3  =	0;
	GPIOC_MODE_R->pin_10 =	0;
	GPIOC_MODE_R->pin_12 =	0;

	//Pull-up resistors for the inputs
	GPIOC_PUPDR_R->pin_3  = 1;//c1
	GPIOC_PUPDR_R->pin_2  = 1;//c2
	GPIOC_PUPDR_R->pin_12 = 1;//c3
	GPIOC_PUPDR_R->pin_10 = 1;//c4

	//Rows are implemented as outputs
	GPIOC_MODE_R->pin_11  =	1;
	GPIOC_MODE_R->pin_13  =	1;
	GPIOC_MODE_R->pin_0  =	1;
	GPIOC_MODE_R->pin_1  =	1;

	//Pull-down resistors for the outputs
	GPIOC_PUPDR_R->pin_11  =	2;
	GPIOC_PUPDR_R->pin_13  =	2;
	GPIOC_PUPDR_R->pin_0   =	2;
	GPIOC_PUPDR_R->pin_1   =	2;

	//Rows are HIGH-state as default
	GPIOC_ODR_R->pin_11  =	1;
	GPIOC_ODR_R->pin_13  =	1;
	GPIOC_ODR_R->pin_0  =	1;
	GPIOC_ODR_R->pin_1  =	1;

	/*SCANNING KEYS FOR THE DETECTING THE PRESSED ONE*/

	while(1)
	{
		/*-----------ROW1--------------*/
		GPIOC_ODR_R->pin_11 = 0;
		if(GPIOC_IDR_R->pin_3 == 0)
		{
			delay(300000);
			printf("Key 1 is pressed\n");

		}
		if(GPIOC_IDR_R->pin_2 == 0)
		{
			delay(300000);
			printf("Key 2 is pressed\n");

		}
		if(GPIOC_IDR_R->pin_12 == 0)
		{
			delay(300000);
			printf("Key 3 is pressed\n");

		}
		if(GPIOC_IDR_R->pin_10 == 0)
		{
			delay(300000);
			printf("Key A is pressed\n");
		}
		GPIOC_ODR_R->pin_11 = 1;

		/*-----------ROW2--------------*/
		GPIOC_ODR_R->pin_13 = 0;
		if(GPIOC_IDR_R->pin_3 == 0)
		{
			delay(300000);
			printf("Key 4 is pressed\n");
		}
		if(GPIOC_IDR_R->pin_2 == 0)
		{
			delay(300000);
			printf("Key 5 is pressed\n");
		}
		if(GPIOC_IDR_R->pin_12 == 0)
		{
			delay(300000);
			printf("Key 6 is pressed\n");
		}
		if(GPIOC_IDR_R->pin_10 == 0)
		{
			delay(300000);
			printf("Key B is pressed\n");
		}
		GPIOC_ODR_R->pin_13 = 1;

		/*-----------ROW3--------------*/
		GPIOC_ODR_R->pin_0 = 0;
		if(GPIOC_IDR_R->pin_3 == 0)
		{
			delay(300000);
			printf("Key 7 is pressed\n");
		}
		if(GPIOC_IDR_R->pin_2 == 0)
		{
			delay(300000);
			printf("Key 8 is pressed\n");
		}
		if(GPIOC_IDR_R->pin_12 == 0)
		{
			delay(300000);
			printf("Key 9 is pressed\n");
		}
		if(GPIOC_IDR_R->pin_10 == 0)
		{
			delay(300000);
			printf("Key C is pressed\n");
		}
		GPIOC_ODR_R->pin_0 = 1;

		/*-----------ROW4--------------*/
		GPIOC_ODR_R->pin_1 = 0;
		if(GPIOC_IDR_R->pin_3 == 0)
		{
			delay(300000);
			printf("Key * is pressed\n");
		}
		if(GPIOC_IDR_R->pin_2 == 0)
		{
			delay(300000);
			printf("Key 0 is pressed\n");
		}
		if(GPIOC_IDR_R->pin_12 == 0)
		{
			delay(300000);
			printf("Key # is pressed\n");
		}
		if(GPIOC_IDR_R->pin_10 == 0)
		{
			delay(300000);
			printf("Key D is pressed\n");
		}
		GPIOC_ODR_R->pin_1 = 1;

	}

}
