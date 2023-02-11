#ifndef DIO_DRIVER_H
#define DIO_DRIVER_H

#include "GPIO_driver.h"

/*************************************************************************
**				DIO_DRIVER RELATED DEFINITONS						**
*************************************************************************/

#define LOCK_KEY 	0x4C4F434B
#define PINS_USED		4

/**
@PortPinMode
**/
#define PORT_PIN_DEN		0 
#define PORT_PIN_ANLG		1
#define PORT_PIN_ALTFUN		2

/**
@PortPinDirection
**/
#define PORT_PIN_INPUT		0
#define	PORT_PIN_OUTPUT		1
#define	PORT_PIN_TIMER		2

/**
@PortPinInternalAttach
**/
#define PORT_PIN_NO_PUPD	0	
#define PORT_PIN_PUR		1
#define PORT_PIN_PUD		2


/**
@PortPinOutputCurrent
**/
#define PORT_PIN_2_mA		2
#define PORT_PIN_4_mA		4	
#define PORT_PIN_8_mA		8


/**
@PortPinLevelValue
**/
#define	PORT_PIN_LOW	0
#define	PORT_PIN_HIGH	1


/*************************************************************************
**						APIs PROTOTYPES									**
*************************************************************************/

uint8_t Dio_ReadChannel  (GPIO_Struct *GPIOx, uint8_t PortPinNum);

void    Dio_WriteChannel (GPIO_Struct *GPIOx, uint8_t PortPinNum, uint8_t level);

void 	Dio_FlipChannel  (GPIO_Struct *GPIOx, uint8_t PortPinNum);


uint16_t Dio_ReadPort(GPIO_Struct *GPIOx);
void Dio_WritePort(GPIO_Struct *GPIOx , uint16_t data);


#endif