#include "ls_hal_mjtag.h"
#include "ls_msp_mjtag.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"


static uint32_t TDO_BUF[0x20] = {0x0};
static uint32_t TDI_BUF[0x20] = {0x20, 0x0, 0x0};
static uint32_t TMS_BUF[0x20] = {0x606, 0x1, 0xc};
static uint32_t DW_BUF[0x20]  = {0xe, 0x20, 0x5};

static MJTAG_Init_Param init_param;
static MJTAG_HandleTypeDef MJTAG_Handler;
static MJTAG_Frame_Param param = {
    .tdi = TDI_BUF,
    .tdo = TDO_BUF,
    .tms = TMS_BUF,
    .bitnum = DW_BUF,
    .count = 3,
};

static void init()
{
    LOG_I("MJTAG Test Demo Start...");
    pinmux_mjtag2_init();
    MJTAG_Handler.MJtag = MJTAG2;
    init_param.tck_divider = 0x8;
    init_param.txd_cap_dly = 0x1;
    init_param.rxd_cap_dly = 0x1;
    HAL_MJTAG_Init(&MJTAG_Handler, &init_param);
}

int main(void)
{
    sys_init_none();
    init();

    while (1)
    {
        param.tdo = TDO_BUF;
        param.tms = TMS_BUF;
        param.bitnum = DW_BUF;
        param.tdi = TDI_BUF;
        HAL_MJTAG_Transmit_Polling(&MJTAG_Handler, &param);
        LOG_I("TDO : 0x%x", TDO_BUF[1]);    // IDCODE(reversed)
    }
}
