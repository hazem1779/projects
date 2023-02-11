
#include <stdint.h>

#define SCB_SHCSR  *((uint32_t *)0xE000ED24)
#define SCB_CCR    *((uint32_t *)0xE000ED14)

#define USGFAULTENA (1U << 18)
#define BUSFAULTENA (1U << 17)
#define MEMFAULTENA (1U << 16)
#define DIV_0_TRP   (1U << 4)

int func_divide(int x, int y){
	return x/y;
}

int main(void)
{
/*--------configure all the exceptions----------------*/
	SCB_SHCSR |= (USGFAULTENA | BUSFAULTENA | MEMFAULTENA);
	SCB_CCR   |= (DIV_0_TRP);

#if 0
	// Execute an undefined instruction
	uint32_t *pSRAM = (uint32_t *) 0x20010000;
	*pSRAM = 0xFFFFFFFF;

	//create a function pointer
	void (*func_pointer) (void);

	func_pointer = (void *) 0x20010001;

	func_pointer();
#endif

#if 0
	// divide by zero
	func_divide(10,0);
#endif

	// try executing from peripheral region

	// executing SVC inside the SVC handler

	/*executing SVC instruction inside the interrupt handler
	with an interrupt with the same priority or lesser*/

}

//implement all the fault exception handlers

void HardFault_Handler(void) {
	while(1);
}

void MemManage_Handler(void) {
	while(1);
}

void BusFault_Handler(void) {
	while(1);
}

__attribute__ ((naked)) void UsageFault_Handler(void) {
	__asm ("MRS r0,MSP"); //to pass the MSP to r0
	__asm ("B UsageFault_Handler_c"); //to pass r0 as the function argument as per AAPCS
}
void UsageFault_Handler_c( uint32_t *pStackFrame){
	while(1);
}




