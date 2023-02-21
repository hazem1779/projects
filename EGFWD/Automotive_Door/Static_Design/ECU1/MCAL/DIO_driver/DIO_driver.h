#ifndef DIO_DRIVER_H
#define DIO_DRIVER_H

#include "ECU1.h"
#include <stdint.h>

#define ENABLE 			1U
#define DISABLE 		0U
#define SET 			ENABLE
#define RESET 			DISABLE


/******************DIO typedef enums and structs**************************/
typedef enum
{
    pin_0,
    pin_1,
    pin_2,
    pin_3,
    pin_4,
    pin_5,
    pin_6,
    pin_7,
}pins_t;


typedef struct
{
	pins_t pin_Num;				
	uint32_t pin_Mode;								
}DIO_PIN_CONFIG_t;


typedef struct
{
	DIO_TypeDef *DIOx; 				//Pointer to the port x address
	DIO_PIN_CONFIG_t gpio_pin_config;  //pin coniguration structure

}DIO_handle_t;


/******************DIO APIs**************************/
void DIO_Init(DIO_handle_t *pDIO_handle);
void DIO_DeInit(DIO_TypeDef *pDIOx);
uint8_t DIO_PinRead(DIO_TypeDef *pDIOx, pins_t PinNumber);
uint16_t DIO_PortRead(DIO_TypeDef *pDIOx);
void DIO_PinWrite(DIO_TypeDef *pDIOx, pins_t PinNumber, uint8_t data);
void DIO_PinToggle(DIO_TypeDef *pDIOx, pins_t PinNumber);
void DIO_PortWrite(GDIO_TypeDef *pDIOxx, uint16_t data);


#endif