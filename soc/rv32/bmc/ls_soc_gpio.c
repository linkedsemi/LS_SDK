#include <stdint.h>
#include <stddef.h>
#include "ls_soc_gpio.h"
#include "platform.h"
#include "reg_pmu.h"
// #include "field_manipulate.h"
// #include "per_func_mux.h"
// #include "bmc.h"
// #include "reg_exti_type.h"
// #include "ls_dbg.h"
// #include "exception_isr.h"
// #include "compile_flag.h"
// #include "common.h"

// #if BOOT_RAM
// #define I2C_DBG_IO_CHECK(x)
// #else
// #define I2C_DBG_IO_CHECK(x)     if(i2c_dbg_io_check(x)){return;}
// #endif

// #define USB_DP_PAD PD00
// #define USB_DM_PAD PD01
// static gpio_port_pin_t uart1_txd;
// static gpio_port_pin_t uart1_rxd;
// static gpio_port_pin_t uart2_txd;
// static gpio_port_pin_t uart2_rxd;
// static gpio_port_pin_t uart3_txd;
// static gpio_port_pin_t uart3_rxd;
// static gpio_port_pin_t dwuart1_txd;
// static gpio_port_pin_t dwuart1_rxd;
// static gpio_port_pin_t dwuart2_txd;
// static gpio_port_pin_t dwuart2_rxd;
// static gpio_port_pin_t iic1_scl;
// static gpio_port_pin_t iic1_sda;
// static gpio_port_pin_t iic2_scl;
// static gpio_port_pin_t iic2_sda;
// static gpio_port_pin_t iic3_sda;
// static gpio_port_pin_t iic3_scl;
// static gpio_port_pin_t iic4_sda;
// static gpio_port_pin_t iic4_scl;
// static gpio_port_pin_t iic5_sda;
// static gpio_port_pin_t iic5_scl;
// static gpio_port_pin_t iic6_sda;
// static gpio_port_pin_t iic6_scl;
// /* spi io init */
// static gpio_port_pin_t spi2_clk;
// static gpio_port_pin_t spi2_nss;
// static gpio_port_pin_t spi2_mosi;
// static gpio_port_pin_t spi2_miso;
// static gpio_port_pin_t spi3_clk;
// static gpio_port_pin_t spi3_nss;
// static gpio_port_pin_t spi3_mosi;
// static gpio_port_pin_t spi3_miso;
// /* iis io init */
// static gpio_port_pin_t i2s2_ck;
// static gpio_port_pin_t i2s2_ws;
// static gpio_port_pin_t i2s2_sd;
// static gpio_port_pin_t i2s2_mck;
// static gpio_port_pin_t i2s3_ck;
// static gpio_port_pin_t i2s3_ws;
// static gpio_port_pin_t i2s3_sd;
// static gpio_port_pin_t i2s3_mck;
// /* ssi io init */
// static gpio_port_pin_t ssi_clk;
// static gpio_port_pin_t ssi_nss0;
// static gpio_port_pin_t ssi_nss1;
// static gpio_port_pin_t ssi_dq0;
// static gpio_port_pin_t ssi_dq1;
// static gpio_port_pin_t ssi_dq2;
// static gpio_port_pin_t ssi_dq3;
// /* pwm io init */
// static gpio_port_pin_t pwm1_pin;
// static gpio_port_pin_t pwm2_pin;
// static gpio_port_pin_t pwm3_pin;
// static gpio_port_pin_t pwm4_pin;
// static gpio_port_pin_t pwm5_pin;
// static gpio_port_pin_t pwm6_pin;
// static gpio_port_pin_t pwm7_pin;
// static gpio_port_pin_t pwm8_pin;

// static gpio_port_pin_t cap1_pin;
// static gpio_port_pin_t cap2_pin;
// static gpio_port_pin_t cap3_pin;
// static gpio_port_pin_t cap4_pin;
// static gpio_port_pin_t cap5_pin;
// static gpio_port_pin_t cap6_pin;
// static gpio_port_pin_t cap7_pin;
// static gpio_port_pin_t cap8_pin;

// static gpio_port_pin_t pdm_clk;
// static gpio_port_pin_t pdm_data0;
// static gpio_port_pin_t pdm_data1;
// static gpio_port_pin_t cec_pin;
// static gpio_port_pin_t comp1_dat;
// static gpio_port_pin_t comp2_dat;
// static gpio_port_pin_t comp3_dat;
// static gpio_port_pin_t fdcan_txd;
// static gpio_port_pin_t fdcan_rxd;

// static gpio_port_pin_t adtim1_ch1;
// static gpio_port_pin_t adtim1_ch1n;
// static gpio_port_pin_t adtim1_ch2;
// static gpio_port_pin_t adtim1_ch2n;
// static gpio_port_pin_t adtim1_ch3;
// static gpio_port_pin_t adtim1_ch3n;
// static gpio_port_pin_t adtim1_ch4;
// static gpio_port_pin_t adtim1_etr;
// static gpio_port_pin_t adtim1_bk;

// static gpio_port_pin_t adtim2_ch1;
// static gpio_port_pin_t adtim2_ch1n;
// static gpio_port_pin_t adtim2_ch2;
// static gpio_port_pin_t adtim2_ch2n;
// static gpio_port_pin_t adtim2_ch3;
// static gpio_port_pin_t adtim2_ch3n;
// static gpio_port_pin_t adtim2_ch4;
// static gpio_port_pin_t adtim2_etr;
// static gpio_port_pin_t adtim2_bk;

// static gpio_port_pin_t gptima1_ch1;
// static gpio_port_pin_t gptima1_ch2;
// static gpio_port_pin_t gptima1_ch3;
// static gpio_port_pin_t gptima1_ch4;
// static gpio_port_pin_t gptima1_etr;

// static gpio_port_pin_t gptimb1_ch1;
// static gpio_port_pin_t gptimb1_ch2;
// static gpio_port_pin_t gptimb1_ch3;
// static gpio_port_pin_t gptimb1_ch4;
// static gpio_port_pin_t gptimb1_etr;

// static gpio_port_pin_t gptimc1_ch1;
// static gpio_port_pin_t gptimc1_ch1n;
// static gpio_port_pin_t gptimc1_ch2;
// static gpio_port_pin_t gptimc1_bk;
// /* ps2h io init */
// static gpio_port_pin_t ps2h1_clk;
// static gpio_port_pin_t ps2h1_dat;
// static gpio_port_pin_t ps2h2_clk;
// static gpio_port_pin_t ps2h2_dat;
// static gpio_port_pin_t ps2h3_clk;
// static gpio_port_pin_t ps2h3_dat;
// static gpio_port_pin_t ps2h4_clk;
// static gpio_port_pin_t ps2h4_dat;

// static gpio_port_pin_t owm_pin;

// static uint8_t otg_id = 0xff;
// uint8_t i2c_dbg_scl_io = 0xff;
// uint8_t i2c_dbg_dat_io = 0xff;

// __attribute__((weak)) void io_exti_callback(uint8_t pin,exti_edge_t edge){}

// __attribute__((weak)) void io_v33_exti_callback(uint8_t pin,exti_edge_t edge)
// {
//     io_exti_callback(pin,edge);
// }
// __attribute__((weak)) void io_vcore_exti_callback(uint8_t pin,exti_edge_t edge)
// {
//     io_exti_callback(pin,edge);
// }

// void exti_async_handler(volatile uint32_t *INT_STAT_BASE,volatile uint32_t *INT_CLR_BASE,void (*callback)(uint8_t,exti_edge_t))
// {
//     uint8_t i;
//     for(i=0;i<8;++i)
//     {
//         volatile uint32_t *INT_STAT_REG = &INT_STAT_BASE[i];
//         volatile uint32_t *INT_CLR_REG = &INT_CLR_BASE[i];
//         uint32_t int_stat = *INT_STAT_REG;
//         if(int_stat == 0) continue;
//         uint8_t j;
//         for(j=0;j<16;++j)
//         {
//             exti_edge_t edge = INT_EDGE_NONE;
//             if(1<<j & int_stat)
//             {
//                 *INT_CLR_REG = 1<<j;
//                 edge |= INT_EDGE_RISING;
//             }
//             if(1<<16<<j & int_stat)
//             {
//                 *INT_CLR_REG = 1<<16<<j;
//                 edge |= INT_EDGE_FALLING;
//             }
//             if(edge)
//             {
//                 *INT_CLR_REG = 0;
//                 callback(i<<4|j,edge);
//             }
//         }
//     }
// }

// void V33_EXTI_Async_Handler(void)
// {
//     exti_async_handler(V33_RG->GPIO_INTR_STT,V33_RG->GPIO_INTR_CLR,io_v33_exti_callback);
// }

// void VCore_EXTI_Async_Handler(void)
// {
//     exti_async_handler(SYSC_AWO->EXTI_STT,SYSC_AWO->EXTI_CLR,io_vcore_exti_callback);
// }

// static void exti_io_handler(uint8_t port,uint8_t num)
// {
//     uint8_t pin = port<<4 | num;
//     EXTI->EICR = 1<<num;
//     EXTI->EICR = 0;
//     io_exti_callback(pin,INT_EDGE_NONE);
// }

// void EXTI_Handler(void)
// {
//     uint16_t int_stat = EXTI->EEIFM;
//     uint8_t i;
//     uint8_t port;
//     for(i=0;i<8;++i)
//     {
//         if(1<<i & int_stat)
//         {
//             port = EXTI->EICFG0 >> (4*i);
//             exti_io_handler(port,i);
//         }
//     }
//     for(i=8;i<16;++i)
//     {
//         if(1<<i & int_stat)
//         {
//             port = EXTI->EICFG1 >> (4*(i-8));
//             exti_io_handler(port,i);
//         }
//     }
// }

