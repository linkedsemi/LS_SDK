#ifndef LS_HAL_SM4_H_
#define LS_HAL_SM4_H_
#include <stdbool.h>
#include <stdint.h>
#include "HAL_def.h"

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

#endif