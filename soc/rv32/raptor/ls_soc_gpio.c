#include <stdint.h>
#include <stddef.h>
#include "common.h"
#include "ls_soc_gpio.h"
#include "field_manipulate.h"
#include "reg_sysc_awo.h"
#include "per_func_mux_mult.h"
#include <string.h>

static gpio_port_pin_t dwuart0_txd;
static gpio_port_pin_t dwuart0_rxd;
static gpio_port_pin_t dwuart1_txd;
static gpio_port_pin_t dwuart1_rxd;
static gpio_port_pin_t dwuart2_txd;
static gpio_port_pin_t dwuart2_rxd;
static gpio_port_pin_t dwuart3_0_txd;
static gpio_port_pin_t dwuart3_0_rxd;
static gpio_port_pin_t dwuart3_1_txd;
static gpio_port_pin_t dwuart3_1_rxd;
static gpio_port_pin_t dwuart4_txd;
static gpio_port_pin_t dwuart4_rxd;
static gpio_port_pin_t dwuart5_txd;
static gpio_port_pin_t dwuart5_rxd;
static gpio_port_pin_t dwuart6_txd;
static gpio_port_pin_t dwuart6_rxd;
static gpio_port_pin_t dwuart7_txd;
static gpio_port_pin_t dwuart7_rxd;
static gpio_port_pin_t dwuart8_txd;
static gpio_port_pin_t dwuart8_rxd;
static gpio_port_pin_t dwuart9_txd;
static gpio_port_pin_t dwuart9_rxd;
static gpio_port_pin_t dwuart10_txd;
static gpio_port_pin_t dwuart10_rxd;
static gpio_port_pin_t dwuart11_txd;
static gpio_port_pin_t dwuart11_rxd;
static gpio_port_pin_t dwuart12_txd;
static gpio_port_pin_t dwuart12_rxd;

void io_init(void)
{
    // uint32_t gpio_ie_value[15] = {0xffff0000,0xfffc0000};
    // for (uint8_t i = 0; i < 15; i++)
    // {
    //     PMU->IO[i].IEN_OD = gpio_ie_value[i];
    //     PMU->IO[i].OE_FIR= 0;
    //     PMU->GPIO_INTR_CLR[i] = 0xffff;
    //     PMU->GPIO_INTR_CLR[i] = 0;
    // }
    
    // EXTI->EICR = 0xffffffff;
    // EXTI->EICR = 0;
    // rv_set_int_isr(EXTI_ASYNC_IRQn,VCore_EXTI_Async_Handler);
    // csi_vic_clear_pending_irq(EXTI_ASYNC_IRQn);
    // csi_vic_enable_irq(EXTI_ASYNC_IRQn);
    
    // rv_set_int_isr(V33_EXT_IRQn,V33_EXTI_Async_Handler);
    // csi_vic_clear_pending_irq(V33_EXT_IRQn);
    // csi_vic_enable_irq(V33_EXT_IRQn);
    
}

bool io_is_output_enabled(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    return READ_BIT(SYSC_AWO_CFG->OE[x->port/4], 1<<x->num<<((x->port % 4)*8)) != 0;
}

bool io_is_opendrain(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    return READ_BIT(SYSC_AWO_CFG->IO_ODE[x->port/4], 1<<x->num<<((x->port % 4)*8)) != 0;
}

void io_cfg_output(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    SYSC_AWO_CFG->OE[x->port/4] |= 1<<x->num<<((x->port % 4)*8);
}

void io_cfg_opendrain(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    SYSC_AWO_CFG->IO_ODE[x->port/4] |= 1<<x->num<<((x->port % 4)*8);
}

void io_cfg_input(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    SYSC_AWO_CFG->IE[x->port/4] |= 1<<x->num<<((x->port % 4)*8);
}

bool io_is_input_enabled(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    return READ_BIT(SYSC_AWO_CFG->IE[x->port/4], 1<<x->num<<((x->port % 4)*8)) != 0;
}

bool io_is_output(uint16_t pin)
{
    return io_is_output_enabled(pin);
}

bool io_is_input(uint16_t pin)
{
    return (!io_is_output_enabled(pin)) && io_is_input_enabled(pin);
}

