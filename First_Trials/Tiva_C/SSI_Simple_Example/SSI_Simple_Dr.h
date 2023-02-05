#ifndef  __SSI_SIMPLE_DR__ 
#define  __SSI_SIMPLE_DR__ 


#define SSI_1 (1U << 1)
#define PORT_D (1U << 3)
#define PORT_F (1U << 5) //(imaginary) slave will be connected to port


void GPIOD_init(void);
void SSI1_init(void);
void SSI_WRITE(unsigned char data);

#endif //__SSI_SIMPLE_DR__ 