// void EXTI1_Handler(void)
// {
//     uint16_t int_stat = EXTI1->EEIFM;
//     uint8_t i;
//     uint8_t port;
//     for(i=0;i<8;++i)
//     {
//         if(1<<i & int_stat)
//         {
//             port = EXTI1->EICFG0 >> (4*i);
//             exti_io_handler(port+4,i);
//         }
//     }
//     for(i=8;i<16;++i)
//     {
//         if(1<<i & int_stat)
//         {
//             port = EXTI1->EICFG1 >> (4*(i-8));
//             exti_io_handler(port+4,i);
//         }
//     }
// }

// void i2c_dbg_io_reinit(uint32_t *value)
// {
//     uint8_t i2c_scl_list[] = {PA11,PC02,PC04,PE00,PB00,PE05,PE13,PB14,PH07};
//     uint8_t i2c_sda_list[] = {PA12,PC03,PC05,PB01,PE04,PE14,PB15,PH06};

//     uint8_t read_io_func = 0;
//     if(io_read_pin(PB06)) //EC_MODE_PIN
//     {
//         for(uint8_t index=0;index<ARRAY_LEN(i2c_scl_list);index++)
//         {
//             read_io_func = READ_REG(SYSC_PER->FUNC_SEL[i2c_scl_list[index]/4]) >> (i2c_scl_list[index]%4)*8;
//             if(read_io_func == FIO_I2C_DBG_SCL)
//             {
//                 value[i2c_scl_list[index]/0x0F] &= ~(1<<16<<(i2c_scl_list[index]&0x0f));
//                 i2c_dbg_scl_io = i2c_scl_list[index];
//                 if(index > 2)
//                 {
//                     value[i2c_sda_list[index-1]/0x0F] &= ~(1<<16<<(i2c_sda_list[index-1]&0x0f));
//                     i2c_dbg_dat_io = i2c_sda_list[index-1];
//                 }
//                 else
//                 {
//                     value[i2c_sda_list[index]/0x0F] &= ~(1<<16<<(i2c_sda_list[index]&0x0f));
//                     i2c_dbg_dat_io = i2c_sda_list[index];
//                 }
//                 break;
//             }
//         }
//     }
// }

// bool i2c_dbg_io_check(uint8_t pin)
// {
//     return (pin==i2c_dbg_dat_io || pin==i2c_dbg_scl_io);
// }

void io_init(void)
{
    uint32_t gpio_ien_od_value[8] = {0xffff0000, 0xffff0000, 0x5fff0000, 0xfeab0000,
                                     0xffff0000, 0xffff0000, 0xffff0000, 0xfff30000};
    
    for (uint8_t i = 0; i < 15; i++)
    {
        PMU->IO[i].IEN_OD = gpio_ien_od_value[i];
        PMU->IO[i].OE_FIR= 0;
        PMU->GPIO_INTR_CLR[i] = 0xffff;
        PMU->GPIO_INTR_CLR[i] = 0;
    }
    
    // EXTI->EICR = 0xffffffff;
    // EXTI->EICR = 0;
    // rv_set_int_isr(EXTI_ASYNC_IRQn,VCore_EXTI_Async_Handler);
    // csi_vic_clear_pending_irq(EXTI_ASYNC_IRQn);
    // csi_vic_enable_irq(EXTI_ASYNC_IRQn);
    
    // rv_set_int_isr(V33_EXT_IRQn,V33_EXTI_Async_Handler);
    // csi_vic_clear_pending_irq(V33_EXT_IRQn);
    // csi_vic_enable_irq(V33_EXT_IRQn);
    
}

// void io_cfg_output(uint8_t pin)
// {
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     SYSC_AWO->IO[x->port].OE_FIR |= 1<<16<<x->num;
// }

// void io_cfg_opendrain(uint8_t pin)
// {
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     SYSC_AWO->IO[x->port].IEN_OD |= 1<<x->num;
// }

// void io_cfg_pushpull(uint8_t pin)
// {
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     SYSC_AWO->IO[x->port].IEN_OD &= ~(1<<x->num);
// }

// void io_cfg_input(uint8_t pin)
// {
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     SYSC_AWO->IO[x->port].OE_FIR &= ~(1<<16<<x->num);
//     SYSC_AWO->IO[x->port].IEN_OD &= ~(1<<16<<x->num);
// }

// void io_write_pin(uint8_t pin,uint8_t val)
// {
//     if(val)
//     {
//         io_set_pin(pin);
//     }else
//     {
//         io_clr_pin(pin);
//     }
// }

// void io_set_pin(uint8_t pin)
// {
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     SYSC_AWO->IO[x->port].DOT = 1<<x->num;
// }

// void io_clr_pin(uint8_t pin)
// {
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     SYSC_AWO->IO[x->port].DOT = 1<<16<<x->num;
// }

// void io_toggle_pin(uint8_t pin)
// {
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     if(SYSC_AWO->IO[x->port].DOT & (1<<x->num))
//     {
//        io_clr_pin(pin);
//     }else
//     {
//        io_set_pin(pin);
//     }
    
// }

// uint8_t io_get_output_val(uint8_t pin)
// {
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     return SYSC_AWO->IO[x->port].DOT >> x->num & 0x1;
// }

// uint8_t io_get_input_val(uint8_t pin)
// {
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     return SYSC_AWO->IO[x->port].DIN >> x->num & 0x1;
// }

// uint8_t io_read_pin(uint8_t pin)
// {
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     if (SYSC_AWO->IO[x->port].OE_FIR & (1<<16<<x->num))
//     {
//         return io_get_output_val(pin);
//     }
//     else
//     {
//         return io_get_input_val(pin);
//     }
// }

// void io_pull_write(uint8_t pin,io_pull_type_t pull)
// {
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     switch(pull)
//     {
//     case IO_PULL_DISABLE:
//         SYSC_AWO->IO[x->port].PUPD &= ~(1<<16<<x->num | 1<<x->num);
//     break;
//     case IO_PULL_UP:
//         MODIFY_REG(SYSC_AWO->IO[x->port].PUPD,1<<16<<x->num,1<<x->num);
//     break;
//     case IO_PULL_DOWN:
//         MODIFY_REG(SYSC_AWO->IO[x->port].PUPD,1<<x->num,1<<16<<x->num);
//     break;
//     case IO_PULL_UP_DOWN:
//         SYSC_AWO->IO[x->port].PUPD |= 1<<16<<x->num | 1<<x->num;
//     break;
//     }
// }

// static inline io_pull_type_t pull_down(uint8_t port,uint8_t num)
// {
//     if((SYSC_AWO->IO[port].PUPD>>num)&0x1)
//     {
//         return IO_PULL_DOWN;
//     }else
//     {
//         return IO_PULL_DISABLE;
//     }
// }

// static inline io_pull_type_t pull_up(uint8_t port,uint8_t num)
// {
//     if((SYSC_AWO->IO[port].PUPD>>num>>16)&0x1)
//     {
//         return IO_PULL_UP;
//     }else
//     {
//         return IO_PULL_DISABLE;
//     }
// }

// io_pull_type_t io_pull_read(uint8_t pin)
// {
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     return pull_down(x->port,x->num)|pull_up(x->port,x->num);
// }

// void io_drive_capacity_write(uint8_t pin, io_drive_type_t drive)
// {
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     MODIFY_REG(SYSC_AWO->IO[x->port].DS, 0x1<< (x->num) | (0x1<< (x->num +16)), (drive&0x1)<< (x->num) |(((drive&0x2)>>1)<< (x->num +16)));
// }

// io_drive_type_t io_drive_capacity_read(uint8_t pin)
// {
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     uint32_t tmp = READ_REG(SYSC_AWO->IO[x->port].DS);
//     return ((tmp & (0x1 <<x->num))?0x1:0) | ((tmp & (0x1 <<(x->num+16)))?0x2:0);
// }

// static inline void ext_intr_mask(volatile uint32_t *mask,volatile uint32_t *clr,uint8_t num,exti_edge_t edge)
// {
//     switch(edge)
//     {
//     case INT_EDGE_NONE:
//         *mask &= ~(1<<num|1<<16<<num);
//     break;
//     case INT_EDGE_RISING:
//         *clr = 1<<num;
//         MODIFY_REG(*mask,1<<16<<num,1<<num);
//     break;
//     case INT_EDGE_FALLING:
//         *clr = 1<<16<<num;
//         MODIFY_REG(*mask,1<<num,1<<16<<num);
//     break;
//     case INT_EDGE_BOTH:
//         *clr = 1<<num|1<<16<<num;
//         *mask |= 1<<num|1<<16<<num;
//     break;
//     }
//     *clr = 0;
// }

// void io_v33_exti_config(uint8_t pin,exti_edge_t edge)
// {
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     ext_intr_mask(&V33_RG->GPIO_INTR_MSK[x->port],&V33_RG->GPIO_INTR_CLR[x->port],x->num,edge);
// }

// void io_vcore_exti_config(uint8_t pin,exti_edge_t edge)
// {
//     I2C_DBG_IO_CHECK(pin);
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     ext_intr_mask(&SYSC_AWO->EXTI_MSK[x->port],&SYSC_AWO->EXTI_CLR[x->port],x->num,edge);
// }

