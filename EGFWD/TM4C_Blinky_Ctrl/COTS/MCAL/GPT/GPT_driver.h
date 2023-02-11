#ifndef GPT_DRIVER_H
#define GPT_DRIVER_H



#include "GPIO_driver.h"
/*************************************************************************
**					TYPEDEF	VARIABLES , ENUMS & STRUCTS					**
*************************************************************************/

typedef volatile uint32_t gpt_type;
typedef struct 
{
	gpt_type GPTMCFG;
	gpt_type GPTMTAMR;
	gpt_type GPTMTBMR;
	gpt_type GPTMCTL;
	gpt_type GPTMSYNC;
	gpt_type RESERVED;	
	gpt_type GPTMIMR;
	gpt_type GPTMRIS;
	gpt_type GPTMMIS;
	gpt_type GPTMICR;
	gpt_type GPTMTAILR;
	gpt_type GPTMTBILR;
	gpt_type GPTMTAMATCHR;
	gpt_type GPTMTBMATCHR;
	gpt_type GPTMTAPR;
	gpt_type GPTMTBPR;	
	gpt_type GPTMTAPMR;
	gpt_type GPTMTBPMR;
	gpt_type GPTMTAR;
	gpt_type GPTMTBR;
	gpt_type GPTMTAV;
	gpt_type GPTMTBV;
	gpt_type GPTMRTCPD;
	gpt_type GPTMTBPS;
	gpt_type GPTMTAPV;
	gpt_type GPTMTBPV;
	gpt_type RESERVED1[981];
	gpt_type GPTMPP;
}GPT_STRUCT;


/*************************************************************************
**				GPT_DRIVER RELATED DEFINITONS							**
*************************************************************************/

#define Fclk		16000000UL
#define RCGCWTIMER						*((volatile uint32_t *)0x400FE65C)
#define WTIMER_0						((GPT_STRUCT *)0x40036000)
#if 0
#define TIMER_1
#define TIMER_2
#define TIMER_3
#define TIMER_4
#define TIMER_5
#endif


/*************************************************************************
**						APIs PROTOTYPES									**
*************************************************************************/
void GPT_Init_ModePWM(void);
void clear_RIS(void);
void PWM_ISR(void);


#endif