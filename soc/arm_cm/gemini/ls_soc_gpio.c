#include <stddef.h>
#include "ls_soc_gpio.h"
#include "field_manipulate.h"
#include "per_func_mux.h"
#include "gemini.h"
#include "platform.h"
#include "reg_v33_rg_type.h"
#include "reg_sysc_per_type.h"
#include "reg_sysc_awo_type.h"
#include "reg_exti_type.h"
#include "ls_dbg.h"

gpio_pin_t uart1_txd;
gpio_pin_t uart1_rxd;
gpio_pin_t iic1_scl;
gpio_pin_t iic1_sda;
static gpio_pin_t adtim1_ch1;
static gpio_pin_t adtim1_ch1n;
static gpio_pin_t adtim1_ch2;
static gpio_pin_t adtim1_ch2n;
static gpio_pin_t adtim1_ch3;
static gpio_pin_t adtim1_ch3n;
static gpio_pin_t adtim1_ch4;
static gpio_pin_t adtim1_etr;
static gpio_pin_t adtim1_bk;
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
static gpio_pin_t spi2_clk;
static gpio_pin_t spi2_nss;
static gpio_pin_t spi2_mosi;
static gpio_pin_t spi2_miso;
/* ssi io init */
static gpio_pin_t ssi_clk;
static gpio_pin_t ssi_nss0;
static gpio_pin_t ssi_nss1;
static gpio_pin_t ssi_dq0;
static gpio_pin_t ssi_dq1;
static gpio_pin_t ssi_dq2;
static gpio_pin_t ssi_dq3;

__attribute__((weak)) void io_exti_callback(uint8_t pin,exti_edge_t edge){}

static inline uint8_t v33_ext_group_sel_get(uint8_t group)
{
    return V33_RG->GPIO_SEL>>(2*group) & 0x1;
}

void V33_EXTI_Handler(void)
{
    uint8_t i;
    uint32_t int_stat = V33_RG->GPIO_INTR;
    for(i=0;i<8;i++)
    {
        exti_edge_t edge = INT_EDGE_NONE;
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


void GPIO_Handler(void)
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
    __NVIC_EnableIRQ(EXT_IRQn);
    __NVIC_EnableIRQ(GPIO_IRQn);
}

void io_init(void)
{
    SYSC_AWO->IO[0].IE_OD = 0x9fff0000;
    SYSC_AWO->IO[0].OE_DOT= 0;
    SYSC_AWO->IO[1].IE_OD = 0xffff0000;
    SYSC_AWO->IO[1].OE_DOT = 0;
    SYSC_AWO->IO[2].IE_OD = 0xffff0000;
    SYSC_AWO->IO[2].OE_DOT = 0;
    SYSC_AWO->IO[3].IE_OD = 0x03ff0000;
    SYSC_AWO->IO[3].OE_DOT = 0;
    arm_cm_set_int_isr(EXT_IRQn,V33_EXTI_Handler);
    arm_cm_set_int_isr(GPIO_IRQn,GPIO_Handler);
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
    SYSC_AWO->IO[x->port].IE_OD &= ~(1<<16<<x->num); 
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

static void v33_ext_intr_mask(uint8_t group,exti_edge_t edge)
{
    switch(edge)
    {
    case INT_EDGE_NONE:
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
        case INT_EDGE_NONE:
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
        }
    }
}

static void uart_io_cfg(uint8_t txd,uint8_t rxd)
{
    io_set_pin(txd);
    io_cfg_output(txd);
    io_cfg_input(rxd);
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


void pinmux_hal_flash_init(void)
{
    REG_FIELD_WR(SYSC_AWO->PIN_SEL0,SYSC_AWO_QSPI_EN,0xf);
}

void pinmux_hal_flash_deinit(void)
{
    REG_FIELD_WR(SYSC_AWO->PIN_SEL0,SYSC_AWO_QSPI_EN,0x0);
}

void pinmux_hal_flash_quad_init(void)
{
    REG_FIELD_WR(SYSC_AWO->PIN_SEL0,SYSC_AWO_QSPI_EN,0x3f);
}

void pinmux_hal_flash_quad_deinit(void)
{
    REG_FIELD_WR(SYSC_AWO->PIN_SEL0,SYSC_AWO_QSPI_EN,0x0);
}

static void spi_clk_io_cfg(uint8_t clk)
{
    io_set_pin(clk);
    io_cfg_output(clk);
}

static void spi_nss_io_cfg(uint8_t nss)
{
    io_set_pin(nss);
    io_pull_write(nss,IO_PULL_UP);
    io_cfg_output(nss);
}

static void spi_mosi_io_cfg(uint8_t mosi)
{
    io_set_pin(mosi);
    io_cfg_output(mosi);
}

static void spi_miso_io_cfg(uint8_t miso)
{
    io_cfg_input(miso);
}

void pinmux_spi2_clk_init(uint8_t clk)
{
    *(uint8_t *)&spi2_clk = clk;
    spi_clk_io_cfg( clk);
     per_func_enable(pin2func_io((gpio_pin_t *)&clk),SPI2_SCK);
}

void pinmux_spi2_nss_init(uint8_t nss)
{
    *(uint8_t *)&spi2_nss = nss;
    spi_nss_io_cfg( nss);
    per_func_enable(pin2func_io((gpio_pin_t *)&nss),SPI2_NSS);  
}

void pinmux_spi2_mosi_init(uint8_t mosi)
{
    *(uint8_t *)&spi2_mosi = mosi;
    spi_mosi_io_cfg( mosi);
    per_func_enable(pin2func_io((gpio_pin_t *)&mosi),SPI2_MOSI);
}

void pinmux_spi2_miso_init(uint8_t miso)
{

    *(uint8_t *)&spi2_miso = miso;
    spi_miso_io_cfg( miso);    
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

void pinmux_ssi_clk_init(uint8_t clk)
{
    *(uint8_t *)&ssi_clk = clk;
    spi_clk_io_cfg(clk);
   per_func_enable(pin2func_io((gpio_pin_t *)&clk),SPI1_SCK);
}

void pinmux_ssi_nss0_init(uint8_t nss0)
{
    *(uint8_t *)&ssi_nss0 = nss0;
    spi_nss_io_cfg(nss0);
    per_func_enable(pin2func_io((gpio_pin_t *)&nss0),SPI1_NSS0);
}

void pinmux_ssi_nss1_init(uint8_t nss1)
{
    *(uint8_t *)&ssi_nss1 = nss1;
    spi_nss_io_cfg(nss1);
    per_func_enable(pin2func_io((gpio_pin_t *)&nss1),SPI1_NSS0); 
}

void pinmux_ssi_dq0_init(uint8_t dq0)
{
    *(uint8_t *)&ssi_dq0 = dq0;
    spi_mosi_io_cfg(dq0);
    per_func_enable(pin2func_io((gpio_pin_t *)&dq0),SPI1_DQ0); 
}

void pinmux_ssi_dq1_init(uint8_t dq1)
{

    *(uint8_t *)&ssi_dq1 = dq1;
    spi_miso_io_cfg(dq1);
    per_func_enable(pin2func_io((gpio_pin_t *)&dq1), SPI1_DQ1);
}

void pinmux_ssi_dq2_init(uint8_t dq2)
{

    *(uint8_t *)&ssi_dq2 = dq2;
    spi_miso_io_cfg(dq2);
    per_func_enable(pin2func_io((gpio_pin_t *)&dq2), SPI1_DQ2);
}

void pinmux_ssi_dq3_init(uint8_t dq3)
{

    *(uint8_t *)&ssi_dq3 = dq3;
    spi_miso_io_cfg(dq3);
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
