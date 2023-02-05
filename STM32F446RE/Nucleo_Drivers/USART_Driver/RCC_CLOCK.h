#ifndef RCC_CLOCK_H
#define RCC_CLOCK_H

#include "stm32f446xx.h"

#define HSI					0U	
#define HSE					1U
#define PLL					2U	
#define PLLR				3U


uint32_t get_AHPPrescalar(void);
uint32_t get_ABP1Prescalar(void);
uint32_t get_ABP2Prescalar(void);
uint32_t get_ClockFreq(void);

//Clock of APB1 
uint32_t RCC_GetPCLK1_HZ(void);


//Clock of APB2
uint32_t RCC_GetPCLK2_HZ(void);

#endif //RCC_CLOCK_H