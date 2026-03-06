#ifndef REG_SYSC_AWO_TYPE_H_
#define REG_SYSC_AWO_TYPE_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SYSC_AWO_CFG           ((reg_sysc_awo_t *)   (REG_TOP_SYS_CFG3_PIN_MUX_BASE))

typedef struct
{
    volatile uint32_t FUNC0_ABCD_EN; //0x0
    volatile uint32_t FUNC0_EFGH_EN; //0x4
    volatile uint32_t FUNC0_IJKL_EN; //0x8
    volatile uint32_t FUNC0_MNOP_EN; //0xc
    volatile uint32_t FUNC0_QRST_EN; //0x10
    volatile uint32_t FUNC0_UVWX_EN; //0x14
    volatile uint32_t FUNC0_YZEEFF_EN; //0x18
    volatile uint32_t FUNC0_AABBCCDD_EN; //0x1c
    volatile uint32_t FUNC1_ABCD_EN; //0x20
    volatile uint32_t FUNC1_EFGH_EN; //0x24
    volatile uint32_t FUNC1_IJKL_EN; //0x28
    volatile uint32_t FUNC1_MNOP_EN; //0x2c
    volatile uint32_t FUNC1_QRST_EN; //0x30
    volatile uint32_t FUNC1_UVWX_EN; //0x34
    volatile uint32_t FUNC1_YZEEFF_EN; //0x38
    volatile uint32_t FUNC1_AABBCCDD_EN; //0x3c
    volatile uint32_t FUNC1_JTAGMS_EN; //0x40
    volatile uint32_t FUNC2_ABCD_EN; //0x44
    volatile uint32_t FUNC2_EFGH_EN; //0x48
    volatile uint32_t FUNC2_IJKL_EN; //0x4c
    volatile uint32_t FUNC2_MNOP_EN; //0x50
    volatile uint32_t FUNC2_QRST_EN; //0x54
    volatile uint32_t FUNC2_UVWX_EN; //0x58
    volatile uint32_t FUNC2_YZEEFF_EN; //0x5c
    volatile uint32_t FUNC2_AABBCCDD_EN; //0x60
    volatile uint32_t FUNC2_JTAGMS_EN; //0x64
    volatile uint32_t FUNC3_ABCD_EN; //0x68
    volatile uint32_t FUNC3_EFGH_EN; //0x6c
    volatile uint32_t FUNC3_IJKL_EN; //0x70
    volatile uint32_t FUNC3_MNOP_EN; //0x74
    volatile uint32_t FUNC3_QRST_EN; //0x78
    volatile uint32_t FUNC3_UVWX_EN; //0x7c
    volatile uint32_t FUNC3_YZEEFF_EN; //0x80
    volatile uint32_t FUNC3_AABBCCDD_EN; //0x84
    volatile uint32_t FUNC4_ABCD_EN; //0x88
    volatile uint32_t FUNC4_EFGH_EN; //0x8c
    volatile uint32_t FUNC4_IJKL_EN; //0x90
    volatile uint32_t FUNC4_MNOP_EN; //0x94
    volatile uint32_t FUNC4_QRST_EN; //0x98
    volatile uint32_t FUNC4_UVWX_EN; //0x9c
    volatile uint32_t FUNC4_YZEEFF_EN; //0xa0
    volatile uint32_t FUNC4_AABBCCDD_EN; //0xa4
    volatile uint32_t FUNC5_ABCD_EN; //0xa8
    volatile uint32_t FUNC5_EFGH_EN; //0xac
    volatile uint32_t FUNC5_IJKL_EN; //0xb0
    volatile uint32_t FUNC5_MNOP_EN; //0xb4
    volatile uint32_t FUNC5_QRST_EN; //0xb8
    volatile uint32_t FUNC5_UVWX_EN; //0xbc
    volatile uint32_t FUNC5_YZEEFF_EN; //0xc0
    volatile uint32_t FUNC5_AABBCCDD_EN; //0xc4
    volatile uint32_t GPABCD_O; //0xc8
    volatile uint32_t GPEFGH_O; //0xcc
    volatile uint32_t GPIJKL_O; //0xd0
    volatile uint32_t GPMNOP_O; //0xd4
    volatile uint32_t GPQRST_O; //0xd8
    volatile uint32_t GPUVWX_O; //0xdc
    volatile uint32_t GPYZEEFF_O; //0xe0
    volatile uint32_t GPAABBCCDD_O; //0xe4
    volatile uint32_t GPJTAGMS_O; //0xe8
    volatile uint32_t GPABCD_OE; //0xec
    volatile uint32_t GPEFGH_OE; //0xf0
    volatile uint32_t GPIJKL_OE; //0xf4
    volatile uint32_t GPMNOP_OE; //0xf8
    volatile uint32_t GPQRST_OE; //0xfc
    volatile uint32_t GPUVWX_OE; //0x100
    volatile uint32_t GPYZEEFF_OE; //0x104
    volatile uint32_t GPAABBCCDD_OE; //0x108
    volatile uint32_t GPJTAGMS_OE; //0x10c
    volatile uint32_t GPABCD_I; //0x110
    volatile uint32_t GPEFGH_I; //0x114
    volatile uint32_t GPIJKL_I; //0x118
    volatile uint32_t GPMNOP_I; //0x11c
    volatile uint32_t GPQRST_I; //0x120
    volatile uint32_t GPUVWX_I; //0x124
    volatile uint32_t GPYZEEFF_I; //0x128
    volatile uint32_t GPAABBCCDD_I; //0x12c
    volatile uint32_t GPJTAGMS_I; //0x130
    volatile uint32_t GPABCD_IE; //0x134
    volatile uint32_t GPEFGH_IE; //0x138
    volatile uint32_t GPIJKL_IE; //0x13c
    volatile uint32_t GPMNOP_IE; //0x140
    volatile uint32_t GPQRST_IE; //0x144
    volatile uint32_t GPUVWX_IE; //0x148
    volatile uint32_t GPYZEEFF_IE; //0x14c
    volatile uint32_t GPAABBCCDD_IE; //0x150
    volatile uint32_t GPJTAGMS_IE; //0x154
    volatile uint32_t GPABCD_REN; //0x158
    volatile uint32_t GPEFGH_REN; //0x15c
    volatile uint32_t GPIJKL_REN; //0x160
    volatile uint32_t GPMNOP_REN; //0x164
    volatile uint32_t GPQRST_REN; //0x168
    volatile uint32_t GPUVWX_REN; //0x16c
    volatile uint32_t GPYZEEFF_REN; //0x170
    volatile uint32_t GPAABBCCDD_REN; //0x174
    volatile uint32_t GPJTAGMS_REN; //0x178
    volatile uint32_t GPABCD_ODE; //0x17c
    volatile uint32_t GPEFGH_ODE; //0x180
    volatile uint32_t GPIJKL_ODE; //0x184
    volatile uint32_t GPMNOP_ODE; //0x188
    volatile uint32_t GPQRST_ODE; //0x18c
    volatile uint32_t GPUVWX_ODE; //0x190
    volatile uint32_t GPYZEEFF_ODE; //0x194
    volatile uint32_t GPAABBCCDD_ODE; //0x198
    volatile uint32_t GPJTAGMS_ODE; //0x19c
    volatile uint32_t GPABCD_PU; //0x1a0
    volatile uint32_t GPEFGH_PU; //0x1a4
    volatile uint32_t GPIL_PU; //0x1a8
    volatile uint32_t GPJ_PU; //0x1ac
    volatile uint32_t GPK_PU; //0x1b0
    volatile uint32_t GPMNOP_PU; //0x1b4
    volatile uint32_t GPQRST_PU; //0x1b8
    volatile uint32_t GPUVWX_PU; //0x1bc
    volatile uint32_t GPYZEEFF_PU; //0x1c0
    volatile uint32_t GPAABBCCDD_PU; //0x1c4
    volatile uint32_t GPJTAGMS_PU; //0x1c8
    volatile uint32_t GPABCD_PD; //0x1cc
    volatile uint32_t GPEFGH_PD; //0x1d0
    volatile uint32_t GPIJKL_PD; //0x1d4
    volatile uint32_t GPMNOP_PD; //0x1d8
    volatile uint32_t GPQRST_PD; //0x1dc
    volatile uint32_t GPUVWX_PD; //0x1e0
    volatile uint32_t GPYZEEFF_PD; //0x1e4
    volatile uint32_t GPAABBCCDD_PD; //0x1e8
    volatile uint32_t GPJTAGMS_PD; //0x1ec
    volatile uint32_t GPABCD_DS0; //0x1f0
    volatile uint32_t GPEFGH_DS0; //0x1f4
    volatile uint32_t GPIJKL_DS0; //0x1f8
    volatile uint32_t GPMNOP_DS0; //0x1fc
    volatile uint32_t GPQRST_DS0; //0x200
    volatile uint32_t GPUVWX_DS0; //0x204
    volatile uint32_t GPYZEEFF_DS0; //0x208
    volatile uint32_t GPAABBCCDD_DS0; //0x20c
    volatile uint32_t GPJTAGMS_DS0; //0x210
    volatile uint32_t GPABCD_DS1; //0x214
    volatile uint32_t GPEFGH_DS1; //0x218
    volatile uint32_t GPIJKL_DS1; //0x21c
    volatile uint32_t GPMNOP_DS1; //0x220
    volatile uint32_t GPQRST_DS1; //0x224
    volatile uint32_t GPUVWX_DS1; //0x228
    volatile uint32_t GPYZEEFF_DS1; //0x22c
    volatile uint32_t GPAABBCCDD_DS1; //0x230
    volatile uint32_t GPJTAGMS_DS1; //0x234
    volatile uint32_t GPABCD_DS2; //0x238
    volatile uint32_t GPEFGH_DS2; //0x23c
    volatile uint32_t GPIJKL_DS2; //0x240
    volatile uint32_t GPMNOP_DS2; //0x244
    volatile uint32_t GPQRST_DS2; //0x248
    volatile uint32_t GPUVWX_DS2; //0x24c
    volatile uint32_t GPYZEEFF_DS2; //0x250
    volatile uint32_t GPAABBCCDD_DS2; //0x254
    volatile uint32_t GPJTAGMS_DS2; //0x258
    volatile uint32_t GPABCD_DS3; //0x25c
    volatile uint32_t GPEFGH_DS3; //0x260
    volatile uint32_t GPIJKL_DS3; //0x264
    volatile uint32_t GPMNOP_DS3; //0x268
    volatile uint32_t GPQRST_DS3; //0x26c
    volatile uint32_t GPUVWX_DS3; //0x270
    volatile uint32_t GPYZEEFF_DS3; //0x274
    volatile uint32_t GPAABBCCDD_DS3; //0x278
    volatile uint32_t GPJTAGMS_DS3; //0x27c
    volatile uint32_t GPABCD_ST; //0x280
    volatile uint32_t GPEFGH_ST; //0x284
    volatile uint32_t GPIJKL_ST; //0x288
    volatile uint32_t GPMNOP_ST; //0x28c
    volatile uint32_t GPQRST_ST; //0x290
    volatile uint32_t GPUVWX_ST; //0x294
    volatile uint32_t GPYZEEFF_ST; //0x298
    volatile uint32_t GPAABBCCDD_ST; //0x29c
    volatile uint32_t GPJTAGMS_ST; //0x2a0
    volatile uint32_t GPABCD_SL; //0x2a4
    volatile uint32_t GPEFGH_SL; //0x2a8
    volatile uint32_t GPIJKL_SL; //0x2ac
    volatile uint32_t GPMNOP_SL; //0x2b0
    volatile uint32_t GPQRST_SL; //0x2b4
    volatile uint32_t GPUVWX_SL; //0x2b8
    volatile uint32_t GPYZEEFF_SL; //0x2bc
    volatile uint32_t GPAABBCCDD_SL; //0x2c0
    volatile uint32_t GPJTAGMS_SL; //0x2c4
    volatile uint32_t MULTIPLEX_SEL; //0x2c8
    volatile uint32_t SIG_SEL; //0x2cc
    volatile uint32_t GPIO_INTR_SEL; //0x2d0
    volatile uint32_t GPAB_INTR0_MSK; //0x2d4
    volatile uint32_t GPCD_INTR0_MSK; //0x2d8
    volatile uint32_t GPEF_INTR0_MSK; //0x2dc
    volatile uint32_t GPGH_INTR0_MSK; //0x2e0
    volatile uint32_t GPIJ_INTR0_MSK; //0x2e4
    volatile uint32_t GPKL_INTR0_MSK; //0x2e8
    volatile uint32_t GPMN_INTR0_MSK; //0x2ec
    volatile uint32_t GPOP_INTR0_MSK; //0x2f0
    volatile uint32_t GPQR_INTR0_MSK; //0x2f4
    volatile uint32_t GPST_INTR0_MSK; //0x2f8
    volatile uint32_t GPUV_INTR0_MSK; //0x2fc
    volatile uint32_t GPWX_INTR0_MSK; //0x300
    volatile uint32_t GPYZ_INTR0_MSK; //0x304
    volatile uint32_t GPEEFF_INTR0_MSK; //0x308
    volatile uint32_t GPAABB_INTR0_MSK; //0x30c
    volatile uint32_t GPCCDD_INTR0_MSK; //0x310
    volatile uint32_t GPJTAGMS_INTR0_MSK; //0x314
    volatile uint32_t GPAIO_INTR0_MSK; //0x318
    volatile uint32_t GPAB_INTR0_CLR; //0x31c
    volatile uint32_t GPCD_INTR0_CLR; //0x320
    volatile uint32_t GPEF_INTR0_CLR; //0x324
    volatile uint32_t GPGH_INTR0_CLR; //0x328
    volatile uint32_t GPIJ_INTR0_CLR; //0x32c
    volatile uint32_t GPKL_INTR0_CLR; //0x330
    volatile uint32_t GPMN_INTR0_CLR; //0x334
    volatile uint32_t GPOP_INTR0_CLR; //0x338
    volatile uint32_t GPQR_INTR0_CLR; //0x33c
    volatile uint32_t GPST_INTR0_CLR; //0x340
    volatile uint32_t GPUV_INTR0_CLR; //0x344
    volatile uint32_t GPWX_INTR0_CLR; //0x348
    volatile uint32_t GPYZ_INTR0_CLR; //0x34c
    volatile uint32_t GPEEFF_INTR0_CLR; //0x350
    volatile uint32_t GPAABB_INTR0_CLR; //0x354
    volatile uint32_t GPCCDD_INTR0_CLR; //0x358
    volatile uint32_t GPJTAGMS_INTR0_CLR; //0x35c
    volatile uint32_t GPAIO_INTR0_CLR; //0x360
    volatile uint32_t GPAB_INTR0_RAW; //0x364
    volatile uint32_t GPCD_INTR0_RAW; //0x368
    volatile uint32_t GPEF_INTR0_RAW; //0x36c
    volatile uint32_t GPGH_INTR0_RAW; //0x370
    volatile uint32_t GPIJ_INTR0_RAW; //0x374
    volatile uint32_t GPKL_INTR0_RAW; //0x378
    volatile uint32_t GPMN_INTR0_RAW; //0x37c
    volatile uint32_t GPOP_INTR0_RAW; //0x380
    volatile uint32_t GPQR_INTR0_RAW; //0x384
    volatile uint32_t GPST_INTR0_RAW; //0x388
    volatile uint32_t GPUV_INTR0_RAW; //0x38c
    volatile uint32_t GPWX_INTR0_RAW; //0x390
    volatile uint32_t GPYZ_INTR0_RAW; //0x394
    volatile uint32_t GPEEFF_INTR0_RAW; //0x398
    volatile uint32_t GPAABB_INTR0_RAW; //0x39c
    volatile uint32_t GPCCDD_INTR0_RAW; //0x3a0
    volatile uint32_t GPJTAGMS_INTR0_RAW; //0x3a4
    volatile uint32_t GPAIO_INTR0_RAW; //0x3a8
    volatile uint32_t GPAB_INTR0_STT; //0x3ac
    volatile uint32_t GPCD_INTR0_STT; //0x3b0
    volatile uint32_t GPEF_INTR0_STT; //0x3b4
    volatile uint32_t GPGH_INTR0_STT; //0x3b8
    volatile uint32_t GPIJ_INTR0_STT; //0x3bc
    volatile uint32_t GPKL_INTR0_STT; //0x3c0
    volatile uint32_t GPMN_INTR0_STT; //0x3c4
    volatile uint32_t GPOP_INTR0_STT; //0x3c8
    volatile uint32_t GPQR_INTR0_STT; //0x3cc
    volatile uint32_t GPST_INTR0_STT; //0x3d0
    volatile uint32_t GPUV_INTR0_STT; //0x3d4
    volatile uint32_t GPWX_INTR0_STT; //0x3d8
    volatile uint32_t GPYZ_INTR0_STT; //0x3dc
    volatile uint32_t GPEEFF_INTR0_STT; //0x3e0
    volatile uint32_t GPAABB_INTR0_STT; //0x3e4
    volatile uint32_t GPCCDD_INTR0_STT; //0x3e8
    volatile uint32_t GPJTAGMS_INTR0_STT; //0x3ec
    volatile uint32_t GPAIO_INTR0_STT; //0x3f0
    volatile uint32_t GPAB_INTR1_MSK; //0x3f4
    volatile uint32_t GPCD_INTR1_MSK; //0x3f8
    volatile uint32_t GPEF_INTR1_MSK; //0x3fc
    volatile uint32_t GPGH_INTR1_MSK; //0x400
    volatile uint32_t GPIJ_INTR1_MSK; //0x404
    volatile uint32_t GPKL_INTR1_MSK; //0x408
    volatile uint32_t GPMN_INTR1_MSK; //0x40c
    volatile uint32_t GPOP_INTR1_MSK; //0x410
    volatile uint32_t GPQR_INTR1_MSK; //0x414
    volatile uint32_t GPST_INTR1_MSK; //0x418
    volatile uint32_t GPUV_INTR1_MSK; //0x41c
    volatile uint32_t GPWX_INTR1_MSK; //0x420
    volatile uint32_t GPYZ_INTR1_MSK; //0x424
    volatile uint32_t GPEEFF_INTR1_MSK; //0x428
    volatile uint32_t GPAABB_INTR1_MSK; //0x42c
    volatile uint32_t GPCCDD_INTR1_MSK; //0x430
    volatile uint32_t GPJTAGMS_INTR1_MSK; //0x434
    volatile uint32_t GPAIO_INTR1_MSK; //0x438
    volatile uint32_t GPAB_INTR1_CLR; //0x43c
    volatile uint32_t GPCD_INTR1_CLR; //0x440
    volatile uint32_t GPEF_INTR1_CLR; //0x444
    volatile uint32_t GPGH_INTR1_CLR; //0x448
    volatile uint32_t GPIJ_INTR1_CLR; //0x44c
    volatile uint32_t GPKL_INTR1_CLR; //0x450
    volatile uint32_t GPMN_INTR1_CLR; //0x454
    volatile uint32_t GPOP_INTR1_CLR; //0x458
    volatile uint32_t GPQR_INTR1_CLR; //0x45c
    volatile uint32_t GPST_INTR1_CLR; //0x460
    volatile uint32_t GPUV_INTR1_CLR; //0x464
    volatile uint32_t GPWX_INTR1_CLR; //0x468
    volatile uint32_t GPYZ_INTR1_CLR; //0x46c
    volatile uint32_t GPEEFF_INTR1_CLR; //0x470
    volatile uint32_t GPAABB_INTR1_CLR; //0x474
    volatile uint32_t GPCCDD_INTR1_CLR; //0x478
    volatile uint32_t GPJTAGMS_INTR1_CLR; //0x47c
    volatile uint32_t GPAIO_INTR1_CLR; //0x480
    volatile uint32_t GPAB_INTR1_RAW; //0x484
    volatile uint32_t GPCD_INTR1_RAW; //0x488
    volatile uint32_t GPEF_INTR1_RAW; //0x48c
    volatile uint32_t GPGH_INTR1_RAW; //0x490
    volatile uint32_t GPIJ_INTR1_RAW; //0x494
    volatile uint32_t GPKL_INTR1_RAW; //0x498
    volatile uint32_t GPMN_INTR1_RAW; //0x49c
    volatile uint32_t GPOP_INTR1_RAW; //0x4a0
    volatile uint32_t GPQR_INTR1_RAW; //0x4a4
    volatile uint32_t GPST_INTR1_RAW; //0x4a8
    volatile uint32_t GPUV_INTR1_RAW; //0x4ac
    volatile uint32_t GPWX_INTR1_RAW; //0x4b0
    volatile uint32_t GPYZ_INTR1_RAW; //0x4b4
    volatile uint32_t GPEEFF_INTR1_RAW; //0x4b8
    volatile uint32_t GPAABB_INTR1_RAW; //0x4bc
    volatile uint32_t GPCCDD_INTR1_RAW; //0x4c0
    volatile uint32_t GPJTAGMS_INTR1_RAW; //0x4c4
    volatile uint32_t GPAIO_INTR1_RAW; //0x4c8
    volatile uint32_t GPAB_INTR1_STT; //0x4cc
    volatile uint32_t GPCD_INTR1_STT; //0x4d0
    volatile uint32_t GPEF_INTR1_STT; //0x4d4
    volatile uint32_t GPGH_INTR1_STT; //0x4d8
    volatile uint32_t GPIJ_INTR1_STT; //0x4dc
    volatile uint32_t GPKL_INTR1_STT; //0x4e0
    volatile uint32_t GPMN_INTR1_STT; //0x4e4
    volatile uint32_t GPOP_INTR1_STT; //0x4e8
    volatile uint32_t GPQR_INTR1_STT; //0x4ec
    volatile uint32_t GPST_INTR1_STT; //0x4f0
    volatile uint32_t GPUV_INTR1_STT; //0x4f4
    volatile uint32_t GPWX_INTR1_STT; //0x4f8
    volatile uint32_t GPYZ_INTR1_STT; //0x4fc
    volatile uint32_t GPEEFF_INTR1_STT; //0x500
    volatile uint32_t GPAABB_INTR1_STT; //0x504
    volatile uint32_t GPCCDD_INTR1_STT; //0x508
    volatile uint32_t GPJTAGMS_INTR1_STT; //0x50c
    volatile uint32_t GPAIO_INTR1_STT; //0x510
    volatile uint32_t GPEYZ_AE; //0x514
    volatile uint32_t APB_EXTI0_INTR; //0x518
    volatile uint32_t APB_EXTI1_INTR; //0x51c
    volatile uint32_t APB_EXTI2_INTR; //0x520
    volatile uint32_t APB_EXTI3_INTR; //0x524
    volatile uint32_t GP_MD_LP_CTRL0; //0x528
    volatile uint32_t GP_MD_LP_CTRL1; //0x52c
    volatile uint32_t UART03_RX_MULTIPLEX_SEL; //0x530
    volatile uint32_t UART47_RX_MULTIPLEX_SEL; //0x534
    volatile uint32_t UART811_RX_MULTIPLEX_SEL; //0x538
    volatile uint32_t UART12_RX_MULTIPLEX_SEL; //0x53c
    volatile uint32_t UART03_TX_MULTIPLEX_SEL; //0x540
    volatile uint32_t UART47_TX_MULTIPLEX_SEL; //0x544
    volatile uint32_t UART811_TX_MULTIPLEX_SEL; //0x548
    volatile uint32_t UART1231_TX_MULTIPLEX_SEL; //0x54c
} reg_sysc_awo_t;

