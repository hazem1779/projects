#include "TM4C123.h"                    // Device header
#include "SSI_Simple_Dr.h"

void GPIOD_init(void){
/*-------------------enable clock--------------------------------------------------*/
	
	SYSCTL->RCGCGPIO |=	 PORT_D;  //clock enabled	
	SYSCTL->RCGCGPIO |=	 PORT_F; //imaginary slave port
	
/*-------------------setting GPIOD pins as alternate functions--------------------------------------------------*/	
	
	GPIOD->AMSEL &= ~0x09; //disable analog signal (in case of enabled previously)
	GPIOD->DEN |= 0x09;    //enable digital pins(0 and 3) 0b0000 1001
	GPIOD->AFSEL |= 0x09;  //alterante fuctions for pins (0 and 3)
	GPIOD->PCTL &= ~0x0000F00FU;   //clearing alternate fuction to ssi1
	GPIOD->PCTL |=  0x00002002U;   //assigning SSI1 to alternate function
	
/*-------------------Imaginary slave in PORTF pin 2--------------------------------------------------*/
	
	GPIOF->DIR  |=0x04;          //select pf2 as output pin (imaginary slave)
	GPIOF->DEN  |=0x04;		   //pf2 digital enable
	GPIOF->DATA |=0x04;    		
	
}

void SSI1_init(void){
	
	SYSCTL->RCGCSSI |= SSI_1;
	SSI1->CR1  = 0x00;  // disable SSI1 before making any configuration
	SSI1->CC   = 0x00;  // System Clock is used
	SSI1->CPSR = 4U;    //CPSDVSR = 4 
	SSI1->CR0  = 0x0F;  //16-bit mode, SPI mode, CPOL=0, CPHASE=0, SCR=0 (0b 0 0 0 00 1111)
	SSI1->CR1  = 0x02;  // 0b 0000 0010 enable SSI and Master mode
	
}

void SSI_WRITE(unsigned char data){
	
	GPIOF->DATA &= ~(0x04U); //set the slave pin as low
	while((SSI1->SR & (1U << 1))== 0){} //wait until fifo is not full
	SSI1->DR = data;
	while((SSI1->SR & (1U << 4))!= 0)   //wait until transmission is done
	GPIOF->DATA |= 0x04;	

}
