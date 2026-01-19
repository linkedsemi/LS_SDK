#ifndef LS_OTBN_RSA_H_
#define LS_OTBN_RSA_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#define MODE_RSA_2048_MODEXP      0x76b
#define MODE_RSA_2048_MODEXP_F4   0x565
#define MODE_RSA_3072_MODEXP      0x378
#define MODE_RSA_3072_MODEXP_F4   0x6d1
#define MODE_RSA_4096_MODEXP      0x70b
#define MODE_RSA_4096_MODEXP_F4   0x0ee

#define RSA_OFFSET_N              0x00000020
#define RSA_OFFSET_MODE           0x00000000
#define RSA_OFFSET_D              0x00000220
#define RSA_OFFSET_INOUT          0x00000420

#define RSA_IMEM_SIZE             1592
#define RSA_DMEM_SIZE             0

extern const uint8_t rsa_imem[1592];
// extern const uint8_t rsa_dmem[];

enum {
  /* Length of the RSA-2048 modulus and private exponent in bits. */
  kRsa2048NumBits = 2048,
  /* Length of the RSA-2048 modulus in bytes */
  kRsa2048NumBytes = kRsa2048NumBits / 8,
  /* Length of the RSA-2048 modulus in words */
  kRsa2048NumWords = kRsa2048NumBytes / sizeof(uint32_t),
  /* Length of the RSA-3072 modulus and private exponent in bits. */
  kRsa3072NumBits = 3072,
  /* Length of the RSA-3072 modulus in bytes */
  kRsa3072NumBytes = kRsa3072NumBits / 8,
  /* Length of the RSA-3072 modulus in words */
  kRsa3072NumWords = kRsa3072NumBytes / sizeof(uint32_t),
  /* Length of the RSA-4096 modulus and private exponent in bits. */
  kRsa4096NumBits = 4096,
  /* Length of the RSA-4096 modulus in bytes */
  kRsa4096NumBytes = kRsa4096NumBits / 8,
  /* Length of the RSA-4096 modulus in words */
  kRsa4096NumWords = kRsa4096NumBytes / sizeof(uint32_t),
};

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif
