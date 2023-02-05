#include "RCC_CLOCK.h"

uint32_t get_ABP1Prescalar(void)
{
	uint32_t Pre =0;
	uint32_t ABP1Pre = (RCC->CFGR >> 10) & (0x7U);
	if (ABP1Pre == 4)
	{
		Pre = 2;	
	}
	else if (ABP1Pre == 5)
	{
		Pre = 4;	
	}
	else if (ABP1Pre == 6)
	{
		Pre = 8;		
	}
	else if (ABP1Pre == 7)
	{
		Pre = 16;		
	}
	else 
	{
		Pre = 1;		
	}
	return Pre;	
}
uint32_t get_AHPPrescalar(void)
{
	uint32_t Pre =0;
	uint32_t AHPPre = (RCC->CFGR >> 4) & (0xFU);
	if (AHPPre == 8)
	{
		Pre = 2;	
	}
	else if (AHPPre == 9)
	{
		Pre = 4;	
	}
	else if (AHPPre == 10)
	{
		Pre = 8;		
	}
	else if (AHPPre == 11)
	{
		Pre = 16;		
	}
	else if (AHPPre == 12)
	{
		Pre = 64;		
	}
	else if (AHPPre == 13)
	{
		Pre = 128;		
	}
	else if (AHPPre == 14)
	{
		Pre = 256;		
	}
	else if (AHPPre == 15)
	{
		Pre = 512;		
	}
	else 
	{
		Pre = 1;		
	}
	return Pre;	
}

uint32_t get_ClockFreq(void)
{
	uint32_t CLOCKsrc;
	uint32_t CLOCK =0;
	
	CLOCKsrc  = (RCC->CFGR >> 2) & (0x3U); 	//Extract bits 2 and 3 to know which clock source is used	
	

	if (CLOCKsrc == HSI)
	{
		CLOCK = 16000000U; //internal oscillator 
	}
	else if(CLOCKsrc == HSE)
	{
		//TODO
		CLOCK=0;
	}
	else if(CLOCKsrc == PLL)
	{
		CLOCK=0;
		//TODO
	}
	else if (CLOCKsrc == PLLR)
	{
		CLOCK=0;
		//TODO
	}	
	return CLOCK;
}
uint32_t RCC_GetPCLK1_HZ(void)
{
	uint32_t freq, CLOCK, AHPPre, APBPre;
	
	CLOCK 	  = get_ClockFreq();	
	AHPPre 	  = get_AHPPrescalar();
	APBPre    = get_ABP1Prescalar(); 	
	
	
	
	freq = (CLOCK/AHPPre)/APBPre;
	return freq;	
}


uint32_t get_ABP2Prescalar(void)
{
	uint32_t Pre =0;
	uint32_t ABP2Pre = (RCC->CFGR >> 13) & (0x7U);
	if (ABP2Pre == 4)
	{
		Pre = 2;	
	}
	else if (ABP2Pre == 5)
	{
		Pre = 4;	
	}
	else if (ABP2Pre == 6)
	{
		Pre = 8;		
	}
	else if (ABP2Pre == 7)
	{
		Pre = 16;		
	}
	else 
	{
		Pre = 1;		
	}
	return Pre;		
}

uint32_t RCC_GetPCLK2_HZ(void)
{
	uint32_t freq, CLOCK, AHPPre, APBPre;
	
	CLOCK 	  = get_ClockFreq();	
	AHPPre 	  = get_AHPPrescalar();
	APBPre    = get_ABP2Prescalar(); 	
	
	
	
	freq = (CLOCK/AHPPre)/APBPre;
	return freq;
}



