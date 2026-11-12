#ifndef _IOPMP_H
#define _IOPMP_H

#include <stdint.h>
#include <stdbool.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IOPMP_MD_CFG      0x00
#define IOPMP_CFG0        0x04
#define IOPMP_CFG1        0x08
#define IOPMP_CFG2        0x0C
#define IOPMP_CFG3        0x10
#define IOPMP_ADDR0       0x14
#define IOPMP_ADDR1       0x18
#define IOPMP_ADDR2       0x1C
#define IOPMP_ADDR3       0x20
#define IOPMP_ADDR4       0x24
#define IOPMP_ADDR5       0x28
#define IOPMP_ADDR6       0x2C
#define IOPMP_ADDR7       0x30
#define IOPMP_INTR_CLR    0x34

#define IOPMP_MODE_NONE   0x0
#define IOPMP_MODE_TOR    0x1
#define IOPMP_MODE_NA4    0x2
#define IOPMP_MODE_NAPOT  0x3

#define PMPCFG_STRIDE sizeof(unsigned long)
#define PMPCFG_SLOTS  8

typedef union {
    uint32_t value;
    struct {
        uint32_t
          MD_EN    :1, /* [0] */
          IOPMP_EN :1, /* [1] */
          INTR_REG :1; /* [4] */
    };
} md_cfg_t;

typedef union {
    uint8_t value;
    struct {
        uint8_t
          COMP_READ      :1, /* [0] */
          COMP_WRITE     :1, /* [1] */
          COMP_EXCUT     :1, /* [2] */
          COMP_ADDR_MODE :2, /* [4:3] */
          COMP_LOCK      :1; /* [7] */
    };
} iopmp_cfg_attr_t;

typedef union {
    uint32_t value;
    struct {
        iopmp_cfg_attr_t arr[PMPCFG_STRIDE];
    };
} iopmp_cfg_t;

inline static uint32_t addr2napot(uint32_t addr, uint64_t size)
{
    return (addr >> 2) | ((size - 1) >> 3);
}

inline static uint32_t napot_reg2size(uint32_t reg)
{
    uint32_t mask = ((reg ^ (reg + 1)) >> 1);
    return ((mask << 3) | 0x7) + 1;
}

inline static uint32_t napot_reg2addr(uint32_t reg)
{
    uint32_t mask = ((reg ^ (reg + 1)) >> 1);
    return (reg & ~mask) << 2;
}

inline static uint32_t napot_reg2addr_size(uint32_t reg, uint32_t *addr, uint32_t *size)
{
    uint32_t mask = ((reg ^ (reg + 1)) >> 1);
    *addr = (reg & ~mask) << 2;
    *size = ((mask << 3) | 0x7) + 1;
    return 0;
}

inline static void iopmp_config_enable(uint32_t dev, bool enable)
{
    md_cfg_t md_cfg;
    md_cfg.IOPMP_EN = 1;
    md_cfg.MD_EN = 1;
    *(volatile uint32_t *)(dev + IOPMP_MD_CFG) = md_cfg.value;
}

inline static bool iopmp_is_enable(uint32_t dev)
{
    md_cfg_t md_cfg;
    md_cfg.value = *(volatile uint32_t *)(dev + IOPMP_MD_CFG);
    return md_cfg.IOPMP_EN;
}

inline static void iopmp_set_pmpaddrx(uint32_t dev, uint8_t idx, uint32_t addr)
{
    uint32_t reg = dev + IOPMP_ADDR0 + (idx * sizeof(uint32_t));
    *(volatile uint32_t *)reg = addr;
}

inline static uint32_t iopmp_get_pmpaddrx(uint32_t dev, uint8_t idx)
{
    uint32_t reg = dev + IOPMP_ADDR0 + (idx * sizeof(uint32_t));
    return *(volatile uint32_t *)reg;
}

inline static void iopmp_set_pmpxcfg(uint32_t dev, uint8_t idx, uint32_t val)
{
    uint32_t reg = dev + IOPMP_CFG0 + (idx * sizeof(uint32_t));
    *(volatile uint32_t *)reg = val;
}

inline static uint32_t iopmp_get_pmpxcfg(uint32_t dev, uint8_t idx)
{
    uint32_t reg = dev + IOPMP_CFG0 + (idx * sizeof(uint32_t));
    return *(volatile uint32_t *)reg;
}

inline static void iopmp_set_pmpxcfg_by_idx(uint32_t dev, uint8_t idx, iopmp_cfg_attr_t attr)
{
    uint32_t reg = dev + IOPMP_CFG0 + ROUND_DOWN(idx, PMPCFG_STRIDE);
    iopmp_cfg_t iopmp_cfg;
    iopmp_cfg.value = *(volatile uint32_t *)reg;
    iopmp_cfg.arr[idx % PMPCFG_STRIDE].value = attr.value;
    *(volatile uint32_t *)reg = iopmp_cfg.value;
}

inline static uint32_t iopmp_get_pmpxcfg_by_idx(uint32_t dev, uint8_t idx)
{
    uint32_t reg = dev + IOPMP_CFG0 + ROUND_DOWN(idx, PMPCFG_STRIDE);
    iopmp_cfg_t iopmp_cfg;
    iopmp_cfg.value = *(volatile uint32_t *)reg;
    return iopmp_cfg.arr[idx % PMPCFG_STRIDE].value;
}

inline static void iopmp_config_region(uint32_t dev, uint8_t idx, uint32_t addr, iopmp_cfg_attr_t attr)
{
    if (idx >= PMPCFG_SLOTS) {
        return;
    }

    iopmp_set_pmpaddrx(dev, idx, addr);
    iopmp_set_pmpxcfg_by_idx(dev, idx, attr);
}

#if !defined(IS_POWER_OF_TWO)
#define IS_POWER_OF_TWO(x) (((x) != 0U) && (((x) & ((x) - 1U)) == 0U))
#endif

inline static int iopmp_config_region_napot(uint32_t dev, uint8_t idx,
                                    uint32_t addr, uint64_t size,
                                    bool read, bool write, bool exe, bool lock)
{
    int ret = 0;
    if ((0 == (addr % size)) && (IS_POWER_OF_TWO(size))) {
        iopmp_cfg_attr_t iopmp_cfg_attr = {
            .COMP_READ = read,
            .COMP_WRITE = write,
            .COMP_EXCUT = exe,
            .COMP_ADDR_MODE = IOPMP_MODE_NAPOT,
            .COMP_LOCK = lock,
        };
        iopmp_config_region(dev, idx, addr2napot(addr, size), iopmp_cfg_attr);
    } else {
        ret = -EINVAL;
    }

    return ret;
}

inline static void iopmp_config_region_tor(uint32_t dev, uint8_t idx, uint32_t addr,
                                bool read, bool write, bool exe, bool lock)
{
    iopmp_cfg_attr_t iopmp_cfg_attr = {
        .COMP_READ = read,
        .COMP_WRITE = write,
        .COMP_EXCUT = exe,
        .COMP_ADDR_MODE = IOPMP_MODE_TOR,
        .COMP_LOCK = lock,
    };
    iopmp_config_region(dev, idx, addr, iopmp_cfg_attr);
}

#ifdef __cplusplus
}
#endif

#endif /* _IOPMP_H */
