#include "ls_hal_ssiv2.h"
#include "ls_msp_ssiv2.h"
#include "field_manipulate.h"
#include "hal_flash_int.h"
#include "reg_cpu1_sys.h"
#include "reg_sysc_awo.h"
#include "ls_soc_gpio.h"

static void fwqspi_pin_enable(){
    // REG_FIELD_WR(SYSC_AWO_CFG->FUNC1_AABBCCDD_EN, SYSC_AWO_FUNC1_IOBB_EN, 0x3f);//sclk/ss_0/1/2/dat[0]/[1]
    // REG_FIELD_WR(SYSC_AWO_CFG->GPAABBCCDD_IE, SYSC_AWO_GPIOBB_IE, 0x30);//dat0/1 ie
    pinmux_ssiv2_init();
}

HAL_StatusTypeDef HAL_SSIV2_Init(uint32_t div_para, enum slave_select slave_sel, uint8_t clk_edg_sel)
{
    HAL_LSSSIV2_MSP_Init();
    fwqspi_pin_enable();
    CPU1_SYS_CFG->SOFT_FWSPI_SS_IN_N = 1; //软件配置片选是否有效位，低有效(此处硬件CS)
    REG_FIELD_WR(flash.reg->ddress_block.SSIENR, SSIENR_SSIC_EN, SSIC_DISABLE);
    MODIFY_REG(flash.reg->ddress_block.CTRLR0, CTRLR0_SSTE_MASK | CTRLR0_SPI_FRF_MASK | CTRLR0_DFS_MASK, TOGGLE_DISABLE << CTRLR0_SSTE_POS | STANDARD_SPI_FORMAT << CTRLR0_SPI_FRF_POS | DFS_8_BIT << CTRLR0_DFS_POS);
    REG_FIELD_WR(flash.reg->ddress_block.BAUDR, BAUDR_SCKDV, div_para); // Fsclk_out = Fssi_clk/BAUDR

    switch (slave_sel){
        case 1:CPU1_SYS_CFG->SOFT_FWSPI_SLAVE_SEL = 0;break;
        case 2:CPU1_SYS_CFG->SOFT_FWSPI_SLAVE_SEL = 1;break;
        case 4:CPU1_SYS_CFG->SOFT_FWSPI_SLAVE_SEL = 2;break;
    }
    flash.slave_select = slave_sel;
    //软件配置fwspi输出clk是否反转，复位值0，0：根据fwspi配置输出；1：根据fwspi配置取反输出。
    CPU1_SYS_CFG->SOFT_FWSPI_OSCLK_INV_SEL = clk_edg_sel;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SSIV2_DeInit(void)
{
    HAL_LSSSIV2_MSP_DeInit();
    return HAL_OK;
}

void lsssiv2_stg_send_command(reg_axi_ssi_t *reg, uint8_t opcode){
    // CTRLR0 can be configured only when it is turned off
    REG_FIELD_WR(reg->ddress_block.SSIENR, SSIENR_SSIC_EN, SSIC_DISABLE);
    MODIFY_REG(reg->ddress_block.CTRLR0, CTRLR0_TMOD_MASK, TX_ONLY<<CTRLR0_TMOD_POS);
    REG_FIELD_WR(reg->ddress_block.SSIENR,SSIENR_SSIC_EN, SSIC_ENABLE);
    reg->ddress_block.DR0 = opcode;
    REG_FIELD_WR(reg->ddress_block.SER, SER_SER, flash.slave_select);
    while(REG_FIELD_RD(reg->ddress_block.SR, SR_BUSY));
    REG_FIELD_WR(reg->ddress_block.SER,SER_SER, 0);
}

void lsssiv2_stg_read_register(reg_axi_ssi_t *reg, uint32_t addr, bool is_addr, uint8_t opcode, uint8_t *data, uint8_t dummy_cycles, uint32_t length)
{
    REG_FIELD_WR(reg->ddress_block.SSIENR, SSIENR_SSIC_EN, SSIC_DISABLE);
    MODIFY_REG(reg->ddress_block.CTRLR0, CTRLR0_TMOD_MASK, EEPROM_READ<<CTRLR0_TMOD_POS);
    //The number of continuously received data frames, in units of CTRLR0 DFS, here represents "length" bytes
    WRITE_REG(reg->ddress_block.CTRLR1, length-1);
    REG_FIELD_WR(reg->ddress_block.SSIENR, SSIENR_SSIC_EN, SSIC_ENABLE);
    reg->ddress_block.DR0 = opcode;
    if(is_addr)
    {
        reg->ddress_block.DR0 = addr>>24;
        reg->ddress_block.DR0 = (addr>>16) & 0xFF;
        reg->ddress_block.DR0 = (addr>>8) & 0xFF;
        reg->ddress_block.DR0 = addr&0xFF;
        while(dummy_cycles--)
        {
            reg->ddress_block.DR0 = 0x00;
        }
    }
    REG_FIELD_WR(reg->ddress_block.SER, SER_SER, flash.slave_select);
    while(length)
    {
        if(READ_BIT(reg->ddress_block.SR, SR_RFNE_MASK))
        {
            *data++ = reg->ddress_block.DR0;
            length--;
        }
    }
    while(REG_FIELD_RD(reg->ddress_block.SR, SR_BUSY));
    REG_FIELD_WR(reg->ddress_block.SER, SER_SER, 0);
}

void lsssiv2_stg_write_register(reg_axi_ssi_t *reg, uint32_t addr, bool is_addr, uint8_t opcode, uint8_t *data, uint16_t length)
{
    lsssiv2_stg_send_command(flash.reg, WRITE_ENABLE_OPCODE);
    reg->ddress_block.DR0 = opcode;
    if(is_addr)
    {
        reg->ddress_block.DR0 = addr>>24;
        reg->ddress_block.DR0 = (addr>>16) & 0xFF;
        reg->ddress_block.DR0 = (addr>>8) & 0xFF;
        reg->ddress_block.DR0 = addr&0xFF;
    }
    //Slave Select Enable Flag: After opening, start sending and receiving data
    REG_FIELD_WR(reg->ddress_block.SER, SER_SER, flash.slave_select);
    while(length)
    {
        if(READ_BIT(reg->ddress_block.SR, SR_TFNF_MASK))
        {
            reg->ddress_block.DR0 = *data++;
            length--;
        }
    }
    while(REG_FIELD_RD(reg->ddress_block.SR, SR_BUSY)); 
    REG_FIELD_WR(reg->ddress_block.SER, SER_SER, 0);
    uint8_t status_reg_0;
    do{
        hal_flash_read_status_register_0(&status_reg_0);
    }while(status_reg_0 & 0x01);
}

void hal_flash_fast_read(uint32_t offset, uint8_t *data, uint32_t length)
{
    lsssiv2_stg_read_register(flash.reg, offset, true, FAST_READ4B_OPCODE, data, 1, length);
}

void hal_flash_page_program(uint32_t offset, uint8_t *data, uint16_t length)
{
    lsssiv2_stg_write_register(flash.reg, offset, true, PAGE_PROGRAM4B_OPCODE, data, length);
}

void hal_flash_read_status_register_0(uint8_t *status_reg_0)
{
    lsssiv2_stg_read_register(flash.reg, 0, false, READ_STATUS_REGISTER_0_OPCODE, status_reg_0, 0, 1);
}

void hal_flash_read_status_register_1(uint8_t *status_reg_1)
{
    lsssiv2_stg_read_register(flash.reg, 0, false, READ_STATUS_REGISTER_1_OPCODE, status_reg_1, 0, 1);
}

void hal_flash_write_status_register_0(uint8_t status_0)
{
    lsssiv2_stg_write_register(flash.reg, 0, false, WRITE_STATUS_REGISTER_0_OPCODE, &status_0, 1);
}

void hal_flash_write_status_register_1(uint8_t status_1)
{
    lsssiv2_stg_write_register(flash.reg, 0, false, WRITE_STATUS_REGISTER_1_OPCODE, &status_1, 1);
}

void hal_flash_sector_erase(uint32_t offset)
{
    lsssiv2_stg_write_register(flash.reg, offset, true, SECTOR_ERASE4B_OPCODE, NULL, 0);
}

void hal_flash_block_32K_erase(uint32_t offset)
{
    lsssiv2_stg_write_register(flash.reg, offset, true, BLOCK_32K_ERASE4B_OPCODE, NULL, 0);
}

void hal_flash_block_64K_erase(uint32_t offset)
{
    lsssiv2_stg_write_register(flash.reg, offset, true, BLOCK_64K_ERASE4B_OPCODE, NULL, 0);
}

void hal_flash_software_reset()
{
    lsssiv2_stg_send_command(flash.reg, RESET_EN_OPCODE);
    lsssiv2_stg_send_command(flash.reg, RESET_OPCODE);
}