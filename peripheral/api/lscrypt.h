#ifndef LSCRYPT_H_
#define LSCRYPT_H_
#include <stdbool.h>
#include <stdint.h>
#include "HAL_def.h"
#include "reg_base_addr.h"
#include "reg_lscrypt_type.h"

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSCRYPT
 *  @{
 */

#ifdef LSCRYPT_BASE_ADDR
/// LSCRYPT Macro for Register Access
#define LSCRYPT ((reg_crypt_t *)LSCRYPT_BASE_ADDR)
#endif

/// AES Key Size
enum aes_key_type
{
    AES_KEY_128 = 0,
    AES_KEY_192,
    AES_KEY_256,
};

/** \brief LSCRYPT Initialize 
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_Init(void);

/** \brief LSCRYPT De-Initialize
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_DeInit(void);

/** \brief LSCRYPT AES Key Config 
 *  \param[in] key Buffer pointer containing the key, must be 4 bytes aligned
 *  \param[in] key_size Key Size
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_AES_Key_Config(const uint32_t *key,enum aes_key_type key_size);

/** \brief LSCRYPT AES ECB Encrypt (Block Mode)
 *  \param[in] plaintext Input data
 *  \param[in] length Input data Length
 *  \param[out] ciphertext Output data
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Encrypt(const uint8_t *plaintext,uint32_t length,uint8_t *ciphertext);

/** \brief LSCRYPT AES ECB Decrypt (Block Mode)
 *  \param[in] ciphertext Input data
 *  \param[in] length Input data Length
 *  \param[out] plaintext Output data
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Decrypt(const uint8_t *ciphertext,uint32_t length,uint8_t *plaintext);

/** \brief LSCRYPT AES CBC Encrypt (Block Mode)
 *  \param[in] iv Initial vector
 *  \param[in] plaintext Input data
 *  \param[in] length Input data Length
 *  \param[out] ciphertext Output data
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Encrypt(const uint32_t iv[4],const uint8_t *plaintext,uint32_t length,uint8_t *ciphertext);

/** \brief LSCRYPT AES CBC Decrypt (Block Mode)
 *  \param[in] iv Initial vector
 *  \param[in] ciphertext Input data
 *  \param[in] length Input data Length
 *  \param[out] plaintext Output data
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Decrypt(const uint32_t iv[4],const uint8_t *ciphertext,uint32_t length,uint8_t *plaintext);

/** \brief LSCRYPT AES ECB Encrypt (Interrupt Mode)
 *  \param[in] plaintext Input data
 *  \param[in] length Input data Length
 *  \param[out] ciphertext Output data
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Encrypt_IT(const uint8_t *plaintext,uint32_t length,uint8_t *ciphertext);

/** \brief LSCRYPT AES ECB Decrypt (Interrupt Mode)
 *  \param[in] ciphertext Input data
 *  \param[in] length Input data Length
 *  \param[out] plaintext Output data
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Decrypt_IT(const uint8_t *ciphertext,uint32_t length,uint8_t *plaintext);

/** \brief LSCRYPT AES CBC Encrypt (Interrupt Mode)
 *  \param[in] iv Initial vector
 *  \param[in] plaintext Input data
 *  \param[in] length Input data Length
 *  \param[out] ciphertext Output data
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Encrypt_IT(const uint32_t iv[4],const uint8_t *plaintext,uint32_t length,uint8_t *ciphertext);

/** \brief LSCRYPT AES CBC Decrypt (Interrupt Mode)
 *  \param[in] iv Initial vector
 *  \param[in] ciphertext Input data
 *  \param[in] length Input data Length
 *  \param[out] plaintext Output data
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Decrypt_IT(const uint32_t iv[4],const uint8_t *ciphertext,uint32_t length,uint8_t *plaintext);

/** Callback function that will be invoked in the interrupt context when AES operation is complete.
 *  Overwrite this function to get notification of completion of AES operation.
 *  \param Encrypt the complete operation is Encryption if ture else Decryption
 *  \param CBC the block cipher mode of the complete operation is CBC if true else ECB
 */
void HAL_LSCRYPT_AES_Complete_Callback(bool Encrypt,bool CBC);

void HAL_LSCRYPT_IRQHandler(void);

/** @}*/

/** @}*/

#endif
