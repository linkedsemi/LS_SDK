#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifndef _LS_24G_H_
#define _LS_24G_H_

#define VALID_TX_LEN_MAX 253

enum prop_24g_status
{
    PROP_24G_NO_ERROR = 0,
    PROP_24G_Invalid_status,
    PROP_24G_Invalid_param,
    PROP_24G_busy
};

enum prop_24g_state
{
    PROP_24G_STATE_IDLE = 0,
    PROP_24G_STATE_SCAN,
    PROP_24G_STATE_ADV,
};
enum prop_24g_tx_power_config
{
    TX_POWER_N_20dbm = 0,              // -20dbm
    TX_POWER_N_8dbm = 2,               // -8dbm
    TX_POWER_0dbm = 4,                 // 0dbm
    TX_POWER_4dbm = 8,                 // 4dbm
    TX_POWER_10dbm = 7,                // 10dbm
    TX_POWER_12dbm = 0xB,              // 12dbm

    TX_POWER_MAX = TX_POWER_12dbm + 1,
};
enum prop_24g_phy
{
    PROP_24G_PHY_1MBPS = 0,
    PROP_24G_PHY_2MBPS,
    PROP_24G_PHY_125KBPS,
    PROP_24G_PHY_500KBPS,
};
enum prop_24g_tx_rx_format
{
    PROP_24G_EXT_ADV_FORMAT = 0,
    PROP_24G_LEGACY_ADV_FORMAT
};

struct prop_24g_tx_rx_cntl_env
{
    uint8_t *dataptr;
    void (*cb)(void*);
    void *param;
    uint8_t *length;
    // bool finished;
};

/**
 ****************************************************************************************
 * \brief Copy memory from source to destination while the code runs on RAM. 
 *        Use this function in interrupt instead of memcpy.
 *
 * \param[in]     src                     Pointer of the source buffer.
 * \param[inout]  dst                     Pointer of the destination buffer.
 * \param[in]     length                  Length of data to copy in units of byte.
 *
 ****************************************************************************************
 */
void memcpy_ram(void *dst, const void *src, uint32_t length);
/**
 ****************************************************************************************
 * \brief 2.4G initialization.
 *
 ****************************************************************************************
 */
void RF_24g_Init(void);
/**
 ****************************************************************************************
 * \brief Stop 2.4G activity. Actually only RX need to be stopped by user. The function 
 *        has nothing to do with TX which will go to end automatically when all the data
 *        have been sent. 
 *        The implementation relies on flag-checking modified in certain interrupt, so don't 
 *        call this function in irq_handler or call-back!
 *
 ****************************************************************************************
 */
void RF_24g_Stop(void);
/**
 ****************************************************************************************
 * \brief Set the RF channel used to send and receive 2.4G data.
 *
 * \param[in]     channel                     Channel number.
 *
 ****************************************************************************************
 */
void RF_24g_SetChannel(uint16_t channel);
/**
 ****************************************************************************************
 * \brief Set the PHY used to send and receive 2.4G data.
 *
 * \param[in]     phy                         PHY. Refer to ::prop_24g_phy.
 *
 ****************************************************************************************
 */
void RF_24g_SetPhy(uint8_t phy);
/**
 ****************************************************************************************
 * \brief Get the RF channel configuration.
 *
 * \return                                     Channel number.
 *
 ****************************************************************************************
 */
uint16_t RF_24g_GetChannel(void);
/**
 ****************************************************************************************
 * \brief Get RSSI.
 *
 * \return                                     RSSI value.
 *
 ****************************************************************************************
 */
int8_t RF_24g_GetRssi(void);
/**
 ****************************************************************************************
 * \brief Set TX power.
 *
 * \param[in]     tx_pwr_config                TX power value. Refer to ::prop_24g_tx_power_config
 *
 ****************************************************************************************
 */
void RF_24g_SetPower(enum prop_24g_tx_power_config tx_pwr_config);
/**
 ****************************************************************************************
 * \brief 2.4G packets send function.
 *
 * \param[in]     txBuf                        Pointer to buffer contains data to send.
 * \param[in]     txLen                        Length of data to send in units of byte.
 * \param[in]     Tx_cmpt_cb                   TX complete callback that will be called in interrupt.
 * \param[in]     param                        TX complete callback parameter.
 * \return                                     Status of TX process. Refer to ::prop_24g_status.
 *
 ****************************************************************************************
 */
enum prop_24g_status RF_24g_Tx(uint8_t *txBuf, uint8_t txLen, void (*Tx_cmpt_cb)(void *), void *param);
/**
 ****************************************************************************************
 * \brief 2.4G packets receive function.
 *
 * \param[in]     rxBuf                        Pointer to buffer contains data to receive.
 * \param[in]     rxLen                        Pointer to the length of data received.
 * \param[in]     Rx_cmpt_cb                   RX complete callback that will be called in interrupt.
 * \param[in]     param                        RX complete callback parameter.
 * \return                                     Status of RX process. Refer to ::prop_24g_status.
 *
 ****************************************************************************************
 */
enum prop_24g_status RF_24g_Rx(uint8_t *rxBuf, uint8_t *rxLen, void (*Rx_cmpt_cb)(void *), void *param);
/**
 ****************************************************************************************
 * \brief Get 2.4G state.
 *
 * \return                                     2.4G state. Refer to ::prop_24g_state.
 *
 ****************************************************************************************
 */
uint8_t get_cur_prop_24g_state(void);
#endif
