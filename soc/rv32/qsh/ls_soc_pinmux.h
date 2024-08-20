#ifndef LS_SOC_PINMUX_H_
#define LS_SOC_PINMUX_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
  * @brief Init IO for SPI Flash (CS CLK DQ0 DQ1)
  */
void pinmux_hal_flash_init(void);

/**
  * @brief DeInit SPI Flash IO
  */
void pinmux_hal_flash_deinit(void);

/**
  * @brief Init IO for QSPI Flash (CS CLK DQ0 DQ1 DQ2 DQ3)
  */
void pinmux_hal_flash_quad_init(void);

/**
  * @brief DeInit QSPI Flash IO
  */
void pinmux_hal_flash_quad_deinit(void);

/**
  * @brief  GPIO initilization
  * @param  clk  Specific GPIO pin
  * @param  cpol  Clock polarity state
  */
void pinmux_ssi_clk_init(uint8_t clk, uint8_t cpol);

/**
  * @brief     GPIO initilization as ssi nss0
  * @param  nss0  Specific GPIO pin
  */
void pinmux_ssi_nss0_init(uint8_t nss0);

/**
  * @brief    Set pin mux function to ssi nss1
  * @param  nss1   Specific GPIO pin
  */
void pinmux_ssi_nss1_init(uint8_t nss1);

/**
  * @brief  config GPIO  to ssi dq0
  * @param  dq0  Specific GPIO pin
  */
void pinmux_ssi_dq0_init(uint8_t dq0);

/**
  * @brief   Set pin mux function to ssi dq1
  * @param  dq1   Specific GPIO pin
  */
void pinmux_ssi_dq1_init(uint8_t dq1);

/**
  * @brief   Set pin mux function to ssi dq2
  * @param  dq2   Specific GPIO pin
  */
void pinmux_ssi_dq2_init(uint8_t dq2);

/**
  * @brief  Set pin mux function to ssi dq3
  * @param  dq3   Specific GPIO pin
  */
void pinmux_ssi_dq3_init(uint8_t dq3);

/**
  * @brief  Set pin mux function to iis2 master ck
  * @param  ck   Specific GPIO pin
  */
void pinmux_iis2_master_ck_init(uint8_t ck);

/**
  * @brief   Set pin mux function to iis2 master ws
  * @param   ws  Specific GPIO pin
  */
void pinmux_iis2_master_ws_init(uint8_t ws);

/**
  * @brief   Set pin mux function to iis2 master sd
  * @param   sd   Specific GPIO pin
  * @param   mode GPIO input/output mode
  */
void pinmux_iis2_master_sd_init(uint8_t sd, uint8_t mode);

/**
  * @brief    Set pin mux function to iis2 master mck
  * @param    mck   Specific GPIO pin
  */
void pinmux_iis2_master_mck_init(uint8_t mck);

/**
  * @brief  Set pin mux function to iis2 slave ck
  * @param  ck   Specific GPIO pin
  */
void pinmux_iis2_slave_ck_init(uint8_t ck);

/**
  * @brief   Set pin mux function to iis2 slave ws
  * @param   ws  Specific GPIO pin
  */
void pinmux_iis2_slave_ws_init(uint8_t ws);

/**
  * @brief   Set pin mux function to iis2 slave sd
  * @param   sd   Specific GPIO pin
  * @param   mode GPIO input/output mode
  */
void pinmux_iis2_slave_sd_init(uint8_t sd, uint8_t mode);

/**
  * @brief    Set pin mux function to iis2 slave mck
  * @param    mck   Specific GPIO pin
  */
void pinmux_iis2_slave_mck_init(uint8_t mck);

/**
  * @brief  clear pin mux function of iis2_clk
  */
void pinmux_iis2_ck_deinit(void);

/**
  * @brief  clear pin mux functions of iis2_ws
  */
void pinmux_iis2_ws_deinit(void);

/**
  * @brief   clear pin mux function of iis2_sd
  */
void pinmux_iis2_sd_deinit(void);

/**
  * @brief   clear pin mux function of iis2_mck
  */
void pinmux_iis2_mck_deinit(void);

/**
  * @brief  Set pin mux function to iis3 master ck
  * @param  ck   Specific GPIO pin
  */
void pinmux_iis3_master_ck_init(uint8_t ck);

/**
  * @brief   Set pin mux function to iis3 master ws
  * @param   ws  Specific GPIO pin
  */
void pinmux_iis3_master_ws_init(uint8_t ws);

/**
  * @brief   Set pin mux function to iis3 master sd
  * @param   sd   Specific GPIO pin
  * @param   mode GPIO input/output mode
  */
void pinmux_iis3_master_sd_init(uint8_t sd, uint8_t mode);

/**
  * @brief    Set pin mux function to iis3 master mck
  * @param    mck   Specific GPIO pin
  */
void pinmux_iis3_master_mck_init(uint8_t mck);

/**
  * @brief  Set pin mux function to iis3 slave ck
  * @param  ck   Specific GPIO pin
  */
void pinmux_iis3_slave_ck_init(uint8_t ck);