void io_write_pin(uint16_t pin, uint16_t val)
{
    if(val)
    {
        io_set_pin(pin);
    }else
    {
        io_clr_pin(pin);
    }
}

void io_set_pin(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    SYSC_AWO_CFG->IO_VAL[x->port/4] |= 1<<x->num<<((x->port % 4)*8);
}

void io_clr_pin(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    SYSC_AWO_CFG->IO_VAL[x->port/4] &= ~(1<<x->num<<((x->port % 4)*8));
}

void io_toggle_pin(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    if(SYSC_AWO_CFG->IO_VAL[x->port/4] & (1<<x->num<<((x->port % 4)*8)))
    {
        io_clr_pin(pin);
    }else
    {
        io_set_pin(pin);
    }
}

uint8_t io_get_output_val(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    return (SYSC_AWO_CFG->IO_VAL[x->port/4] >> ((x->port % 4)*8 + x->num)) & 0x1;
}

uint8_t io_get_input_val(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    return (SYSC_AWO_CFG->IO_INPUT[x->port/4] >> ((x->port % 4)*8 + x->num)) & 0x1;
}

void io_pull_write(uint16_t pin,io_pull_type_t pull)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    switch(pull)
    {
    case IO_PULL_UP:
        if(x->port == 0x8 || x->port == 0xb)
            SYSC_AWO_CFG->GPIL_PU |= 1<<x->num<<((x->port % 2)*8);
        else if(x->port == 0x9 || x->port == 0xa)
            SYSC_AWO_CFG->GPJK_PU[x->port-0x9] |= 1<<x->num;
        else if(x->port < 0x8)
            SYSC_AWO_CFG->GPA_H_PU[x->port/4] |= 1<<x->num<<((x->port % 4)*8);
        else
            SYSC_AWO_CFG->GPM_DD_PU[(x->port-0xc)/4] |= 1<<x->num<<((x->port % 4)*8);
    break;

    case IO_PULL_DOWN:
        SYSC_AWO_CFG->IO_PULL_DOWN[x->port/4] |= 1<<x->num<<((x->port % 4)*8);
    break;

    case IO_PULL_DISABLE:
        if(x->port == 0x8 || x->port == 0xb)
            SYSC_AWO_CFG->GPIL_PU &= ~(1<<x->num<<((x->port % 2)*8));
        if(x->port == 0x9 || x->port == 0xa)
            SYSC_AWO_CFG->GPJK_PU[x->port-0x9] &= ~(1<<x->num);
        else if(x->port < 0x8)
            SYSC_AWO_CFG->GPA_H_PU[x->port/4] &= ~(1<<x->num<<((x->port % 4)*8));
        else
            SYSC_AWO_CFG->GPM_DD_PU[(x->port-0xc)/4] &= ~(1<<x->num<<((x->port % 4)*8));

        SYSC_AWO_CFG->IO_PULL_DOWN[x->port/4] &= ~(1<<x->num<<((x->port % 4)*8));
    break;
    }
}

static void dwuart_io_cfg(uint16_t txd,uint16_t rxd)
{
    io_set_pin(txd);
    io_cfg_output(txd);
    io_cfg_input(rxd);
    io_pull_write(rxd, IO_PULL_UP);
}

static uint16_t pin2func_io(gpio_port_pin_t *x)
{
    return x->port * 16 + x->num;
}

void per_func1_enable(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    SYSC_AWO_CFG->IO_FUNC1_EN[x->port/4] |= 1<<x->num<<((x->port % 4)*8);
}

void per_func1_disable(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    SYSC_AWO_CFG->IO_FUNC1_EN[x->port/4] &= ~(1<<x->num<<((x->port % 4)*8));
}

void per_func2_enable(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    SYSC_AWO_CFG->IO_FUNC2_EN[x->port/4] |= 1<<x->num<<((x->port % 4)*8);
}

void per_func2_disable(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    SYSC_AWO_CFG->IO_FUNC2_EN[x->port/4] &= ~(1<<x->num<<((x->port % 4)*8));
}

void per_func3_enable(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    SYSC_AWO_CFG->IO_FUNC3_EN[x->port/4] |= 1<<x->num<<((x->port % 4)*8);
}

