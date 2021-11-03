#ifndef LL_TEST_H_
#define LL_TEST_H_
#include "ll_evt.h"
#define TEST_PKT_ACCESS_CODE (0x71764129)
#define TEST_PKT_CRC_INIT (0x555555)

///Transmitter test Packet Payload Type
enum
{
    ///Pseudo-random 9 TX test payload type
    PAYL_PSEUDO_RAND_9            = 0x00,
    ///11110000 TX test payload type
    PAYL_11110000,
    ///10101010 TX test payload type
    PAYL_10101010,
    ///Pseudo-random 15 TX test payload type
    PAYL_PSEUDO_RAND_15,
    ///All 1s TX test payload type
    PAYL_ALL_1,
    ///All 0s TX test payload type
    PAYL_ALL_0,
    ///00001111 TX test payload type
    PAYL_00001111,
    ///01010101 TX test payload type
    PAYL_01010101,
};

void ll_test_env_reset(void);

enum co_error le_rx_test(uint8_t phy_ch);

enum co_error le_tx_test(uint8_t phy_ch,uint8_t length,uint8_t payload_type);

bool le_test_end(enum co_error *err,uint16_t *num_of_pkts);

void test_evt_end_handler(struct ll_evt *evt);

void test_evt_terminate_handler(struct ll_evt *evt);

enum ll_evt_start_type htimer_test_evt_start(struct ll_evt *evt);

enum ll_evt_transition_type htimer_test_tx_end(struct ll_evt *evt);

bool htimer_test_evt_header_rx(struct ll_evt *evt,bool third_byte,uint8_t *remain_length);

enum ll_evt_transition_type htimer_test_evt_rx_end(struct ll_evt *evt);

enum ll_evt_transition_type htimer_test_evt_sync_timeout(struct ll_evt *evt);

#endif
