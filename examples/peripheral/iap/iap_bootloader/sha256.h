#ifndef _SHA256_H
#define _SHA256_H

#include <stdint.h>

#if defined(LE501X)
void sha256_get(uint8_t *data,uint32_t len,uint8_t *hash);
#endif

#endif