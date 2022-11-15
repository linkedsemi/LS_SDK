#ifndef LS_HAL_IWDG_H_
#define LS_HAL_IWDG_H_
#include <stdint.h>
#include <stdbool.h>
#include "HAL_def.h"
#include "ls_msp_wwdg.h"

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSWWDG
 *  @{
 */

enum no_feeding_win
{
    NO_FEEDING_WWDG_1_4 = 0,
    NO_FEEDING_WWDG_2_4,
    NO_FEEDING_WWDG_3_4,
    NO_FEEDING_WWDG_NONE,
};

/** \brief LSIWDG Initialize 
 *  \param[in]  LoadValue Counter load value.
 *  \return status
 */
HAL_StatusTypeDef HAL_WWDG_Init(uint32_t LoadValue,enum no_feeding_win win);

/** \brief The watchdog counter reloads the value.
 * If the dog is not fed within the WDT timeout time, the WDT timeout behavior occurs.
 * \return status
 */
HAL_StatusTypeDef HAL_WWDG_Refresh(void);


HAL_StatusTypeDef HAL_WWDG_Get_Count(uint8_t *window_cnt,uint32_t *value);


/** \brief LSIWDG DeInitialize 
 *  \return status
 */
HAL_StatusTypeDef HAL_WWDG_DeInit(void);

/** @}*/


/** @}*/

#endif 

