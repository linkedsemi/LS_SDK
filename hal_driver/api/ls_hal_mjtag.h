#ifndef LS_HAL_MJTAG_H_
#define LS_HAL_MJTAG_H_
#include <stdbool.h>
#include "reg_mjtag_type.h"
#include "HAL_def.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    HAL_MJTAG_STATE_READY             = 0x0,
    HAL_MJTAG_STATE_BUSY              = 0x1,
} HAL_MJTAG_StateTypeDef;

typedef struct __MJTAG_Init_Param
{
    uint32_t tck_divider : 12;
    uint32_t : 4;
    uint32_t txd_cap_dly: 5;
    uint32_t :3;
    uint32_t rxd_cap_dly: 5;
    uint32_t :3;
} MJTAG_Init_Param;

typedef struct __MJTAG_Frame_Param
{
    uint32_t                *tdi;
    uint32_t                *tms;
    uint32_t                *tdo;
    uint32_t                *bitnum;
    uint32_t                count;
} MJTAG_Frame_Param;

typedef struct __MJTAG_HandleTypeDef
{
    reg_mjtag_t                 *MJtag;

    MJTAG_Frame_Param           Interuupt;

    uint32_t                    rx_count;

    HAL_MJTAG_StateTypeDef      state;

} MJTAG_HandleTypeDef;

void HAL_MJTAG_Init(MJTAG_HandleTypeDef *mjtag_h, MJTAG_Init_Param *init_param);

void HAL_MJTAG_DeInit(MJTAG_HandleTypeDef *mjtag_h);

void HAL_MJTAG_IRQHandler(MJTAG_HandleTypeDef *mjtag_h);

HAL_StatusTypeDef HAL_MJTAG_TransmitReceive_Polling(MJTAG_HandleTypeDef *mjtag_h, MJTAG_Frame_Param *param);

HAL_StatusTypeDef HAL_MJTAG_TransmitReceive_IT(MJTAG_HandleTypeDef *mjtag_h, MJTAG_Frame_Param *param);

void HAL_MJTAG_TransmitReceive_CallBack(void);

#ifdef __cplusplus
}
#endif
#endif