/**
  * @brief   Set pin mux function to iis3 slave ws
  * @param   ws  Specific GPIO pin
  */
void pinmux_iis3_slave_ws_init(uint8_t ws);

/**
  * @brief   Set pin mux function to iis3 slave sd
  * @param   sd   Specific GPIO pin
  * @param   mode GPIO input/output mode
  */
void pinmux_iis3_slave_sd_init(uint8_t sd, uint8_t mode);

/**
  * @brief    Set pin mux function to iis3 slave mck
  * @param    mck   Specific GPIO pin
  */
void pinmux_iis3_slave_mck_init(uint8_t mck);

/**
  * @brief  clear pin mux function of iis3_clk
  */
void pinmux_iis3_ck_deinit(void);

/**
  * @brief  clear pin mux functions of iis3_ws
  */
void pinmux_iis3_ws_deinit(void);

/**
  * @brief   clear pin mux function of iis3_sd
  */
void pinmux_iis3_sd_deinit(void);

/**
  * @brief   clear pin mux function of iis3_mck
  */
void pinmux_iis3_mck_deinit(void);
/**
  * @brief  Set pin mux function to spi2 clk
  * @param  clk   Specific GPIO pin
  */
void pinmux_spi2_clk_init(uint8_t clk);

/**
  * @brief   Set pin mux function to spi2 nss
  * @param  nss  Specific GPIO pin
  */
void pinmux_spi2_nss_init(uint8_t nss);

/**
  * @brief   Set pin mux function to spi2 mosi
  * @param  mosi   Specific GPIO pin
  */
void pinmux_spi2_mosi_init(uint8_t mosi);

/**
  * @brief    Set pin mux function to spi2 mosi
  * @param  miso   Specific GPIO pin
  */
void pinmux_spi2_miso_init(uint8_t miso);

/**
  * @brief  clear pin mux function of spi2_clk
  */
void pinmux_spi2_clk_deinit(void);

/**
  * @brief  clear pin mux functions of spi2_nss
  */
void pinmux_spi2_nss_deinit(void);

/**
  * @brief   clear pin mux function of spi2_mosi
  */
void pinmux_spi2_mosi_deinit(void);

/**
  * @brief   clear pin mux function of spi2_miso
  */
void pinmux_spi2_miso_deinit(void);

/**
  * @brief  Set pin mux function to spi2 master clk
  * @param  clk   Specific GPIO pin
  * @param  cpol  Clock polarity state
  */
void pinmux_spi2_master_clk_init(uint8_t clk, uint8_t cpol);

/**
  * @brief   Set pin mux function to spi2 master nss
  * @param  nss  Specific GPIO pin
  */
void pinmux_spi2_master_nss_init(uint8_t nss);

/**
  * @brief   Set pin mux function to spi2 master mosi
  * @param  mosi   Specific GPIO pin
  */
void pinmux_spi2_master_mosi_init(uint8_t mosi);

/**
  * @brief    Set pin mux function to spi2 master mosi
  * @param  miso   Specific GPIO pin
  */
void pinmux_spi2_master_miso_init(uint8_t miso);

/**
  * @brief  Set pin mux function to spi2 slave clk
  * @param  clk   Specific GPIO pin
  */
void pinmux_spi2_slave_clk_init(uint8_t clk);

/**
  * @brief   Set pin mux function to spi2 slave nss
  * @param  nss  Specific GPIO pin
  */
void pinmux_spi2_slave_nss_init(uint8_t nss);

/**
  * @brief   Set pin mux function to spi2 slave mosi
  * @param  mosi   Specific GPIO pin
  */
void pinmux_spi2_slave_mosi_init(uint8_t mosi);

/**
  * @brief    Set pin mux function to spi2 slave mosi
  * @param  miso   Specific GPIO pin
  */
void pinmux_spi2_slave_miso_init(uint8_t miso);

/**
  * @brief  Set pin mux function to spi3 master clk
  * @param  clk   Specific GPIO pin
  */
void pinmux_spi3_master_clk_init(uint8_t clk, uint8_t cpol);

/**
  * @brief   Set pin mux function to spi3 master nss
  * @param  nss  Specific GPIO pin
  */
void pinmux_spi3_master_nss_init(uint8_t nss);

/**
  * @brief   Set pin mux function to spi3 master mosi
  * @param  mosi   Specific GPIO pin
  */
void pinmux_spi3_master_mosi_init(uint8_t mosi);

/**
  * @brief    Set pin mux function to spi3 master mosi
  * @param  miso   Specific GPIO pin
  */
void pinmux_spi3_master_miso_init(uint8_t miso);

/**
  * @brief  Set pin mux function to spi3 slave clk
  * @param  clk   Specific GPIO pin
  */
void pinmux_spi3_slave_clk_init(uint8_t clk);

/**
  * @brief   Set pin mux function to spi3 slave nss
  * @param  nss  Specific GPIO pin
  */
void pinmux_spi3_slave_nss_init(uint8_t nss);

