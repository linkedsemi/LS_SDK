#include <stddef.h>
#include "ls_soc_gpio.h"
#include "field_manipulate.h"
#include "per_func_mux.h"
#include "lm3050.h"
#include "platform.h"
#include "reg_v33_rg_type.h"
#include "reg_sysc_per_type.h"
#include "reg_sysc_awo_type.h"
#include "reg_exti_type.h"
#include "ls_dbg.h"
#include "compile_flag.h"

gpio_pin_t uart1_txd;
gpio_pin_t uart1_rxd;
gpio_pin_t uart1_ctsn;
gpio_pin_t uart1_rtsn;
gpio_pin_t uart1_ck;

gpio_pin_t uart2_txd;
gpio_pin_t uart2_rxd;
gpio_pin_t uart3_txd;
gpio_pin_t uart3_rxd;
gpio_pin_t uart4_txd;
gpio_pin_t uart4_rxd;
gpio_pin_t uart5_txd;
gpio_pin_t uart5_rxd;

gpio_pin_t iic1_scl;
gpio_pin_t iic1_sda;
gpio_pin_t iic2_scl;
gpio_pin_t iic2_sda;
gpio_pin_t iic3_sda;
gpio_pin_t iic3_scl;

static gpio_pin_t adtim1_ch1;
static gpio_pin_t adtim1_ch1n;
static gpio_pin_t adtim1_ch2;
static gpio_pin_t adtim1_ch2n;
static gpio_pin_t adtim1_ch3;
static gpio_pin_t adtim1_ch3n;
static gpio_pin_t adtim1_ch4;
static gpio_pin_t adtim1_etr;
static gpio_pin_t adtim1_bk;

static gpio_pin_t adtim2_ch1;
static gpio_pin_t adtim2_ch1n;
static gpio_pin_t adtim2_ch2;
static gpio_pin_t adtim2_ch2n;
static gpio_pin_t adtim2_ch3;
static gpio_pin_t adtim2_ch3n;
static gpio_pin_t adtim2_ch4;
static gpio_pin_t adtim2_etr;
static gpio_pin_t adtim2_bk;

static gpio_pin_t gptima1_ch1;
static gpio_pin_t gptima1_ch2;
static gpio_pin_t gptima1_ch3;
static gpio_pin_t gptima1_ch4;
static gpio_pin_t gptima1_etr;

static gpio_pin_t gptimb1_ch1;
static gpio_pin_t gptimb1_ch2;
static gpio_pin_t gptimb1_ch3;
static gpio_pin_t gptimb1_ch4;
static gpio_pin_t gptimb1_etr;

static gpio_pin_t gptimc1_ch1;
static gpio_pin_t gptimc1_ch1n;
static gpio_pin_t gptimc1_ch2;
static gpio_pin_t gptimc1_bk;

static gpio_pin_t pdm_clk;
static gpio_pin_t pdm_data0;
static gpio_pin_t pdm_data1;

static gpio_pin_t spi2_clk;
static gpio_pin_t spi2_nss;
static gpio_pin_t spi2_mosi;
static gpio_pin_t spi2_miso;
static gpio_pin_t spi3_clk;
static gpio_pin_t spi3_nss;
static gpio_pin_t spi3_mosi;
static gpio_pin_t spi3_miso;
static gpio_pin_t i2s2_ck;
static gpio_pin_t i2s2_ws;
static gpio_pin_t i2s2_sd;
static gpio_pin_t i2s2_mck;
static gpio_pin_t i2s3_ck;
static gpio_pin_t i2s3_ws;
static gpio_pin_t i2s3_sd;
static gpio_pin_t i2s3_mck;
/* ssi io init */
static gpio_pin_t ssi_clk;
static gpio_pin_t ssi_nss0;
static gpio_pin_t ssi_nss1;
static gpio_pin_t ssi_dq0;
static gpio_pin_t ssi_dq1;
static gpio_pin_t ssi_dq2;
static gpio_pin_t ssi_dq3;

static gpio_pin_t bxcan_txd;
static gpio_pin_t bxcan_rxd;
static gpio_pin_t usb_dp;
static gpio_pin_t usb_dm;
static gpio_pin_t comp1_dat;
static gpio_pin_t comp2_dat;
static gpio_pin_t comp3_dat;

__attribute__((weak)) void io_exti_callback(uint8_t pin,exti_edge_t edge){}

static inline uint8_t v33_ext_group_sel_get(uint8_t group)
{
    return V33_RG->GPIO_SEL>>(2*group) & 0x1;
}

void V33_EXTI_Async_Handler(void)
{
    uint8_t i;
    uint32_t int_stat = V33_RG->GPIO_INTR;
    for(i=0;i<8;i++)
    {
        exti_edge_t edge = INT_EDGE_DISABLE;
        if (1<<i & int_stat)
        {
            V33_RG->EXTI_CTRL2 = 1<<i;
            edge |= INT_EDGE_RISING;
        }
        if(1<<(i+8) & int_stat)
        {
            V33_RG->EXTI_CTRL2 = 1<<(i+8);
            edge |= INT_EDGE_FALLING;
        }
        if(edge)
        {
            V33_RG->EXTI_CTRL2 = 0;
            uint8_t pin_sel = v33_ext_group_sel_get(i);
            switch(i)
            {
            case 0:
                io_exti_callback(pin_sel ? PC01: PA00,edge);
            break;
            case 1:
                io_exti_callback(pin_sel ? PC02: PA01,edge);
            break;
            case 2:
                io_exti_callback(pin_sel ? PC03: PA02,edge);
            break;
            case 3:
                io_exti_callback(pin_sel ? PC13: PC00,edge);
            break;
            case 4:
                io_exti_callback(pin_sel ? PB06: PA14,edge);
            break;
            case 5:
                io_exti_callback(pin_sel ? PB07: PC11,edge);
            break;
            case 6:
                io_exti_callback(pin_sel ? PB08: PB04,edge);
            break;
            case 7:
                io_exti_callback(pin_sel ? PB09: PB05,edge);
            break;
            }
        }
    }
}

static void exti_io_handler(uint8_t port,uint8_t num)
{
    uint8_t pin = port<<4 | num;
    EXTI->EICR = 1<<num;
    io_exti_callback(pin,INT_EDGE_UNKNOWN);
}


void EXTI_Handler(void)
{
    uint16_t int_stat = EXTI->EEIFM;
    uint8_t i;
    uint8_t port;
    for(i=0;i<8;++i)
    {
        if(1<<i & int_stat)
        {
            port = EXTI->EICFG0 >> (4*i);
            exti_io_handler(port,i);
        }
    }
    for(i=8;i<16;++i)
    {
        if(1<<i & int_stat)
        {
            port = EXTI->EICFG1 >> (4*(i-8));
            exti_io_handler(port,i);
        }
    }
}

void io_irq_enable()
{
    __NVIC_EnableIRQ(EXTI_ASYNC_IRQn);
    __NVIC_EnableIRQ(EXTI_IRQn);
}

void io_init(void)
{
    SYSC_AWO->IO[0].IEN_OD = 0x9fff0000;
    SYSC_AWO->IO[0].OE_DOT= 0;
    SYSC_AWO->IO[0].PUPD = 0x60000000;
    SYSC_AWO->IO[1].IEN_OD = 0xffff0000;
    SYSC_AWO->IO[1].OE_DOT = 0;
    SYSC_AWO->IO[2].IEN_OD = 0xffff0000;
    SYSC_AWO->IO[2].OE_DOT = 0;
    SYSC_AWO->IO[3].IEN_OD = 0x03ff0000;
    SYSC_AWO->IO[3].OE_DOT = 0;
    SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_SET_EXTI_MASK;
    arm_cm_set_int_isr(EXTI_ASYNC_IRQn,V33_EXTI_Async_Handler);
    arm_cm_set_int_isr(EXTI_IRQn,EXTI_Handler);
    __NVIC_ClearPendingIRQ(EXTI_ASYNC_IRQn);
    __NVIC_ClearPendingIRQ(EXTI_IRQn);
    io_irq_enable();
}


