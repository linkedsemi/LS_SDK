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
    PROP_24G_PHY_2MBPS
};

struct prop_24g_tx_rx_cntl_env
{
    uint8_t *dataptr;
    void (*cb)(void*);
    void *param;
    uint8_t *length;
    // bool finished;
};

// Use this function in interrupt instead of memcpy!!!
void memcpy_ram(void *dst, const void *src, uint32_t length);

void RF_24g_Init(void);
// void RF_24g_Start(void);
// Only rx can be stopped!!!
void RF_24g_Stop(void);
void RF_24g_SetChannel(uint16_t channel);
void RF_24g_SetPhy(uint8_t phy);
uint16_t RF_24g_GetChannel(void);
int8_t RF_24g_GetRssi(void);
void RF_24g_SetPower(enum prop_24g_tx_power_config tx_pwr_config);
enum prop_24g_status RF_24g_Tx(uint8_t *txBuf, uint8_t txLen, void (*Tx_cmpt_cb)(void *), void *param);
enum prop_24g_status RF_24g_Rx(uint8_t *rxBuf, uint8_t *rxLen, void (*Rx_cmpt_cb)(void *), void *param);
#endif