// void io_exti_config(uint8_t pin,exti_edge_t edge)
// {
//     if(pin==PB07||pin==PB08||pin==PB09||pin==PB10||pin==PC04||pin==PD00||pin==PD01||pin==PD09
//     ||pin==PD10||pin==PD11||pin==PD12||pin==PD13||pin==PD14||pin==PD15||pin==PG14||pin==PG15)
//     {
//         io_vcore_exti_config(pin,edge);
//         return ;
//     }
//     io_v33_exti_config(pin,edge);
// }

// static void uart_io_cfg(uint8_t txd,uint8_t rxd)
// {
//     io_set_pin(txd);
//     io_cfg_output(txd);
//     io_cfg_input(rxd);
//     io_pull_write(rxd, IO_PULL_UP);
// }

// static uint8_t pin2func_io(gpio_port_pin_t *x)
// {
//     return x->port*16+x->num;
// }

// static void per_func_enable(uint8_t func_io_num,uint8_t per_func)
// {
//     MODIFY_REG(SYSC_PER->FUNC_SEL[func_io_num/4],0xff<<8*(func_io_num%4),per_func<<8*(func_io_num%4));
//     if(func_io_num >= 96)
//     {
//         SYSC_AWO->PIN_SEL4 |= 1<<(func_io_num-96);
//     }else if(func_io_num >= 64)
//     {
//         SYSC_AWO->PIN_SEL3 |= 1<<(func_io_num-64);
//     }else if(func_io_num >= 32)
//     {
//         SYSC_AWO->PIN_SEL2 |= 1<<(func_io_num-32);
//     }else
//     {
//         SYSC_AWO->PIN_SEL1 |= 1<<func_io_num;
//     }
// }

// static void per_func_disable(uint8_t func_io_num)
// {
//     if(func_io_num >= 96)
//     {
//         SYSC_AWO->PIN_SEL4 &= ~(1<<(func_io_num-96));
//     }else if(func_io_num >= 64)
//     {
//         SYSC_AWO->PIN_SEL3 &= ~(1<<(func_io_num-64));
//     }else if(func_io_num >= 32)
//     {
//         SYSC_AWO->PIN_SEL2 &= ~(1<<(func_io_num-32));
//     }else
//     {
//         SYSC_AWO->PIN_SEL1 &= ~(1<<func_io_num);
//     }
//     MODIFY_REG(SYSC_PER->FUNC_SEL[func_io_num/4],0xff<<8*(func_io_num%4),0);
// }

// static void iic_io_cfg(uint8_t scl,uint8_t sda)
// {
//     io_cfg_input(scl);
//     io_cfg_input(sda);
//     io_pull_write(scl,IO_PULL_UP);
//     io_pull_write(sda,IO_PULL_UP);
// }

// void pinmux_uart1_init(uint8_t txd,uint8_t rxd)
// {
//     I2C_DBG_IO_CHECK(txd);
//     I2C_DBG_IO_CHECK(rxd);
//     *(uint8_t *)&uart1_txd = txd;
//     *(uint8_t *)&uart1_rxd = rxd;
//     uart_io_cfg(txd,rxd);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&txd),UART1_TXD);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&rxd),UART1_RXD);
// }

// void pinmux_uart1_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&uart1_txd));
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&uart1_rxd));
// }

// void pinmux_uart2_init(uint8_t txd,uint8_t rxd)
// {
//     I2C_DBG_IO_CHECK(txd);
//     I2C_DBG_IO_CHECK(rxd);
//     *(uint8_t *)&uart2_txd = txd;
//     *(uint8_t *)&uart2_rxd = rxd;
//     uart_io_cfg(txd,rxd);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&txd),UART2_TXD);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&rxd),UART2_RXD);
// }

// void pinmux_uart2_deinit()
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&uart2_txd));
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&uart2_rxd));
// }

// void pinmux_uart3_init(uint8_t txd,uint8_t rxd)
// {
//     I2C_DBG_IO_CHECK(txd);
//     I2C_DBG_IO_CHECK(rxd);
//     *(uint8_t *)&uart3_txd = txd;
//     *(uint8_t *)&uart3_rxd = rxd;
//     uart_io_cfg(txd,rxd);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&txd),UART3_TXD);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&rxd),UART3_RXD);
// }

// void pinmux_uart3_deinit()
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&uart3_txd));
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&uart3_rxd));
// }

// void pinmux_dwuart1_init(uint8_t txd,uint8_t rxd)
// {
//     I2C_DBG_IO_CHECK(txd);
//     I2C_DBG_IO_CHECK(rxd);
//     *(uint8_t *)&dwuart1_txd = txd;
//     *(uint8_t *)&dwuart1_rxd = rxd;
//     uart_io_cfg(txd,rxd);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&txd),DWUART1_TXD);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&rxd),DWUART1_RXD);
// }

// void pinmux_dwuart1_deinit()
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&dwuart1_txd));
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&dwuart1_rxd));
// }

// void pinmux_dwuart2_init(uint8_t txd,uint8_t rxd)
// {
//     I2C_DBG_IO_CHECK(txd);
//     I2C_DBG_IO_CHECK(rxd);
//     *(uint8_t *)&dwuart2_txd = txd;
//     *(uint8_t *)&dwuart2_rxd = rxd;
//     uart_io_cfg(txd,rxd);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&txd),DWUART2_TXD);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&rxd),DWUART2_RXD);
// }

// void pinmux_dwuart2_deinit()
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&dwuart2_txd));
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&dwuart2_rxd));
// }

// void pinmux_i2c_dbg_init(uint8_t clk,uint8_t dat)
// {
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&clk),I2C_DBG_CLK);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&dat),I2C_DBG_DAT);
// }

// void pinmux_pwm_ch1_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&pwm1_pin = pin;
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), PWM_CH1);
// }

// void pinmux_pwm_ch1_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&pwm1_pin));
// }

// void pinmux_pwm_ch2_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&pwm2_pin = pin;
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), PWM_CH2);
// }

// void pinmux_pwm_ch2_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&pwm2_pin));
// }

// void pinmux_pwm_ch3_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&pwm3_pin = pin;
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), PWM_CH3);
// }

// void pinmux_pwm_ch3_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&pwm3_pin));
// }

// void pinmux_pwm_ch4_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&pwm4_pin = pin;
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), PWM_CH4);
// }

// void pinmux_pwm_ch4_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&pwm4_pin));
// }

// void pinmux_pwm_ch5_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&pwm5_pin = pin;
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), PWM_CH5);
// }

// void pinmux_pwm_ch5_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&pwm5_pin));
// }

// void pinmux_pwm_ch6_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&pwm6_pin = pin;
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), PWM_CH6);
// }

// void pinmux_pwm_ch6_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&pwm6_pin));
// }

// void pinmux_pwm_ch7_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&pwm7_pin = pin;
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), PWM_CH7);
// }

// void pinmux_pwm_ch7_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&pwm7_pin));
// }

// void pinmux_pwm_ch8_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&pwm8_pin = pin;
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), PWM_CH8);
// }

// void pinmux_pwm_ch8_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&pwm8_pin));
// }

// void pinmux_cap_ch1_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&cap1_pin = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), FIO_CAP1);
// }

// void pinmux_cap_ch1_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&cap1_pin));
// }

// void pinmux_cap_ch2_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&cap2_pin = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), FIO_CAP2);
// }

// void pinmux_cap_ch2_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&cap2_pin));
// }

// void pinmux_cap_ch3_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&cap3_pin = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), FIO_CAP3);
// }

// void pinmux_cap_ch3_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&cap3_pin));
// }

// void pinmux_cap_ch4_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&cap4_pin = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), FIO_CAP4);
// }

// void pinmux_cap_ch4_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&cap4_pin));
// }

// void pinmux_cap_ch5_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&cap5_pin = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), FIO_CAP5);
// }

// void pinmux_cap_ch5_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&cap5_pin));
// }

// void pinmux_cap_ch6_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&cap6_pin = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), FIO_CAP6);
// }

// void pinmux_cap_ch6_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&cap6_pin));
// }

// void pinmux_cap_ch7_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&cap7_pin = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), FIO_CAP7);
// }

// void pinmux_cap_ch7_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&cap7_pin));
// }

// void pinmux_cap_ch8_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&cap8_pin = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), FIO_CAP8);
// }

// void pinmux_cap_ch8_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&cap8_pin));
// }

// void pinmux_cec_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&cec_pin = pin;
//     io_cfg_input(pin);
//     io_pull_write(pin, IO_PULL_UP);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), CEC_CH);
// }

// void pinmux_cec_deinit()
// {
//     io_pull_write(*(uint8_t *)&cec_pin, IO_PULL_DISABLE);
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&cec_pin));
// }

// void pinmux_owm_init(uint8_t pin)
// {
//     *(uint8_t *)&owm_pin = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), OWM_CH);
// }

// void pinmux_owm_deinit()
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&owm_pin));
// }

// ROM_SYMBOL void pinmux_hal_flash_init(void)
// {
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL0,SYSC_AWO_QSPI_EN,0xf);
// }

// ROM_SYMBOL void pinmux_hal_flash_deinit(void)
// {
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL0,SYSC_AWO_QSPI_EN,0x0);
// }

// ROM_SYMBOL void pinmux_hal_flash_quad_init(void)
// {
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL0,SYSC_AWO_QSPI_EN,0x3f);
// }

// ROM_SYMBOL void pinmux_hal_flash_quad_deinit(void)
// {
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL0,SYSC_AWO_QSPI_EN,0x0);
// }

