#include "efuse.h"
#include "reg_sysc_awo.h"
#include "field_manipulate.h"
#define RW_MASK 0x1
#define CS_MASK 0x2
#define PGM_MASK 0x4
#define SCLK_MASK 0x8
#define SCLK_CLR() MODIFY_REG(SYSC_AWO->EFUSE_CTRL,SCLK_MASK,0)
#define SCLK_SET() MODIFY_REG(SYSC_AWO->EFUSE_CTRL,0,SCLK_MASK)
#define PGM_CLR() MODIFY_REG(SYSC_AWO->EFUSE_CTRL,PGM_MASK,0)
#define RW_SET() MODIFY_REG(SYSC_AWO->EFUSE_CTRL,0,RW_MASK)
#define RW_CLR() MODIFY_REG(SYSC_AWO->EFUSE_CTRL,RW_MASK,0)
#define CS_CLR() MODIFY_REG(SYSC_AWO->EFUSE_CTRL,CS_MASK,0)
#define CS_SET() MODIFY_REG(SYSC_AWO->EFUSE_CTRL,0,CS_MASK)
#define DOUT_GET() SYSC_AWO->EFUSE_RDATA
void efuse_read(struct efuse_data *data)
{
    SCLK_CLR();
    PGM_CLR();
    RW_CLR();
    CS_SET();
    uint8_t *end = (uint8_t *)&data[1];
    uint8_t *ptr;
    for(ptr = end-1;ptr>=(uint8_t *)data;--ptr)
    {
        uint8_t byte = 0;
        uint8_t i;
        for(i=0;i<8;++i)
        {
            SCLK_SET();
            SCLK_CLR();
            byte |= DOUT_GET()<<(7-i);
        }
        *ptr = byte;
    }
    CS_CLR();
}