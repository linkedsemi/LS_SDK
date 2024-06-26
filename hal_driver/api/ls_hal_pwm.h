#ifndef LS_HAL_PWM_H_
#define LS_HAL_PWM_H_
#include "sdk_config.h"
#include <stdbool.h>
#include "HAL_def.h"
#include "reg_pwm_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PWM_POLARITY_NOINVERTED           0x00U // the output of current channel is not inverted
#define PWM_POLARITY_INVERTED             0x01U // the output of current channel is inverted
#define PWM_CMP_OUTVALUE_HIGH             0x00U
#define PWM_CMP_OUTVALUE_LOW              0x01U
#define PWM_MODE_ONLY_COUNTSUP            0x00U // the internal counter only counts up
#define PWM_MODE_COUNST_DOWN_AFTER_UP     0x01U // the internal counter counts down after counts up
#define PWM_CLK_PRE_DIV_1                 0x01U
#define PWM_CLK_PRE_DIV_2                 0x02U
#define PWM_CLK_PRE_DIV_4                 0x04U
#define PWM_CLK_PRE_DIV_8                 0x08U
#define PWM_CLK_PRE_DIV_16                0x10U
#define PWM_CLK_PRE_DIV_32                0x20U
#define PWM_CLK_PRE_DIV_64                0x40U
#define PWM_CLK_PRE_DIV_128               0x80U


typedef enum
{
  PWM_Channel1                            = 0x00U,
  PWM_Channel2                            = 0x01U,
  PWM_Channel3                            = 0x02U,
  PWM_Channel4                            = 0x03U,
  PWM_Channel5                            = 0x04U,
  PWM_Channel6                            = 0x05U,
  PWM_Channel7                            = 0x06U,
  PWM_Channel8                            = 0x07U,
} pwm_channel_t;

typedef struct
{
  uint16_t                                pwm_cyc;
  uint16_t                                pwm_high;
  uint16_t                                pwm_num;
  uint8_t                                 pol : 1,  // output polarity
                                          cmp : 1,  // the output value of current channel when the internal counter is equal to or bigger than the pwm_high
                                          mode : 1, // internal counter mode
                                          dma_en : 1; // dma enable
} PWM_Param;

/**
 * @brief  PWM handle Structure definition
 */

/**
 * @brief Initializes the PWM mode according to the specified parameters in
 *         the PWM_Param and create the associated handle.
 * @param  pwm_pre_div pwm frequency division coefficient
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_PWM_Init(uint8_t pwm_pre_div);

/**
 * @brief  HAL_PWM_DeInit
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_PWM_DeInit(void);

/**
 * @brief  HAL_PWM_DeInit
 * @param  channel pwm channel
 * @param  param Pointer to a PWM_Param structure that contains
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_PWM_SetConfig(pwm_channel_t channel, PWM_Param *param);

/**
 * @brief  HAL_PWM_START
 * @param  channel pwm channel
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_PWM_Start(pwm_channel_t channel);

/**
 * @brief  HAL_PWM_STOP
 * @param  param pwm channel
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_PWM_Stop(pwm_channel_t channel);

/**
 * @brief  HAL_PWM_START_Callback
 * NOTE: This function should not be modified, when the callback is needed,
 *         the HAL_PWM_START_Callback could be implemented in the user file
 */
void HAL_PWM_START_Callback(pwm_channel_t channel);

/**
 * @brief  HAL_PWM_END_Callback
 * NOTE: This function should not be modified, when the callback is needed,
 *         the HAL_PWM_END_Callback could be implemented in the user file
 */
void HAL_PWM_STOP_Callback(pwm_channel_t channel);

void HAL_PWM_IRQHandler(void);

#ifdef __cplusplus
}
#endif
#endif /* LS_HAL_PWM_H_ */


