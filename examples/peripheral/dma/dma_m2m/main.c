#include "ls_hal_dmacv3.h"
#include "platform.h"

#define BUFFER_SIZE 8

static DEF_DMA_CONTROLLER(dmac1_inst,DMAC1)
__aligned(4) static uint8_t test_src[BUFFER_SIZE] = {};
__aligned(4) static uint8_t test_dst[BUFFER_SIZE] = {};
static volatile bool rx_flag = true;
static volatile bool tx_flag = false;

static void HAL_DMA_TxCpltCallback(DMA_Controller_HandleTypeDef *hdma, uint32_t param, uint8_t ch_idx, uint32_t *lli, bool tfr_end)
{
    tx_flag = true;
}

int main(void)
{
    void *DMAC_Instance = &dmac1_inst;
    sys_init_none();
    HAL_DMA_Controller_Init(&dmac1_inst);
    test_src[0] = 0x12;
    test_src[1] = 0x5a;
    test_src[2] = 0x34;
    test_src[3] = 0x6b;

    struct ch_reg cfg;
    DMA_CHANNEL_CFG(cfg,
                      0,
                      test_src,
                      test_dst,
                      TRANSFER_WIDTH_32BITS,
                      1,
                      M2M,
                      0,
                      0,
                      0, 0, 0, 0);
    HAL_DMA_Channel_Start_IT(DMAC_Instance, &cfg, HAL_DMA_TxCpltCallback, 0);

    while (1);
}
