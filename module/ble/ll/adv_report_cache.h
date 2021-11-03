#ifndef ADV_REPORT_CACHE_H_
#define ADV_REPORT_CACHE_H_
#include <stdbool.h>
#include <stdint.h>
#include "ll_evt.h"

struct adv_report_cache
{
    struct co_list_hdr hdr;
    struct ble_dev_addr dev;
    struct ADI_field adi;
    bool adi_present;
};

void adv_report_cache_add(uint8_t addr_type,uint8_t *addr,struct ADI_field *ADI);

bool adv_report_cache_search(uint8_t addr_type,uint8_t *addr,struct ADI_field *ADI);

bool adv_report_cache_remove(uint8_t addr_type,uint8_t *addr,struct ADI_field *ADI);

bool adv_report_cache_full(void);

void adv_report_cache_clean_up(void);

#endif
