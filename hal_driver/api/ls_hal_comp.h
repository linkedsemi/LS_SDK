#ifndef LS_HAL_COMP_H_
#define LS_HAL_COMP_H_
#include <stdint.h>
#include <stdbool.h>
#include "HAL_def.h"
#include "ls_msp_comp.h"

enum SpeedMode
{
  LowSpeed = 1,
  MediumSpeed = 2,
  HighSpeed = 4,
};

enum comp_intr_edge
{
  COMP_EDGE_RISING = 0x1,
  COMP_EDGE_FALLING = 0x2,
  COMP_EDGE_BOTH = (COMP_EDGE_FALLING | COMP_EDGE_RISING),
};

typedef struct
{
  uint32_t
      comp_en : 1,        // COMP enable
      clk_mode : 3,       // COMP speed mode
      hysteresis : 2,     // COMP hysteresis select
      vrefctl : 2,        // COMP internal reference voltage select
      vrefsel : 3,        // COMP reference source select
      input : 2,          // COMP input select
      reserved1 : 3,      // reserved 3 bit
      flt_prd : 2,        // the filter period in MSI clock
      flt_byp : 1,        // filter bypass
      risingintr_en : 1,  // interrupt enable for the rising edge interrupt
      fallingintr_en : 1, // interrupt enable for the falling edge interrupt
      reserved2 : 11;     // reserved 11 bit
} COMP_Param;

typedef struct __COMP_HandleTypeDef
{
  reg_comp_t *COMP;
} COMP_HandleTypeDef;

/**
 * @brief LSCOMP Initialize
 *
 * @param  hcomp Pointer to a COMP_HandleTypeDef structure that contains
 *               the configuration information for the specified COMP module.int_t
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef HAL_COMP_Init(COMP_HandleTypeDef *hcomp);

/**
 * @brief LSCOMP DeInitialize
 *
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef HAL_COMP_DeInit(void);

/**
 * @brief LSCOMP Config
 *
 * @param  hcomp Pointer to a COMP_HandleTypeDef structure that contains
 *               the configuration information for the specified COMP module.int_t
 * @param param[in] Pointer to a COMP_Param structure
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef HAL_COMP_Config(COMP_HandleTypeDef *hcomp, COMP_Param *param);

/**
 * @brief LSCOMP start
 *
 * @param  hcomp Pointer to a COMP_HandleTypeDef structure that contains
 *               the configuration information for the specified COMP module.int_t
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef HAL_COMP_Start(COMP_HandleTypeDef *hcomp);

/**
 * @brief LSCOMP stop
 *
 * @param  hcomp Pointer to a COMP_HandleTypeDef structure that contains
 *               the configuration information for the specified COMP module.int_t
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef HAL_COMP_Stop(COMP_HandleTypeDef *hcomp);

/**
  * @brief Rising/falling edge interrupt callbacks.
  *
  * @note  This function needs to be implemented when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file
 * @param  hcomp Pointer to a COMP_HandleTypeDef structure that contains
  *               the configuration information for the specified COMP module.int_t
  * @param  edge enum comp_intr_edge, rising/falling/both
  */
void HAL_COMP_Callback(COMP_HandleTypeDef *hcomp, enum comp_intr_edge edge, bool status);

/**
 * @brief  This function handles COMP interrupt request.
 *
 * @param  hcomp Pointer to a COMP_HandleTypeDef structure that contains
 *               the configuration information for the specified COMP module.int_t
 * @param  edge enum comp_intr_edge, rising/falling/both
 */
void HAL_COMP_IRQHandler(COMP_HandleTypeDef *hcomp, enum comp_intr_edge edge, bool status);

#endif
