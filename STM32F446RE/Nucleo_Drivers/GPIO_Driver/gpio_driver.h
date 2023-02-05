#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "stm32f446xx.h"

/*******************MODES AND STATUS MACROS******************************/
#define ENABLE 			1U
#define DISABLE 		0U
#define SET 			ENABLE
#define RESET 			DISABLE

/*
	@GPIO_PIN_NUMBER	
	Pin numbers Macros
*/

#define GPIO_PIN_NO_0 		0
#define GPIO_PIN_NO_1 		1
#define GPIO_PIN_NO_2 		2
#define GPIO_PIN_NO_3 		3
#define GPIO_PIN_NO_4 		4
#define GPIO_PIN_NO_5 		5
#define GPIO_PIN_NO_6 		6
#define GPIO_PIN_NO_7 		7
#define GPIO_PIN_NO_8 		8
#define GPIO_PIN_NO_9 		9
#define GPIO_PIN_NO_10 		10
#define GPIO_PIN_NO_11 		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13 		13
#define GPIO_PIN_NO_14 		14
#define GPIO_PIN_NO_15 		15


/*
	@GPIO_PIN_MODE
	Pin Different Modes
*/

#define GPIO_MODE_IN  			0
#define GPIO_MODE_OUT 			1
#define GPIO_MODE_ALTFUN  		2
#define GPIO_MODE_ANG  			3
#define RISING_EDGE  			4
#define FALLING_EDGE  			5
#define RISING_FALLING			6

/*
	@GPIO_SPEED
	Pin different Speed
*/
#define LOW_SPEED 						0
#define MEDIUM_SPEED 					1
#define HIGH_SPEED 						2
#define VERY_HIGH_SPEED 				3


/*
	@GPIO_PUPD
	PULL-UP or PULL-DOWN resistor
*/

#define NO_PUPD			0
#define	PULL_UP			1
#define	PULL_DOWN		2


/*
	@GPIO_Output_Modes
	Output Modes
*/

#define PUSH_PULL	0
#define OPEN_DRAIN	1


/*
*	@GPIO_ALT
	Alternate Functionality
*/
#define	AF0			0 
#define	AF1			1 
#define	AF2			2 
#define	AF3			3 
#define	AF4			4 
#define	AF5			5 
#define	AF6			6	 
#define	AF7			7	 
#define	AF8			8	 
#define	AF9			9
#define	AF10		10 
#define	AF11		11 
#define	AF12		12 
#define	AF13		13
#define	AF14		14
#define	AF15		15 

/**************************************************/
#define GPIOX_TO_CODE(x)   ((x == GPIOA) ? 0 :\
							(x == GPIOB) ? 1 :\
							(x == GPIOC) ? 2 :\
							(x == GPIOD) ? 3 :\
							(x == GPIOE) ? 4 :\
							(x == GPIOF) ? 5 :\
							(x == GPIOG) ? 6 :\
							(x == GPIOH) ? 7 :0)
							




/*******************SYSTEM CONFIG CONTROLLER CLOCK ENABLE & DISABLE******************************/
#define SYSCFG_PCLK_EN()  (RCC->APB2ENR |=  (1U << 14))
#define SYSCFG_PCLK_DIS() (RCC->APB2ENR &= ~(1U << 14))

/*******************GPIO PORT CLOCK ENABLE MACROS******************************/

#define GPIOA_PCLK_EN() (RCC->AHB1ENR |= (1U <<0))
#define GPIOB_PCLK_EN() (RCC->AHB1ENR |= (1U <<1))
#define GPIOC_PCLK_EN() (RCC->AHB1ENR |= (1U <<2))
#define GPIOD_PCLK_EN() (RCC->AHB1ENR |= (1U <<3))
#define GPIOE_PCLK_EN() (RCC->AHB1ENR |= (1U <<4))
#define GPIOF_PCLK_EN() (RCC->AHB1ENR |= (1U <<5))
#define GPIOG_PCLK_EN() (RCC->AHB1ENR |= (1U <<6))
#define GPIOH_PCLK_EN() (RCC->AHB1ENR |= (1U <<7))

