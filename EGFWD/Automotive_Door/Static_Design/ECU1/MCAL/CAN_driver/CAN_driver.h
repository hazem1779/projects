** @defgroup CAN_Exported_Types CAN Exported Types
  * @{
  */
/**
  * @brief  HAL State structures definition
  */
typedef enum
{
  HAL_CAN_STATE_RESET             = 0x00U,  /*!< CAN not yet initialized or disabled */
  HAL_CAN_STATE_READY             = 0x01U,  /*!< CAN initialized and ready for use   */
  HAL_CAN_STATE_LISTENING         = 0x02U,  /*!< CAN receive process is ongoing      */
  HAL_CAN_STATE_SLEEP_PENDING     = 0x03U,  /*!< CAN sleep request is pending        */
  HAL_CAN_STATE_SLEEP_ACTIVE      = 0x04U,  /*!< CAN sleep mode is active            */
  HAL_CAN_STATE_ERROR             = 0x05U   /*!< CAN error state                     */

} HAL_CAN_StateTypeDef;

**
  * @}
  */

/**
  * @brief  CAN handle Structure definition
  */
typedef struct __CAN_HandleTypeDef
{
  CAN_TypeDef                 *Instance;                 /*!< Register base address */

  CAN_InitTypeDef             Init;                      /*!< CAN required parameters */

  __IO HAL_CAN_StateTypeDef   State;                     /*!< CAN communication state */

  __IO uint32_t               ErrorCode;                 /*!< CAN Error code.
 This parameter can be a value of @ref CAN_Error_Code */
}




/** @defgroup CAN_InitStatus CAN InitStatus
  * @{
  */
#define CAN_INITSTATUS_FAILED       (0x00000000U)  /*!< CAN initialization failed */
#define CAN_INITSTATUS_SUCCESS      (0x00000001U)  /*!< CAN initialization OK     */
/**
  * @}
  */

/** @defgroup CAN_operating_mode CAN Operating Mode
  * @{
  */
#define CAN_MODE_NORMAL             (0x00000000U)                              /*!< Normal mode   */
#define CAN_MODE_LOOPBACK           ((uint32_t)CAN_BTR_LBKM)                   /*!< Loopback mode */
#define CAN_MODE_SILENT             ((uint32_t)CAN_BTR_SILM)                   /*!< Silent mode   */
#define CAN_MODE_SILENT_LOOPBACK    ((uint32_t)(CAN_BTR_LBKM | CAN_BTR_SILM))  /*!< Loopback combined with silent mode */

/* Initialization and de-initialization functions *****************************/
HAL_StatusTypeDef HAL_CAN_Init(CAN_HandleTypeDef *hcan);
HAL_StatusTypeDef HAL_CAN_DeInit(CAN_HandleTypeDef *hcan);

/* Control functions **********************************************************/
HAL_StatusTypeDef HAL_CAN_Start(CAN_HandleTypeDef *hcan);
HAL_StatusTypeDef HAL_CAN_Stop(CAN_HandleTypeDef *hcan);
HAL_StatusTypeDef HAL_CAN_AddTxMessage(CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *pHeader, uint8_t aData[], uint32_t *pTxMailbox);
HAL_StatusTypeDef HAL_CAN_GetRxMessage(CAN_HandleTypeDef *hcan, uint32_t RxFifo, CAN_RxHeaderTypeDef *pHeader, uint8_t aData[]);