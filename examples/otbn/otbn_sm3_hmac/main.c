/*
 * OTBN SM3 HMAC bare-metal test
 *
 * Tests HAL_OTBN_SM3_HMAC_* interfaces:
 *   1. One-shot  — HAL_OTBN_SM3_HMAC()
 *   2. Streaming — HAL_OTBN_SM3_HMAC_SetKey / Update / Final
 *   3. Generic   — HAL_OTBN_HASH_HMAC(OTBN_HASH_ALGO_SM3, ...)
 *   4. LSSHA cross-check (HAL_LSSHA_SM3_HMAC)
 *
 * Build:  scons ic=qsh  (from this directory)
 */

#include <string.h>
#include <stdint.h>
#include "ls_hal_otbn_sha.h"
#include "ls_hal_sha.h"
#include "platform.h"
#include "log.h"

#define SM3_MAC_LEN 32

static unsigned int g_pass, g_fail;

#define CHECK(cond, tag) do {                                           \
    if (cond) { g_pass++; LOG_I("[PASS] %s", tag); }                   \
    else      { g_fail++; LOG_I("[FAIL] %s", tag); }                   \
} while (0)

static void hexdump(const char *tag, const uint8_t *buf, uint32_t len)
{
    LOG_I("%s:", tag);
    LOG_HEX((uint8_t *)buf, len);
}

/* constant-time MAC compare */
static int mac_equal(const uint8_t *a, const uint8_t *b, uint32_t len)
{
    volatile uint8_t diff = 0;
    for (uint32_t i = 0; i < len; i++)
        diff |= a[i] ^ b[i];
    return diff == 0;
}

/* ── Test vectors ──────────────────────────────────────────────────── */

/* TV1: 16-byte key, short message */
static const uint8_t tv1_key[] = {
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
};
static const uint8_t tv1_msg[] =
    "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";

/* TV2: 64-byte key (exact block size), 8-byte msg */
static const uint8_t tv2_key[64] = { [0 ... 63] = 0x0b };
static const uint8_t tv2_msg[] = "Hi There";

/* TV3: 80-byte key (> block size, triggers key hash), 4096-byte msg */
static const uint8_t tv3_key[80] = { [0 ... 79] = 0xaa };
static uint8_t tv3_long_msg[4096];  /* filled with 0xdd in main */

/* TV4: 4-byte key, empty message */
static const uint8_t tv4_key[] = { 0x4a, 0x65, 0x66, 0x65 };  /* "Jefe" */
static const uint8_t tv4_msg[] = "";

/* ── Test functions ────────────────────────────────────────────────── */

/* one-shot vs streaming consistency */
static void test_oneshot_vs_streaming(const uint8_t *key, uint32_t key_len,
                                      const uint8_t *msg, uint32_t msg_len,
                                      const char *label)
{
    uint8_t mac_oneshot[SM3_MAC_LEN];
    uint8_t mac_stream[SM3_MAC_LEN];

    if (HAL_OTBN_SM3_HMAC(mac_oneshot, (uint8_t *)msg, msg_len,
                          (uint8_t *)key, key_len) != HAL_OK) {
        CHECK(0, "HMAC oneshot returns OK");
        return;
    }
    CHECK(1, "HMAC oneshot returns OK");

    if (HAL_OTBN_SM3_HMAC_SetKey((uint8_t *)key, key_len) != HAL_OK) {
        CHECK(0, "HMAC_SetKey returns OK");
        return;
    }
    CHECK(1, "HMAC_SetKey returns OK");

    if (msg_len > 0) {
        if (HAL_OTBN_SM3_HMAC_Update((uint8_t *)msg, msg_len) != HAL_OK) {
            CHECK(0, "HMAC_Update returns OK");
            return;
        }
        CHECK(1, "HMAC_Update returns OK");
    }

    if (HAL_OTBN_SM3_HMAC_Final(mac_stream) != HAL_OK) {
        CHECK(0, "HMAC_Final returns OK");
        return;
    }
    CHECK(1, "HMAC_Final returns OK");

    CHECK(mac_equal(mac_oneshot, mac_stream, SM3_MAC_LEN),
          "oneshot == streaming");
    hexdump(label, mac_oneshot, SM3_MAC_LEN);
}