void per_func3_disable(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    SYSC_AWO_CFG->IO_FUNC3_EN[x->port/4] &= ~(1<<x->num<<((x->port % 4)*8));
}

void per_func4_enable(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    SYSC_AWO_CFG->IO_FUNC4_EN[x->port/4] |= 1<<x->num<<((x->port % 4)*8);
}

void per_func4_disable(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    SYSC_AWO_CFG->IO_FUNC4_EN[x->port/4] &= ~(1<<x->num<<((x->port % 4)*8));
}

void per_func5_enable(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    SYSC_AWO_CFG->IO_FUNC5_EN[x->port/4] |= 1<<x->num<<((x->port % 4)*8);
}

void per_func5_disable(uint16_t pin)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    SYSC_AWO_CFG->IO_FUNC5_EN[x->port/4] &= ~(1<<x->num<<((x->port % 4)*8));
}

void io_drive_capacity_write(uint16_t pin, io_drive_type_t drive)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;

    if(drive&DS0){
        SYSC_AWO_CFG->IO_DS0[x->port/4] |= 1<<x->num<<((x->port % 4)*8);
    }else{
        SYSC_AWO_CFG->IO_DS0[x->port/4] &= ~(1<<x->num<<((x->port % 4)*8));
    }
        
    if(drive&DS1){
        SYSC_AWO_CFG->IO_DS1[x->port/4] |= 1<<x->num<<((x->port % 4)*8);
    }else{
        SYSC_AWO_CFG->IO_DS1[x->port/4] &= ~(1<<x->num<<((x->port % 4)*8));
    }

    if(drive&DS2){
        SYSC_AWO_CFG->IO_DS2[x->port/4] |= 1<<x->num<<((x->port % 4)*8);
    }else{
        SYSC_AWO_CFG->IO_DS2[x->port/4] &= ~(1<<x->num<<((x->port % 4)*8));
    }

    if(drive&DS3){
        SYSC_AWO_CFG->IO_DS3[x->port/4] |= 1<<x->num<<((x->port % 4)*8);
    }else{
        SYSC_AWO_CFG->IO_DS3[x->port/4] &= ~(1<<x->num<<((x->port % 4)*8));
    }
}

void pinmux_ssiv2_init()
{
    per_func1_enable(PBB00); //clk
    per_func1_enable(PBB01); //ss_0
    per_func1_enable(PBB02); //ss_1
    per_func1_enable(PBB03); //ss_2
    per_func1_enable(PBB04); //dat0
    per_func1_enable(PBB05); //dat1
    io_cfg_input(PBB04);
    io_cfg_input(PBB05);
    io_pull_write(PU06, IO_PULL_UP); //dat2
    io_pull_write(PU07, IO_PULL_UP); //dat3
    io_pull_write(PN03, IO_PULL_UP); //dat2
    io_pull_write(PN04, IO_PULL_UP); //dat3
    io_pull_write(PO03, IO_PULL_UP); //dat2
    io_pull_write(PO04, IO_PULL_UP); //dat3
    io_drive_capacity_write(PBB00, DS3);
    io_drive_capacity_write(PBB01, DS3);
    io_drive_capacity_write(PBB02, DS3);
    io_drive_capacity_write(PBB03, DS3);
    io_drive_capacity_write(PBB04, DS3);
    io_drive_capacity_write(PBB05, DS3);
    io_drive_capacity_write(PBB06, DS3);
    io_drive_capacity_write(PBB07, DS3);
    io_drive_capacity_write(PP07, DS3);
    io_drive_capacity_write(PQ07, DS3);
    io_drive_capacity_write(PU06, DS3);
    io_drive_capacity_write(PU07, DS3);
    io_drive_capacity_write(PU07, DS3);
    io_drive_capacity_write(PO00, DS3);
    io_drive_capacity_write(PO01, DS3);
    io_drive_capacity_write(PO02, DS3);
    io_drive_capacity_write(PO03, DS3);
    io_drive_capacity_write(PO04, DS3);
    io_drive_capacity_write(PO05, DS3);
    io_drive_capacity_write(PO06, DS3);
    io_drive_capacity_write(PO07, DS3);
    io_drive_capacity_write(PN00, DS3);
    io_drive_capacity_write(PN01, DS3);
    io_drive_capacity_write(PN02, DS3);
    io_drive_capacity_write(PN03, DS3);
    io_drive_capacity_write(PN04, DS3);
    io_drive_capacity_write(PN05, DS3);
    io_drive_capacity_write(PN06, DS3);
    io_drive_capacity_write(PN07, DS3);
}