void io_cfg_output(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    SYSC_AWO->IO[x->port].OE_DOT |= 1<<16<<x->num;
}

void io_cfg_input(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    SYSC_AWO->IO[x->port].OE_DOT &= ~(1<<16<<x->num);
    SYSC_AWO->IO[x->port].IEN_OD &= ~(1<<16<<x->num); 
}

void io_cfg_disable(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    SYSC_AWO->IO[x->port].OE_DOT &= ~(1<<16<<x->num);
    SYSC_AWO->IO[x->port].IEN_OD |= 1<<16<<x->num; 
}

void io_write_pin(uint8_t pin,uint8_t val)
{
    if(val)
    {
        io_set_pin(pin);
    }else
    {
        io_clr_pin(pin);
    }
}

void io_set_pin(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    *PERI_BIT_BAND_ADDR(&SYSC_AWO->IO[x->port].OE_DOT,x->num) = 1;
}

void io_clr_pin(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    *PERI_BIT_BAND_ADDR(&SYSC_AWO->IO[x->port].OE_DOT,x->num) = 0;
}

void io_toggle_pin(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    if(SYSC_AWO->IO[x->port].OE_DOT >> x->num & 0x1)
    {
        *PERI_BIT_BAND_ADDR(&SYSC_AWO->IO[x->port].OE_DOT,x->num) = 0;
    }else
    {
        *PERI_BIT_BAND_ADDR(&SYSC_AWO->IO[x->port].OE_DOT,x->num) = 1;
    }
}

uint8_t io_get_output_val(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    return SYSC_AWO->IO[x->port].OE_DOT >> x->num & 0x1;
}

uint8_t io_read_pin(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    return SYSC_AWO->IO[x->port].DIN >> x->num & 0x1;
}

void io_pull_write(uint8_t pin,io_pull_type_t pull)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    switch(pull)
    {
    case IO_PULL_DISABLE:
        SYSC_AWO->IO[x->port].PUPD &= ~(1<<16<<x->num | 1<<x->num);
    break;
    case IO_PULL_UP:
        MODIFY_REG(SYSC_AWO->IO[x->port].PUPD,1<<16<<x->num,1<<x->num);
    break;
    case IO_PULL_DOWN:
        MODIFY_REG(SYSC_AWO->IO[x->port].PUPD,1<<x->num,1<<16<<x->num);
    break;
    case IO_PULL_UP_DOWN:
        SYSC_AWO->IO[x->port].PUPD |= 1<<16<<x->num | 1<<x->num;
    break;
    }
}

static inline io_pull_type_t pull_down(uint8_t port,uint8_t num)
{
    if((SYSC_AWO->IO[port].PUPD>>num)&0x1)
    {
        return IO_PULL_DOWN;
    }else
    {
        return IO_PULL_DISABLE;
    }
}

static inline io_pull_type_t pull_up(uint8_t port,uint8_t num)
{
    if((SYSC_AWO->IO[port].PUPD>>num>>16)&0x1)
    {
        return IO_PULL_UP;
    }else
    {
        return IO_PULL_DISABLE;
    }
}

io_pull_type_t io_pull_read(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    return pull_down(x->port,x->num)|pull_up(x->port,x->num);
}

void io_drive_capacity_write(uint8_t pin, io_drive_type_t drive)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    MODIFY_REG(SYSC_AWO->IO[x->port].DS, SYSC_AWO_GPIOA_DS2_MASK << 2*x->num, drive << 2*x->num);
}

io_drive_type_t io_drive_capacity_read(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    io_drive_type_t drive = (io_drive_type_t)((SYSC_AWO->IO[x->port].DS >> 2 * x->num) & SYSC_AWO_GPIOA_DS2_MASK);
    return drive;
}

static void v33_ext_intr_mask(uint8_t group,exti_edge_t edge)
{
    switch(edge)
    {
    case INT_EDGE_DISABLE:
        V33_RG->EXTI_CTRL0 &= ~(1<<group | 1<<8<<group);
    break;
    case INT_EDGE_RISING:
        V33_RG->EXTI_CTRL2 = 1<<group;
        MODIFY_REG(V33_RG->EXTI_CTRL0,1<<8<<group,1<<group);
    break;
    case INT_EDGE_FALLING:
        V33_RG->EXTI_CTRL2 = 1<<8<<group;
        MODIFY_REG(V33_RG->EXTI_CTRL0,1<<group,1<<8<<group);
    break;
    case INT_EDGE_BOTH:
        V33_RG->EXTI_CTRL2 = 1<<group | (1<<8<<group);
        V33_RG->EXTI_CTRL0 |= 1<<group | (1<<8<<group);
    break;
    default:break;
    }
    V33_RG->EXTI_CTRL2 = 0;
}

static inline void v33_ext_group_sel_set(uint8_t group,uint8_t sel)
{
    if(sel)
    {
        V33_RG->GPIO_SEL |= 1<<(2*group);
    }else
    {
        V33_RG->GPIO_SEL &= ~(1<<(2*group));
    }
}

void io_exti_config(uint8_t pin,exti_edge_t edge)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    bool v33_wkup = true;
    switch(pin)
    {
    case PA00:
        v33_ext_group_sel_set(0,0);
        v33_ext_intr_mask(0,edge);
    break;
    case PC01:
        v33_ext_group_sel_set(0,1);
        v33_ext_intr_mask(0,edge);
    break;
    case PA01:
        v33_ext_group_sel_set(1,0);
        v33_ext_intr_mask(1,edge);
    break;
    case PC02:
        v33_ext_group_sel_set(1,1);
        v33_ext_intr_mask(1,edge);
    break;
    case PA02:
        v33_ext_group_sel_set(2,0);
        v33_ext_intr_mask(2,edge);
    break;
    case PC03:
        v33_ext_group_sel_set(2,1);
        v33_ext_intr_mask(2,edge);
    break;
    case PC00:
        v33_ext_group_sel_set(3,0);
        v33_ext_intr_mask(3,edge);
    break;
    case PC13:
        v33_ext_group_sel_set(3,1);
        v33_ext_intr_mask(3,edge);
    break;
    case PA14:
        v33_ext_group_sel_set(4,0);
        v33_ext_intr_mask(4,edge);
    break;
    case PB06:
        v33_ext_group_sel_set(4,1);
        v33_ext_intr_mask(4,edge);
    break;
    case PC11:
        v33_ext_group_sel_set(5,0);
        v33_ext_intr_mask(5,edge);
    break;
    case PB07:
        v33_ext_group_sel_set(5,1);
        v33_ext_intr_mask(5,edge);
    break;
    case PB04:
        v33_ext_group_sel_set(6,0);
        v33_ext_intr_mask(6,edge);
    break;
    case PB08:
        v33_ext_group_sel_set(6,1);
        v33_ext_intr_mask(6,edge);
    break;
    case PB05:
        v33_ext_group_sel_set(7,0);
        v33_ext_intr_mask(7,edge);
    break;
    case PB09:
        v33_ext_group_sel_set(7,1);
        v33_ext_intr_mask(7,edge);
    break;
    default:
        v33_wkup = false;
    break;
    }
    if(v33_wkup == false)
    {
        if(x->num <= 7)
        {
            MODIFY_REG(EXTI->EICFG0, 0xf<< 4 * x->num,x->port << 4 * x->num);
        }else
        {
            MODIFY_REG(EXTI->EICFG1, 0xf<< 4 * (x->num - 8),x->port << 4 * (x->num - 8));
        }
        switch(edge)
        {
        case INT_EDGE_DISABLE:
            EXTI->EIDR = 1 << x->num;
            EXTI->ERTS &= ~(1<<x->num);
            EXTI->EFTS &= ~(1<<x->num);
        break;
        case INT_EDGE_RISING:
            EXTI->ERTS |= 1 << x->num;
            EXTI->EFTS &= ~(1<<x->num);
            EXTI->EICR = 1 << x->num;
            EXTI->EIER = 1 << x->num;
        break;
        case INT_EDGE_FALLING:
            EXTI->ERTS &= ~(1<<x->num);
            EXTI->EFTS |= 1 << x->num;
            EXTI->EICR = 1 << x->num;
            EXTI->EIER = 1 << x->num;
        break;
        case INT_EDGE_BOTH:
            EXTI->ERTS |= 1 << x->num;
            EXTI->EFTS |= 1 << x->num;
            EXTI->EICR = 1 << x->num;
            EXTI->EIER = 1 << x->num;
        break;
        default:break;
        }
    }
}

