#include "ls_msp_emmc.h"
#include "field_manipulate.h"
#include "exception_isr.h"
#include "core_rv32.h"
#include "sys_stat.h"
#include "qsh.h"
#include "reg_sysc_app_cpu.h"
#include "reg_sysc_app_awo.h"

static sdhci_host *emmc_inst_env[2];

void HAL_LSEMMC_IRQHandler(sdhci_host *host);

void LSEMMC1_IRQHandler(void)
{
    HAL_LSEMMC_IRQHandler(emmc_inst_env[0]);
}

void LSEMMC2_IRQHandler(void)
{
    HAL_LSEMMC_IRQHandler(emmc_inst_env[1]);
}

void lsqsh_emmc_txck_rxck_config()
{
    CLEAR_BIT(SYSC_APP_AWO->ETH_EMMC_RST, SYSC_APP_AWO_EMMC1_CLK_TX_RST_N_MASK);   //emmc1 tx soft reset
    CLEAR_BIT(SYSC_APP_AWO->ETH_EMMC_RST, SYSC_APP_AWO_EMMC1_CLK_RX_RST_N_MASK);   //emmc1 rx soft reset
    CLEAR_BIT(SYSC_APP_AWO->ETH_EMMC_RST, SYSC_APP_AWO_EMMC1_CLK_CORE_RST_N_MASK); //emmc1 base core soft reset
    CLEAR_BIT(SYSC_APP_AWO->ETH_EMMC_RST, SYSC_APP_AWO_EMMC1_CLK_TIM_RST_N_MASK);  //emmc1 timer soft reset

    SET_BIT(SYSC_APP_AWO->ETH_EMMC_RST, SYSC_APP_AWO_EMMC1_CLK_TX_RST_N_MASK);
    SET_BIT(SYSC_APP_AWO->ETH_EMMC_RST, SYSC_APP_AWO_EMMC1_CLK_RX_RST_N_MASK);
    SET_BIT(SYSC_APP_AWO->ETH_EMMC_RST, SYSC_APP_AWO_EMMC1_CLK_CORE_RST_N_MASK);
    SET_BIT(SYSC_APP_AWO->ETH_EMMC_RST, SYSC_APP_AWO_EMMC1_CLK_TIM_RST_N_MASK);

    CLEAR_BIT(SYSC_APP_AWO->EMMC1_TX_RX_CLK, SYSC_APP_AWO_EMMC1_CLK_TX_CG_MASK);
    SET_BIT(SYSC_APP_AWO->EMMC1_TX_RX_CLK, 0x40);  //25M 的64分频 390K
    REG_FIELD_WR(SYSC_APP_AWO->EMMC1_TX_RX_CLK, SYSC_APP_AWO_EMMC1_CLK_TX_SEL, 0x1); //his 25M
    SET_BIT(SYSC_APP_AWO->EMMC1_TX_RX_CLK, SYSC_APP_AWO_EMMC1_CLK_TX_CG_MASK);

    CLEAR_BIT(SYSC_APP_AWO->EMMC1_TX_RX_CLK, SYSC_APP_AWO_EMMC1_CLK_RX_CG_MASK);
    REG_FIELD_WR(SYSC_APP_AWO->EMMC1_TX_RX_CLK, SYSC_APP_AWO_EMMC1_CLK_RX_SEL, 0x4); //tx_clk_pad
    SET_BIT(SYSC_APP_AWO->EMMC1_TX_RX_CLK, SYSC_APP_AWO_EMMC1_CLK_RX_CG_MASK);

    CLEAR_BIT(SYSC_APP_AWO->EMMC1_CORE_TIM_CLK, SYSC_APP_AWO_EMMC1_CLK_CORE_CG_MASK);
    REG_FIELD_WR(SYSC_APP_AWO->EMMC1_CORE_TIM_CLK, SYSC_APP_AWO_EMMC1_CLK_CORE_DIV, 0); //不分频
    REG_FIELD_WR(SYSC_APP_AWO->EMMC1_CORE_TIM_CLK, SYSC_APP_AWO_EMMC1_CLK_CORE_SEL, 0x1); /* his 25M */
    SET_BIT(SYSC_APP_AWO->EMMC1_CORE_TIM_CLK, SYSC_APP_AWO_EMMC1_CLK_CORE_CG_MASK);

    CLEAR_BIT(SYSC_APP_AWO->EMMC1_CORE_TIM_CLK, SYSC_APP_AWO_EMMC1_CLK_TIM_CG_MASK);
    SET_BIT(SYSC_APP_AWO->EMMC1_CORE_TIM_CLK, SYSC_APP_AWO_EMMC1_CLK_TIM_DIV_MASK);
    REG_FIELD_WR(SYSC_APP_AWO->EMMC1_CORE_TIM_CLK, SYSC_APP_AWO_EMMC1_CLK_TIM_SEL, 0x1); /* hsi 25M */
    SET_BIT(SYSC_APP_AWO->EMMC1_CORE_TIM_CLK, SYSC_APP_AWO_EMMC1_CLK_TIM_CG_MASK);
}

void HAL_LSEMMC_MSP_Init(sdhci_host *host)
{
    lsqsh_emmc_txck_rxck_config();
    switch (host->mapbase)
    {
        case LSEMMC1:
            SYSC_APP_CPU->PD_CPU_CLKG1 = SYSC_APP_CPU_CLKG_CLR_EMMC1_MASK;
            SYSC_APP_CPU->PD_CPU_SRST1 = SYSC_APP_CPU_SRST_CLR_EMMC1_MASK;
            SYSC_APP_CPU->PD_CPU_SRST1 = SYSC_APP_CPU_SRST_SET_EMMC1_MASK;
            SYSC_APP_CPU->PD_CPU_CLKG1 = SYSC_APP_CPU_CLKG_SET_EMMC1_MASK;
            emmc_inst_env[0] = host;
            rv_set_int_isr(EMMC1_IRQN, LSEMMC1_IRQHandler);
            csi_vic_clear_pending_irq(EMMC1_IRQN);
            csi_vic_enable_irq(EMMC1_IRQN);
        break;
        case LSEMMC2:
            SYSC_APP_CPU->PD_CPU_CLKG1 = SYSC_APP_CPU_CLKG_CLR_EMMC2_MASK;
            SYSC_APP_CPU->PD_CPU_SRST1 = SYSC_APP_CPU_SRST_CLR_EMMC2_MASK;
            SYSC_APP_CPU->PD_CPU_SRST1 = SYSC_APP_CPU_SRST_SET_EMMC2_MASK;
            SYSC_APP_CPU->PD_CPU_CLKG1 = SYSC_APP_CPU_CLKG_SET_EMMC2_MASK;
            emmc_inst_env[1] = host;
            rv_set_int_isr(EMMC2_IRQN, LSEMMC2_IRQHandler);
            csi_vic_clear_pending_irq(EMMC2_IRQN);
            csi_vic_enable_irq(EMMC2_IRQN);
        break;
        default:
        break;
    }
}

void HAL_LSEMMC_MSP_DeInit(sdhci_host *host)
{
    switch (host->mapbase)
    {
        case LSEMMC1:
            SYSC_APP_CPU->PD_CPU_CLKG1 = SYSC_APP_CPU_CLKG_CLR_EMMC1_MASK;
            csi_vic_disable_irq(EMMC1_IRQN);
        break;
        case LSEMMC2:
            SYSC_APP_CPU->PD_CPU_CLKG1 = SYSC_APP_CPU_CLKG_CLR_EMMC2_MASK;
            csi_vic_disable_irq(EMMC2_IRQN);
        break;
        default:
        break;
    }
}