#ifndef LS_HAL_OTBN_SHA256_H_
#define LS_HAL_OTBN_SHA256_H_
#include "ls_hal_otbn.h"
#ifdef __cplusplus
extern "C" {
#endif

#define SHA256_RESULT_SIZE          (0x20)
#define SHA384_RESULT_SIZE          (0x30)
#define SHA256_TEXT_LENTH           (540)
#define SHA384_TEXT_LENTH           (1588)
extern const char sha256_text[SHA256_TEXT_LENTH];
extern const char sha384_text[SHA384_TEXT_LENTH];

void HAL_OTBN_SHA256_Init();
void HAL_OTBN_SHA256_Update(uint8_t *msg, uint32_t length);
void HAL_OTBN_SHA256_Final(uint8_t result[SHA256_RESULT_SIZE]);

void HAL_OTBN_SHA384_Init();
void HAL_OTBN_SHA384_Update(uint8_t *msg, uint32_t length);
void HAL_OTBN_SHA384_Final(uint8_t result[SHA384_RESULT_SIZE]);



#ifdef __cplusplus
}
#endif
#endif