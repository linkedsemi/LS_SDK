#include <stddef.h>
#include "gpio_mode.h"
#include "reg_rcc.h"
#include "reg_gpio.h"
#include "ls_soc_gpio.h"
#include "reg_syscfg.h"
#include "sleep.h"
#include "ls_dbg.h"
#include "platform.h"
#include "le501x.h"
#include "field_manipulate.h"

static gpio_pin_t spi2_clk;
static gpio_pin_t spi2_nss;
static gpio_pin_t spi2_mosi;
static gpio_pin_t spi2_miso;
static gpio_pin_t i2s2_ck;
static gpio_pin_t i2s2_ws;
static gpio_pin_t i2s2_sd;
static gpio_pin_t i2s2_mck;
static gpio_pin_t uart1_txd;
static gpio_pin_t uart1_rxd;
static gpio_pin_t uart1_ck;
static gpio_pin_t uart2_txd;
static gpio_pin_t uart2_rxd;
static gpio_pin_t uart3_txd;
static gpio_pin_t uart3_rxd;
static gpio_pin_t i2c1_scl;
static gpio_pin_t i2c1_sda;
static gpio_pin_t i2c2_scl;
static gpio_pin_t i2c2_sda;
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
static gpio_pin_t pdm_clk;
static gpio_pin_t pdm_data0;
static gpio_pin_t pdm_data1;

/* ssi io init */
static gpio_pin_t ssi_clk;
static gpio_pin_t ssi_nss0;
static gpio_pin_t ssi_nss1;
static gpio_pin_t ssi_dq0;
static gpio_pin_t ssi_dq1;
static gpio_pin_t ssi_dq2;
static gpio_pin_t ssi_dq3;

reg_lsgpio_t* GPIO_GetPort(uint8_t Pin_port)
{
    uint8_t       PortID = Pin_port;
    reg_lsgpio_t* Port = NULL;

    switch (PortID)
    {
    case 0:
        Port = LSGPIOA;
        break;
    case 1:
        Port = LSGPIOB;
        break;
    case 2:
        Port = LSGPIOC;
        break;
    default:
        LS_ASSERT(0);
        break;
    }
    return Port;
}

static void uart_io_cfg(uint8_t txd,uint8_t rxd)
{
    io_set_pin(txd);
    io_cfg_output(txd);
    io_cfg_input(rxd);
}

void gpio_af_init(gpio_pin_t *pin,enum GPIO_AF af)
{
    reg_lsgpio_t *port = GPIO_GetPort(pin->port);
    switch(pin->num)
    {
    case 0: case 1: case 2: case 3:
        MODIFY_REG(port->AF0, GPIO_IO0_AF_MASK << pin->num * 8, af << pin->num * 8);
    break;
    case 4: case 5: case 6: case 7:
        MODIFY_REG(port->AF1, GPIO_IO4_AF_MASK << (pin->num - 4) * 8, af << (pin->num - 4) * 8);
    break;
    case 8: case 9: case 10: case 11:
        MODIFY_REG(port->AF2, GPIO_IO8_AF_MASK << (pin->num - 8) * 8, af << (pin->num - 8) * 8);
    break;
    case 12: case 13: case 14: case 15:
        MODIFY_REG(port->AF3, GPIO_IO12_AF_MASK << (pin->num - 12) * 8, af << (pin->num - 12) * 8);
    break;
    }
    MODIFY_REG(port->MODE, GPIO_MODE0_MASK << (pin->num << 1u), SET_GPIO_MODE_AF << (pin->num << 1u));
}

static void gpio_ana_init(gpio_pin_t *pin,enum GPIO_ANA_FUNC ana)
{
   reg_lsgpio_t *port = GPIO_GetPort(pin->port);
   MODIFY_REG(port->AE, GPIO_AE0_MASK << (pin->num << 1u), ana << (pin->num << 1u));
   MODIFY_REG(port->MODE, GPIO_MODE0_MASK << (pin->num << 1u), SET_GPIO_MODE_ANALOG << (pin->num << 1u));
  
}

void set_gpio_mode(gpio_pin_t *pin)
{
    reg_lsgpio_t *gpiox = GPIO_GetPort(pin->port);
    MODIFY_REG(gpiox->MODE, GPIO_MODE0_MASK << (pin->num << 1u), SET_GPIO_MODE_GPIO << (pin->num << 1u));
}

