#ifndef REG_GPIO_H_
#define REG_GPIO_H_
#include <stdint.h>
#include "reg_base_addr.h"

#define SEC_GPIO ((reg_gpio_t *)(SEC_PMU_RG_SEC_ADDR + 0x80))
#define APP_GPIO ((reg_gpio_t *)(APP_PMU_RG_APP_ADDR + 0x80))

typedef struct {
    volatile uint32_t LOCK; //[15:0]

    volatile uint32_t PU1_PU0;
    // volatile uint16_t PU0; //[15:0]
    // volatile uint16_t PU1; //[31:16]

    volatile uint32_t PD_PU2;
    // volatile uint16_t PU2; //[15:0]
    // volatile uint16_t PD; //[31:16]

    volatile uint32_t IEN1_IEN0;
    // volatile uint16_t IEN_3V3; //[15:0]
    // volatile uint16_t IEN_1V8; //[31:16]

    volatile uint32_t DS1_DS0;
    // volatile uint16_t DS0; //[15:0]
    // volatile uint16_t DS1; //[31:16]

    volatile uint32_t AE_DS2;
    // volatile uint16_t DS2; //[15:0]
    // volatile uint16_t AE; //[31:16]

    volatile uint32_t OD_FIR;
    // volatile uint16_t FIR; //[15:0]
    // volatile uint16_t OD; //[31:16]

    volatile uint32_t SL_ST;
    // volatile uint16_t ST; //[15:0]
    // volatile uint16_t SL; //[31:16]
} reg_io_cfg_t;

typedef struct {
    volatile uint32_t OE_DIN;
    // const volatile uint16_t DIN; //[15:0]
    // volatile uint16_t OE; //[31:16]

    volatile uint32_t DOC_DOS; //[15:0]
    // volatile uint16_t DOT_SET; //[15:0]
    // volatile uint16_t DOT_CLR; //[31:16]
} reg_io_val_t;