/* OTBN vs LSSHA cross-validation */
static void test_otbn_vs_lssha(const uint8_t *key, uint32_t key_len,
                                const uint8_t *msg, uint32_t msg_len,
                                const char *label)
{
    uint8_t mac_otbn[SM3_MAC_LEN];
    uint8_t mac_lssha[SM3_MAC_LEN];

    if (HAL_OTBN_SM3_HMAC(mac_otbn, (uint8_t *)msg, msg_len,
                          (uint8_t *)key, key_len) != HAL_OK) {
        CHECK(0, "OTBN SM3_HMAC returns OK");
        return;
    }
    CHECK(1, "OTBN SM3_HMAC returns OK");

    if (HAL_LSSHA_SM3_HMAC(mac_lssha, (uint8_t *)msg, msg_len,
                           (uint8_t *)key, key_len) != HAL_OK) {
        CHECK(0, "LSSHA SM3_HMAC returns OK");
        return;
    }
    CHECK(1, "LSSHA SM3_HMAC returns OK");

    CHECK(mac_equal(mac_otbn, mac_lssha, SM3_MAC_LEN),
          "OTBN == LSSHA");
    hexdump(label, mac_otbn, SM3_MAC_LEN);
}

/* generic wrapper vs dedicated API */
static void test_generic_vs_dedicated(const uint8_t *key, uint32_t key_len,
                                      const uint8_t *msg, uint32_t msg_len,
                                      const char *label)
{
    uint8_t mac_dedicated[SM3_MAC_LEN];
    uint8_t mac_generic[SM3_MAC_LEN];

    if (HAL_OTBN_SM3_HMAC(mac_dedicated, (uint8_t *)msg, msg_len,
                          (uint8_t *)key, key_len) != HAL_OK) {
        CHECK(0, "dedicated SM3_HMAC returns OK");
        return;
    }
    CHECK(1, "dedicated SM3_HMAC returns OK");

    otbn_hash_hamc_env hmac;
    hmac.hash_algo = OTBN_HASH_ALGO_SM3;
    if (HAL_OTBN_HASH_HMAC_SetKey(&hmac, (uint8_t *)key, key_len) != HAL_OK) {
        CHECK(0, "generic HMAC_SetKey returns OK");
        return;
    }
    CHECK(1, "generic HMAC_SetKey returns OK");

    if (msg_len > 0) {
        if (HAL_OTBN_HASH_HMAC_Update(&hmac, (uint8_t *)msg, msg_len) != HAL_OK) {
            CHECK(0, "generic HMAC_Update returns OK");
            return;
        }
        CHECK(1, "generic HMAC_Update returns OK");
    }

    if (HAL_OTBN_HASH_HMAC_Final(&hmac, mac_generic) != HAL_OK) {
        CHECK(0, "generic HMAC_Final returns OK");
        return;
    }
    CHECK(1, "generic HMAC_Final returns OK");

    CHECK(mac_equal(mac_dedicated, mac_generic, SM3_MAC_LEN),
          "dedicated == generic");
    hexdump(label, mac_generic, SM3_MAC_LEN);
}

