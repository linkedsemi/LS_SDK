#ifndef INFLASH_SETTINGS_H_
#define INFLASH_SETTINGS_H_
#include <stdint.h>
#include <stdbool.h>
struct setting_info
{
    uint32_t start;
    uint16_t range;
    uint8_t size_by_word;
};

void settings_set(const struct setting_info *info,uint32_t *data);

bool settings_get(const struct setting_info *info,uint32_t *data,uint32_t *valid_offset);

void settings_make_invalid(const struct setting_info *info);
#endif