void pinmux_emmc_init()
{
    per_func1_enable(PEE00);
    per_func1_enable(PEE01);
    per_func1_enable(PEE02);
    per_func1_enable(PEE03);
    per_func1_enable(PEE04);
    per_func1_enable(PEE05);
    per_func1_enable(PEE06);
    per_func1_enable(PEE07);
    per_func2_enable(PFF00);
    per_func2_enable(PFF01);
    per_func1_enable(PFF02);
    per_func1_enable(PFF03);
    io_cfg_input(PEE00); //clk
    io_cfg_input(PEE01); //cmd
    io_cfg_input(PEE02); //dat[0]
    io_cfg_input(PEE03); //dat[1]
    io_cfg_input(PEE04); //dat[2]
    io_cfg_input(PEE05); //dat[3]
    io_cfg_input(PFF00); //dat[4]
    io_cfg_input(PFF01); //dat[5]
    io_cfg_input(PFF02); //dat[6]
    io_cfg_input(PFF03); //dat[7]
    io_pull_write(PEE00, IO_PULL_DOWN);
    io_pull_write(PEE01, IO_PULL_UP);
    io_pull_write(PEE02, IO_PULL_UP);
    io_pull_write(PEE03, IO_PULL_UP);
    io_pull_write(PEE04, IO_PULL_UP);
    io_pull_write(PEE05, IO_PULL_UP);
    io_pull_write(PEE06, IO_PULL_UP);
    io_pull_write(PEE07, IO_PULL_UP);
    io_pull_write(PFF00, IO_PULL_UP);
    io_pull_write(PFF01, IO_PULL_UP);
    io_pull_write(PFF02, IO_PULL_UP);
    io_pull_write(PFF03, IO_PULL_UP);
    io_drive_capacity_write(PEE00, DS3);
    io_drive_capacity_write(PEE01, DS3);
    io_drive_capacity_write(PEE02, DS3);
    io_drive_capacity_write(PEE03, DS3);
    io_drive_capacity_write(PEE04, DS3);
    io_drive_capacity_write(PEE05, DS3);
    io_drive_capacity_write(PEE06, DS3);
    io_drive_capacity_write(PEE07, DS3);
    io_drive_capacity_write(PFF00, DS3);
    io_drive_capacity_write(PFF01, DS3);
    io_drive_capacity_write(PFF02, DS3);
    io_drive_capacity_write(PFF03, DS3);
}

void pinmux_dwuart0_init(uint16_t txd,uint16_t rxd)
{
    memcpy(&dwuart0_txd, &txd, sizeof(uint16_t));
    memcpy(&dwuart0_rxd, &rxd, sizeof(uint16_t));
    dwuart_io_cfg(txd,rxd);
    per_func1_enable(txd);
    per_func1_enable(rxd);
    REG_FIELD_WR(SYSC_AWO_CFG->UART03_TX_MULTIPLEX_SEL, SYSC_AWO_UART0_TX_MULTIPLEX_SEL, 0x0);
    REG_FIELD_WR(SYSC_AWO_CFG->UART03_RX_MULTIPLEX_SEL, SYSC_AWO_UART0_RX_MULTIPLEX_SEL, 0x0);
}

void pinmux_dwuart0_deinit(void)
{
    per_func1_disable(pin2func_io(&dwuart0_txd));
    per_func1_disable(pin2func_io(&dwuart0_rxd));
}