static void uart_7816_io_cfg(uint8_t txd,uint8_t ck)
{
    io_set_pin(txd);
    io_set_pin(ck);
    io_cfg_opendrain(txd);
    io_cfg_output(txd);
    io_cfg_output(ck);
}

void pinmux_hal_flash_quad_init(void){}

void pinmux_hal_flash_quad_deinit(void){}

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
    spi_master_clk_io_cfg(clk);
    gpio_af_init((gpio_pin_t *)&clk,AF_SPI2_SCK);
}

void pinmux_spi2_master_nss_init(uint8_t nss)
{
    *(uint8_t *)&spi2_nss = nss;
    spi_master_nss_io_cfg(nss);
    gpio_af_init((gpio_pin_t *)&nss,AF_SPI2_NSS);    
}

void pinmux_spi2_master_mosi_init(uint8_t mosi)
{
    *(uint8_t *)&spi2_mosi = mosi;
    spi_master_mosi_io_cfg(mosi);
    gpio_af_init((gpio_pin_t *)&mosi,AF_SPI2_MOSI);
}

void pinmux_spi2_master_miso_init(uint8_t miso)
{
    *(uint8_t *)&spi2_miso = miso;
    spi_master_miso_io_cfg(miso);
    gpio_af_init((gpio_pin_t *)&miso,AF_SPI2_MISO); 
}

void pinmux_spi2_slave_clk_init(uint8_t clk)
{
    *(uint8_t *)&spi2_clk = clk;
    spi_slave_clk_io_cfg(clk);
    gpio_af_init((gpio_pin_t *)&clk,AF_SPI2_SCK);
}

void pinmux_spi2_slave_nss_init(uint8_t nss)
{
    *(uint8_t *)&spi2_nss = nss;
    spi_slave_nss_io_cfg(nss);
    gpio_af_init((gpio_pin_t *)&nss,AF_SPI2_NSS);    
}

void pinmux_spi2_slave_mosi_init(uint8_t mosi)
{
    *(uint8_t *)&spi2_mosi = mosi;
    spi_slave_mosi_io_cfg(mosi);
    gpio_af_init((gpio_pin_t *)&mosi,AF_SPI2_MOSI);
}

