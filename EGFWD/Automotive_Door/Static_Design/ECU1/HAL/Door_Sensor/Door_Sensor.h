#ifndef DOOR_SENSOR_H
#define DOOR_SENSOR_H

/**
*@brief Door status
**/
typedef enum
{
    Door_closed,
    Doo_opened
}Door_status;

/**
*@brief Door Sensor APIs
**/

void Door_init(void);
void Door_Deinit(void);

Door_status Get_Door_status(void);
#endif