#ifndef PER_ADV_LIST_H_
#define PER_ADV_LIST_H_
#include <stdint.h>
#include <stdbool.h>
#include "hci_format.h"
#include "co_list.h"
struct per_adv_list_env
{
    struct co_list_hdr hdr;
    struct bd_addr addr;
    uint8_t addr_type;
    uint8_t sid;
};

extern uint8_t per_adv_list_size;

void per_adv_list_clear(void);

bool per_adv_list_remove(uint8_t addr_type,struct bd_addr *addr,uint8_t sid);

struct per_adv_list_env *per_adv_list_search(uint8_t addr_type,struct bd_addr *addr,uint8_t sid);

bool per_adv_list_add(uint8_t addr_type,struct bd_addr *addr,uint8_t sid);


#endif