static void uart_io_cfg(uint8_t txd,uint8_t rxd)
{
    io_set_pin(txd);
    io_cfg_output(txd);
    io_cfg_input(rxd);
}

static void uart_7816_io_cfg(uint8_t txd,uint8_t ck)
{
    io_set_pin(txd);
    io_set_pin(ck);
    io_cfg_opendrain(txd);
    io_cfg_output(txd);
    io_cfg_output(ck);
}

static uint8_t pin2func_io(gpio_pin_t *x)
{
    return x->port*16+x->num;
}

static void per_func_enable(uint8_t func_io_num,uint8_t per_func)
{
    MODIFY_REG(SYSC_PER->FUNC_SEL[func_io_num/4],0xff<<8*(func_io_num%4),per_func<<8*(func_io_num%4));
    if(func_io_num >= 32)
    {
        SYSC_AWO->PIN_SEL2 |= 1<<(func_io_num-32);
    }else
    {
        SYSC_AWO->PIN_SEL1 |= 1<<func_io_num;
    }

}

static void per_func_disable(uint8_t func_io_num)
{
    if(func_io_num >= 32)
    {
        SYSC_AWO->PIN_SEL2 &= ~(1<<(func_io_num-32));
    }else
    {
        SYSC_AWO->PIN_SEL1 &= ~(1<<func_io_num);
    }
}

static void iic_io_cfg(uint8_t scl,uint8_t sda)
{
    io_cfg_input(scl);
    io_cfg_input(sda);
    io_pull_write(scl,IO_PULL_UP);
    io_pull_write(sda,IO_PULL_UP);
}

void pinmux_iic1_init(uint8_t scl,uint8_t sda)
{
    *(uint8_t *)&iic1_scl = scl;
    *(uint8_t *)&iic1_sda = sda;
    iic_io_cfg(scl,sda);
    per_func_enable(pin2func_io((gpio_pin_t *)&scl), IIC1_SCL);
    per_func_enable(pin2func_io((gpio_pin_t *)&sda), IIC1_SDA);
}

void pinmux_iic1_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&iic1_scl));
    per_func_disable(pin2func_io((gpio_pin_t *)&iic1_sda));
}

void pinmux_iic2_init(uint8_t scl,uint8_t sda)  
{
    *(uint8_t *)&iic2_scl = scl;
    *(uint8_t *)&iic2_sda = sda;
    iic_io_cfg(scl,sda);
    per_func_enable(pin2func_io((gpio_pin_t *)&scl), IIC2_SCL);
    per_func_enable(pin2func_io((gpio_pin_t *)&sda), IIC2_SDA);
}

void pinmux_iic2_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&iic2_scl));
    per_func_disable(pin2func_io((gpio_pin_t *)&iic2_sda));
}

void pinmux_iic3_init(uint8_t scl,uint8_t sda)  
{
    *(uint8_t *)&iic3_scl = scl;
    *(uint8_t *)&iic3_sda = sda;
    iic_io_cfg(scl,sda);
    per_func_enable(pin2func_io((gpio_pin_t *)&scl), IIC3_SCL);
    per_func_enable(pin2func_io((gpio_pin_t *)&sda), IIC3_SDA);
}

void pinmux_iic3_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&iic3_scl));
    per_func_disable(pin2func_io((gpio_pin_t *)&iic3_sda));
}

void io_cfg_opendrain(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    SYSC_AWO->IO[x->port].IEN_OD |= 1<<x->num;
}

void io_cfg_pushpull(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    SYSC_AWO->IO[x->port].IEN_OD &=~(1<<x->num);
}

void pinmux_uart1_7816_init(uint8_t txd,uint8_t ck)
{
    *(uint8_t *)&uart1_txd = txd;
    *(uint8_t *)&uart1_ck = ck;
    uart_7816_io_cfg(txd,ck);
    per_func_enable(pin2func_io((gpio_pin_t *)&txd),UART1_TXD);
    per_func_enable(pin2func_io((gpio_pin_t *)&ck),UART1_CK);
}

void pinmux_uart1_7816_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&uart1_txd));
    per_func_disable(pin2func_io((gpio_pin_t *)&uart1_ck));
}

void pinmux_uart1_init(uint8_t txd,uint8_t rxd)
{
    *(uint8_t *)&uart1_txd = txd;
    *(uint8_t *)&uart1_rxd = rxd;
    uart_io_cfg(txd,rxd);
    per_func_enable(pin2func_io((gpio_pin_t *)&txd),UART1_TXD);
    per_func_enable(pin2func_io((gpio_pin_t *)&rxd),UART1_RXD);
}

void pinmux_uart1_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&uart1_txd));
    per_func_disable(pin2func_io((gpio_pin_t *)&uart1_rxd));
}

void pinmux_uart1_rts_cts_init(uint8_t rtsn,uint8_t ctsn)
{
    *(uint8_t *)&uart1_rtsn = rtsn;
    *(uint8_t *)&uart1_ctsn = ctsn;
    uart_io_cfg(rtsn,ctsn);
    per_func_enable(pin2func_io((gpio_pin_t *)&rtsn),UART1_RTSN);
    per_func_enable(pin2func_io((gpio_pin_t *)&ctsn),UART1_CTSN);
}

void pinmux_uart1_rts_cts_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&uart1_rtsn));
    per_func_disable(pin2func_io((gpio_pin_t *)&uart1_ctsn));
}

void pinmux_uart2_init(uint8_t txd,uint8_t rxd)
{
    *(uint8_t *)&uart2_txd = txd;
    *(uint8_t *)&uart2_rxd = rxd;
    uart_io_cfg(txd,rxd);
    per_func_enable(pin2func_io((gpio_pin_t *)&txd),UART2_TXD);
    per_func_enable(pin2func_io((gpio_pin_t *)&rxd),UART2_RXD);
}

void pinmux_uart2_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&uart2_txd));
    per_func_disable(pin2func_io((gpio_pin_t *)&uart2_rxd));
}

void pinmux_uart3_init(uint8_t txd,uint8_t rxd)
{
    *(uint8_t *)&uart3_txd = txd;
    *(uint8_t *)&uart3_rxd = rxd;
    uart_io_cfg(txd,rxd);
    per_func_enable(pin2func_io((gpio_pin_t *)&txd),UART3_TXD);
    per_func_enable(pin2func_io((gpio_pin_t *)&rxd),UART3_RXD);
}

void pinmux_uart3_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&uart3_txd));
    per_func_disable(pin2func_io((gpio_pin_t *)&uart3_rxd));
}

void pinmux_uart4_init(uint8_t txd,uint8_t rxd)
{
    *(uint8_t *)&uart4_txd = txd;
    *(uint8_t *)&uart4_rxd = rxd;
    uart_io_cfg(txd,rxd);
    per_func_enable(pin2func_io((gpio_pin_t *)&txd),UART4_TXD);
    per_func_enable(pin2func_io((gpio_pin_t *)&rxd),UART4_RXD);
}

void pinmux_uart4_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&uart4_txd));
    per_func_disable(pin2func_io((gpio_pin_t *)&uart4_rxd));
}

