#ifndef __DRIVER_H
#define __DRIVER_H

#include <stdint.h>


/*------------------GPIO pins defintions------------*/
#define ECHO    (1U << 6) //PORTB pin 6 (input)
#define TRIGGER (1U << 4) //PORTA pin 4 (output)
#define BLUE    (1U << 2)	//OnBoard blue LED (PORTF)

#define PORTA   (1U << 0)
#define PORTB   (1U << 1)
#define PORTF   (1U << 5)

/*------------------functions prototypes------------*/

void Timer0_init(void);
void delay_microseconds(uint32_t delay);
void Ports_init(void);
double Measure_Distance(void);

#endif //__DRIVER_H