void pinmux_spi2_slave_miso_init(uint8_t miso)
{
    *(uint8_t *)&spi2_miso = miso;
    spi_slave_miso_io_cfg(miso);
    gpio_af_init((gpio_pin_t *)&miso,AF_SPI2_MISO); 
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

void pinmux_iis2_master_ck_init(uint8_t ck)
{
    *(uint8_t *)&i2s2_ck = ck;
    iis_master_ck_io_cfg(ck);
    gpio_af_init((gpio_pin_t *)&ck,AF_SPI2_SCK);
}

void pinmux_iis2_master_ws_init(uint8_t ws)
{
    *(uint8_t *)&i2s2_ws = ws;
    iis_master_ws_io_cfg(ws);
    gpio_af_init((gpio_pin_t *)&ws,AF_SPI2_NSS);    
}

void pinmux_iis2_master_sd_init(uint8_t sd, uint8_t mode)
{
    *(uint8_t *)&i2s2_sd = sd;
    iis_master_sd_io_cfg(sd, mode);
    gpio_af_init((gpio_pin_t *)&sd,AF_SPI2_MOSI);
}

void pinmux_iis2_master_mck_init(uint8_t mck)
{
    *(uint8_t *)&i2s2_mck = mck;
    iis_master_mck_io_cfg( mck);    
    gpio_af_init((gpio_pin_t *)&mck,AF_I2S_CLK); 
}

void pinmux_iis2_slave_ck_init(uint8_t ck)
{
    *(uint8_t *)&i2s2_ck = ck;
    iis_slave_ck_io_cfg(ck);
    gpio_af_init((gpio_pin_t *)&ck,AF_SPI2_SCK);
}

void pinmux_iis2_slave_ws_init(uint8_t ws)
{
    *(uint8_t *)&i2s2_ws = ws;
    iis_slave_ws_io_cfg(ws);
    gpio_af_init((gpio_pin_t *)&ws,AF_SPI2_NSS);    
}

void pinmux_iis2_slave_sd_init(uint8_t sd, uint8_t mode)
{
    *(uint8_t *)&i2s2_sd = sd;
    iis_slave_sd_io_cfg(sd, mode);
    gpio_af_init((gpio_pin_t *)&sd,AF_SPI2_MOSI);
}

void pinmux_iis2_slave_mck_init(uint8_t mck)
{
    *(uint8_t *)&i2s2_mck = mck;
    iis_slave_mck_io_cfg( mck);    
    gpio_af_init((gpio_pin_t *)&mck,AF_I2S_CLK); 
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

void pinmux_ssi_clk_init(uint8_t clk)
{
    *(uint8_t *)&ssi_clk = clk;
    spi_master_clk_io_cfg(clk);
    gpio_af_init((gpio_pin_t *)&clk,AF_SPI1_SCK);
}

void pinmux_ssi_nss0_init(uint8_t nss0)
{
    *(uint8_t *)&ssi_nss0 = nss0;
    spi_master_nss_io_cfg(nss0);
    gpio_af_init((gpio_pin_t *)&nss0,AF_SPI1_NSS0);
}

void pinmux_ssi_nss1_init(uint8_t nss1)
{
    *(uint8_t *)&ssi_nss1 = nss1;
    spi_master_nss_io_cfg(nss1);
    gpio_af_init((gpio_pin_t *)&nss1,AF_SPI1_NSS0);    
}

void pinmux_ssi_dq0_init(uint8_t dq0)
{
    *(uint8_t *)&ssi_dq0 = dq0;
    spi_master_mosi_io_cfg(dq0);
    gpio_af_init((gpio_pin_t *)&dq0,AF_SPI1_DQ0);
}

void pinmux_ssi_dq1_init(uint8_t dq1)
{
    *(uint8_t *)&ssi_dq1 = dq1;
    spi_master_miso_io_cfg(dq1);
    gpio_af_init((gpio_pin_t *)&dq1,AF_SPI1_DQ1); 
}

void pinmux_ssi_dq2_init(uint8_t dq2)
{
    *(uint8_t *)&ssi_dq2 = dq2;
    spi_master_miso_io_cfg(dq2);
    gpio_af_init((gpio_pin_t *)&dq2,AF_SPI1_DQ2); 
}

void pinmux_ssi_dq3_init(uint8_t dq3)
{
    *(uint8_t *)&ssi_dq3 = dq3;
    spi_master_miso_io_cfg(dq3);
    gpio_af_init((gpio_pin_t *)&dq3,AF_SPI1_DQ3); 
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

void pinmux_uart1_init(uint8_t txd,uint8_t rxd)
{
    *(uint8_t *)&uart1_txd = txd;
    *(uint8_t *)&uart1_rxd = rxd;
    uart_io_cfg(txd,rxd);
    gpio_af_init((gpio_pin_t *)&txd,AF_UART1_TXD);
    gpio_af_init((gpio_pin_t *)&rxd,AF_UART1_RXD);
}

void pinmux_uart1_deinit()
{
    set_gpio_mode((gpio_pin_t *)&uart1_txd);
    set_gpio_mode((gpio_pin_t *)&uart1_rxd);
}

void pinmux_uart2_init(uint8_t txd,uint8_t rxd)
{
    *(uint8_t *)&uart2_txd = txd;
    *(uint8_t *)&uart2_rxd = rxd;
    uart_io_cfg(txd,rxd);
    gpio_af_init((gpio_pin_t *)&txd,AF_UART2_TXD);
    gpio_af_init((gpio_pin_t *)&rxd,AF_UART2_RXD);
}

void pinmux_uart2_deinit()
{
    set_gpio_mode((gpio_pin_t *)&uart2_txd);
    set_gpio_mode((gpio_pin_t *)&uart2_rxd);
}

void pinmux_uart3_init(uint8_t txd,uint8_t rxd)
{
    *(uint8_t *)&uart3_txd = txd;
    *(uint8_t *)&uart3_rxd = rxd;
    uart_io_cfg(txd,rxd);
    gpio_af_init((gpio_pin_t *)&txd,AF_UART3_TXD);
    gpio_af_init((gpio_pin_t *)&rxd,AF_UART3_RXD);
}

void pinmux_uart3_deinit()
{
    set_gpio_mode((gpio_pin_t *)&uart3_txd);
    set_gpio_mode((gpio_pin_t *)&uart3_rxd);
}

void pinmux_uart1_7816_deinit()
{
    set_gpio_mode((gpio_pin_t *)&uart1_txd);
    set_gpio_mode((gpio_pin_t *)&uart1_ck);
}
static void i2c_io_cfg(uint8_t scl,uint8_t sda)
{
    io_cfg_input(scl);
	io_cfg_input(sda);
    io_pull_write(scl,IO_PULL_UP);
    io_pull_write(sda,IO_PULL_UP);
}
void pinmux_iic1_init(uint8_t scl,uint8_t sda)
{
    *(uint8_t *)&i2c1_scl = scl;
    *(uint8_t *)&i2c1_sda = sda;
    i2c_io_cfg( scl, sda);
    gpio_af_init((gpio_pin_t *)&scl,AF_I2C1_SCL);
    gpio_af_init((gpio_pin_t *)&sda,AF_I2C1_SDA);    
}
void pinmux_iic1_deinit()
{
    set_gpio_mode((gpio_pin_t *)&i2c1_scl);
    set_gpio_mode((gpio_pin_t *)&i2c1_sda);
}
void pinmux_iic2_init(uint8_t scl,uint8_t sda)
{
    *(uint8_t *)&i2c2_scl = scl;
    *(uint8_t *)&i2c2_sda = sda;
    i2c_io_cfg( scl, sda);
    gpio_af_init((gpio_pin_t *)&scl,AF_I2C2_SCL);
    gpio_af_init((gpio_pin_t *)&sda,AF_I2C2_SDA);    
}
void pinmux_iic2_deinit()
{
    set_gpio_mode((gpio_pin_t *)&i2c2_scl);
    set_gpio_mode((gpio_pin_t *)&i2c2_sda);
}

void io_cfg_opendrain(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    reg_lsgpio_t *gpiox = GPIO_GetPort(x->port);
    gpiox->OT |= 1<< x->num;
}

void io_cfg_pushpull(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    reg_lsgpio_t *gpiox = GPIO_GetPort(x->port);
    gpiox->OT &= ~(1<< x->num);
}

void pinmux_uart1_7816_init(uint8_t txd,uint8_t ck)
{
    *(uint8_t *)&uart1_txd = txd;
    *(uint8_t *)&uart1_ck = ck;
    uart_7816_io_cfg(txd,ck);
    gpio_af_init((gpio_pin_t *)&txd,AF_UART1_TXD);
    gpio_af_init((gpio_pin_t *)&ck,AF_UART1_CK);
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
    gpio_af_init((gpio_pin_t *)&pin,AF_ADTIM1_CH1);
}

void pinmux_adtim1_ch1_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_ch1);
}

void pinmux_adtim1_ch2_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&adtim1_ch2 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    gpio_af_init((gpio_pin_t *)&pin,AF_ADTIM1_CH2);
}

