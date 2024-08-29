#include "linked_buffer.h"
#include "sw_cache.h"
#include "ll_ext_adv.h"
#include "ll_ext_scan.h"
#include "ll_sync.h"
#include "ll_conn.h"
#include "ll_hci.h"
#include "ll_env.h"
#include "white_list.h"
#include "per_adv_list.h"
#include "adv_report_cache.h"
#include "async_call.h"
#include "evt_ctrl.h"
#define ADV_SETS_NUM 1
#define LL_CONNECTION_MAX 1
#define SCAN_RX_BUF_NUM (5)
#define SECOND_SCAN_BUF_NUM (0)
#define HCI_ACL_DATA_RX_BUFFER_NUM (2*LL_CONNECTION_MAX)  //tx_data_buf_num
#define HCI_ACL_DATA_TX_BUFFER_NUM 10//(2*LL_CONNECTION_MAX)
#define LL_SYNC_ENV_NUM 0
#define SYNC_RX_BUF_NUM 0
#define HCI_TX_ELEMENT_MAX_NUM 10
#define AES_128_CALC_ENV_BUF_SIZE 2
#define LL_SCHED_BUF_NUM (10)
#define SWINT_POST_BUF_NUM (10)
#define WHITE_LIST_SIZE 1
#define PER_ADV_LIST_SIZE 1
#define ADV_REPORT_CACHE_SIZE 2
#define SW_TIMER_BUF_NUM 5

#define TX_RAMPUP_TIME (110)
#define TX_RAMPDOWN_TIME (1)
#define RX_RAMPUP_TIME (110)
#define RX_PATH_DELAY_1M_PHY (28)
#define RX_PATH_DELAY_2M_PHY (15)
#define TX_PATH_DELAY_1M_PHY (2)
#define TX_PATH_DELAY_2M_PHY (2)

//ll_ext_adv
struct adv_set_env adv_sets[ADV_SETS_NUM];
extern struct adv_set_env *adv_sets_ptr;

//ll_ext_scan
struct ll_ext_scan_env ll_ext_scan;
DEF_LINKED_BUF(prim_scan_rx_buf, struct prim_scan_rx_env, SCAN_RX_BUF_NUM);
DEF_LINKED_BUF(second_scan_buf,struct second_scan_buf_env, SECOND_SCAN_BUF_NUM);
extern struct ll_ext_scan_env *ll_ext_scan_ptr;
extern linked_buffer_t *second_scan_buf_ptr;
extern linked_buffer_t *prim_scan_rx_buf_ptr;

//ll_sync
DEF_LINKED_BUF(ll_sync_env,struct sync_env, LL_SYNC_ENV_NUM);
DEF_LINKED_BUF(sync_rx_buf,struct sync_evt_rx_env, SYNC_RX_BUF_NUM);
extern linked_buffer_t *ll_sync_env_ptr;
extern linked_buffer_t *sync_rx_buf_ptr;

//ll_conn
DEF_LINKED_BUF(ll_conn_buf,struct ll_conn_env,LL_CONNECTION_MAX);
DEF_LINKED_BUF(ll_conn_rx_buf, struct hci_acl_air_rx_data, HCI_ACL_DATA_TX_BUFFER_NUM);
DEF_LINKED_BUF(hci_acl_data_rx_buf, struct hci_acl_air_tx_data, HCI_ACL_DATA_RX_BUFFER_NUM);
extern linked_buffer_t *ll_conn_buf_ptr;
extern linked_buffer_t *ll_conn_rx_buf_ptr;
extern linked_buffer_t *hci_acl_data_rx_buf_ptr;

//ll_hci
DEF_LINKED_BUF(hci_tx_element_buf, struct hci_tx_element, HCI_TX_ELEMENT_MAX_NUM);
extern linked_buffer_t *hci_tx_element_buf_ptr;

//ll_env
DEF_LINKED_BUF(aes_128_calc_env_buf, struct aes_128_calc_env, AES_128_CALC_ENV_BUF_SIZE);
extern linked_buffer_t *aes_128_calc_env_buf_ptr;

//ll_sched
DEF_FIFO(ll_sched_fifo,struct async_call_param,LL_SCHED_BUF_NUM);
DEF_FIFO(swint2_post_fifo,struct async_call_param,SWINT_POST_BUF_NUM);
extern struct fifo_env *ll_sched_fifo_ptr;
extern struct fifo_env *swint2_post_fifo_ptr;

//white_list
DEF_SW_CACHE(white_list_cache,struct dev_addr_cache, WHITE_LIST_SIZE);
extern struct sw_cache *white_list_cache_ptr;

//per_adv_list
DEF_SW_CACHE(per_adv_list,struct per_adv_list_env,PER_ADV_LIST_SIZE);
extern struct sw_cache *per_adv_list_ptr;

//adv_report_cache
DEF_SW_CACHE(adv_rx_cache,struct adv_report_cache,ADV_REPORT_CACHE_SIZE);
extern struct sw_cache *adv_rx_cache_ptr;

//timer_wrapper
DEF_LINKED_BUF(sw_timer_buf,struct sw_timer_env,SW_TIMER_BUF_NUM);
extern linked_buffer_t *sw_timer_buf_ptr;

extern void (*hci_reset_reset_buf_fn)(void);

