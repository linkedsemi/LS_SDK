#include "ls_soc_gpio.h"
#include "platform.h"
#include "sleep.h"
#include "log.h"
#include <string.h>
#include "field_manipulate.h"
#include "reg_v33_rg.h"

void LVD33_Handler(void)
{
    LOG_RAW("LVD33 interrupt!\r\n");
    csi_vic_clear_pending_irq(LVD33_IRQn);
    REG_FIELD_WR(V33_RG->MISC_CTRL0, V33_RG_LVD33_INTR_CLR, 1);
    REG_FIELD_WR(V33_RG->MISC_CTRL0, V33_RG_LVD33_INTR_CLR, 0);
    while(1) {
        if (REG_FIELD_RD(V33_RG->MISC_CTRL0, V33_RG_LVD33_DTCT)) {
            //LOG_RAW("LVD33 DETECTED!\r\n");
        } else {
            LOG_RAW("LVD33 NOT DETECTED!\r\n");
            break;
        }
    }
}

/* 这个例程针对的是riscv的内核的芯片 */
int main(void)
{
    sys_init_none();

    LOG_RAW("start lvd test\r\n");
    REG_FIELD_WR(V33_RG->ANA_PMU_CTRL, V33_RG_LVD_CTRL, 0x1F);
    REG_FIELD_WR(V33_RG->MISC_CTRL0, V33_RG_LVD33_POL, 0);
    REG_FIELD_WR(V33_RG->MISC_CTRL0, V33_RG_LVD33_INTR_EN, 1);
    /* 设置为1，会自动清除lvd33的中断，导致中断上不去，必须设置为0, */
    REG_FIELD_WR(V33_RG->MISC_CTRL0, V33_RG_LVD33_INTR_CLR, 0);

    rv_set_int_isr(LVD33_IRQn,LVD33_Handler);
    csi_vic_clear_pending_irq(LVD33_IRQn);
    csi_vic_enable_irq(LVD33_IRQn);

    static uint32_t tickCnt = 0;
    while (1)
    {
        DELAY_MS(1000);
        LOG_RAW("cur tick %lx\r\n", tickCnt++);
    }
}
