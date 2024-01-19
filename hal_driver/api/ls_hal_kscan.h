#ifndef LS_HAL_KSCAN_H_
#define LS_HAL_KSCAN_H_
#include "reg_base_addr.h"
#include "sdk_config.h"
#include "HAL_def.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define COL_MAX               8
#define ROW_MAX               18

extern uint8_t kscan_matrix[ROW_MAX];

#define IDX_US(us)  (((SDK_PCLK_MHZ * (us)) / 64) - 1)
#define IDX_MS(ms)  (SDK_PCLK_MHZ * ((ms * 1000) / 64) - 1)

/**
  * itv new
  * us = (idx + 1) / (SDK_PCLK_MHZ / 64);
  * idx = SDK_PCLK_MHZ * (us / 64) - 1
  * 16M:  12us  ~  4194.3ms
  * 24M:  8us   ~  2796.2ms
  * 32M： 24us  ~  2097.1ms
  * 144M：1.3us ~  466ms
  */
enum kscan_idx_itv_t
{
    ITV_1MS   =  IDX_MS(1),
    ITV_2MS   =  IDX_MS(2),
    ITV_5MS   =  IDX_MS(5),
    ITV_10MS   =  IDX_MS(10),
    ITV_15MS   =  IDX_MS(15),
    ITV_20MS   =  IDX_MS(20),
    ITV_25MS   =  IDX_MS(25),
    ITV_30MS   =  IDX_MS(30),
    ITV_35MS   =  IDX_MS(35),
    ITV_40MS   =  IDX_MS(40),
    ITV_45MS   =  IDX_MS(45),
    ITV_50MS   =  IDX_MS(50),
    ITV_60MS   =  IDX_MS(60),
    ITV_70MS   =  IDX_MS(70),
    ITV_80MS   =  IDX_MS(80),
    ITV_90MS   =  IDX_MS(90),
    ITV_100MS   =  IDX_MS(100),
    ITV_200MS   =  IDX_MS(200),
    ITV_300MS   =  IDX_MS(300),
    ITV_400MS   =  IDX_MS(400)
};

/**
  * cyc new
  * us = (idx + 1) / (SDK_PCLK_MHZ / 64);
  * 16M:   12  ~  1024us
  * 24M:   8   ~  682.67us
  * 32M：  6   ~  512us
  * 144M: 1.33 ~ 113.78us
  */
enum kscan_idx_cyc_t
{
    CYC_15US   =  IDX_US(15),
    CYC_20US   =  IDX_US(20),
    CYC_25US   =  IDX_US(25),
    CYC_30US   =  IDX_US(30),
    CYC_35US   =  IDX_US(35),
    CYC_40US   =  IDX_US(40),
    CYC_45US   =  IDX_US(45),
    CYC_50US   =  IDX_US(50),
    CYC_60US   =  IDX_US(60),
    CYC_70US   =  IDX_US(70),
    CYC_80US   =  IDX_US(80),
    CYC_90US   =  IDX_US(90),
    CYC_100US  =  IDX_US(100)
};

typedef struct
{
    enum kscan_idx_itv_t itv;
    enum kscan_idx_cyc_t cyc_cap;
    enum kscan_idx_cyc_t cyc_udrv;
    enum kscan_idx_cyc_t cyc_len;
    uint32_t             row_en;
    uint8_t              col_en;
    uint8_t              scan_cnt_nopress;
} KSCAN_PARAM;

/**
  * @brief Initializes the KSCAN peripheral.
  * @param  KSCAN_PARAM
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_KSCAN_Init(KSCAN_PARAM *param);

/**
  * @brief DeInitializes the KSCAN peripheral.
  * @param  None
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_KSCAN_DeInit(void);

/**
  * @brief  moulde kscan starts scanning
  * @param  None
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_KSCAN_Start(void);

/**
  * @brief  moulde kscan stops scanning
  * @param  None
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_KSCAN_Stop(void);

/**
  * @brief  KSCAN key press callback
  * @param  col Press key col
  * @param  row Press key row
  * @param  pressed key pressed state，0: nopress 1:press
  */
void HAL_KSCAN_Press_callback(uint8_t col, uint8_t row, uint8_t pressed);

void HAL_KSCAN_IRQHandler();

#ifdef __cplusplus
}
#endif

#endif /* LS_HAL_KSCAN_H_ */