void pinmux_uart5_init(uint8_t txd,uint8_t rxd)
{
    *(uint8_t *)&uart5_txd = txd;
    *(uint8_t *)&uart5_rxd = rxd;
    uart_io_cfg(txd,rxd);
    per_func_enable(pin2func_io((gpio_pin_t *)&txd),UART5_TXD);
    per_func_enable(pin2func_io((gpio_pin_t *)&rxd),UART5_RXD);
}

void pinmux_uart5_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&uart5_txd));
    per_func_disable(pin2func_io((gpio_pin_t *)&uart5_rxd));
}

static void timer_ch_io_output_cfg(uint8_t pin,uint8_t default_val)
{
    io_write_pin(pin, default_val);
    io_cfg_output(pin);
}

static void timer_ch_io_cfg(uint8_t pin,bool output,uint8_t default_val)
{
    if(output)
    {
        timer_ch_io_output_cfg(pin,default_val);
    }else
    {
        io_cfg_input(pin);
    }
}

void pinmux_adtim1_ch1_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&adtim1_ch1 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_CH1);
}

void set_gpio_mode(gpio_pin_t *pin)
{
    per_func_disable(pin2func_io(pin));
}

void pinmux_adtim1_ch1_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_ch1);
}

void pinmux_adtim1_ch2_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&adtim1_ch2 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_CH2);
}

void pinmux_adtim1_ch2_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_ch2);
}

void pinmux_adtim1_ch3_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&adtim1_ch3 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_CH3);
}

void pinmux_adtim1_ch3_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_ch3);
}

void pinmux_adtim1_ch4_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&adtim1_ch4 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_CH4);
}

void pinmux_adtim1_ch4_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_ch4);
}

void pinmux_adtim1_ch1n_init(uint8_t pin)
{
    *(uint8_t *)&adtim1_ch1n = pin;
    timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim1_ch1));
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_CH1N);
}

void pinmux_adtim1_ch1n_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_ch1n);
}

void pinmux_adtim1_ch2n_init(uint8_t pin)
{
    *(uint8_t *)&adtim1_ch2n = pin;
    timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim1_ch2));
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_CH2N);
}

void pinmux_adtim1_ch2n_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_ch2n);
}

void pinmux_adtim1_ch3n_init(uint8_t pin)
{
    *(uint8_t *)&adtim1_ch3n = pin;
    timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim1_ch3));
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_CH3N);
}

void pinmux_adtim1_ch3n_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_ch3n);
}

void pinmux_adtim1_etr_init(uint8_t pin)
{
    *(uint8_t *)&adtim1_etr = pin;
    io_cfg_input(pin);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_ETR);
}

void pinmux_adtim1_etr_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_etr);
}

void pinmux_adtim1_bk_init(uint8_t pin)
{
    *(uint8_t *)&adtim1_bk = pin;
    io_cfg_input(pin);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_BK);
}

void pinmux_adtim1_bk_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_bk);
}


void pinmux_adtim2_ch1_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&adtim2_ch1 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM2_CH1);
}

void pinmux_adtim2_ch1_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim2_ch1);
}

void pinmux_adtim2_ch2_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&adtim2_ch2 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM2_CH2);
}

void pinmux_adtim2_ch2_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim2_ch2);
}

void pinmux_adtim2_ch3_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&adtim2_ch3 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM2_CH3);
}

void pinmux_adtim2_ch3_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim2_ch3);
}

void pinmux_adtim2_ch4_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&adtim2_ch4 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM2_CH4);
}

void pinmux_adtim2_ch4_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim2_ch4);
}

void pinmux_adtim2_ch1n_init(uint8_t pin)
{
    *(uint8_t *)&adtim1_ch1n = pin;
    timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim2_ch1));
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM2_CH1N);
}

void pinmux_adtim2_ch1n_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim2_ch1n);
}

void pinmux_adtim2_ch2n_init(uint8_t pin)
{
    *(uint8_t *)&adtim1_ch2n = pin;
    timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim2_ch2));
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM2_CH2N);
}

void pinmux_adtim2_ch2n_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim2_ch2n);
}

void pinmux_adtim2_ch3n_init(uint8_t pin)
{
    *(uint8_t *)&adtim2_ch3n = pin;
    timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim2_ch3));
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM2_CH3N);
}

void pinmux_adtim2_ch3n_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim2_ch3n);
}

void pinmux_adtim2_etr_init(uint8_t pin)
{
    *(uint8_t *)&adtim2_etr = pin;
    io_cfg_input(pin);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM2_ETR);
}

void pinmux_adtim2_etr_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim2_etr);
}

void pinmux_adtim2_bk_init(uint8_t pin)
{
    *(uint8_t *)&adtim2_bk = pin;
    io_cfg_input(pin);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM2_BK);
}

void pinmux_adtim2_bk_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim2_bk);
}

void pinmux_gptima1_ch1_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptima1_ch1 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMA1_CH1);
}

void pinmux_gptima1_ch1_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptima1_ch1);
}

void pinmux_gptima1_ch2_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptima1_ch2 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMA1_CH2);
}

void pinmux_gptima1_ch2_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptima1_ch2);
}

void pinmux_gptima1_ch3_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptima1_ch3 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMA1_CH3);
}

void pinmux_gptima1_ch3_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptima1_ch3);
}

void pinmux_gptima1_ch4_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptima1_ch4 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMA1_CH4);
}

void pinmux_gptima1_ch4_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptima1_ch4);
}

void pinmux_gptima1_etr_init(uint8_t pin)
{
    *(uint8_t *)&gptima1_etr = pin;
    io_cfg_input(pin);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMA1_ETR);
}

void pinmux_gptima1_etr_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptima1_etr);
}

void pinmux_gptimb1_ch1_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimb1_ch1 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMB1_CH1);
}

void pinmux_gptimb1_ch1_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptimb1_ch1);
}

void pinmux_gptimb1_ch2_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimb1_ch2 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMB1_CH2);
}

void pinmux_gptimb1_ch2_deinit(void)

{
    set_gpio_mode((gpio_pin_t *)&gptimb1_ch2);
}

void pinmux_gptimb1_ch3_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimb1_ch3 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMB1_CH3);
}

void pinmux_gptimb1_ch3_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptimb1_ch3);
}

void pinmux_gptimb1_ch4_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimb1_ch4 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMB1_CH4);
}

void pinmux_gptimb1_ch4_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptimb1_ch4);
}

void pinmux_gptimb1_etr_init(uint8_t pin)
{
    *(uint8_t *)&gptimb1_etr = pin;
    io_cfg_input(pin);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMB1_ETR);
}

void pinmux_gptimb1_etr_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptimb1_etr);
}

void pinmux_gptimc1_ch1_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimc1_ch1 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMC1_CH1);
}

void pinmux_gptimc1_ch1_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptimc1_ch1);
}

void pinmux_gptimc1_ch1n_init(uint8_t pin)
{
    *(uint8_t *)&gptimc1_ch1n = pin;
    timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&gptimc1_ch1));
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMC1_CH1N);
}

void pinmux_gptimc1_ch1n_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptimc1_ch1n);
}

void pinmux_gptimc1_ch2_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimc1_ch2 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMC1_CH2);
}

void pinmux_gptimc1_ch2_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptimc1_ch2);
}

void pinmux_gptimc1_bk_init(uint8_t pin)
{
    *(uint8_t *)&gptimc1_bk = pin;
    io_cfg_input(pin);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMC1_BK);
}

void pinmux_gptimc1_bk_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptimc1_bk);
}

void pinmux_pdm_clk_init(uint8_t pin)
{
    *(uint8_t *)&pdm_clk = pin;
    io_cfg_output(pin);
    per_func_enable(pin2func_io((gpio_pin_t *)&pdm_clk), PDM_CLK);
}

void pinmux_pdm_clk_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&pdm_clk);
}

void pinmux_pdm_data0_init(uint8_t pin)
{
    *(uint8_t *)&pdm_data0 = pin;
    io_cfg_input(pin);
    per_func_enable(pin2func_io((gpio_pin_t *)&pdm_data0), PDM_DATA0);
}

