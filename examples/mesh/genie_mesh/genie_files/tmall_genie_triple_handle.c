#include <string.h>
#include <stdio.h>
#include "tmall_genie_triple_handle.h"
#include "tinycrypt/sha256.h"
#include "tinycrypt/constants.h"
#include "ls_hal_flash.h"

extern uint8_t ali_pid[TRIPLE_PID_LEN];
extern uint32_t ali_pid_u32;
extern uint8_t ali_mac[TRIPLE_MAC_LEN];
extern uint8_t ali_secret[TRIPLE_SECRET_LEN];
extern uint8_t ali_authvalue[ALI_AUTH_VALUE_LEN];

#define TMALL_TRITUPLE_FLASH_OFFSET (0x0200)

static uint8_t sha256_handler(const char *input_str, uint8_t *chiper)
{
    uint8_t ret = TC_CRYPTO_FAIL;
    uint8_t g_auth[32];
    struct tc_sha256_state_struct sha256_ctx;

    ret = tc_sha256_init(&sha256_ctx);
    if (ret == TC_CRYPTO_FAIL)
    {
        return ret;
    }

    ret = tc_sha256_update(&sha256_ctx, (const uint8_t *)input_str, strlen(input_str));
    if (ret == TC_CRYPTO_FAIL)
    {
        return ret;
    }

    ret = tc_sha256_final(&g_auth[0], &sha256_ctx);
    if (ret == TC_CRYPTO_FAIL)
    {
        return ret;
    }

    memcpy(chiper, &g_auth[0], 16);
    return ret;
}

void hextostring(const uint8_t *source, char *dest, int len)
{
    int i;
    char tmp[3];

    for (i = 0; i < len; i++)
    {
        sprintf(tmp, "%02x", (unsigned char)source[i]);
        memcpy(&dest[i * 2], tmp, 2);
    }
}

uint8_t gen_ali_authValue(void)
{
    uint8_t status = TC_CRYPTO_FAIL;
    char cal_ble_key_input[55] = ""; // pid + ',' + mac + ',' + secret = 8+1+12+1+32+'\0'
    char mac_str[(TRIPLE_MAC_LEN << 1) + 1] = "";
    char secret_str[(TRIPLE_SECRET_LEN << 1) + 1] = "";
    uint8_t tmp_arry[ALI_AUTH_VALUE_LEN] = {0};

    uint8_t ali_trituple[ALI_TRIPLE_SUM_LEN] = {0};
    hal_flash_fast_read(TMALL_TRITUPLE_FLASH_OFFSET, &ali_trituple[0], ALI_TRIPLE_SUM_LEN);
    if ((ali_trituple[0] != 0xff) && (ali_trituple[1] != 0xff) && (ali_trituple[2] != 0xff))
    {
        ali_pid_u32 = (((uint32_t)ali_trituple[0]) << 24) | (((uint32_t)ali_trituple[1]) << 16) | (((uint32_t)ali_trituple[2]) << 8) | (((uint32_t)ali_trituple[3]));
        memcpy(&ali_mac[0], &ali_trituple[TRIPLE_PID_LEN], TRIPLE_MAC_LEN);
        memcpy(&ali_secret[0], &ali_trituple[TRIPLE_PID_LEN + TRIPLE_MAC_LEN], TRIPLE_SECRET_LEN);
    }

    hextostring(ali_mac, mac_str, TRIPLE_MAC_LEN);
    hextostring(ali_secret, secret_str, TRIPLE_SECRET_LEN);

    sprintf(&cal_ble_key_input[0], "%08lx,%s,%s", ali_pid_u32, mac_str, secret_str);

    status = sha256_handler(&cal_ble_key_input[0], &ali_authvalue[0]);

    memcpy(&ali_pid[0], ((uint8_t *)&ali_pid_u32), TRIPLE_PID_LEN);

    memcpy(tmp_arry, ali_mac, TRIPLE_MAC_LEN);
    for (uint8_t j = 0; j < TRIPLE_MAC_LEN; j++)
    {
        ali_mac[j] = tmp_arry[TRIPLE_MAC_LEN - 1 - j];
    }

    memcpy(tmp_arry, ali_authvalue, ALI_AUTH_VALUE_LEN);
    for (uint8_t j = 0; j < ALI_AUTH_VALUE_LEN; j++)
    {
        ali_authvalue[j] = tmp_arry[ALI_AUTH_VALUE_LEN - 1 - j];
    }

    if (status == TC_CRYPTO_FAIL)
    {
        memset(&ali_authvalue[0], 0, ALI_AUTH_VALUE_LEN);
        return (0);
    }

    return (1);
}