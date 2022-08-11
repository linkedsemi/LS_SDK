#ifndef LS_HAL_PIS_H_
#define LS_HAL_PIS_H_
#include <stdbool.h>
#include "ls_msp_pis.h"
#include "HAL_def.h"

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSPIS
 *  @{
 */

/// PIS Sync Mode
enum pis_sync_mode
{
    PIS_SYNC_DIRECT,
    PIS_SYNC_SRC_LEVEL,
    PIS_SYNC_SRC_PULSE,
};

/// PIS Edge Select
enum pis_edge_sel
{
    PIS_EDGE_NONE,
    PIS_POS_EDGE,
    PIS_NEG_EDGE,
    PIS_BOTH_EDGES,
};

/** \brief LSPIS Initialize 
 *  \return status 
 */
HAL_StatusTypeDef HAL_PIS_Init(void);

/** \brief LSPIS De-Initialize 
 *  \return status 
 */
HAL_StatusTypeDef HAL_PIS_DeInit(void);

/** \brief LSPIS Channel Configuration
 *  \param channel 
 *  \param src enum pis_src in pis_config.h
 *  \param dst enum pis_dst in pis_config.h
 *  \param sync ::pis_sync_mode
 *  \param edge ::pis_edge_sel
 *  \return status 
 */
HAL_StatusTypeDef HAL_PIS_Config(uint8_t channel,enum pis_src src,enum pis_dst dst,enum pis_sync_mode sync,enum pis_edge_sel edge);

/** \brief LSPIS Channel Output Enable/Disable
 *  \param channel 
 *  \param enable
 *  \return status 
 */
HAL_StatusTypeDef HAL_PIS_Output(uint8_t channel,bool enable);


/** @}*/

/** @}*/

#endif