void pinmux_pdm_data0_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&pdm_data0);
}

void pinmux_pdm_data1_init(uint8_t pin)
{
    *(uint8_t *)&pdm_data1 = pin;
    io_cfg_input(pin);
    per_func_enable(pin2func_io((gpio_pin_t *)&pdm_data1), PDM_DATA1);
}

void pinmux_pdm_data1_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&pdm_data1);
}

ROM_SYMBOL void pinmux_hal_flash_init(void)
{
    REG_FIELD_WR(SYSC_AWO->PIN_SEL0,SYSC_AWO_QSPI_EN,0xf); 
}

ROM_SYMBOL void pinmux_hal_flash_deinit(void)
{
    REG_FIELD_WR(SYSC_AWO->PIN_SEL0,SYSC_AWO_QSPI_EN,0x0);
}

ROM_SYMBOL void pinmux_hal_flash_quad_init(void)
{
    REG_FIELD_WR(SYSC_AWO->PIN_SEL0,SYSC_AWO_QSPI_EN,0x3f); 
}

ROM_SYMBOL void pinmux_hal_flash_quad_deinit(void)
{
    REG_FIELD_WR(SYSC_AWO->PIN_SEL0,SYSC_AWO_QSPI_EN,0x0);
}

static void spi_master_clk_io_cfg(uint8_t clk)
{
    io_clr_pin(clk);
    io_pull_write(clk,IO_PULL_DOWN);
    io_cfg_output(clk);
}

static void spi_master_nss_io_cfg(uint8_t nss)
{
    io_set_pin(nss);
    io_pull_write(nss,IO_PULL_UP);
    io_cfg_output(nss);
}

static void spi_master_mosi_io_cfg(uint8_t mosi)
{
    io_set_pin(mosi);
    io_cfg_output(mosi);
}

static void spi_master_miso_io_cfg(uint8_t miso)
{
    io_cfg_input(miso);
}

static void spi_slave_clk_io_cfg(uint8_t clk)
{
    io_cfg_input(clk);
}

static void spi_slave_nss_io_cfg(uint8_t nss)
{
    io_pull_write(nss,IO_PULL_UP);
    io_cfg_input(nss);
}

static void spi_slave_mosi_io_cfg(uint8_t mosi)
{
    io_cfg_input(mosi);
}

static void spi_slave_miso_io_cfg(uint8_t miso)
{
    io_set_pin(miso);
    io_cfg_output(miso);
}

static void iis_master_ck_io_cfg(uint8_t ck)
{
    io_clr_pin(ck);
    io_pull_write(ck,IO_PULL_DOWN);
    io_cfg_output(ck);
}

static void iis_master_ws_io_cfg(uint8_t ws)
{
    io_set_pin(ws);
    io_pull_write(ws,IO_PULL_UP);
    io_cfg_output(ws);
}

static void iis_master_sd_io_cfg(uint8_t sd, uint8_t mode)
{
    if (mode)
    {
        io_set_pin(sd);
        io_cfg_output(sd);
    }
    else 
    {
        io_cfg_input(sd);
    }
}

static void iis_master_mck_io_cfg(uint8_t mck)
{
    io_clr_pin(mck);
    io_pull_write(mck,IO_PULL_DOWN);
    io_cfg_output(mck);
}

static void iis_slave_ck_io_cfg(uint8_t ck)
{
    io_cfg_input(ck);
}

static void iis_slave_ws_io_cfg(uint8_t ws)
{
    io_pull_write(ws,IO_PULL_UP);
    io_cfg_input(ws);
}

static void iis_slave_sd_io_cfg(uint8_t sd, uint8_t mode)
{
    if (mode)
    {
        io_set_pin(sd);
        io_cfg_output(sd);
    }
    else 
    {
        io_cfg_input(sd);
    }
}

static void iis_slave_mck_io_cfg(uint8_t mck)
{
    io_cfg_input(mck);
}

void pinmux_spi2_master_clk_init(uint8_t clk)
{
    *(uint8_t *)&spi2_clk = clk;
    spi_master_clk_io_cfg( clk);
    per_func_enable(pin2func_io((gpio_pin_t *)&clk),SPI2_SCK);
}

void pinmux_spi2_master_nss_init(uint8_t nss)
{
    *(uint8_t *)&spi2_nss = nss;
    spi_master_nss_io_cfg( nss);
    per_func_enable(pin2func_io((gpio_pin_t *)&nss),SPI2_NSS);  
}

void pinmux_spi2_master_mosi_init(uint8_t mosi)
{
    *(uint8_t *)&spi2_mosi = mosi;
    spi_master_mosi_io_cfg( mosi);
    per_func_enable(pin2func_io((gpio_pin_t *)&mosi),SPI2_MOSI);
}

void pinmux_spi2_master_miso_init(uint8_t miso)
{
    *(uint8_t *)&spi2_miso = miso;
    spi_master_miso_io_cfg( miso);    
    per_func_enable(pin2func_io((gpio_pin_t *)&miso),SPI2_MISO);
}

void pinmux_spi2_slave_clk_init(uint8_t clk)
{
    *(uint8_t *)&spi2_clk = clk;
    spi_slave_clk_io_cfg( clk);
    per_func_enable(pin2func_io((gpio_pin_t *)&clk),SPI2_SCK);
}

void pinmux_spi2_slave_nss_init(uint8_t nss)
{
    *(uint8_t *)&spi2_nss = nss;
    spi_slave_nss_io_cfg( nss);
    per_func_enable(pin2func_io((gpio_pin_t *)&nss),SPI2_NSS);  
}

void pinmux_spi2_slave_mosi_init(uint8_t mosi)
{
    *(uint8_t *)&spi2_mosi = mosi;
    spi_slave_mosi_io_cfg( mosi);
    per_func_enable(pin2func_io((gpio_pin_t *)&mosi),SPI2_MOSI);
}

void pinmux_spi2_slave_miso_init(uint8_t miso)
{
    *(uint8_t *)&spi2_miso = miso;
    spi_slave_miso_io_cfg( miso);    
    per_func_enable(pin2func_io((gpio_pin_t *)&miso),SPI2_MISO);
}

void pinmux_spi2_clk_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&spi2_clk);
}

void pinmux_spi2_nss_deinit(void)
{
    io_pull_write(*(uint8_t *)&spi2_nss,IO_PULL_DISABLE);
    set_gpio_mode((gpio_pin_t *)&spi2_nss);
}

void pinmux_spi2_mosi_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&spi2_mosi);
}

void pinmux_spi2_miso_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&spi2_miso);
}

void pinmux_spi3_master_clk_init(uint8_t clk)
{
    *(uint8_t *)&spi3_clk = clk;
    spi_master_clk_io_cfg( clk);
    per_func_enable(pin2func_io((gpio_pin_t *)&clk),SPI3_SCK);
}

void pinmux_spi3_master_nss_init(uint8_t nss)
{
    *(uint8_t *)&spi3_nss = nss;
    spi_master_nss_io_cfg( nss);
    per_func_enable(pin2func_io((gpio_pin_t *)&nss),SPI3_NSS);  
}

void pinmux_spi3_master_mosi_init(uint8_t mosi)
{
    *(uint8_t *)&spi3_mosi = mosi;
    spi_master_mosi_io_cfg( mosi);
    per_func_enable(pin2func_io((gpio_pin_t *)&mosi),SPI3_MOSI);
}

void pinmux_spi3_master_miso_init(uint8_t miso)
{
    *(uint8_t *)&spi3_miso = miso;
    spi_master_miso_io_cfg( miso);    
    per_func_enable(pin2func_io((gpio_pin_t *)&miso),SPI3_MISO);
}