void pinmux_dwuart1_init(uint16_t txd,uint16_t rxd)
{
    memcpy(&dwuart1_txd, &txd, sizeof(uint16_t));
    memcpy(&dwuart1_rxd, &rxd, sizeof(uint16_t));
    dwuart_io_cfg(txd,rxd);
    per_func1_enable(txd);
    per_func1_enable(rxd);
    REG_FIELD_WR(SYSC_AWO_CFG->UART03_TX_MULTIPLEX_SEL, SYSC_AWO_UART1_TX_MULTIPLEX_SEL, 0x1);
    REG_FIELD_WR(SYSC_AWO_CFG->UART03_RX_MULTIPLEX_SEL, SYSC_AWO_UART1_RX_MULTIPLEX_SEL, 0x1);
}

void pinmux_dwuart1_deinit(void)
{
    per_func1_disable(pin2func_io(&dwuart1_txd));
    per_func1_disable(pin2func_io(&dwuart1_rxd));
}

void pinmux_dwuart2_init(uint16_t txd,uint16_t rxd)
{
    memcpy(&dwuart2_txd, &txd, sizeof(uint16_t));
    memcpy(&dwuart2_rxd, &rxd, sizeof(uint16_t));
    dwuart_io_cfg(txd,rxd);
    per_func1_enable(txd);
    per_func1_enable(rxd);
    REG_FIELD_WR(SYSC_AWO_CFG->UART03_TX_MULTIPLEX_SEL, SYSC_AWO_UART2_TX_MULTIPLEX_SEL, 0x2);
    REG_FIELD_WR(SYSC_AWO_CFG->UART03_RX_MULTIPLEX_SEL, SYSC_AWO_UART2_RX_MULTIPLEX_SEL, 0x2);
}

void pinmux_dwuart2_deinit(void)
{
    per_func1_disable(pin2func_io(&dwuart2_txd));
    per_func1_disable(pin2func_io(&dwuart2_rxd));
}

void pinmux_dwuart3_0_init(uint16_t txd,uint16_t rxd)
{
    memcpy(&dwuart3_0_txd, &txd, sizeof(uint16_t));
    memcpy(&dwuart3_0_rxd, &rxd, sizeof(uint16_t));
    dwuart_io_cfg(txd,rxd);
    per_func1_enable(txd);
    per_func1_enable(rxd);
    REG_FIELD_WR(SYSC_AWO_CFG->UART03_TX_MULTIPLEX_SEL, SYSC_AWO_UART30_TX_MULTIPLEX_SEL, 0x3);
    REG_FIELD_WR(SYSC_AWO_CFG->UART03_RX_MULTIPLEX_SEL, SYSC_AWO_UART3_RX_MULTIPLEX_SEL, 0x3);
}

void pinmux_dwuart3_0_deinit(void)
{
    per_func1_disable(pin2func_io(&dwuart3_0_txd));
    per_func1_disable(pin2func_io(&dwuart3_0_rxd));
}

void pinmux_dwuart3_1_init(uint16_t txd,uint16_t rxd)
{
    memcpy(&dwuart3_1_txd, &txd, sizeof(uint16_t));
    memcpy(&dwuart3_1_rxd, &rxd, sizeof(uint16_t));
    dwuart_io_cfg(txd,rxd);
    per_func4_enable(txd);
    per_func4_enable(rxd);
    REG_FIELD_WR(SYSC_AWO_CFG->UART1231_TX_MULTIPLEX_SEL, SYSC_AWO_UART31_TX_MULTIPLEX_SEL, 0x3);
    REG_FIELD_WR(SYSC_AWO_CFG->UART03_RX_MULTIPLEX_SEL, SYSC_AWO_UART3_RX_MULTIPLEX_SEL, 0xd);
}

void pinmux_dwuart3_1_deinit(void)
{
    per_func4_disable(pin2func_io(&dwuart3_1_txd));
    per_func4_disable(pin2func_io(&dwuart3_1_rxd));
}

void pinmux_dwuart4_init(uint16_t txd,uint16_t rxd)
{
    memcpy(&dwuart4_txd, &txd, sizeof(uint16_t));
    memcpy(&dwuart4_rxd, &rxd, sizeof(uint16_t));
    dwuart_io_cfg(txd,rxd);
    per_func1_enable(txd);
    per_func1_enable(rxd);
    REG_FIELD_WR(SYSC_AWO_CFG->UART47_TX_MULTIPLEX_SEL, SYSC_AWO_UART4_TX_MULTIPLEX_SEL, 0x4);
    REG_FIELD_WR(SYSC_AWO_CFG->UART47_RX_MULTIPLEX_SEL, SYSC_AWO_UART4_RX_MULTIPLEX_SEL, 0x4);
}

