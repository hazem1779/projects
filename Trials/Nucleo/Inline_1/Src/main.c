

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
#if 0
	__asm volatile ("LDR R1,=#0x20001000");
	__asm volatile ("LDR R2,=#0x20001004");
	__asm volatile ("LDR R0,[R1]");
	__asm volatile ("LDR R1,[R2]");
	__asm volatile ("ADD R0,R0,R1");
	__asm volatile ("STR R0,[R2]");
#endif

	int val = 100;
	__asm volatile ("MOV R0,%0": :"r"(val));

	int control_reg;
	__asm volatile ("MSR %0,CONTROL": "=r"(control_reg) : : );

	int val1,val2;
	val1=50;
	val2=1000;
	__asm volatile ("MOV %0,%1": "=r"(val1) : "r" (val2) : );

	int p1;
	int *p2;
	p2 = (int *) 0x2000002;
	__asm volatile ("LDR %0, [%1]": "=r" (p1) : "r" (p2) : ); //p1=*p2



	for(;;);
}