void pinmux_spi3_slave_clk_init(uint8_t clk)
{
    *(uint8_t *)&spi3_clk = clk;
    spi_slave_clk_io_cfg( clk);
    per_func_enable(pin2func_io((gpio_pin_t *)&clk),SPI3_SCK);
}

void pinmux_spi3_slave_nss_init(uint8_t nss)
{
    *(uint8_t *)&spi3_nss = nss;
    spi_slave_nss_io_cfg( nss);
    per_func_enable(pin2func_io((gpio_pin_t *)&nss),SPI3_NSS);  
}

void pinmux_spi3_slave_mosi_init(uint8_t mosi)
{
    *(uint8_t *)&spi3_mosi = mosi;
    spi_slave_mosi_io_cfg( mosi);
    per_func_enable(pin2func_io((gpio_pin_t *)&mosi),SPI3_MOSI);
}

void pinmux_spi3_slave_miso_init(uint8_t miso)
{
    *(uint8_t *)&spi3_miso = miso;
    spi_slave_miso_io_cfg( miso);    
    per_func_enable(pin2func_io((gpio_pin_t *)&miso),SPI3_MISO);
}

void pinmux_spi3_clk_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&spi3_clk);
}

void pinmux_spi3_nss_deinit(void)
{
    io_pull_write(*(uint8_t *)&spi3_nss,IO_PULL_DISABLE);
    set_gpio_mode((gpio_pin_t *)&spi3_nss);
}

void pinmux_spi3_mosi_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&spi3_mosi);
}

void pinmux_spi3_miso_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&spi3_miso);
}

void pinmux_iis2_master_ck_init(uint8_t ck)
{
    *(uint8_t *)&i2s2_ck = ck;
    iis_master_ck_io_cfg(ck);
    per_func_enable(pin2func_io((gpio_pin_t *)&ck),SPI2_SCK);
}

void pinmux_iis2_master_ws_init(uint8_t ws)
{
    *(uint8_t *)&i2s2_ws = ws;
    iis_master_ws_io_cfg(ws);
    per_func_enable(pin2func_io((gpio_pin_t *)&ws),SPI2_NSS);    
}

void pinmux_iis2_master_sd_init(uint8_t sd, uint8_t mode)
{
    *(uint8_t *)&i2s2_sd = sd;
    iis_master_sd_io_cfg(sd, mode);
    per_func_enable(pin2func_io((gpio_pin_t *)&sd),SPI2_MOSI);
}

void pinmux_iis2_master_mck_init(uint8_t mck)
{
    *(uint8_t *)&i2s2_mck = mck;
    iis_master_mck_io_cfg( mck);    
    per_func_enable(pin2func_io((gpio_pin_t *)&mck),SPI2_IIS);
}

void pinmux_iis2_slave_ck_init(uint8_t ck)
{
    *(uint8_t *)&i2s2_ck = ck;
    iis_slave_ck_io_cfg(ck);
    per_func_enable(pin2func_io((gpio_pin_t *)&ck),SPI2_SCK);
}

void pinmux_iis2_slave_ws_init(uint8_t ws)
{
    *(uint8_t *)&i2s2_ws = ws;
    iis_slave_ws_io_cfg(ws);
    per_func_enable(pin2func_io((gpio_pin_t *)&ws),SPI2_NSS);    
}

void pinmux_iis2_slave_sd_init(uint8_t sd, uint8_t mode)
{
    *(uint8_t *)&i2s2_sd = sd;
    iis_slave_sd_io_cfg(sd, mode);
    per_func_enable(pin2func_io((gpio_pin_t *)&sd),SPI2_MOSI);
}

void pinmux_iis2_slave_mck_init(uint8_t mck)
{
    *(uint8_t *)&i2s2_mck = mck;
    iis_slave_mck_io_cfg( mck);    
    per_func_enable(pin2func_io((gpio_pin_t *)&mck),SPI2_IIS);
}

void pinmux_iis2_ck_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&i2s2_ck);
}

void pinmux_iis2_ws_deinit(void)
{
    io_pull_write(*(uint8_t *)&i2s2_ws,IO_PULL_DISABLE);
    set_gpio_mode((gpio_pin_t *)&i2s2_ws);
}

void pinmux_iis2_sd_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&i2s2_sd);
}

void pinmux_iis2_mck_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&i2s2_mck);
}

void pinmux_iis3_master_ck_init(uint8_t ck)
{
    *(uint8_t *)&i2s3_ck = ck;
    iis_master_ck_io_cfg(ck);
    per_func_enable(pin2func_io((gpio_pin_t *)&ck),SPI3_SCK);
}

void pinmux_iis3_master_ws_init(uint8_t ws)
{
    *(uint8_t *)&i2s3_ws = ws;
    iis_master_ws_io_cfg(ws);
    per_func_enable(pin2func_io((gpio_pin_t *)&ws),SPI3_NSS);  
}

void pinmux_iis3_master_sd_init(uint8_t sd, uint8_t mode)
{
    *(uint8_t *)&i2s3_sd = sd;
    iis_master_sd_io_cfg(sd, mode);
    per_func_enable(pin2func_io((gpio_pin_t *)&sd),SPI3_MOSI);
}

void pinmux_iis3_master_mck_init(uint8_t mck)
{
    *(uint8_t *)&i2s3_mck = mck;
    iis_master_mck_io_cfg( mck);    
    per_func_enable(pin2func_io((gpio_pin_t *)&mck),SPI3_IIS);
}

void pinmux_iis3_slave_ck_init(uint8_t ck)
{
    *(uint8_t *)&i2s3_ck = ck;
    iis_slave_ck_io_cfg(ck);
    per_func_enable(pin2func_io((gpio_pin_t *)&ck),SPI3_SCK);
}

void pinmux_iis3_slave_ws_init(uint8_t ws)
{
    *(uint8_t *)&i2s3_ws = ws;
    iis_slave_ws_io_cfg(ws);
    per_func_enable(pin2func_io((gpio_pin_t *)&ws),SPI3_NSS);  
}

void pinmux_iis3_slave_sd_init(uint8_t sd, uint8_t mode)
{
    *(uint8_t *)&i2s3_sd = sd;
    iis_slave_sd_io_cfg(sd, mode);
    per_func_enable(pin2func_io((gpio_pin_t *)&sd),SPI3_MOSI);
}

void pinmux_iis3_slave_mck_init(uint8_t mck)
{
    *(uint8_t *)&i2s3_mck = mck;
    iis_slave_mck_io_cfg( mck);    
    per_func_enable(pin2func_io((gpio_pin_t *)&mck),SPI3_IIS);
}

void pinmux_iis3_ck_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&i2s3_ck);
}

void pinmux_iis3_ws_deinit(void)
{
    io_pull_write(*(uint8_t *)&i2s3_ws,IO_PULL_DISABLE);
    set_gpio_mode((gpio_pin_t *)&i2s3_ws);
}

void pinmux_iis3_sd_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&i2s3_sd);
}

void pinmux_iis3_mck_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&i2s3_mck);
}

void pinmux_ssi_clk_init(uint8_t clk) 
{
    *(uint8_t *)&ssi_clk = clk;
    spi_master_clk_io_cfg(clk);
    per_func_enable(pin2func_io((gpio_pin_t *)&clk),SPI1_SCK);
}

void pinmux_ssi_nss0_init(uint8_t nss0)
{
    *(uint8_t *)&ssi_nss0 = nss0;
    spi_master_nss_io_cfg(nss0);
    per_func_enable(pin2func_io((gpio_pin_t *)&nss0),SPI1_NSS0);
}

void pinmux_ssi_nss1_init(uint8_t nss1)
{
    *(uint8_t *)&ssi_nss1 = nss1;
    spi_master_nss_io_cfg(nss1);
    per_func_enable(pin2func_io((gpio_pin_t *)&nss1),SPI1_NSS0); 
}

void pinmux_ssi_dq0_init(uint8_t dq0)
{
    *(uint8_t *)&ssi_dq0 = dq0;
    spi_master_mosi_io_cfg(dq0);
    per_func_enable(pin2func_io((gpio_pin_t *)&dq0),SPI1_DQ0); 
}

