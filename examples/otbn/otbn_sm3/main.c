#include <string.h>
#include <stdint.h>
#include "ls_hal_otbn_sha.h"
#include "platform.h"
#include "log.h"

static uint8_t string[] = "abc";
static uint8_t result[32];
// 0x66C7F0F462EEEDD9D1F2D46BDC10E4E24167C4875CF2F7A2297DA02B8F4BA8E0

/* Padding-boundary digests: [0..2] one Update per message, [3..5] same
 * messages fed byte-by-byte (exercises the HAL's internal buffering). */
static uint8_t g_edge[6][32];
static uint8_t edge_buf[57];

int main(void)
{
    sys_init_none();
    HAL_OTBN_Init();

    if (HAL_OTBN_SM3_Init() != HAL_OK ||
        HAL_OTBN_SM3_Update((uint8_t *)string, 3) != HAL_OK ||
        HAL_OTBN_SM3_Final(result) != HAL_OK) {
        LOG_I("SM3 fail!");
        while (1) ;
    }
    LOG_HEX((uint8_t *)result, 0x20);

    /* Padding-boundary tests: 55 bytes exactly fills one 64-byte block
     * (msg + 0x80 + 8-byte length), 56/57 cross into a second block.
     * Each length runs once as a single Update and once byte-by-byte. */
    memset(edge_buf, 'a', sizeof(edge_buf));
    static const uint32_t edge_len[3] = {55, 56, 57};
    for (int t = 0; t < 3; t++) {
        if (HAL_OTBN_SM3_Init() != HAL_OK ||
            HAL_OTBN_SM3_Update(edge_buf, edge_len[t]) != HAL_OK ||
            HAL_OTBN_SM3_Final(g_edge[t]) != HAL_OK) {
            LOG_I("SM3 edge test fail!");
            while (1) ;
        }
    }
    for (int t = 0; t < 3; t++) {
        if (HAL_OTBN_SM3_Init() != HAL_OK) {
            LOG_I("SM3 edge test fail!");
            while (1) ;
        }
        for (uint32_t i = 0; i < edge_len[t]; i++) {
            if (HAL_OTBN_SM3_Update(edge_buf + i, 1) != HAL_OK) {
                LOG_I("SM3 edge test fail!");
                while (1) ;
            }
        }
        if (HAL_OTBN_SM3_Final(g_edge[3 + t]) != HAL_OK) {
            LOG_I("SM3 edge test fail!");
            while (1) ;
        }
    }

    while (1) ;
}
