#ifndef LS_HAL_TOUCHKEY_H_
#define LS_HAL_TOUCHKEY_H_
#include <stdbool.h>
#include <stdint.h>
#include "HAL_def.h"

#define TOUCHKEY_VCTRL_1540mV 0x01U /* touchkey_cp_vctl:1.54V   */
#define TOUCHKEY_VCTRL_1670mV 0x02U /* touchkey_cp_vctl:1.67V   */
#define TOUCHKEY_VCTRL_1800mV 0x03U /* touchkey_cp_vctl:1.8V   */

typedef struct
{
    uint16_t clk_hprd;        // High pulse period of the output clock to the TK analog module in bus clock. hprd defines the timing period to charge the C~x~
    uint16_t clk_lprd;        // Low pulse period of the output clock to the TK analog module in bus clcok. lprd defines the timing period to charge the C~MOD~
    uint32_t scan_mtim;       // maximum times of charge sequence(charge C~x~ plus charge C~MOD~) to scan once per channel.
    uint16_t scan_channel_en; // Channel enable, each bit is for one channel, high active
    uint8_t scan_flt_prd;     // Filter period for the TK analog module output signal, the high pulse less than (0x7>>(0x3-flt_prd)) will be blocked.
    uint8_t scan_iter;        // scan_iter+1 is the number of scans of a single channel in a single scan process
    uint8_t scam_disch_prd;   // 2**(disch_prd+5) is the discharge period in the bus clock
    uint8_t touchkey_cp_vctl; // Touch Key charge pump voltage control: 0: 1.54V  1: 1.54V  2: 1.67V  3: 1.8V
} TOUCHKEY_PARAM;

/**
 * @brief LSTOUCHKEY Initialize
 *
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef HAL_TOUCHKEY_Init();

/**
 * @brief LSTOUCHKEY De-Initialize
 * 
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef HAL_TOUCHKEY_DeInit();

/**
 * @brief LSTOUCHKEY set up parameters
 *
 * @param param [inout]Structure TOUCHKEY_PARAM
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef HAL_TOUCHKEY_SetParam(TOUCHKEY_PARAM *param);

/**
 * @brief LSTOUCHKEY StartScan
 *
 * @param cntresult [OutPut] Scan result data
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef HAL_TOUCHKEY_StartScan(uint32_t cntresult[16]);

/**
 * @brief LSTOUCHKEY StartScan (Interrupt Mode)
 * @return HAL_StatusTypeDef
 */

HAL_StatusTypeDef HAL_TOUCHKEY_StartScan_IT();

/**
 * @brief Callback function that will be invoked in the interrupt context when the scan is complete.
 *        Overwrite this function to get notification of completion of scan is complete.
 * 
 * @param cntresult [OutPut] Scan result data
 */
void HAL_TOUCHKEY_END_Callback(uint32_t cntresult[16]);

/**
 * @brief Callback function that will be invoked in the interrupt context when an error is encountered during a scan.
 *        Overwrite this function to get notification of completion of scan is error.
 */
void HAL_TOUCHKEY_ERR_Callback();

void HAL_TOUCHKEY_IRQHandler();

#endif