void pinmux_ssi_dq1_init(uint8_t dq1)
{
    *(uint8_t *)&ssi_dq1 = dq1;
    spi_master_miso_io_cfg(dq1);
    per_func_enable(pin2func_io((gpio_pin_t *)&dq1), SPI1_DQ1);
}

void pinmux_ssi_dq2_init(uint8_t dq2)
{
    *(uint8_t *)&ssi_dq2 = dq2;
    spi_master_miso_io_cfg(dq2);
    per_func_enable(pin2func_io((gpio_pin_t *)&dq2), SPI1_DQ2);
}

void pinmux_ssi_dq3_init(uint8_t dq3)
{
    *(uint8_t *)&ssi_dq3 = dq3;
    spi_master_miso_io_cfg(dq3);
    per_func_enable(pin2func_io((gpio_pin_t *)&dq3), SPI1_DQ3);
}
void pinmux_ssi_deinit(void)
{
	set_gpio_mode((gpio_pin_t *)&ssi_clk);
	set_gpio_mode((gpio_pin_t *)&ssi_nss0);
	set_gpio_mode((gpio_pin_t *)&ssi_dq0);
	set_gpio_mode((gpio_pin_t *)&ssi_dq1);
}

void pinmux_ssi_clk_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&ssi_clk);
}

void pinmux_ssi_nss0_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&ssi_nss0);
}

void pinmux_ssi_nss1_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&ssi_nss1);
}

void pinmux_ssi_dq0_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&ssi_dq0);
}

void pinmux_ssi_dq1_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&ssi_dq1);
}

void pinmux_ssi_dq2_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&ssi_dq2);
}

void pinmux_ssi_dq3_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&ssi_dq3);
}

static void io_ae1_enable(uint8_t pin, uint8_t val)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    *PERI_BIT_BAND_ADDR(&SYSC_AWO->IO[x->port].AE, x->num + 16) = val;
}

void pinmux_touchkey_cmod_init()
{
    io_ae1_enable(PB03, 1);
}

void pinmux_touchkey_cmod_deinit()
{
    io_ae1_enable(PB03, 0);
}

void pinmux_touchkey_ch0_init()
{
    io_ae1_enable(PA08, 1);
}

void pinmux_touchkey_ch0_deinit()
{
    io_ae1_enable(PA08, 0);
}

void pinmux_touchkey_ch1_init()
{
    io_ae1_enable(PA09, 1);
}

void pinmux_touchkey_ch1_deinit()
{
    io_ae1_enable(PA09, 0);
}

void pinmux_touchkey_ch2_init()
{
    io_ae1_enable(PA10, 1);
}

void pinmux_touchkey_ch2_deinit()
{
    io_ae1_enable(PA10, 0);
}

void pinmux_touchkey_ch3_init()
{
    io_ae1_enable(PC11, 1);
}

void pinmux_touchkey_ch3_deinit()
{
    io_ae1_enable(PC11, 0);
}

void pinmux_touchkey_ch4_init()
{
    io_ae1_enable(PB04, 1);
}

void pinmux_touchkey_ch4_deinit()
{
    io_ae1_enable(PB04, 0);
}

void pinmux_touchkey_ch5_init()
{
    io_ae1_enable(PB05, 1);
}

void pinmux_touchkey_ch5_deinit()
{
    io_ae1_enable(PB05, 0);
}

void pinmux_touchkey_ch6_init()
{
    io_ae1_enable(PB06, 1);
}

void pinmux_touchkey_ch6_deinit()
{
    io_ae1_enable(PB06, 0);
}

void pinmux_touchkey_ch7_init()
{
    io_ae1_enable(PB07, 1);
}

void pinmux_touchkey_ch7_deinit()
{
    io_ae1_enable(PB07, 0);
}

void pinmux_touchkey_ch8_init()
{
    io_ae1_enable(PB08, 1);
}

void pinmux_touchkey_ch8_deinit()
{
    io_ae1_enable(PB08, 0);
}

void pinmux_touchkey_ch9_init()
{
    io_ae1_enable(PB09, 1);
}

void pinmux_touchkey_ch9_deinit()
{
    io_ae1_enable(PB09, 0);
}

void pinmux_touchkey_ch10_init()
{
    io_ae1_enable(PC06, 1);
}

void pinmux_touchkey_ch10_deinit()
{
    io_ae1_enable(PC06, 0);
}

void pinmux_touchkey_ch11_init()
{
    io_ae1_enable(PC07, 1);
}

void pinmux_touchkey_ch11_deinit()
{
    io_ae1_enable(PC07, 0);
}

void pinmux_touchkey_ch12_init()
{
    io_ae1_enable(PC08, 1);
}

void pinmux_touchkey_ch12_deinit()
{
    io_ae1_enable(PC08, 0);
}

void pinmux_touchkey_ch13_init()
{
    io_ae1_enable(PC09, 1);
}

void pinmux_touchkey_ch13_deinit()
{
    io_ae1_enable(PC09, 0);
}

void pinmux_touchkey_ch14_init()
{
    io_ae1_enable(PC12, 1);
}

void pinmux_touchkey_ch14_deinit()
{
    io_ae1_enable(PC12, 0);
}

void pinmux_touchkey_ch15_init()
{
    io_ae1_enable(PD02, 1);
}

void pinmux_touchkey_ch15_deinit()
{
    io_ae1_enable(PD02, 0);
}

void gpio_ana_func1_init(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    SYSC_AWO->IO[x->port].AE |= 1<<16<<x->num;
}

void gpio_ana_deinit(uint8_t ain)
{
    gpio_pin_t *x = (gpio_pin_t *)&ain;
    SYSC_AWO->IO[x->port].AE &= ~(1<<16<<x->num);
    io_cfg_disable(ain);
}

void gpio_ana_func2_init(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    SYSC_AWO->IO[x->port].AE |= 1<<x->num;
}

void gpio_ana_func2_deinit(uint8_t ain)
{
    gpio_pin_t *x = (gpio_pin_t *)&ain;
    SYSC_AWO->IO[x->port].AE &= ~(1<<x->num);
    io_cfg_disable(ain);
}

void pinmux_adc1_in0_init(void)
{
    gpio_ana_func1_init(PC00);
}

void pinmux_adc1_in0_deinit(void)
{
    gpio_ana_deinit(PC00);
}

void pinmux_adc1_in1_init(void)
{
    gpio_ana_func1_init(PC01);
}

void pinmux_adc1_in1_deinit(void)
{
    gpio_ana_deinit(PC01);
}

void pinmux_adc1_in2_init(void)
{
    gpio_ana_func1_init(PC02);
}

void pinmux_adc1_in2_deinit(void)
{
    gpio_ana_deinit(PC02);
}

void pinmux_adc1_in3_init(void)
{
    gpio_ana_func1_init(PC03);
}

void pinmux_adc1_in3_deinit(void)
{
    gpio_ana_deinit(PC03);
}

void pinmux_adc1_in4_init(void)
{
    gpio_ana_func1_init(PA00);
}

void pinmux_adc1_in4_deinit(void)
{
    gpio_ana_deinit(PA00);
}

void pinmux_adc1_in5_init(void)
{
    gpio_ana_func1_init(PA01);
}

void pinmux_adc1_in5_deinit(void)
{
    gpio_ana_deinit(PA01);
}

void pinmux_adc1_in6_init(void)
{
    gpio_ana_func1_init(PA02);
}

void pinmux_adc1_in6_deinit(void)
{
    gpio_ana_deinit(PA02);
}

void pinmux_adc1_in7_init(void)
{
    gpio_ana_func1_init(PA03);
}

void pinmux_adc1_in7_deinit(void)
{
    gpio_ana_deinit(PA03);
}

void pinmux_adc2_in0_init(void)
{
    gpio_ana_func1_init(PA04);
}

