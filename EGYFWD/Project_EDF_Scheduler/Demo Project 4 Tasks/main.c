/*
 * FreeRTOS Kernel V10.2.0
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/* 
	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used.
*/


/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the demo application tasks.
 * 
 * Main.c also creates a task called "Check".  This only executes every three 
 * seconds but has the highest priority so is guaranteed to get processor time.  
 * Its main function is to check that all the other tasks are still operational.
 * Each task (other than the "flash" tasks) maintains a unique count that is 
 * incremented each time the task successfully completes its function.  Should 
 * any error occur within such a task the count is permanently halted.  The 
 * check task inspects the count of each task to ensure it has changed since
 * the last time the check task executed.  If all the count variables have 
 * changed all the tasks are still executing error free, and the check task
 * toggles the onboard LED.  Should any task contain an error at any time 
 * the LED toggle rate will change from 3 seconds to 500ms.
 *
 */

/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "lpc21xx.h"

/* Peripheral includes. */
#include "serial.h"
#include "GPIO.h"


/*-----------------------------------------------------------*/

/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )


/*
 * Configure the processor for use with the Keil demo board.  This is very
 * minimal as most of the setup is managed by the settings in the project
 * file.
 */
static void prvSetupHardware( void );
/*-----------------------------------------------------------*/

TaskHandle_t Button_1_Handle 		= NULL;
TaskHandle_t Button_2_Handle	  = NULL;
TaskHandle_t Periodic_Transmiiter_Handle	= NULL;
TaskHandle_t UART_Reciever_Handle	= NULL;
TaskHandle_t Load_1_Simulation_Handle = NULL;
TaskHandle_t Load_2_Simulation_Handle = NULL;


int task1_InTime,task1_OutTime,task1_TotalTime = 0;
int task2_InTime,task2_OutTime,task2_TotalTime = 0;
int task3_InTime,task3_OutTime,task3_TotalTime = 0;
int task4_InTime,task4_OutTime,task4_TotalTime = 0;
int task5_InTime,task5_OutTime,task5_TotalTime = 0;
int task6_InTime,task6_OutTime,task6_TotalTime = 0;


int system_time = 0; 
float cpu_load = 0.0;
pinState_t	Button_1_State,Button_2_State = PIN_IS_LOW;
char *Button_1_Buffer_rising;
char *Button_2_Buffer_rising;

char *Button_1_Buffer_falling;
char *Button_2_Buffer_falling;

char *Periodic_Buffer;

int rised_1_flag,rised_2_flag = 0;
int falling_1_flag, falling_2_flag = 0;
int periodic_flag = 0;

int B1_check = 1;
int B2_check = 1;

/*Function to trace the tick*/
void vApplicationTickHook( void );
void vApplicationTickHook( void )
{
    /*Write your tracing feature here*/
	  GPIO_write(PORT_0, PIN0, PIN_IS_HIGH);
	  GPIO_write(PORT_0, PIN0, PIN_IS_LOW);
		
}

/*Function to trace the idle state*/
void vApplicationIdleHook( void );
void vApplicationIdleHook( void )
{
	  /*Write code here*/
	  GPIO_write(PORT_0, PIN7,  PIN_IS_HIGH);
	  GPIO_write(PORT_0, PIN7,  PIN_IS_LOW);
}


void Button_1_code( void * pvParameters )
{
   	TickType_t xLastWakeTime;
    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount(); 
	
	    /* This task is going to be represented by a voltage scale of 1. */
    vTaskSetApplicationTaskTag( NULL, ( void * ) 1 );
	 
	  for( ;; )
    {
			Button_1_State = GPIO_read(PORT_0, PIN1);
			
			if(Button_1_State == 1)
			{
				Button_1_Buffer_rising = "Button 1 detected Rising Edge\n";
				rised_1_flag++;
			}
			else if(Button_1_State == PIN_IS_LOW && rised_1_flag)
			{
				Button_1_Buffer_falling = "Button 1 detected Falling Edge\n";
				falling_1_flag++;
				rised_1_flag = 0;
			}
			vTaskDelayUntil( &xLastWakeTime, 50 );
    }
}
			//vTaskGetRunTimeStats(pcWriteBuffer);




void Button_2_code( void * pvParameters )
{
		TickType_t xLastWakeTime;
    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
	
	vTaskSetApplicationTaskTag( NULL, ( void * ) 2 );
    for( ;; )
    {
			Button_2_State = GPIO_read(PORT_0, PIN2);
			
			if(Button_2_State)
			{
				Button_2_Buffer_rising = "Button 2 detected Rising Edge\n";
				rised_2_flag++;
			}
			else if(Button_2_State != PIN_IS_HIGH && rised_2_flag )
			{
				Button_2_Buffer_falling = "Button 2 detected Falling Edge\n";
				falling_2_flag++;
				rised_2_flag = 0;
			}
			vTaskDelayUntil( &xLastWakeTime, 50 );
		}
}

void Periodic_Transmiiter( void * pvParameters )
{
		TickType_t xLastWakeTime;
    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
	
	vTaskSetApplicationTaskTag( NULL, ( void * ) 3 );
    for( ;; )
    {
			vTaskDelayUntil( &xLastWakeTime, 100 );
			Periodic_Buffer = "Periodic 100ms\n";
			periodic_flag = 1;
		}
}


