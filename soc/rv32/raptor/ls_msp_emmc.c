#include "ls_msp_emmc.h"
#include "ls_hal_emmc.h"
#include "raptor.h"
#include "exception_isr.h"
#include "core_rv32.h"

#include "reg_cpu1_sys.h"
#include "field_manipulate.h"

#include "reg_sysc_awo.h"
#include "reg_pipe_sys.h"
#include "ls_soc_gpio.h"
#define BOOT             0

#define TX_RX_EQ         1    //rx clk from tx clk

void emmc_interal_clk_cfg(void) {
  /** Bclk */ //200mhz
  // x/x 0x90928070
  PIPE_SYS_CFG -> EMMC_CORE_CLK_CLK_DEGLITCH_SW3_REG = 0x4;
  // x/x 0x90928074
  PIPE_SYS_CFG -> EMMC_CORE_CLK_CLK_DIV0_DIV2_REG = 0x0;
  /** Tclk */ //50mhz
  // x/x 0x90928088
  PIPE_SYS_CFG -> EMMC_TM_CLK_CLK_DEGLITCH_SW3_REG = 0x4;
  // x/x 0x9092808c
  PIPE_SYS_CFG -> EMMC_TM_CLK_CLK_DIV0_DIV8_REG = 0x0;
}

void emmc_txrx_clk_cfg(volatile uint32_t mode,volatile uint32_t rx_mode) {
  /** tx */
  if(mode == BOOT ) { 	
    // x/x 0x9092807c
    PIPE_SYS_CFG -> EMMC_CCLK_TX_CLK_CLK_DEGLITCH_SW2_REG = 0x1;
    // x/x 0x90928080
    // PIPE_SYS_CFG -> EMMC_CCLK_TX_CLK_CLK_DIV0_DIV10_REG = 0x40; 
    PIPE_SYS_CFG -> EMMC_CCLK_TX_CLK_CLK_DIV0_DIV10_REG = 0xa; //10分频  370k左右

    // x/x 0x90928144
    REG_FIELD_WR(PIPE_SYS_CFG -> EMMC_REG0, PIPE_SYS_EMMC_TX_CLK_INV_SEL, 0x1); //bit25
  } 	
  
    //FPGA 一定要配，
    PIPE_SYS_CFG -> EMMC_CCLK_TX_CLK_CLK_DIV0_DIV10_REG = 0xa; //10分频  370k左右

  /** rx */
  if(rx_mode == TX_RX_EQ)  {
    // x/x 0x90928094
    PIPE_SYS_CFG -> EMMC_CCLK_RX_CLK_CLK_DEGLITCH_SW3_REG = 0x4;
    //REG_FIELD_WR(PIPE_SYS_CFG -> EMMC_REG1, PIPE_SYS_EMMC_RX_CLK_INV_SEL, 0x1);	   
  } else {
    if(mode == BOOT) {
      PIPE_SYS_CFG -> EMMC_CCLK_RX_CLK_CLK_DEGLITCH_SW3_REG = 0x1;
    // x/x 0x90928098
    //   PIPE_SYS_CFG -> EMMC_CCLK_RX_CLK_CLK_DIV0_DIV10_REG = 0x40;
      PIPE_SYS_CFG -> EMMC_CCLK_RX_CLK_CLK_DIV0_DIV10_REG = 0xa;

    }
  }
}

void emmc_interal_clk_en(void) {
  /** Enabel T/B CLK*/
  // x/x 0x90928078
  PIPE_SYS_CFG -> EMMC_CORE_CLK_CLK_CG0_REG = 0x1;
  // x/x 0x90928090
  PIPE_SYS_CFG -> EMMC_TM_CLK_CLK_CG0_REG = 0x1; 
}

void emmc_txrx_clk_en(void) {
    // x/x 0x90928084
   PIPE_SYS_CFG -> EMMC_CCLK_TX_CLK_CLK_CG0_REG = 0x1;
    // x/x 0x9092809c
   PIPE_SYS_CFG -> EMMC_CCLK_RX_CLK_CLK_CG0_REG = 0x1;
}

void emmc_clk_stable(void) {
  // x/x 0x90928138  配置内部clk
  REG_FIELD_WR(PIPE_SYS_CFG -> EMMC_CTL0, PIPE_SYS_EMMC_SOFT_INT_BCLK_STABLE, 0x1); 	//bit22
  REG_FIELD_WR(PIPE_SYS_CFG -> EMMC_CTL0, PIPE_SYS_EMMC_SOFT_INT_ACLK_STABLE, 0x1);  //bit23
  REG_FIELD_WR(PIPE_SYS_CFG -> EMMC_CTL0, PIPE_SYS_EMMC_SOFT_INT_TMCLK_STABLE, 0x1);  //bit24
}

void HAL_LSEMMC_MSP_Init(uint32_t mapbase)
{
  //复位操作
  WRITE_REG(PIPE_SYS_CFG -> SOFT_RST_N_REG0_CLR, 0xffffff);
  PIPE_SYS_CFG -> SOFT_RST_N_REG0 = 0xffffff;

    // SYSC_AWO_CFG -> FUNC1_YZEEFF_EN = SYSC_AWO_CFG -> FUNC1_YZEEFF_EN | 0xcff0000;
    // SYSC_AWO_CFG -> FUNC1_YZEEFF_EN = SYSC_AWO_CFG -> FUNC1_YZEEFF_EN | 0xC3F0000; //不配ee6 和 ee7

    // SYSC_AWO_CFG -> FUNC2_YZEEFF_EN = SYSC_AWO_CFG -> FUNC2_YZEEFF_EN | 0x3000000;
    // SYSC_AWO_CFG -> GPYZEEFF_IE = SYSC_AWO_CFG -> GPYZEEFF_IE | 0xfff0000;
    // SYSC_AWO_CFG -> GPYZEEFF_IE = SYSC_AWO_CFG -> GPYZEEFF_IE | 0xf3f0000; //输入使能 不配ee6 和 ee7

    REG_FIELD_WR(PIPE_SYS_CFG -> EMMC_CTL0, PIPE_SYS_EMMC_SOFT_HOST_REG_VOL_STABLE, 0x1);

    /** <DONE> card_detect_n/card_write_prot config by software 软件告知emmc 卡起来了， 有实卡可选软件或者硬件pad告知*/
    REG_FIELD_WR(PIPE_SYS_CFG -> EMMC_CTL0, PIPE_SYS_EMMC_SOFT_CARD_DETECT_N, 0x1);
    REG_FIELD_WR(PIPE_SYS_CFG -> EMMC_CTL0, PIPE_SYS_EMMC_SOFT_CARD_WRITE_PROT, 0x1);

    emmc_interal_clk_cfg();
    emmc_txrx_clk_cfg(BOOT,TX_RX_EQ);  //tx  clk 配置
    emmc_interal_clk_en();
    emmc_txrx_clk_en();
    emmc_clk_stable();

    // 0x90928110
    // PIPE_SYS_CFG -> SOFT_RST_N_REG0 = 0x0;
    // PIPE_SYS_CFG -> SOFT_RST_N_REG0 = 0xffffffff;


   //总线clk
    REG_FIELD_WR(CPU1_SYS_CFG -> PIPE_SYS_CFG_REG1, PIPE_SYS_EMMC_AXI_CLK_CLK_CG0_5, 0x1); 
    REG_FIELD_WR(CPU1_SYS_CFG -> PIPE_SYS_CFG_REG3, PIPE_SYS_EMMC_AHB_CLK_CLK_CG0_1, 0x1);
}

void HAL_LSEMMC_MSP_DeInit(uint32_t mapbase)
{

}