void pinmux_adtim1_ch2_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_ch2);
}

void pinmux_adtim1_ch3_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&adtim1_ch3 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    gpio_af_init((gpio_pin_t *)&pin,AF_ADTIM1_CH3);
}

void pinmux_adtim1_ch3_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_ch3);
}

void pinmux_adtim1_ch4_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&adtim1_ch4 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    gpio_af_init((gpio_pin_t *)&pin,AF_ADTIM1_CH4);
}

void pinmux_adtim1_ch4_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_ch4);
}

void pinmux_adtim1_ch1n_init(uint8_t pin)
{
    *(uint8_t *)&adtim1_ch1n = pin;
    timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim1_ch1));
    gpio_af_init((gpio_pin_t *)&pin,AF_ADTIM1_CH1N);
}

void pinmux_adtim1_ch1n_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_ch1n);
}

void pinmux_adtim1_ch2n_init(uint8_t pin)
{
    *(uint8_t *)&adtim1_ch2n = pin;
    timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim1_ch2));
    gpio_af_init((gpio_pin_t *)&pin,AF_ADTIM1_CH2N);
}

void pinmux_adtim1_ch2n_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_ch2n);
}

void pinmux_adtim1_ch3n_init(uint8_t pin)
{
    *(uint8_t *)&adtim1_ch3n = pin;
    timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&adtim1_ch3));
    gpio_af_init((gpio_pin_t *)&pin,AF_ADTIM1_CH3N);
}

