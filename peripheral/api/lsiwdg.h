#ifndef LSIWDG_H_
#define LSIWDG_H_
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "HAL_def.h"
#include "reg_lsiwdg_type.h"
#include "reg_base_addr.h"

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSIWDG
 *  @{
 */

#ifdef LSIWDG_BASE_ADDR
#define LSIWDG ((reg_iwdg_t *)LSIWDG_BASE_ADDR) /*!< LSIWDG Macro for Register Access*/
#endif

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

/** @}*/


/** @}*/

#endif 

