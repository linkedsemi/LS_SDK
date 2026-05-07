#ifndef COMMON_H_
#define COMMON_H_
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const unsigned char one_bits[];
/// Number of '1' bits in a byte
#define NB_ONE_BITS(byte)   (one_bits[(byte) & 0x0F] + one_bits[(byte) >> 4])

/// Get the number of elements within an array, give also number of rows in a 2-D array
#define ARRAY_LEN(array)   (sizeof((array))/sizeof((array)[0]))

/// Get the number of columns within a 2-D array
#define ARRAY_NB_COLUMNS(array)  (sizeof((array[0]))/sizeof((array)[0][0]))

/// Macro to get a structure from one of its structure field
#if !defined(KERNEL)
#ifndef CONTAINER_OF
#define CONTAINER_OF(ptr, type, member)    ((type *)( (char *)ptr - offsetof(type,member) ))
#endif
#endif

#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif

#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif

#define CEILING(dividend,divisor) (((dividend) + ((divisor) - 1))/(divisor))

#ifndef __fallthrough
#if __GNUC__ >= 7
#define __fallthrough        __attribute__((fallthrough))
#else
#define __fallthrough
#endif /* __GNUC__ >= 7 */
#endif

/**
 * @brief Check if @p ptr is aligned to @p align alignment
 */
#ifndef IS_ALIGNED
#define IS_ALIGNED(ptr, align) (((uintptr_t)(ptr)) % (align) == 0)
#endif

/**
 * @brief Value of @p x rounded up to the next multiple of @p align.
 */
#ifndef ROUND_UP
#define ROUND_UP(x, align)                                   \
	((((unsigned long)(x) + ((unsigned long)(align) - 1)) / \
	  (unsigned long)(align)) * (unsigned long)(align))
#endif

/**
 * @brief Value of @p x rounded down to the previous multiple of @p align.
 */
#ifndef ROUND_DOWN
#define ROUND_DOWN(x, align)                                 \
	(((unsigned long)(x) / (unsigned long)(align)) * (unsigned long)(align))
#endif

#if !defined(KB)
#ifdef _LINKER
/* This is used in linker scripts so need to avoid type casting there */
#define KB(x) ((x) << 10)
#else
#define KB(x) (((size_t)(x)) << 10)
#endif
#endif

#if !defined(MB)
/** @brief Number of bytes in @p x mebibytes */
#define MB(x) (KB(x) << 10)
#endif

#if !defined(GB)
/** @brief Number of bytes in @p x gibibytes */
#define GB(x) (MB(x) << 10)
#endif

#if !defined(KHZ)
/** @brief Number of Hz in @p x kHz */
#define KHZ(x) ((x) * 1000)
#endif

#if !defined(MHZ)
/** @brief Number of Hz in @p x MHz */
#define MHZ(x) (KHZ(x) * 1000)
#endif

__attribute__((always_inline)) static inline int32_t time_diff(uint32_t time0,uint32_t time1)
{
    int32_t diff = time0 - time1;
    return diff;
}

void *ll_malloc(uint32_t size);

void ll_free(void *data);

void rand_gen_by_word(uint8_t *ptr,uint8_t word_num);

void memcpy32(uint32_t *dest, const uint32_t *src, uint32_t size_word);

void memset32(uint32_t *start,uint32_t data,uint32_t size_word);

uint8_t count_trailing_zeros(uint32_t x);

uint8_t count_leading_zeros(uint32_t x);

uint32_t __div64_32(uint64_t *n, uint32_t base);

void memcpy_rev(uint8_t *dest, const uint8_t *src, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif
