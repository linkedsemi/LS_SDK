#include "ls_hal_qspiv2.h"
#include "compile_flag.h"
#include "field_manipulate.h"
#include "hal_flash_int.h"
#define LSQSPIV2_FIFO_DEPTH 8

ROM_SYMBOL void XIP_BANNED_FUNC(lsqspiv2_init)
{
    lsqspiv2_msp_init();
    LSQSPIV2->QSPI_CTRL0 = FIELD_BUILD(LSQSPIV2_CLK_CYC,QSPI_CLK_CYCLE) | FIELD_BUILD(LSQSPIV2_CS_INTV,QSPI_CS_INTERVAL) 
        | FIELD_BUILD(LSQSPIV2_CS_HOLD, QSPI_CS_HOLD) | FIELD_BUILD(LSQSPIV2_CS_SETUP, QSPI_CS_SETUP);
    MODIFY_REG(LSQSPIV2->QSPI_CTRL1,LSQSPIV2_CAP_DLY_MASK|LSQSPIV2_CAP_NEG_MASK,QSPI_CAPTURE_DELAY<<LSQSPIV2_CAP_DLY_POS|QSPI_CAPTURE_NEG<<LSQSPIV2_CAP_NEG_POS);
}

static void XIP_BANNED_FUNC(lsqspiv2_xip_mode_start)
{
    LSQSPIV2->DAC_CMD = FIELD_BUILD(LSQSPIV2_DAC_CMD_EN,0);
    LSQSPIV2->DAC_CA_LOW = 0x20<<24;
    REG_FIELD_WR(LSQSPIV2->QSPI_CTRL1,LSQSPIV2_MODE_DAC,1);
}

void XIP_BANNED_FUNC(lsqspiv2_direct_quad_read_config)
{
    LSQSPIV2->DAC_CTRL = FIELD_BUILD(LSQSPIV2_DAC_HZ_CYC,4)|FIELD_BUILD(LSQSPIV2_DAC_MW_WID,QUAD_WIRE)|FIELD_BUILD(LSQSPIV2_DAC_MW_CYC,11)
        | FIELD_BUILD(LSQSPIV2_DAC_MW_EN,1)|FIELD_BUILD(LSQSPIV2_DAC_SW_EN,0);
    lsqspiv2_xip_mode_start();
}

#if DUAL_CONTINUOUS_MODE_OFF
void XIP_BANNED_FUNC(lsqspiv2_direct_dual_read_config)
{
    LSQSPIV2->DAC_CTRL = FIELD_BUILD(LSQSPIV2_DAC_HZ_CYC,1)|FIELD_BUILD(LSQSPIV2_DAC_MW_WID,DUAL_WIRE)|FIELD_BUILD(LSQSPIV2_DAC_MW_CYC,15)
        | FIELD_BUILD(LSQSPIV2_DAC_MW_EN,1)|FIELD_BUILD(LSQSPIV2_DAC_SW_CYC,7)|FIELD_BUILD(LSQSPIV2_DAC_SW_EN,1);
    LSQSPIV2->DAC_CMD = FIELD_BUILD(LSQSPIV2_DAC_CMD,DUAL_IO_READ_OPCODE)|FIELD_BUILD(LSQSPIV2_DAC_CMD_EN,1);
    LSQSPIV2->DAC_CA_LOW = 0;
    REG_FIELD_WR(LSQSPIV2->QSPI_CTRL1,LSQSPIV2_MODE_DAC,1);
}
#else
void XIP_BANNED_FUNC(lsqspiv2_direct_dual_read_config)
{
    LSQSPIV2->DAC_CTRL = FIELD_BUILD(LSQSPIV2_DAC_HZ_CYC,1)|FIELD_BUILD(LSQSPIV2_DAC_MW_WID,DUAL_WIRE)|FIELD_BUILD(LSQSPIV2_DAC_MW_CYC,15)
        | FIELD_BUILD(LSQSPIV2_DAC_MW_EN,1)|FIELD_BUILD(LSQSPIV2_DAC_SW_EN,0);
    lsqspiv2_xip_mode_start();
}
#endif

static void XIP_BANNED_FUNC(write_data_to_fifo,struct lsqspiv2_stg_cfg *cfg)
{
    int16_t tx_remain = cfg->dat_ctrl.dat_bytes + 1 + cfg->dat_ctrl.dat_offset;
    uint32_t *tx_ptr = (uint32_t *)(cfg->data - cfg->dat_ctrl.dat_offset);
    while(tx_remain>0)
    {
        if(LSQSPIV2->FIFO_FLVL!=LSQSPIV2_FIFO_DEPTH)
        {
            LSQSPIV2->FIFO_WDAT = *tx_ptr++;
            tx_remain -= 4;
        }
    }
    while((LSQSPIV2->INTR_RAW&LSQSPIV2_INT_FSM_END_MASK)==0);
}