/**
  * @brief   Set pin mux function to spi3 slave mosi
  * @param  mosi   Specific GPIO pin
  */
void pinmux_spi3_slave_mosi_init(uint8_t mosi);

/**
  * @brief    Set pin mux function to spi3 slave mosi
  * @param  miso   Specific GPIO pin
  */
void pinmux_spi3_slave_miso_init(uint8_t miso);

/**
  * @brief  clear pin mux function of spi3_clk
  */
void pinmux_spi3_clk_deinit(void);

/**
  * @brief  clear pin mux functions of spi3_nss
  */
void pinmux_spi3_nss_deinit(void);

/**
  * @brief   clear pin mux function of spi3_mosi
  */
void pinmux_spi3_mosi_deinit(void);

/**
  * @brief   clear pin mux function of spi3_miso
  */
void pinmux_spi3_miso_deinit(void);

/**
  * @brief Set pin mux function as spis
  */
void pinmux_spis_init(void);

/**
 * @brief   clear pin mux function of spis
*/
void pinmux_spis_deinit(void);

/**
  * @brief       Set pin mux function as iic1_io_init
  * @param  scl  Specific GPIO pin 
  * @param  sda  Specific GPIO pin 
  */
void pinmux_iic1_init(uint8_t scl,uint8_t sda);

/**
  * @brief clean pin mux function  of iic1
  */
void pinmux_iic1_deinit(void);


/**
  * @brief         Set pin mux function as iic2_io_init
  * @param  scl    Specific GPIO pin  
  * @param  sda    Specific GPIO pin 
  */
void pinmux_iic2_init(uint8_t scl,uint8_t sda);


/**
  * @brief clean pin mux function of iic2
  */
void pinmux_iic2_deinit(void);

/**
  * @brief         Set pin mux function to uart1 (config of gpio)
  * @param  txd    Specific GPIO pin  
  * @param   rxd   Specific GPIO pin   
  */
void pinmux_uart1_init(uint8_t txd,uint8_t rxd);

/**
  * @brief clear  pin mux function of uart1
  */
void pinmux_uart1_deinit(void);

/**
  * @brief          Set pin mux function to uart1_7816
   * @param  txd    Specific GPIO pin  
  * @param   ck     Specific GPIO pin  
  */
void pinmux_uart1_7816_init(uint8_t txd,uint8_t ck);

/**
  * @brief clear pin mux function of uart1_7816
  */
void pinmux_uart1_7816_deinit(void);

/**
  * @brief          Set pin mux function to uart2
  * @param  txd     Specific GPIO pin  
  * @param rxd      Specific GPIO pin  
  */
void pinmux_uart2_init(uint8_t txd,uint8_t rxd);

/**
  * @brief clear  pin mux function of uart2
  */
void pinmux_uart2_deinit(void);

/**
  * @brief       Set pin mux function to uart3
  * @param  txd   Specific GPIO pin  
  * @param rxd   Specific GPIO pin   
  */
void pinmux_uart3_init(uint8_t txd,uint8_t rxd);

/**
  * @brief clear  pin mux function of uart3
  */
void pinmux_uart3_deinit(void);

/**
  * @brief       Set pin mux function to dwuart1
  * @param  txd   Specific GPIO pin  
  * @param rxd   Specific GPIO pin   
  */
void pinmux_dwuart1_init(uint8_t txd,uint8_t rxd);

/**
  * @brief clear  pin mux function of dwuart1
  */
void pinmux_dwuart1_deinit(void);

/**
  * @brief       Set pin mux function to dwuart2
  * @param  txd   Specific GPIO pin  
  * @param rxd   Specific GPIO pin   
  */
void pinmux_dwuart2_init(uint8_t txd,uint8_t rxd);

/**
  * @brief clear  pin mux function of dwuart2
  */
void pinmux_dwuart2_deinit(void);

/**
  * @brief Set pin mux function to adtim1 
  * @param   pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_adtim1_ch1_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear  mux function of pin adtim1
  */
void pinmux_adtim1_ch1_deinit(void);

/**
  * @brief Set  mux function of pin adtmi1 of channel 2
  * @param   pin Specific GPIO pin  
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level 
  */
void pinmux_adtim1_ch2_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin adtim1
  */
void pinmux_adtim1_ch2_deinit(void);

/**
  * @brief Set  mux function of pin adtmi1 of channel 3
  * @param   pin Specific GPIO pin  
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_adtim1_ch3_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief Set pin mux function
  */
void pinmux_adtim1_ch3_deinit(void);

/**
  * @brief  Set  mux function of pin adtmi1 of channel 4
  * @param   pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_adtim1_ch4_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin adtim1 of channel 4
  */
void pinmux_adtim1_ch4_deinit(void);

/**
  * @brief      Set mux function of pin adtim1  of ch1n as input and output
  * @param  pin  Specific GPIO pin 
  */
void pinmux_adtim1_ch1n_init(uint8_t pin);

/**
  * @brief clear mux function of pin adtim1 of ch1n
  */
void pinmux_adtim1_ch1n_deinit(void);

