/*
 * Copyright (C) 2018-2020 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "genie_triple.h"

#define TMALL_TRITUPLE_FLASH_OFFSET (0x0200)

static genie_triple_t genie_triple;
extern uint32_t ali_pid_u32;
extern uint8_t ali_mac[6];
extern uint8_t ali_secret[16];

void genie_triple_read(uint32_t *p_pid, uint8_t *p_mac, uint8_t *p_key)
{
    uint8_t tmp_mac[GENIE_TRIPLE_MAC_SIZE]={0};

  for(uint8_t i=0;i<GENIE_TRIPLE_MAC_SIZE;i++)
   {
      tmp_mac[i]= ali_mac[GENIE_TRIPLE_MAC_SIZE-i-1]; 
   }

	//PIDС��ģʽ
	memcpy(p_pid, (uint8_t*)&ali_pid_u32, GENIE_TRIPLE_PID_SIZE);
	memcpy(p_mac, tmp_mac, GENIE_TRIPLE_MAC_SIZE);
	memcpy(p_key, ali_secret, GENIE_TRIPLE_KEY_SIZE);

}

void genie_triple_init(void)
{
    memset(&genie_triple, 0, sizeof(genie_triple_t));
    genie_triple_read(&genie_triple.pid, genie_triple.mac, genie_triple.key);
}


genie_triple_t *genie_triple_get(void)
{
    return &genie_triple;
}

uint8_t *genie_triple_get_mac(void)
{
    return genie_triple.mac;
}

