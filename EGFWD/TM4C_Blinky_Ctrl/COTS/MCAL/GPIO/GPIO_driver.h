#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>

/*************************************************************************
**					TYPEDEF	VARIABLES & ENUMS							**
*************************************************************************/
typedef volatile uint32_t gpio_type;

typedef uint8_t Port_PinLevelValueType,Port_PinDirectionType,Port_ModeType;
typedef uint8_t Port_PinInternalAttachType,Port_PinOutputCurrentType,Port_ConfigType;


typedef uint8_t Dio_PortLevelType;

typedef enum
{
	PIN_0	= 0,
	PIN_1	= 1,
	PIN_2	= 2,
	PIN_3	= 3,
	PIN_4	= 4,
	PIN_5	= 5,
	PIN_6	= 6,
	PIN_7	= 7,
	PIN_8	= 8,
	PIN_9	= 9,
	PIN_10	= 10,
	PIN_11	= 11,
	PIN_12	= 12,
	PIN_13	= 13,
	PIN_14	= 14,
	PIN_15	= 15,
}Dio_ChannelType;



typedef enum
{
	LOW 	=0,
	HIGH	=1
}Dio_LevelType;

/*************************************************************************
**					TYPEDEF	STRUCTS										**
*************************************************************************/
typedef struct
{
	gpio_type DataBits[255];
	gpio_type DATA;
	gpio_type DIR;
	gpio_type IS;
	gpio_type IBE;
	gpio_type IEV;
	gpio_type IM;
	gpio_type RIS;
	gpio_type MIS;
	gpio_type ICR;
	gpio_type AFSEL;
	gpio_type Reserved[55];
	gpio_type DR2R;
	gpio_type DR4R;
	gpio_type DR8R;
	gpio_type ODR;
	gpio_type PUR;
	gpio_type PDR;
	gpio_type SLR;
	gpio_type DEN;
	gpio_type LOCK;
	gpio_type CR;
	gpio_type AMSEL;
	gpio_type PCTL;
	gpio_type DCCTL;
	gpio_type MACTL;
	gpio_type Reserved1[678];
	gpio_type PeriphID4;
	gpio_type PeriphID5;
	gpio_type PeriphID6;
	gpio_type PeriphID7;
	gpio_type PeriphID0;
	gpio_type PeriphID1;
	gpio_type PeriphID2;
	gpio_type PeriphID3;
	gpio_type CellID0;
	gpio_type CellID1;
	gpio_type CellID2;
	gpio_type CellID3;
}GPIO_Struct;

typedef struct
{
	GPIO_Struct * GPIOx;

	Port_ModeType			 	PortPinMode;
	Port_PinDirectionType 	 	PortPinDirection;
	Port_PinInternalAttachType	PortPinInternalAttach;
	Port_PinOutputCurrentType	PortPinOutputCurrent;
	
	Dio_ChannelType 			PortPinNum;		
	
}GPIO_Handle_Struct;

/*************************************************************************
**				GPIO_DRIVER RELATED DEFINITONS						**
*************************************************************************/
	
#define GPIOA_APB				((GPIO_Struct *)0x40004000)
#define GPIOB_APB				((GPIO_Struct *)0x40005000)
#define GPIOC_APB				((GPIO_Struct *)0x40006000)	
#define GPIOD_APB				((GPIO_Struct *)0x40007000)
#define GPIOE_APB				((GPIO_Struct *)0x40024000)	
#define GPIOF_APB				((GPIO_Struct *)0x40025000)
/*************************************************************************/
#if 1
#define GPIOA_AHB				((GPIO_Struct *)0x40058000)
#define GPIOB_AHB				((GPIO_Struct *)0x40059000)
#define GPIOC_AHB				((GPIO_Struct *)0x4005A000)
#define GPIOD_AHB				((GPIO_Struct *)0x4005B000)
#define GPIOE_AHB				((GPIO_Struct *)0x4005C000)
#define GPIOF_AHB				((GPIO_Struct *)0x4005D000)
#endif
/*************************************************************************/
#define set_bit(Reg,bit_pos)			(Reg |=  (1U << bit_pos))
#define clear_bit(Reg,bit_pos)			(Reg &= ~(1U << bit_pos))
#define toggle_bit(Reg,bit_pos)			(Reg ^=  (1U << bit_pos))
/*************************************************************************/
#define RCGCGPIO				*((volatile uint32_t *)0x400FE608)
#define GPIOA_Clock_Enable() (set_bit(RCGCGPIO,(0)))
#define GPIOB_Clock_Enable() (set_bit(RCGCGPIO,(1)))
#define GPIOC_Clock_Enable() (set_bit(RCGCGPIO,(2)))
#define GPIOD_Clock_Enable() (set_bit(RCGCGPIO,(3)))
#define GPIOE_Clock_Enable() (set_bit(RCGCGPIO,(4)))
#define GPIOF_Clock_Enable() (set_bit(RCGCGPIO,(5)))
/*************************************************************************/


/*************************************************************************
**						APIs PROTOTYPES									**
*************************************************************************/
void GPIO_Port_init(const GPIO_Handle_Struct *GPIOxHandle);
void GPIO_CLOCK_ENABLE(GPIO_Struct *GPIOx);
void BUTTON_COUNTER_ISR(void);
void Enable_Interrupts(uint8_t Pin);

#endif //GPIO_DRIVER_H

