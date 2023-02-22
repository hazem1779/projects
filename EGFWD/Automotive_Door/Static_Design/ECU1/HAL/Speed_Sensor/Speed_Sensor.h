#ifndef SPEED_SENSOR_H
#define SPEED_SENSOR_H

/**
*@brief Speed Sensor status
**/
typedef enum
{
    Car_stopped,
    Car_moving
}Car_status;

/**
*@brief Speed Sensor APIs
**/

void Speed_init(void);
void Speed_Deinit(void);

Car_status Get_SpSensor_status(void);
#endif