// void pinmux_iic1_init(uint8_t scl,uint8_t sda)
// {
//     I2C_DBG_IO_CHECK(scl);
//     I2C_DBG_IO_CHECK(sda);
//     *(uint8_t *)&iic1_scl = scl;
//     *(uint8_t *)&iic1_sda = sda;
//     iic_io_cfg(scl,sda);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&scl), IIC1_SCL);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&sda), IIC1_SDA);
// }

// void pinmux_iic1_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&iic1_scl));
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&iic1_sda));
// }

// void pinmux_iic2_init(uint8_t scl,uint8_t sda)  
// {
//     I2C_DBG_IO_CHECK(scl);
//     I2C_DBG_IO_CHECK(sda);
//     *(uint8_t *)&iic2_scl = scl;
//     *(uint8_t *)&iic2_sda = sda;
//     iic_io_cfg(scl,sda);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&scl), IIC2_SCL);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&sda), IIC2_SDA);
// }

// void pinmux_iic2_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&iic2_scl));
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&iic2_sda));
// }

// void pinmux_iic3_init(uint8_t scl,uint8_t sda)  
// {
//     I2C_DBG_IO_CHECK(scl);
//     I2C_DBG_IO_CHECK(sda);
//     *(uint8_t *)&iic3_scl = scl;
//     *(uint8_t *)&iic3_sda = sda;
//     iic_io_cfg(scl,sda);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&scl), IIC3_SCL);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&sda), IIC3_SDA);
// }

// void pinmux_iic3_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&iic3_scl));
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&iic3_sda));
// }

// void pinmux_iic4_init(uint8_t scl,uint8_t sda)  
// {
//     I2C_DBG_IO_CHECK(scl);
//     I2C_DBG_IO_CHECK(sda);
//     *(uint8_t *)&iic4_scl = scl;
//     *(uint8_t *)&iic4_sda = sda;
//     iic_io_cfg(scl,sda);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&scl), IIC4_SCL);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&sda), IIC4_SDA);
// }

// void pinmux_iic4_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&iic4_scl));
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&iic4_sda));
// }

// void pinmux_iic5_init(uint8_t scl,uint8_t sda)  
// {
//     I2C_DBG_IO_CHECK(scl);
//     I2C_DBG_IO_CHECK(sda);
//     *(uint8_t *)&iic5_scl = scl;
//     *(uint8_t *)&iic5_sda = sda;
//     iic_io_cfg(scl,sda);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&scl), IIC5_SCL);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&sda), IIC5_SDA);
// }

// void pinmux_iic5_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&iic5_scl));
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&iic5_sda));
// }

// void pinmux_iic6_init(uint8_t scl,uint8_t sda)  
// {
//     I2C_DBG_IO_CHECK(scl);
//     I2C_DBG_IO_CHECK(sda);
//     *(uint8_t *)&iic6_scl = scl;
//     *(uint8_t *)&iic6_sda = sda;
//     iic_io_cfg(scl,sda);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&scl), IIC6_SCL);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&sda), IIC6_SDA);
// }

// void pinmux_iic6_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&iic6_scl));
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&iic6_sda));
// }

// void espi_high_speed_init()
// {
//     SYSC_AWO->IO[3].DIN = 0xfe000000;
// }

// void espi_high_speed_deinit()
// {
//     SYSC_AWO->IO[3].DIN = 0;
// }

// void pinmux_espi_init(void)
// {
//     SYSC_AWO->IO[3].IEN_OD &= ~0xfe000000;
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL0,SYSC_AWO_ESPI_EN,0x1);
// }

// void pinmux_espi_deinit(void)
// {
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL0,SYSC_AWO_ESPI_EN,0x0);
// }

// void pinmux_peci_init()
// {
//     uint8_t pin = PC04;
//     MODIFY_REG(V33_RG->TRIM0,0,1<<23);
//     io_pull_write(pin,IO_PULL_DOWN);
//     SYSC_AWO->IO[2].DS |= 0x00100010;
//     SYSC_AWO->IO[2].IEN_OD |= 0x0010;
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), PECI_DAT);
// }

// void pinmux_peci_deinit(void)
// {
//     uint8_t pin = PC04;
//     io_pull_write(pin,IO_PULL_DISABLE);
//     SYSC_AWO->IO[2].DS &= ~0x00100010;
//     SYSC_AWO->IO[2].IEN_OD &= ~0x0010;
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&pin));
//     MODIFY_REG(V33_RG->TRIM0,1<<23,0);
// }

// void pinmux_lpc_init(void)
// {
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL0, SYSC_AWO_LPC_EN, 0x1);
//     io_cfg_input(PD10);
//     io_cfg_input(PD11);
//     io_cfg_input(PD12);
//     io_cfg_input(PD13);
//     io_cfg_input(PD14);
//     io_cfg_input(PD15);
// }

// void pinmux_lpc_deinit(void)
// {
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL0, SYSC_AWO_LPC_EN, 0x0);
// }

// void pinmux_lpc_serirq_init(void)
// {
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL0, SYSC_AWO_LPC_SERIRQ_EN, 0x1);
// }

// void pinmux_lpc_serirq_deinit(void)
// {
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL0, SYSC_AWO_LPC_SERIRQ_EN, 0x0);
// }

// static void spi_nss_io_cfg(uint8_t nss)
// {
//     io_set_pin(nss);
//     io_pull_write(nss,IO_PULL_UP);
//     io_cfg_output(nss);
// }

// static void spi_mosi_io_cfg(uint8_t mosi)
// {
//     io_set_pin(mosi);
//     io_cfg_input(mosi);
//     io_cfg_output(mosi);
// }

// static void spi_miso_io_cfg(uint8_t miso)
// {
//     io_cfg_input(miso);
// }

// static void spi_master_clk_io_cfg(uint8_t clk, uint8_t cpol)
// {
//     if (cpol)
//     {
//         io_set_pin(clk);
//         io_pull_write(clk,IO_PULL_UP);
//     }
//     else
//     {
//         io_clr_pin(clk);
//         io_pull_write(clk,IO_PULL_DOWN);
//     }
//     io_cfg_output(clk);
// }

// static void spi_master_nss_io_cfg(uint8_t nss)
// {
//     io_set_pin(nss);
//     io_pull_write(nss,IO_PULL_UP);
//     io_cfg_output(nss);
// }

// static void spi_master_mosi_io_cfg(uint8_t mosi)
// {
//     io_set_pin(mosi);
//     io_cfg_output(mosi);
// }

// static void spi_master_miso_io_cfg(uint8_t miso)
// {
//     io_cfg_input(miso);
// }

// static void spi_slave_clk_io_cfg(uint8_t clk)
// {
//     io_cfg_input(clk);
// }

// static void spi_slave_nss_io_cfg(uint8_t nss)
// {
//     io_pull_write(nss,IO_PULL_UP);
//     io_cfg_input(nss);
// }

// static void spi_slave_mosi_io_cfg(uint8_t mosi)
// {
//     io_cfg_input(mosi);
// }

// static void spi_slave_miso_io_cfg(uint8_t miso)
// {
//     io_set_pin(miso);
//     io_cfg_output(miso);
// }

// void pinmux_spi2_master_clk_init(uint8_t clk, uint8_t cpol)
// {
//     I2C_DBG_IO_CHECK(clk);
//     *(uint8_t *)&spi2_clk = clk;
//     spi_master_clk_io_cfg(clk, cpol);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&clk),SPI2_SCK);
// }

// void pinmux_spi2_master_nss_init(uint8_t nss)
// {
//     I2C_DBG_IO_CHECK(nss);
//     *(uint8_t *)&spi2_nss = nss;
//     spi_master_nss_io_cfg( nss);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&nss),SPI2_NSS);  
// }

// void pinmux_spi2_master_mosi_init(uint8_t mosi)
// {
//     I2C_DBG_IO_CHECK(mosi);
//     *(uint8_t *)&spi2_mosi = mosi;
//     spi_master_mosi_io_cfg( mosi);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&mosi),SPI2_MOSI);
// }

// void pinmux_spi2_master_miso_init(uint8_t miso)
// {
//     I2C_DBG_IO_CHECK(miso);
//     *(uint8_t *)&spi2_miso = miso;
//     spi_master_miso_io_cfg( miso);    
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&miso),SPI2_MISO);
// }

// void pinmux_spi2_slave_clk_init(uint8_t clk)
// {
//     I2C_DBG_IO_CHECK(clk);
//     *(uint8_t *)&spi2_clk = clk;
//     spi_slave_clk_io_cfg( clk);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&clk),SPI2_SCK);
// }

// void pinmux_spi2_slave_nss_init(uint8_t nss)
// {
//     I2C_DBG_IO_CHECK(nss);
//     *(uint8_t *)&spi2_nss = nss;
//     spi_slave_nss_io_cfg( nss);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&nss),SPI2_NSS);  
// }

// void pinmux_spi2_slave_mosi_init(uint8_t mosi)
// {
//     I2C_DBG_IO_CHECK(mosi);
//     *(uint8_t *)&spi2_mosi = mosi;
//     spi_slave_mosi_io_cfg( mosi);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&mosi),SPI2_MOSI);
// }

// void pinmux_spi2_slave_miso_init(uint8_t miso)
// {
//     I2C_DBG_IO_CHECK(miso);
//     *(uint8_t *)&spi2_miso = miso;
//     spi_slave_miso_io_cfg( miso);    
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&miso),SPI2_MISO);
// }

// void pinmux_spi2_clk_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&spi2_clk);
// }

// void pinmux_spi2_nss_deinit(void)
// {
//     io_pull_write(*(uint8_t *)&spi2_nss,IO_PULL_DISABLE);
//     set_gpio_mode((gpio_port_pin_t *)&spi2_nss);
// }

