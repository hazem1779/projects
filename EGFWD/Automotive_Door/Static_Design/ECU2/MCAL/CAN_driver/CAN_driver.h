#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H

#include "ECU1.h"
#include <stdint.h>


/******************CAN APIs**************************/
void CAN_Init(CAN_handle_t *pCAN_handle);
void CAN_DeInit(CAN_TypeDef *pCANx);

void CAN_Send();
void CAN_Send_IT();

uint16_t CAN_Receive();
uint16_t CAN_Receive_IT();
#endif