void pinmux_adtim1_ch3n_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_ch3n);
}

void pinmux_adtim1_etr_init(uint8_t pin)
{
    *(uint8_t *)&adtim1_etr = pin;
    io_cfg_input(pin);
    gpio_af_init((gpio_pin_t *)&pin,AF_ADTIM1_ETR);
}

void pinmux_adtim1_etr_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_etr);
}

void pinmux_adtim1_bk_init(uint8_t pin)
{
    *(uint8_t *)&adtim1_bk = pin;
    io_cfg_input(pin);
    gpio_af_init((gpio_pin_t *)&pin,AF_ADTIM1_BK);
}

void pinmux_adtim1_bk_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&adtim1_bk);
}

void pinmux_gptima1_ch1_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptima1_ch1 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    gpio_af_init((gpio_pin_t *)&pin,AF_GPTIMA1_CH1);
}

void pinmux_gptima1_ch1_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptima1_ch1);
}

void pinmux_gptima1_ch2_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptima1_ch2 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    gpio_af_init((gpio_pin_t *)&pin,AF_GPTIMA1_CH2);
}

void pinmux_gptima1_ch2_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptima1_ch2);
}

void pinmux_gptima1_ch3_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptima1_ch3 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    gpio_af_init((gpio_pin_t *)&pin,AF_GPTIMA1_CH3);
}

void pinmux_gptima1_ch3_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptima1_ch3);
}

void pinmux_gptima1_ch4_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptima1_ch4 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    gpio_af_init((gpio_pin_t *)&pin,AF_GPTIMA1_CH4);
}

void pinmux_gptima1_ch4_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptima1_ch4);
}

void pinmux_gptima1_etr_init(uint8_t pin)
{
    *(uint8_t *)&gptima1_etr = pin;
    io_cfg_input(pin);
    gpio_af_init((gpio_pin_t *)&pin,AF_GPTIMA1_ETR);
}

void pinmux_gptima1_etr_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptima1_etr);
}

void pinmux_gptimb1_ch1_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimb1_ch1 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    gpio_af_init((gpio_pin_t *)&pin,AF_GPTIMB1_CH1);
}

void pinmux_gptimb1_ch1_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptimb1_ch1);
}

void pinmux_gptimb1_ch2_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimb1_ch2 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    gpio_af_init((gpio_pin_t *)&pin,AF_GPTIMB1_CH2);
}

void pinmux_gptimb1_ch2_deinit(void)

{
    set_gpio_mode((gpio_pin_t *)&gptimb1_ch2);
}

void pinmux_gptimb1_ch3_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimb1_ch3 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    gpio_af_init((gpio_pin_t *)&pin,AF_GPTIMB1_CH3);
}

void pinmux_gptimb1_ch3_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptimb1_ch3);
}

void pinmux_gptimb1_ch4_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimb1_ch4 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    gpio_af_init((gpio_pin_t *)&pin,AF_GPTIMB1_CH4);
}

void pinmux_gptimb1_ch4_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptimb1_ch4);
}

void pinmux_gptimb1_etr_init(uint8_t pin)
{
    *(uint8_t *)&gptimb1_etr = pin;
    io_cfg_input(pin);
    gpio_af_init((gpio_pin_t *)&pin,AF_GPTIMB1_ETR);
}

void pinmux_gptimb1_etr_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptimb1_etr);
}

void pinmux_gptimc1_ch1_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimc1_ch1 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    gpio_af_init((gpio_pin_t *)&pin,AF_GPTIMC1_CH1);
}

void pinmux_gptimc1_ch1_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptimc1_ch1);
}

void pinmux_gptimc1_ch1n_init(uint8_t pin)
{
    *(uint8_t *)&gptimc1_ch1n = pin;
    timer_ch_io_output_cfg(pin,!io_get_output_val(*(uint8_t *)&gptimc1_ch1));
    gpio_af_init((gpio_pin_t *)&pin,AF_GPTIMC1_CH1N);
}

void pinmux_gptimc1_ch1n_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptimc1_ch1n);
}

