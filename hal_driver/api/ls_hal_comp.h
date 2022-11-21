#ifndef LS_HAL_COMP_H_
#define LS_HAL_COMP_H_
#include <stdint.h>
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
  EDGE_RISING = 0x1,
  EDGE_FALLING = 0x2,
  EDGE_BOTH = (EDGE_FALLING | EDGE_RISING),
};

typedef struct
{
  uint32_t
      comp_en : 1,
      clk_mode : 3,
      hysteresis : 2,
      vrefctl : 2,
      vrefsel : 3,
      input : 2,
      reserved1 : 3,
      flt_prd : 2,
      flt_byp : 1,
      risingintr_en : 1,
      fallingintr_en : 1,
      reserved2 : 11;
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
 * @brief LSCOMP start
 *
 * @param  hcomp Pointer to a COMP_HandleTypeDef structure that contains
 *               the configuration information for the specified COMP module.int_t
 * @param param[in] Pointer to a COMP_Param structure
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef HAL_COMP_Start(COMP_HandleTypeDef *hcomp, COMP_Param *param);

/**
  * @brief Rising/falling edge interrupt callbacks.
  *
  * @note  This function needs to be implemented when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file
 * @param  hcomp Pointer to a COMP_HandleTypeDef structure that contains
  *               the configuration information for the specified COMP module.int_t
  * @param  edge enum comp_intr_edge, rising/falling/both
  */
void HAL_COMP_Callback(COMP_HandleTypeDef *hcomp, enum comp_intr_edge edge);

/**
 * @brief  This function handles COMP interrupt request.
 *
 * @param  hcomp Pointer to a COMP_HandleTypeDef structure that contains
 *               the configuration information for the specified COMP module.int_t
 * @param  edge enum comp_intr_edge, rising/falling/both
 */
void HAL_COMP_IRQHandler(COMP_HandleTypeDef *hcomp, enum comp_intr_edge edge);

#endif