/**
  * @brief           Set mux function of pin adtim1 of ch2n
  * @param  pin      Specific GPIO pin 
  */

void pinmux_adtim1_ch2n_init(uint8_t pin);

/**
  * @brief          clear  mux function of pin adtim1 of ch2n
  */
void pinmux_adtim1_ch2n_deinit(void);

/**
    @brief          Set mux function of pin adtim1 of ch3n
  * @param  pin     Specific GPIO pin 
  */
void pinmux_adtim1_ch3n_init(uint8_t pin);

/**
  @brief             clear mux function of pin adtim1 of ch3n
  */
void pinmux_adtim1_ch3n_deinit(void);

/**
    @brief           Set mux function of pin adtim1 of etr
  * @param  pin      Specific GPIO pin 
  */
void pinmux_adtim1_etr_init(uint8_t pin);

/**
  @brief      clear mux function of pin adtim1 of etr
  */
void pinmux_adtim1_etr_deinit(void);

/**
    @brief           configure gpio pin as adtim1_bk
  * @param  pin      Specific GPIO pin 
  */
void pinmux_adtim1_bk_init(uint8_t pin);

/**
 @brief clear  mux function of pin adtim1_bk 
  */
void pinmux_adtim1_bk_deinit(void);

/**
  *  @brief Set mux function of pin gptima1 of channel 1
  *  @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_gptima1_ch1_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptima1 of channel 1
  */
void pinmux_gptima1_ch1_deinit(void);

/**
  * @brief  Set mux function of pin gptima1 of channel 2
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_gptima1_ch2_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief   clear  mux function of pin gptima1 of channel 2
  */
void pinmux_gptima1_ch2_deinit(void);

/**
  * @brief                Set mux function of pin gptima1 of channel 3
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_gptima1_ch3_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief       clear mux function of pin gptima1 of channel 3
  */
void pinmux_gptima1_ch3_deinit(void);

/**
  * @brief                Set mux function of pin gptima1 of channel 4
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_gptima1_ch4_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief     clear mux function of pin gptima1 of channel 4
  */
void pinmux_gptima1_ch4_deinit(void);

/**
  * @brief       Set mux function of pin gptima1 of channel etr
  * @param  pin  Specific GPIO pin 
  */
void pinmux_gptima1_etr_init(uint8_t pin);

/**
  * @brief      clear mux function of pin gptima1 of etr
  */
void pinmux_gptima1_etr_deinit(void);

/**
  * @brief Set mux function of pin gptima1 of channel 1
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_gptimb1_ch1_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptimb1 of channel 1
  */
void pinmux_gptimb1_ch1_deinit(void);

/**
  * @brief Set mux function of pin gptima1 of channel 2
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_gptimb1_ch2_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief        clear mux function of pin gptimb1 of channel 2
  */
void pinmux_gptimb1_ch2_deinit(void);

/**
  * @brief Set mux function of pin gptima1 of channel 3
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_gptimb1_ch3_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptimb1 of channel 3
  */
void pinmux_gptimb1_ch3_deinit(void);

/**
  * @brief Set mux function of pin gptima1 of channel 4
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level 
  */
void pinmux_gptimb1_ch4_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptimb1 of channel 4
  */
void pinmux_gptimb1_ch4_deinit(void);

/**
  * @brief Set mux function of pin gptimb1 of etr
  * @param  pin  Specific GPIO pin 
  */
void pinmux_gptimb1_etr_init(uint8_t pin);

/**
  * @brief   clear mux function of pin gptimb1 of etr
  */
void pinmux_gptimb1_etr_deinit(void);

/**
  * @brief Set mux function of pin gptima1 of channel 1
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level 
  */
void pinmux_gptimc1_ch1_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptimc1 of channel 1
  */
void pinmux_gptimc1_ch1_deinit(void);

/**
  * @brief Set mux function of pin gptimc1 of channel 1
  * @param  pin  Specific GPIO pin 
  */
void pinmux_gptimc1_ch1n_init(uint8_t pin);

/**
  * @brief clear mux function of pin gptimc1 of channel 1
  */
void pinmux_gptimc1_ch1n_deinit(void);

/**
  * @brief Set mux function of pin gptimc1 of channel 2
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_gptimc1_ch2_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptimc1 of channel 2
  */
void pinmux_gptimc1_ch2_deinit(void);

/**
  * @brief Set mux function of pin gptimc1 of bk
  * @param  pin   Specific GPIO pin 
  */
void pinmux_gptimc1_bk_init(uint8_t pin);

/**
  * @brief clear mux function of pin gptimc1 of bk
  */
void pinmux_gptimc1_bk_deinit(void);

/**
  * @brief        configure gpio pin as pdm_clk
  * @param  pin   Specific GPIO pin 
  */
void pinmux_pdm_clk_init(uint8_t pin);

/**
  * @brief clear gpio of pdm_clk
  */
void pinmux_pdm_clk_deinit(void);

/**
  * @brief       configure gpio of pdm_data0
  * @param  pin  Specific GPIO pin 
  */