void pinmux_gptimc1_ch2_init(uint8_t pin,bool output,uint8_t default_val)
{
    *(uint8_t *)&gptimc1_ch2 = pin;
    timer_ch_io_cfg(pin,output,default_val);
    gpio_af_init((gpio_pin_t *)&pin,AF_GPTIMC1_CH2);
}

void pinmux_gptimc1_ch2_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptimc1_ch2);
}

void pinmux_gptimc1_bk_init(uint8_t pin)
{
    *(uint8_t *)&gptimc1_bk = pin;
    io_cfg_input(pin);
    gpio_af_init((gpio_pin_t *)&pin,AF_GPTIMC1_BK);
}

void pinmux_gptimc1_bk_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&gptimc1_bk);
}

void pinmux_ana_func1_init(uint8_t ain)
{
    gpio_ana_init((gpio_pin_t *)&ain,ANA_FUNC1);
}

void gpio_ana_deinit(uint8_t ain)
{
    set_gpio_mode((gpio_pin_t *)&ain);
    io_cfg_disable(ain);
}

void pinmux_adc12b_in0_init(void)
{
    pinmux_ana_func1_init(PB12);
}

void pinmux_adc12b_in0_deinit(void)
{    
    gpio_ana_deinit(PB12);
}

void pinmux_adc12b_in1_init(void)
{
    pinmux_ana_func1_init(PB13);
}

void pinmux_adc12b_in1_deinit(void)
{
    gpio_ana_deinit(PB13);
}

void pinmux_adc12b_in2_init(void)
{
    pinmux_ana_func1_init(PC00);
}

void pinmux_adc12b_in2_deinit(void)
{
    gpio_ana_deinit(PC00);
}

void pinmux_adc12b_in3_init(void)
{
    pinmux_ana_func1_init(PC01);
}

void pinmux_adc12b_in3_deinit(void)
{
    gpio_ana_deinit(PC01);
}

void pinmux_adc12b_in4_init(void)
{
    pinmux_ana_func1_init(PA00);
}

void pinmux_adc12b_in4_deinit(void)
{
    gpio_ana_deinit(PA00);
}

void pinmux_adc12b_in5_init(void)
{
    pinmux_ana_func1_init(PA01);
}

void pinmux_adc12b_in5_deinit(void)
{
    gpio_ana_deinit(PA01);
}


void pinmux_adc12b_in6_init(void)
{
    pinmux_ana_func1_init(PA02);
}

void pinmux_adc12b_in6_deinit(void)
{
    gpio_ana_deinit(PA02);
}

void pinmux_adc12b_in7_init(void)
{
    pinmux_ana_func1_init(PA03);
}

void pinmux_adc12b_in7_deinit(void)
{
    gpio_ana_deinit(PA03);
}

void pinmux_adc12b_in8_init(void)
{
    pinmux_ana_func1_init(PA04);
}

void pinmux_adc12b_in8_deinit(void)
{
    gpio_ana_deinit(PA04);
}

void pinmux_pdm_clk_init(uint8_t pin)
{
    *(uint8_t *)&pdm_clk = pin;
    io_cfg_output(pin);
    gpio_af_init((gpio_pin_t *)&pin,AF_PDM_CLK);
}

void pinmux_pdm_clk_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&pdm_clk);
}

void pinmux_pdm_data0_init(uint8_t pin)
{
    *(uint8_t *)&pdm_data0 = pin;
    io_cfg_input(pin);
    gpio_af_init((gpio_pin_t *)&pin,AF_PDM_DATA0);
}

void pinmux_pdm_data0_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&pdm_data0);
}

void pinmux_pdm_data1_init(uint8_t pin)
{
    *(uint8_t *)&pdm_data1 = pin;
    io_cfg_input(pin);
    gpio_af_init((gpio_pin_t *)&pin,AF_PDM_DATA1);
}

void pinmux_pdm_data1_deinit(void)
{
    set_gpio_mode((gpio_pin_t *)&pdm_data1);
}

void EXTI_Handler(void);
void io_init(void)
{
    RCC->AHBEN |= RCC_GPIOA_MASK | RCC_GPIOB_MASK | RCC_GPIOC_MASK;
    LSGPIOA->MODE = 0;
    LSGPIOA->IE = 0;
    LSGPIOA->OE = 0;
    LSGPIOA->PUPD = 0;
    LSGPIOB->MODE &= 0x3c00;
    LSGPIOB->IE = 0;
    LSGPIOB->OE = 0;
    LSGPIOB->PUPD = 0x2800;
    arm_cm_set_int_isr(EXTI_IRQn,EXTI_Handler);
    __NVIC_EnableIRQ(EXTI_IRQn);
}