enum SYSC_AWO_REG_FUNC0_ABCD_EN_FIELD
{
    SYSC_AWO_FUNC0_IOA_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC0_IOA_EN_POS = 0,
    SYSC_AWO_FUNC0_IOB_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC0_IOB_EN_POS = 8,
    SYSC_AWO_FUNC0_IOC_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC0_IOC_EN_POS = 16,
    SYSC_AWO_FUNC0_IOD_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC0_IOD_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC0_EFGH_EN_FIELD
{
    SYSC_AWO_FUNC0_IOE_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC0_IOE_EN_POS = 0,
    SYSC_AWO_FUNC0_IOF_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC0_IOF_EN_POS = 8,
    SYSC_AWO_FUNC0_IOG_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC0_IOG_EN_POS = 16,
    SYSC_AWO_FUNC0_IOH_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC0_IOH_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC0_IJKL_EN_FIELD
{
    SYSC_AWO_FUNC0_IOI_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC0_IOI_EN_POS = 0,
    SYSC_AWO_FUNC0_IOJ_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC0_IOJ_EN_POS = 8,
    SYSC_AWO_FUNC0_IOK_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC0_IOK_EN_POS = 16,
    SYSC_AWO_FUNC0_IOL_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC0_IOL_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC0_MNOP_EN_FIELD
{
    SYSC_AWO_FUNC0_IOM_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC0_IOM_EN_POS = 0,
    SYSC_AWO_FUNC0_ION_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC0_ION_EN_POS = 8,
    SYSC_AWO_FUNC0_IOO_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC0_IOO_EN_POS = 16,
    SYSC_AWO_FUNC0_IOP_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC0_IOP_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC0_QRST_EN_FIELD
{
    SYSC_AWO_FUNC0_IOQ_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC0_IOQ_EN_POS = 0,
    SYSC_AWO_FUNC0_IOR_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC0_IOR_EN_POS = 8,
    SYSC_AWO_FUNC0_IOS_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC0_IOS_EN_POS = 16,
    SYSC_AWO_FUNC0_IOT_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC0_IOT_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC0_UVWX_EN_FIELD
{
    SYSC_AWO_FUNC0_IOU_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC0_IOU_EN_POS = 0,
    SYSC_AWO_FUNC0_IOV_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC0_IOV_EN_POS = 8,
    SYSC_AWO_FUNC0_IOW_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC0_IOW_EN_POS = 16,
    SYSC_AWO_FUNC0_IOX_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC0_IOX_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC0_YZEEFF_EN_FIELD
{
    SYSC_AWO_FUNC0_IOY_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC0_IOY_EN_POS = 0,
    SYSC_AWO_FUNC0_IOZ_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC0_IOZ_EN_POS = 8,
    SYSC_AWO_FUNC0_IOEE_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC0_IOEE_EN_POS = 16,
    SYSC_AWO_FUNC0_IOFF_EN_MASK = (int)0xf000000,
    SYSC_AWO_FUNC0_IOFF_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC0_AABBCCDD_EN_FIELD
{
    SYSC_AWO_FUNC0_IOAA_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC0_IOAA_EN_POS = 0,
    SYSC_AWO_FUNC0_IOBB_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC0_IOBB_EN_POS = 8,
    SYSC_AWO_FUNC0_IOCC_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC0_IOCC_EN_POS = 16,
    SYSC_AWO_FUNC0_IODD_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC0_IODD_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC1_ABCD_EN_FIELD
{
    SYSC_AWO_FUNC1_IOA_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC1_IOA_EN_POS = 0,
    SYSC_AWO_FUNC1_IOB_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC1_IOB_EN_POS = 8,
    SYSC_AWO_FUNC1_IOC_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC1_IOC_EN_POS = 16,
    SYSC_AWO_FUNC1_IOD_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC1_IOD_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC1_EFGH_EN_FIELD
{
    SYSC_AWO_FUNC1_IOE_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC1_IOE_EN_POS = 0,
    SYSC_AWO_FUNC1_IOF_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC1_IOF_EN_POS = 8,
    SYSC_AWO_FUNC1_IOG_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC1_IOG_EN_POS = 16,
    SYSC_AWO_FUNC1_IOH_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC1_IOH_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC1_IJKL_EN_FIELD
{
    SYSC_AWO_FUNC1_IOI_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC1_IOI_EN_POS = 0,
    SYSC_AWO_FUNC1_IOJ_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC1_IOJ_EN_POS = 8,
    SYSC_AWO_FUNC1_IOK_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC1_IOK_EN_POS = 16,
    SYSC_AWO_FUNC1_IOL_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC1_IOL_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC1_MNOP_EN_FIELD
{
    SYSC_AWO_FUNC1_IOM_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC1_IOM_EN_POS = 0,
    SYSC_AWO_FUNC1_ION_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC1_ION_EN_POS = 8,
    SYSC_AWO_FUNC1_IOO_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC1_IOO_EN_POS = 16,
    SYSC_AWO_FUNC1_IOP_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC1_IOP_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC1_QRST_EN_FIELD
{
    SYSC_AWO_FUNC1_IOQ_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC1_IOQ_EN_POS = 0,
    SYSC_AWO_FUNC1_IOR_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC1_IOR_EN_POS = 8,
    SYSC_AWO_FUNC1_IOS_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC1_IOS_EN_POS = 16,
    SYSC_AWO_FUNC1_IOT_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC1_IOT_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC1_UVWX_EN_FIELD
{
    SYSC_AWO_FUNC1_IOU_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC1_IOU_EN_POS = 0,
    SYSC_AWO_FUNC1_IOV_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC1_IOV_EN_POS = 8,
    SYSC_AWO_FUNC1_IOW_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC1_IOW_EN_POS = 16,
    SYSC_AWO_FUNC1_IOX_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC1_IOX_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC1_YZEEFF_EN_FIELD
{
    SYSC_AWO_FUNC1_IOY_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC1_IOY_EN_POS = 0,
    SYSC_AWO_FUNC1_IOZ_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC1_IOZ_EN_POS = 8,
    SYSC_AWO_FUNC1_IOEE_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC1_IOEE_EN_POS = 16,
    SYSC_AWO_FUNC1_IOFF_EN_MASK = (int)0xf000000,
    SYSC_AWO_FUNC1_IOFF_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC1_AABBCCDD_EN_FIELD
{
    SYSC_AWO_FUNC1_IOAA_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC1_IOAA_EN_POS = 0,
    SYSC_AWO_FUNC1_IOBB_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC1_IOBB_EN_POS = 8,
    SYSC_AWO_FUNC1_IOCC_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC1_IOCC_EN_POS = 16,
    SYSC_AWO_FUNC1_IODD_EN_MASK = (int)0x1000000,
    SYSC_AWO_FUNC1_IODD_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC1_JTAGMS_EN_FIELD
{
    SYSC_AWO_FUNC1_IOJTAGMS_EN_MASK = (int)0x1f,
    SYSC_AWO_FUNC1_IOJTAGMS_EN_POS = 0,
};

enum SYSC_AWO_REG_FUNC2_ABCD_EN_FIELD
{
    SYSC_AWO_FUNC2_IOA_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC2_IOA_EN_POS = 0,
    SYSC_AWO_FUNC2_IOB_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC2_IOB_EN_POS = 8,
    SYSC_AWO_FUNC2_IOC_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC2_IOC_EN_POS = 16,
    SYSC_AWO_FUNC2_IOD_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC2_IOD_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC2_EFGH_EN_FIELD
{
    SYSC_AWO_FUNC2_IOE_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC2_IOE_EN_POS = 0,
    SYSC_AWO_FUNC2_IOF_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC2_IOF_EN_POS = 8,
    SYSC_AWO_FUNC2_IOG_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC2_IOG_EN_POS = 16,
    SYSC_AWO_FUNC2_IOH_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC2_IOH_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC2_IJKL_EN_FIELD
{
    SYSC_AWO_FUNC2_IOI_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC2_IOI_EN_POS = 0,
    SYSC_AWO_FUNC2_IOJ_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC2_IOJ_EN_POS = 8,
    SYSC_AWO_FUNC2_IOK_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC2_IOK_EN_POS = 16,
    SYSC_AWO_FUNC2_IOL_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC2_IOL_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC2_MNOP_EN_FIELD
{
    SYSC_AWO_FUNC2_IOM_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC2_IOM_EN_POS = 0,
    SYSC_AWO_FUNC2_ION_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC2_ION_EN_POS = 8,
    SYSC_AWO_FUNC2_IOO_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC2_IOO_EN_POS = 16,
    SYSC_AWO_FUNC2_IOP_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC2_IOP_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC2_QRST_EN_FIELD
{
    SYSC_AWO_FUNC2_IOQ_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC2_IOQ_EN_POS = 0,
    SYSC_AWO_FUNC2_IOR_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC2_IOR_EN_POS = 8,
    SYSC_AWO_FUNC2_IOS_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC2_IOS_EN_POS = 16,
    SYSC_AWO_FUNC2_IOT_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC2_IOT_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC2_UVWX_EN_FIELD
{
    SYSC_AWO_FUNC2_IOU_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC2_IOU_EN_POS = 0,
    SYSC_AWO_FUNC2_IOV_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC2_IOV_EN_POS = 8,
    SYSC_AWO_FUNC2_IOW_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC2_IOW_EN_POS = 16,
    SYSC_AWO_FUNC2_IOX_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC2_IOX_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC2_YZEEFF_EN_FIELD
{
    SYSC_AWO_FUNC2_IOY_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC2_IOY_EN_POS = 0,
    SYSC_AWO_FUNC2_IOZ_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC2_IOZ_EN_POS = 8,
    SYSC_AWO_FUNC2_IOEE_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC2_IOEE_EN_POS = 16,
    SYSC_AWO_FUNC2_IOFF_EN_MASK = (int)0xf000000,
    SYSC_AWO_FUNC2_IOFF_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC2_AABBCCDD_EN_FIELD
{
    SYSC_AWO_FUNC2_IOAA_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC2_IOAA_EN_POS = 0,
    SYSC_AWO_FUNC2_IOBB_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC2_IOBB_EN_POS = 8,
    SYSC_AWO_FUNC2_IOCC_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC2_IOCC_EN_POS = 16,
    SYSC_AWO_FUNC2_IODD_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC2_IODD_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC2_JTAGMS_EN_FIELD
{
    SYSC_AWO_FUNC2_IOJTAGMS_EN_MASK = (int)0x1f,
    SYSC_AWO_FUNC2_IOJTAGMS_EN_POS = 0,
};

enum SYSC_AWO_REG_FUNC3_ABCD_EN_FIELD
{
    SYSC_AWO_FUNC3_IOA_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC3_IOA_EN_POS = 0,
    SYSC_AWO_FUNC3_IOB_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC3_IOB_EN_POS = 8,
    SYSC_AWO_FUNC3_IOC_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC3_IOC_EN_POS = 16,
    SYSC_AWO_FUNC3_IOD_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC3_IOD_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC3_EFGH_EN_FIELD
{
    SYSC_AWO_FUNC3_IOE_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC3_IOE_EN_POS = 0,
    SYSC_AWO_FUNC3_IOF_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC3_IOF_EN_POS = 8,
    SYSC_AWO_FUNC3_IOG_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC3_IOG_EN_POS = 16,
    SYSC_AWO_FUNC3_IOH_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC3_IOH_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC3_IJKL_EN_FIELD
{
    SYSC_AWO_FUNC3_IOI_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC3_IOI_EN_POS = 0,
    SYSC_AWO_FUNC3_IOJ_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC3_IOJ_EN_POS = 8,
    SYSC_AWO_FUNC3_IOK_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC3_IOK_EN_POS = 16,
    SYSC_AWO_FUNC3_IOL_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC3_IOL_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC3_MNOP_EN_FIELD
{
    SYSC_AWO_FUNC3_IOM_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC3_IOM_EN_POS = 0,
    SYSC_AWO_FUNC3_ION_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC3_ION_EN_POS = 8,
    SYSC_AWO_FUNC3_IOO_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC3_IOO_EN_POS = 16,
    SYSC_AWO_FUNC3_IOP_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC3_IOP_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC3_QRST_EN_FIELD
{
    SYSC_AWO_FUNC3_IOQ_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC3_IOQ_EN_POS = 0,
    SYSC_AWO_FUNC3_IOR_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC3_IOR_EN_POS = 8,
    SYSC_AWO_FUNC3_IOS_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC3_IOS_EN_POS = 16,
    SYSC_AWO_FUNC3_IOT_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC3_IOT_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC3_UVWX_EN_FIELD
{
    SYSC_AWO_FUNC3_IOU_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC3_IOU_EN_POS = 0,
    SYSC_AWO_FUNC3_IOV_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC3_IOV_EN_POS = 8,
    SYSC_AWO_FUNC3_IOW_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC3_IOW_EN_POS = 16,
    SYSC_AWO_FUNC3_IOX_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC3_IOX_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC3_YZEEFF_EN_FIELD
{
    SYSC_AWO_FUNC3_IOY_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC3_IOY_EN_POS = 0,
    SYSC_AWO_FUNC3_IOZ_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC3_IOZ_EN_POS = 8,
    SYSC_AWO_FUNC3_IOEE_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC3_IOEE_EN_POS = 16,
    SYSC_AWO_FUNC3_IOFF_EN_MASK = (int)0xf000000,
    SYSC_AWO_FUNC3_IOFF_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC3_AABBCCDD_EN_FIELD
{
    SYSC_AWO_FUNC3_IOAA_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC3_IOAA_EN_POS = 0,
    SYSC_AWO_FUNC3_IOBB_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC3_IOBB_EN_POS = 8,
    SYSC_AWO_FUNC3_IOCC_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC3_IOCC_EN_POS = 16,
    SYSC_AWO_FUNC3_IODD_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC3_IODD_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC4_ABCD_EN_FIELD
{
    SYSC_AWO_FUNC4_IOA_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC4_IOA_EN_POS = 0,
    SYSC_AWO_FUNC4_IOB_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC4_IOB_EN_POS = 8,
    SYSC_AWO_FUNC4_IOC_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC4_IOC_EN_POS = 16,
    SYSC_AWO_FUNC4_IOD_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC4_IOD_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC4_EFGH_EN_FIELD
{
    SYSC_AWO_FUNC4_IOE_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC4_IOE_EN_POS = 0,
    SYSC_AWO_FUNC4_IOF_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC4_IOF_EN_POS = 8,
    SYSC_AWO_FUNC4_IOG_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC4_IOG_EN_POS = 16,
    SYSC_AWO_FUNC4_IOH_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC4_IOH_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC4_IJKL_EN_FIELD
{
    SYSC_AWO_FUNC4_IOI_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC4_IOI_EN_POS = 0,
    SYSC_AWO_FUNC4_IOJ_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC4_IOJ_EN_POS = 8,
    SYSC_AWO_FUNC4_IOK_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC4_IOK_EN_POS = 16,
    SYSC_AWO_FUNC4_IOL_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC4_IOL_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC4_MNOP_EN_FIELD
{
    SYSC_AWO_FUNC4_IOM_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC4_IOM_EN_POS = 0,
    SYSC_AWO_FUNC4_ION_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC4_ION_EN_POS = 8,
    SYSC_AWO_FUNC4_IOO_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC4_IOO_EN_POS = 16,
    SYSC_AWO_FUNC4_IOP_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC4_IOP_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC4_QRST_EN_FIELD
{
    SYSC_AWO_FUNC4_IOQ_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC4_IOQ_EN_POS = 0,
    SYSC_AWO_FUNC4_IOR_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC4_IOR_EN_POS = 8,
    SYSC_AWO_FUNC4_IOS_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC4_IOS_EN_POS = 16,
    SYSC_AWO_FUNC4_IOT_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC4_IOT_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC4_UVWX_EN_FIELD
{
    SYSC_AWO_FUNC4_IOU_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC4_IOU_EN_POS = 0,
    SYSC_AWO_FUNC4_IOV_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC4_IOV_EN_POS = 8,
    SYSC_AWO_FUNC4_IOW_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC4_IOW_EN_POS = 16,
    SYSC_AWO_FUNC4_IOX_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC4_IOX_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC4_YZEEFF_EN_FIELD
{
    SYSC_AWO_FUNC4_IOY_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC4_IOY_EN_POS = 0,
    SYSC_AWO_FUNC4_IOZ_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC4_IOZ_EN_POS = 8,
    SYSC_AWO_FUNC4_IOEE_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC4_IOEE_EN_POS = 16,
    SYSC_AWO_FUNC4_IOFF_EN_MASK = (int)0xf000000,
    SYSC_AWO_FUNC4_IOFF_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC4_AABBCCDD_EN_FIELD
{
    SYSC_AWO_FUNC4_IOAA_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC4_IOAA_EN_POS = 0,
    SYSC_AWO_FUNC4_IOBB_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC4_IOBB_EN_POS = 8,
    SYSC_AWO_FUNC4_IOCC_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC4_IOCC_EN_POS = 16,
    SYSC_AWO_FUNC4_IODD_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC4_IODD_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC5_ABCD_EN_FIELD
{
    SYSC_AWO_FUNC5_IOA_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC5_IOA_EN_POS = 0,
    SYSC_AWO_FUNC5_IOB_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC5_IOB_EN_POS = 8,
    SYSC_AWO_FUNC5_IOC_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC5_IOC_EN_POS = 16,
    SYSC_AWO_FUNC5_IOD_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC5_IOD_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC5_EFGH_EN_FIELD
{
    SYSC_AWO_FUNC5_IOE_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC5_IOE_EN_POS = 0,
    SYSC_AWO_FUNC5_IOF_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC5_IOF_EN_POS = 8,
    SYSC_AWO_FUNC5_IOG_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC5_IOG_EN_POS = 16,
    SYSC_AWO_FUNC5_IOH_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC5_IOH_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC5_IJKL_EN_FIELD
{
    SYSC_AWO_FUNC5_IOI_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC5_IOI_EN_POS = 0,
    SYSC_AWO_FUNC5_IOJ_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC5_IOJ_EN_POS = 8,
    SYSC_AWO_FUNC5_IOK_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC5_IOK_EN_POS = 16,
    SYSC_AWO_FUNC5_IOL_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC5_IOL_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC5_MNOP_EN_FIELD
{
    SYSC_AWO_FUNC5_IOM_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC5_IOM_EN_POS = 0,
    SYSC_AWO_FUNC5_ION_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC5_ION_EN_POS = 8,
    SYSC_AWO_FUNC5_IOO_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC5_IOO_EN_POS = 16,
    SYSC_AWO_FUNC5_IOP_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC5_IOP_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC5_QRST_EN_FIELD
{
    SYSC_AWO_FUNC5_IOQ_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC5_IOQ_EN_POS = 0,
    SYSC_AWO_FUNC5_IOR_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC5_IOR_EN_POS = 8,
    SYSC_AWO_FUNC5_IOS_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC5_IOS_EN_POS = 16,
    SYSC_AWO_FUNC5_IOT_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC5_IOT_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC5_UVWX_EN_FIELD
{
    SYSC_AWO_FUNC5_IOU_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC5_IOU_EN_POS = 0,
    SYSC_AWO_FUNC5_IOV_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC5_IOV_EN_POS = 8,
    SYSC_AWO_FUNC5_IOW_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC5_IOW_EN_POS = 16,
    SYSC_AWO_FUNC5_IOX_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC5_IOX_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC5_YZEEFF_EN_FIELD
{
    SYSC_AWO_FUNC5_IOY_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC5_IOY_EN_POS = 0,
    SYSC_AWO_FUNC5_IOZ_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC5_IOZ_EN_POS = 8,
    SYSC_AWO_FUNC5_IOEE_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC5_IOEE_EN_POS = 16,
    SYSC_AWO_FUNC5_IOFF_EN_MASK = (int)0xf000000,
    SYSC_AWO_FUNC5_IOFF_EN_POS = 24,
};

enum SYSC_AWO_REG_FUNC5_AABBCCDD_EN_FIELD
{
    SYSC_AWO_FUNC5_IOAA_EN_MASK = (int)0xff,
    SYSC_AWO_FUNC5_IOAA_EN_POS = 0,
    SYSC_AWO_FUNC5_IOBB_EN_MASK = (int)0xff00,
    SYSC_AWO_FUNC5_IOBB_EN_POS = 8,
    SYSC_AWO_FUNC5_IOCC_EN_MASK = (int)0xff0000,
    SYSC_AWO_FUNC5_IOCC_EN_POS = 16,
    SYSC_AWO_FUNC5_IODD_EN_MASK = (int)0xff000000,
    SYSC_AWO_FUNC5_IODD_EN_POS = 24,
};

enum SYSC_AWO_REG_GPABCD_O_FIELD
{
    SYSC_AWO_GPIOA_O_MASK = (int)0xff,
    SYSC_AWO_GPIOA_O_POS = 0,
    SYSC_AWO_GPIOB_O_MASK = (int)0xff00,
    SYSC_AWO_GPIOB_O_POS = 8,
    SYSC_AWO_GPIOC_O_MASK = (int)0xff0000,
    SYSC_AWO_GPIOC_O_POS = 16,
    SYSC_AWO_GPIOD_O_MASK = (int)0xff000000,
    SYSC_AWO_GPIOD_O_POS = 24,
};

enum SYSC_AWO_REG_GPEFGH_O_FIELD
{
    SYSC_AWO_GPIOE_O_MASK = (int)0xff,
    SYSC_AWO_GPIOE_O_POS = 0,
    SYSC_AWO_GPIOF_O_MASK = (int)0xff00,
    SYSC_AWO_GPIOF_O_POS = 8,
    SYSC_AWO_GPIOG_O_MASK = (int)0xff0000,
    SYSC_AWO_GPIOG_O_POS = 16,
    SYSC_AWO_GPIOH_O_MASK = (int)0xf000000,
    SYSC_AWO_GPIOH_O_POS = 24,
};

enum SYSC_AWO_REG_GPIJKL_O_FIELD
{
    SYSC_AWO_GPIOI_O_MASK = (int)0xff,
    SYSC_AWO_GPIOI_O_POS = 0,
    SYSC_AWO_GPIOJ_O_MASK = (int)0xff00,
    SYSC_AWO_GPIOJ_O_POS = 8,
    SYSC_AWO_GPIOK_O_MASK = (int)0xff0000,
    SYSC_AWO_GPIOK_O_POS = 16,
    SYSC_AWO_GPIOL_O_MASK = (int)0xff000000,
    SYSC_AWO_GPIOL_O_POS = 24,
};

enum SYSC_AWO_REG_GPMNOP_O_FIELD
{
    SYSC_AWO_GPIOM_O_MASK = (int)0xff,
    SYSC_AWO_GPIOM_O_POS = 0,
    SYSC_AWO_GPION_O_MASK = (int)0xff00,
    SYSC_AWO_GPION_O_POS = 8,
    SYSC_AWO_GPIOO_O_MASK = (int)0xff0000,
    SYSC_AWO_GPIOO_O_POS = 16,
    SYSC_AWO_GPIOP_O_MASK = (int)0xff000000,
    SYSC_AWO_GPIOP_O_POS = 24,
};

enum SYSC_AWO_REG_GPQRST_O_FIELD
{
    SYSC_AWO_GPIOQ_O_MASK = (int)0xff,
    SYSC_AWO_GPIOQ_O_POS = 0,
    SYSC_AWO_GPIOR_O_MASK = (int)0xff00,
    SYSC_AWO_GPIOR_O_POS = 8,
    SYSC_AWO_GPIOS_O_MASK = (int)0xff0000,
    SYSC_AWO_GPIOS_O_POS = 16,
    SYSC_AWO_GPIOT_O_MASK = (int)0xff000000,
    SYSC_AWO_GPIOT_O_POS = 24,
};

enum SYSC_AWO_REG_GPUVWX_O_FIELD
{
    SYSC_AWO_GPIOU_O_MASK = (int)0xff,
    SYSC_AWO_GPIOU_O_POS = 0,
    SYSC_AWO_GPIOV_O_MASK = (int)0xff00,
    SYSC_AWO_GPIOV_O_POS = 8,
    SYSC_AWO_GPIOW_O_MASK = (int)0xff0000,
    SYSC_AWO_GPIOW_O_POS = 16,
    SYSC_AWO_GPIOX_O_MASK = (int)0xff000000,
    SYSC_AWO_GPIOX_O_POS = 24,
};

enum SYSC_AWO_REG_GPYZEEFF_O_FIELD
{
    SYSC_AWO_GPIOY_O_MASK = (int)0xff,
    SYSC_AWO_GPIOY_O_POS = 0,
    SYSC_AWO_GPIOZ_O_MASK = (int)0xff00,
    SYSC_AWO_GPIOZ_O_POS = 8,
    SYSC_AWO_GPIOEE_O_MASK = (int)0xff0000,
    SYSC_AWO_GPIOEE_O_POS = 16,
    SYSC_AWO_GPIOFF_O_MASK = (int)0xf000000,
    SYSC_AWO_GPIOFF_O_POS = 24,
};

enum SYSC_AWO_REG_GPAABBCCDD_O_FIELD
{
    SYSC_AWO_GPIOAA_O_MASK = (int)0xff,
    SYSC_AWO_GPIOAA_O_POS = 0,
    SYSC_AWO_GPIOBB_O_MASK = (int)0xff00,
    SYSC_AWO_GPIOBB_O_POS = 8,
    SYSC_AWO_GPIOCC_O_MASK = (int)0xff0000,
    SYSC_AWO_GPIOCC_O_POS = 16,
    SYSC_AWO_GPIODD_O_MASK = (int)0x1000000,
    SYSC_AWO_GPIODD_O_POS = 24,
};

enum SYSC_AWO_REG_GPJTAGMS_O_FIELD
{
    SYSC_AWO_GPIOJTAGMS_O_MASK = (int)0x1f,
    SYSC_AWO_GPIOJTAGMS_O_POS = 0,
    SYSC_AWO_GPIOAIO_O_MASK = (int)0x1fe0,
    SYSC_AWO_GPIOAIO_O_POS = 5,
};

enum SYSC_AWO_REG_GPABCD_OE_FIELD
{
    SYSC_AWO_GPIOA_OE_MASK = (int)0xff,
    SYSC_AWO_GPIOA_OE_POS = 0,
    SYSC_AWO_GPIOB_OE_MASK = (int)0xff00,
    SYSC_AWO_GPIOB_OE_POS = 8,
    SYSC_AWO_GPIOC_OE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOC_OE_POS = 16,
    SYSC_AWO_GPIOD_OE_MASK = (int)0xff000000,
    SYSC_AWO_GPIOD_OE_POS = 24,
};

enum SYSC_AWO_REG_GPEFGH_OE_FIELD
{
    SYSC_AWO_GPIOE_OE_MASK = (int)0xff,
    SYSC_AWO_GPIOE_OE_POS = 0,
    SYSC_AWO_GPIOF_OE_MASK = (int)0xff00,
    SYSC_AWO_GPIOF_OE_POS = 8,
    SYSC_AWO_GPIOG_OE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOG_OE_POS = 16,
    SYSC_AWO_GPIOH_OE_MASK = (int)0xf000000,
    SYSC_AWO_GPIOH_OE_POS = 24,
};

enum SYSC_AWO_REG_GPIJKL_OE_FIELD
{
    SYSC_AWO_GPIOI_OE_MASK = (int)0xff,
    SYSC_AWO_GPIOI_OE_POS = 0,
    SYSC_AWO_GPIOJ_OE_MASK = (int)0xff00,
    SYSC_AWO_GPIOJ_OE_POS = 8,
    SYSC_AWO_GPIOK_OE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOK_OE_POS = 16,
    SYSC_AWO_GPIOL_OE_MASK = (int)0xff000000,
    SYSC_AWO_GPIOL_OE_POS = 24,
};

enum SYSC_AWO_REG_GPMNOP_OE_FIELD
{
    SYSC_AWO_GPIOM_OE_MASK = (int)0xff,
    SYSC_AWO_GPIOM_OE_POS = 0,
    SYSC_AWO_GPION_OE_MASK = (int)0xff00,
    SYSC_AWO_GPION_OE_POS = 8,
    SYSC_AWO_GPIOO_OE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOO_OE_POS = 16,
    SYSC_AWO_GPIOP_OE_MASK = (int)0xff000000,
    SYSC_AWO_GPIOP_OE_POS = 24,
};

enum SYSC_AWO_REG_GPQRST_OE_FIELD
{
    SYSC_AWO_GPIOQ_OE_MASK = (int)0xff,
    SYSC_AWO_GPIOQ_OE_POS = 0,
    SYSC_AWO_GPIOR_OE_MASK = (int)0xff00,
    SYSC_AWO_GPIOR_OE_POS = 8,
    SYSC_AWO_GPIOS_OE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOS_OE_POS = 16,
    SYSC_AWO_GPIOT_OE_MASK = (int)0xff000000,
    SYSC_AWO_GPIOT_OE_POS = 24,
};

enum SYSC_AWO_REG_GPUVWX_OE_FIELD
{
    SYSC_AWO_GPIOU_OE_MASK = (int)0xff,
    SYSC_AWO_GPIOU_OE_POS = 0,
    SYSC_AWO_GPIOV_OE_MASK = (int)0xff00,
    SYSC_AWO_GPIOV_OE_POS = 8,
    SYSC_AWO_GPIOW_OE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOW_OE_POS = 16,
    SYSC_AWO_GPIOX_OE_MASK = (int)0xff000000,
    SYSC_AWO_GPIOX_OE_POS = 24,
};

enum SYSC_AWO_REG_GPYZEEFF_OE_FIELD
{
    SYSC_AWO_GPIOY_OE_MASK = (int)0xff,
    SYSC_AWO_GPIOY_OE_POS = 0,
    SYSC_AWO_GPIOZ_OE_MASK = (int)0xff00,
    SYSC_AWO_GPIOZ_OE_POS = 8,
    SYSC_AWO_GPIOEE_OE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOEE_OE_POS = 16,
    SYSC_AWO_GPIOFF_OE_MASK = (int)0xf000000,
    SYSC_AWO_GPIOFF_OE_POS = 24,
};

enum SYSC_AWO_REG_GPAABBCCDD_OE_FIELD
{
    SYSC_AWO_GPIOAA_OE_MASK = (int)0xff,
    SYSC_AWO_GPIOAA_OE_POS = 0,
    SYSC_AWO_GPIOBB_OE_MASK = (int)0xff00,
    SYSC_AWO_GPIOBB_OE_POS = 8,
    SYSC_AWO_GPIOCC_OE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOCC_OE_POS = 16,
    SYSC_AWO_GPIODD_OE_MASK = (int)0x1000000,
    SYSC_AWO_GPIODD_OE_POS = 24,
};

enum SYSC_AWO_REG_GPJTAGMS_OE_FIELD
{
    SYSC_AWO_GPIOJTAGMS_OE_MASK = (int)0x1f,
    SYSC_AWO_GPIOJTAGMS_OE_POS = 0,
    SYSC_AWO_GPIOAIO_OE_MASK = (int)0x1fe0,
    SYSC_AWO_GPIOAIO_OE_POS = 5,
};

enum SYSC_AWO_REG_GPABCD_I_FIELD
{
    SYSC_AWO_GPIOA_I_MASK = (int)0xff,
    SYSC_AWO_GPIOA_I_POS = 0,
    SYSC_AWO_GPIOB_I_MASK = (int)0xff00,
    SYSC_AWO_GPIOB_I_POS = 8,
    SYSC_AWO_GPIOC_I_MASK = (int)0xff0000,
    SYSC_AWO_GPIOC_I_POS = 16,
    SYSC_AWO_GPIOD_I_MASK = (int)0xff000000,
    SYSC_AWO_GPIOD_I_POS = 24,
};

enum SYSC_AWO_REG_GPEFGH_I_FIELD
{
    SYSC_AWO_GPIOE_I_MASK = (int)0xff,
    SYSC_AWO_GPIOE_I_POS = 0,
    SYSC_AWO_GPIOF_I_MASK = (int)0xff00,
    SYSC_AWO_GPIOF_I_POS = 8,
    SYSC_AWO_GPIOG_I_MASK = (int)0xff0000,
    SYSC_AWO_GPIOG_I_POS = 16,
    SYSC_AWO_GPIOH_I_MASK = (int)0xf000000,
    SYSC_AWO_GPIOH_I_POS = 24,
};

enum SYSC_AWO_REG_GPIJKL_I_FIELD
{
    SYSC_AWO_GPIOI_I_MASK = (int)0xff,
    SYSC_AWO_GPIOI_I_POS = 0,
    SYSC_AWO_GPIOJ_I_MASK = (int)0xff00,
    SYSC_AWO_GPIOJ_I_POS = 8,
    SYSC_AWO_GPIOK_I_MASK = (int)0xff0000,
    SYSC_AWO_GPIOK_I_POS = 16,
    SYSC_AWO_GPIOL_I_MASK = (int)0xff000000,
    SYSC_AWO_GPIOL_I_POS = 24,
};

enum SYSC_AWO_REG_GPMNOP_I_FIELD
{
    SYSC_AWO_GPIOM_I_MASK = (int)0xff,
    SYSC_AWO_GPIOM_I_POS = 0,
    SYSC_AWO_GPION_I_MASK = (int)0xff00,
    SYSC_AWO_GPION_I_POS = 8,
    SYSC_AWO_GPIOO_I_MASK = (int)0xff0000,
    SYSC_AWO_GPIOO_I_POS = 16,
    SYSC_AWO_GPIOP_I_MASK = (int)0xff000000,
    SYSC_AWO_GPIOP_I_POS = 24,
};

enum SYSC_AWO_REG_GPQRST_I_FIELD
{
    SYSC_AWO_GPIOQ_I_MASK = (int)0xff,
    SYSC_AWO_GPIOQ_I_POS = 0,
    SYSC_AWO_GPIOR_I_MASK = (int)0xff00,
    SYSC_AWO_GPIOR_I_POS = 8,
    SYSC_AWO_GPIOS_I_MASK = (int)0xff0000,
    SYSC_AWO_GPIOS_I_POS = 16,
    SYSC_AWO_GPIOT_I_MASK = (int)0xff000000,
    SYSC_AWO_GPIOT_I_POS = 24,
};

enum SYSC_AWO_REG_GPUVWX_I_FIELD
{
    SYSC_AWO_GPIOU_I_MASK = (int)0xff,
    SYSC_AWO_GPIOU_I_POS = 0,
    SYSC_AWO_GPIOV_I_MASK = (int)0xff00,
    SYSC_AWO_GPIOV_I_POS = 8,
    SYSC_AWO_GPIOW_I_MASK = (int)0xff0000,
    SYSC_AWO_GPIOW_I_POS = 16,
    SYSC_AWO_GPIOX_I_MASK = (int)0xff000000,
    SYSC_AWO_GPIOX_I_POS = 24,
};

enum SYSC_AWO_REG_GPYZEEFF_I_FIELD
{
    SYSC_AWO_GPIOY_I_MASK = (int)0xff,
    SYSC_AWO_GPIOY_I_POS = 0,
    SYSC_AWO_GPIOZ_I_MASK = (int)0xff00,
    SYSC_AWO_GPIOZ_I_POS = 8,
    SYSC_AWO_GPIOEE_I_MASK = (int)0xff0000,
    SYSC_AWO_GPIOEE_I_POS = 16,
    SYSC_AWO_GPIOFF_I_MASK = (int)0xf000000,
    SYSC_AWO_GPIOFF_I_POS = 24,
};

enum SYSC_AWO_REG_GPAABBCCDD_I_FIELD
{
    SYSC_AWO_GPIOAA_I_MASK = (int)0xff,
    SYSC_AWO_GPIOAA_I_POS = 0,
    SYSC_AWO_GPIOBB_I_MASK = (int)0xff00,
    SYSC_AWO_GPIOBB_I_POS = 8,
    SYSC_AWO_GPIOCC_I_MASK = (int)0xff0000,
    SYSC_AWO_GPIOCC_I_POS = 16,
    SYSC_AWO_GPIODD_I_MASK = (int)0x1000000,
    SYSC_AWO_GPIODD_I_POS = 24,
};

enum SYSC_AWO_REG_GPJTAGMS_I_FIELD
{
    SYSC_AWO_GPIOJTAGMS_I_MASK = (int)0x1f,
    SYSC_AWO_GPIOJTAGMS_I_POS = 0,
    SYSC_AWO_GPIOAIO_I_MASK = (int)0x1fe0,
    SYSC_AWO_GPIOAIO_I_POS = 5,
    SYSC_AWO_TSPRST_I_MASK = (int)0x2000,
    SYSC_AWO_TSPRST_I_POS = 13,
};

enum SYSC_AWO_REG_GPABCD_IE_FIELD
{
    SYSC_AWO_GPIOA_IE_MASK = (int)0xff,
    SYSC_AWO_GPIOA_IE_POS = 0,
    SYSC_AWO_GPIOB_IE_MASK = (int)0xff00,
    SYSC_AWO_GPIOB_IE_POS = 8,
    SYSC_AWO_GPIOC_IE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOC_IE_POS = 16,
    SYSC_AWO_GPIOD_IE_MASK = (int)0xff000000,
    SYSC_AWO_GPIOD_IE_POS = 24,
};

enum SYSC_AWO_REG_GPEFGH_IE_FIELD
{
    SYSC_AWO_GPIOE_IE_MASK = (int)0xff,
    SYSC_AWO_GPIOE_IE_POS = 0,
    SYSC_AWO_GPIOF_IE_MASK = (int)0xff00,
    SYSC_AWO_GPIOF_IE_POS = 8,
    SYSC_AWO_GPIOG_IE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOG_IE_POS = 16,
    SYSC_AWO_GPIOH_IE_MASK = (int)0xff000000,
    SYSC_AWO_GPIOH_IE_POS = 24,
};

enum SYSC_AWO_REG_GPIJKL_IE_FIELD
{
    SYSC_AWO_GPIOI_IE_MASK = (int)0xff,
    SYSC_AWO_GPIOI_IE_POS = 0,
    SYSC_AWO_GPIOJ_IE_MASK = (int)0xff00,
    SYSC_AWO_GPIOJ_IE_POS = 8,
    SYSC_AWO_GPIOK_IE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOK_IE_POS = 16,
    SYSC_AWO_GPIOL_IE_MASK = (int)0xff000000,
    SYSC_AWO_GPIOL_IE_POS = 24,
};

enum SYSC_AWO_REG_GPMNOP_IE_FIELD
{
    SYSC_AWO_GPIOM_IE_MASK = (int)0xff,
    SYSC_AWO_GPIOM_IE_POS = 0,
    SYSC_AWO_GPION_IE_MASK = (int)0xff00,
    SYSC_AWO_GPION_IE_POS = 8,
    SYSC_AWO_GPIOO_IE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOO_IE_POS = 16,
    SYSC_AWO_GPIOP_IE_MASK = (int)0xff000000,
    SYSC_AWO_GPIOP_IE_POS = 24,
};

enum SYSC_AWO_REG_GPQRST_IE_FIELD
{
    SYSC_AWO_GPIOQ_IE_MASK = (int)0xff,
    SYSC_AWO_GPIOQ_IE_POS = 0,
    SYSC_AWO_GPIOR_IE_MASK = (int)0xff00,
    SYSC_AWO_GPIOR_IE_POS = 8,
    SYSC_AWO_GPIOS_IE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOS_IE_POS = 16,
    SYSC_AWO_GPIOT_IE_MASK = (int)0xff000000,
    SYSC_AWO_GPIOT_IE_POS = 24,
};

enum SYSC_AWO_REG_GPUVWX_IE_FIELD
{
    SYSC_AWO_GPIOU_IE_MASK = (int)0xff,
    SYSC_AWO_GPIOU_IE_POS = 0,
    SYSC_AWO_GPIOV_IE_MASK = (int)0xff00,
    SYSC_AWO_GPIOV_IE_POS = 8,
    SYSC_AWO_GPIOW_IE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOW_IE_POS = 16,
    SYSC_AWO_GPIOX_IE_MASK = (int)0xff000000,
    SYSC_AWO_GPIOX_IE_POS = 24,
};

enum SYSC_AWO_REG_GPYZEEFF_IE_FIELD
{
    SYSC_AWO_GPIOY_IE_MASK = (int)0xff,
    SYSC_AWO_GPIOY_IE_POS = 0,
    SYSC_AWO_GPIOZ_IE_MASK = (int)0xff00,
    SYSC_AWO_GPIOZ_IE_POS = 8,
    SYSC_AWO_GPIOEE_IE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOEE_IE_POS = 16,
    SYSC_AWO_GPIOFF_IE_MASK = (int)0xf000000,
    SYSC_AWO_GPIOFF_IE_POS = 24,
};

enum SYSC_AWO_REG_GPAABBCCDD_IE_FIELD
{
    SYSC_AWO_GPIOAA_IE_MASK = (int)0xff,
    SYSC_AWO_GPIOAA_IE_POS = 0,
    SYSC_AWO_GPIOBB_IE_MASK = (int)0xff00,
    SYSC_AWO_GPIOBB_IE_POS = 8,
    SYSC_AWO_GPIOCC_IE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOCC_IE_POS = 16,
    SYSC_AWO_GPIODD_IE_MASK = (int)0xff000000,
    SYSC_AWO_GPIODD_IE_POS = 24,
};

enum SYSC_AWO_REG_GPJTAGMS_IE_FIELD
{
    SYSC_AWO_GPIOJTAGMS_IE_MASK = (int)0x1f,
    SYSC_AWO_GPIOJTAGMS_IE_POS = 0,
    SYSC_AWO_GPIOAIO_IE_MASK = (int)0x1fe0,
    SYSC_AWO_GPIOAIO_IE_POS = 5,
};

enum SYSC_AWO_REG_GPABCD_REN_FIELD
{
    SYSC_AWO_GPIOA_REN_MASK = (int)0xff,
    SYSC_AWO_GPIOA_REN_POS = 0,
    SYSC_AWO_GPIOB_REN_MASK = (int)0xff00,
    SYSC_AWO_GPIOB_REN_POS = 8,
    SYSC_AWO_GPIOC_REN_MASK = (int)0xff0000,
    SYSC_AWO_GPIOC_REN_POS = 16,
    SYSC_AWO_GPIOD_REN_MASK = (int)0xff000000,
    SYSC_AWO_GPIOD_REN_POS = 24,
};

enum SYSC_AWO_REG_GPEFGH_REN_FIELD
{
    SYSC_AWO_GPIOE_REN_MASK = (int)0xff,
    SYSC_AWO_GPIOE_REN_POS = 0,
    SYSC_AWO_GPIOF_REN_MASK = (int)0xff00,
    SYSC_AWO_GPIOF_REN_POS = 8,
    SYSC_AWO_GPIOG_REN_MASK = (int)0xff0000,
    SYSC_AWO_GPIOG_REN_POS = 16,
    SYSC_AWO_GPIOH_REN_MASK = (int)0xff000000,
    SYSC_AWO_GPIOH_REN_POS = 24,
};

enum SYSC_AWO_REG_GPIJKL_REN_FIELD
{
    SYSC_AWO_GPIOI_REN_MASK = (int)0xff,
    SYSC_AWO_GPIOI_REN_POS = 0,
    SYSC_AWO_GPIOJ_REN_MASK = (int)0xff00,
    SYSC_AWO_GPIOJ_REN_POS = 8,
    SYSC_AWO_GPIOK_REN_MASK = (int)0xff0000,
    SYSC_AWO_GPIOK_REN_POS = 16,
    SYSC_AWO_GPIOL_REN_MASK = (int)0xff000000,
    SYSC_AWO_GPIOL_REN_POS = 24,
};

enum SYSC_AWO_REG_GPMNOP_REN_FIELD
{
    SYSC_AWO_GPIOM_REN_MASK = (int)0xff,
    SYSC_AWO_GPIOM_REN_POS = 0,
    SYSC_AWO_GPION_REN_MASK = (int)0xff00,
    SYSC_AWO_GPION_REN_POS = 8,
    SYSC_AWO_GPIOO_REN_MASK = (int)0xff0000,
    SYSC_AWO_GPIOO_REN_POS = 16,
    SYSC_AWO_GPIOP_REN_MASK = (int)0xff000000,
    SYSC_AWO_GPIOP_REN_POS = 24,
};

enum SYSC_AWO_REG_GPQRST_REN_FIELD
{
    SYSC_AWO_GPIOQ_REN_MASK = (int)0xff,
    SYSC_AWO_GPIOQ_REN_POS = 0,
    SYSC_AWO_GPIOR_REN_MASK = (int)0xff00,
    SYSC_AWO_GPIOR_REN_POS = 8,
    SYSC_AWO_GPIOS_REN_MASK = (int)0xff0000,
    SYSC_AWO_GPIOS_REN_POS = 16,
    SYSC_AWO_GPIOT_REN_MASK = (int)0xff000000,
    SYSC_AWO_GPIOT_REN_POS = 24,
};

enum SYSC_AWO_REG_GPUVWX_REN_FIELD
{
    SYSC_AWO_GPIOU_REN_MASK = (int)0xff,
    SYSC_AWO_GPIOU_REN_POS = 0,
    SYSC_AWO_GPIOV_REN_MASK = (int)0xff00,
    SYSC_AWO_GPIOV_REN_POS = 8,
    SYSC_AWO_GPIOW_REN_MASK = (int)0xff0000,
    SYSC_AWO_GPIOW_REN_POS = 16,
    SYSC_AWO_GPIOX_REN_MASK = (int)0xff000000,
    SYSC_AWO_GPIOX_REN_POS = 24,
};

enum SYSC_AWO_REG_GPYZEEFF_REN_FIELD
{
    SYSC_AWO_GPIOY_REN_MASK = (int)0xff,
    SYSC_AWO_GPIOY_REN_POS = 0,
    SYSC_AWO_GPIOZ_REN_MASK = (int)0xff00,
    SYSC_AWO_GPIOZ_REN_POS = 8,
    SYSC_AWO_GPIOEE_REN_MASK = (int)0xff0000,
    SYSC_AWO_GPIOEE_REN_POS = 16,
    SYSC_AWO_GPIOFF_REN_MASK = (int)0xf000000,
    SYSC_AWO_GPIOFF_REN_POS = 24,
};

enum SYSC_AWO_REG_GPAABBCCDD_REN_FIELD
{
    SYSC_AWO_GPIOAA_REN_MASK = (int)0xff,
    SYSC_AWO_GPIOAA_REN_POS = 0,
    SYSC_AWO_GPIOBB_REN_MASK = (int)0xff00,
    SYSC_AWO_GPIOBB_REN_POS = 8,
    SYSC_AWO_GPIOCC_REN_MASK = (int)0xff0000,
    SYSC_AWO_GPIOCC_REN_POS = 16,
    SYSC_AWO_GPIODD_REN_MASK = (int)0xff000000,
    SYSC_AWO_GPIODD_REN_POS = 24,
};

enum SYSC_AWO_REG_GPJTAGMS_REN_FIELD
{
    SYSC_AWO_GPIOJTAGMS_REN_MASK = (int)0x1f,
    SYSC_AWO_GPIOJTAGMS_REN_POS = 0,
    SYSC_AWO_GPIOAIO_REN_MASK = (int)0x1fe0,
    SYSC_AWO_GPIOAIO_REN_POS = 5,
};

enum SYSC_AWO_REG_GPABCD_ODE_FIELD
{
    SYSC_AWO_GPIOA_ODE_MASK = (int)0xff,
    SYSC_AWO_GPIOA_ODE_POS = 0,
    SYSC_AWO_GPIOB_ODE_MASK = (int)0xff00,
    SYSC_AWO_GPIOB_ODE_POS = 8,
    SYSC_AWO_GPIOC_ODE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOC_ODE_POS = 16,
    SYSC_AWO_GPIOD_ODE_MASK = (int)0xff000000,
    SYSC_AWO_GPIOD_ODE_POS = 24,
};

enum SYSC_AWO_REG_GPEFGH_ODE_FIELD
{
    SYSC_AWO_GPIOE_ODE_MASK = (int)0xff,
    SYSC_AWO_GPIOE_ODE_POS = 0,
    SYSC_AWO_GPIOF_ODE_MASK = (int)0xff00,
    SYSC_AWO_GPIOF_ODE_POS = 8,
    SYSC_AWO_GPIOG_ODE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOG_ODE_POS = 16,
    SYSC_AWO_GPIOH_ODE_MASK = (int)0xff000000,
    SYSC_AWO_GPIOH_ODE_POS = 24,
};

enum SYSC_AWO_REG_GPIJKL_ODE_FIELD
{
    SYSC_AWO_GPIOI_ODE_MASK = (int)0xff,
    SYSC_AWO_GPIOI_ODE_POS = 0,
    SYSC_AWO_GPIOJ_ODE_MASK = (int)0xff00,
    SYSC_AWO_GPIOJ_ODE_POS = 8,
    SYSC_AWO_GPIOK_ODE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOK_ODE_POS = 16,
    SYSC_AWO_GPIOL_ODE_MASK = (int)0xff000000,
    SYSC_AWO_GPIOL_ODE_POS = 24,
};

enum SYSC_AWO_REG_GPMNOP_ODE_FIELD
{
    SYSC_AWO_GPIOM_ODE_MASK = (int)0xff,
    SYSC_AWO_GPIOM_ODE_POS = 0,
    SYSC_AWO_GPION_ODE_MASK = (int)0xff00,
    SYSC_AWO_GPION_ODE_POS = 8,
    SYSC_AWO_GPIOO_ODE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOO_ODE_POS = 16,
    SYSC_AWO_GPIOP_ODE_MASK = (int)0xff000000,
    SYSC_AWO_GPIOP_ODE_POS = 24,
};

enum SYSC_AWO_REG_GPQRST_ODE_FIELD
{
    SYSC_AWO_GPIOQ_ODE_MASK = (int)0xff,
    SYSC_AWO_GPIOQ_ODE_POS = 0,
    SYSC_AWO_GPIOR_ODE_MASK = (int)0xff00,
    SYSC_AWO_GPIOR_ODE_POS = 8,
    SYSC_AWO_GPIOS_ODE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOS_ODE_POS = 16,
    SYSC_AWO_GPIOT_ODE_MASK = (int)0xff000000,
    SYSC_AWO_GPIOT_ODE_POS = 24,
};

enum SYSC_AWO_REG_GPUVWX_ODE_FIELD
{
    SYSC_AWO_GPIOU_ODE_MASK = (int)0xff,
    SYSC_AWO_GPIOU_ODE_POS = 0,
    SYSC_AWO_GPIOV_ODE_MASK = (int)0xff00,
    SYSC_AWO_GPIOV_ODE_POS = 8,
    SYSC_AWO_GPIOW_ODE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOW_ODE_POS = 16,
    SYSC_AWO_GPIOX_ODE_MASK = (int)0xff000000,
    SYSC_AWO_GPIOX_ODE_POS = 24,
};

enum SYSC_AWO_REG_GPYZEEFF_ODE_FIELD
{
    SYSC_AWO_GPIOY_ODE_MASK = (int)0xff,
    SYSC_AWO_GPIOY_ODE_POS = 0,
    SYSC_AWO_GPIOZ_ODE_MASK = (int)0xff00,
    SYSC_AWO_GPIOZ_ODE_POS = 8,
    SYSC_AWO_GPIOEE_ODE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOEE_ODE_POS = 16,
    SYSC_AWO_GPIOFF_ODE_MASK = (int)0xf000000,
    SYSC_AWO_GPIOFF_ODE_POS = 24,
};

enum SYSC_AWO_REG_GPAABBCCDD_ODE_FIELD
{
    SYSC_AWO_GPIOAA_ODE_MASK = (int)0xff,
    SYSC_AWO_GPIOAA_ODE_POS = 0,
    SYSC_AWO_GPIOBB_ODE_MASK = (int)0xff00,
    SYSC_AWO_GPIOBB_ODE_POS = 8,
    SYSC_AWO_GPIOCC_ODE_MASK = (int)0xff0000,
    SYSC_AWO_GPIOCC_ODE_POS = 16,
    SYSC_AWO_GPIODD_ODE_MASK = (int)0xff000000,
    SYSC_AWO_GPIODD_ODE_POS = 24,
};

enum SYSC_AWO_REG_GPJTAGMS_ODE_FIELD
{
    SYSC_AWO_GPIOJTAGMS_ODE_MASK = (int)0x1f,
    SYSC_AWO_GPIOJTAGMS_ODE_POS = 0,
    SYSC_AWO_GPIOAIO_ODE_MASK = (int)0x1fe0,
    SYSC_AWO_GPIOAIO_ODE_POS = 5,
};

enum SYSC_AWO_REG_GPABCD_PU_FIELD
{
    SYSC_AWO_GPIOA_PU_MASK = (int)0xff,
    SYSC_AWO_GPIOA_PU_POS = 0,
    SYSC_AWO_GPIOB_PU_MASK = (int)0xff00,
    SYSC_AWO_GPIOB_PU_POS = 8,
    SYSC_AWO_GPIOC_PU_MASK = (int)0xff0000,
    SYSC_AWO_GPIOC_PU_POS = 16,
    SYSC_AWO_GPIOD_PU_MASK = (int)0xff000000,
    SYSC_AWO_GPIOD_PU_POS = 24,
};

enum SYSC_AWO_REG_GPEFGH_PU_FIELD
{
    SYSC_AWO_GPIOE_PU_MASK = (int)0xff,
    SYSC_AWO_GPIOE_PU_POS = 0,
    SYSC_AWO_GPIOF_PU_MASK = (int)0xff00,
    SYSC_AWO_GPIOF_PU_POS = 8,
    SYSC_AWO_GPIOG_PU_MASK = (int)0xff0000,
    SYSC_AWO_GPIOG_PU_POS = 16,
    SYSC_AWO_GPIOH_PU_MASK = (int)0xff000000,
    SYSC_AWO_GPIOH_PU_POS = 24,
};

enum SYSC_AWO_REG_GPIL_PU_FIELD
{
    SYSC_AWO_GPIOI_PU_MASK = (int)0xff,
    SYSC_AWO_GPIOI_PU_POS = 0,
    SYSC_AWO_GPIOL_PU_MASK = (int)0xff00,
    SYSC_AWO_GPIOL_PU_POS = 8,
};

enum SYSC_AWO_REG_GPJ_PU_FIELD
{
    SYSC_AWO_GPIOJ_PU_MASK = (int)0xffffff,
    SYSC_AWO_GPIOJ_PU_POS = 0,
};

enum SYSC_AWO_REG_GPK_PU_FIELD
{
    SYSC_AWO_GPIOK_PU_MASK = (int)0xffffff,
    SYSC_AWO_GPIOK_PU_POS = 0,
};

enum SYSC_AWO_REG_GPMNOP_PU_FIELD
{
    SYSC_AWO_GPIOM_PU_MASK = (int)0xff,
    SYSC_AWO_GPIOM_PU_POS = 0,
    SYSC_AWO_GPION_PU_MASK = (int)0xff00,
    SYSC_AWO_GPION_PU_POS = 8,
    SYSC_AWO_GPIOO_PU_MASK = (int)0xff0000,
    SYSC_AWO_GPIOO_PU_POS = 16,
    SYSC_AWO_GPIOP_PU_MASK = (int)0xff000000,
    SYSC_AWO_GPIOP_PU_POS = 24,
};

enum SYSC_AWO_REG_GPQRST_PU_FIELD
{
    SYSC_AWO_GPIOQ_PU_MASK = (int)0xff,
    SYSC_AWO_GPIOQ_PU_POS = 0,
    SYSC_AWO_GPIOR_PU_MASK = (int)0xff00,
    SYSC_AWO_GPIOR_PU_POS = 8,
    SYSC_AWO_GPIOS_PU_MASK = (int)0xff0000,
    SYSC_AWO_GPIOS_PU_POS = 16,
    SYSC_AWO_GPIOT_PU_MASK = (int)0xff000000,
    SYSC_AWO_GPIOT_PU_POS = 24,
};

enum SYSC_AWO_REG_GPUVWX_PU_FIELD
{
    SYSC_AWO_GPIOU_PU_MASK = (int)0xff,
    SYSC_AWO_GPIOU_PU_POS = 0,
    SYSC_AWO_GPIOV_PU_MASK = (int)0xff00,
    SYSC_AWO_GPIOV_PU_POS = 8,
    SYSC_AWO_GPIOW_PU_MASK = (int)0xff0000,
    SYSC_AWO_GPIOW_PU_POS = 16,
    SYSC_AWO_GPIOX_PU_MASK = (int)0xff000000,
    SYSC_AWO_GPIOX_PU_POS = 24,
};

enum SYSC_AWO_REG_GPYZEEFF_PU_FIELD
{
    SYSC_AWO_GPIOY_PU_MASK = (int)0xff,
    SYSC_AWO_GPIOY_PU_POS = 0,
    SYSC_AWO_GPIOZ_PU_MASK = (int)0xff00,
    SYSC_AWO_GPIOZ_PU_POS = 8,
    SYSC_AWO_GPIOEE_PU_MASK = (int)0xff0000,
    SYSC_AWO_GPIOEE_PU_POS = 16,
    SYSC_AWO_GPIOFF_PU_MASK = (int)0xf000000,
    SYSC_AWO_GPIOFF_PU_POS = 24,
};

enum SYSC_AWO_REG_GPAABBCCDD_PU_FIELD
{
    SYSC_AWO_GPIOAA_PU_MASK = (int)0xff,
    SYSC_AWO_GPIOAA_PU_POS = 0,
    SYSC_AWO_GPIOBB_PU_MASK = (int)0xff00,
    SYSC_AWO_GPIOBB_PU_POS = 8,
    SYSC_AWO_GPIOCC_PU_MASK = (int)0xff0000,
    SYSC_AWO_GPIOCC_PU_POS = 16,
    SYSC_AWO_GPIODD_PU_MASK = (int)0xff000000,
    SYSC_AWO_GPIODD_PU_POS = 24,
};

enum SYSC_AWO_REG_GPJTAGMS_PU_FIELD
{
    SYSC_AWO_GPIOJTAGMS_PU_MASK = (int)0x1f,
    SYSC_AWO_GPIOJTAGMS_PU_POS = 0,
    SYSC_AWO_GPIOAIO_PU_MASK = (int)0x1fe0,
    SYSC_AWO_GPIOAIO_PU_POS = 5,
};

enum SYSC_AWO_REG_GPABCD_PD_FIELD
{
    SYSC_AWO_GPIOA_PD_MASK = (int)0xff,
    SYSC_AWO_GPIOA_PD_POS = 0,
    SYSC_AWO_GPIOB_PD_MASK = (int)0xff00,
    SYSC_AWO_GPIOB_PD_POS = 8,
    SYSC_AWO_GPIOC_PD_MASK = (int)0xff0000,
    SYSC_AWO_GPIOC_PD_POS = 16,
    SYSC_AWO_GPIOD_PD_MASK = (int)0xff000000,
    SYSC_AWO_GPIOD_PD_POS = 24,
};

enum SYSC_AWO_REG_GPEFGH_PD_FIELD
{
    SYSC_AWO_GPIOE_PD_MASK = (int)0xff,
    SYSC_AWO_GPIOE_PD_POS = 0,
    SYSC_AWO_GPIOF_PD_MASK = (int)0xff00,
    SYSC_AWO_GPIOF_PD_POS = 8,
    SYSC_AWO_GPIOG_PD_MASK = (int)0xff0000,
    SYSC_AWO_GPIOG_PD_POS = 16,
    SYSC_AWO_GPIOH_PD_MASK = (int)0xff000000,
    SYSC_AWO_GPIOH_PD_POS = 24,
};

enum SYSC_AWO_REG_GPIJKL_PD_FIELD
{
    SYSC_AWO_GPIOI_PD_MASK = (int)0xff,
    SYSC_AWO_GPIOI_PD_POS = 0,
    SYSC_AWO_GPIOJ_PD_MASK = (int)0xff00,
    SYSC_AWO_GPIOJ_PD_POS = 8,
    SYSC_AWO_GPIOK_PD_MASK = (int)0xff0000,
    SYSC_AWO_GPIOK_PD_POS = 16,
    SYSC_AWO_GPIOL_PD_MASK = (int)0xff000000,
    SYSC_AWO_GPIOL_PD_POS = 24,
};

enum SYSC_AWO_REG_GPMNOP_PD_FIELD
{
    SYSC_AWO_GPIOM_PD_MASK = (int)0xff,
    SYSC_AWO_GPIOM_PD_POS = 0,
    SYSC_AWO_GPION_PD_MASK = (int)0xff00,
    SYSC_AWO_GPION_PD_POS = 8,
    SYSC_AWO_GPIOO_PD_MASK = (int)0xff0000,
    SYSC_AWO_GPIOO_PD_POS = 16,
    SYSC_AWO_GPIOP_PD_MASK = (int)0xff000000,
    SYSC_AWO_GPIOP_PD_POS = 24,
};

enum SYSC_AWO_REG_GPQRST_PD_FIELD
{
    SYSC_AWO_GPIOQ_PD_MASK = (int)0xff,
    SYSC_AWO_GPIOQ_PD_POS = 0,
    SYSC_AWO_GPIOR_PD_MASK = (int)0xff00,
    SYSC_AWO_GPIOR_PD_POS = 8,
    SYSC_AWO_GPIOS_PD_MASK = (int)0xff0000,
    SYSC_AWO_GPIOS_PD_POS = 16,
    SYSC_AWO_GPIOT_PD_MASK = (int)0xff000000,
    SYSC_AWO_GPIOT_PD_POS = 24,
};

enum SYSC_AWO_REG_GPUVWX_PD_FIELD
{
    SYSC_AWO_GPIOU_PD_MASK = (int)0xff,
    SYSC_AWO_GPIOU_PD_POS = 0,
    SYSC_AWO_GPIOV_PD_MASK = (int)0xff00,
    SYSC_AWO_GPIOV_PD_POS = 8,
    SYSC_AWO_GPIOW_PD_MASK = (int)0xff0000,
    SYSC_AWO_GPIOW_PD_POS = 16,
    SYSC_AWO_GPIOX_PD_MASK = (int)0xff000000,
    SYSC_AWO_GPIOX_PD_POS = 24,
};

enum SYSC_AWO_REG_GPYZEEFF_PD_FIELD
{
    SYSC_AWO_GPIOY_PD_MASK = (int)0xff,
    SYSC_AWO_GPIOY_PD_POS = 0,
    SYSC_AWO_GPIOZ_PD_MASK = (int)0xff00,
    SYSC_AWO_GPIOZ_PD_POS = 8,
    SYSC_AWO_GPIOEE_PD_MASK = (int)0xff0000,
    SYSC_AWO_GPIOEE_PD_POS = 16,
    SYSC_AWO_GPIOFF_PD_MASK = (int)0xf000000,
    SYSC_AWO_GPIOFF_PD_POS = 24,
};

enum SYSC_AWO_REG_GPAABBCCDD_PD_FIELD
{
    SYSC_AWO_GPIOAA_PD_MASK = (int)0xff,
    SYSC_AWO_GPIOAA_PD_POS = 0,
    SYSC_AWO_GPIOBB_PD_MASK = (int)0xff00,
    SYSC_AWO_GPIOBB_PD_POS = 8,
    SYSC_AWO_GPIOCC_PD_MASK = (int)0xff0000,
    SYSC_AWO_GPIOCC_PD_POS = 16,
    SYSC_AWO_GPIODD_PD_MASK = (int)0xff000000,
    SYSC_AWO_GPIODD_PD_POS = 24,
};

enum SYSC_AWO_REG_GPJTAGMS_PD_FIELD
{
    SYSC_AWO_GPIOJTAGMS_PD_MASK = (int)0x1f,
    SYSC_AWO_GPIOJTAGMS_PD_POS = 0,
    SYSC_AWO_GPIOAIO_PD_MASK = (int)0x1fe0,
    SYSC_AWO_GPIOAIO_PD_POS = 5,
};

enum SYSC_AWO_REG_GPABCD_DS0_FIELD
{
    SYSC_AWO_GPIOA_DS0_MASK = (int)0xff,
    SYSC_AWO_GPIOA_DS0_POS = 0,
    SYSC_AWO_GPIOB_DS0_MASK = (int)0xff00,
    SYSC_AWO_GPIOB_DS0_POS = 8,
    SYSC_AWO_GPIOC_DS0_MASK = (int)0xff0000,
    SYSC_AWO_GPIOC_DS0_POS = 16,
    SYSC_AWO_GPIOD_DS0_MASK = (int)0xff000000,
    SYSC_AWO_GPIOD_DS0_POS = 24,
};

enum SYSC_AWO_REG_GPEFGH_DS0_FIELD
{
    SYSC_AWO_GPIOE_DS0_MASK = (int)0xff,
    SYSC_AWO_GPIOE_DS0_POS = 0,
    SYSC_AWO_GPIOF_DS0_MASK = (int)0xff00,
    SYSC_AWO_GPIOF_DS0_POS = 8,
    SYSC_AWO_GPIOG_DS0_MASK = (int)0xff0000,
    SYSC_AWO_GPIOG_DS0_POS = 16,
    SYSC_AWO_GPIOH_DS0_MASK = (int)0xff000000,
    SYSC_AWO_GPIOH_DS0_POS = 24,
};

enum SYSC_AWO_REG_GPIJKL_DS0_FIELD
{
    SYSC_AWO_GPIOI_DS0_MASK = (int)0xff,
    SYSC_AWO_GPIOI_DS0_POS = 0,
    SYSC_AWO_GPIOJ_DS0_MASK = (int)0xff00,
    SYSC_AWO_GPIOJ_DS0_POS = 8,
    SYSC_AWO_GPIOK_DS0_MASK = (int)0xff0000,
    SYSC_AWO_GPIOK_DS0_POS = 16,
    SYSC_AWO_GPIOL_DS0_MASK = (int)0xff000000,
    SYSC_AWO_GPIOL_DS0_POS = 24,
};

enum SYSC_AWO_REG_GPMNOP_DS0_FIELD
{
    SYSC_AWO_GPIOM_DS0_MASK = (int)0xff,
    SYSC_AWO_GPIOM_DS0_POS = 0,
    SYSC_AWO_GPION_DS0_MASK = (int)0xff00,
    SYSC_AWO_GPION_DS0_POS = 8,
    SYSC_AWO_GPIOO_DS0_MASK = (int)0xff0000,
    SYSC_AWO_GPIOO_DS0_POS = 16,
    SYSC_AWO_GPIOP_DS0_MASK = (int)0xff000000,
    SYSC_AWO_GPIOP_DS0_POS = 24,
};

enum SYSC_AWO_REG_GPQRST_DS0_FIELD
{
    SYSC_AWO_GPIOQ_DS0_MASK = (int)0xff,
    SYSC_AWO_GPIOQ_DS0_POS = 0,
    SYSC_AWO_GPIOR_DS0_MASK = (int)0xff00,
    SYSC_AWO_GPIOR_DS0_POS = 8,
    SYSC_AWO_GPIOS_DS0_MASK = (int)0xff0000,
    SYSC_AWO_GPIOS_DS0_POS = 16,
    SYSC_AWO_GPIOT_DS0_MASK = (int)0xff000000,
    SYSC_AWO_GPIOT_DS0_POS = 24,
};

enum SYSC_AWO_REG_GPUVWX_DS0_FIELD
{
    SYSC_AWO_GPIOU_DS0_MASK = (int)0xff,
    SYSC_AWO_GPIOU_DS0_POS = 0,
    SYSC_AWO_GPIOV_DS0_MASK = (int)0xff00,
    SYSC_AWO_GPIOV_DS0_POS = 8,
    SYSC_AWO_GPIOW_DS0_MASK = (int)0xff0000,
    SYSC_AWO_GPIOW_DS0_POS = 16,
    SYSC_AWO_GPIOX_DS0_MASK = (int)0xff000000,
    SYSC_AWO_GPIOX_DS0_POS = 24,
};

enum SYSC_AWO_REG_GPYZEEFF_DS0_FIELD
{
    SYSC_AWO_GPIOY_DS0_MASK = (int)0xff,
    SYSC_AWO_GPIOY_DS0_POS = 0,
    SYSC_AWO_GPIOZ_DS0_MASK = (int)0xff00,
    SYSC_AWO_GPIOZ_DS0_POS = 8,
    SYSC_AWO_GPIOEE_DS0_MASK = (int)0xff0000,
    SYSC_AWO_GPIOEE_DS0_POS = 16,
    SYSC_AWO_GPIOFF_DS0_MASK = (int)0xf000000,
    SYSC_AWO_GPIOFF_DS0_POS = 24,
};

enum SYSC_AWO_REG_GPAABBCCDD_DS0_FIELD
{
    SYSC_AWO_GPIOAA_DS0_MASK = (int)0xff,
    SYSC_AWO_GPIOAA_DS0_POS = 0,
    SYSC_AWO_GPIOBB_DS0_MASK = (int)0xff00,
    SYSC_AWO_GPIOBB_DS0_POS = 8,
    SYSC_AWO_GPIOCC_DS0_MASK = (int)0xff0000,
    SYSC_AWO_GPIOCC_DS0_POS = 16,
    SYSC_AWO_GPIODD_DS0_MASK = (int)0xff000000,
    SYSC_AWO_GPIODD_DS0_POS = 24,
};

enum SYSC_AWO_REG_GPJTAGMS_DS0_FIELD
{
    SYSC_AWO_GPIOJTAGMS_DS0_MASK = (int)0x1f,
    SYSC_AWO_GPIOJTAGMS_DS0_POS = 0,
    SYSC_AWO_GPIOAIO_DS0_MASK = (int)0x1fe0,
    SYSC_AWO_GPIOAIO_DS0_POS = 5,
};

enum SYSC_AWO_REG_GPABCD_DS1_FIELD
{
    SYSC_AWO_GPIOA_DS1_MASK = (int)0xff,
    SYSC_AWO_GPIOA_DS1_POS = 0,
    SYSC_AWO_GPIOB_DS1_MASK = (int)0xff00,
    SYSC_AWO_GPIOB_DS1_POS = 8,
    SYSC_AWO_GPIOC_DS1_MASK = (int)0xff0000,
    SYSC_AWO_GPIOC_DS1_POS = 16,
    SYSC_AWO_GPIOD_DS1_MASK = (int)0xff000000,
    SYSC_AWO_GPIOD_DS1_POS = 24,
};

enum SYSC_AWO_REG_GPEFGH_DS1_FIELD
{
    SYSC_AWO_GPIOE_DS1_MASK = (int)0xff,
    SYSC_AWO_GPIOE_DS1_POS = 0,
    SYSC_AWO_GPIOF_DS1_MASK = (int)0xff00,
    SYSC_AWO_GPIOF_DS1_POS = 8,
    SYSC_AWO_GPIOG_DS1_MASK = (int)0xff0000,
    SYSC_AWO_GPIOG_DS1_POS = 16,
    SYSC_AWO_GPIOH_DS1_MASK = (int)0xff000000,
    SYSC_AWO_GPIOH_DS1_POS = 24,
};

enum SYSC_AWO_REG_GPIJKL_DS1_FIELD
{
    SYSC_AWO_GPIOI_DS1_MASK = (int)0xff,
    SYSC_AWO_GPIOI_DS1_POS = 0,
    SYSC_AWO_GPIOJ_DS1_MASK = (int)0xff00,
    SYSC_AWO_GPIOJ_DS1_POS = 8,
    SYSC_AWO_GPIOK_DS1_MASK = (int)0xff0000,
    SYSC_AWO_GPIOK_DS1_POS = 16,
    SYSC_AWO_GPIOL_DS1_MASK = (int)0xff000000,
    SYSC_AWO_GPIOL_DS1_POS = 24,
};

enum SYSC_AWO_REG_GPMNOP_DS1_FIELD
{
    SYSC_AWO_GPIOM_DS1_MASK = (int)0xff,
    SYSC_AWO_GPIOM_DS1_POS = 0,
    SYSC_AWO_GPION_DS1_MASK = (int)0xff00,
    SYSC_AWO_GPION_DS1_POS = 8,
    SYSC_AWO_GPIOO_DS1_MASK = (int)0xff0000,
    SYSC_AWO_GPIOO_DS1_POS = 16,
    SYSC_AWO_GPIOP_DS1_MASK = (int)0xff000000,
    SYSC_AWO_GPIOP_DS1_POS = 24,
};

enum SYSC_AWO_REG_GPQRST_DS1_FIELD
{
    SYSC_AWO_GPIOQ_DS1_MASK = (int)0xff,
    SYSC_AWO_GPIOQ_DS1_POS = 0,
    SYSC_AWO_GPIOR_DS1_MASK = (int)0xff00,
    SYSC_AWO_GPIOR_DS1_POS = 8,
    SYSC_AWO_GPIOS_DS1_MASK = (int)0xff0000,
    SYSC_AWO_GPIOS_DS1_POS = 16,
    SYSC_AWO_GPIOT_DS1_MASK = (int)0xff000000,
    SYSC_AWO_GPIOT_DS1_POS = 24,
};

enum SYSC_AWO_REG_GPUVWX_DS1_FIELD
{
    SYSC_AWO_GPIOU_DS1_MASK = (int)0xff,
    SYSC_AWO_GPIOU_DS1_POS = 0,
    SYSC_AWO_GPIOV_DS1_MASK = (int)0xff00,
    SYSC_AWO_GPIOV_DS1_POS = 8,
    SYSC_AWO_GPIOW_DS1_MASK = (int)0xff0000,
    SYSC_AWO_GPIOW_DS1_POS = 16,
    SYSC_AWO_GPIOX_DS1_MASK = (int)0xff000000,
    SYSC_AWO_GPIOX_DS1_POS = 24,
};

enum SYSC_AWO_REG_GPYZEEFF_DS1_FIELD
{
    SYSC_AWO_GPIOY_DS1_MASK = (int)0xff,
    SYSC_AWO_GPIOY_DS1_POS = 0,
    SYSC_AWO_GPIOZ_DS1_MASK = (int)0xff00,
    SYSC_AWO_GPIOZ_DS1_POS = 8,
    SYSC_AWO_GPIOEE_DS1_MASK = (int)0xff0000,
    SYSC_AWO_GPIOEE_DS1_POS = 16,
    SYSC_AWO_GPIOFF_DS1_MASK = (int)0xf000000,
    SYSC_AWO_GPIOFF_DS1_POS = 24,
};

enum SYSC_AWO_REG_GPAABBCCDD_DS1_FIELD
{
    SYSC_AWO_GPIOAA_DS1_MASK = (int)0xff,
    SYSC_AWO_GPIOAA_DS1_POS = 0,
    SYSC_AWO_GPIOBB_DS1_MASK = (int)0xff00,
    SYSC_AWO_GPIOBB_DS1_POS = 8,
    SYSC_AWO_GPIOCC_DS1_MASK = (int)0xff0000,
    SYSC_AWO_GPIOCC_DS1_POS = 16,
    SYSC_AWO_GPIODD_DS1_MASK = (int)0xff000000,
    SYSC_AWO_GPIODD_DS1_POS = 24,
};

enum SYSC_AWO_REG_GPJTAGMS_DS1_FIELD
{
    SYSC_AWO_GPIOJTAGMS_DS1_MASK = (int)0x1f,
    SYSC_AWO_GPIOJTAGMS_DS1_POS = 0,
    SYSC_AWO_GPIOAIO_DS1_MASK = (int)0x1fe0,
    SYSC_AWO_GPIOAIO_DS1_POS = 5,
};

enum SYSC_AWO_REG_GPABCD_DS2_FIELD
{
    SYSC_AWO_GPIOA_DS2_MASK = (int)0xff,
    SYSC_AWO_GPIOA_DS2_POS = 0,
    SYSC_AWO_GPIOB_DS2_MASK = (int)0xff00,
    SYSC_AWO_GPIOB_DS2_POS = 8,
    SYSC_AWO_GPIOC_DS2_MASK = (int)0xff0000,
    SYSC_AWO_GPIOC_DS2_POS = 16,
    SYSC_AWO_GPIOD_DS2_MASK = (int)0xff000000,
    SYSC_AWO_GPIOD_DS2_POS = 24,
};

enum SYSC_AWO_REG_GPEFGH_DS2_FIELD
{
    SYSC_AWO_GPIOE_DS2_MASK = (int)0xff,
    SYSC_AWO_GPIOE_DS2_POS = 0,
    SYSC_AWO_GPIOF_DS2_MASK = (int)0xff00,
    SYSC_AWO_GPIOF_DS2_POS = 8,
    SYSC_AWO_GPIOG_DS2_MASK = (int)0xff0000,
    SYSC_AWO_GPIOG_DS2_POS = 16,
    SYSC_AWO_GPIOH_DS2_MASK = (int)0xff000000,
    SYSC_AWO_GPIOH_DS2_POS = 24,
};

enum SYSC_AWO_REG_GPIJKL_DS2_FIELD
{
    SYSC_AWO_GPIOI_DS2_MASK = (int)0xff,
    SYSC_AWO_GPIOI_DS2_POS = 0,
    SYSC_AWO_GPIOJ_DS2_MASK = (int)0xff00,
    SYSC_AWO_GPIOJ_DS2_POS = 8,
    SYSC_AWO_GPIOK_DS2_MASK = (int)0xff0000,
    SYSC_AWO_GPIOK_DS2_POS = 16,
    SYSC_AWO_GPIOL_DS2_MASK = (int)0xff000000,
    SYSC_AWO_GPIOL_DS2_POS = 24,
};

enum SYSC_AWO_REG_GPMNOP_DS2_FIELD
{
    SYSC_AWO_GPIOM_DS2_MASK = (int)0xff,
    SYSC_AWO_GPIOM_DS2_POS = 0,
    SYSC_AWO_GPION_DS2_MASK = (int)0xff00,
    SYSC_AWO_GPION_DS2_POS = 8,
    SYSC_AWO_GPIOO_DS2_MASK = (int)0xff0000,
    SYSC_AWO_GPIOO_DS2_POS = 16,
    SYSC_AWO_GPIOP_DS2_MASK = (int)0xff000000,
    SYSC_AWO_GPIOP_DS2_POS = 24,
};

enum SYSC_AWO_REG_GPQRST_DS2_FIELD
{
    SYSC_AWO_GPIOQ_DS2_MASK = (int)0xff,
    SYSC_AWO_GPIOQ_DS2_POS = 0,
    SYSC_AWO_GPIOR_DS2_MASK = (int)0xff00,
    SYSC_AWO_GPIOR_DS2_POS = 8,
    SYSC_AWO_GPIOS_DS2_MASK = (int)0xff0000,
    SYSC_AWO_GPIOS_DS2_POS = 16,
    SYSC_AWO_GPIOT_DS2_MASK = (int)0xff000000,
    SYSC_AWO_GPIOT_DS2_POS = 24,
};

enum SYSC_AWO_REG_GPUVWX_DS2_FIELD
{
    SYSC_AWO_GPIOU_DS2_MASK = (int)0xff,
    SYSC_AWO_GPIOU_DS2_POS = 0,
    SYSC_AWO_GPIOV_DS2_MASK = (int)0xff00,
    SYSC_AWO_GPIOV_DS2_POS = 8,
    SYSC_AWO_GPIOW_DS2_MASK = (int)0xff0000,
    SYSC_AWO_GPIOW_DS2_POS = 16,
    SYSC_AWO_GPIOX_DS2_MASK = (int)0xff000000,
    SYSC_AWO_GPIOX_DS2_POS = 24,
};

enum SYSC_AWO_REG_GPYZEEFF_DS2_FIELD
{
    SYSC_AWO_GPIOY_DS2_MASK = (int)0xff,
    SYSC_AWO_GPIOY_DS2_POS = 0,
    SYSC_AWO_GPIOZ_DS2_MASK = (int)0xff00,
    SYSC_AWO_GPIOZ_DS2_POS = 8,
    SYSC_AWO_GPIOEE_DS2_MASK = (int)0xff0000,
    SYSC_AWO_GPIOEE_DS2_POS = 16,
    SYSC_AWO_GPIOFF_DS2_MASK = (int)0xf000000,
    SYSC_AWO_GPIOFF_DS2_POS = 24,
};

enum SYSC_AWO_REG_GPAABBCCDD_DS2_FIELD
{
    SYSC_AWO_GPIOAA_DS2_MASK = (int)0xff,
    SYSC_AWO_GPIOAA_DS2_POS = 0,
    SYSC_AWO_GPIOBB_DS2_MASK = (int)0xff00,
    SYSC_AWO_GPIOBB_DS2_POS = 8,
    SYSC_AWO_GPIOCC_DS2_MASK = (int)0xff0000,
    SYSC_AWO_GPIOCC_DS2_POS = 16,
    SYSC_AWO_GPIODD_DS2_MASK = (int)0xff000000,
    SYSC_AWO_GPIODD_DS2_POS = 24,
};

enum SYSC_AWO_REG_GPJTAGMS_DS2_FIELD
{
    SYSC_AWO_GPIOJTAGMS_DS2_MASK = (int)0x1f,
    SYSC_AWO_GPIOJTAGMS_DS2_POS = 0,
    SYSC_AWO_GPIOAIO_DS2_MASK = (int)0x1fe0,
    SYSC_AWO_GPIOAIO_DS2_POS = 5,
};

enum SYSC_AWO_REG_GPABCD_DS3_FIELD
{
    SYSC_AWO_GPIOA_DS3_MASK = (int)0xff,
    SYSC_AWO_GPIOA_DS3_POS = 0,
    SYSC_AWO_GPIOB_DS3_MASK = (int)0xff00,
    SYSC_AWO_GPIOB_DS3_POS = 8,
    SYSC_AWO_GPIOC_DS3_MASK = (int)0xff0000,
    SYSC_AWO_GPIOC_DS3_POS = 16,
    SYSC_AWO_GPIOD_DS3_MASK = (int)0xff000000,
    SYSC_AWO_GPIOD_DS3_POS = 24,
};

enum SYSC_AWO_REG_GPEFGH_DS3_FIELD
{
    SYSC_AWO_GPIOE_DS3_MASK = (int)0xff,
    SYSC_AWO_GPIOE_DS3_POS = 0,
    SYSC_AWO_GPIOF_DS3_MASK = (int)0xff00,
    SYSC_AWO_GPIOF_DS3_POS = 8,
    SYSC_AWO_GPIOG_DS3_MASK = (int)0xff0000,
    SYSC_AWO_GPIOG_DS3_POS = 16,
    SYSC_AWO_GPIOH_DS3_MASK = (int)0xff000000,
    SYSC_AWO_GPIOH_DS3_POS = 24,
};

enum SYSC_AWO_REG_GPIJKL_DS3_FIELD
{
    SYSC_AWO_GPIOI_DS3_MASK = (int)0xff,
    SYSC_AWO_GPIOI_DS3_POS = 0,
    SYSC_AWO_GPIOJ_DS3_MASK = (int)0xff00,
    SYSC_AWO_GPIOJ_DS3_POS = 8,
    SYSC_AWO_GPIOK_DS3_MASK = (int)0xff0000,
    SYSC_AWO_GPIOK_DS3_POS = 16,
    SYSC_AWO_GPIOL_DS3_MASK = (int)0xff000000,
    SYSC_AWO_GPIOL_DS3_POS = 24,
};

enum SYSC_AWO_REG_GPMNOP_DS3_FIELD
{
    SYSC_AWO_GPIOM_DS3_MASK = (int)0xff,
    SYSC_AWO_GPIOM_DS3_POS = 0,
    SYSC_AWO_GPION_DS3_MASK = (int)0xff00,
    SYSC_AWO_GPION_DS3_POS = 8,
    SYSC_AWO_GPIOO_DS3_MASK = (int)0xff0000,
    SYSC_AWO_GPIOO_DS3_POS = 16,
    SYSC_AWO_GPIOP_DS3_MASK = (int)0xff000000,
    SYSC_AWO_GPIOP_DS3_POS = 24,
};

enum SYSC_AWO_REG_GPQRST_DS3_FIELD
{
    SYSC_AWO_GPIOQ_DS3_MASK = (int)0xff,
    SYSC_AWO_GPIOQ_DS3_POS = 0,
    SYSC_AWO_GPIOR_DS3_MASK = (int)0xff00,
    SYSC_AWO_GPIOR_DS3_POS = 8,
    SYSC_AWO_GPIOS_DS3_MASK = (int)0xff0000,
    SYSC_AWO_GPIOS_DS3_POS = 16,
    SYSC_AWO_GPIOT_DS3_MASK = (int)0xff000000,
    SYSC_AWO_GPIOT_DS3_POS = 24,
};

enum SYSC_AWO_REG_GPUVWX_DS3_FIELD
{
    SYSC_AWO_GPIOU_DS3_MASK = (int)0xff,
    SYSC_AWO_GPIOU_DS3_POS = 0,
    SYSC_AWO_GPIOV_DS3_MASK = (int)0xff00,
    SYSC_AWO_GPIOV_DS3_POS = 8,
    SYSC_AWO_GPIOW_DS3_MASK = (int)0xff0000,
    SYSC_AWO_GPIOW_DS3_POS = 16,
    SYSC_AWO_GPIOX_DS3_MASK = (int)0xff000000,
    SYSC_AWO_GPIOX_DS3_POS = 24,
};

enum SYSC_AWO_REG_GPYZEEFF_DS3_FIELD
{
    SYSC_AWO_GPIOY_DS3_MASK = (int)0xff,
    SYSC_AWO_GPIOY_DS3_POS = 0,
    SYSC_AWO_GPIOZ_DS3_MASK = (int)0xff00,
    SYSC_AWO_GPIOZ_DS3_POS = 8,
    SYSC_AWO_GPIOEE_DS3_MASK = (int)0xff0000,
    SYSC_AWO_GPIOEE_DS3_POS = 16,
    SYSC_AWO_GPIOFF_DS3_MASK = (int)0xf000000,
    SYSC_AWO_GPIOFF_DS3_POS = 24,
};

enum SYSC_AWO_REG_GPAABBCCDD_DS3_FIELD
{
    SYSC_AWO_GPIOAA_DS3_MASK = (int)0xff,
    SYSC_AWO_GPIOAA_DS3_POS = 0,
    SYSC_AWO_GPIOBB_DS3_MASK = (int)0xff00,
    SYSC_AWO_GPIOBB_DS3_POS = 8,
    SYSC_AWO_GPIOCC_DS3_MASK = (int)0xff0000,
    SYSC_AWO_GPIOCC_DS3_POS = 16,
    SYSC_AWO_GPIODD_DS3_MASK = (int)0xff000000,
    SYSC_AWO_GPIODD_DS3_POS = 24,
};

enum SYSC_AWO_REG_GPJTAGMS_DS3_FIELD
{
    SYSC_AWO_GPIOJTAGMS_DS3_MASK = (int)0x1f,
    SYSC_AWO_GPIOJTAGMS_DS3_POS = 0,
    SYSC_AWO_GPIOAIO_DS3_MASK = (int)0x1fe0,
    SYSC_AWO_GPIOAIO_DS3_POS = 5,
};

enum SYSC_AWO_REG_GPABCD_ST_FIELD
{
    SYSC_AWO_GPIOA_ST_MASK = (int)0xff,
    SYSC_AWO_GPIOA_ST_POS = 0,
    SYSC_AWO_GPIOB_ST_MASK = (int)0xff00,
    SYSC_AWO_GPIOB_ST_POS = 8,
    SYSC_AWO_GPIOC_ST_MASK = (int)0xff0000,
    SYSC_AWO_GPIOC_ST_POS = 16,
    SYSC_AWO_GPIOD_ST_MASK = (int)0xff000000,
    SYSC_AWO_GPIOD_ST_POS = 24,
};

enum SYSC_AWO_REG_GPEFGH_ST_FIELD
{
    SYSC_AWO_GPIOE_ST_MASK = (int)0xff,
    SYSC_AWO_GPIOE_ST_POS = 0,
    SYSC_AWO_GPIOF_ST_MASK = (int)0xff00,
    SYSC_AWO_GPIOF_ST_POS = 8,
    SYSC_AWO_GPIOG_ST_MASK = (int)0xff0000,
    SYSC_AWO_GPIOG_ST_POS = 16,
    SYSC_AWO_GPIOH_ST_MASK = (int)0xff000000,
    SYSC_AWO_GPIOH_ST_POS = 24,
};

enum SYSC_AWO_REG_GPIJKL_ST_FIELD
{
    SYSC_AWO_GPIOI_ST_MASK = (int)0xff,
    SYSC_AWO_GPIOI_ST_POS = 0,
    SYSC_AWO_GPIOJ_ST_MASK = (int)0xff00,
    SYSC_AWO_GPIOJ_ST_POS = 8,
    SYSC_AWO_GPIOK_ST_MASK = (int)0xff0000,
    SYSC_AWO_GPIOK_ST_POS = 16,
    SYSC_AWO_GPIOL_ST_MASK = (int)0xff000000,
    SYSC_AWO_GPIOL_ST_POS = 24,
};

enum SYSC_AWO_REG_GPMNOP_ST_FIELD
{
    SYSC_AWO_GPIOM_ST_MASK = (int)0xff,
    SYSC_AWO_GPIOM_ST_POS = 0,
    SYSC_AWO_GPION_ST_MASK = (int)0xff00,
    SYSC_AWO_GPION_ST_POS = 8,
    SYSC_AWO_GPIOO_ST_MASK = (int)0xff0000,
    SYSC_AWO_GPIOO_ST_POS = 16,
    SYSC_AWO_GPIOP_ST_MASK = (int)0xff000000,
    SYSC_AWO_GPIOP_ST_POS = 24,
};

enum SYSC_AWO_REG_GPQRST_ST_FIELD
{
    SYSC_AWO_GPIOQ_ST_MASK = (int)0xff,
    SYSC_AWO_GPIOQ_ST_POS = 0,
    SYSC_AWO_GPIOR_ST_MASK = (int)0xff00,
    SYSC_AWO_GPIOR_ST_POS = 8,
    SYSC_AWO_GPIOS_ST_MASK = (int)0xff0000,
    SYSC_AWO_GPIOS_ST_POS = 16,
    SYSC_AWO_GPIOT_ST_MASK = (int)0xff000000,
    SYSC_AWO_GPIOT_ST_POS = 24,
};

enum SYSC_AWO_REG_GPUVWX_ST_FIELD
{
    SYSC_AWO_GPIOU_ST_MASK = (int)0xff,
    SYSC_AWO_GPIOU_ST_POS = 0,
    SYSC_AWO_GPIOV_ST_MASK = (int)0xff00,
    SYSC_AWO_GPIOV_ST_POS = 8,
    SYSC_AWO_GPIOW_ST_MASK = (int)0xff0000,
    SYSC_AWO_GPIOW_ST_POS = 16,
    SYSC_AWO_GPIOX_ST_MASK = (int)0xff000000,
    SYSC_AWO_GPIOX_ST_POS = 24,
};

enum SYSC_AWO_REG_GPYZEEFF_ST_FIELD
{
    SYSC_AWO_GPIOY_ST_MASK = (int)0xff,
    SYSC_AWO_GPIOY_ST_POS = 0,
    SYSC_AWO_GPIOZ_ST_MASK = (int)0xff00,
    SYSC_AWO_GPIOZ_ST_POS = 8,
    SYSC_AWO_GPIOEE_ST_MASK = (int)0xff0000,
    SYSC_AWO_GPIOEE_ST_POS = 16,
    SYSC_AWO_GPIOFF_ST_MASK = (int)0xf000000,
    SYSC_AWO_GPIOFF_ST_POS = 24,
};

enum SYSC_AWO_REG_GPAABBCCDD_ST_FIELD
{
    SYSC_AWO_GPIOAA_ST_MASK = (int)0xff,
    SYSC_AWO_GPIOAA_ST_POS = 0,
    SYSC_AWO_GPIOBB_ST_MASK = (int)0xff00,
    SYSC_AWO_GPIOBB_ST_POS = 8,
    SYSC_AWO_GPIOCC_ST_MASK = (int)0xff0000,
    SYSC_AWO_GPIOCC_ST_POS = 16,
    SYSC_AWO_GPIODD_ST_MASK = (int)0xff000000,
    SYSC_AWO_GPIODD_ST_POS = 24,
};

enum SYSC_AWO_REG_GPJTAGMS_ST_FIELD
{
    SYSC_AWO_GPIOJTAGMS_ST_MASK = (int)0x1f,
    SYSC_AWO_GPIOJTAGMS_ST_POS = 0,
    SYSC_AWO_GPIOAIO_ST_MASK = (int)0x1fe0,
    SYSC_AWO_GPIOAIO_ST_POS = 5,
};

enum SYSC_AWO_REG_GPABCD_SL_FIELD
{
    SYSC_AWO_GPIOA_SL_MASK = (int)0xff,
    SYSC_AWO_GPIOA_SL_POS = 0,
    SYSC_AWO_GPIOB_SL_MASK = (int)0xff00,
    SYSC_AWO_GPIOB_SL_POS = 8,
    SYSC_AWO_GPIOC_SL_MASK = (int)0xff0000,
    SYSC_AWO_GPIOC_SL_POS = 16,
    SYSC_AWO_GPIOD_SL_MASK = (int)0xff000000,
    SYSC_AWO_GPIOD_SL_POS = 24,
};

enum SYSC_AWO_REG_GPEFGH_SL_FIELD
{
    SYSC_AWO_GPIOE_SL_MASK = (int)0xff,
    SYSC_AWO_GPIOE_SL_POS = 0,
    SYSC_AWO_GPIOF_SL_MASK = (int)0xff00,
    SYSC_AWO_GPIOF_SL_POS = 8,
    SYSC_AWO_GPIOG_SL_MASK = (int)0xff0000,
    SYSC_AWO_GPIOG_SL_POS = 16,
    SYSC_AWO_GPIOH_SL_MASK = (int)0xff000000,
    SYSC_AWO_GPIOH_SL_POS = 24,
};

enum SYSC_AWO_REG_GPIJKL_SL_FIELD
{
    SYSC_AWO_GPIOI_SL_MASK = (int)0xff,
    SYSC_AWO_GPIOI_SL_POS = 0,
    SYSC_AWO_GPIOJ_SL_MASK = (int)0xff00,
    SYSC_AWO_GPIOJ_SL_POS = 8,
    SYSC_AWO_GPIOK_SL_MASK = (int)0xff0000,
    SYSC_AWO_GPIOK_SL_POS = 16,
    SYSC_AWO_GPIOL_SL_MASK = (int)0xff000000,
    SYSC_AWO_GPIOL_SL_POS = 24,
};

enum SYSC_AWO_REG_GPMNOP_SL_FIELD
{
    SYSC_AWO_GPIOM_SL_MASK = (int)0xff,
    SYSC_AWO_GPIOM_SL_POS = 0,
    SYSC_AWO_GPION_SL_MASK = (int)0xff00,
    SYSC_AWO_GPION_SL_POS = 8,
    SYSC_AWO_GPIOO_SL_MASK = (int)0xff0000,
    SYSC_AWO_GPIOO_SL_POS = 16,
    SYSC_AWO_GPIOP_SL_MASK = (int)0xff000000,
    SYSC_AWO_GPIOP_SL_POS = 24,
};

enum SYSC_AWO_REG_GPQRST_SL_FIELD
{
    SYSC_AWO_GPIOQ_SL_MASK = (int)0xff,
    SYSC_AWO_GPIOQ_SL_POS = 0,
    SYSC_AWO_GPIOR_SL_MASK = (int)0xff00,
    SYSC_AWO_GPIOR_SL_POS = 8,
    SYSC_AWO_GPIOS_SL_MASK = (int)0xff0000,
    SYSC_AWO_GPIOS_SL_POS = 16,
    SYSC_AWO_GPIOT_SL_MASK = (int)0xff000000,
    SYSC_AWO_GPIOT_SL_POS = 24,
};

enum SYSC_AWO_REG_GPUVWX_SL_FIELD
{
    SYSC_AWO_GPIOU_SL_MASK = (int)0xff,
    SYSC_AWO_GPIOU_SL_POS = 0,
    SYSC_AWO_GPIOV_SL_MASK = (int)0xff00,
    SYSC_AWO_GPIOV_SL_POS = 8,
    SYSC_AWO_GPIOW_SL_MASK = (int)0xff0000,
    SYSC_AWO_GPIOW_SL_POS = 16,
    SYSC_AWO_GPIOX_SL_MASK = (int)0xff000000,
    SYSC_AWO_GPIOX_SL_POS = 24,
};

enum SYSC_AWO_REG_GPYZEEFF_SL_FIELD
{
    SYSC_AWO_GPIOY_SL_MASK = (int)0xff,
    SYSC_AWO_GPIOY_SL_POS = 0,
    SYSC_AWO_GPIOZ_SL_MASK = (int)0xff00,
    SYSC_AWO_GPIOZ_SL_POS = 8,
    SYSC_AWO_GPIOEE_SL_MASK = (int)0xff0000,
    SYSC_AWO_GPIOEE_SL_POS = 16,
    SYSC_AWO_GPIOFF_SL_MASK = (int)0xf000000,
    SYSC_AWO_GPIOFF_SL_POS = 24,
};

enum SYSC_AWO_REG_GPAABBCCDD_SL_FIELD
{
    SYSC_AWO_GPIOAA_SL_MASK = (int)0xff,
    SYSC_AWO_GPIOAA_SL_POS = 0,
    SYSC_AWO_GPIOBB_SL_MASK = (int)0xff00,
    SYSC_AWO_GPIOBB_SL_POS = 8,
    SYSC_AWO_GPIOCC_SL_MASK = (int)0xff0000,
    SYSC_AWO_GPIOCC_SL_POS = 16,
    SYSC_AWO_GPIODD_SL_MASK = (int)0xff000000,
    SYSC_AWO_GPIODD_SL_POS = 24,
};

enum SYSC_AWO_REG_GPJTAGMS_SL_FIELD
{
    SYSC_AWO_GPIOJTAGMS_SL_MASK = (int)0x1f,
    SYSC_AWO_GPIOJTAGMS_SL_POS = 0,
    SYSC_AWO_GPIOAIO_SL_MASK = (int)0x1fe0,
    SYSC_AWO_GPIOAIO_SL_POS = 5,
};

enum SYSC_AWO_REG_MULTIPLEX_SEL_FIELD
{
    SYSC_AWO_I2C_MULTIPLEX_SEL_MASK = (int)0xffff,
    SYSC_AWO_I2C_MULTIPLEX_SEL_POS = 0,
    SYSC_AWO_SPI_MULTIPLEX_SEL_MASK = (int)0x30000,
    SYSC_AWO_SPI_MULTIPLEX_SEL_POS = 16,
    SYSC_AWO_LTPI_I2C_MULTIPLEX_SEL_MASK = (int)0x3ffc0000,
    SYSC_AWO_LTPI_I2C_MULTIPLEX_SEL_POS = 18,
    SYSC_AWO_SGPIO_MASTER_MULTIPLEX_SEL_MASK = (int)0x40000000,
    SYSC_AWO_SGPIO_MASTER_MULTIPLEX_SEL_POS = 30,
};

enum SYSC_AWO_REG_SIG_SEL_FIELD
{
    SYSC_AWO_FUNC_USB_DEBUG_SIG_MASK = (int)0x1f,
    SYSC_AWO_FUNC_USB_DEBUG_SIG_POS = 0,
    SYSC_AWO_FUNC_PTEST_JTAG_SIG_MASK = (int)0x3e0,
    SYSC_AWO_FUNC_PTEST_JTAG_SIG_POS = 5,
};

enum SYSC_AWO_REG_GPIO_INTR_SEL_FIELD
{
    SYSC_AWO_GPIO_INTR0_SEL_MASK = (int)0x1,
    SYSC_AWO_GPIO_INTR0_SEL_POS = 0,
    SYSC_AWO_GPIO_INTR1_SEL_MASK = (int)0x2,
    SYSC_AWO_GPIO_INTR1_SEL_POS = 1,
};

enum SYSC_AWO_REG_GPAB_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOA_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_INTR0_MSK_POS = 0,
    SYSC_AWO_GPIOB_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOB_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPCD_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOC_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOC_INTR0_MSK_POS = 0,
    SYSC_AWO_GPIOD_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOD_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPEF_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOE_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOE_INTR0_MSK_POS = 0,
    SYSC_AWO_GPIOF_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOF_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPGH_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOG_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOG_INTR0_MSK_POS = 0,
    SYSC_AWO_GPIOH_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOH_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPIJ_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOI_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOI_INTR0_MSK_POS = 0,
    SYSC_AWO_GPIOJ_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOJ_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPKL_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOK_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOK_INTR0_MSK_POS = 0,
    SYSC_AWO_GPIOL_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOL_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPMN_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOM_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOM_INTR0_MSK_POS = 0,
    SYSC_AWO_GPION_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPION_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPOP_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOO_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOO_INTR0_MSK_POS = 0,
    SYSC_AWO_GPIOP_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOP_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPQR_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOQ_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOQ_INTR0_MSK_POS = 0,
    SYSC_AWO_GPIOR_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOR_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPST_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOS_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOS_INTR0_MSK_POS = 0,
    SYSC_AWO_GPIOT_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOT_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPUV_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOU_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOU_INTR0_MSK_POS = 0,
    SYSC_AWO_GPIOV_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOV_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPWX_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOW_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOW_INTR0_MSK_POS = 0,
    SYSC_AWO_GPIOX_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOX_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPYZ_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOY_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOY_INTR0_MSK_POS = 0,
    SYSC_AWO_GPIOZ_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOZ_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPEEFF_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOEE_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOEE_INTR0_MSK_POS = 0,
    SYSC_AWO_GPIOFF_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOFF_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPAABB_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOAA_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOAA_INTR0_MSK_POS = 0,
    SYSC_AWO_GPIOBB_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOBB_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPCCDD_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOCC_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOCC_INTR0_MSK_POS = 0,
    SYSC_AWO_GPIODD_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIODD_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPJTAGMS_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOJTAGMS_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOJTAGMS_INTR0_MSK_POS = 0,
    SYSC_AWO_GPIORSTIND_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIORSTIND_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPAIO_INTR0_MSK_FIELD
{
    SYSC_AWO_GPIOAIO_INTR0_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOAIO_INTR0_MSK_POS = 0,
    SYSC_AWO_GPIOTSPRST_INTR0_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOTSPRST_INTR0_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPAB_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOA_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_INTR0_CLR_POS = 0,
    SYSC_AWO_GPIOB_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOB_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPCD_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOC_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOC_INTR0_CLR_POS = 0,
    SYSC_AWO_GPIOD_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOD_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPEF_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOE_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOE_INTR0_CLR_POS = 0,
    SYSC_AWO_GPIOF_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOF_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPGH_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOG_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOG_INTR0_CLR_POS = 0,
    SYSC_AWO_GPIOH_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOH_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPIJ_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOI_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOI_INTR0_CLR_POS = 0,
    SYSC_AWO_GPIOJ_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOJ_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPKL_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOK_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOK_INTR0_CLR_POS = 0,
    SYSC_AWO_GPIOL_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOL_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPMN_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOM_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOM_INTR0_CLR_POS = 0,
    SYSC_AWO_GPION_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPION_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPOP_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOO_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOO_INTR0_CLR_POS = 0,
    SYSC_AWO_GPIOP_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOP_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPQR_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOQ_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOQ_INTR0_CLR_POS = 0,
    SYSC_AWO_GPIOR_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOR_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPST_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOS_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOS_INTR0_CLR_POS = 0,
    SYSC_AWO_GPIOT_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOT_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPUV_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOU_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOU_INTR0_CLR_POS = 0,
    SYSC_AWO_GPIOV_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOV_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPWX_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOW_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOW_INTR0_CLR_POS = 0,
    SYSC_AWO_GPIOX_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOX_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPYZ_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOY_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOY_INTR0_CLR_POS = 0,
    SYSC_AWO_GPIOZ_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOZ_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPEEFF_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOEE_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOEE_INTR0_CLR_POS = 0,
    SYSC_AWO_GPIOFF_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOFF_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPAABB_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOAA_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOAA_INTR0_CLR_POS = 0,
    SYSC_AWO_GPIOBB_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOBB_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPCCDD_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOCC_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOCC_INTR0_CLR_POS = 0,
    SYSC_AWO_GPIODD_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIODD_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPJTAGMS_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOJTAGMS_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOJTAGMS_INTR0_CLR_POS = 0,
    SYSC_AWO_GPIORSTIND_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIORSTIND_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPAIO_INTR0_CLR_FIELD
{
    SYSC_AWO_GPIOAIO_INTR0_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOAIO_INTR0_CLR_POS = 0,
    SYSC_AWO_GPIOTSPRST_INTR0_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOTSPRST_INTR0_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPAB_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOA_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_INTR0_RAW_POS = 0,
    SYSC_AWO_GPIOB_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOB_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPCD_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOC_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOC_INTR0_RAW_POS = 0,
    SYSC_AWO_GPIOD_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOD_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPEF_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOE_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOE_INTR0_RAW_POS = 0,
    SYSC_AWO_GPIOF_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOF_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPGH_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOG_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOG_INTR0_RAW_POS = 0,
    SYSC_AWO_GPIOH_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOH_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPIJ_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOI_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOI_INTR0_RAW_POS = 0,
    SYSC_AWO_GPIOJ_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOJ_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPKL_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOK_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOK_INTR0_RAW_POS = 0,
    SYSC_AWO_GPIOL_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOL_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPMN_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOM_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOM_INTR0_RAW_POS = 0,
    SYSC_AWO_GPION_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPION_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPOP_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOO_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOO_INTR0_RAW_POS = 0,
    SYSC_AWO_GPIOP_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOP_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPQR_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOQ_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOQ_INTR0_RAW_POS = 0,
    SYSC_AWO_GPIOR_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOR_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPST_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOS_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOS_INTR0_RAW_POS = 0,
    SYSC_AWO_GPIOT_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOT_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPUV_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOU_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOU_INTR0_RAW_POS = 0,
    SYSC_AWO_GPIOV_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOV_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPWX_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOW_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOW_INTR0_RAW_POS = 0,
    SYSC_AWO_GPIOX_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOX_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPYZ_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOY_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOY_INTR0_RAW_POS = 0,
    SYSC_AWO_GPIOZ_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOZ_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPEEFF_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOEE_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOEE_INTR0_RAW_POS = 0,
    SYSC_AWO_GPIOFF_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOFF_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPAABB_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOAA_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOAA_INTR0_RAW_POS = 0,
    SYSC_AWO_GPIOBB_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOBB_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPCCDD_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOCC_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOCC_INTR0_RAW_POS = 0,
    SYSC_AWO_GPIODD_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIODD_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPJTAGMS_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOJTAGMS_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOJTAGMS_INTR0_RAW_POS = 0,
    SYSC_AWO_GPIORSTIND_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIORSTIND_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPAIO_INTR0_RAW_FIELD
{
    SYSC_AWO_GPIOAIO_INTR0_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOAIO_INTR0_RAW_POS = 0,
    SYSC_AWO_GPIOTSPRST_INTR0_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOTSPRST_INTR0_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPAB_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOA_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_INTR0_STT_POS = 0,
    SYSC_AWO_GPIOB_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOB_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPCD_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOC_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOC_INTR0_STT_POS = 0,
    SYSC_AWO_GPIOD_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOD_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPEF_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOE_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOE_INTR0_STT_POS = 0,
    SYSC_AWO_GPIOF_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOF_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPGH_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOG_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOG_INTR0_STT_POS = 0,
    SYSC_AWO_GPIOH_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOH_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPIJ_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOI_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOI_INTR0_STT_POS = 0,
    SYSC_AWO_GPIOJ_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOJ_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPKL_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOK_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOK_INTR0_STT_POS = 0,
    SYSC_AWO_GPIOL_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOL_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPMN_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOM_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOM_INTR0_STT_POS = 0,
    SYSC_AWO_GPION_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPION_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPOP_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOO_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOO_INTR0_STT_POS = 0,
    SYSC_AWO_GPIOP_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOP_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPQR_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOQ_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOQ_INTR0_STT_POS = 0,
    SYSC_AWO_GPIOR_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOR_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPST_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOS_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOS_INTR0_STT_POS = 0,
    SYSC_AWO_GPIOT_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOT_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPUV_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOU_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOU_INTR0_STT_POS = 0,
    SYSC_AWO_GPIOV_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOV_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPWX_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOW_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOW_INTR0_STT_POS = 0,
    SYSC_AWO_GPIOX_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOX_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPYZ_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOY_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOY_INTR0_STT_POS = 0,
    SYSC_AWO_GPIOZ_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOZ_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPEEFF_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOEE_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOEE_INTR0_STT_POS = 0,
    SYSC_AWO_GPIOFF_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOFF_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPAABB_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOAA_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOAA_INTR0_STT_POS = 0,
    SYSC_AWO_GPIOBB_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOBB_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPCCDD_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOCC_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOCC_INTR0_STT_POS = 0,
    SYSC_AWO_GPIODD_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIODD_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPJTAGMS_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOJTAGMS_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOJTAGMS_INTR0_STT_POS = 0,
    SYSC_AWO_GPIORSTIND_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIORSTIND_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPAIO_INTR0_STT_FIELD
{
    SYSC_AWO_GPIOAIO_INTR0_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOAIO_INTR0_STT_POS = 0,
    SYSC_AWO_GPIOTSPRST_INTR0_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOTSPRST_INTR0_STT_POS = 16,
};

enum SYSC_AWO_REG_GPAB_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOA_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_INTR1_MSK_POS = 0,
    SYSC_AWO_GPIOB_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOB_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPCD_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOC_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOC_INTR1_MSK_POS = 0,
    SYSC_AWO_GPIOD_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOD_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPEF_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOE_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOE_INTR1_MSK_POS = 0,
    SYSC_AWO_GPIOF_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOF_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPGH_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOG_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOG_INTR1_MSK_POS = 0,
    SYSC_AWO_GPIOH_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOH_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPIJ_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOI_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOI_INTR1_MSK_POS = 0,
    SYSC_AWO_GPIOJ_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOJ_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPKL_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOK_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOK_INTR1_MSK_POS = 0,
    SYSC_AWO_GPIOL_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOL_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPMN_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOM_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOM_INTR1_MSK_POS = 0,
    SYSC_AWO_GPION_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPION_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPOP_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOO_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOO_INTR1_MSK_POS = 0,
    SYSC_AWO_GPIOP_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOP_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPQR_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOQ_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOQ_INTR1_MSK_POS = 0,
    SYSC_AWO_GPIOR_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOR_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPST_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOS_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOS_INTR1_MSK_POS = 0,
    SYSC_AWO_GPIOT_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOT_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPUV_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOU_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOU_INTR1_MSK_POS = 0,
    SYSC_AWO_GPIOV_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOV_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPWX_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOW_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOW_INTR1_MSK_POS = 0,
    SYSC_AWO_GPIOX_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOX_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPYZ_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOY_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOY_INTR1_MSK_POS = 0,
    SYSC_AWO_GPIOZ_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOZ_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPEEFF_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOEE_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOEE_INTR1_MSK_POS = 0,
    SYSC_AWO_GPIOFF_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOFF_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPAABB_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOAA_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOAA_INTR1_MSK_POS = 0,
    SYSC_AWO_GPIOBB_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOBB_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPCCDD_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOCC_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOCC_INTR1_MSK_POS = 0,
    SYSC_AWO_GPIODD_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIODD_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPJTAGMS_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOJTAGMS_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOJTAGMS_INTR1_MSK_POS = 0,
    SYSC_AWO_GPIORSTIND_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIORSTIND_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPAIO_INTR1_MSK_FIELD
{
    SYSC_AWO_GPIOAIO_INTR1_MSK_MASK = (int)0xffff,
    SYSC_AWO_GPIOAIO_INTR1_MSK_POS = 0,
    SYSC_AWO_GPIOTSPRST_INTR1_MSK_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOTSPRST_INTR1_MSK_POS = 16,
};

enum SYSC_AWO_REG_GPAB_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOA_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_INTR1_CLR_POS = 0,
    SYSC_AWO_GPIOB_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOB_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPCD_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOC_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOC_INTR1_CLR_POS = 0,
    SYSC_AWO_GPIOD_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOD_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPEF_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOE_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOE_INTR1_CLR_POS = 0,
    SYSC_AWO_GPIOF_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOF_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPGH_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOG_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOG_INTR1_CLR_POS = 0,
    SYSC_AWO_GPIOH_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOH_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPIJ_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOI_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOI_INTR1_CLR_POS = 0,
    SYSC_AWO_GPIOJ_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOJ_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPKL_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOK_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOK_INTR1_CLR_POS = 0,
    SYSC_AWO_GPIOL_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOL_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPMN_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOM_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOM_INTR1_CLR_POS = 0,
    SYSC_AWO_GPION_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPION_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPOP_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOO_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOO_INTR1_CLR_POS = 0,
    SYSC_AWO_GPIOP_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOP_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPQR_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOQ_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOQ_INTR1_CLR_POS = 0,
    SYSC_AWO_GPIOR_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOR_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPST_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOS_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOS_INTR1_CLR_POS = 0,
    SYSC_AWO_GPIOT_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOT_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPUV_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOU_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOU_INTR1_CLR_POS = 0,
    SYSC_AWO_GPIOV_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOV_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPWX_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOW_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOW_INTR1_CLR_POS = 0,
    SYSC_AWO_GPIOX_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOX_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPYZ_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOY_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOY_INTR1_CLR_POS = 0,
    SYSC_AWO_GPIOZ_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOZ_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPEEFF_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOEE_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOEE_INTR1_CLR_POS = 0,
    SYSC_AWO_GPIOFF_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOFF_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPAABB_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOAA_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOAA_INTR1_CLR_POS = 0,
    SYSC_AWO_GPIOBB_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOBB_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPCCDD_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOCC_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOCC_INTR1_CLR_POS = 0,
    SYSC_AWO_GPIODD_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIODD_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPJTAGMS_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOJTAGMS_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOJTAGMS_INTR1_CLR_POS = 0,
    SYSC_AWO_GPIORSTIND_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIORSTIND_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPAIO_INTR1_CLR_FIELD
{
    SYSC_AWO_GPIOAIO_INTR1_CLR_MASK = (int)0xffff,
    SYSC_AWO_GPIOAIO_INTR1_CLR_POS = 0,
    SYSC_AWO_GPIOTSPRST_INTR1_CLR_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOTSPRST_INTR1_CLR_POS = 16,
};

enum SYSC_AWO_REG_GPAB_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOA_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_INTR1_RAW_POS = 0,
    SYSC_AWO_GPIOB_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOB_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPCD_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOC_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOC_INTR1_RAW_POS = 0,
    SYSC_AWO_GPIOD_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOD_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPEF_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOE_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOE_INTR1_RAW_POS = 0,
    SYSC_AWO_GPIOF_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOF_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPGH_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOG_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOG_INTR1_RAW_POS = 0,
    SYSC_AWO_GPIOH_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOH_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPIJ_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOI_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOI_INTR1_RAW_POS = 0,
    SYSC_AWO_GPIOJ_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOJ_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPKL_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOK_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOK_INTR1_RAW_POS = 0,
    SYSC_AWO_GPIOL_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOL_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPMN_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOM_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOM_INTR1_RAW_POS = 0,
    SYSC_AWO_GPION_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPION_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPOP_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOO_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOO_INTR1_RAW_POS = 0,
    SYSC_AWO_GPIOP_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOP_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPQR_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOQ_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOQ_INTR1_RAW_POS = 0,
    SYSC_AWO_GPIOR_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOR_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPST_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOS_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOS_INTR1_RAW_POS = 0,
    SYSC_AWO_GPIOT_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOT_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPUV_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOU_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOU_INTR1_RAW_POS = 0,
    SYSC_AWO_GPIOV_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOV_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPWX_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOW_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOW_INTR1_RAW_POS = 0,
    SYSC_AWO_GPIOX_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOX_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPYZ_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOY_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOY_INTR1_RAW_POS = 0,
    SYSC_AWO_GPIOZ_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOZ_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPEEFF_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOEE_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOEE_INTR1_RAW_POS = 0,
    SYSC_AWO_GPIOFF_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOFF_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPAABB_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOAA_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOAA_INTR1_RAW_POS = 0,
    SYSC_AWO_GPIOBB_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOBB_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPCCDD_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOCC_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOCC_INTR1_RAW_POS = 0,
    SYSC_AWO_GPIODD_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIODD_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPJTAGMS_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOJTAGMS_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOJTAGMS_INTR1_RAW_POS = 0,
    SYSC_AWO_GPIORSTIND_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIORSTIND_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPAIO_INTR1_RAW_FIELD
{
    SYSC_AWO_GPIOAIO_INTR1_RAW_MASK = (int)0xffff,
    SYSC_AWO_GPIOAIO_INTR1_RAW_POS = 0,
    SYSC_AWO_GPIOTSPRST_INTR1_RAW_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOTSPRST_INTR1_RAW_POS = 16,
};

enum SYSC_AWO_REG_GPAB_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOA_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_INTR1_STT_POS = 0,
    SYSC_AWO_GPIOB_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOB_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPCD_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOC_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOC_INTR1_STT_POS = 0,
    SYSC_AWO_GPIOD_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOD_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPEF_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOE_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOE_INTR1_STT_POS = 0,
    SYSC_AWO_GPIOF_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOF_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPGH_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOG_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOG_INTR1_STT_POS = 0,
    SYSC_AWO_GPIOH_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOH_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPIJ_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOI_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOI_INTR1_STT_POS = 0,
    SYSC_AWO_GPIOJ_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOJ_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPKL_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOK_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOK_INTR1_STT_POS = 0,
    SYSC_AWO_GPIOL_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOL_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPMN_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOM_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOM_INTR1_STT_POS = 0,
    SYSC_AWO_GPION_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPION_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPOP_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOO_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOO_INTR1_STT_POS = 0,
    SYSC_AWO_GPIOP_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOP_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPQR_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOQ_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOQ_INTR1_STT_POS = 0,
    SYSC_AWO_GPIOR_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOR_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPST_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOS_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOS_INTR1_STT_POS = 0,
    SYSC_AWO_GPIOT_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOT_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPUV_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOU_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOU_INTR1_STT_POS = 0,
    SYSC_AWO_GPIOV_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOV_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPWX_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOW_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOW_INTR1_STT_POS = 0,
    SYSC_AWO_GPIOX_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOX_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPYZ_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOY_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOY_INTR1_STT_POS = 0,
    SYSC_AWO_GPIOZ_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOZ_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPEEFF_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOEE_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOEE_INTR1_STT_POS = 0,
    SYSC_AWO_GPIOFF_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOFF_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPAABB_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOAA_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOAA_INTR1_STT_POS = 0,
    SYSC_AWO_GPIOBB_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOBB_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPCCDD_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOCC_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOCC_INTR1_STT_POS = 0,
    SYSC_AWO_GPIODD_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIODD_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPJTAGMS_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOJTAGMS_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOJTAGMS_INTR1_STT_POS = 0,
    SYSC_AWO_GPIORSTIND_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIORSTIND_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPAIO_INTR1_STT_FIELD
{
    SYSC_AWO_GPIOAIO_INTR1_STT_MASK = (int)0xffff,
    SYSC_AWO_GPIOAIO_INTR1_STT_POS = 0,
    SYSC_AWO_GPIOTSPRST_INTR1_STT_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOTSPRST_INTR1_STT_POS = 16,
};

enum SYSC_AWO_REG_GPEYZ_AE_FIELD
{
    SYSC_AWO_GPIOY_AE_MASK = (int)0xff,
    SYSC_AWO_GPIOY_AE_POS = 0,
    SYSC_AWO_GPIOZ_AE_MASK = (int)0xff00,
    SYSC_AWO_GPIOZ_AE_POS = 8,
    SYSC_AWO_GPIOAIO_AE_MASK = (int)0x1ff0000,
    SYSC_AWO_GPIOAIO_AE_POS = 16,
};

enum SYSC_AWO_REG_APB_EXTI0_INTR_FIELD
{
    SYSC_AWO_APB_EXTI0_CMP_MASK = (int)0xf,
    SYSC_AWO_APB_EXTI0_CMP_POS = 0,
    SYSC_AWO_APB_EXTI0_EXTI_DBC_CMP_MASK = (int)0xf0,
    SYSC_AWO_APB_EXTI0_EXTI_DBC_CMP_POS = 4,
    SYSC_AWO_APB_EXTI0_COMP_ADTRIG_MASK = (int)0xf00,
    SYSC_AWO_APB_EXTI0_COMP_ADTRIG_POS = 8,
    SYSC_AWO_APB_EXTI0_GPIO_ADTRIG_MASK = (int)0x1000,
    SYSC_AWO_APB_EXTI0_GPIO_ADTRIG_POS = 12,
};

enum SYSC_AWO_REG_APB_EXTI1_INTR_FIELD
{
    SYSC_AWO_APB_EXTI1_CMP_MASK = (int)0xf,
    SYSC_AWO_APB_EXTI1_CMP_POS = 0,
    SYSC_AWO_APB_EXTI1_EXTI_DBC_CMP_MASK = (int)0xf0,
    SYSC_AWO_APB_EXTI1_EXTI_DBC_CMP_POS = 4,
    SYSC_AWO_APB_EXTI1_COMP_ADTRIG_MASK = (int)0xf00,
    SYSC_AWO_APB_EXTI1_COMP_ADTRIG_POS = 8,
    SYSC_AWO_APB_EXTI1_GPIO_ADTRIG_MASK = (int)0x1000,
    SYSC_AWO_APB_EXTI1_GPIO_ADTRIG_POS = 12,
};

enum SYSC_AWO_REG_APB_EXTI2_INTR_FIELD
{
    SYSC_AWO_APB_EXTI2_CMP_MASK = (int)0xf,
    SYSC_AWO_APB_EXTI2_CMP_POS = 0,
    SYSC_AWO_APB_EXTI2_EXTI_DBC_CMP_MASK = (int)0xf0,
    SYSC_AWO_APB_EXTI2_EXTI_DBC_CMP_POS = 4,
    SYSC_AWO_APB_EXTI2_COMP_ADTRIG_MASK = (int)0xf00,
    SYSC_AWO_APB_EXTI2_COMP_ADTRIG_POS = 8,
    SYSC_AWO_APB_EXTI2_GPIO_ADTRIG_MASK = (int)0x1000,
    SYSC_AWO_APB_EXTI2_GPIO_ADTRIG_POS = 12,
};

enum SYSC_AWO_REG_APB_EXTI3_INTR_FIELD
{
    SYSC_AWO_APB_EXTI3_CMP_MASK = (int)0xf,
    SYSC_AWO_APB_EXTI3_CMP_POS = 0,
    SYSC_AWO_APB_EXTI3_EXTI_DBC_CMP_MASK = (int)0xf0,
    SYSC_AWO_APB_EXTI3_EXTI_DBC_CMP_POS = 4,
    SYSC_AWO_APB_EXTI3_COMP_ADTRIG_MASK = (int)0xf00,
    SYSC_AWO_APB_EXTI3_COMP_ADTRIG_POS = 8,
    SYSC_AWO_APB_EXTI3_GPIO_ADTRIG_MASK = (int)0x1000,
    SYSC_AWO_APB_EXTI3_GPIO_ADTRIG_POS = 12,
};

enum SYSC_AWO_REG_GP_MD_LP_CTRL0_FIELD
{
    SYSC_AWO_GPIOEMC_MS_MASK = (int)0x1,
    SYSC_AWO_GPIOEMC_MS_POS = 0,
    SYSC_AWO_GPIOESP1_MS_MASK = (int)0x2,
    SYSC_AWO_GPIOESP1_MS_POS = 1,
    SYSC_AWO_GPIOIO0_MD_MASK = (int)0x4,
    SYSC_AWO_GPIOIO0_MD_POS = 2,
    SYSC_AWO_GPIOIO0_LP_MASK = (int)0x8,
    SYSC_AWO_GPIOIO0_LP_POS = 3,
    SYSC_AWO_GPIOIO1_MD_MASK = (int)0x10,
    SYSC_AWO_GPIOIO1_MD_POS = 4,
    SYSC_AWO_GPIOIO1_LP_MASK = (int)0x20,
    SYSC_AWO_GPIOIO1_LP_POS = 5,
    SYSC_AWO_GPIOIO2_MD_MASK = (int)0x40,
    SYSC_AWO_GPIOIO2_MD_POS = 6,
    SYSC_AWO_GPIOIO2_LP_MASK = (int)0x80,
    SYSC_AWO_GPIOIO2_LP_POS = 7,
    SYSC_AWO_GPIOURT_MD_MASK = (int)0x100,
    SYSC_AWO_GPIOURT_MD_POS = 8,
    SYSC_AWO_GPIOURT_LP_MASK = (int)0x200,
    SYSC_AWO_GPIOURT_LP_POS = 9,
    SYSC_AWO_GPIOH3C0_MD_MASK = (int)0x400,
    SYSC_AWO_GPIOH3C0_MD_POS = 10,
    SYSC_AWO_GPIOH3C0_LP_MASK = (int)0x800,
    SYSC_AWO_GPIOH3C0_LP_POS = 11,
    SYSC_AWO_GPIOH3C1_MD_MASK = (int)0x1000,
    SYSC_AWO_GPIOH3C1_MD_POS = 12,
    SYSC_AWO_GPIOH3C1_LP_MASK = (int)0x2000,
    SYSC_AWO_GPIOH3C1_LP_POS = 13,
    SYSC_AWO_GPIOESP0_MD_MASK = (int)0x4000,
    SYSC_AWO_GPIOESP0_MD_POS = 14,
    SYSC_AWO_GPIOESP0_LP_MASK = (int)0x8000,
    SYSC_AWO_GPIOESP0_LP_POS = 15,
    SYSC_AWO_GPIOSPI0_MD_MASK = (int)0x10000,
    SYSC_AWO_GPIOSPI0_MD_POS = 16,
    SYSC_AWO_GPIOSPI0_LP_MASK = (int)0x20000,
    SYSC_AWO_GPIOSPI0_LP_POS = 17,
    SYSC_AWO_GPIOSPI1_MD_MASK = (int)0x40000,
    SYSC_AWO_GPIOSPI1_MD_POS = 18,
    SYSC_AWO_GPIOSPI1_LP_MASK = (int)0x80000,
    SYSC_AWO_GPIOSPI1_LP_POS = 19,
    SYSC_AWO_GPIOSPI2_MD_MASK = (int)0x100000,
    SYSC_AWO_GPIOSPI2_MD_POS = 20,
    SYSC_AWO_GPIOSPI2_LP_MASK = (int)0x200000,
    SYSC_AWO_GPIOSPI2_LP_POS = 21,
    SYSC_AWO_GPIOBMC33_MD_MASK = (int)0x400000,
    SYSC_AWO_GPIOBMC33_MD_POS = 22,
    SYSC_AWO_GPIOBMC33_LP_MASK = (int)0x800000,
    SYSC_AWO_GPIOBMC33_LP_POS = 23,
    SYSC_AWO_GPIOFSP_MD_MASK = (int)0x1000000,
    SYSC_AWO_GPIOFSP_MD_POS = 24,
    SYSC_AWO_GPIOFSP_LP_MASK = (int)0x2000000,
    SYSC_AWO_GPIOFSP_LP_POS = 25,
    SYSC_AWO_GPIOSMB0_MD_MASK = (int)0x4000000,
    SYSC_AWO_GPIOSMB0_MD_POS = 26,
    SYSC_AWO_GPIOSMB0_LP_MASK = (int)0x8000000,
    SYSC_AWO_GPIOSMB0_LP_POS = 27,
    SYSC_AWO_GPIOSMB1_MD_MASK = (int)0x10000000,
    SYSC_AWO_GPIOSMB1_MD_POS = 28,
    SYSC_AWO_GPIOSMB1_LP_MASK = (int)0x20000000,
    SYSC_AWO_GPIOSMB1_LP_POS = 29,
    SYSC_AWO_GPIOSGP0_MD_MASK = (int)0x40000000,
    SYSC_AWO_GPIOSGP0_MD_POS = 30,
    SYSC_AWO_GPIOSGP0_LP_MASK = (int)0x80000000,
    SYSC_AWO_GPIOSGP0_LP_POS = 31,
};

enum SYSC_AWO_REG_GP_MD_LP_CTRL1_FIELD
{
    SYSC_AWO_GPIOSGP1_MD_MASK = (int)0x1,
    SYSC_AWO_GPIOSGP1_MD_POS = 0,
    SYSC_AWO_GPIOSGP1_LP_MASK = (int)0x2,
    SYSC_AWO_GPIOSGP1_LP_POS = 1,
    SYSC_AWO_GPIORGM0_MD_MASK = (int)0x4,
    SYSC_AWO_GPIORGM0_MD_POS = 2,
    SYSC_AWO_GPIORGM0_LP_MASK = (int)0x8,
    SYSC_AWO_GPIORGM0_LP_POS = 3,
    SYSC_AWO_GPIORGM1_MD_MASK = (int)0x10,
    SYSC_AWO_GPIORGM1_MD_POS = 4,
    SYSC_AWO_GPIORGM1_LP_MASK = (int)0x20,
    SYSC_AWO_GPIORGM1_LP_POS = 5,
};

enum SYSC_AWO_REG_UART03_RX_MULTIPLEX_SEL_FIELD
{
    SYSC_AWO_UART0_RX_MULTIPLEX_SEL_MASK = (int)0xff,
    SYSC_AWO_UART0_RX_MULTIPLEX_SEL_POS = 0,
    SYSC_AWO_UART1_RX_MULTIPLEX_SEL_MASK = (int)0xff00,
    SYSC_AWO_UART1_RX_MULTIPLEX_SEL_POS = 8,
    SYSC_AWO_UART2_RX_MULTIPLEX_SEL_MASK = (int)0xff0000,
    SYSC_AWO_UART2_RX_MULTIPLEX_SEL_POS = 16,
    SYSC_AWO_UART3_RX_MULTIPLEX_SEL_MASK = (int)0xff000000,
    SYSC_AWO_UART3_RX_MULTIPLEX_SEL_POS = 24,
};

enum SYSC_AWO_REG_UART47_RX_MULTIPLEX_SEL_FIELD
{
    SYSC_AWO_UART4_RX_MULTIPLEX_SEL_MASK = (int)0xff,
    SYSC_AWO_UART4_RX_MULTIPLEX_SEL_POS = 0,
    SYSC_AWO_UART5_RX_MULTIPLEX_SEL_MASK = (int)0xff00,
    SYSC_AWO_UART5_RX_MULTIPLEX_SEL_POS = 8,
    SYSC_AWO_UART6_RX_MULTIPLEX_SEL_MASK = (int)0xff0000,
    SYSC_AWO_UART6_RX_MULTIPLEX_SEL_POS = 16,
    SYSC_AWO_UART7_RX_MULTIPLEX_SEL_MASK = (int)0xff000000,
    SYSC_AWO_UART7_RX_MULTIPLEX_SEL_POS = 24,
};

enum SYSC_AWO_REG_UART811_RX_MULTIPLEX_SEL_FIELD
{
    SYSC_AWO_UART8_RX_MULTIPLEX_SEL_MASK = (int)0xff,
    SYSC_AWO_UART8_RX_MULTIPLEX_SEL_POS = 0,
    SYSC_AWO_UART9_RX_MULTIPLEX_SEL_MASK = (int)0xff00,
    SYSC_AWO_UART9_RX_MULTIPLEX_SEL_POS = 8,
    SYSC_AWO_UART10_RX_MULTIPLEX_SEL_MASK = (int)0xff0000,
    SYSC_AWO_UART10_RX_MULTIPLEX_SEL_POS = 16,
    SYSC_AWO_UART11_RX_MULTIPLEX_SEL_MASK = (int)0xff000000,
    SYSC_AWO_UART11_RX_MULTIPLEX_SEL_POS = 24,
};

enum SYSC_AWO_REG_UART12_RX_MULTIPLEX_SEL_FIELD
{
    SYSC_AWO_UART12_RX_MULTIPLEX_SEL_MASK = (int)0xff,
    SYSC_AWO_UART12_RX_MULTIPLEX_SEL_POS = 0,
};

enum SYSC_AWO_REG_UART03_TX_MULTIPLEX_SEL_FIELD
{
    SYSC_AWO_UART0_TX_MULTIPLEX_SEL_MASK = (int)0xff,
    SYSC_AWO_UART0_TX_MULTIPLEX_SEL_POS = 0,
    SYSC_AWO_UART1_TX_MULTIPLEX_SEL_MASK = (int)0xff00,
    SYSC_AWO_UART1_TX_MULTIPLEX_SEL_POS = 8,
    SYSC_AWO_UART2_TX_MULTIPLEX_SEL_MASK = (int)0xff0000,
    SYSC_AWO_UART2_TX_MULTIPLEX_SEL_POS = 16,
    SYSC_AWO_UART30_TX_MULTIPLEX_SEL_MASK = (int)0xff000000,
    SYSC_AWO_UART30_TX_MULTIPLEX_SEL_POS = 24,
};

enum SYSC_AWO_REG_UART47_TX_MULTIPLEX_SEL_FIELD
{
    SYSC_AWO_UART4_TX_MULTIPLEX_SEL_MASK = (int)0xff,
    SYSC_AWO_UART4_TX_MULTIPLEX_SEL_POS = 0,
    SYSC_AWO_UART5_TX_MULTIPLEX_SEL_MASK = (int)0xff00,
    SYSC_AWO_UART5_TX_MULTIPLEX_SEL_POS = 8,
    SYSC_AWO_UART6_TX_MULTIPLEX_SEL_MASK = (int)0xff0000,
    SYSC_AWO_UART6_TX_MULTIPLEX_SEL_POS = 16,
    SYSC_AWO_UART7_TX_MULTIPLEX_SEL_MASK = (int)0xff000000,
    SYSC_AWO_UART7_TX_MULTIPLEX_SEL_POS = 24,
};

enum SYSC_AWO_REG_UART811_TX_MULTIPLEX_SEL_FIELD
{
    SYSC_AWO_UART8_TX_MULTIPLEX_SEL_MASK = (int)0xff,
    SYSC_AWO_UART8_TX_MULTIPLEX_SEL_POS = 0,
    SYSC_AWO_UART9_TX_MULTIPLEX_SEL_MASK = (int)0xff00,
    SYSC_AWO_UART9_TX_MULTIPLEX_SEL_POS = 8,
    SYSC_AWO_UART10_TX_MULTIPLEX_SEL_MASK = (int)0xff0000,
    SYSC_AWO_UART10_TX_MULTIPLEX_SEL_POS = 16,
    SYSC_AWO_UART11_TX_MULTIPLEX_SEL_MASK = (int)0xff000000,
    SYSC_AWO_UART11_TX_MULTIPLEX_SEL_POS = 24,
};

enum SYSC_AWO_REG_UART1231_TX_MULTIPLEX_SEL_FIELD
{
    SYSC_AWO_UART12_TX_MULTIPLEX_SEL_MASK = (int)0xff,
    SYSC_AWO_UART12_TX_MULTIPLEX_SEL_POS = 0,
    SYSC_AWO_UART31_TX_MULTIPLEX_SEL_MASK = (int)0xff00,
    SYSC_AWO_UART31_TX_MULTIPLEX_SEL_POS = 8,
};

#ifdef __cplusplus
}
#endif

#endif