// void pinmux_spi2_mosi_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&spi2_mosi);
// }

// void pinmux_spi2_miso_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&spi2_miso);
// }

// void pinmux_spi3_master_clk_init(uint8_t clk, uint8_t cpol)
// {
//     I2C_DBG_IO_CHECK(clk);
//     *(uint8_t *)&spi3_clk = clk;
//     spi_master_clk_io_cfg(clk, cpol);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&clk),SPI3_SCK);
// }

// void pinmux_spi3_master_nss_init(uint8_t nss)
// {
//     I2C_DBG_IO_CHECK(nss);
//     *(uint8_t *)&spi3_nss = nss;
//     spi_master_nss_io_cfg( nss);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&nss),SPI3_NSS);  
// }

// void pinmux_spi3_master_mosi_init(uint8_t mosi)
// {
//     I2C_DBG_IO_CHECK(mosi);
//     *(uint8_t *)&spi3_mosi = mosi;
//     spi_master_mosi_io_cfg( mosi);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&mosi),SPI3_MOSI);
// }

// void pinmux_spi3_master_miso_init(uint8_t miso)
// {
//     I2C_DBG_IO_CHECK(miso);
//     *(uint8_t *)&spi3_miso = miso;
//     spi_master_miso_io_cfg( miso);    
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&miso),SPI3_MISO);
// }

// void pinmux_spi3_slave_clk_init(uint8_t clk)
// {
//     I2C_DBG_IO_CHECK(clk);
//     *(uint8_t *)&spi3_clk = clk;
//     spi_slave_clk_io_cfg( clk);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&clk),SPI3_SCK);
// }

// void pinmux_spi3_slave_nss_init(uint8_t nss)
// {
//     I2C_DBG_IO_CHECK(nss);
//     *(uint8_t *)&spi3_nss = nss;
//     spi_slave_nss_io_cfg( nss);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&nss),SPI3_NSS);  
// }

// void pinmux_spi3_slave_mosi_init(uint8_t mosi)
// {
//     I2C_DBG_IO_CHECK(mosi);
//     *(uint8_t *)&spi3_mosi = mosi;
//     spi_slave_mosi_io_cfg( mosi);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&mosi),SPI3_MOSI);
// }

// void pinmux_spi3_slave_miso_init(uint8_t miso)
// {
//     I2C_DBG_IO_CHECK(miso);
//     *(uint8_t *)&spi3_miso = miso;
//     spi_slave_miso_io_cfg( miso);    
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&miso),SPI3_MISO);
// }

// void pinmux_spi3_clk_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&spi3_clk);
// }

// void pinmux_spi3_nss_deinit(void)
// {
//     io_pull_write(*(uint8_t *)&spi3_nss,IO_PULL_DISABLE);
//     set_gpio_mode((gpio_port_pin_t *)&spi3_nss);
// }

// void pinmux_spi3_mosi_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&spi3_mosi);
// }

// void pinmux_spi3_miso_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&spi3_miso);
// }

// void pinmux_spis_init(void)
// {
//     io_cfg_input(PE00);
//     io_cfg_input(PE01);
//     io_cfg_input(PE02);
//     io_cfg_output(PE03);
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL0, SYSC_AWO_SPIS_EN,1);
// }

// void pinmux_spis_deinit(void)
// {
//     uint8_t pin = PE00;
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL0, SYSC_AWO_SPIS_EN,0);
//     set_gpio_mode((gpio_port_pin_t *)&pin);
//     pin = PE01;
//     set_gpio_mode((gpio_port_pin_t *)&pin);
//     pin = PE02;
//     set_gpio_mode((gpio_port_pin_t *)&pin);
//     pin = PE03;
//     set_gpio_mode((gpio_port_pin_t *)&pin);
// }

// void pinmux_ssi_clk_init(uint8_t clk, uint8_t cpol)
// {
//     I2C_DBG_IO_CHECK(clk);
//     *(uint8_t *)&ssi_clk = clk;
//     spi_master_clk_io_cfg(clk,cpol);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&clk),SPI1_SCK);
// }

// void pinmux_ssi_nss0_init(uint8_t nss0)
// {
//     I2C_DBG_IO_CHECK(nss0);
//     *(uint8_t *)&ssi_nss0 = nss0;
//     spi_nss_io_cfg(nss0);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&nss0),SPI1_NSS0);
// }

// void pinmux_ssi_nss1_init(uint8_t nss1)
// {
//     I2C_DBG_IO_CHECK(nss1);
//     *(uint8_t *)&ssi_nss1 = nss1;
//     spi_nss_io_cfg(nss1);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&nss1),SPI1_NSS1);
// }

// void pinmux_ssi_dq0_init(uint8_t dq0)
// {
//     I2C_DBG_IO_CHECK(dq0);
//     *(uint8_t *)&ssi_dq0 = dq0;
//     spi_mosi_io_cfg(dq0);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&dq0),SPI1_DQ0);
// }

// void pinmux_ssi_dq1_init(uint8_t dq1)
// {
//     I2C_DBG_IO_CHECK(dq1);
//     *(uint8_t *)&ssi_dq1 = dq1;
//     spi_miso_io_cfg(dq1);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&dq1),SPI1_DQ1);
// }

// void pinmux_ssi_dq2_init(uint8_t dq2)
// {
//     I2C_DBG_IO_CHECK(dq2);
//     *(uint8_t *)&ssi_dq2 = dq2;
//     spi_miso_io_cfg(dq2);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&dq2),SPI1_DQ2);
// }

// void pinmux_ssi_dq3_init(uint8_t dq3)
// {
//     I2C_DBG_IO_CHECK(dq3);
//     *(uint8_t *)&ssi_dq3 = dq3;
//     spi_miso_io_cfg(dq3);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&dq3),SPI1_DQ3);
// }

// void pinmux_ssi_deinit(void)
// {
// 	set_gpio_mode((gpio_port_pin_t *)&ssi_clk);
// 	set_gpio_mode((gpio_port_pin_t *)&ssi_nss0);
// 	set_gpio_mode((gpio_port_pin_t *)&ssi_dq0);
// 	set_gpio_mode((gpio_port_pin_t *)&ssi_dq1);
// }

// void pinmux_ssi_clk_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&ssi_clk);
// }

// void pinmux_ssi_nss0_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&ssi_nss0);
// }

// void pinmux_ssi_nss1_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&ssi_nss1);
// }

// void pinmux_ssi_dq0_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&ssi_dq0);
// }

// void pinmux_ssi_dq1_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&ssi_dq1);
// }

// void pinmux_ssi_dq2_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&ssi_dq2);
// }

// void pinmux_ssi_dq3_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&ssi_dq3);
// }

// static void iis_master_ck_io_cfg(uint8_t ck)
// {
//     io_clr_pin(ck);
//     io_pull_write(ck,IO_PULL_DOWN);
//     io_cfg_output(ck);
// }

// static void iis_master_ws_io_cfg(uint8_t ws)
// {
//     io_set_pin(ws);
//     io_pull_write(ws,IO_PULL_UP);
//     io_cfg_output(ws);
// }

// static void iis_master_sd_io_cfg(uint8_t sd, uint8_t mode)
// {
//     if (mode)
//     {
//         io_set_pin(sd);
//         io_cfg_output(sd);
//     }
//     else 
//     {
//         io_cfg_input(sd);
//     }
// }

// static void iis_master_mck_io_cfg(uint8_t mck)
// {
//     io_clr_pin(mck);
//     io_pull_write(mck,IO_PULL_DOWN);
//     io_cfg_output(mck);
// }

// static void iis_slave_ck_io_cfg(uint8_t ck)
// {
//     io_cfg_input(ck);
// }

// static void iis_slave_ws_io_cfg(uint8_t ws)
// {
//     io_pull_write(ws,IO_PULL_UP);
//     io_cfg_input(ws);
// }

// static void iis_slave_sd_io_cfg(uint8_t sd, uint8_t mode)
// {
//     if (mode)
//     {
//         io_set_pin(sd);
//         io_cfg_output(sd);
//     }
//     else 
//     {
//         io_cfg_input(sd);
//     }
// }

// static void iis_slave_mck_io_cfg(uint8_t mck)
// {
//     io_cfg_input(mck);
// }

// void pinmux_iis2_master_ck_init(uint8_t ck)
// {
//     I2C_DBG_IO_CHECK(ck);
//     *(uint8_t *)&i2s2_ck = ck;
//     iis_master_ck_io_cfg(ck);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&ck),SPI2_SCK);
// }

// void pinmux_iis2_master_ws_init(uint8_t ws)
// {
//     I2C_DBG_IO_CHECK(ws);
//     *(uint8_t *)&i2s2_ws = ws;
//     iis_master_ws_io_cfg(ws);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&ws),SPI2_NSS);    
// }

// void pinmux_iis2_master_sd_init(uint8_t sd, uint8_t mode)
// {
//     I2C_DBG_IO_CHECK(sd);
//     *(uint8_t *)&i2s2_sd = sd;
//     iis_master_sd_io_cfg(sd, mode);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&sd),SPI2_MOSI);
// }

// void pinmux_iis2_master_mck_init(uint8_t mck)
// {
//     I2C_DBG_IO_CHECK(mck);
//     *(uint8_t *)&i2s2_mck = mck;
//     iis_master_mck_io_cfg( mck);    
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&mck),SPI2_IIS);
// }

// void pinmux_iis2_slave_ck_init(uint8_t ck)
// {
//     I2C_DBG_IO_CHECK(ck);
//     *(uint8_t *)&i2s2_ck = ck;
//     iis_slave_ck_io_cfg(ck);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&ck),SPI2_SCK);
// }

