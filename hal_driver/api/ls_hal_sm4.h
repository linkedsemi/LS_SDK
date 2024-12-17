#ifndef LS_HAL_SM4_H_
#define LS_HAL_SM4_H_
#include <stdbool.h>
#include <stdint.h>
#include "HAL_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief LSSM4 Initialize 
 * 
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_SM4_Init(void);

/**
 * @brief LSSM4 De-Initialize
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_SM4_DeInit(void);

/**
 * @brief LSSM4 KeyExpansion
 * 
 * @param key Buffer pointer containing the key, the bufferSize must be 16.
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_SM4_KeyExpansion(const uint8_t *key);

/**
 * @brief LSSM4 KeyExpansion (Interrupt Mode)
 * 
 * @param key Buffer pointer containing the key, must be 16 bytes aligned.
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_SM4_KeyExpansion_IT(const uint8_t *key);

/**
 * @brief LSSM4 Encrypt
 * 
 * @param data Intput data
 * @param result Output data
 * @param length the length of Intput data，Must be 16 byte aligned
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_SM4_Encrypt(const uint8_t *data,uint8_t *result,uint32_t length);

/**
 * @brief LSSM4 Decrypt
 * 
 * @param data Intput data
 * @param result Output data
 * @param length the length of Intput data，Must be 16 byte aligned
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_SM4_Decrypt(const uint8_t *data, uint8_t *result, uint32_t length);

/**
 * @brief LSSM4 Encrypt (Interrupt Mode)
 * 
 * @param data Intput data
 * @param result Output data
 * @param length the length of Intput data，Must be 16 byte aligned
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_SM4_Encrypt_IT(const uint8_t *data,uint8_t *result,uint32_t length);

/**
 * @brief LSSM4 Decrypt (Interrupt Mode)
 * 
 * @param data Intput data
 * @param result Output data
 * @param length the length of Intput data，Must be 16 byte aligned
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_SM4_Decrypt_IT(const uint8_t *data,uint8_t *result,uint32_t length);

/**
 * @brief Callback function that will be invoked in the interrupt context when SM4 calculate is complete.
 *        Overwrite this function to get notification of completion of SM4 calculate.
 */
void HAL_SM4_Calculation_Complete_Callback(bool Encrypt);

/**
 * @brief  Callback function that will be invoked in the interrupt context when KeyExpansion is complete.
 *         Overwrite this function to get notification of completion of KeyExpansion.
 */
void HAL_SM4_KeyExpansion_Complete_Callback();

void HAL_SM4_IRQHandler(void);

void HAL_SM4_CTR_Crypt(uint8_t cnt[0x10], const uint8_t *in, uint32_t in_len, uint8_t *out);


typedef struct 
{
    uint8_t counter[0x10];
    uint8_t h[0x10];
    uint8_t prime[0x10];
    uint8_t j0[0x10];
    uint64_t big_h[2];
    uint64_t x[2];
    uint32_t counter_size;
    uint32_t data_size;
    uint32_t aad_size;
} sm4_gcm_env;

void HAL_SM4_GCM_Decrypt_Init(sm4_gcm_env *gcm, uint8_t *nonce, uint32_t nonce_size);
void HAL_SM4_GCM_Decrypt_Update(sm4_gcm_env *gcm, uint8_t *out,
                                        uint8_t *in, uint32_t in_size,
                                        uint8_t *aad, uint32_t aad_size);
bool HAL_SM4_GCM_Decrypt_Final(sm4_gcm_env *gcm, uint8_t *tag, uint32_t tag_size);

bool HAL_SM4_GCM_Decrypt(uint8_t *in, uint32_t in_size,
                                              uint8_t *nonce, uint32_t nonce_size,
                                              uint8_t *tag, uint32_t tag_size,
                                              uint8_t *aad, uint32_t aad_size,
                                              uint8_t *out);
                 
#ifdef __cplusplus
}
#endif

#endif