void pinmux_dwuart4_deinit(void)
{
    per_func1_disable(pin2func_io(&dwuart4_txd));
    per_func1_disable(pin2func_io(&dwuart4_rxd));
}

void pinmux_dwuart5_init(uint16_t txd,uint16_t rxd)
{
    memcpy(&dwuart5_txd, &txd, sizeof(uint16_t));
    memcpy(&dwuart5_rxd, &rxd, sizeof(uint16_t));
    dwuart_io_cfg(txd,rxd);
    per_func1_enable(txd);
    per_func1_enable(rxd);
    REG_FIELD_WR(SYSC_AWO_CFG->UART47_TX_MULTIPLEX_SEL, SYSC_AWO_UART5_TX_MULTIPLEX_SEL, 0x5);
    REG_FIELD_WR(SYSC_AWO_CFG->UART47_RX_MULTIPLEX_SEL, SYSC_AWO_UART5_RX_MULTIPLEX_SEL, 0x5);
}

void pinmux_dwuart5_deinit(void)
{
    per_func1_disable(pin2func_io(&dwuart5_txd));
    per_func1_disable(pin2func_io(&dwuart5_rxd));
}

void pinmux_dwuart6_init(uint16_t txd,uint16_t rxd)
{
    memcpy(&dwuart6_txd, &txd, sizeof(uint16_t));
    memcpy(&dwuart6_rxd, &rxd, sizeof(uint16_t));
    dwuart_io_cfg(txd,rxd);
    per_func1_enable(txd);
    per_func1_enable(rxd);
    REG_FIELD_WR(SYSC_AWO_CFG->UART47_TX_MULTIPLEX_SEL, SYSC_AWO_UART6_TX_MULTIPLEX_SEL, 0x6);
    REG_FIELD_WR(SYSC_AWO_CFG->UART47_RX_MULTIPLEX_SEL, SYSC_AWO_UART6_RX_MULTIPLEX_SEL, 0x6);
}

void pinmux_dwuart6_deinit(void)
{
    per_func1_disable(pin2func_io(&dwuart6_txd));
    per_func1_disable(pin2func_io(&dwuart6_rxd));
}

void pinmux_dwuart7_init(uint16_t txd,uint16_t rxd)
{
    memcpy(&dwuart7_txd, &txd, sizeof(uint16_t));
    memcpy(&dwuart7_rxd, &rxd, sizeof(uint16_t));
    dwuart_io_cfg(txd,rxd);
    per_func1_enable(txd);
    per_func1_enable(rxd);
    REG_FIELD_WR(SYSC_AWO_CFG->UART47_TX_MULTIPLEX_SEL, SYSC_AWO_UART7_TX_MULTIPLEX_SEL, 0x7);
    REG_FIELD_WR(SYSC_AWO_CFG->UART47_RX_MULTIPLEX_SEL, SYSC_AWO_UART7_RX_MULTIPLEX_SEL, 0x7);
}

void pinmux_dwuart7_deinit(void)
{
    per_func1_disable(pin2func_io(&dwuart7_txd));
    per_func1_disable(pin2func_io(&dwuart7_rxd));
}

void pinmux_dwuart8_init(uint16_t txd,uint16_t rxd)
{
    memcpy(&dwuart8_txd, &txd, sizeof(uint16_t));
    memcpy(&dwuart8_rxd, &rxd, sizeof(uint16_t));
    dwuart_io_cfg(txd,rxd);
    per_func3_enable(txd);
    per_func3_enable(rxd);
    REG_FIELD_WR(SYSC_AWO_CFG->UART811_TX_MULTIPLEX_SEL, SYSC_AWO_UART8_TX_MULTIPLEX_SEL, 0x8);
    REG_FIELD_WR(SYSC_AWO_CFG->UART811_RX_MULTIPLEX_SEL, SYSC_AWO_UART8_RX_MULTIPLEX_SEL, 0x8);
}