// void pinmux_iis2_slave_ws_init(uint8_t ws)
// {
//     I2C_DBG_IO_CHECK(ws);
//     *(uint8_t *)&i2s2_ws = ws;
//     iis_slave_ws_io_cfg(ws);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&ws),SPI2_NSS);    
// }

// void pinmux_iis2_slave_sd_init(uint8_t sd, uint8_t mode)
// {
//     I2C_DBG_IO_CHECK(sd);
//     *(uint8_t *)&i2s2_sd = sd;
//     iis_slave_sd_io_cfg(sd, mode);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&sd),SPI2_MOSI);
// }

// void pinmux_iis2_slave_mck_init(uint8_t mck)
// {
//     I2C_DBG_IO_CHECK(mck);
//     *(uint8_t *)&i2s2_mck = mck;
//     iis_slave_mck_io_cfg( mck);    
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&mck),SPI2_IIS);
// }

// void pinmux_iis2_ck_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&i2s2_ck);
// }

// void pinmux_iis2_ws_deinit(void)
// {
//     io_pull_write(*(uint8_t *)&i2s2_ws,IO_PULL_DISABLE);
//     set_gpio_mode((gpio_port_pin_t *)&i2s2_ws);
// }

// void pinmux_iis2_sd_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&i2s2_sd);
// }

// void pinmux_iis2_mck_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&i2s2_mck);
// }

// void pinmux_iis3_master_ck_init(uint8_t ck)
// {
//     I2C_DBG_IO_CHECK(ck);
//     *(uint8_t *)&i2s3_ck = ck;
//     iis_master_ck_io_cfg(ck);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&ck),SPI3_SCK);
// }

// void pinmux_iis3_master_ws_init(uint8_t ws)
// {
//     I2C_DBG_IO_CHECK(ws);
//     *(uint8_t *)&i2s3_ws = ws;
//     iis_master_ws_io_cfg(ws);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&ws),SPI3_NSS);  
// }

// void pinmux_iis3_master_sd_init(uint8_t sd, uint8_t mode)
// {
//     I2C_DBG_IO_CHECK(sd);
//     *(uint8_t *)&i2s3_sd = sd;
//     iis_master_sd_io_cfg(sd, mode);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&sd),SPI3_MOSI);
// }

// void pinmux_iis3_master_mck_init(uint8_t mck)
// {
//     I2C_DBG_IO_CHECK(mck);
//     *(uint8_t *)&i2s3_mck = mck;
//     iis_master_mck_io_cfg( mck);    
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&mck),SPI3_IIS);
// }

// void pinmux_iis3_slave_ck_init(uint8_t ck)
// {
//     I2C_DBG_IO_CHECK(ck);
//     *(uint8_t *)&i2s3_ck = ck;
//     iis_slave_ck_io_cfg(ck);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&ck),SPI3_SCK);
// }

// void pinmux_iis3_slave_ws_init(uint8_t ws)
// {
//     I2C_DBG_IO_CHECK(ws);
//     *(uint8_t *)&i2s3_ws = ws;
//     iis_slave_ws_io_cfg(ws);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&ws),SPI3_NSS);  
// }

// void pinmux_iis3_slave_sd_init(uint8_t sd, uint8_t mode)
// {
//     I2C_DBG_IO_CHECK(sd);
//     *(uint8_t *)&i2s3_sd = sd;
//     iis_slave_sd_io_cfg(sd, mode);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&sd),SPI3_MOSI);
// }

// void pinmux_iis3_slave_mck_init(uint8_t mck)
// {
//     I2C_DBG_IO_CHECK(mck);
//     *(uint8_t *)&i2s3_mck = mck;
//     iis_slave_mck_io_cfg( mck);    
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&mck),SPI3_IIS);
// }

// void pinmux_iis3_ck_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&i2s3_ck);
// }

// void pinmux_iis3_ws_deinit(void)
// {
//     io_pull_write(*(uint8_t *)&i2s3_ws,IO_PULL_DISABLE);
//     set_gpio_mode((gpio_port_pin_t *)&i2s3_ws);
// }

// void pinmux_iis3_sd_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&i2s3_sd);
// }

// void pinmux_iis3_mck_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&i2s3_mck);
// }

// void pinmux_pdm_clk_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&pdm_clk = pin;
//     io_cfg_output(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pdm_clk), PDM_CLK);
// }

// void pinmux_pdm_clk_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&pdm_clk);
// }

// void pinmux_pdm_data0_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&pdm_data0 = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pdm_data0), PDM_DATA0);
// }

// void pinmux_pdm_data0_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&pdm_data0);
// }

// void pinmux_pdm_data1_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&pdm_data1 = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pdm_data1), PDM_DATA1);
// }

// void pinmux_pdm_data1_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&pdm_data1);
// }

// static void io_ae1_enable(uint8_t pin, uint8_t val)
// {
//     if(i2c_dbg_io_check(pin))
//     {
//         return;
//     }
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     SYSC_AWO->IO[x->port].AE |= 1 << (x->num + 16);
// }

// void pinmux_touchkey_cmod_init()
// {
//     io_ae1_enable(PC02, 1);
// }

// void pinmux_touchkey_cmod_deinit()
// {
//     io_ae1_enable(PC02, 0);
// }

// void pinmux_touchkey_ch0_init()
// {
//     io_ae1_enable(PC03, 1);
// }

// void pinmux_touchkey_ch0_deinit()
// {
//     io_ae1_enable(PC03, 0);
// }

// void pinmux_touchkey_ch1_init()
// {
//     io_ae1_enable(PC05, 1);
// }

// void pinmux_touchkey_ch1_deinit()
// {
//     io_ae1_enable(PC05, 0);
// }

// void pinmux_touchkey_ch2_init()
// {
//     io_ae1_enable(PC06, 1);
// }

// void pinmux_touchkey_ch2_deinit()
// {
//     io_ae1_enable(PC06, 0);
// }

// void pinmux_touchkey_ch3_init()
// {
//     io_ae1_enable(PC07, 1);
// }

// void pinmux_touchkey_ch3_deinit()
// {
//     io_ae1_enable(PC07, 0);
// }

// void pinmux_touchkey_ch4_init()
// {
//     io_ae1_enable(PC08, 1);
// }

// void pinmux_touchkey_ch4_deinit()
// {
//     io_ae1_enable(PC08, 0);
// }

// void pinmux_touchkey_ch5_init()
// {
//     io_ae1_enable(PC09, 1);
// }

// void pinmux_touchkey_ch5_deinit()
// {
//     io_ae1_enable(PC09, 0);
// }

// void pinmux_touchkey_ch6_init()
// {
//     io_ae1_enable(PC10, 1);
// }

// void pinmux_touchkey_ch6_deinit()
// {
//     io_ae1_enable(PC10, 0);
// }

// void pinmux_touchkey_ch7_init()
// {
//     io_ae1_enable(PC11, 1);
// }

// void pinmux_touchkey_ch7_deinit()
// {
//     io_ae1_enable(PC11, 0);
// }

// void pinmux_touchkey_ch8_init()
// {
//     io_ae1_enable(PC12, 1);
// }

// void pinmux_touchkey_ch8_deinit()
// {
//     io_ae1_enable(PC12, 0);
// }

// void pinmux_touchkey_ch9_init()
// {
//     io_ae1_enable(PC14, 1);
// }

// void pinmux_touchkey_ch9_deinit()
// {
//     io_ae1_enable(PC14, 0);
// }

// void pinmux_touchkey_ch10_init()
// {
//     io_ae1_enable(PD03, 1);
// }

// void pinmux_touchkey_ch10_deinit()
// {
//     io_ae1_enable(PD03, 0);
// }

// void pinmux_touchkey_ch11_init()
// {
//     io_ae1_enable(PD05, 1);
// }

// void pinmux_touchkey_ch11_deinit()
// {
//     io_ae1_enable(PD05, 0);
// }

// void pinmux_touchkey_ch12_init()
// {
//     io_ae1_enable(PD07, 1);
// }

// void pinmux_touchkey_ch12_deinit()
// {
//     io_ae1_enable(PD07, 0);
// }

// void pinmux_touchkey_ch13_init()
// {
//     io_ae1_enable(PD09, 1);
// }

// void pinmux_touchkey_ch13_deinit()
// {
//     io_ae1_enable(PD09, 0);
// }

// void pinmux_touchkey_ch14_init()
// {
//     io_ae1_enable(PD10, 1);
// }

// void pinmux_touchkey_ch14_deinit()
// {
//     io_ae1_enable(PD10, 0);
// }

// void pinmux_touchkey_ch15_init()
// {
//     io_ae1_enable(PD11, 1);
// }

// void pinmux_touchkey_ch15_deinit()
// {
//     io_ae1_enable(PD11, 0);
// }

// void io_cfg_disable(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     SYSC_AWO->IO[x->port].OE_FIR &= ~(1<<16<<x->num);
//     SYSC_AWO->IO[x->port].IEN_OD |= 1<<16<<x->num; 
// }

// void gpio_ana_func1_deinit(uint8_t ain)
// {
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&ain;
//     SYSC_AWO->IO[x->port].AE &= ~(1<<16<<x->num);
//     io_cfg_disable(ain);
// }

// void gpio_ana_func2_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     SYSC_AWO->IO[x->port].AE |= 1<<x->num;
// }

// void gpio_ana_func2_deinit(uint8_t ain)
// {
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&ain;
//     SYSC_AWO->IO[x->port].AE &= ~(1<<x->num);
//     io_cfg_disable(ain);
// }

