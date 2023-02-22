#ifndef LIGHT_SWITCH_H
#define LIGHT_SWITCH_H

/**
*@brief Light switch  status
**/
typedef enum
{
    Switch_closed,
    Switch_opened
}Switch_status;

/**
*@brief Door Sensor APIs
**/

void Switch_init(void);
void Switch_Deinit(void);

Switch_status Get_Switch_status(void);
#endif