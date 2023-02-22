typedef struct
{
  uint32_t ClockPrescaler;               /*!< Select ADC clock prescaler. The clock is common for 
                                              all the ADCs.
                                              This parameter can be a value of @ref ADC_ClockPrescaler */
  uint32_t Resolution;                   /*!< Configures the ADC resolution.
                                              This parameter can be a value of @ref ADC_Resolution */
  uint32_t DataAlign;                    /*!< Specifies ADC data alignment to right (MSB on register bit 11 and LSB on register bit 0) (default setting)
                                              or to left (if regular group: MSB on register bit 15 and LSB on register bit 4, if injected group (MSB kept as signed value due to potential negative value after offset application): MSB on register bit 14 and LSB on register bit 3).
                                              This parameter can be a value of @ref ADC_Data_align */
}ADC_InitTypeDef;

/** 
  * @brief  Structure definition of ADC channel for regular group   
  * @note   The setting of these parameters with function HAL_ADC_ConfigChannel() is conditioned to ADC state.
  *         ADC can be either disabled or enabled without conversion on going on regular group.
  */ 
typedef struct 
{
  uint32_t Channel;                /*!< Specifies the channel to configure into ADC regular group.
                                        This parameter can be a value of @ref ADC_channels */
  uint32_t Rank;                   /*!< Specifies the rank in the regular group sequencer.
                                        This parameter must be a number between Min_Data = 1 and Max_Data = 16 */
  uint32_t SamplingTime;           /*!< Sampling time value to be set for the selected channel.
                                        Unit: ADC clock cycles
                                        Conversion time is the addition of sampling time and processing time (12 ADC clock cycles at ADC resolution 12 bits, 11 cycles at 10 bits, 9 cycles at 8 bits, 7 cycles at 6 bits).
                                        This parameter can be a value of @ref ADC_sampling_times
                                        Caution: This parameter updates the parameter property of the channel, that can be used into regular and/or injected groups.
                                                 If this same channel has been previously configured in the other group (regular/injected), it will be updated to last setting.
                                        Note: In case of usage of internal measurement channels (VrefInt/Vbat/TempSensor),
                                              sampling time constraints must be respected (sampling time can be adjusted in function of ADC clock frequency and sampling time setting)
                                              Refer to device datasheet for timings values, parameters TS_vrefint, TS_temp (values rough order: 4us min). */
  uint32_t Offset;                 /*!< Reserved for future use, can be set to 0 */
}ADC_ChannelConfTypeDef;

/** 
  * @brief  HAL ADC state machine: ADC states definition (bitfields)
  */ 
/* States of ADC global scope */
#define HAL_ADC_STATE_RESET             0x00000000U    /*!< ADC not yet initialized or disabled */
#define HAL_ADC_STATE_READY             0x00000001U    /*!< ADC peripheral ready for use */
#define HAL_ADC_STATE_BUSY_INTERNAL     0x00000002U    /*!< ADC is busy to internal process (initialization, calibration) */
#define HAL_ADC_STATE_TIMEOUT           0x00000004U    /*!< TimeOut occurrence */



typedef struct

{
  ADC_TypeDef                   *Instance;                   /*!< Register base address */

  ADC_InitTypeDef               Init;                        /*!< ADC required parameters */

  HAL_LockTypeDef               Lock;                        /*!< ADC locking object */

  __IO uint32_t                 State;                       /*!< ADC communication state */

  __IO uint32_t                 ErrorCode;                   /*!< ADC Error code */
}ADC_HandleTypeDef;



/* Initialization/de-initialization functions ***********************************/
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef *hadc);
/* I/O operation functions ******************************************************/
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout);

HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout);

HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc);
