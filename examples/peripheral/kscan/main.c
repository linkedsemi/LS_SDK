#include "ls_hal_kscan.h"
#include "ls_msp_kscan.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"

#define DEBUG_CLOSE 1

#if (DEBUG_CLOSE == 1)
#define COL_EN 0xFF
#else
#define COL_EN 0xF3
#endif

#define ROW_EN 0x3FFFF

static void demo_kscan_init(void)
{
#if (DEBUG_CLOSE == 1)
    pinmux_cjtag_deinit();          // col1,col2 is cjtag ping, cjtag debugging must be turned off
#endif
    LOG_I("kscan demo started!");
    pinmux_kscan_init(COL_EN, ROW_EN);
    static KSCAN_PARAM param;
    param.col_en            = COL_EN;
    param.row_en            = ROW_EN;
    param.cyc_cap           = CYC_15US;
    param.cyc_len           = CYC_40US;
    param.cyc_udrv          = CYC_20US;
    param.itv               = ITV_20MS;
    param.scan_cnt_nopress  = 5;        // No key press event after scanning `scan_cnt_nopress` stops
    HAL_KSCAN_Init(&param);
}

int main(void)
{
    sys_init_none();
    demo_kscan_init();
    HAL_KSCAN_Start();
    while (1)
    {

    }
}

void HAL_KSCAN_Press_callback(uint8_t col, uint8_t row, uint8_t pressed)
{
    if (pressed)
    {
        LOG_I("PRESS\n\t>>>>>>>>>>>>>>   row: %x   col: %x", row, col);
    }
    else
    {
        LOG_I("UNPRESS\n\t<<<<<<<<<<<<<<   row: %x   col: %x", row, col );
    }
    LOG_HEX(kscan_matrix, sizeof(kscan_matrix));
}