void io_cfg_output(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    reg_lsgpio_t *gpiox = GPIO_GetPort(x->port);
    gpiox->OE |= 1<< x->num;
}

void io_cfg_input(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    reg_lsgpio_t *gpiox = GPIO_GetPort(x->port);
    gpiox->OE &= ~(1<< x->num);
    gpiox->IE |= 1<< x->num;
}

void io_cfg_disable(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    reg_lsgpio_t *gpiox = GPIO_GetPort(x->port);
    gpiox->OE &= ~(1<< x->num);
    gpiox->IE &= ~(1<< x->num);
}

void io_set_pin(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    reg_lsgpio_t *gpiox = GPIO_GetPort(x->port);
    gpiox->BSBR = 1<< x->num;
}

void io_clr_pin(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    reg_lsgpio_t *gpiox = GPIO_GetPort(x->port);
    gpiox->BSBR = 1<<(x->num+16);
}

void io_write_pin(uint8_t pin, uint8_t val)
{
    if(val)
    {
        io_set_pin(pin);
    }else
    {
        io_clr_pin(pin);
    }
}

uint8_t io_get_output_val(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    reg_lsgpio_t *gpiox = GPIO_GetPort(x->port);
    uint8_t val = (gpiox->DOUT >> x->num) & 0x1;
    return val;
}

uint8_t io_read_pin(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    reg_lsgpio_t *gpiox = GPIO_GetPort(x->port);
    uint8_t val = (gpiox->DIN >> x->num) & 0x1;
    return val;
}

void io_toggle_pin(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    reg_lsgpio_t *gpiox = GPIO_GetPort(x->port);
    if(gpiox->DOUT & 1<< x->num)
    {
        gpiox->BSBR = 1<<(x->num+16);
    }else
    {
        gpiox->BSBR = 1<< x->num;
    }
}

void io_pull_write(uint8_t pin,io_pull_type_t pull)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    reg_lsgpio_t *gpiox = GPIO_GetPort(x->port);
    MODIFY_REG(gpiox->PUPD, 0x3 << 2*x->num, pull << 2*x->num);
}

io_pull_type_t io_pull_read(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    reg_lsgpio_t *gpiox = GPIO_GetPort(x->port);
    io_pull_type_t pull = (io_pull_type_t)((gpiox->PUPD >> 2 * x->num ) & 0x3);
    return pull;
}

void io_drive_capacity_write(uint8_t pin, io_drive_type_t drive)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    reg_lsgpio_t *gpiox = GPIO_GetPort(x->port);
    MODIFY_REG(gpiox->OD, GPIO_OD0_MASK << 2*x->num, drive << 2*x->num);
}

io_drive_type_t io_drive_capacity_read(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    reg_lsgpio_t *gpiox = GPIO_GetPort(x->port);
    io_drive_type_t drive = (io_drive_type_t)((gpiox->OD >> 2 * x->num ) & GPIO_OD0_MASK);
    return drive;
}