void pinmux_pdm_data0_init(uint8_t pin);

/**
  * @brief clear gpio pin of pdm_data0
  */
void pinmux_pdm_data0_deinit(void);

/**
  * @brief       configure gpio pin as pdm_data1
  * @param  pin  Specific GPIO pin 
  */
void pinmux_pdm_data1_init(uint8_t pin);

/**
  * @brief disable pin mux function from pdm_data1
  */
void pinmux_pdm_data1_deinit(void);


/**
  * @brief       configure gpio pin as touchkey cmod
  */
void pinmux_touchkey_cmod_init();

/**
  * @brief disable pin mux function from touchkey cmod
  */
void pinmux_touchkey_cmod_deinit();

/**
  * @brief       configure gpio pin as touchkey ch0
  */
void pinmux_touchkey_ch0_init();

/**
  * @brief disable pin mux function from touchkey ch0
  */
void pinmux_touchkey_ch0_deinit();

/**
  * @brief       configure gpio pin as touchkey ch1
  */
void pinmux_touchkey_ch1_init();

/**
  * @brief disable pin mux function from touchkey ch1
  */
void pinmux_touchkey_ch1_deinit();

/**
  * @brief       configure gpio pin as touchkey ch2
  */
void pinmux_touchkey_ch2_init();

/**
  * @brief disable pin mux function from touchkey ch2
  */
void pinmux_touchkey_ch2_deinit();

/**
  * @brief       configure gpio pin as touchkey ch3
  */
void pinmux_touchkey_ch3_init();

/**
  * @brief disable pin mux function from touchkey ch3
  */
void pinmux_touchkey_ch3_deinit();

/**
  * @brief       configure gpio pin as touchkey ch4
  */
void pinmux_touchkey_ch4_init();

/**
  * @brief disable pin mux function from touchkey ch4
  */
void pinmux_touchkey_ch4_deinit();

/**
  * @brief       configure gpio pin as touchkey ch5
  */
void pinmux_touchkey_ch5_init();

/**
  * @brief disable pin mux function from touchkey ch5
  */
void pinmux_touchkey_ch5_deinit();

/**
  * @brief       configure gpio pin as touchkey ch6
  */
void pinmux_touchkey_ch6_init();

/**
  * @brief disable pin mux function from touchkey ch6
  */
void pinmux_touchkey_ch6_deinit();

/**
  * @brief       configure gpio pin as touchkey ch7
  */
void pinmux_touchkey_ch7_init();

/**
  * @brief disable pin mux function from touchkey ch7
  */
void pinmux_touchkey_ch7_deinit();

/**
  * @brief       configure gpio pin as touchkey ch8
  */
void pinmux_touchkey_ch8_init();

/**
  * @brief disable pin mux function from touchkey ch8
  */
void pinmux_touchkey_ch8_deinit();

/**
  * @brief       configure gpio pin as touchkey ch9
  */
void pinmux_touchkey_ch9_init();

/**
  * @brief disable pin mux function from touchkey ch9
  */
void pinmux_touchkey_ch9_deinit();

/**
  * @brief       configure gpio pin as touchkey ch10
  */
void pinmux_touchkey_ch10_init();

/**
  * @brief disable pin mux function from touchkey ch10
  */
void pinmux_touchkey_ch10_deinit();

/**
  * @brief       configure gpio pin as touchkey ch11
  */
void pinmux_touchkey_ch11_init();

/**
  * @brief disable pin mux function from touchkey ch11
  */
void pinmux_touchkey_ch11_deinit();

/**
  * @brief       configure gpio pin as touchkey ch12 
  */
void pinmux_touchkey_ch12_init();

/**
  * @brief disable pin mux function from touchkey ch12
  */
void pinmux_touchkey_ch12_deinit();

/**
  * @brief       configure gpio pin as touchkey ch13
  */
void pinmux_touchkey_ch13_init();

/**
  * @brief disable pin mux function from touchkey ch13
  */
void pinmux_touchkey_ch13_deinit();

/**
  * @brief       configure gpio pin as touchkey ch14
  */
void pinmux_touchkey_ch14_init();

/**
  * @brief disable pin mux function from touchkey ch14
  */
void pinmux_touchkey_ch14_deinit();

/**
  * @brief       configure gpio pin as touchkey ch15
  */
void pinmux_touchkey_ch15_init();

/**
  * @brief disable pin mux function from touchkey ch15
  */
void pinmux_touchkey_ch15_deinit();

/**
 * @brief         set pin mux function to comp1
 * @param dat     Specific GPIO pin
 */
void pinmux_comp1_init(uint8_t dat);

/**
 * @brief clear pin mux function of comp1
 */
void pinmux_comp1_deinit(void);

/**
 * @brief         set pin mux function to comp2
 * @param dat     Specific GPIO pin
 */
void pinmux_comp2_init(uint8_t dat);

/**
 * @brief clear pin mux function of comp2
 */
void pinmux_comp2_deinit(void);

/**
 * @brief         set pin mux function to comp3
 * @param dat     Specific GPIO pin
 */
