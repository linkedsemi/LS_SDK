#include "io_config.h"
#include "reg_sysc_awo.h"
#include "reg_v33_rg.h"
#include "field_manipulate.h"
#include "per_func_mux.h"
#include "reg_sysc_per.h"
#include "exception_isr.h"
#include "taurus.h"
#include "core_rv32.h"
static gpio_pin_t uart1_txd;
static gpio_pin_t uart1_rxd;
static gpio_pin_t uart2_txd;
static gpio_pin_t uart2_rxd;
static gpio_pin_t iic1_scl;
static gpio_pin_t iic1_sda;
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
static gpio_pin_t pis_ch0;
static gpio_pin_t pis_ch1;

__attribute__((weak)) void io_exti_callback(uint8_t pin){}
void EXTI_Handler(void)
{
    uint8_t i;
    uint32_t int_stat = V33_RG->GPIO_INTR;
    for(i=0;i<32;i++)
    {
        if ((1<<i) & int_stat)
        {
            V33_RG->EXTI_CTRL2 = 1<<i;
            V33_RG->EXTI_CTRL2 = 0;
            io_exti_callback(i);
        }
    }
}

void io_init(void)
{
    SYSC_AWO->IO[0].OE_DOT=0X0;
    SYSC_AWO->IO[0].IE_OD = 0XFFFF0000;
    SYSC_AWO->IO[1].OE_DOT=0X0;
    SYSC_AWO->IO[1].IE_OD = 0X30000;  //disable 
    rv_set_int_isr(EXT_IRQn,EXTI_Handler);
    csi_vic_clear_pending_irq(EXT_IRQn);
    csi_vic_enable_irq(EXT_IRQn);
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
    SYSC_AWO->IO[x->port].OE_DOT |= 1<<x->num;
}

void io_clr_pin(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    SYSC_AWO->IO[x->port].OE_DOT &= ~(1<<x->num);
}

void io_toggle_pin(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    SYSC_AWO->IO[x->port].OE_DOT ^= 1<<x->num;
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
    }
}

io_pull_type_t io_pull_read(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    if((SYSC_AWO->IO[x->port].PUPD>>x->num)&0x1)
    {
        return IO_PULL_DOWN;
    }else if((SYSC_AWO->IO[x->port].PUPD>>x->num>>16)&0x1)
    {
        return IO_PULL_UP;
    }else
    {
        return IO_PULL_DISABLE;
    }
}

void io_exti_config(uint8_t pin,exti_edge_t edge)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    switch (x->port)
    {
        case 0:
            if(edge == INT_EDGE_FALLING)
            {
                V33_RG->EXTI_CTRL1 |= 1<<(x->num);
            }
            else
            {
                V33_RG->EXTI_CTRL1 &= ~(1<<(x->num));
            }
        break;
        case 1:
            if(edge == INT_EDGE_FALLING)
            {
                V33_RG->EXTI_CTRL1 |= 1<<(x->num-16);
            }
            else
            {
                V33_RG->EXTI_CTRL1 &= ~(1<<(x->num-16));
            }
        break;
    }
}

void io_exti_enable(uint8_t pin,bool enable)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    V33_RG->EXTI_CTRL2 =0XFFFFFFFF;
    V33_RG->EXTI_CTRL2 =0;
    switch (x->port)
    {
        case 0:
            if(enable)
            {
                V33_RG->EXTI_CTRL0 |= 1<<(x->num);
            }
            else
            {
                V33_RG->EXTI_CTRL0 &= ~(1<<(x->num));
            }
        break;
        case 1:
            if(enable)
            {
                V33_RG->EXTI_CTRL0 |= 1<<(x->num+16);
            }
            else
            {
                V33_RG->EXTI_CTRL0 &= ~(1<<(x->num+16));
            }
        break;
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

void iic1_io_init(uint8_t scl,uint8_t sda)
{
    *(uint8_t *)&iic1_scl = scl;
    *(uint8_t *)&iic1_sda = sda;
    iic_io_cfg(scl,sda);
    per_func_enable(pin2func_io((gpio_pin_t *)&scl), IIC1_SCL);
    per_func_enable(pin2func_io((gpio_pin_t *)&sda), IIC1_SDA);
}

void iic1_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&iic1_scl));
    per_func_disable(pin2func_io((gpio_pin_t *)&iic1_sda));
}