static void XIP_BANNED_FUNC(read_data_from_fifo,struct lsqspiv2_stg_cfg *cfg)
{
    while(LSQSPIV2->FIFO_FLVL==0);
    uint32_t rx = LSQSPIV2->FIFO_RDAT;
    uint8_t *end = (uint8_t *)cfg->data + cfg->dat_ctrl.dat_bytes + 1;
    uint8_t *head = (uint8_t *)cfg->data;
    switch(cfg->dat_ctrl.dat_offset)
    {
    case 0:
        *head++ = rx;
        if(head==end) break;
    //no break;
    case 1:
        *head++ = rx>>8;
        if(head==end) break;
    //no break;
    case 2:
        *head++ = rx>>16;
        if(head==end) break;
    //no break;
    case 3:
        *head++ = rx>>24;
        if(head==end) break;
    //no break;
    default:
    break;
    }
    uint32_t *rx_ptr = (uint32_t *)head;
    while(end - (uint8_t *)rx_ptr>=4)
    {
        if(LSQSPIV2->FIFO_FLVL)
        {
            *rx_ptr++ = LSQSPIV2->FIFO_RDAT;
        }
    }
    if(end - (uint8_t *)rx_ptr)
    {
        while(LSQSPIV2->FIFO_FLVL==0);
        rx = LSQSPIV2->FIFO_RDAT;
        uint8_t *tail = (uint8_t *)rx_ptr;
        switch(end - (uint8_t *)rx_ptr)
        {
        case 3:
            tail[2] = rx>>16;
        //no break;
        case 2:
            tail[1] = rx>>8;
        //no break;
        case 1:
            tail[0] = rx;
        //no break;
        default:
        break;
        }
    }
}

ROM_SYMBOL void XIP_BANNED_FUNC(lsqspiv2_stg_read_write,struct lsqspiv2_stg_cfg *cfg)
{
    uint32_t cpu_stat = ENTER_CRITICAL();
    LSQSPIV2->INTR_CLR = LSQSPIV2_INT_FSM_END_MASK;
    REG_FIELD_WR(LSQSPIV2->QSPI_CTRL1,LSQSPIV2_MODE_DAC,0);
    uint32_t *ctrl = (uint32_t *)&cfg->ctrl;
    LSQSPIV2->STG_CTRL = *ctrl;
    LSQSPIV2->STG_CA_HIGH = cfg->ca_high;
    LSQSPIV2->STG_CA_LOW = cfg->ca_low;
    uint32_t *dat_ctrl = (uint32_t *)&cfg->dat_ctrl;
    LSQSPIV2->STG_DAT_CTRL = *dat_ctrl;
    LSQSPIV2->STG_REQ_T = 1;
    if(cfg->dat_ctrl.dat_en == 0)
    {
        while((LSQSPIV2->INTR_RAW&LSQSPIV2_INT_FSM_END_MASK)==0);
    }else
    {
        if(cfg->dat_ctrl.dat_dir == WRITE_TO_FLASH)
        {
            write_data_to_fifo(cfg);
        }else
        {
            read_data_from_fifo(cfg);
        }
    }
    EXIT_CRITICAL(cpu_stat);
}

ROM_SYMBOL void XIP_BANNED_FUNC(lsqspiv2_stg_send_command,uint8_t opcode)
{
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 7;
    cfg.ctrl.sw_en = 1;
    cfg.ctrl.hz_cyc = 0;
    cfg.ctrl.mw_wid = 0;
    cfg.ctrl.mw_cyc = 0;
    cfg.ctrl.mw_en = 0;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.ca_high = opcode << 24;
    cfg.dat_ctrl.dat_en = 0;
    cfg.dat_ctrl.dat_bytes = 0;
    cfg.dat_ctrl.dat_dir = 0;
    cfg.dat_ctrl.dat_offset = 0;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    lsqspiv2_stg_read_write(&cfg);
}

ROM_SYMBOL void XIP_BANNED_FUNC(lsqspiv2_stg_read_register,uint8_t opcode,uint8_t *data,uint8_t length)
{
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 7;
    cfg.ctrl.sw_en = 1;
    cfg.ctrl.mw_wid = SINGLE_WIRE;
    cfg.ctrl.hz_cyc = 0;
    cfg.ctrl.mw_cyc = 0;
    cfg.ctrl.mw_en = 0;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.ca_high = opcode << 24;
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_bytes = length - 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)data&0x3;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.data = data;
    lsqspiv2_stg_read_write(&cfg);
}

ROM_SYMBOL void XIP_BANNED_FUNC(lsqspiv2_stg_write_register,uint8_t opcode,uint8_t *data,uint8_t length)
{
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 7;
    cfg.ctrl.sw_en = 1;
    cfg.ctrl.mw_wid = SINGLE_WIRE;
    cfg.ctrl.hz_cyc = 0;
    cfg.ctrl.mw_cyc = 0;
    cfg.ctrl.mw_en = 0;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.ca_high = opcode << 24;
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_bytes = length - 1;
    cfg.dat_ctrl.dat_dir = WRITE_TO_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)data&0x3;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.data = data;
    lsqspiv2_stg_read_write(&cfg);
}
