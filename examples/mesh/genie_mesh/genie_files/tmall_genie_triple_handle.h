#ifndef __TMALL_GENIE_TRIPLE_HANDLE_H__
#define __TMALL_GENIE_TRIPLE_HANDLE_H__
#include <stdint.h>

#define TRIPLE_PID_LEN 4
#define TRIPLE_MAC_LEN 6
#define TRIPLE_SECRET_LEN 16
#define ALI_AUTH_VALUE_LEN 16
#define ALI_TRIPLE_SUM_LEN (TRIPLE_PID_LEN + TRIPLE_MAC_LEN + TRIPLE_SECRET_LEN)


uint8_t gen_ali_authValue(void);
void ls_uart_init(void);
void hextostring(const uint8_t *source, char *dest, int len);
#endif // __TMALL_GENIE_TRIPLE_HANDLE_H__