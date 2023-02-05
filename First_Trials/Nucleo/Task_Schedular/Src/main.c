
#include <stdint.h>
#include <stdio.h>
#include "header.h"

int main(void)
{
	enable_processor_faults();

	init_schedular_stack(SCHED_STACK_START); 		//MSP for this stack

	init_tasks_stack(); 							//dummy stack frames

	init_systick_timer(TICK_HZ); 					//generate SysTick interrupt every 1ms

	switch_sp_to_psp();								//tasks must use PSP (until this code, MSP was used)

	task1_handler();

	for(;;);
}











