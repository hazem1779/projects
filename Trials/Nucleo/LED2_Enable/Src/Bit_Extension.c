#include <stdio.h>
#include <stdint.h>

uint64_t bit_extend(uint64_t number, uint8_t start, uint8_t end );

uint64_t bit_extend(uint64_t number, uint8_t start, uint8_t end )
{
	if((start < 0) | (end > 63) | (start > end))
	{
		return 0;
	}
	else
	{
		uint8_t diff,sum;

		diff = (uint8_t) 63 - end;
		sum  = diff + start;

		number = number << diff;
		number = number >> sum;
		return number;
	}

}
