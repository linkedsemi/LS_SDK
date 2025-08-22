#ifndef BOOT_H_
#define BOOT_H_
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "boot_port.h"

#define SM2_PRIVATEKEY_LENGTH           (0x20)
#define SM4_KEY_LENGTH                  (0x10)
#define AES256_KEY_LENGTH               (0x20)

#define HASH_SM3_LENGTH     (0x20)
#define HASH_SHA256_LENGTH  (0x20)
#define HASH_SHA384_LENGTH  (0x30)
#define HASH_MAX_LENGTH  (0x40)

#define TEST_WORD0 0xa5a53c3c
#define TEST_WORD1 0x5a5ac3c3

extern uint8_t temp_buf[TEMP_BUF_SIZE];
extern struct boot_otp otp_cfg;
extern struct BOOT_Share shareMemory;

enum BOOT_LIFE_CYCLE_STATUS
{
    BOOT_LIFE_CYCLE_STATUS_FRA          = 0x00,
    BOOT_LIFE_CYCLE_STATUS_NON_DEBUG    = 0xFC,
    BOOT_LIFE_CYCLE_STATUS_APP_DEBUG    = 0xFE,
    BOOT_LIFE_CYCLE_STATUS_BLANK        = 0xFF,
};

enum BOOT_START_FROM
{
    BOOT_START_FROM_A = 0,
    BOOT_START_FROM_B,
    BOOT_START_FROM_UART,
};

enum BOOT_BLOCK_CIPHER_MODE
{
    BOOT_BLOCK_CIPHER_MODE_GCM = 0,
    BOOT_BLOCK_CIPHER_MODE_CBC,       // Cipher-Block Chaining (:ref:`cbc_mode`)
    BOOT_BLOCK_CIPHER_MODE_CTR,       // Counter mode (:ref:`ctr_mode`)
    BOOT_BLOCK_CIPHER_MODE_ECB,       // Electronic Code Book (:ref:`ecb_mode`)
    BOOT_BLOCK_CIPHER_MODE_CFB,      // Cipher Feedback (:ref:`cfb_mode`)
    BOOT_BLOCK_CIPHER_MODE_OFB,       // Output Feedback (:ref:`ofb_mode`)
};

enum BOOT_HASH_ALGO
{
    BOOT_HASH_ALGO_SHA256 = 0,
    BOOT_HASH_ALGO_SHA384 = 1,
    BOOT_HASH_ALGO_SM3 = 6,
};

enum BOOT_KEY_DERIVE_ALGO
{
    BOOT_KEY_DERIVE_ALGO_NONE           = 0x00,
    BOOT_KEY_DERIVE_ALGO_KEK            = 0x01,
    BOOT_KEY_DERIVE_ALGO_HKDF_SM3       = 0x10,
    BOOT_KEY_DERIVE_ALGO_HKDF_SHA256    = 0x11,
    BOOT_KEY_DERIVE_ALGO_HKDF_SHA384    = 0x12,
};

enum BOOT_ECC_CURVE_TYPE
{
    BOOT_ECC_Curve_P256 = 3,
    BOOT_ECC_Curve_P384 = 4,
    BOOT_ECC_Curve_SM2 = 6,
};

typedef struct entryParam
{
    uint32_t offset;
    uint32_t size;
    uint32_t exe_addr;
} entryParam_t;

typedef struct imageHeader
{
    uint32_t test_word[2];
    uint32_t offset;
    uint32_t length;
    uint32_t version;
    uint8_t decrypt_key_id;
    uint8_t public_key_id;
    uint8_t key_derive_algo;
    uint8_t realtime_decrypt_lock;
    uint8_t iv[0x10];
    uint8_t encrypt_key[0x90];
    uint8_t sign[0x40];
    uint32_t exe_addr;
    uint32_t header_crc;
} imageHeader_t;

void platform_init();
void goto_next(void *exe_addr);
void boot_otp_code_check();
void boot_life_cycle_update_request(uint8_t life_cycle, uint32_t *token, uint32_t bitmap_addr);
void boot_life_cycle_check();
void boot_open_wdg();
bool boot_io_read(uint8_t pin);
uint8_t boot_flow_get();
void clr_startup_part_flag();

uint32_t boot_crc32(uint8_t *data, uint32_t length);

void boot_uart_init();
void boot_uart_buaddetect_cb();
void boot_uart_tx_cb();
void boot_uart_rx_cb();
void boot_uart_read(uint8_t *buf,uint16_t length, bool it_mode);
void boot_uart_write(uint8_t *buf,uint16_t length, bool it_mode);

void boot_flash_start_xip(uint32_t offset);
void boot_flash_sm4_realtime_decrypt(uint8_t *nonce, uint8_t *key, uint32_t start, uint32_t end, bool lock);
void boot_flash_read(uint32_t offset, uint8_t * data, uint32_t length);

void boot_set_otp_premission();
void boot_otp_read(uint32_t offset, uint8_t *data, uint32_t length);

void boot_hash(enum BOOT_HASH_ALGO algo, uint8_t *data, uint32_t length, uint8_t *hash_val);
void boot_sha256_flash(uint32_t offset, uint32_t length, uint8_t hash_val[HASH_SHA256_LENGTH]);
void boot_sha384_flash(uint32_t offset, uint32_t length, uint8_t hash_val[HASH_SHA384_LENGTH]);
void boot_sm3_flash(uint32_t offset, uint32_t length, uint8_t hash_val[HASH_SM3_LENGTH]);
void boot_sm3_ecdsa(uint8_t *pubkey_x, uint8_t *pubkey_y, uint8_t *msg, uint32_t msg_len, uint8_t hash_val[HASH_SM3_LENGTH]);
void boot_sm3_ecdsa_flash(uint8_t *pubkey_x, uint8_t *pubkey_y, uint32_t offset, uint32_t msg_len, uint8_t hash_val[HASH_SM3_LENGTH]);

bool boot_sm2_decrypt(uint8_t *ciphertext, uint8_t *plaintext, uint32_t klen, uint8_t *private_key, bool standard_mode);
bool boot_ecc_verify(enum BOOT_ECC_CURVE_TYPE curve, uint8_t *pubkey_x, uint8_t *pubkey_y, uint8_t *msg, uint8_t *sign);

void boot_aes_ctr_decrypt(uint32_t offset, uint32_t length, uint8_t *key, uint8_t *cnt, uint8_t *out);
bool boot_aes_gcm_decrypt(uint32_t offset, uint32_t length,
                          uint8_t *out, uint8_t *key,
                          uint8_t *iv, uint16_t iv_len,
                          uint8_t *tag, uint16_t tag_len);
void boot_sm4_ctr_decrypt(uint32_t offset, uint32_t length, uint8_t *key, uint8_t *cnt, uint8_t *out);
bool boot_sm4_gcm_decrypt(uint32_t offset, uint32_t length,
                          uint8_t *out, uint8_t *key,
                          uint8_t *iv, uint16_t iv_len,
                          uint8_t *tag, uint16_t tag_len);

#define SHAMaxHashSize (0x30)
bool boot_hkdf(enum BOOT_HASH_ALGO hash_algo,
               uint8_t *salt, uint32_t salt_len,
               uint8_t *ikm, uint32_t ikm_len,
               uint8_t *info, uint32_t info_len,
               uint8_t *okm, uint32_t okm_len);
#endif