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

/** \brief SM4 CTR encrypt/decrypt (one-shot, symmetric operation)
 *  \param[in] cnt Initial counter block (16 bytes), updated in place
 *  \param[in] in Input data
 *  \param[in] in_len Data length in bytes
 *  \param[out] out Output data
 *  \return HAL_OK on success, HAL_INVALIAD_PARAM on a NULL pointer argument
 */
HAL_StatusTypeDef HAL_SM4_CTR_Crypt(uint8_t cnt[0x10], const uint8_t *in, uint32_t in_len, uint8_t *out);


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

/* GCM authenticated decryption reports HAL_StatusTypeDef like the rest of
 * SM4: HAL_OK = authentication tag verified (plaintext valid);
 * HAL_ERROR = tag mismatch (plaintext NOT authentic, discard it);
 * HAL_INVALIAD_PARAM = bad pointer/size.  Only Final and the one-shot
 * report the tag result; Init/Update report HAL_OK unless a parameter is
 * invalid. */

/** \brief SM4 GCM Decrypt Initialize
 *  \param[in] gcm GCM context (zeroed on success)
 *  \param[in] nonce Initial vector
 *  \param[in] nonce_size Nonce length in bytes
 *  \return HAL_OK, or HAL_INVALIAD_PARAM on NULL gcm/nonce or bad nonce_size
 */
HAL_StatusTypeDef HAL_SM4_GCM_Decrypt_Init(sm4_gcm_env *gcm, uint8_t *nonce, uint32_t nonce_size);

/** \brief SM4 GCM Decrypt Update (streaming)
 *  \param[in] gcm GCM context
 *  \param[out] out Plaintext output
 *  \param[in] in Ciphertext input
 *  \param[in] in_size Ciphertext length in bytes
 *  \param[in] aad Additional authenticated data
 *  \param[in] aad_size AAD length in bytes
 *  \return HAL_OK, or HAL_INVALIAD_PARAM on NULL gcm or bad in/out/aad
 */
HAL_StatusTypeDef HAL_SM4_GCM_Decrypt_Update(sm4_gcm_env *gcm, uint8_t *out,
                                        uint8_t *in, uint32_t in_size,
                                        uint8_t *aad, uint32_t aad_size);

/** \brief SM4 GCM Decrypt Final: verify the authentication tag
 *  \param[in] gcm GCM context
 *  \param[in] tag Expected authentication tag
 *  \param[in] tag_size Tag length in bytes
 *  \return HAL_OK if the tag matches (plaintext authentic), HAL_ERROR on
 *          tag mismatch, HAL_INVALIAD_PARAM on NULL gcm/tag
 */
HAL_StatusTypeDef HAL_SM4_GCM_Decrypt_Final(sm4_gcm_env *gcm, uint8_t *tag, uint32_t tag_size);

/** \brief SM4 GCM Decrypt (one-shot)
 *  \param[in] in Ciphertext input
 *  \param[in] in_size Ciphertext length in bytes
 *  \param[in] nonce Initial vector
 *  \param[in] nonce_size Nonce length in bytes
 *  \param[in] tag Expected authentication tag
 *  \param[in] tag_size Tag length in bytes
 *  \param[in] aad Additional authenticated data
 *  \param[in] aad_size AAD length in bytes
 *  \param[out] out Plaintext output (valid only when the return is HAL_OK)
 *  \return HAL_OK if the tag matches, HAL_ERROR on tag mismatch,
 *          HAL_INVALIAD_PARAM on bad pointer/size
 */
HAL_StatusTypeDef HAL_SM4_GCM_Decrypt(uint8_t *in, uint32_t in_size,
                                              uint8_t *nonce, uint32_t nonce_size,
                                              uint8_t *tag, uint32_t tag_size,
                                              uint8_t *aad, uint32_t aad_size,
                                              uint8_t *out);
                 
#ifdef __cplusplus
}
#endif

#endif