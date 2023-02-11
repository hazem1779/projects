#include <stdint.h>
#include <stdio.h>
#include "header.h"

#if 0
uint32_t  extern pspOfTasks[MAX_TASKS];
uint32_t  extern taskHandlers[MAX_TASKS];
#endif

uint8_t   current_task = 0; //global variable for current task running


typedef struct
{
	uint32_t psp_value;
	uint32_t block_state;
	uint8_t  current_state;
	void (* task_handler)(void);
} TCB_T;

TCB_T user_tasks[MAX_TASKS];

void task1_handler (void)
{
	while(1)
	{
		printf("This is task==>> 1\n");
	}
}

void task2_handler (void)
{
	while(1)
	{
		printf("This is task==>> 2\n");
	}
}

void task3_handler (void)
{
	while(1)
	{
		printf("This is task==>> 3\n");
	}
}

void task4_handler (void)
{
	while(1)
	{
		printf("This is task==>> 4\n");
	}
}


void enable_processor_faults(void)
{
	SCB_SHCSR |= (USGFAULTENA | BUSFAULTENA | MEMFAULTENA);

}



uint32_t get_psp_value(void) //helper function
{
	return user_tasks[current_task].psp_value;
}

__attribute__((naked)) void switch_sp_to_psp(void){

	/*Preserve main return address*/
	__asm volatile ("PUSH {LR}");

	//1. Initialize PSP with TASK1_START
	__asm volatile ("BL get_psp_value"); 	/*current task address will be stored in R0 (AAPCS)*/
	__asm volatile ("MSR PSP,R0");			/*PSP has the current task value*/

	/*LR has the main return address again*/
	__asm volatile ("POP {LR}");

	//2. Change SP to PSP in CONTROL register
	__asm volatile ("MOV R0,#0x02");
	__asm volatile ("MSR CONTROL,R0");		/*SPEL is 1 to switch SP to PSP*/

	/*Return to main*/
	__asm volatile ("BX LR");

}

__attribute__((naked)) void init_schedular_stack(uint32_t sched_TopOfStack)
{
	__asm volatile ("MSR MSP,%0" : :"r"(sched_TopOfStack): );
	__asm volatile ("BX LR"); //return to main
}


void init_systick_timer(uint32_t tick_hz)

{
	uint32_t count_value = (SYSTEM_CLK / tick_hz) - 1U;
	SYST_RVR &= ~(0x00FFFFFFU);

	//reload value
	SYST_RVR = count_value ;


	//do some settings
	SYST_CSR |= (1U << 1 | 1U << 2); // Enables SysTick exception request & Indicates the clock source

	//enable
	SYST_CSR |= 1U ;
}

void init_tasks_stack(void)
{

	user_tasks[0].current_state = TASK_READY_STATE;
	user_tasks[1].current_state = TASK_READY_STATE;
	user_tasks[2].current_state = TASK_READY_STATE;
	user_tasks[3].current_state = TASK_READY_STATE;

	user_tasks[0].psp_value = T1_STACK_START;
	user_tasks[1].psp_value = T2_STACK_START;
	user_tasks[2].psp_value = T3_STACK_START;
	user_tasks[3].psp_value = T4_STACK_START;

	user_tasks[0].task_handler = task1_handler;
	user_tasks[1].task_handler = task2_handler;
	user_tasks[2].task_handler = task3_handler;
	user_tasks[3].task_handler = task4_handler;


	uint32_t *pPSP;
	for(uint32_t i = 0 ; i < MAX_TASKS; i++)
	{
		pPSP = (uint32_t *) user_tasks[i].psp_value;

		/*FULL DESCENDING STACK : decrease the pointer first then store the value*/

		*(--pPSP) = DUMMY_XPSR; 		//0x0100 0000 (THUMB state bit is set)
		*(--pPSP) = (uint32_t) user_tasks[i].task_handler;	//Address of the function
		*(--pPSP) = 0xFFFFFFFD;			//EXC_RETURN VALUE (THREAD mode and PSP is used after return)
		*(--pPSP) =	0; 					//R12
		*(--pPSP) =	0; 					//R3
		*(--pPSP) =	0; 					//R2
		*(--pPSP) =	0; 					//R1
		*(--pPSP) =	0; 					//R0
/********************************************************************************************************/
		*(--pPSP) =	0; 					//R11
		*(--pPSP) =	0; 					//R10
		*(--pPSP) =	0; 					//R9
		*(--pPSP) =	0; 					//R8
		*(--pPSP) =	0; 					//R7
		*(--pPSP) =	0; 					//R6
		*(--pPSP) =	0; 					//R5
		*(--pPSP) =	0; 					//R4
/********************************************************************************************************/
		user_tasks[i].psp_value = (uint32_t) pPSP;  //Preserve the PSP final value
	}
}


void save_psp_value (uint32_t current_psp_value)
{
	user_tasks[current_task].psp_value = current_psp_value;
}

void update_next_task(void)
{
	++current_task;
	current_task = current_task % MAX_TASKS;
}

/*context_switch*/
__attribute__((naked))void SysTick_Handler(void)
{

	/*save the context of the current task*/

	//1. get the PSP of the current running thread
	__asm volatile("MRS R0,PSP");
	//2. store the content from R4 to R11 on the current task private stack memory
	__asm volatile ("STMDB R0!,{R4-R11}");

	/*****SAVE LR BEFOR USING BL********/
	__asm volatile("PUSH {LR}");

	//3. update the stack pointer to the current value
	__asm volatile("BL save_psp_value");

	/*retrieve the context of the next task task*/

	//1. decide the next task to run
	__asm volatile("BL update_next_task");
	//2. get its past PSP value
	__asm volatile ("BL get_psp_value");
	//3. using its PSP retrieve from R4 to R11 from its private stack
	__asm volatile ("LDMIA R0!,{R4-R11}");
	//4. update PSP then exit (exit will retrieve the rest of the stack frame)
	__asm volatile ("MSR PSP,R0");

	/*****RETRIEVE LR AFTER USING BL AND RETURN MANUALLY (because it is a naked function)********/
	__asm volatile ("POP {LR}");
	__asm volatile ("BX LR");
}

/*Fault Handlers*/
void HardFault_Handler(void) {
	while(1);
}

void MemManage_Handler(void) {
	while(1);
}

void BusFault_Handler(void) {
	while(1);
}
void UsageFault_Handler(void){
	while(1);
}


