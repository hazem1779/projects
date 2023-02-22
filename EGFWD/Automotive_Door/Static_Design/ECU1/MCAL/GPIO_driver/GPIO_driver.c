#include "DIO_driver.h"

void DIO_Init(DIO_handle_t *pDIO_handle)
{
    //Pin initialization Code
}
void DIO_DeInit(DIO_TypeDef *pDIOx)
{
    //Pin De-initialization Code
}
uint8_t DIO_PinRead(DIO_TypeDef *pDIOx, pins_t PinNumber)
{
    //API to read pin status
}
uint16_t DIO_PortRead(DIO_TypeDef *pDIOx)
{
    //API to read port status
}
void DIO_PinWrite(DIO_TypeDef *pDIOx, pins_t PinNumber, uint8_t data){
    //API to write data to a pin
}
void DIO_PinToggle(DIO_TypeDef *pDIOx, pins_t PinNumber){
    //API to toggle a pin
}
void DIO_PortWrite(GDIO_TypeDef *pDIOxx, uint16_t data)
{
    //API to write data to a port
}