void pinmux_dwuart8_deinit(void)
{
    per_func3_disable(pin2func_io(&dwuart8_txd));
    per_func3_disable(pin2func_io(&dwuart8_rxd));
}

void pinmux_dwuart9_init(uint16_t txd,uint16_t rxd)
{
    memcpy(&dwuart9_txd, &txd, sizeof(uint16_t));
    memcpy(&dwuart9_rxd, &rxd, sizeof(uint16_t));
    dwuart_io_cfg(txd,rxd);
    per_func3_enable(txd);
    per_func3_enable(rxd);
    REG_FIELD_WR(SYSC_AWO_CFG->UART811_TX_MULTIPLEX_SEL, SYSC_AWO_UART9_TX_MULTIPLEX_SEL, 0x9);
    REG_FIELD_WR(SYSC_AWO_CFG->UART811_RX_MULTIPLEX_SEL, SYSC_AWO_UART9_RX_MULTIPLEX_SEL, 0x9);
}

void pinmux_dwuart9_deinit(void)
{
    per_func3_disable(pin2func_io(&dwuart9_txd));
    per_func3_disable(pin2func_io(&dwuart9_rxd));
}

void pinmux_dwuart10_init(uint16_t txd,uint16_t rxd)
{
    memcpy(&dwuart10_txd, &txd, sizeof(uint16_t));
    memcpy(&dwuart10_rxd, &rxd, sizeof(uint16_t));
    dwuart_io_cfg(txd,rxd);
    per_func3_enable(txd);
    per_func3_enable(rxd);
    REG_FIELD_WR(SYSC_AWO_CFG->UART811_TX_MULTIPLEX_SEL, SYSC_AWO_UART10_TX_MULTIPLEX_SEL, 0xa);
    REG_FIELD_WR(SYSC_AWO_CFG->UART811_RX_MULTIPLEX_SEL, SYSC_AWO_UART10_RX_MULTIPLEX_SEL, 0xa);
}

void pinmux_dwuart10_deinit(void)
{
    per_func3_disable(pin2func_io(&dwuart10_txd));
    per_func3_disable(pin2func_io(&dwuart10_rxd));
}

void pinmux_dwuart11_init(uint16_t txd,uint16_t rxd)
{
    memcpy(&dwuart11_txd, &txd, sizeof(uint16_t));
    memcpy(&dwuart11_rxd, &rxd, sizeof(uint16_t));
    dwuart_io_cfg(txd,rxd);
    per_func3_enable(txd);
    per_func3_enable(rxd);
    REG_FIELD_WR(SYSC_AWO_CFG->UART811_TX_MULTIPLEX_SEL, SYSC_AWO_UART11_TX_MULTIPLEX_SEL, 0xb);
    REG_FIELD_WR(SYSC_AWO_CFG->UART811_RX_MULTIPLEX_SEL, SYSC_AWO_UART11_RX_MULTIPLEX_SEL, 0xb);
}

void pinmux_dwuart11_deinit(void)
{
    per_func3_disable(pin2func_io(&dwuart11_txd));
    per_func3_disable(pin2func_io(&dwuart11_rxd));
}

void pinmux_dwuart12_init(uint16_t txd,uint16_t rxd)
{
    memcpy(&dwuart12_txd, &txd, sizeof(uint16_t));
    memcpy(&dwuart12_rxd, &rxd, sizeof(uint16_t));
    dwuart_io_cfg(txd,rxd);
    per_func1_enable(txd);
    per_func1_enable(rxd);
    REG_FIELD_WR(SYSC_AWO_CFG->UART1231_TX_MULTIPLEX_SEL, SYSC_AWO_UART12_TX_MULTIPLEX_SEL, 0xc);
    REG_FIELD_WR(SYSC_AWO_CFG->UART12_RX_MULTIPLEX_SEL, SYSC_AWO_UART12_RX_MULTIPLEX_SEL, 0xc);
}

void pinmux_dwuart12_deinit(void)
{
    per_func1_disable(pin2func_io(&dwuart12_txd));
    per_func1_disable(pin2func_io(&dwuart12_rxd));
}