#ifndef LS_HAL_CRYPT_H_
#define LS_HAL_CRYPT_H_
#include <stdbool.h>
#include <stdint.h>
#include "HAL_def.h"
#include "ls_msp_crypt.h"

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSCRYPT
 *  @{
 */
/// crypt mode select
enum crypt_mode
{
    AES_MODE = 0,
    DES_MODE,
};

/// encryption and decryption mode select
enum crypt_type
{
    ENCRYPT = 0,
    DECRYPT,
};

/// AES Key Size
enum aes_key_type
{
    AES_KEY_128 = 0,
    AES_KEY_192,
    AES_KEY_256,
};

/// TDES Key Size
enum tdes_key_type
{
    TDES_KEY_128 = 0,
    TDES_KEY_192,
    DES_KEY_64,
};

/// Padding mode
// https://asecuritysite.com/encryption/go_pad
// https://en.wikipedia.org/wiki/Padding_(cryptography)
enum padding_mode
{
    Padding_None,
    Padding_PKCS7,
    Padding_ANSIX923,
    Padding_ISO7816,
    Padding_ISO10126,
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

/** \brief LSCRYPT Block Padding Mode Set
 *  \param[in] mode @ref padding_mode
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_Block_Padding_Mode_Set(enum padding_mode mode);

/** \brief LSCRYPT AES ECB Encrypt (Block Mode)
 *  \param[in] plaintext Input data
 *  \param[in] plaintextlength Input data Length
 *  \param[out] ciphertext Output data
 *  \param[inout] ciphertextlength in: Size of the ciphertext buffer; out: Output data Length
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Encrypt(const uint8_t *plaintext,uint32_t plaintextlength,uint8_t *ciphertext,uint32_t *ciphertextlength);

/** \brief LSCRYPT AES ECB Decrypt (Block Mode)
 *  \param[in] ciphertext Input data
 *  \param[in] ciphertextlength Input data Length
 *  \param[out] plaintext Output data
 *  \param[inout] plaintextlength in: Size of the plaintext buffer; out: Output data Length
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Decrypt(const uint8_t *ciphertext,uint32_t ciphertextlength,uint8_t *plaintext,uint32_t *plaintextlength);

/** \brief LSCRYPT AES CBC Encrypt (Block Mode)
 *  \param[in] iv Initial vector
 *  \param[in] plaintext Input data
 *  \param[in] plaintextlength Input data Length
 *  \param[out] ciphertext Output data
 *  \param[inout] ciphertextlength in: Size of the ciphertext buffer; out: Output data Length
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Encrypt(const uint32_t iv[4],const uint8_t *plaintext,uint32_t plaintextlength,uint8_t *ciphertext,uint32_t *ciphertextlength);

/** \brief LSCRYPT AES CBC Decrypt (Block Mode)
 *  \param[in] iv Initial vector
 *  \param[in] ciphertext Input data
 *  \param[in] ciphertextlength Input data Length
 *  \param[out] plaintext Output data
 *  \param[inout] plaintextlength in: Size of the plaintext buffer; out: Output data Length
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Decrypt(const uint32_t iv[4],const uint8_t *ciphertext,uint32_t ciphertextlength,uint8_t *plaintext,uint32_t *plaintextlength);

/** \brief LSCRYPT AES ECB Encrypt (Interrupt Mode)
 *  \param[in] plaintext Input data
 *  \param[in] plaintextlength Input data Length
 *  \param[out] ciphertext Output data
 *  \param[in] ciphertextlength Size of the ciphertext buffer
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Encrypt_IT(const uint8_t *plaintext,uint32_t plaintextlength,uint8_t *ciphertext,uint32_t ciphertextlength);

/** \brief LSCRYPT AES ECB Decrypt (Interrupt Mode)
 *  \param[in] ciphertext Input data
 *  \param[in] ciphertextlength Input data Length
 *  \param[out] plaintext Output data
 *  \param[in] plaintextlength Size of the plaintext buffer
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Decrypt_IT(const uint8_t *ciphertext,uint32_t ciphertextlength,uint8_t *plaintext,uint32_t plaintextlength);

/** \brief LSCRYPT AES CBC Encrypt (Interrupt Mode)
 *  \param[in] iv Initial vector
 *  \param[in] plaintext Input data
 *  \param[in] plaintextlength Input data Length
 *  \param[out] ciphertext Output data
 *  \param[in] ciphertextlength Size of the ciphertext buffer
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Encrypt_IT(const uint32_t iv[4],const uint8_t *plaintext,uint32_t plaintextlength,uint8_t *ciphertext,uint32_t ciphertextlength);

/** \brief LSCRYPT AES CBC Decrypt (Interrupt Mode)
 *  \param[in] iv Initial vector
 *  \param[in] ciphertext Input data
 *  \param[in] ciphertextlength Input data Length
 *  \param[out] plaintext Output data
 *  \param[in] plaintextlength Size of the plaintext buffer
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Decrypt_IT(const uint32_t iv[4],const uint8_t *ciphertext,uint32_t ciphertextlength,uint8_t *plaintext,uint32_t plaintextlength);

/** \brief LSCRYPT DES Key Config 
 *  \param[in] key Buffer pointer containing the key, must be 4 bytes aligned
 *  \param key_size Select key size
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_DES_Key_Config(const uint32_t *key,enum tdes_key_type key_size);

/** \brief LSCRYPT DES ECB Encrypt (Block Mode)
 *  \param[in] plaintext Input data
 *  \param[in] plaintextlength Input data Length
 *  \param[out] ciphertext Output data
 *  \param[inout] ciphertextlength in: Size of the ciphertext buffer; out: Output data Length
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_DES_ECB_Encrypt(const uint8_t *plaintext,uint32_t plaintextlength,uint8_t *ciphertext,uint32_t *ciphertextlength);

/** \brief LSCRYPT DES ECB Decrypt (Block Mode)
 *  \param[in] ciphertext Input data
 *  \param[in] ciphertextlength Input data Length
 *  \param[out] plaintext Output data
 *  \param[inout] plaintextlength in: Size of the plaintext buffer; out: Output data Length
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_DES_ECB_Decrypt(const uint8_t *ciphertext,uint32_t ciphertextlength,uint8_t *plaintext,uint32_t *plaintextlength);

/** \brief LSCRYPT DES CBC Encrypt (Block Mode)
 *  \param[in] iv Initial vector
 *  \param[in] plaintext Input data
 *  \param[in] plaintextlength Input data Length
 *  \param[out] ciphertext Output data
 *  \param[inout] ciphertextlength in: Size of the ciphertext buffer; out: Output data Length
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_DES_CBC_Encrypt(const uint32_t iv[4],const uint8_t *plaintext,uint32_t plaintextlength,uint8_t *ciphertext,uint32_t *ciphertextlength);

/** \brief LSCRYPT DES CBC Decrypt (Block Mode)
 *  \param[in] iv Initial vector
 *  \param[in] ciphertext Input data
 *  \param[in] ciphertextlength Input data Length
 *  \param[out] plaintext Output data
 *  \param[inout] plaintextlength in: Size of the plaintext buffer; out: Output data Length
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_DES_CBC_Decrypt(const uint32_t iv[4],const uint8_t *ciphertext,uint32_t ciphertextlength,uint8_t *plaintext,uint32_t *plaintextlength);

/** \brief LSCRYPT DES ECB Encrypt (Interrupt Mode)
 *  \param[in] plaintext Input data
 *  \param[in] plaintextlength Input data Length
 *  \param[out] ciphertext Output data
 *  \param[in] ciphertextlength Size of the ciphertext buffer
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_DES_ECB_Encrypt_IT(const uint8_t *plaintext,uint32_t plaintextlength,uint8_t *ciphertext,uint32_t ciphertextlength);

/** \brief LSCRYPT DES ECB Decrypt (Interrupt Mode)
 *  \param[in] ciphertext Input data
 *  \param[in] ciphertextlength Input data Length
 *  \param[out] plaintext Output data
 *  \param[in] plaintextlength Size of the plaintext buffer
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_DES_ECB_Decrypt_IT(const uint8_t *ciphertext,uint32_t ciphertextlength,uint8_t *plaintext,uint32_t plaintextlength);

/** \brief LSCRYPT DES CBC Encrypt (Interrupt Mode)
 *  \param[in] iv Initial vector
 *  \param[in] plaintext Input data
 *  \param[in] plaintextlength Input data Length
 *  \param[out] ciphertext Output data
 *  \param[in] ciphertextlength Size of the ciphertext buffer
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_DES_CBC_Encrypt_IT(const uint32_t iv[4],const uint8_t *plaintext,uint32_t plaintextlength,uint8_t *ciphertext,uint32_t ciphertextlength);

/** \brief LSCRYPT DES CBC Decrypt (Interrupt Mode)
 *  \param[in] iv Initial vector
 *  \param[in] ciphertext Input data
 *  \param[in] ciphertextlength Input data Length
 *  \param[out] plaintext Output data
 *  \param[in] plaintextlength Size of the plaintext buffer
 *  \return status 
 */
HAL_StatusTypeDef HAL_LSCRYPT_DES_CBC_Decrypt_IT(const uint32_t iv[4],const uint8_t *ciphertext,uint32_t ciphertextlength,uint8_t *plaintext,uint32_t plaintextlength);

/** Callback function that will be invoked in the interrupt context when AES operation is complete.
 *  Overwrite this function to get notification of completion of AES operation.
 *  \param Encrypt the complete operation is Encryption if ture else Decryption
 *  \param CBC the block cipher mode of the complete operation is CBC if true else ECB
 *  \param length Output data length of the operation
 */
void HAL_LSCRYPT_AES_Complete_Callback(bool Encrypt,bool CBC,uint32_t length);

/** Callback function that will be invoked in the interrupt context when DES operation is complete.
 *  Overwrite this function to get notification of completion of DES operation.
 *  \param Encrypt the complete operation is Encryption if ture else Decryption
 *  \param CBC the block cipher mode of the complete operation is CBC if true else ECB
 *  \param length Output data length of the operation
 */
void HAL_LSCRYPT_DES_Complete_Callback(bool Encrypt,bool CBC,uint32_t length);

void HAL_LSCRYPT_IRQHandler(void);

/** @}*/

/** @}*/

#endif