void pinmux_comp3_init(uint8_t dat);

/**
 * @brief clear pin mux function of comp3
 */
void pinmux_comp3_deinit(void);

/**
  * @brief         Set pin mux function as iic2_io_init
  * @param  scl    Specific GPIO pin  
  * @param  sda    Specific GPIO pin 
  */
void pinmux_iic2_init(uint8_t scl,uint8_t sda);

/**
  * @brief clean pin mux function of iic2
  */
void pinmux_iic2_deinit(void);  

/**
  * @brief         Set pin mux function as iic3_io_init
  * @param  scl    Specific GPIO pin  
  * @param  sda    Specific GPIO pin 
  */
void pinmux_iic3_init(uint8_t scl,uint8_t sda);

/**
  * @brief clean pin mux function of iic3
  */
void pinmux_iic3_deinit(void);

/**
  * @brief         Set pin mux function as iic4_io_init
  * @param  scl    Specific GPIO pin
  * @param  sda    Specific GPIO pin
  */
void pinmux_iic4_init(uint8_t scl,uint8_t sda);

/**
  * @brief clean pin mux function of iic4
  */
void pinmux_iic4_deinit(void);

/**
  * @brief         Set pin mux function as iic5_io_init
  * @param  scl    Specific GPIO pin
  * @param  sda    Specific GPIO pin
  */
void pinmux_iic5_init(uint8_t scl,uint8_t sda);

/**
  * @brief clean pin mux function of iic5
  */
void pinmux_iic5_deinit(void);

/**
  * @brief         Set pin mux function as iic6_io_init
  * @param  scl    Specific GPIO pin
  * @param  sda    Specific GPIO pin
  */
void pinmux_iic6_init(uint8_t scl,uint8_t sda);

/**
  * @brief clean pin mux function of iic6
  */
void pinmux_iic6_deinit(void);

/**
  * @brief Set pin mux function to espi
  */
void pinmux_espi_init(void);

/**
  * @brief clean pin mux function of espi
  */
void pinmux_espi_deinit(void);

/**
  * @brief         Set pin mux function to peci
  * @param  pin    Specific GPIO pin
  */
void pinmux_peci_init(void);

/**
  * @brief clear pin mux function of peci
  */
void pinmux_peci_deinit(void);

/**
  * @brief Set pin mux function to lpc
  */
void pinmux_lpc_init(void);

/**
  * @brief clean pin mux function of lpc
  */
void pinmux_lpc_deinit(void);

/**
  * @brief Set pin mux function to serirq
  */
void pinmux_lpc_serirq_init(void);

/**
  * @brief clean pin mux function of serirq
  */
void pinmux_lpc_serirq_deinit(void);

/**
  * @brief Set mux function of pin gadc1 of in0
  */
void pinmux_adc1_in0_init(void);

/**
  * @brief clear mux function of pin gadc1 of in0
  */
void pinmux_adc1_in0_deinit(void);

/**
  * @brief Set mux function of pin gadc1 of in1
  */
void pinmux_adc1_in1_init(void);

/**
  * @brief clear mux function of pin gadc1 of in1
  */
void pinmux_adc1_in1_deinit(void);

/**
  * @brief Set mux function of pin gadc1 of in2
  */
void pinmux_adc1_in2_init(void);

/**
  * @brief clear mux function of pin gadc1 of in2
  */
void pinmux_adc1_in2_deinit(void);

/**
  * @brief Set mux function of pin gadc1 of in3
  */
void pinmux_adc1_in3_init(void);

/**
  * @brief clear mux function of pin gadc1 of in3
  */
void pinmux_adc1_in3_deinit(void);

/**
  * @brief Set mux function of pin gadc1 of in4
  */
void pinmux_adc1_in4_init(void);

/**
  * @brief clear mux function of pin gadc1 of in4
  */
void pinmux_adc1_in4_deinit(void);

/**
  * @brief Set mux function of pin gadc1 of in5
  */
void pinmux_adc1_in5_init(void);

/**
  * @brief clear mux function of pin gadc1 of in5
  */
void pinmux_adc1_in5_deinit(void);

/**
  * @brief Set mux function of pin gadc1 of in6
  */
void pinmux_adc1_in6_init(void);

/**
  * @brief clear mux function of pin gadc1 of in6
  */
void pinmux_adc1_in6_deinit(void);

/**
  * @brief Set mux function of pin gadc1 of in7
  */
void pinmux_adc1_in7_init(void);

/**
  * @brief clear mux function of pin gadc1 of in7
  */
void pinmux_adc1_in7_deinit(void);

/**
  * @brief Set mux function of pin gadc2 of in0
  */
void pinmux_adc2_in0_init(void);

/**
  * @brief clear mux function of pin gadc2 of in0
  */
void pinmux_adc2_in0_deinit(void);

/**
  * @brief Set mux function of pin gadc2 of in1
  */
void pinmux_adc2_in1_init(void);

/**
  * @brief clear mux function of pin gadc2 of in1
  */
void pinmux_adc2_in1_deinit(void);

