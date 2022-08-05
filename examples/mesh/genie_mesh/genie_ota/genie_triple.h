/*
 * Copyright (C) 2018-2020 Alibaba Group Holding Limited
 */

#ifndef __GENIE_TRIPLE_H__
#define __GENIE_TRIPLE_H__
#include <stdint.h>

#define GENIE_TRIPLE_PID_SIZE 4
#define GENIE_TRIPLE_KEY_SIZE 16
#define GENIE_TRIPLE_MAC_SIZE 6
#define GENIE_SIZE_TRI_TRUPLE (GENIE_TRIPLE_PID_SIZE + GENIE_TRIPLE_MAC_SIZE+ GENIE_TRIPLE_KEY_SIZE)

typedef struct _genie_triple_s
{
    uint32_t pid;
    uint8_t key[GENIE_TRIPLE_KEY_SIZE];
    uint8_t mac[GENIE_TRIPLE_MAC_SIZE];
} genie_triple_t;


void genie_triple_init(void);

genie_triple_t *genie_triple_get(void);

uint8_t *genie_triple_get_mac(void);

#endif
