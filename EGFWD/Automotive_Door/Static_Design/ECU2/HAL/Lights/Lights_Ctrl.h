#ifndef LIGHTS_CTRL_H
#define LIGHTS_CTRL_H

/**
*@brief Lights State
**/
typedef enum
{
    Lights_OFF,
    Lights_ON
}Light_status;

/**
*@brief Lights APIs
**/

void Light_init(void);
void Light_Deinit(void);

Light_status Get_Light_status(void);
void Set_Light(void);
void Reset_Light(void);
#endif