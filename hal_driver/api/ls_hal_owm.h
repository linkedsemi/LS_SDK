#ifndef LS_HAL_OWM_H_
#define LS_HAL_OWM_H_
#include <stdbool.h>
#include "HAL_def.h"
#include "ls_msp_owm.h"

#define     RST_DAT_LEN             0x0             /* The configuration during reset. (RST_DAT_LEN)+1 indicates the total bit number of the current owm transfer. units: bit */

#define     RST_WRITE_BIT_CYC       0x202           /* The configuration during reset. (RST_WRITE_BIT_CYC+1) indicates the timing period for one bit of the owm transfer in write mode. units: us*/

#define     RST_WRITE_SMP_IDX       0x225           /* The configuration during reset. (RST_WRITE_SMP_IDX+1) indicates the timing period from the falling edge of each bit to the sample point of each bit in write mode.units: us*/

#define     RST_READ_BIT_CYC        0x1bc           /* The configuration during reset. (RST_READ_BIT_CYC+1) indicates the timing period for one bit of the owm transfer in read mode. units: us */

#define     RST_READ_SMP_IDX        0xE             /* The configuration during reset. (RST_READ_SMP_IDX+1) indicates the timing period from the falling edge of each bit to the sample point of each bit in read mode. units: us */

#define     RST_TGL0_IDX            0x1DF           /* the configuration during reset. (RST_TGL0_IDX+1) the low pulse timing period of bit "0" of the owm transfer.units: us */

#define     BIT_CYC                 0x45            /* 0~0x3ff,clk_period\*(BIT_CYC+1)*(pre_div+1) indicates the timing period for one bit of the owm transfer. units: us */

#define     SMP_IDX                 0xE             /* clk_period*(SMP_IDX+1)*(pre_div+1) indicates the timing period from the falling edge of each bit to the sample point of each bit.units: us */

#define     TGL0_IDX                0x3B            /* (TGL0_IDX+1) the low pulse timing period of bit "0" of the owm transfer. units: us*/

#define     TGL1_IDX                0x5             /* (TGL1_IDX+1) the low pulse timing period of bit "1" of the owm transfer. units: us*/

typedef enum
{
    HAL_OWM_WRITE,
    HAL_OWM_READ,
    HAL_OWM_RESET_WRITE,
    HAL_OWM_RESET_READ
}HAL_OWM_StateTypeDef;

typedef struct __OWM_HandleTypeDef
{
    reg_owm_t       *Instance;      /* !< owm Register base address */
    uint8_t         *pBuffPtr;      /*!< Pointer to UART Tx/Rx transfer Buffer */
    uint32_t        XferCount; 
    uint8_t         dat_len;         /* dat_len+1 indicates the total bit number of the current owm transfer */
    uint8_t         per_div;        /* 0~0xff,Set the clock frequency division coefficient */
    uint8_t         flt_num;        /* 0~0xf, Glitches narrower than clk_period*flt_num will be blocked by the internal input filter*/
    HAL_OWM_StateTypeDef  State;
    uint8_t         owm_ack;
}OWM_HandleTypeDef;


/* Initialization and de-initialization functions  **********************************/
void HAL_OWM_Init(OWM_HandleTypeDef* owm);
void HAL_OWM_DeInit(OWM_HandleTypeDef* owm);

/* Exported functions --------------------------------------------------------*/

/**
 * @brief Polling mode.Perform a 1-Wire reset. Returns 0 if a device responds with a presence pulse. Returns 1 if there is no device.
 *        A pull-up resistance is required for corresponding io.
 * @param owm: owm handle
 * @return uint8_t 
 */
uint8_t HAL_OneWireRst(OWM_HandleTypeDef *owm);

/**
 * @brief Interrupt mode.Perform a 1-Wire reset. Returns 0 if a device responds with a presence pulse. Returns 1 if there is no device.
 *        A pull-up resistance is required for corresponding io.
 * @param owm 
 */
void HAL_OneWireRst_IT(OWM_HandleTypeDef *owm);

/**
 * @brief Write multiple bytes in polling mode
 * @param numbytes The total number of bytes to write
 * @param dat Data to write
 * @param owm: owm handle
 */
void HAL_OWM_WriteData(OWM_HandleTypeDef *owm, uint8_t *pData, uint32_t numbytes);

/**
 * @brief read multiple bytes in  interrupt mode
 * @param numbytes the total number of bytes to read
 * @param owm: owm handle
 * @return uint32_t 
 */
void HAL_OWM_ReadData(OWM_HandleTypeDef *owm, uint8_t* pData,uint32_t numbytes);

/**
 * @brief Write multiple bytes in interrupt mode
 * @param numbytes The total number of bytes to write
 * @param dat Data to write
 * @param owm: owm handle
 */
void HAL_OWM_WriteData_IT(OWM_HandleTypeDef *owm, uint8_t *pData, uint32_t numbytes);

/**
 * @brief read multiple bytes in  interrupt mode
 * @param numbytes the total number of bytes to read
 * @param owm: owm handle
 */
void HAL_OWM_ReadData_IT(OWM_HandleTypeDef *owm, uint8_t* pData,uint32_t numbytes);


void HAL_LSOWM_RstComplete_Callback(OWM_HandleTypeDef* owm, uint8_t ack);
void HAL_LSOWM_TxComplete_Callback(OWM_HandleTypeDef* owm);
void HAL_LSOWM_RxComplete_Callback(OWM_HandleTypeDef* owm);
void HAL_LSOWM_IRQHandler(OWM_HandleTypeDef* owm);
#endif