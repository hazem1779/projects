#ifndef BUZZER_CTRL_H
#define BUZZER_CTRL_H

/**
*@brief Buzzer State
**/
typedef enum
{
    BUZZER_OFF,
    BUZZER_ON
}Buzzer_status;

/**
*@brief Buzzer APIs
**/

void Buzzer_init(void);
void Buzzer_Deinit(void);

Buzzer_status Get_Buzzer_status(void);
void Set_Buzzer(void);
void Reset_Buzzer(void);
#endif