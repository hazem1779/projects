#include "TM4C123.h"                    // Device header
#include "SSI_Simple_Dr.h"

int main()
{
	GPIOD_init();
	SSI1_init();
	unsigned char i;
	while(1){
		for(i='A'; i <='Z'; i++){
			SSI_WRITE('i');	
		}	
	}
}