void pinmux_adc2_in0_deinit(void)
{
    gpio_ana_deinit(PA04);
}

void pinmux_adc2_in1_init(void)
{
    gpio_ana_func1_init(PA05);
}

void pinmux_adc2_in1_deinit(void)
{
    gpio_ana_deinit(PA05);
}

void pinmux_adc2_in2_init(void)
{
    gpio_ana_func1_init(PA06);
}

void pinmux_adc2_in2_deinit(void)
{
    gpio_ana_deinit(PA06);
}

void pinmux_adc2_in3_init(void)
{
    gpio_ana_func1_init(PA07);
}

void pinmux_adc2_in3_deinit(void)
{
    gpio_ana_deinit(PA07);
}

void pinmux_adc2_in4_init(void)
{
    gpio_ana_func1_init(PC04);
}

void pinmux_adc2_in4_deinit(void)
{
    gpio_ana_deinit(PC04);
}

void pinmux_adc2_in5_init(void)
{
    gpio_ana_func1_init(PC05);
}

void pinmux_adc2_in5_deinit(void)
{
    gpio_ana_deinit(PC05);
}

void pinmux_adc2_in6_init(void)
{
    gpio_ana_func1_init(PB00);
}

void pinmux_adc2_in6_deinit(void)
{
    gpio_ana_deinit(PB00);
}

void pinmux_adc2_in7_init(void)
{
    gpio_ana_func1_init(PB01);
}

void pinmux_adc2_in7_deinit(void)
{
    gpio_ana_deinit(PB01);
}

void pinmux_amic_init(void)
{
    gpio_ana_func1_init(PB10);
} 

void pinmux_amic_deinit(void)
{
    gpio_ana_deinit(PB10);
} 

void pinmux_dac1_init(void)
{
    gpio_ana_func2_init(PA07);
}

void pinmux_dac1_deinit(void)
{
    gpio_ana_func2_deinit(PA07);
}

void pinmux_dac2_init(void)
{
    gpio_ana_func2_init(PC04);
}

void pinmux_dac2_deinit(void)
{
    gpio_ana_func2_deinit(PC04);
}

void pinmux_bxcan_init(uint8_t txd,uint8_t rxd)
{
    *(uint8_t *)&bxcan_txd = txd;
    *(uint8_t *)&bxcan_rxd = rxd;
    uart_io_cfg(txd,rxd);
    per_func_enable(pin2func_io((gpio_pin_t *)&txd),BXCAN_TXD);
    per_func_enable(pin2func_io((gpio_pin_t *)&rxd),BXCAN_RXD);
}

void pinmux_bxcan_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&bxcan_txd));
    per_func_disable(pin2func_io((gpio_pin_t *)&bxcan_rxd));
}

static void usb_io_cfg(uint8_t dp,uint8_t dm)
{
    io_clr_pin(dp);
    io_clr_pin(dm);
    io_cfg_output(dp);
    io_cfg_output(dm);
}

void pinmux_usb_init(uint8_t dp,uint8_t dm)
{
    *(uint8_t *)&usb_dp = dp;
    *(uint8_t *)&usb_dm = dm;
    usb_io_cfg(dp,dm);
    per_func_enable(pin2func_io((gpio_pin_t *)&dp),USB_DP);
    per_func_enable(pin2func_io((gpio_pin_t *)&dm),USB_DM);
}

void pinmux_usb_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&usb_dp));
    per_func_disable(pin2func_io((gpio_pin_t *)&usb_dm));
}

static void  comp_io_cfg(uint8_t dat)
{
    io_clr_pin(dat);
    io_cfg_output(dat);
}

void pinmux_comp1_init(uint8_t dat)
{
    *(uint8_t *)&comp1_dat = dat;
    comp_io_cfg(dat);
    per_func_enable(pin2func_io((gpio_pin_t *)&dat),COMP1_DAT);
}

void pinmux_comp1_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&comp1_dat));
}

void pinmux_comp2_init(uint8_t dat)
{
    *(uint8_t *)&comp2_dat = dat;
    comp_io_cfg(dat);
    per_func_enable(pin2func_io((gpio_pin_t *)&dat),COMP2_DAT);
}

void pinmux_comp2_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&comp2_dat));
}

void pinmux_comp3_init(uint8_t dat)
{
    *(uint8_t *)&comp3_dat = dat;
    comp_io_cfg(dat);
    per_func_enable(pin2func_io((gpio_pin_t *)&dat),COMP3_DAT);
}

void pinmux_comp3_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&comp3_dat));
}

void pinmux_uart2_init(uint8_t txd,uint8_t rxd);
void pinmux_uart2_deinit(void);

void pinmux_uart3_init(uint8_t txd,uint8_t rxd);
void pinmux_uart3_deinit(void);

void pinmux_adtim1_ch1_init(uint8_t pin,bool output,uint8_t default_val);
void pinmux_adtim1_ch1_deinit(void);
void pinmux_adtim1_ch2_init(uint8_t pin,bool output,uint8_t default_val);
void pinmux_adtim1_ch2_deinit(void);
void pinmux_adtim1_ch3_init(uint8_t pin,bool output,uint8_t default_val);
void pinmux_adtim1_ch3_deinit(void);
void pinmux_adtim1_ch4_init(uint8_t pin,bool output,uint8_t default_val);
void pinmux_adtim1_ch4_deinit(void);
void pinmux_adtim1_ch1n_init(uint8_t pin);
void pinmux_adtim1_ch1n_deinit(void);
void pinmux_adtim1_ch2n_init(uint8_t pin);
void pinmux_adtim1_ch2n_deinit(void);
void pinmux_adtim1_ch3n_init(uint8_t pin);
void pinmux_adtim1_ch3n_deinit(void);
void pinmux_adtim1_etr_init(uint8_t pin);
void pinmux_adtim1_etr_deinit(void);
void pinmux_adtim1_bk_init(uint8_t pin);
void pinmux_adtim1_bk_deinit(void);


void pinmux_gptima1_ch1_init(uint8_t pin,bool output,uint8_t default_val);
void pinmux_gptima1_ch1_deinit(void);
void pinmux_gptima1_ch2_init(uint8_t pin,bool output,uint8_t default_val);
void pinmux_gptima1_ch2_deinit(void);
void pinmux_gptima1_ch3_init(uint8_t pin,bool output,uint8_t default_val);
void pinmux_gptima1_ch3_deinit(void);
void pinmux_gptima1_ch4_init(uint8_t pin,bool output,uint8_t default_val);
void pinmux_gptima1_ch4_deinit(void);
void pinmux_gptima1_etr_init(uint8_t pin);
void pinmux_gptima1_etr_deinit(void);

void pinmux_gptimb1_ch1_init(uint8_t pin,bool output,uint8_t default_val);
void pinmux_gptimb1_ch1_deinit(void);
void pinmux_gptimb1_ch2_init(uint8_t pin,bool output,uint8_t default_val);
void pinmux_gptimb1_ch2_deinit(void);
void pinmux_gptimb1_ch3_init(uint8_t pin,bool output,uint8_t default_val);
void pinmux_gptimb1_ch3_deinit(void);
void pinmux_gptimb1_ch4_init(uint8_t pin,bool output,uint8_t default_val);
void pinmux_gptimb1_ch4_deinit(void);
void pinmux_gptimb1_etr_init(uint8_t pin);
void pinmux_gptimb1_etr_deinit(void);

void pinmux_gptimc1_ch1_init(uint8_t pin,bool output,uint8_t default_val);
void pinmux_gptimc1_ch1_deinit(void);
void pinmux_gptimc1_ch1n_init(uint8_t pin);
void pinmux_gptimc1_ch1n_deinit(void);
void pinmux_gptimc1_ch2_init(uint8_t pin,bool output,uint8_t default_val);
void pinmux_gptimc1_ch2_deinit(void);
void pinmux_gptimc1_bk_init(uint8_t pin);
void pinmux_gptimc1_bk_deinit(void);