/**
  * @brief Set mux function of pin gadc2 of in2
  */
void pinmux_adc2_in2_init(void);

/**
  * @brief clear mux function of pin gadc2 of in2
  */
void pinmux_adc2_in2_deinit(void);

/**
  * @brief Set mux function of pin gadc2 of in3
  */
void pinmux_adc2_in3_init(void);

/**
  * @brief clear mux function of pin gadc2 of in3
  */
void pinmux_adc2_in3_deinit(void);

/**
  * @brief Set mux function of pin gadc2 of in4
  */
void pinmux_adc2_in4_init(void);

/**
  * @brief clear mux function of pin gadc2 of in4
  */
void pinmux_adc2_in4_deinit(void);

/**
  * @brief Set mux function of pin gadc2 of in5
  */
void pinmux_adc2_in5_init(void);

/**
  * @brief clear mux function of pin gadc2 of in5
  */
void pinmux_adc2_in5_deinit(void);

/**
  * @brief Set mux function of pin gadc2 of in6
  */
void pinmux_adc2_in6_init(void);

/**
  * @brief clear mux function of pin gadc2 of in6
  */
void pinmux_adc2_in6_deinit(void);

/**
  * @brief Set mux function of pin gadc2 of in7
  */
void pinmux_adc2_in7_init(void);

/**
  * @brief clear mux function of pin gadc2 of in7
  */
void pinmux_adc2_in7_deinit(void);

/**
  * @brief Set mux function of pin amic
  */
void pinmux_amic_init(void);

/**
  * @brief clear mux function of pin amic
  */
void pinmux_amic_deinit(void);

/**
  * @brief Set mux function of pin dac1 of in1
  */
void pinmux_dac1_out1_init(void);

/**
  * @brief clear mux function of pin dac1 of in1
  */
void pinmux_dac1_out1_deinit(void);

/**
  * @brief Set mux function of pin dac1 of in2
  */
void pinmux_dac1_out2_init(void);

/**
  * @brief clear mux function of pin dac1 of in2
  */
void pinmux_dac1_out2_deinit(void);

/**
  * @brief Set mux function of pin dac2 of in1
  */
void pinmux_dac2_out1_init(void);

/**
  * @brief clear mux function of pin dac2 of in1
  */
void pinmux_dac2_out1_deinit(void);

/**
  * @brief Set mux function of pin dac2 of in2
  */
void pinmux_dac2_out2_init(void);

/**
  * @brief clear mux function of pin dac2 of in2
  */
void pinmux_dac2_out2_deinit(void);

/**
 * @brief          Set pin mux function to bxcan (config of gpio)
 * @param txd      Specific GPIO pin 
 * @param rxd      Specific GPIO pin 
 */
void pinmux_fdcan_init(uint8_t txd,uint8_t rxd);

/**
 * @brief clear pin mux function of bxcan
 */
void pinmux_fdcan_deinit(void);

/**
 * @brief          Set pin mux function to cec
 * @param pin      Specific GPIO pin 
 */
void pinmux_cec_init(uint8_t pin);

/**
 * @brief           clear pin mux function of cec
 */
void pinmux_cec_deinit(void);

/**
 * @brief         Set pin mux function to cap channel 1
 * @param pin     Specific GPIO pin
 */
void pinmux_cap_ch1_init(uint8_t pin);

/**
 * @brief         clear pin mux function of cap channel 1
 */
void pinmux_cap_ch1_deinit(void);

/**
 * @brief           Set pin mux function to cap channel 2
 * @param pin       Specific GPIO pin
 */
void pinmux_cap_ch2_init(uint8_t pin);

/**
 * @brief           clear pin mux function of cap channel 2
 */
void pinmux_cap_ch2_deinit(void);

/**
 * @brief           Set pin mux function to cap channel 3
 * @param pin       Specific GPIO pin
 */
void pinmux_cap_ch3_init(uint8_t pin);

/**
 * @brief           clear pin mux function of cap channel 3
 */
void pinmux_cap_ch3_deinit(void);

/**
 * @brief         Set pin mux function to cap channel 4
 * @param pin     Specific GPIO pin
 */
void pinmux_cap_ch4_init(uint8_t pin);

/**
 * @brief         clear pin mux function of cap channel 4
 */
void pinmux_cap_ch4_deinit(void);

/**
 * @brief         Set pin mux function to cap channel 5
 * @param pin     Specific GPIO pin
 */
void pinmux_cap_ch5_init(uint8_t pin);

/**
 * @brief         clear pin mux function of cap channel 5
 */
void pinmux_cap_ch5_deinit(void);

/**
 * @brief         Set pin mux function to cap channel 6
 * @param pin     Specific GPIO pin
 */
void pinmux_cap_ch6_init(uint8_t pin);

/**
 * @brief         clear pin mux function of cap channel 6
 */
void pinmux_cap_ch6_deinit(void);

/**
 * @brief         Set pin mux function to cap channel 7
 * @param pin     Specific GPIO pin
 */
void pinmux_cap_ch7_init(uint8_t pin);

