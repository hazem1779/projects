;Objective: Turn on the light by pressing the button
;Unlock the entire PORTF 
;ADD 3 more registers with 1 lock-key
;Switch is active low so we need to use a pull-up resistor register 
;Unlock register for GPIO and add the lock key
;Commit register to PORTF

;switch1 => pf4 input
;switch2 => pf0 input
;RED_LED => pf1 output 
;BLUE_LED => pf2 output

SYSCTL_RCGCGPIO_R 	EQU		0x400FE608
GPIO_PORtF_DIR_R  	EQU 	0x40025400
GPIO_PORtF_DEN_R	EQU		0x4002551C
GPIO_PORtF_DATA_R	EQU		0x400253FC

GPIO_PORtF_PUR_R  	EQU 	0x40025510
GPIO_PORtF_LOCK_R  	EQU 	0x40025520
GPIO_PORtF_CR_R  	EQU 	0x40025524

GPIO_LOCK_KEY  		EQU 	0x4C4F434B
	
RED  EQU 0x02 ; red led is connected to pf1 0000 0010
BLUE EQU 0x04 ; blue led is connected to pf2 0000 0100
GREEN EQU 0x08 ; blue led is connected to pf2 0000 1000
	
SEC_DIV_FIVE EQU 1066666 ; fifth of a seconf based on the microcontroller frequency 16 migahertz


				AREA |.text|,CODE,READONLY,ALIGN=2
				THUMB
				EXPORT Main

Main
		BL  GPIO_init
loop
		LDR R0,=SEC_DIV_FIVE 
		BL 	delay
		BL 	input
		
		CMP R0,#0x01 ;switch 1 is pressed => pf4=0 and pf0=1 
		BEQ red_on
		CMP R0,#0x10 ;switch 2 is pressed => pf4=1 and pf0=0 
		BEQ blue_on
		CMP R0,#0x00 ;both pressed
		BEQ green_on 
		
		BL  output	
		B 	loop
		
delay
		SUBS R0,R0,#0x01
		BNE  delay
		BX 	 LR
		
input
		LDR R1,=GPIO_PORtF_DATA_R
		LDR R0,[R1]
		AND R0,R0,#0x11 ;0b 0001 0001 it will return with which switch is pressed
		BX  LR

red_on
		MOV R0,#RED
		BL  output
		B 	loop
blue_on
		MOV R0,#BLUE
		BL  output
		B 	loop	
		
green_on
		MOV R0,#GREEN
		BL  output
		B 	loop		

output
		LDR R1,=GPIO_PORtF_DATA_R
		STR R0,[R1]
		BX LR

GPIO_init
		LDR R1,=SYSCTL_RCGCGPIO_R
		LDR R0,[R1]
		ORR R0,R0,#0x20
		STR R0,[R1]
		
		LDR R1,=GPIO_PORtF_LOCK_R
		LDR R0,=GPIO_LOCK_KEY
		STR R0,[R1]
		
		LDR R1,=GPIO_PORtF_CR_R
		MOV R0,#0xFF ;0b 1111 111
		STR R0,[R1]		

		LDR R1,=GPIO_PORtF_DIR_R
		MOV R0,#0x0E ;0b 0000 1110
		STR R0,[R1]
		
		LDR R1,=GPIO_PORtF_PUR_R
		MOV R0,#0x11 ;0b 0001 0001 =>SWITCH1 pull-up
		STR R0,[R1]
		
		LDR R1,=GPIO_PORtF_DEN_R
		MOV R0,#0x1F ;0b 0001 1111
		STR R0,[R1]

		BX  LR
		
		ALIGN 
		END	