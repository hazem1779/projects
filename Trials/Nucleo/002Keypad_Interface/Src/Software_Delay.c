#include <stdint.h>

void delay(uint64_t ticks);

void delay(uint64_t ticks)
{
	for (; ticks != 0; --ticks)
	{
		;
	}
}