/* chunked streaming (odd-sized chunks) */
static void test_streaming_chunks(const uint8_t *key, uint32_t key_len,
                                  const uint8_t *msg, uint32_t msg_len,
                                  const char *label)
{
    uint8_t mac_whole[SM3_MAC_LEN];
    uint8_t mac_chunk[SM3_MAC_LEN];
    uint32_t chunk_size = 13;

    if (HAL_OTBN_SM3_HMAC(mac_whole, (uint8_t *)msg, msg_len,
                          (uint8_t *)key, key_len) != HAL_OK) {
        CHECK(0, "whole HMAC returns OK");
        return;
    }
    CHECK(1, "whole HMAC returns OK");

    if (HAL_OTBN_SM3_HMAC_SetKey((uint8_t *)key, key_len) != HAL_OK) {
        CHECK(0, "chunked HMAC_SetKey returns OK");
        return;
    }
    CHECK(1, "chunked HMAC_SetKey returns OK");

    uint32_t off = 0;
    while (off < msg_len) {
        uint32_t n = (msg_len - off < chunk_size) ? (msg_len - off) : chunk_size;
        if (HAL_OTBN_SM3_HMAC_Update((uint8_t *)msg + off, n) != HAL_OK) {
            CHECK(0, "chunked HMAC_Update returns OK");
            return;
        }
        off += n;
    }
    CHECK(1, "chunked HMAC_Update returns OK");

    if (HAL_OTBN_SM3_HMAC_Final(mac_chunk) != HAL_OK) {
        CHECK(0, "chunked HMAC_Final returns OK");
        return;
    }
    CHECK(1, "chunked HMAC_Final returns OK");

    CHECK(mac_equal(mac_whole, mac_chunk, SM3_MAC_LEN),
          "whole == chunked");
    hexdump(label, mac_chunk, SM3_MAC_LEN);
}

/* ── main ──────────────────────────────────────────────────────────── */

int main(void)
{
    sys_init_none();
    HAL_OTBN_Init();

    memset(tv3_long_msg, 0xdd, sizeof(tv3_long_msg));

    LOG_I("=== OTBN SM3 HMAC Test ===");

    /* TV1: 16-byte key, 56-byte msg */
    LOG_I("TV1: 16B key, %dB msg", (int)(sizeof(tv1_msg) - 1));
    test_oneshot_vs_streaming(tv1_key, sizeof(tv1_key),
                              tv1_msg, sizeof(tv1_msg) - 1,
                              "TV1 OTBN SM3-HMAC");

    /* TV2: 64-byte key (exact block), 8-byte msg */
    LOG_I("TV2: 64B key, %dB msg", (int)(sizeof(tv2_msg) - 1));
    test_oneshot_vs_streaming(tv2_key, sizeof(tv2_key),
                              tv2_msg, sizeof(tv2_msg) - 1,
                              "TV2 OTBN SM3-HMAC");

    /* TV3: 80-byte key (> block), 4096-byte msg */
    LOG_I("TV3: 80B key (>block), 4096B msg");
    test_oneshot_vs_streaming(tv3_key, sizeof(tv3_key),
                              tv3_long_msg, sizeof(tv3_long_msg),
                              "TV3 OTBN SM3-HMAC");

    /* TV4: empty message */
    LOG_I("TV4: 4B key, 0B msg");
    test_oneshot_vs_streaming(tv4_key, sizeof(tv4_key),
                              tv4_msg, 0,
                              "TV4 OTBN SM3-HMAC");

    /* TV5: chunked streaming */
    LOG_I("TV5: chunked (13B pieces, 4096B msg)");
    test_streaming_chunks(tv3_key, sizeof(tv3_key),
                          tv3_long_msg, sizeof(tv3_long_msg),
                          "TV5 chunked SM3-HMAC");

    /* TV6: generic wrapper */
    LOG_I("TV6: generic vs dedicated");
    test_generic_vs_dedicated(tv1_key, sizeof(tv1_key),
                              tv1_msg, sizeof(tv1_msg) - 1,
                              "TV6 generic SM3-HMAC");

    /* TV7: OTBN vs LSSHA */
    LOG_I("TV7: OTBN vs LSSHA");
    test_otbn_vs_lssha(tv1_key, sizeof(tv1_key),
                       tv1_msg, sizeof(tv1_msg) - 1,
                       "TV7 OTBN-vs-LSSHA");

    LOG_I("=== Result: %d passed, %d failed ===", g_pass, g_fail);

    while (1) ;
}
