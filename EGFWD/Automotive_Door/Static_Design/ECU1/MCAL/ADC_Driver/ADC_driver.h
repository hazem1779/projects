#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

typedef enum{
    OFF,
    ON
}status;

/******************ADC APIs**************************/
void ADC_Init(ADC_handle_t *pADC_handle);
void ADC_DeInit(ADC_TypeDef *pADCx);

status ADC_Start_Convert();


#endif