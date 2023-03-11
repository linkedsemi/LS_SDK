#ifndef TINYFS_NVM_H_
#define TINYFS_NVM_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void (*const nvm_program)(uint32_t,uint8_t *,uint16_t);
extern void (*const nvm_read)(uint32_t, uint8_t *, uint16_t);
extern void (*const nvm_sector_ease)(uint32_t);

#ifdef __cplusplus
}
#endif

#endif