void UART_Reciever( void * pvParameters )
{
			TickType_t xLastWakeTime;
    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
	
		vTaskSetApplicationTaskTag( NULL, ( void * ) 4 );
	
	
    for( ;; )
    {	
			//GPIO_write(PORT_0, PIN4, PIN_IS_HIGH); 		/*Indication*/	
	    //GPIO_write(PORT_0, PIN4, PIN_IS_LOW);			/*Indication*/
			if(rised_1_flag == 1 && B1_check)
			{
				vSerialPutString((const signed char *)Button_1_Buffer_rising, strlen(Button_1_Buffer_rising));	
				B1_check=0;			
			}
			if(falling_1_flag == 1)
			{
				vSerialPutString((const signed char *)Button_1_Buffer_falling, strlen(Button_1_Buffer_falling));
				falling_1_flag =0;
				B1_check=1;		
			}
			if(rised_2_flag == 1 && B2_check)
			{
				vSerialPutString((const signed char *)Button_2_Buffer_rising, strlen(Button_2_Buffer_rising));
				B2_check=0;		
			}
			if(falling_2_flag == 1)
			{
				vSerialPutString((const signed char *)Button_2_Buffer_falling, strlen(Button_2_Buffer_falling));
				falling_2_flag = 0;
				B2_check=1;	
			}
			if(periodic_flag == 1)
			{
				vSerialPutString((const signed char *)Periodic_Buffer, strlen(Periodic_Buffer));
				periodic_flag = 0;				
			}
			vTaskDelayUntil( &xLastWakeTime, 20);
		}
}



void Load_1_Simulation( void * pvParameters )
{
		int i;
		TickType_t xLastWakeTime;
    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
	
	vTaskSetApplicationTaskTag( NULL, ( void * ) 5 );
    for( ;; )
    {	
			for(i =0; i < 32895; i++)
			{
				i=i;				//executin time 5 ms
			}
			vTaskDelayUntil( &xLastWakeTime, 10);
		}
}

void Load_2_Simulation( void * pvParameters )
{
		int i;
		TickType_t xLastWakeTime;
    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
	
	vTaskSetApplicationTaskTag( NULL, ( void * ) 6 );
    for( ;; )
    {
			
			for(i =0; i < 78948; i++)
			{
				i=i;				//executin time 12 ms
			}
			vTaskDelayUntil( &xLastWakeTime, 100);
		}
}

/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */
int main( void )
{
	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();

	/* Create Tasks here */
	xTaskPeriodicCreate(
                    Button_1_code,       /* Function that implements the task. */
                    "Button_1_code",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    2,/* Priority at which the task is created. */
                    &Button_1_Handle,/* Used to pass out the created task's handle. */
										50);      /*Deadline*/ 
												
	xTaskPeriodicCreate(
                    Button_2_code,       /* Function that implements the task. */
                    "Button_2_code",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &Button_2_Handle, /* Used to pass out the created task's handle. */
										50);     		/*Deadline*/ 									
										
										
	xTaskPeriodicCreate(
                    Periodic_Transmiiter,       /* Function that implements the task. */
                    "Periodic_Transmiiter",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    3,/* Priority at which the task is created. */
                    &Periodic_Transmiiter_Handle,  /* Used to pass out the created task's handle. */
										100);  /*Deadline*/  	
										
										
	xTaskPeriodicCreate(
                    UART_Reciever,       /* Function that implements the task. */
                    "UART_Reciever",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &UART_Reciever_Handle, /* Used to pass out the created task's handle. */
										20);     		/*Deadline*/

	xTaskPeriodicCreate(
                    Load_1_Simulation,       /* Function that implements the task. */
                    "Load_1_Simulation",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    2,/* Priority at which the task is created. */
                    &Load_1_Simulation_Handle, /* Used to pass out the created task's handle. */
										10);     		/*Deadline*/ 	
										
	xTaskPeriodicCreate(
                    Load_2_Simulation,       /* Function that implements the task. */
                    "Load_2_Simulation",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &Load_2_Simulation_Handle, /* Used to pass out the created task's handle. */
										100);     		/*Deadline*/ 											
										
										

	/* Now all the tasks have been started - start the scheduler.

	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */
	vTaskStartScheduler();

	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
	for( ;; );
}
/*-----------------------------------------------------------*/

/* Function to reset timer 1 */
void timer1Reset(void)
{
	T1TCR |= 0x2;
	T1TCR &= ~0x2;
}

/* Function to initialize and start timer 1 */
 void configTimer1(void)
{
	T1PR = 1000;
	T1TCR |= 0x1;
}

static void prvSetupHardware( void )
{
	/* Perform the hardware setup required.  This is minimal as most of the
	setup is managed by the settings in the project file. */

	/* Configure UART */
	xSerialPortInitMinimal(mainCOM_TEST_BAUD_RATE);

	/* Configure GPIO */
	GPIO_init();
	
	/* Config trace timer 1 and read T1TC to get current tick */
	configTimer1();

	/* Setup the peripheral bus to be the same as the PLL output. */
	VPBDIV = mainBUS_CLK_FULL;
}
/*-----------------------------------------------------------*/


