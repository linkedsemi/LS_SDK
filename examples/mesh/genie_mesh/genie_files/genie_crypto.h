#ifndef __GENIE_CRYPTO_H__
#define __GENIE_CRYPTO_H__

#define GENIE_CRYPTO_UNIT_SIZE (16)

#define STATIC_OOB_LENGTH 16
#include <stdint.h>
 
/**
 * @brief get the authentication info
 * @param[in] random: the random sequence used for calculating.
 * @return the authenticated sequence
 */
uint8_t *genie_crypto_get_auth(const uint8_t random[16]);

 
void genie_crypto_encrypt(const uint8_t data_in[16], uint8_t data_out[16]);
void genie_ais_get_cipher(const uint8_t random[16], uint8_t *cipher);
void genie_crypto_adv_create(uint8_t ad_structure[14], uint8_t is_silent);
void genie_ais_reset(void);
void genie_crypto_decrypt(const uint8_t data_in[16], uint8_t data_out[16]);


#endif