// void gpio_ana_func1_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
//     SYSC_AWO->IO[x->port].AE |= 1<<16<<x->num;
// }

// void pinmux_adc1_in0_init(void)
// {
//     gpio_ana_func1_init(PA09);
// }

// void pinmux_adc1_in0_deinit(void)
// {
//     gpio_ana_func1_deinit(PA09);
// }

// void pinmux_adc1_in1_init(void)
// {
//     gpio_ana_func1_init(PA10);
// }

// void pinmux_adc1_in1_deinit(void)
// {
//     gpio_ana_func1_deinit(PA10);
// }

// void pinmux_adc1_in2_init(void)
// {
//     gpio_ana_func1_init(PA11);
// }

// void pinmux_adc1_in2_deinit(void)
// {
//     gpio_ana_func1_deinit(PA11);
// }

// void pinmux_adc1_in3_init(void)
// {
//     gpio_ana_func1_init(PA12);
// }

// void pinmux_adc1_in3_deinit(void)
// {
//     gpio_ana_func1_deinit(PA12);
// }

// void pinmux_adc1_in4_init(void)
// {
//     gpio_ana_func1_init(PA13);
// }

// void pinmux_adc1_in4_deinit(void)
// {
//     gpio_ana_func1_deinit(PA13);
// }

// void pinmux_adc1_in5_init(void)
// {
//     gpio_ana_func1_init(PA14);
// }

// void pinmux_adc1_in5_deinit(void)
// {
//     gpio_ana_func1_deinit(PA14);
// }

// void pinmux_adc1_in6_init(void)
// {
//     gpio_ana_func1_init(PA15);
// }

// void pinmux_adc1_in6_deinit(void)
// {
//     gpio_ana_func1_deinit(PA15);
// }

// void pinmux_adc1_in7_init(void)
// {
//     gpio_ana_func1_init(PB00);
// }

// void pinmux_adc1_in7_deinit(void)
// {
//     gpio_ana_func1_deinit(PB00);
// }

// void pinmux_adc2_in0_init(void)
// {
//     gpio_ana_func1_init(PH08);
// }

// void pinmux_adc2_in0_deinit(void)
// {
//     gpio_ana_func1_deinit(PH08);
// }

// void pinmux_adc2_in1_init(void)
// {
//     gpio_ana_func1_init(PH09);
// }

// void pinmux_adc2_in1_deinit(void)
// {
//     gpio_ana_func1_deinit(PH09);
// }

// void pinmux_adc2_in2_init(void)
// {
//     gpio_ana_func1_init(PH10);
// }

// void pinmux_adc2_in2_deinit(void)
// {
//     gpio_ana_func1_deinit(PH10);
// }

// void pinmux_adc2_in3_init(void)
// {
//     gpio_ana_func1_init(PH11);
// }

// void pinmux_adc2_in3_deinit(void)
// {
//     gpio_ana_func1_deinit(PH11);
// }

// void pinmux_adc2_in4_init(void)
// {
//     gpio_ana_func1_init(PH12);
// }

// void pinmux_adc2_in4_deinit(void)
// {
//     gpio_ana_func1_deinit(PH12);
// }

// void pinmux_adc2_in5_init(void)
// {
//     gpio_ana_func1_init(PH13);
// }

// void pinmux_adc2_in5_deinit(void)
// {
//     gpio_ana_func1_deinit(PH13);
// }

// void pinmux_adc2_in6_init(void)
// {
//     gpio_ana_func1_init(PH14);
// }

// void pinmux_adc2_in6_deinit(void)
// {
//     gpio_ana_func1_deinit(PH14);
// }

// void pinmux_adc2_in7_init(void)
// {
//     gpio_ana_func1_init(PH15);
// }

// void pinmux_adc2_in7_deinit(void)
// {
//     gpio_ana_func1_deinit(PH15);
// }

// void pinmux_amic_init(void)
// {
//     gpio_ana_func1_init(PA00);
// } 

// void pinmux_amic_deinit(void)
// {
//     gpio_ana_func1_deinit(PA00);
// } 

// void pinmux_dac1_out1_init(void)
// {
//     gpio_ana_func1_init(PA02);
// }

// void pinmux_dac1_out1_deinit(void)
// {
//     gpio_ana_func1_deinit(PA02);
// }

// void pinmux_dac1_out2_init(void)
// {
//     gpio_ana_func1_init(PA04);
// }

// void pinmux_dac1_out2_deinit(void)
// {
//     gpio_ana_func1_deinit(PA04);
// }

// void pinmux_dac2_out1_init(void)
// {
//     gpio_ana_func1_init(PA03);
// }

// void pinmux_dac2_out1_deinit(void)
// {
//     gpio_ana_func1_deinit(PA03);
// }

// void pinmux_dac2_out2_init(void)
// {
//     gpio_ana_func1_init(PA05);
// }

// void pinmux_dac2_out2_deinit(void)
// {
//     gpio_ana_func1_deinit(PA05);
// }

// static void  comp_io_cfg(uint8_t dat)
// {
//     io_clr_pin(dat);
//     io_cfg_output(dat);
// }

// void pinmux_comp1_init(uint8_t dat)
// {
//     I2C_DBG_IO_CHECK(dat);
//     *(uint8_t *)&comp1_dat = dat;
//     comp_io_cfg(dat);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&dat),COMP1);
// }

// void pinmux_comp1_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&comp1_dat));
// }

// void pinmux_comp2_init(uint8_t dat)
// {
//     I2C_DBG_IO_CHECK(dat);
//     *(uint8_t *)&comp2_dat = dat;
//     comp_io_cfg(dat);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&dat),COMP2);
// }

// void pinmux_comp2_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&comp2_dat));
// }

// void pinmux_comp3_init(uint8_t dat)
// {
//     I2C_DBG_IO_CHECK(dat);
//     *(uint8_t *)&comp3_dat = dat;
//     comp_io_cfg(dat);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&dat),COMP3);
// }

// void pinmux_comp3_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&comp3_dat));
// }

// void pinmux_fdcan_init(uint8_t txd,uint8_t rxd)
// {
//     I2C_DBG_IO_CHECK(txd);
//     I2C_DBG_IO_CHECK(rxd);
//     *(uint8_t *)&fdcan_txd = txd;
//     *(uint8_t *)&fdcan_rxd = rxd;
//     uart_io_cfg(txd,rxd);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&txd),FDCAN_TXD);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&rxd),FDCAN_RXD);
// }

// void pinmux_fdcan_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&fdcan_txd));
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&fdcan_rxd));
// }

// static void timer_ch_io_output_cfg(uint8_t pin,uint8_t default_val)
// {
//     io_write_pin(pin, default_val);
//     io_cfg_output(pin);
// }

// static void timer_ch_io_cfg(uint8_t pin,bool output,uint8_t default_val)
// {
//     if(output)
//     {
//         timer_ch_io_output_cfg(pin,default_val);
//     }else
//     {
//         io_cfg_input(pin);
//     }
// }

// void pinmux_adtim1_ch1_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim1_ch1 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM1_CH1);
// }

// void set_gpio_mode(gpio_port_pin_t *pin)
// {
//     per_func_disable(pin2func_io(pin));
// }

// void pinmux_adtim1_ch1_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim1_ch1);
// }

// void pinmux_adtim1_ch2_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim1_ch2 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM1_CH2);
// }

// void pinmux_adtim1_ch2_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim1_ch2);
// }

// void pinmux_adtim1_ch3_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim1_ch3 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM1_CH3);
// }

// void pinmux_adtim1_ch3_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim1_ch3);
// }

// void pinmux_adtim1_ch4_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim1_ch4 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM1_CH4);
// }

// void pinmux_adtim1_ch4_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim1_ch4);
// }

// void pinmux_adtim1_ch1n_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim1_ch1n = pin;
//     timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim1_ch1));
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM1_CH1N);
// }

// void pinmux_adtim1_ch1n_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim1_ch1n);
// }

// void pinmux_adtim1_ch2n_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim1_ch2n = pin;
//     timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim1_ch2));
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM1_CH2N);
// }

// void pinmux_adtim1_ch2n_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim1_ch2n);
// }

// void pinmux_adtim1_ch3n_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim1_ch3n = pin;
//     timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim1_ch3));
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM1_CH3N);
// }

// void pinmux_adtim1_ch3n_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim1_ch3n);
// }

// void pinmux_adtim1_etr_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim1_etr = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM1_ETR);
// }

// void pinmux_adtim1_etr_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim1_etr);
// }

// void pinmux_adtim1_bk_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim1_bk = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM1_BK);
// }

// void pinmux_adtim1_bk_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim1_bk);
// }


// void pinmux_adtim2_ch1_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim2_ch1 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM2_CH1);
// }

// void pinmux_adtim2_ch1_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim2_ch1);
// }

// void pinmux_adtim2_ch2_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim2_ch2 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM2_CH2);
// }

// void pinmux_adtim2_ch2_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim2_ch2);
// }

// void pinmux_adtim2_ch3_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim2_ch3 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM2_CH3);
// }

// void pinmux_adtim2_ch3_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim2_ch3);
// }

// void pinmux_adtim2_ch4_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim2_ch4 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM2_CH4);
// }

// void pinmux_adtim2_ch4_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim2_ch4);
// }

// void pinmux_adtim2_ch1n_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim1_ch1n = pin;
//     timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim2_ch1));
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM2_CH1N);
// }

// void pinmux_adtim2_ch1n_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim2_ch1n);
// }

// void pinmux_adtim2_ch2n_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim1_ch2n = pin;
//     timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim2_ch2));
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM2_CH2N);
// }

