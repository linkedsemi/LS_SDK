#ifndef LS_HAL_IWDG_H_
#define LS_HAL_IWDG_H_
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "HAL_def.h"
#include "ls_msp_iwdg.h"

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSIWDG
 *  @{
 */


/** \brief LSIWDG Initialize 
 *  \param[in]  LoadValue Counter load value.
 *  \return status
 */
HAL_StatusTypeDef HAL_IWDG_Init(uint32_t LoadValue);

/** \brief The watchdog counter reloads the value.
 * If the dog is not fed within the WDT timeout time, the WDT timeout behavior occurs.
 * \return status
 */
HAL_StatusTypeDef HAL_IWDG_Refresh(void);

/** \brief LSIWDG DeInitialize 
 *  \return status
 */
HAL_StatusTypeDef HAL_IWDG_DeInit(void);

/** @}*/


/** @}*/

#endif 