/*******************GPIO PORT CLOCK DISABLE MACROS******************************/
#define GPIOA_PCLK_DIS() (RCC->AHB1ENR &= ~(1U <<0))
#define GPIOB_PCLK_DIS() (RCC->AHB1ENR &= ~(1U <<1))
#define GPIOC_PCLK_DIS() (RCC->AHB1ENR &= ~(1U <<2))
#define GPIOD_PCLK_DIS() (RCC->AHB1ENR &= ~(1U <<3))
#define GPIOE_PCLK_DIS() (RCC->AHB1ENR &= ~(1U <<4))
#define GPIOF_PCLK_DIS() (RCC->AHB1ENR &= ~(1U <<5))
#define GPIOG_PCLK_DIS() (RCC->AHB1ENR &= ~(1U <<6))
#define GPIOH_PCLK_DIS() (RCC->AHB1ENR &= ~(1U <<7))


/*******************GPIO PORT RESET MACROS******************************/
#define GPIOA_RESET() 	do {RCC->AHB1RSTR |= (1U <<0); RCC->AHB1RSTR &= ~(1U <<0);}while(0)
#define GPIOB_RESET() 	do {RCC->AHB1RSTR |= (1U <<1); RCC->AHB1RSTR &= ~(1U <<0);}while(1)
#define GPIOC_RESET() 	do {RCC->AHB1RSTR |= (1U <<2); RCC->AHB1RSTR &= ~(1U <<0);}while(2)
#define GPIOD_RESET() 	do {RCC->AHB1RSTR |= (1U <<3); RCC->AHB1RSTR &= ~(1U <<0);}while(3)
#define GPIOE_RESET() 	do {RCC->AHB1RSTR |= (1U <<4); RCC->AHB1RSTR &= ~(1U <<0);}while(4)
#define GPIOF_RESET() 	do {RCC->AHB1RSTR |= (1U <<5); RCC->AHB1RSTR &= ~(1U <<0);}while(5)
#define GPIOG_RESET() 	do {RCC->AHB1RSTR |= (1U <<6); RCC->AHB1RSTR &= ~(1U <<0);}while(6)
#define GPIOH_RESET() 	do {RCC->AHB1RSTR |= (1U <<7); RCC->AHB1RSTR &= ~(1U <<0);}while(7)

 

/******************GPIO pin configuration structure**************************/
typedef struct
{
	uint32_t pin_Num;				/*<refer to section @GPIO_PIN_NUMBER>*/
	uint32_t pin_Mode;				/*<refer to section @GPIO_PIN_MODE>*/
	uint32_t pin_Speed;				/*<refer to section @GPIO_SPEED>*/	
	uint32_t pin_PUPD;				/*<refer to section @GPIO_PUPD>*/
	uint32_t pin_OutputMode;			/*<refer to section @GPIO_Output_Modes>*/	
	uint32_t pin_AltFun;				/*<refer to section @GPIO_ALT>*/
	
}GPIO_PIN_CONFIG_t;

/***********************GPIO Handle structure*******************************/

typedef struct
{
	GPIO_TypeDef *pGPIOx; 				//Pointer to the port x address
	GPIO_PIN_CONFIG_t gpio_pin_config;  //pin coniguration structure

}GPIO_handle_t;
/*****************************************************************************
* 					APIs supported by this driver
*****************************************************************************/

/*  1- GPIOx clock control */
void GPIO_CLK_CTRL(GPIO_TypeDef *pGPIOx, uint8_t status);


/*  2- GPIOx init and de-init */
void GPIO_Init(GPIO_handle_t *pGPIO_handle);
void GPIO_DeInit(GPIO_TypeDef *pGPIOx);

/*  3- Data Read and Write */
uint8_t GPIO_PinRead(GPIO_TypeDef *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_PortRead(GPIO_TypeDef *pGPIOx);

void GPIO_PinWrite(GPIO_TypeDef *pGPIOx, uint8_t PinNumber, uint8_t data);
void GPIO_PinToggle(GPIO_TypeDef *pGPIOx, uint8_t PinNumber);
void GPIO_PortWrite(GPIO_TypeDef *pGPIOx, uint16_t data);


/*  4- IRQ configuration and ISR handling*/
void GPIO_IRQConfig(IRQn_Type IRQNumber, uint8_t status);
void GPIO_IRQ_Handler(uint8_t PinNumber);
void GPIO_IRQSetPriority(IRQn_Type IRQNumber, uint8_t IRQPrio);





#endif //GPIO_DRIVER_H