// void pinmux_adtim2_ch2n_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim2_ch2n);
// }

// void pinmux_adtim2_ch3n_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim2_ch3n = pin;
//     timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim2_ch3));
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM2_CH3N);
// }

// void pinmux_adtim2_ch3n_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim2_ch3n);
// }

// void pinmux_adtim2_etr_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim2_etr = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM2_ETR);
// }

// void pinmux_adtim2_etr_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim2_etr);
// }

// void pinmux_adtim2_bk_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&adtim2_bk = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),ADTIM2_BK);
// }

// void pinmux_adtim2_bk_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&adtim2_bk);
// }

// void pinmux_gptima1_ch1_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&gptima1_ch1 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),GPTIMA1_CH1);
// }

// void pinmux_gptima1_ch1_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&gptima1_ch1);
// }

// void pinmux_gptima1_ch2_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&gptima1_ch2 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),GPTIMA1_CH2);
// }

// void pinmux_gptima1_ch2_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&gptima1_ch2);
// }

// void pinmux_gptima1_ch3_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&gptima1_ch3 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),GPTIMA1_CH3);
// }

// void pinmux_gptima1_ch3_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&gptima1_ch3);
// }

// void pinmux_gptima1_ch4_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&gptima1_ch4 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),GPTIMA1_CH4);
// }

// void pinmux_gptima1_ch4_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&gptima1_ch4);
// }

// void pinmux_gptima1_etr_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&gptima1_etr = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),GPTIMA1_ETR);
// }

// void pinmux_gptima1_etr_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&gptima1_etr);
// }

// void pinmux_gptimb1_ch1_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&gptimb1_ch1 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),GPTIMB1_CH1);
// }

// void pinmux_gptimb1_ch1_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&gptimb1_ch1);
// }

// void pinmux_gptimb1_ch2_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&gptimb1_ch2 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),GPTIMB1_CH2);
// }

// void pinmux_gptimb1_ch2_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&gptimb1_ch2);
// }

// void pinmux_gptimb1_ch3_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&gptimb1_ch3 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),GPTIMB1_CH3);
// }

// void pinmux_gptimb1_ch3_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&gptimb1_ch3);
// }

// void pinmux_gptimb1_ch4_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&gptimb1_ch4 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),GPTIMB1_CH4);
// }

// void pinmux_gptimb1_ch4_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&gptimb1_ch4);
// }

// void pinmux_gptimb1_etr_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&gptimb1_etr = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),GPTIMB1_ETR);
// }

// void pinmux_gptimb1_etr_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&gptimb1_etr);
// }

// void pinmux_gptimc1_ch1_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&gptimc1_ch1 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),GPTIMC1_CH1);
// }

// void pinmux_gptimc1_ch1_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&gptimc1_ch1);
// }

// void pinmux_gptimc1_ch1n_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&gptimc1_ch1n = pin;
//     timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&gptimc1_ch1));
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),GPTIMC1_CH1N);
// }

// void pinmux_gptimc1_ch1n_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&gptimc1_ch1n);
// }

// void pinmux_gptimc1_ch2_init(uint8_t pin,bool output,uint8_t default_val)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&gptimc1_ch2 = pin;
//     timer_ch_io_cfg(pin,output,default_val);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),GPTIMC1_CH2);
// }

// void pinmux_gptimc1_ch2_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&gptimc1_ch2);
// }

// void pinmux_gptimc1_bk_init(uint8_t pin)
// {
//     I2C_DBG_IO_CHECK(pin);
//     *(uint8_t *)&gptimc1_bk = pin;
//     io_cfg_input(pin);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin),GPTIMC1_BK);
// }

// void pinmux_gptimc1_bk_deinit(void)
// {
//     set_gpio_mode((gpio_port_pin_t *)&gptimc1_bk);
// }

// static void usb_io_cfg(uint8_t dp,uint8_t dm, bool host)
// {
//     if(host)
//     {
//         io_pull_write(dp,IO_PULL_DOWN);
//     }else
//     {
//         io_pull_write(dp,IO_PULL_UP);
//     }
//     io_pull_write(dm,IO_PULL_DOWN);
//     io_cfg_input(dm);
//     io_cfg_input(dp);
// }

// void PD00_PD01_PowerOn(void)
// {
//     SYSC_AWO->IO[3].DS |= 1 << 16 << 1;
// }

// void pinmux_usb_init(bool host)
// {
//     uint8_t dp = USB_DP_PAD;
//     uint8_t dm = USB_DM_PAD;
//     usb_io_cfg(dp,dm,host);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&dp),USB_DP);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&dm),USB_DM);
    
//     PD00_PD01_PowerOn();

//     REG_FIELD_WR(SYSC_CPU->GATE_SYS,SYSC_CPU_USB_RX_DIFF_SEL,1);
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL0, SYSC_AWO_USB_PUPD, 1);
//     if (otg_id == 0xff)
//     {
//         REG_FIELD_WR(SYSC_AWO->PIN_SEL0, SYSC_AWO_USB_CID, 0x2 + !host);
//     }
// }

// void pinmux_usb_otg_id_init(uint8_t pin)
// {
//     otg_id = pin;
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL0, SYSC_AWO_USB_CID, 0);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&pin), USB_CID);
// }

// void pinmux_usb_deinit(void)
// {
//     uint8_t dp = USB_DP_PAD;
//     uint8_t dm = USB_DM_PAD;
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&dp));
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&dm));
//     if (otg_id != 0xff)
//     {
//         per_func_disable(pin2func_io((gpio_port_pin_t *)&otg_id));
//     }
// }

// static void ps2h_io_cfg(uint8_t clk, uint8_t dat)
// {
//     io_cfg_input(clk);
//     io_cfg_input(dat);
//     io_pull_write(dat, IO_PULL_UP);
//     io_pull_write(clk, IO_PULL_UP);
// }

// void pinmux_ps2h1_init(uint8_t clk, uint8_t dat)
// {
//     I2C_DBG_IO_CHECK(clk);
//     I2C_DBG_IO_CHECK(dat);
//     *(uint8_t *)&ps2h1_clk = clk;
//     *(uint8_t *)&ps2h1_dat = dat;
//     ps2h_io_cfg(clk,dat);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&clk),PS2H1_CLK);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&dat),PS2H1_DAT);
// }

// void pinmux_ps2h1_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&ps2h1_clk));
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&ps2h1_dat));
// }

// void pinmux_ps2h2_init(uint8_t clk, uint8_t dat)
// {
//     I2C_DBG_IO_CHECK(clk);
//     I2C_DBG_IO_CHECK(dat);
//     *(uint8_t *)&ps2h2_clk = clk;
//     *(uint8_t *)&ps2h2_dat = dat;
//     ps2h_io_cfg(clk,dat);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&clk),PS2H2_CLK);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&dat),PS2H2_DAT);
// }

// void pinmux_ps2h2_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&ps2h2_clk));
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&ps2h2_dat));
// }

// void pinmux_ps2h3_init(uint8_t clk, uint8_t dat)
// {
//     I2C_DBG_IO_CHECK(clk);
//     I2C_DBG_IO_CHECK(dat);
//     *(uint8_t *)&ps2h3_clk = clk;
//     *(uint8_t *)&ps2h3_dat = dat;
//     ps2h_io_cfg(clk,dat);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&clk),PS2H3_CLK);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&dat),PS2H3_DAT);
// }

// void pinmux_ps2h3_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&ps2h3_clk));
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&ps2h3_dat));
// }

// void pinmux_ps2h4_init(uint8_t clk, uint8_t dat)
// {
//     I2C_DBG_IO_CHECK(clk);
//     I2C_DBG_IO_CHECK(dat);
//     *(uint8_t *)&ps2h4_clk = clk;
//     *(uint8_t *)&ps2h4_dat = dat;
//     ps2h_io_cfg(clk,dat);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&clk),PS2H4_CLK);
//     per_func_enable(pin2func_io((gpio_port_pin_t *)&dat),PS2H4_DAT);
// }

// void pinmux_ps2h4_deinit(void)
// {
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&ps2h4_clk));
//     per_func_disable(pin2func_io((gpio_port_pin_t *)&ps2h4_dat));
// }

// void pinmux_kscan_init(uint8_t col_en, uint32_t row_en)
// {
//     if(i2c_dbg_io_check(PH06))
//     {
//         col_en &= ~(0xc0); // clear PH06 PH07 
//     }
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL5, SYSC_AWO_KEYI_EN, col_en);
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL5, SYSC_AWO_KEYO_EN, row_en);
//     SYSC_AWO->IO[5].OE_FIR |= (row_en & 0x7ff) << 19;
//     SYSC_AWO->IO[6].OE_FIR |= (row_en & 0x3f800) << 5;
//     SYSC_AWO->IO[7].OE_FIR &= ~(col_en << 16);
//     SYSC_AWO->IO[7].IEN_OD &= ~(col_en << 16);
//     MODIFY_REG(SYSC_AWO->IO[7].PUPD, 16<<col_en, col_en);
// }

// void pinmux_kscan_deinit(void)
// {
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL5, SYSC_AWO_KEYI_EN, 0x0);
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL5, SYSC_AWO_KEYO_EN, 0x0);
// }

// void pinmux_cjtag_init(void)
// {
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL0, SYSC_AWO_CJTAG_EN, 0x1);
// }

// void pinmux_cjtag_deinit(void)
// {
//     REG_FIELD_WR(SYSC_AWO->PIN_SEL0, SYSC_AWO_CJTAG_EN, 0x0);
// }