#ifdef LE501X
#define TX_DESC_NUM (20)
#define RX_DESC_NUM (HCI_ACL_DATA_TX_BUFFER_NUM - 1)
struct rx_desc rx_desc_buf[RX_DESC_NUM];
struct tx_desc tx_desc_buf[LL_CONNECTION_MAX][TX_DESC_NUM];
static void tx_rx_desc_buf_init()
{
    rx_desc_buf_ptr = rx_desc_buf;
    tx_desc_buf_ptr = tx_desc_buf;
    tx_desc_buf_num = TX_DESC_NUM;
    rx_desc_buf_num = RX_DESC_NUM;
}
#else
static void tx_rx_desc_buf_init(){}
#endif
static void adv_report_cache_init(void)
{
    adv_rx_cache_ptr = &adv_rx_cache;
}

static void adv_report_cache_reset(void)
{
    INIT_SW_CACHE(adv_rx_cache);
}

static void hci_acl_data_rx_buf_init()
{
    hci_acl_data_rx_buf_ptr = &hci_acl_data_rx_buf;
}

static void hci_acl_data_rx_buf_reset()
{
    INIT_LINKED_BUF(hci_acl_data_rx_buf);
}

static void rx_buf_list_init()
{
    ll_conn_rx_buf_ptr = &ll_conn_rx_buf;
}

static void rx_buf_list_reset()
{
    INIT_LINKED_BUF(ll_conn_rx_buf);
}

static void ll_conn_buf_init()
{
    ll_conn_buf_ptr = &ll_conn_buf;
}

static void ll_conn_buf_reset()
{
    INIT_LINKED_BUF(ll_conn_buf);
}

static void aes_128_calc_env_buf_init()
{
    aes_128_calc_env_buf_ptr = &aes_128_calc_env_buf;
}

static void aes_128_calc_env_buf_reset()
{
    INIT_LINKED_BUF(aes_128_calc_env_buf);
}

static void ll_ext_scan_buf_init()
{
    ll_ext_scan_ptr = &ll_ext_scan;
    prim_scan_rx_buf_ptr = &prim_scan_rx_buf;
    second_scan_buf_ptr = &second_scan_buf;
}

static void ll_ext_scan_buf_reset()
{
    INIT_LINKED_BUF(prim_scan_rx_buf);
    INIT_LINKED_BUF(second_scan_buf);
}

static void hci_tx_element_buf_init()
{
    hci_tx_element_buf_ptr = &hci_tx_element_buf;
}

static void hci_tx_element_buf_reset()
{
    INIT_LINKED_BUF(hci_tx_element_buf);
}

static void ll_sched_init()
{
    ll_sched_fifo_ptr = &ll_sched_fifo;
}

static void ll_sched_reset()
{
    INIT_FIFO(ll_sched_fifo);
}

static void swint2_fifo_init()
{
    swint2_post_fifo_ptr = &swint2_post_fifo;
}

static void swint2_fifo_reset()
{
    INIT_FIFO(swint2_post_fifo);
}

static void ll_sync_buf_init()
{
    ll_sync_env_ptr = &ll_sync_env;
    sync_rx_buf_ptr = &sync_rx_buf;
}

static void ll_sync_buf_reset()
{
    INIT_LINKED_BUF(ll_sync_env);
    INIT_LINKED_BUF(sync_rx_buf);
}

static void per_adv_list_init(void)
{
    per_adv_list_ptr = &per_adv_list;
}

static void per_adv_list_reset()
{
    INIT_SW_CACHE(per_adv_list);
}

static void white_list_buf_init()
{
    white_list_cache_ptr = &white_list_cache;
}

static void white_list_buf_reset()
{
    INIT_SW_CACHE(white_list_cache);
}

static void sw_timer_buf_init()
{
    sw_timer_buf_ptr = &sw_timer_buf;
}

static void sw_timer_buf_reset()
{
    INIT_LINKED_BUF(sw_timer_buf);
}

void hci_reset_reset_buf()
{
    adv_report_cache_reset();
    hci_acl_data_rx_buf_reset();
    rx_buf_list_reset();
    //tx_desc_list_reset();
    ll_conn_buf_reset();
    ll_ext_scan_buf_reset();
    hci_tx_element_buf_reset();
    ll_sync_buf_reset();
    per_adv_list_reset();
    white_list_buf_reset();
    sw_timer_buf_reset();
    swint2_fifo_reset();
    aes_128_calc_env_buf_reset();
}

void ll_buf_init()
{
    tx_rampup_time = TX_RAMPUP_TIME;
    tx_rampdown_time_minus_1 = TX_RAMPDOWN_TIME - 1;
    rx_rampup_time = RX_RAMPUP_TIME;
    rx_path_delay_1m_phy = RX_PATH_DELAY_1M_PHY;
    rx_path_delay_2m_phy = RX_PATH_DELAY_2M_PHY;
    tx_path_delay_1m_phy = TX_PATH_DELAY_1M_PHY;
    tx_path_delay_2m_phy = TX_PATH_DELAY_2M_PHY;

    hci_reset_reset_buf_fn = hci_reset_reset_buf;
    adv_sets_ptr = adv_sets;
    adv_sets_num = ADV_SETS_NUM;
    per_adv_list_size = PER_ADV_LIST_SIZE;
    white_list_size = WHITE_LIST_SIZE;
    conn_data_max_len = CONN_DATA_MAX_LEN;
    tx_data_buf_num = HCI_ACL_DATA_RX_BUFFER_NUM;
    ll_default_tx_pwr = 0x7;
    adv_report_cache_init();
    hci_acl_data_rx_buf_init();
    rx_buf_list_init();
    ll_conn_buf_init();
    ll_ext_scan_buf_init();
    hci_tx_element_buf_init();
    ll_sync_buf_init();
    per_adv_list_init();
    white_list_buf_init();
    sw_timer_buf_init();
    swint2_fifo_init();
    aes_128_calc_env_buf_init();
    tx_rx_desc_buf_init();

    ll_sched_init();
    ll_sched_reset();
}