void io_exti_config(uint8_t pin,exti_edge_t edge)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    if(x->num <= 7)
    {
        MODIFY_REG(EXTI->EICFG0, 0xf<< 4 * x->num,x->port << 4 * x->num);
    }else
    {
        MODIFY_REG(EXTI->EICFG1, 0xf<< 4 * (x->num - 8),x->port << 4 * (x->num - 8));
    }
    if(edge == INT_EDGE_FALLING)
    {
        EXTI->ERTS &= ~(1 << x->num);
        EXTI->EFTS |= 1 << x->num;
        EXTI->EICR =  1 << x->num;
        EXTI->EIER =  1 << x->num;
        switch(pin)
        {
        case PA00:
            MODIFY_REG(SYSCFG->PMU_WKUP,PA00_IO_WKUP<<WKUP_EDGE_POS,PA00_IO_WKUP<<WKUP_EN_POS);
        break;
        case PA07:
            MODIFY_REG(SYSCFG->PMU_WKUP,PA07_IO_WKUP<<WKUP_EDGE_POS,PA07_IO_WKUP<<WKUP_EN_POS);
        break;
        case PB11:
            MODIFY_REG(SYSCFG->PMU_WKUP,PB11_IO_WKUP<<WKUP_EDGE_POS,PB11_IO_WKUP<<WKUP_EN_POS);
        break;
        case PB15:
            MODIFY_REG(SYSCFG->PMU_WKUP,PB15_IO_WKUP<<WKUP_EDGE_POS,PB15_IO_WKUP<<WKUP_EN_POS);
        break;
        }
    }else if(edge == INT_EDGE_RISING)
    {
        EXTI->EFTS &= ~(1 << x->num);
        EXTI->ERTS |= 1 << x->num;
        EXTI->EICR =  1 << x->num;
        EXTI->EIER =  1 << x->num;
        switch(pin)
        {
        case PA00:
            SET_BIT(SYSCFG->PMU_WKUP,PA00_IO_WKUP<<WKUP_EDGE_POS|PA00_IO_WKUP<<WKUP_EN_POS);
        break;
        case PA07:
            SET_BIT(SYSCFG->PMU_WKUP,PA07_IO_WKUP<<WKUP_EDGE_POS|PA07_IO_WKUP<<WKUP_EN_POS);
        break;
        case PB11:
            SET_BIT(SYSCFG->PMU_WKUP,PB11_IO_WKUP<<WKUP_EDGE_POS|PB11_IO_WKUP<<WKUP_EN_POS);
        break;
        case PB15:
            SET_BIT(SYSCFG->PMU_WKUP,PB15_IO_WKUP<<WKUP_EDGE_POS|PB15_IO_WKUP<<WKUP_EN_POS);
        break;
        }
    }else if(edge == INT_EDGE_BOTH)
    {
        EXTI->ERTS |= 1 << x->num;
        EXTI->EFTS |= 1 << x->num;
        EXTI->EICR =  1 << x->num;
        EXTI->EIER =  1 << x->num;
    }else
    {
        EXTI->EIDR =  1 << x->num;
        switch(pin)
        {
        case PA00:
            CLEAR_BIT(SYSCFG->PMU_WKUP,PA00_IO_WKUP<<WKUP_EN_POS);
        break;
        case PA07:
            CLEAR_BIT(SYSCFG->PMU_WKUP,PA07_IO_WKUP<<WKUP_EN_POS);
        break;
        case PB11:
            CLEAR_BIT(SYSCFG->PMU_WKUP,PB11_IO_WKUP<<WKUP_EN_POS);
        break;
        case PB15:
            CLEAR_BIT(SYSCFG->PMU_WKUP,PB15_IO_WKUP<<WKUP_EN_POS);
        break;
        }
    }
}

void io_wkup_en_clr_set(uint8_t pin)
{
    switch(pin)
    {
    case PA00:
        CLEAR_BIT(SYSCFG->PMU_WKUP,PA00_IO_WKUP<<WKUP_EN_POS);
        SET_BIT(SYSCFG->PMU_WKUP,PA00_IO_WKUP<<WKUP_EN_POS);
    break;
    case PA07:
        CLEAR_BIT(SYSCFG->PMU_WKUP,PA07_IO_WKUP<<WKUP_EN_POS);
        SET_BIT(SYSCFG->PMU_WKUP,PA07_IO_WKUP<<WKUP_EN_POS);
    break;
    case PB11:
        CLEAR_BIT(SYSCFG->PMU_WKUP,PB11_IO_WKUP<<WKUP_EN_POS);
        SET_BIT(SYSCFG->PMU_WKUP,PB11_IO_WKUP<<WKUP_EN_POS);
    break;
    case PB15:
        CLEAR_BIT(SYSCFG->PMU_WKUP,PB15_IO_WKUP<<WKUP_EN_POS);
        SET_BIT(SYSCFG->PMU_WKUP,PB15_IO_WKUP<<WKUP_EN_POS);
    break;
    }
}

__attribute__((weak)) void io_exti_callback(uint8_t pin,exti_edge_t edge){}

static void exti_io_handler(uint8_t port,uint8_t num)
{
    uint8_t pin = port<<4 | num;
    EXTI->EICR = 1<<num;
    io_wkup_en_clr_set(pin);
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