/**
 * @brief         clear pin mux function of cap channel 7
 */
void pinmux_cap_ch7_deinit(void);

/**
 * @brief           Set pin mux function to cap channel 8
 * @param pin       Specific GPIO pin
 */
void pinmux_cap_ch8_init(uint8_t pin);

/**
 * @brief           clear pin mux function of cap channel 8
 */
void pinmux_cap_ch8_deinit(void);

/**
 * @brief           Set pin mux function to owm
 * 
 * @param pin       Specific GPIO pin
 */
void pinmux_owm_init(uint8_t pin);

/**
 * @brief           clear pin mux function of owm
 */
void pinmux_owm_deinit(void);

/**
 * @brief             Set pin mux function to pwm
 * @param pin         Specific GPIO pin 
 */
void pinmux_pwm_ch1_init(uint8_t pin);

/**
 * @brief             clear pin mux function of pwm channel 1
 */
void pinmux_pwm_ch1_deinit(void);

/**
 * @brief             Set pin mux function to pwm channel 2
 * @param pin         Specific GPIO pin 
 */
void pinmux_pwm_ch2_init(uint8_t pin);

/**
 * @brief             clear pin mux function of pwm channel 2
 */
void pinmux_pwm_ch2_deinit(void);

/**
 * @brief             Set pin mux function to pwm channel 3
 * @param pin         Specific GPIO pin 
 */
void pinmux_pwm_ch3_init(uint8_t pin);

/**
 * @brief             clear pin mux function of pwm channel 3
 */
void pinmux_pwm_ch3_deinit(void);

/**
 * @brief             Set pin mux function to pwm channel 4
 * @param pin         Specific GPIO pin 
 */
void pinmux_pwm_ch4_init(uint8_t pin);

/**
 * @brief             clear pin mux function of pwm channel 4
 */
void pinmux_pwm_ch4_deinit(void);

/**
 * @brief             Set pin mux function to pwm channel 5
 * @param pin         Specific GPIO pin 
 */
void pinmux_pwm_ch5_init(uint8_t pin);

/**
 * @brief             clear pin mux function of pwm channel 5
 */
void pinmux_pwm_ch5_deinit(void);

/**
 * @brief             Set pin mux function to pwm channel 6
 * @param pin         Specific GPIO pin 
 */
void pinmux_pwm_ch6_init(uint8_t pin);

/**
 * @brief             clear pin mux function of pwm channel 6
 */
void pinmux_pwm_ch6_deinit(void);

/**
 * @brief             Set pin mux function to pwm channel 7
 * @param pin         Specific GPIO pin 
 */
void pinmux_pwm_ch7_init(uint8_t pin);

/**
 * @brief             clear pin mux function of pwm channel 7
 */
void pinmux_pwm_ch7_deinit(void);

/**
 * @brief             Set pin mux function to pwm channel 8
 * @param pin         Specific GPIO pin 
 */
void pinmux_pwm_ch8_init(uint8_t pin);

/**
 * @brief             clear pin mux function of pwm channel 8
 */
void pinmux_pwm_ch8_deinit(void);

/**
 * @brief          Set pin mux function to ps2h1
 * @param clk      Specific GPIO pin 
 * @param dat      Specific GPIO pin 
 */
void pinmux_ps2h1_init(uint8_t clk, uint8_t dat);

/**
 * @brief          Set pin mux function to ps2h2
 * @param clk      Specific GPIO pin 
 * @param dat      Specific GPIO pin 
 */
void pinmux_ps2h2_init(uint8_t clk, uint8_t dat);

/**
 * @brief          Set pin mux function to ps2h3
 * @param clk      Specific GPIO pin 
 * @param dat      Specific GPIO pin 
 */
void pinmux_ps2h3_init(uint8_t clk, uint8_t dat);

/**
 * @brief          Set pin mux function to ps2h4
 * @param clk      Specific GPIO pin 
 * @param dat      Specific GPIO pin 
 */
void pinmux_ps2h4_init(uint8_t clk, uint8_t dat);

/**
 * @brief             Init IO FOR Cjtag 
 */
void pinmux_cjtag_init();

/**
 * @brief            DeInit IO FOR Cjtag
 */
void pinmux_cjtag_deinit();

/**
 * @brief             Set pin mux function to kscan
 * @param col_en      Kscan col pin enable
 * @param row_en      Kscan row pin enable
 */
void pinmux_kscan_init(uint8_t col_en, uint32_t row_en);

/**
 * @brief          clear pin mux function of bxcan
 */
void pinmux_kscan_deinit(void);

/**
 * @brief             Init IO FOR USB 
 */
void pinmux_usb_init(bool host);

/**
 * @brief            DeInit IO FOR USB
 */
void pinmux_usb_deinit(void);

/**
 * @brief          Set pin mux function to usb cid
 * @param pin      Specific GPIO pin 
 */
void pinmux_usb_otg_id_init(uint8_t pin);

/**
 * @brief          PowerOn PD00,PD01
 */
void PD00_PD01_PowerOn(void);

#ifdef __cplusplus
}
#endif

#endif
