#ifndef LS_HAL_CAP_H_
#define LS_HAL_CAP_H_
#include "sdk_config.h"
#include "stdbool.h"
#include "HAL_def.h"
#include "ls_msp_cap.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CAP_CHANNEL 8
#define LOW_HIGH 0
#define HIGH_LOW 1
typedef struct
{
  uint32_t  cap_low  : 16,
            cap_high : 16;
}cap_count_t;

/**
 * @brief Frequency formula
 * fre_div                                Frequency division coefficient, defined by the user
 * cap_low                                The value of CAP_COUNT structure member
 * cap_high                               The value of CAP_COUNT structure member
 */
#define  CAP_GET_FREQ(fre_div, cap_low, cap_high)             (((SDK_HCLK_MHZ*1000000)/((fre_div)+1))/((cap_low) + (cap_high)))



typedef enum 
{
    CAP_Channel1  = 0x00,
    CAP_Channel2  = 0x01,
    CAP_Channel3  = 0x02,
    CAP_Channel4  = 0x03,
    CAP_Channel5  = 0x04,
    CAP_Channel6  = 0x05,
    CAP_Channel7  = 0x06,
    CAP_Channel8  = 0x07,
}cap_channel_t;

typedef struct
{
  uint8_t  cap_pre_div;
}CAP_Param;

/**
 * @brief Initializes the CAP mode according to the specified parameters in
 *         the CAP_InitTypeDef and create the associated handle.
 * @param  cap_param Pointer to a CAP_Param structure that contains
 *              the configuration information for the specified CAP module.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_CAP_Init(CAP_Param *cap_param);

/**
 * @brief  HAL_CAP_DeInit
 * @param
 * @retval
 */
HAL_StatusTypeDef HAL_CAP_DeInit();


/**
 * @brief  polling mode and interrupt mode initialization
 * @param channel   1~8
 * @param cap_mode  Low + High or High + Low as a cycle
 * @param enable_it 0:polling mode; 1:interrupt mode
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_CAP_Start(uint8_t channel, uint8_t cap_mode, bool enable_it);

/**
 * @brief Close the selected channel
 * 
 * @param channel 1~8
 */
void HAL_CAP_Stop(uint8_t channel);

/**
 * @brief               Gets the value of the register
 * @param channel       1~8
 * @param cap_count     a pointer to cap_count_t
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_CAP_GetCount(uint8_t channel, cap_count_t *cap_count);

/**
 * @brief  Handles CAP interrupt request
 * @param 
 * @retval
 */
void HAL_LSCAP_IRQHandler();

void HAL_CAP_END_Callback(uint8_t channel, cap_count_t cap_count);
void HAL_CAP_ERR_HIGH_Callback(uint8_t channel);
void HAL_CAP_ERR_LOW_Callback(uint8_t channel);

#ifdef __cplusplus
}
#endif

#endif 