typedef struct {
#if 1
    volatile uint32_t GPIO_INTR_MSK[15]; //0x80
    volatile uint32_t RESERVED1[1];
    volatile uint32_t GPIO_INTR_CLR[15]; //0xc0
    volatile uint32_t RESERVED2[1];
    volatile uint32_t GPIO_INTR_STT[15]; //0x100
    volatile uint32_t RESERVED3[1];
    volatile uint32_t GPIO_INTR_RAW[15]; //0x140
    volatile uint32_t RESERVED4[1];

    reg_io_cfg_t IO_CFG[15];
    reg_io_val_t IO_VAL[15];
#else
    volatile uint32_t GPIOA_INTR_MSK; //0x80
    volatile uint32_t RESERVED1[1];
    volatile uint32_t GPIOC_INTR_MSK; //0x88
    volatile uint32_t RESERVED2[1];
    volatile uint32_t GPIOE_INTR_MSK; //0x90
    volatile uint32_t RESERVED3[3];
    volatile uint32_t GPIOI_INTR_MSK; //0xa0
    volatile uint32_t RESERVED4[1];
    volatile uint32_t GPIOK_INTR_MSK; //0xa8
    volatile uint32_t RESERVED5[5];
    volatile uint32_t GPIOA_INTR_CLR; //0xc0
    volatile uint32_t RESERVED6[1];
    volatile uint32_t GPIOC_INTR_CLR; //0xc8
    volatile uint32_t RESERVED7[1];
    volatile uint32_t GPIOE_INTR_CLR; //0xd0
    volatile uint32_t RESERVED8[3];
    volatile uint32_t GPIOI_INTR_CLR; //0xe0
    volatile uint32_t RESERVED9[1];
    volatile uint32_t GPIOK_INTR_CLR; //0xe8
    volatile uint32_t RESERVED10[5];
    volatile uint32_t GPIOA_INTR_STT; //0x100
    volatile uint32_t RESERVED11[1];
    volatile uint32_t GPIOC_INTR_STT; //0x108
    volatile uint32_t RESERVED12[1];
    volatile uint32_t GPIOE_INTR_STT; //0x110
    volatile uint32_t RESERVED13[3];
    volatile uint32_t GPIOI_INTR_STT; //0x120
    volatile uint32_t RESERVED14[1];
    volatile uint32_t GPIOK_INTR_STT; //0x128
    volatile uint32_t RESERVED15[5];
    volatile uint32_t GPIOA_INTR_RAW; //0x140
    volatile uint32_t RESERVED16[1];
    volatile uint32_t GPIOC_INTR_RAW; //0x148
    volatile uint32_t RESERVED17[1];
    volatile uint32_t GPIOE_INTR_RAW; //0x150
    volatile uint32_t RESERVED18[3];
    volatile uint32_t GPIOI_INTR_RAW; //0x160
    volatile uint32_t RESERVED19[1];
    volatile uint32_t GPIOK_INTR_RAW; //0x168
    volatile uint32_t RESERVED20[5];
    volatile uint32_t IOA_LOCK; //0x180
    volatile uint32_t IOA_PU0_PU1; //0x184
    volatile uint32_t IOA_PU2_PD; //0x188
    volatile uint32_t IOA_REN; //0x18c
    volatile uint32_t IOA_DS0_DS1; //0x190
    volatile uint32_t IOA_DS2_AE; //0x194
    volatile uint32_t IOA_FIR_ODE; //0x198
    volatile uint32_t RESERVED21[9];
    volatile uint32_t IOC_LOCK; //0x1c0
    volatile uint32_t IOC_PU0_PU1; //0x1c4
    volatile uint32_t IOC_PU2_PD; //0x1c8
    volatile uint32_t IOC_REN; //0x1cc
    volatile uint32_t IOC_DS0_DS1; //0x1d0
    volatile uint32_t IOC_DS2_AE; //0x1d4
    volatile uint32_t IOC_FIR_ODE; //0x1d8
    volatile uint32_t IOC_ST_SL; //0x1dc
    volatile uint32_t RESERVED22[8];
    volatile uint32_t IOE_LOCK; //0x200
    volatile uint32_t IOE_PU0_PU1; //0x204
    volatile uint32_t IOE_PU2_PD; //0x208
    volatile uint32_t IOE_REN; //0x20c
    volatile uint32_t IOE_DS0_DS1; //0x210
    volatile uint32_t IOE_DS2_AE; //0x214
    volatile uint32_t IOE_FIR_ODE; //0x218
    volatile uint32_t IOE_ST_SL; //0x21c
    volatile uint32_t RESERVED23[24];
    volatile uint32_t IOI_LOCK; //0x280
    volatile uint32_t IOI_PU0_PU1; //0x284
    volatile uint32_t IOI_PU2_PD; //0x288
    volatile uint32_t IOI_REN; //0x28c
    volatile uint32_t IOI_DS0_DS1; //0x290
    volatile uint32_t IOI_DS2_AE; //0x294
    volatile uint32_t IOI_FIR_ODE; //0x298
    volatile uint32_t IOI_ST_SL; //0x29c
    volatile uint32_t RESERVED24[8];
    volatile uint32_t IOK_LOCK; //0x2c0
    volatile uint32_t IOK_PU0_PU1; //0x2c4
    volatile uint32_t IOK_PU2_PD; //0x2c8
    volatile uint32_t IOK_REN; //0x2cc
    volatile uint32_t IOK_DS0_DS1; //0x2d0
    volatile uint32_t IOK_DS2_AE; //0x2d4
    volatile uint32_t IOK_FIR_ODE; //0x2d8
    volatile uint32_t IOK_ST_SL; //0x2dc
    volatile uint32_t RESERVED25[32];
    volatile uint32_t IOA_DIN_OE; //0x360
    volatile uint32_t IOA_DOT; //0x364
    volatile uint32_t RESERVED26[2];
    volatile uint32_t IOC_DIN_OE; //0x370
    volatile uint32_t IOC_DOT; //0x374
    volatile uint32_t RESERVED27[2];
    volatile uint32_t IOE_DIN_OE; //0x380
    volatile uint32_t IOE_DOT; //0x384
    volatile uint32_t RESERVED28[6];
    volatile uint32_t IOI_DIN_OE; //0x3a0
    volatile uint32_t IOI_DOT; //0x3a4
    volatile uint32_t RESERVED29[2];
    volatile uint32_t IOK_DIN_OE; //0x3b0
    volatile uint32_t IOK_DOT; //0x3b4
    volatile uint32_t RESERVED30[10];
#endif
    volatile uint32_t MODE_PAD_LOCK_ST; //0x3e0
    volatile uint32_t MODE_PAD_PU_PD; //0x3e4
    volatile uint32_t MODE_PAD_REN_DS0; //0x3e8
    volatile uint32_t MODE_PAD_DS1_FIR; //0x3ec
} reg_gpio_t;

#endif
