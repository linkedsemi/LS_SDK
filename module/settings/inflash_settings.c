#include "inflash_settings.h"
#include "ls_hal_flash.h"
#include "common.h"
#include "ls_dbg.h"
#define NOT_PROGRAMMED_DATA 0xffffffff

static void invalid_flag_write(uint32_t offset)
{
    uint8_t flag[4] = {'I','N','V','A'};
    hal_flash_multi_io_page_program(offset,flag,sizeof(flag));
}

static void inversion_data_write(uint32_t offset,uint32_t *data,uint8_t size_by_word)
{
    uint32_t buf[size_by_word*2];
    memcpy32(buf,data,size_by_word);
    uint8_t i;
    for(i=0;i<size_by_word;++i)
    {
        buf[size_by_word + i] = ~data[i];
    }
    hal_flash_multi_io_page_program(offset,(uint8_t *)buf,sizeof(buf));
}

static bool inversion_data_check(uint32_t *data,uint8_t size_by_word)
{
    uint8_t i;
    for(i=0;i<size_by_word;++i)
    {
        if(data[size_by_word+i] != ~data[i])
        {
            return false;
        }
    }
    return true;
}

static bool not_programmed(uint32_t *data,uint8_t size_by_word)
{
    while(size_by_word--)
    {
        if(data[size_by_word]!=NOT_PROGRAMMED_DATA)
        {
            return false;
        }
    }
    return true;
}

static bool _settings_get(const struct setting_info *info,uint32_t *buf,uint16_t buf_size,uint32_t *valid_offset)
{
    uint32_t offset = info->start;
    while(offset<info->start+info->range)
    {
        *valid_offset = offset;
        hal_flash_multi_io_read(offset,(uint8_t *)buf,buf_size);
        offset += buf_size;
        uint32_t flag;
        hal_flash_multi_io_read(offset,(uint8_t *)&flag,sizeof(uint32_t));
        offset += sizeof(uint32_t);
        if(flag == NOT_PROGRAMMED_DATA)
        {
            if(not_programmed(buf,info->size_by_word*2))
            {
                return false;
            }else if(inversion_data_check(buf,info->size_by_word))
            {
                return true;
            }
        }
    }
    *valid_offset = 0;
    return false;
}

bool settings_get(const struct setting_info *info,uint32_t *data,uint32_t *valid_offset)
{
    uint32_t buf[info->size_by_word*2];
    if(_settings_get(info,buf,sizeof(buf),valid_offset))
    {
        memcpy32(data,buf,info->size_by_word);
        return true;
    }else
    {
        return false;
    }
}

void settings_make_invalid(const struct setting_info *info)
{
    uint32_t buf[info->size_by_word*2];
    uint32_t offset;
    if(_settings_get(info,buf,sizeof(buf),&offset))
    {
        invalid_flag_write(offset+sizeof(buf));
    }
}

void settings_set(const struct setting_info *info,uint32_t *data)
{
    uint32_t offset;
    uint32_t buf[info->size_by_word*2];
    if(_settings_get(info,buf,sizeof(buf),&offset))
    {
        invalid_flag_write(offset+sizeof(uint32_t)*info->size_by_word*2);
        offset += sizeof(uint32_t)*info->size_by_word*2 + sizeof(uint32_t);
    }
    LS_ASSERT(offset);
    inversion_data_write(offset,data,info->size_by_word);
}
