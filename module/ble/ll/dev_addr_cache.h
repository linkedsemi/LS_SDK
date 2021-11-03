#ifndef DEV_ADDR_CACHE_H_
#define DEV_ADDR_CACHE_H_
#include <stdarg.h>
#include <stdbool.h>
#include "hci_format.h"
#include "co_list.h"
struct dev_addr_cache
{
    struct co_list_hdr hdr;
    struct ble_dev_addr dev;
};

void dev_addr_cache_data_copy(struct co_list_hdr const *hdr,va_list *args);

bool dev_addr_cache_data_compare(struct co_list_hdr const *hdr,va_list *args);

#endif
