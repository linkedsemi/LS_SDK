#ifndef __SERIAL_SEMIHOSTING_H__
#define __SERIAL_SEMIHOSTING_H__

#include "sdk_config.h"
#include <stdlib.h>
#include <stdbool.h>

#define asm __asm

#define SBI_ENODEV		-1000
#define SBI_ENOSYS		-1001
#define SBI_ETIMEDOUT	-1002
#define SBI_EIO			-1003
#define SBI_EILL		-1004
#define SBI_ENOSPC		-1005
#define SBI_ENOMEM		-1006
#define SBI_EUNKNOWN	-1007
#define SBI_ENOENT		-1008

/**
 * enum semihosting_open_mode - Numeric file modes for use with semihosting_open()
 * MODE_READ: 'r'
 * MODE_BINARY: 'b'
 * MODE_PLUS: '+'
 * MODE_WRITE: 'w'
 * MODE_APPEND: 'a'
 *
 * These modes represent the mode string used by fopen(3) in a form which can
 * be passed to semihosting_open(). These do NOT correspond directly to %O_RDONLY,
 * %O_CREAT, etc; see fopen(3) for details. In particular, @MODE_PLUS
 * effectively results in adding %O_RDWR, and @MODE_WRITE will add %O_TRUNC.
 * For compatibility, @MODE_BINARY should be added when opening non-text files
 * (such as images).
 */
enum semihosting_open_mode {
	MODE_READ	= 0x0,
	MODE_BINARY	= 0x1,
	MODE_PLUS	= 0x2,
	MODE_WRITE	= 0x4,
	MODE_APPEND	= 0x8,
};

void semihosting_init(void);
bool semihosting_enabled(void);
unsigned long semihosting_puts(const char *str, unsigned long len);
bool get_semihosting_state();

#endif