void uart1_io_init(uint8_t txd,uint8_t rxd)
{
    *(uint8_t *)&uart1_txd = txd;
    *(uint8_t *)&uart1_rxd = rxd;
    uart_io_cfg(txd,rxd);
    per_func_enable(pin2func_io((gpio_pin_t *)&txd),UART1_TXD);
    per_func_enable(pin2func_io((gpio_pin_t *)&rxd),UART1_RXD);
}

void uart1_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&uart1_txd));
    per_func_disable(pin2func_io((gpio_pin_t *)&uart1_rxd));
}

void qspi_flash_io_init(void)
{
    REG_FIELD_WR(SYSC_AWO->PIN_SEL0,SYSC_AWO_QSPI_EN,0x3f);
}

void qspi_flash_io_deinit(void)
{
    REG_FIELD_WR(SYSC_AWO->PIN_SEL0,SYSC_AWO_QSPI_EN,0);
}

void usb_func_enable(uint8_t dp,uint8_t dm)
{
    per_func_enable(pin2func_io((gpio_pin_t *)&dp),USB_DP);
    per_func_enable(pin2func_io((gpio_pin_t *)&dm),USB_DM);
}

void uart2_io_init(uint8_t txd,uint8_t rxd)
{
    *(uint8_t *)&uart2_txd = txd;
    *(uint8_t *)&uart2_rxd = rxd;
    uart_io_cfg(txd,rxd);
    per_func_enable(pin2func_io((gpio_pin_t *)&txd),UART2_TXD);
    per_func_enable(pin2func_io((gpio_pin_t *)&rxd),UART2_RXD);
}
void uart2_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&uart2_txd));
    per_func_disable(pin2func_io((gpio_pin_t *)&uart2_rxd));
}

void uart3_io_init(uint8_t txd,uint8_t rxd);
void uart3_io_deinit(void);

static void timer_ch_io_cfg(uint8_t pin,bool output,uint8_t default_val)
{
    if(output)
    {
        io_write_pin(pin, default_val);
        io_cfg_output(pin);
    }else
    {
        io_cfg_input(pin);
    }
}

static void timer_ch_io_output_cfg(uint8_t pin,uint8_t default_val)
{
    io_write_pin(pin, default_val);
    io_cfg_output(pin);
}

void adtim1_ch1_io_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&adtim1_ch1 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_CH1);
}
void adtim1_ch1_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&adtim1_ch1));
}
void adtim1_ch2_io_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&adtim1_ch2 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_CH2);
}

void adtim1_ch2_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&adtim1_ch2));
}

void adtim1_ch3_io_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&adtim1_ch3 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_CH3);
}

void adtim1_ch3_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&adtim1_ch3));
}

void adtim1_ch4_io_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&adtim1_ch4 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_CH4);
}

void adtim1_ch4_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&adtim1_ch4));
}

void adtim1_ch1n_io_init(uint8_t pin)
{
    *(uint8_t *)&adtim1_ch1n = pin;
    timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim1_ch1));
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_CH1N);
}

void adtim1_ch1n_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&adtim1_ch1n));
}

void adtim1_ch2n_io_init(uint8_t pin)
{
    *(uint8_t *)&adtim1_ch2n = pin;
    timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim1_ch2));
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_CH2N);
}

void adtim1_ch2n_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&adtim1_ch2n));
}

void adtim1_ch3n_io_init(uint8_t pin)
{
    *(uint8_t *)&adtim1_ch3n = pin;
    timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim1_ch3));
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_CH3N);
}

void adtim1_ch3n_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&adtim1_ch3n));
}

void adtim1_etr_io_init(uint8_t pin)
{
    *(uint8_t *)&adtim1_etr = pin;
    io_cfg_input(pin);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_ETR);
}

void adtim1_etr_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&adtim1_etr));
}

void adtim1_bk_io_init(uint8_t pin)
{
    *(uint8_t *)&adtim1_bk = pin;
    io_cfg_input(pin);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),ADTIM1_BK);
}

void adtim1_bk_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&adtim1_bk));
}

void gptima1_ch1_io_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptima1_ch1 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMA1_CH1);
}

void gptima1_ch1_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&gptima1_ch1));
}

void gptima1_ch2_io_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptima1_ch2 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMA1_CH2);
}

void gptima1_ch2_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&gptima1_ch2));
}

void gptima1_ch3_io_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptima1_ch3 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMA1_CH3);
}

void gptima1_ch3_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&gptima1_ch3));
}

void gptima1_ch4_io_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptima1_ch4 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMA1_CH4);
}

void gptima1_ch4_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&gptima1_ch4));
}

void gptima1_etr_io_init(uint8_t pin)
{
    *(uint8_t *)&gptima1_etr = pin;
    io_cfg_input(pin);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMA1_ETR);
}

void gptima1_etr_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&gptima1_etr));
}

void gptimb1_ch1_io_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimb1_ch1 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMB1_CH1);
}

void gptimb1_ch1_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&gptimb1_ch1));
}

void gptimb1_ch2_io_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimb1_ch2 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMB1_CH2);
}

void gptimb1_ch2_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&gptimb1_ch2));
}

void gptimb1_ch3_io_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimb1_ch3 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMB1_CH3);
}

void gptimb1_ch3_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&gptimb1_ch3));
}

void gptimb1_ch4_io_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimb1_ch4 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMB1_CH4);
}

void gptimb1_ch4_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&gptimb1_ch4));
}

void gptimb1_etr_io_init(uint8_t pin)
{
    *(uint8_t *)&gptimb1_etr = pin;
    io_cfg_input(pin);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMB1_ETR);
}

void gptimb1_etr_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&gptimb1_etr));
}

void gptimc1_ch1_io_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimc1_ch1 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMC1_CH1);
}

void gptimc1_ch1_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&gptimc1_ch1));
}

void gptimc1_ch1n_io_init(uint8_t pin)
{
    *(uint8_t *)&gptimc1_ch1n = pin;
    timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&gptimc1_ch1));
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMC1_CH1N);
}

void gptimc1_ch1n_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&gptimc1_ch1n));
}

void gptimc1_ch2_io_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimc1_ch2 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMC1_CH2);
}

void gptimc1_ch2_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&gptimc1_ch2));
}

void gptimc1_bk_io_init(uint8_t pin)
{
    *(uint8_t *)&gptimc1_bk = pin;
    io_cfg_input(pin);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),GPTIMC1_BK);
}

void gptimc1_bk_io_deinit(void)
{
    per_func_disable(pin2func_io((gpio_pin_t *)&gptimc1_bk));
}

void pis_ch0out_io_init(uint8_t pin)
{
    *(uint8_t *)&pis_ch0 = pin;
    io_cfg_input(pin);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),PIS_CH0);
}

void pis_ch0out_io_deinit()
{
    per_func_disable(pin2func_io((gpio_pin_t *)&pis_ch0));
}

void pis_ch1out_io_init(uint8_t pin)
{
    *(uint8_t *)&pis_ch1 = pin;
    io_cfg_input(pin);
    per_func_enable(pin2func_io((gpio_pin_t *)&pin),PIS_CH1);
}

void pis_ch1out_io_deinit()
{
    per_func_disable(pin2func_io((gpio_pin_t *)&pis_ch1));
}