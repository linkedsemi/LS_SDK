#ifndef REG_PIPE_SYS_TYPE_H_
#define REG_PIPE_SYS_TYPE_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PIPE_SYS_CFG ((reg_pipe_sys_t *)REG_PIPE_SYS_CFG_BASE)

typedef struct
{
    volatile uint32_t PCIE0_PCLK_CLK_DEGLITCH_SW2_REG; //0x0
    volatile uint32_t PCIE0_PCLK_CLK_CG0_REG; //0x4
    volatile uint32_t PCIE0_AUXCLK_CLK_DEGLITCH_SW4_REG; //0x8
    volatile uint32_t PCIE0_AUXCLK_CLK_DIV0_DIV4_REG; //0xc
    volatile uint32_t PCIE0_AUXCLK_CLK_CG0_REG; //0x10
    volatile uint32_t PCIE1_PCLK_CLK_DEGLITCH_SW2_REG; //0x14
    volatile uint32_t PCIE1_PCLK_CLK_CG0_REG; //0x18
    volatile uint32_t PCIE1_AUXCLK_CLK_DEGLITCH_SW4_REG; //0x1c
    volatile uint32_t PCIE1_AUXCLK_CLK_DIV0_DIV4_REG; //0x20
    volatile uint32_t PCIE1_AUXCLK_CLK_CG0_REG; //0x24
    volatile uint32_t VP0_INT_CLK_CLK_DEGLITCH_SW2_REG; //0x28
    volatile uint32_t VP0_INT_CLK_CLK_DIV0_DIV2_REG; //0x2c
    volatile uint32_t VP0_INT_CLK_CLK_CG0_REG; //0x30
    volatile uint32_t VP0_VDAC_CLK_CLK_DEGLITCH_SW2_REG; //0x34
    volatile uint32_t VP0_VDAC_CLK_CLK_DIV0_DIV4_2_REG; //0x38
    volatile uint32_t VP0_VDAC_CLK_CLK_CG0_REG; //0x3c
    volatile uint32_t VP0_OUT_CLK_CLK_DEGLITCH_SW2_REG; //0x40
    volatile uint32_t VP0_OUT_CLK_CLK_DIV0_DIV4_6_REG; //0x44
    volatile uint32_t VP0_OUT_CLK_CLK_CG0_REG; //0x48
    volatile uint32_t VP1_INT_CLK_CLK_DEGLITCH_SW2_REG; //0x4c
    volatile uint32_t VP1_INT_CLK_CLK_DIV0_DIV2_REG; //0x50
    volatile uint32_t VP1_INT_CLK_CLK_CG0_REG; //0x54
    volatile uint32_t VP1_VDAC_CLK_CLK_DEGLITCH_SW2_REG; //0x58
    volatile uint32_t VP1_VDAC_CLK_CLK_DIV0_DIV4_2_REG; //0x5c
    volatile uint32_t VP1_VDAC_CLK_CLK_CG0_REG; //0x60
    volatile uint32_t VP1_OUT_CLK_CLK_DEGLITCH_SW2_REG; //0x64
    volatile uint32_t VP1_OUT_CLK_CLK_DIV0_DIV4_6_REG; //0x68
    volatile uint32_t VP1_OUT_CLK_CLK_CG0_REG; //0x6c
    volatile uint32_t EMMC_CORE_CLK_CLK_DEGLITCH_SW3_REG; //0x70
    volatile uint32_t EMMC_CORE_CLK_CLK_DIV0_DIV2_REG; //0x74
    volatile uint32_t EMMC_CORE_CLK_CLK_CG0_REG; //0x78
    volatile uint32_t EMMC_CCLK_TX_CLK_CLK_DEGLITCH_SW2_REG; //0x7c
    volatile uint32_t EMMC_CCLK_TX_CLK_CLK_DIV0_DIV10_REG; //0x80
    volatile uint32_t EMMC_CCLK_TX_CLK_CLK_CG0_REG; //0x84
    volatile uint32_t EMMC_TM_CLK_CLK_DEGLITCH_SW3_REG; //0x88
    volatile uint32_t EMMC_TM_CLK_CLK_DIV0_DIV8_REG; //0x8c
    volatile uint32_t EMMC_TM_CLK_CLK_CG0_REG; //0x90
    volatile uint32_t EMMC_CCLK_RX_CLK_CLK_DEGLITCH_SW3_REG; //0x94
    volatile uint32_t EMMC_CCLK_RX_CLK_CLK_DIV0_DIV10_REG; //0x98
    volatile uint32_t EMMC_CCLK_RX_CLK_CLK_CG0_REG; //0x9c
    volatile uint32_t WDT3_LRC_CLK_CLK_DEGLITCH_SW2_REG; //0xa0
    volatile uint32_t WDT3_LRC_CLK_CLK_CG0_REG; //0xa4
    volatile uint32_t CLK_SGETH1_TX_CLK_DEGLITCH_SW3_REG; //0xa8
    volatile uint32_t CLK_SGETH1_TX_CLK_DIV0_DIV6_REG; //0xac
    volatile uint32_t CLK_SGETH1_TX_CLK_CG0_REG; //0xb0
    volatile uint32_t CLK_SGETH1_RX_CLK_DEGLITCH_SW3_REG; //0xb4
    volatile uint32_t CLK_SGETH1_RX_CLK_DIV0_DIV6_REG; //0xb8
    volatile uint32_t CLK_SGETH1_RX_CLK_CG0_REG; //0xbc
    volatile uint32_t CLK_SGETH1_125_TX_CLK_DEGLITCH_SW3_REG; //0xc0
    volatile uint32_t CLK_SGETH1_125_TX_CLK_DIV0_DIV6_REG; //0xc4
    volatile uint32_t CLK_SGETH1_125_TX_CLK_CG0_REG; //0xc8
    volatile uint32_t CLK_SGETH1_125_RX_CLK_DEGLITCH_SW3_REG; //0xcc
    volatile uint32_t CLK_SGETH1_125_RX_CLK_DIV0_DIV6_REG; //0xd0
    volatile uint32_t CLK_SGETH1_125_RX_CLK_CG0_REG; //0xd4
    volatile uint32_t CLK_SGETH2_TX_CLK_DEGLITCH_SW3_REG; //0xd8
    volatile uint32_t CLK_SGETH2_TX_CLK_DIV0_DIV6_REG; //0xdc
    volatile uint32_t CLK_SGETH2_TX_CLK_CG0_REG; //0xe0
    volatile uint32_t CLK_SGETH2_RX_CLK_DEGLITCH_SW3_REG; //0xe4
    volatile uint32_t CLK_SGETH2_RX_CLK_DIV0_DIV6_REG; //0xe8
    volatile uint32_t CLK_SGETH2_RX_CLK_CG0_REG; //0xec
    volatile uint32_t CLK_SGETH2_125_TX_CLK_DEGLITCH_SW3_REG; //0xf0
    volatile uint32_t CLK_SGETH2_125_TX_CLK_DIV0_DIV6_REG; //0xf4
    volatile uint32_t CLK_SGETH2_125_TX_CLK_CG0_REG; //0xf8
    volatile uint32_t CLK_SGETH2_125_RX_CLK_DEGLITCH_SW3_REG; //0xfc
    volatile uint32_t CLK_SGETH2_125_RX_CLK_DIV0_DIV6_REG; //0x100
    volatile uint32_t CLK_SGETH2_125_RX_CLK_CG0_REG; //0x104
    volatile uint32_t PHY_LNK_CLK_TX_CLK_DEGLITCH_SW3_REG; //0x108
    volatile uint32_t PHY_LNK_CLK_TX_CLK_CG0_REG; //0x10c
    volatile uint32_t SOFT_RST_N_REG0; //0x110
    volatile uint32_t SOFT_RST_N_REG0_CLR; //0x114
    volatile uint32_t PIPE_SYS_DUMMY0; //0x118
    volatile uint32_t PIPE_SYS_DUMMY1; //0x11c
    volatile uint32_t PIPE_SYS_DUMMY2; //0x120
    volatile uint32_t PIPE_SYS_DUMMY3; //0x124
    volatile uint32_t PIPE_SYS_RD_DUMMY0; //0x128
    volatile uint32_t PIPE_SYS_RD_DUMMY1; //0x12c
    volatile uint32_t PIPE_SYS_RD_DUMMY2; //0x130
    volatile uint32_t PIPE_SYS_RD_DUMMY3; //0x134
    volatile uint32_t EMMC_CTL0; //0x138
    volatile uint32_t EMMC_RD0; //0x13c
    volatile uint32_t EMMC_RD1; //0x140
    volatile uint32_t EMMC_REG0; //0x144
    volatile uint32_t EMMC_REG1; //0x148
    volatile uint32_t EMMC_REG2; //0x14c
    volatile uint32_t ADDR_HIGH2BIT_XOR_PCIE0; //0x150
    volatile uint32_t ADDR_HIGH2BIT_XOR_PCIE1; //0x154
    volatile uint32_t GDMA2_MODULE_EN; //0x158
    volatile uint32_t DPTX_CTL; //0x15c
    volatile uint32_t SGMII_CTRL0; //0x160
    volatile uint32_t PIPE_SYS_CRG_AXI_CLK_TOP_RST_N_REG0; //0x164
    volatile uint32_t PIPE_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_CLR; //0x168
    volatile uint32_t PIPE_SYS_CRG_APB_CLK_TOP_RST_N_REG0; //0x16c
    volatile uint32_t PIPE_SYS_CRG_APB_CLK_TOP_RST_N_REG0_CLR; //0x170
    volatile uint32_t PIPE_SYS_CRG_AHB_CLK_TOP_RST_N_REG0; //0x174
    volatile uint32_t PIPE_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_CLR; //0x178
    volatile uint32_t PIPE_SYS_CFG_REG1; //0x17c
    volatile uint32_t PIPE_SYS_CFG_REG2; //0x180
    volatile uint32_t PIPE_SYS_CFG_REG3; //0x184
    volatile uint32_t PIPE_SYS_CFG_LOCK; //0x188
    volatile uint32_t DPTX_CONFIG0; //0x18c
    volatile uint32_t DPTX_CONFIG1; //0x190
    volatile uint32_t DPTX_LANE; //0x194
    volatile uint32_t PHY_DPTX_PHY_STATUS; //0x198
    volatile uint32_t VPN_SEL; //0x19c
    volatile uint32_t PIPE_SYS_ADJUST_ADB400_EN; //0x1a0
    volatile uint32_t HF_DLL_CTRL_RD_REG; //0x1a4
    volatile uint32_t HF_DLL_CTRL_REG; //0x1a8
    volatile uint32_t PCIE1_REG0; //0x1ac
    volatile uint32_t PCIE1_REG1; //0x1b0
    volatile uint32_t PCIE1_REG2; //0x1b4
    volatile uint32_t PCIE1_REG3; //0x1b8
    volatile uint32_t PCIE1_REG4; //0x1bc
    volatile uint32_t PCIE1_REG5; //0x1c0
    volatile uint32_t PCIE1_REG6; //0x1c4
    volatile uint32_t PCIE1_REG7; //0x1c8
    volatile uint32_t PCIE1_REG8; //0x1cc
    volatile uint32_t PCIE1_REG9; //0x1d0
    volatile uint32_t PCIE1_REG10; //0x1d4
    volatile uint32_t PCIE1_REG11; //0x1d8
    volatile uint32_t PCIE1_REG12; //0x1dc
    volatile uint32_t PCIE1_REG13; //0x1e0
    volatile uint32_t PCIE1_REG14; //0x1e4
    volatile uint32_t PCIE1_REG15; //0x1e8
    volatile uint32_t PCIE1_REG16; //0x1ec
    volatile uint32_t PCIE1_REG17; //0x1f0
    volatile uint32_t PCIE1_REG18; //0x1f4
    volatile uint32_t PCIE1_REG19; //0x1f8
    volatile uint32_t PCIE1_REG20; //0x1fc
    volatile uint32_t PCIE1_REG21; //0x200
    volatile uint32_t PCIE1_REG22; //0x204
    volatile uint32_t PCIE1_REG23; //0x208
    volatile uint32_t PCIE1_REG24; //0x20c
    volatile uint32_t PCIE1_REG25; //0x210
    volatile uint32_t PCIE1_REG26; //0x214
    volatile uint32_t PCIE1_REG27; //0x218
    volatile uint32_t PCIE1_REG28; //0x21c
    volatile uint32_t PCIE1_REG29; //0x220
    volatile uint32_t PCIE1_REG30; //0x224
    volatile uint32_t PCIE1_REG31; //0x228
    volatile uint32_t PCIE1_REG32; //0x22c
    volatile uint32_t PCIE1_REG33; //0x230
    volatile uint32_t PCIE1_REG34; //0x234
    volatile uint32_t PCIE1_REG35; //0x238
    volatile uint32_t PCIE1_REG36; //0x23c
    volatile uint32_t PCIE1_REG37; //0x240
    volatile uint32_t PCIE1_REG38; //0x244
    volatile uint32_t PCIE1_REG39; //0x248
    volatile uint32_t PCIE1_REG40; //0x24c
    volatile uint32_t PCIE1_REG41; //0x250
    volatile uint32_t PCIE1_REG42; //0x254
    volatile uint32_t PCIE1_REG43; //0x258
    volatile uint32_t PCIE1_REG44; //0x25c
    volatile uint32_t PCIE1_REG45; //0x260
    volatile uint32_t PCIE1_REG46; //0x264
    volatile uint32_t PCIE1_REG47; //0x268
    volatile uint32_t PCIE1_REG48; //0x26c
    volatile uint32_t PCIE1_REG49; //0x270
    volatile uint32_t PCIE1_REG50; //0x274
    volatile uint32_t PCIE1_REG51; //0x278
    volatile uint32_t PCIE1_REG52; //0x27c
    volatile uint32_t PCIE1_REG53; //0x280
    volatile uint32_t PCIE1_REG54; //0x284
    volatile uint32_t PCIE1_REG55; //0x288
    volatile uint32_t PCIE1_REG56; //0x28c
    volatile uint32_t PCIE1_REG57; //0x290
    volatile uint32_t PCIE1_REG58; //0x294
    volatile uint32_t PCIE1_REG59; //0x298
    volatile uint32_t PCIE1_REG60; //0x29c
    volatile uint32_t PCIE1_REG61; //0x2a0
    volatile uint32_t PCIE1_REG62; //0x2a4
    volatile uint32_t PCIE1_REG63; //0x2a8
    volatile uint32_t PCIE1_REG64; //0x2ac
    volatile uint32_t PCIE1_REG65; //0x2b0
    volatile uint32_t PCIE1_REG66; //0x2b4
    volatile uint32_t PCIE1_REG67; //0x2b8
    volatile uint32_t PCIE1_REG68; //0x2bc
    volatile uint32_t PCIE1_REG69; //0x2c0
    volatile uint32_t PCIE1_REG70; //0x2c4
    volatile uint32_t PCIE1_REG71; //0x2c8
    volatile uint32_t PCIE1_REG72; //0x2cc
    volatile uint32_t PCIE1_REG73; //0x2d0
    volatile uint32_t PCIE1_REG74; //0x2d4
    volatile uint32_t PCIE1_REG75; //0x2d8
    volatile uint32_t PCIE1_REG76; //0x2dc
    volatile uint32_t PCIE1_REG77; //0x2e0
    volatile uint32_t PCIE1_REG78; //0x2e4
    volatile uint32_t PCIE1_REG79; //0x2e8
    volatile uint32_t PCIE1_REG80; //0x2ec
    volatile uint32_t PCIE1_REG81; //0x2f0
    volatile uint32_t PCIE1_REG82; //0x2f4
    volatile uint32_t PCIE1_REG83; //0x2f8
    volatile uint32_t PCIE1_REG84; //0x2fc
    volatile uint32_t PCIE1_REG85; //0x300
    volatile uint32_t PCIE1_REG86; //0x304
    volatile uint32_t PCIE1_REG87; //0x308
    volatile uint32_t PCIE1_REG88; //0x30c
    volatile uint32_t PCIE1_REG89; //0x310
    volatile uint32_t PCIE1_REG90; //0x314
    volatile uint32_t PCIE1_REG91; //0x318
    volatile uint32_t PCIE1_REG92; //0x31c
    volatile uint32_t PCIE1_REG93; //0x320
    volatile uint32_t PCIE1_REG94; //0x324
    volatile uint32_t PCIE1_REG95; //0x328
    volatile uint32_t PCIE1_REG96; //0x32c
    volatile uint32_t PCIE1_REG97; //0x330
    volatile uint32_t PCIE1_REG98; //0x334
    volatile uint32_t PCIE1_REG99; //0x338
    volatile uint32_t PCIE1_REG100; //0x33c
    volatile uint32_t PCIE1_REG101; //0x340
    volatile uint32_t PCIE1_REG102; //0x344
    volatile uint32_t PCIE1_REG103; //0x348
    volatile uint32_t PCIE1_REG104; //0x34c
    volatile uint32_t PCIE1_REG105; //0x350
    volatile uint32_t PCIE1_REG106; //0x354
    volatile uint32_t PCIE1_REG107; //0x358
    volatile uint32_t PCIE1_REG108; //0x35c
    volatile uint32_t PCIE1_REG109; //0x360
    volatile uint32_t PCIE1_REG110; //0x364
    volatile uint32_t PCIE1_REG111; //0x368
    volatile uint32_t PCIE1_REG112; //0x36c
    volatile uint32_t PCIE1_REG113; //0x370
    volatile uint32_t PCIE1_REG114; //0x374
    volatile uint32_t PCIE1_REG115; //0x378
    volatile uint32_t PCIE1_REG116; //0x37c
    volatile uint32_t PCIE1_REG117; //0x380
    volatile uint32_t PCIE1_REG118; //0x384
    volatile uint32_t PCIE1_REG119; //0x388
    volatile uint32_t PCIE1_REG120; //0x38c
    volatile uint32_t PCIE1_REG121; //0x390
    volatile uint32_t PCIE1_REG122; //0x394
    volatile uint32_t PCIE1_REG123; //0x398
    volatile uint32_t PCIE1_REG124; //0x39c
    volatile uint32_t PCIE1_REG125; //0x3a0
    volatile uint32_t PCIE1_REG126; //0x3a4
    volatile uint32_t PCIE1_REG127; //0x3a8
    volatile uint32_t PCIE1_REG128; //0x3ac
    volatile uint32_t PCIE1_REG129; //0x3b0
    volatile uint32_t PCIE1_REG130; //0x3b4
    volatile uint32_t PCIE1_REG131; //0x3b8
    volatile uint32_t PCIE1_REG132; //0x3bc
    volatile uint32_t PCIE1_REG133; //0x3c0
    volatile uint32_t PCIE1_REG134; //0x3c4
    volatile uint32_t PCIE1_REG135; //0x3c8
    volatile uint32_t PCIE1_REG136; //0x3cc
    volatile uint32_t PCIE1_REG137; //0x3d0
    volatile uint32_t PCIE1_REG138; //0x3d4
    volatile uint32_t PCIE1_REG139; //0x3d8
    volatile uint32_t PCIE1_REG140; //0x3dc
    volatile uint32_t PCIE1_REG141; //0x3e0
    volatile uint32_t PCIE1_REG142; //0x3e4
    volatile uint32_t PCIE1_REG143; //0x3e8
    volatile uint32_t PCIE1_REG144; //0x3ec
    volatile uint32_t PCIE1_REG145; //0x3f0
    volatile uint32_t PCIE1_REG146; //0x3f4
    volatile uint32_t PCIE1_REG147; //0x3f8
    volatile uint32_t PCIE1_REG148; //0x3fc
    volatile uint32_t PCIE1_REG149; //0x400
    volatile uint32_t PCIE1_REG150; //0x404
    volatile uint32_t PCIE1_REG151; //0x408
    volatile uint32_t PCIE1_REG152; //0x40c
    volatile uint32_t PCIE1_REG153; //0x410
    volatile uint32_t PCIE1_REG154; //0x414
    volatile uint32_t PCIE1_REG155; //0x418
    volatile uint32_t PCIE1_REG156; //0x41c
    volatile uint32_t PCIE1_REG157; //0x420
    volatile uint32_t PCIE1_REG158; //0x424
    volatile uint32_t PCIE1_REG159; //0x428
    volatile uint32_t PCIE1_REG160; //0x42c
    volatile uint32_t PCIE1_REG161; //0x430
    volatile uint32_t PCIE1_REG162; //0x434
    volatile uint32_t PCIE1_REG163; //0x438
    volatile uint32_t PCIE1_REG164; //0x43c
    volatile uint32_t PCIE1_REG165; //0x440
    volatile uint32_t PCIE1_REG166; //0x444
    volatile uint32_t PCIE1_REG167; //0x448
    volatile uint32_t PCIE1_REG168; //0x44c
    volatile uint32_t PCIE1_REG169; //0x450
    volatile uint32_t PCIE1_REG170; //0x454
    volatile uint32_t PCIE1_REG171; //0x458
    volatile uint32_t PCIE1_REG172; //0x45c
    volatile uint32_t PCIE1_REG173; //0x460
    volatile uint32_t PCIE1_REG174; //0x464
    volatile uint32_t PCIE1_REG175; //0x468
    volatile uint32_t PCIE1_REG176; //0x46c
    volatile uint32_t PCIE1_REG177; //0x470
    volatile uint32_t PCIE1_REG178; //0x474
    volatile uint32_t PCIE1_REG179; //0x478
    volatile uint32_t PCIE1_REG180; //0x47c
    volatile uint32_t PCIE1_REG181; //0x480
    volatile uint32_t PCIE1_REG182; //0x484
    volatile uint32_t PCIE1_REG183; //0x488
    volatile uint32_t PCIE1_REG184; //0x48c
    volatile uint32_t PCIE1_REG185; //0x490
    volatile uint32_t PCIE1_REG186; //0x494
    volatile uint32_t PCIE1_REG187; //0x498
    volatile uint32_t PCIE1_REG188; //0x49c
    volatile uint32_t PCIE1_REG189; //0x4a0
    volatile uint32_t PCIE1_REG190; //0x4a4
    volatile uint32_t PCIE1_REG191; //0x4a8
    volatile uint32_t PCIE1_REG192; //0x4ac
    volatile uint32_t PCIE1_REG193; //0x4b0
    volatile uint32_t PCIE1_REG194; //0x4b4
    volatile uint32_t PCIE1_REG195; //0x4b8
    volatile uint32_t PCIE1_REG196; //0x4bc
    volatile uint32_t PCIE1_REG197; //0x4c0
    volatile uint32_t PCIE1_REG198; //0x4c4
    volatile uint32_t PCIE1_REG199; //0x4c8
    volatile uint32_t PCIE1_REG200; //0x4cc
    volatile uint32_t PCIE1_REG201; //0x4d0
    volatile uint32_t PCIE1_REG202; //0x4d4
    volatile uint32_t PCIE1_REG203; //0x4d8
    volatile uint32_t PCIE1_REG204; //0x4dc
    volatile uint32_t PCIE1_REG205; //0x4e0
    volatile uint32_t PCIE1_REG206; //0x4e4
    volatile uint32_t PCIE1_REG207; //0x4e8
    volatile uint32_t PCIE1_REG208; //0x4ec
    volatile uint32_t PCIE1_REG209; //0x4f0
    volatile uint32_t PCIE1_REG210; //0x4f4
    volatile uint32_t PCIE1_REG211; //0x4f8
    volatile uint32_t PCIE1_REG212; //0x4fc
    volatile uint32_t PCIE1_REG213; //0x500
    volatile uint32_t PCIE1_REG214; //0x504
    volatile uint32_t PCIE1_REG215; //0x508
    volatile uint32_t PCIE1_REG216; //0x50c
    volatile uint32_t PCIE1_REG217; //0x510
    volatile uint32_t PCIE1_REG218; //0x514
    volatile uint32_t PCIE1_REG219; //0x518
    volatile uint32_t PCIE1_REG220; //0x51c
    volatile uint32_t PCIE1_REG221; //0x520
    volatile uint32_t PCIE1_REG222; //0x524
    volatile uint32_t PCIE1_REG223; //0x528
    volatile uint32_t PCIE1_REG224; //0x52c
    volatile uint32_t PCIE1_REG225; //0x530
    volatile uint32_t PCIE1_REG226; //0x534
    volatile uint32_t PCIE1_REG227; //0x538
    volatile uint32_t PCIE1_REG228; //0x53c
    volatile uint32_t PCIE1_REG229; //0x540
    volatile uint32_t PCIE1_REG230; //0x544
    volatile uint32_t PCIE1_REG231; //0x548
    volatile uint32_t PCIE1_REG232; //0x54c
    volatile uint32_t PCIE1_REG233; //0x550
    volatile uint32_t PCIE1_REG234; //0x554
    volatile uint32_t PCIE1_REG235; //0x558
    volatile uint32_t PCIE1_REG236; //0x55c
    volatile uint32_t PCIE1_REG237; //0x560
    volatile uint32_t PCIE1_REG238; //0x564
    volatile uint32_t PCIE1_REG239; //0x568
    volatile uint32_t PCIE1_REG240; //0x56c
    volatile uint32_t PCIE1_REG241; //0x570
    volatile uint32_t PCIE1_REG242; //0x574
    volatile uint32_t PCIE1_REG243; //0x578
    volatile uint32_t PCIE1_REG244; //0x57c
    volatile uint32_t PCIE1_REG245; //0x580
    volatile uint32_t PCIE1_REG246; //0x584
    volatile uint32_t PCIE1_REG247; //0x588
    volatile uint32_t PCIE1_REG248; //0x58c
    volatile uint32_t PCIE1_REG249; //0x590
    volatile uint32_t PCIE1_REG250; //0x594
    volatile uint32_t PCIE1_REG251; //0x598
    volatile uint32_t PCIE1_REG252; //0x59c
    volatile uint32_t PCIE1_REG253; //0x5a0
    volatile uint32_t PCIE1_REG254; //0x5a4
    volatile uint32_t PCIE1_REG255; //0x5a8
    volatile uint32_t PCIE1_REG256; //0x5ac
    volatile uint32_t PCIE1_REG257; //0x5b0
    volatile uint32_t PCIE1_REG258; //0x5b4
    volatile uint32_t PCIE1_REG259; //0x5b8
    volatile uint32_t PCIE1_REG260; //0x5bc
    volatile uint32_t PCIE1_REG261; //0x5c0
    volatile uint32_t PCIE1_REG262; //0x5c4
    volatile uint32_t PCIE1_REG263; //0x5c8
    volatile uint32_t PCIE1_REG264; //0x5cc
    volatile uint32_t PCIE1_REG265; //0x5d0
    volatile uint32_t PCIE1_REG266; //0x5d4
    volatile uint32_t PCIE1_REG267; //0x5d8
    volatile uint32_t PCIE1_REG268; //0x5dc
    volatile uint32_t PCIE1_REG269; //0x5e0
    volatile uint32_t PCIE1_REG270; //0x5e4
    volatile uint32_t PCIE1_REG271; //0x5e8
    volatile uint32_t PCIE1_REG272; //0x5ec
    volatile uint32_t PCIE1_REG273; //0x5f0
    volatile uint32_t PCIE1_REG274; //0x5f4
    volatile uint32_t PCIE1_REG275; //0x5f8
    volatile uint32_t PCIE1_REG276; //0x5fc
    volatile uint32_t PCIE1_REG277; //0x600
    volatile uint32_t PCIE1_REG278; //0x604
    volatile uint32_t PCIE1_REG279; //0x608
    volatile uint32_t PCIE1_REG280; //0x60c
    volatile uint32_t PCIE1_REG281; //0x610
    volatile uint32_t PCIE1_REG282; //0x614
    volatile uint32_t PCIE1_REG283; //0x618
    volatile uint32_t PCIE1_REG284; //0x61c
    volatile uint32_t PCIE1_REG285; //0x620
    volatile uint32_t PCIE1_REG286; //0x624
    volatile uint32_t PCIE1_REG287; //0x628
    volatile uint32_t PCIE1_REG288; //0x62c
    volatile uint32_t PCIE1_RAM_REG_0; //0x630
    volatile uint32_t PCIE1_RAM_REG_1; //0x634
    volatile uint32_t PCIE1_RAM_REG_2; //0x638
    volatile uint32_t PCIE1_RAM_REG_3; //0x63c
    volatile uint32_t PCIE1_RAM_REG_4; //0x640
    volatile uint32_t PCIE1_RAM_REG_5; //0x644
    volatile uint32_t PCIE1_AXI_SLV_REG0; //0x648
    volatile uint32_t PCIE1_AXI_SLV_REG1; //0x64c
    volatile uint32_t PCIE1_AXI_SLV_REG2; //0x650
    volatile uint32_t PCIE1_AXI_SLV_REG3; //0x654
    volatile uint32_t PCIE1_AXI_SLV_REG4; //0x658
    volatile uint32_t PCIE1_AXI_SLV_REG5; //0x65c
    volatile uint32_t PCIE1_AXI_MST_REG0; //0x660
    volatile uint32_t PCIE1_AXI_MST_REG1; //0x664
    volatile uint32_t PCIE1_AXI_MST_REG2; //0x668
    volatile uint32_t PCIE1_AXI_MST_REG3; //0x66c
    volatile uint32_t PCIE1_AXI_MST_REG4; //0x670
    volatile uint32_t PCIE1_AXI_MST_REG5; //0x674
    volatile uint32_t PCIE1_AXI_MST_REG6; //0x678
    volatile uint32_t PCIE1_AXI_MST_REG7; //0x67c
    volatile uint32_t PCIE1_DBI_SLV_REG0; //0x680
    volatile uint32_t PCIE1_VEN_MSG_START_T; //0x684
    volatile uint32_t PCIE1_VEN_MSI_START_T; //0x688
    volatile uint32_t PCIE1_APP_LTR_MSG_START_T; //0x68c
    volatile uint32_t PCIE1_APP_OBFF_IDLE_MSG_START_T; //0x690
    volatile uint32_t PCIE1_APP_OBFF_OBFF_MSG_START_T; //0x694
    volatile uint32_t PCIE1_APP_OBFF_CPU_ACTIVE_MSG_START_T; //0x698
    volatile uint32_t PCIE1_VEN_MSG_REQ_TIMEOUT_CNT; //0x69c
    volatile uint32_t PCIE0_DUMMY0; //0x6a0
    volatile uint32_t PCIE0_RD_DUMMY0; //0x6a4
    volatile uint32_t PCIE0_REG0; //0x6a8
    volatile uint32_t PCIE0_REG1; //0x6ac
    volatile uint32_t PCIE0_REG2; //0x6b0
    volatile uint32_t PCIE0_REG3; //0x6b4
    volatile uint32_t PCIE0_REG4; //0x6b8
    volatile uint32_t PCIE0_REG5; //0x6bc
    volatile uint32_t PCIE0_REG6; //0x6c0
    volatile uint32_t PCIE0_REG7; //0x6c4
    volatile uint32_t PCIE0_REG8; //0x6c8
    volatile uint32_t PCIE0_REG9; //0x6cc
    volatile uint32_t PCIE0_REG10; //0x6d0
    volatile uint32_t PCIE0_REG11; //0x6d4
    volatile uint32_t PCIE0_REG12; //0x6d8
    volatile uint32_t PCIE0_REG13; //0x6dc
    volatile uint32_t PCIE0_REG14; //0x6e0
    volatile uint32_t PCIE0_REG15; //0x6e4
    volatile uint32_t PCIE0_REG16; //0x6e8
    volatile uint32_t PCIE0_REG17; //0x6ec
    volatile uint32_t PCIE0_REG18; //0x6f0
    volatile uint32_t PCIE0_REG19; //0x6f4
    volatile uint32_t PCIE0_REG20; //0x6f8
    volatile uint32_t PCIE0_REG21; //0x6fc
    volatile uint32_t PCIE0_REG22; //0x700
    volatile uint32_t PCIE0_REG23; //0x704
    volatile uint32_t PCIE0_REG24; //0x708
    volatile uint32_t PCIE0_REG25; //0x70c
    volatile uint32_t PCIE0_REG26; //0x710
    volatile uint32_t PCIE0_REG27; //0x714
    volatile uint32_t PCIE0_REG28; //0x718
    volatile uint32_t PCIE0_REG29; //0x71c
    volatile uint32_t PCIE0_REG30; //0x720
    volatile uint32_t PCIE0_REG31; //0x724
    volatile uint32_t PCIE0_REG32; //0x728
    volatile uint32_t PCIE0_REG33; //0x72c
    volatile uint32_t PCIE0_REG34; //0x730
    volatile uint32_t PCIE0_REG35; //0x734
    volatile uint32_t PCIE0_REG36; //0x738
    volatile uint32_t PCIE0_REG37; //0x73c
    volatile uint32_t PCIE0_REG38; //0x740
    volatile uint32_t PCIE0_REG39; //0x744
    volatile uint32_t PCIE0_REG40; //0x748
    volatile uint32_t PCIE0_REG41; //0x74c
    volatile uint32_t PCIE0_REG42; //0x750
    volatile uint32_t PCIE0_REG43; //0x754
    volatile uint32_t PCIE0_REG44; //0x758
    volatile uint32_t PCIE0_REG45; //0x75c
    volatile uint32_t PCIE0_REG46; //0x760
    volatile uint32_t PCIE0_REG47; //0x764
    volatile uint32_t PCIE0_REG48; //0x768
    volatile uint32_t PCIE0_REG49; //0x76c
    volatile uint32_t PCIE0_REG50; //0x770
    volatile uint32_t PCIE0_REG51; //0x774
    volatile uint32_t PCIE0_REG52; //0x778
    volatile uint32_t PCIE0_REG53; //0x77c
    volatile uint32_t PCIE0_REG54; //0x780
    volatile uint32_t PCIE0_REG55; //0x784
    volatile uint32_t PCIE0_REG56; //0x788
    volatile uint32_t PCIE0_REG57; //0x78c
    volatile uint32_t PCIE0_REG58; //0x790
    volatile uint32_t PCIE0_REG59; //0x794
    volatile uint32_t PCIE0_REG60; //0x798
    volatile uint32_t PCIE0_REG61; //0x79c
    volatile uint32_t PCIE0_REG62; //0x7a0
    volatile uint32_t PCIE0_REG63; //0x7a4
    volatile uint32_t PCIE0_REG64; //0x7a8
    volatile uint32_t PCIE0_REG65; //0x7ac
    volatile uint32_t PCIE0_REG66; //0x7b0
    volatile uint32_t PCIE0_REG67; //0x7b4
    volatile uint32_t PCIE0_REG68; //0x7b8
    volatile uint32_t PCIE0_REG69; //0x7bc
    volatile uint32_t PCIE0_REG70; //0x7c0
    volatile uint32_t PCIE0_REG71; //0x7c4
    volatile uint32_t PCIE0_REG72; //0x7c8
    volatile uint32_t PCIE0_REG73; //0x7cc
    volatile uint32_t PCIE0_REG74; //0x7d0
    volatile uint32_t PCIE0_REG75; //0x7d4
    volatile uint32_t PCIE0_REG76; //0x7d8
    volatile uint32_t PCIE0_REG77; //0x7dc
    volatile uint32_t PCIE0_REG78; //0x7e0
    volatile uint32_t PCIE0_REG79; //0x7e4
    volatile uint32_t PCIE0_REG80; //0x7e8
    volatile uint32_t PCIE0_REG81; //0x7ec
    volatile uint32_t PCIE0_REG82; //0x7f0
    volatile uint32_t PCIE0_REG83; //0x7f4
    volatile uint32_t PCIE0_REG84; //0x7f8
    volatile uint32_t PCIE0_REG85; //0x7fc
    volatile uint32_t PCIE0_REG86; //0x800
    volatile uint32_t PCIE0_REG87; //0x804
    volatile uint32_t PCIE0_REG88; //0x808
    volatile uint32_t PCIE0_REG89; //0x80c
    volatile uint32_t PCIE0_REG90; //0x810
    volatile uint32_t PCIE0_REG91; //0x814
    volatile uint32_t PCIE0_REG92; //0x818
    volatile uint32_t PCIE0_REG93; //0x81c
    volatile uint32_t PCIE0_REG94; //0x820
    volatile uint32_t PCIE0_REG95; //0x824
    volatile uint32_t PCIE0_REG96; //0x828
    volatile uint32_t PCIE0_REG97; //0x82c
    volatile uint32_t PCIE0_REG98; //0x830
    volatile uint32_t PCIE0_REG99; //0x834
    volatile uint32_t PCIE0_REG100; //0x838
    volatile uint32_t PCIE0_REG101; //0x83c
    volatile uint32_t PCIE0_REG102; //0x840
    volatile uint32_t PCIE0_REG103; //0x844
    volatile uint32_t PCIE0_REG104; //0x848
    volatile uint32_t PCIE0_REG105; //0x84c
    volatile uint32_t PCIE0_REG106; //0x850
    volatile uint32_t PCIE0_REG107; //0x854
    volatile uint32_t PCIE0_REG108; //0x858
    volatile uint32_t PCIE0_REG109; //0x85c
    volatile uint32_t PCIE0_REG110; //0x860
    volatile uint32_t PCIE0_REG111; //0x864
    volatile uint32_t PCIE0_REG112; //0x868
    volatile uint32_t PCIE0_REG113; //0x86c
    volatile uint32_t PCIE0_REG114; //0x870
    volatile uint32_t PCIE0_REG115; //0x874
    volatile uint32_t PCIE0_REG116; //0x878
    volatile uint32_t PCIE0_REG117; //0x87c
    volatile uint32_t PCIE0_REG118; //0x880
    volatile uint32_t PCIE0_REG119; //0x884
    volatile uint32_t PCIE0_REG120; //0x888
    volatile uint32_t PCIE0_REG121; //0x88c
    volatile uint32_t PCIE0_REG122; //0x890
    volatile uint32_t PCIE0_REG123; //0x894
    volatile uint32_t PCIE0_REG124; //0x898
    volatile uint32_t PCIE0_REG125; //0x89c
    volatile uint32_t PCIE0_REG126; //0x8a0
    volatile uint32_t PCIE0_REG127; //0x8a4
    volatile uint32_t PCIE0_REG128; //0x8a8
    volatile uint32_t PCIE0_REG129; //0x8ac
    volatile uint32_t PCIE0_REG130; //0x8b0
    volatile uint32_t PCIE0_REG131; //0x8b4
    volatile uint32_t PCIE0_REG132; //0x8b8
    volatile uint32_t PCIE0_REG133; //0x8bc
    volatile uint32_t PCIE0_REG134; //0x8c0
    volatile uint32_t PCIE0_REG135; //0x8c4
    volatile uint32_t PCIE0_REG136; //0x8c8
    volatile uint32_t PCIE0_REG137; //0x8cc
    volatile uint32_t PCIE0_REG138; //0x8d0
    volatile uint32_t PCIE0_REG139; //0x8d4
    volatile uint32_t PCIE0_REG140; //0x8d8
    volatile uint32_t PCIE0_REG141; //0x8dc
    volatile uint32_t PCIE0_REG142; //0x8e0
    volatile uint32_t PCIE0_REG143; //0x8e4
    volatile uint32_t PCIE0_REG144; //0x8e8
    volatile uint32_t PCIE0_REG145; //0x8ec
    volatile uint32_t PCIE0_REG146; //0x8f0
    volatile uint32_t PCIE0_REG147; //0x8f4
    volatile uint32_t PCIE0_REG148; //0x8f8
    volatile uint32_t PCIE0_REG149; //0x8fc
    volatile uint32_t PCIE0_REG150; //0x900
    volatile uint32_t PCIE0_REG151; //0x904
    volatile uint32_t PCIE0_REG152; //0x908
    volatile uint32_t PCIE0_REG153; //0x90c
    volatile uint32_t PCIE0_REG154; //0x910
    volatile uint32_t PCIE0_REG155; //0x914
    volatile uint32_t PCIE0_REG156; //0x918
    volatile uint32_t PCIE0_REG157; //0x91c
    volatile uint32_t PCIE0_REG158; //0x920
    volatile uint32_t PCIE0_REG159; //0x924
    volatile uint32_t PCIE0_REG160; //0x928
    volatile uint32_t PCIE0_REG161; //0x92c
    volatile uint32_t PCIE0_REG162; //0x930
    volatile uint32_t PCIE0_REG163; //0x934
    volatile uint32_t PCIE0_REG164; //0x938
    volatile uint32_t PCIE0_REG165; //0x93c
    volatile uint32_t PCIE0_REG166; //0x940
    volatile uint32_t PCIE0_REG167; //0x944
    volatile uint32_t PCIE0_REG168; //0x948
    volatile uint32_t PCIE0_REG169; //0x94c
    volatile uint32_t PCIE0_REG170; //0x950
    volatile uint32_t PCIE0_REG171; //0x954
    volatile uint32_t PCIE0_REG172; //0x958
    volatile uint32_t PCIE0_REG173; //0x95c
    volatile uint32_t PCIE0_REG174; //0x960
    volatile uint32_t PCIE0_REG175; //0x964
    volatile uint32_t PCIE0_REG176; //0x968
    volatile uint32_t PCIE0_REG177; //0x96c
    volatile uint32_t PCIE0_REG178; //0x970
    volatile uint32_t PCIE0_REG179; //0x974
    volatile uint32_t PCIE0_REG180; //0x978
    volatile uint32_t PCIE0_REG181; //0x97c
    volatile uint32_t PCIE0_REG182; //0x980
    volatile uint32_t PCIE0_REG183; //0x984
    volatile uint32_t PCIE0_REG184; //0x988
    volatile uint32_t PCIE0_REG185; //0x98c
    volatile uint32_t PCIE0_REG186; //0x990
    volatile uint32_t PCIE0_REG187; //0x994
    volatile uint32_t PCIE0_REG188; //0x998
    volatile uint32_t PCIE0_REG189; //0x99c
    volatile uint32_t PCIE0_REG190; //0x9a0
    volatile uint32_t PCIE0_REG191; //0x9a4
    volatile uint32_t PCIE0_REG192; //0x9a8
    volatile uint32_t PCIE0_REG193; //0x9ac
    volatile uint32_t PCIE0_REG194; //0x9b0
    volatile uint32_t PCIE0_REG195; //0x9b4
    volatile uint32_t PCIE0_REG196; //0x9b8
    volatile uint32_t PCIE0_REG197; //0x9bc
    volatile uint32_t PCIE0_REG198; //0x9c0
    volatile uint32_t PCIE0_REG199; //0x9c4
    volatile uint32_t PCIE0_REG200; //0x9c8
    volatile uint32_t PCIE0_REG201; //0x9cc
    volatile uint32_t PCIE0_REG202; //0x9d0
    volatile uint32_t PCIE0_REG203; //0x9d4
    volatile uint32_t PCIE0_REG204; //0x9d8
    volatile uint32_t PCIE0_REG205; //0x9dc
    volatile uint32_t PCIE0_REG206; //0x9e0
    volatile uint32_t PCIE0_REG207; //0x9e4
    volatile uint32_t PCIE0_REG208; //0x9e8
    volatile uint32_t PCIE0_REG209; //0x9ec
    volatile uint32_t PCIE0_REG210; //0x9f0
    volatile uint32_t PCIE0_REG211; //0x9f4
    volatile uint32_t PCIE0_REG212; //0x9f8
    volatile uint32_t PCIE0_REG213; //0x9fc
    volatile uint32_t PCIE0_REG214; //0xa00
    volatile uint32_t PCIE0_REG215; //0xa04
    volatile uint32_t PCIE0_REG216; //0xa08
    volatile uint32_t PCIE0_REG217; //0xa0c
    volatile uint32_t PCIE0_REG218; //0xa10
    volatile uint32_t PCIE0_REG219; //0xa14
    volatile uint32_t PCIE0_REG220; //0xa18
    volatile uint32_t PCIE0_REG221; //0xa1c
    volatile uint32_t PCIE0_REG222; //0xa20
    volatile uint32_t PCIE0_REG223; //0xa24
    volatile uint32_t PCIE0_REG224; //0xa28
    volatile uint32_t PCIE0_REG225; //0xa2c
    volatile uint32_t PCIE0_REG226; //0xa30
    volatile uint32_t PCIE0_REG227; //0xa34
    volatile uint32_t PCIE0_REG228; //0xa38
    volatile uint32_t PCIE0_REG229; //0xa3c
    volatile uint32_t PCIE0_REG230; //0xa40
    volatile uint32_t PCIE0_REG231; //0xa44
    volatile uint32_t PCIE0_REG232; //0xa48
    volatile uint32_t PCIE0_REG233; //0xa4c
    volatile uint32_t PCIE0_REG234; //0xa50
    volatile uint32_t PCIE0_REG235; //0xa54
    volatile uint32_t PCIE0_REG236; //0xa58
    volatile uint32_t PCIE0_REG237; //0xa5c
    volatile uint32_t PCIE0_REG238; //0xa60
    volatile uint32_t PCIE0_REG239; //0xa64
    volatile uint32_t PCIE0_REG240; //0xa68
    volatile uint32_t PCIE0_REG241; //0xa6c
    volatile uint32_t PCIE0_REG242; //0xa70
    volatile uint32_t PCIE0_REG243; //0xa74
    volatile uint32_t PCIE0_REG244; //0xa78
    volatile uint32_t PCIE0_REG245; //0xa7c
    volatile uint32_t PCIE0_REG246; //0xa80
    volatile uint32_t PCIE0_REG247; //0xa84
    volatile uint32_t PCIE0_REG248; //0xa88
    volatile uint32_t PCIE0_REG249; //0xa8c
    volatile uint32_t PCIE0_REG250; //0xa90
    volatile uint32_t PCIE0_REG251; //0xa94
    volatile uint32_t PCIE0_REG252; //0xa98
    volatile uint32_t PCIE0_REG253; //0xa9c
    volatile uint32_t PCIE0_REG254; //0xaa0
    volatile uint32_t PCIE0_REG255; //0xaa4
    volatile uint32_t PCIE0_REG256; //0xaa8
    volatile uint32_t PCIE0_REG257; //0xaac
    volatile uint32_t PCIE0_REG258; //0xab0
    volatile uint32_t PCIE0_REG259; //0xab4
    volatile uint32_t PCIE0_REG260; //0xab8
    volatile uint32_t PCIE0_REG261; //0xabc
    volatile uint32_t PCIE0_REG262; //0xac0
    volatile uint32_t PCIE0_REG263; //0xac4
    volatile uint32_t PCIE0_REG264; //0xac8
    volatile uint32_t PCIE0_REG265; //0xacc
    volatile uint32_t PCIE0_REG266; //0xad0
    volatile uint32_t PCIE0_REG267; //0xad4
    volatile uint32_t PCIE0_REG268; //0xad8
    volatile uint32_t PCIE0_REG269; //0xadc
    volatile uint32_t PCIE0_REG270; //0xae0
    volatile uint32_t PCIE0_REG271; //0xae4
    volatile uint32_t PCIE0_REG272; //0xae8
    volatile uint32_t PCIE0_REG273; //0xaec
    volatile uint32_t PCIE0_REG274; //0xaf0
    volatile uint32_t PCIE0_REG275; //0xaf4
    volatile uint32_t PCIE0_REG276; //0xaf8
    volatile uint32_t PCIE0_REG277; //0xafc
    volatile uint32_t PCIE0_REG278; //0xb00
    volatile uint32_t PCIE0_REG279; //0xb04
    volatile uint32_t PCIE0_REG280; //0xb08
    volatile uint32_t PCIE0_REG281; //0xb0c
    volatile uint32_t PCIE0_REG282; //0xb10
    volatile uint32_t PCIE0_REG283; //0xb14
    volatile uint32_t PCIE0_REG284; //0xb18
    volatile uint32_t PCIE0_REG285; //0xb1c
    volatile uint32_t PCIE0_REG286; //0xb20
    volatile uint32_t PCIE0_REG287; //0xb24
    volatile uint32_t PCIE0_REG288; //0xb28
    volatile uint32_t PCIE0_RAM_REG_0; //0xb2c
    volatile uint32_t PCIE0_RAM_REG_1; //0xb30
    volatile uint32_t PCIE0_RAM_REG_2; //0xb34
    volatile uint32_t PCIE0_RAM_REG_3; //0xb38
    volatile uint32_t PCIE0_RAM_REG_4; //0xb3c
    volatile uint32_t PCIE0_RAM_REG_5; //0xb40
    volatile uint32_t PCIE0_AXI_SLV_REG0; //0xb44
    volatile uint32_t PCIE0_AXI_SLV_REG1; //0xb48
    volatile uint32_t PCIE0_AXI_SLV_REG2; //0xb4c
    volatile uint32_t PCIE0_AXI_SLV_REG3; //0xb50
    volatile uint32_t PCIE0_AXI_SLV_REG4; //0xb54
    volatile uint32_t PCIE0_AXI_SLV_REG5; //0xb58
    volatile uint32_t PCIE0_AXI_MST_REG0; //0xb5c
    volatile uint32_t PCIE0_AXI_MST_REG1; //0xb60
    volatile uint32_t PCIE0_AXI_MST_REG2; //0xb64
    volatile uint32_t PCIE0_AXI_MST_REG3; //0xb68
    volatile uint32_t PCIE0_AXI_MST_REG4; //0xb6c
    volatile uint32_t PCIE0_AXI_MST_REG5; //0xb70
    volatile uint32_t PCIE0_AXI_MST_REG6; //0xb74
    volatile uint32_t PCIE0_AXI_MST_REG7; //0xb78
    volatile uint32_t PCIE0_DBI_SLV_REG0; //0xb7c
    volatile uint32_t PCIE0_VEN_MSG_START_T; //0xb80
    volatile uint32_t PCIE0_VEN_MSI_START_T; //0xb84
    volatile uint32_t PCIE0_APP_LTR_MSG_START_T; //0xb88
    volatile uint32_t PCIE0_APP_OBFF_IDLE_MSG_START_T; //0xb8c
    volatile uint32_t PCIE0_APP_OBFF_OBFF_MSG_START_T; //0xb90
    volatile uint32_t PCIE0_APP_OBFF_CPU_ACTIVE_MSG_START_T; //0xb94
    volatile uint32_t PCIE0_VEN_MSG_REQ_TIMEOUT_CNT; //0xb98
    volatile uint32_t PIPE_ADJUST_ADB400_MST_AXI_EN; //0xb9c
    volatile uint32_t PCIE0_REG300; //0xba0
    volatile uint32_t PCIE0_REG301; //0xba4
    volatile uint32_t PCIE0_REG302; //0xba8
    volatile uint32_t PCIE0_REG303; //0xbac
    volatile uint32_t PCIE0_REG304; //0xbb0
    volatile uint32_t PCIE0_REG305; //0xbb4
    volatile uint32_t PCIE0_REG306; //0xbb8
    volatile uint32_t PCIE0_REG307; //0xbbc
    volatile uint32_t PCIE0_REG308; //0xbc0
    volatile uint32_t PCIE0_REG309; //0xbc4
    volatile uint32_t PCIE0_REG310; //0xbc8
    volatile uint32_t PCIE0_REG311; //0xbcc
    volatile uint32_t PCIE0_REG312; //0xbd0
    volatile uint32_t PCIE0_REG313; //0xbd4
    volatile uint32_t PCIE0_REG314; //0xbd8
    volatile uint32_t PCIE0_REG315; //0xbdc
    volatile uint32_t PCIE0_REG316; //0xbe0
    volatile uint32_t PCIE0_REG317; //0xbe4
    volatile uint32_t PCIE0_REG318; //0xbe8
    volatile uint32_t PCIE0_REG319; //0xbec
    volatile uint32_t PCIE0_REG320; //0xbf0
    volatile uint32_t PCIE0_REG321; //0xbf4
    volatile uint32_t PCIE0_REG322; //0xbf8
    volatile uint32_t PCIE0_CFG_PBUS_NUM_0; //0xbfc
    volatile uint32_t PCIE0_CFG_PBUS_NUM_1; //0xc00
    volatile uint32_t PCIE0_CFG_PBUS_DEV_NUM_0; //0xc04
    volatile uint32_t PCIE0_CFG_PBUS_DEV_NUM_1; //0xc08
    volatile uint32_t PCIE0_REG323; //0xc0c
    volatile uint32_t PCIE0_REG324; //0xc10
    volatile uint32_t PCIE0_REG325; //0xc14
    volatile uint32_t PCIE1_REG300; //0xc18
    volatile uint32_t PCIE1_REG301; //0xc1c
    volatile uint32_t PCIE1_REG302; //0xc20
    volatile uint32_t PCIE1_REG303; //0xc24
    volatile uint32_t PCIE1_REG304; //0xc28
    volatile uint32_t PCIE1_REG305; //0xc2c
    volatile uint32_t PCIE1_REG306; //0xc30
    volatile uint32_t PCIE1_REG307; //0xc34
    volatile uint32_t PCIE1_REG308; //0xc38
    volatile uint32_t PCIE1_REG309; //0xc3c
    volatile uint32_t PCIE1_REG310; //0xc40
    volatile uint32_t PCIE1_REG311; //0xc44
    volatile uint32_t PCIE1_REG312; //0xc48
    volatile uint32_t PCIE1_REG313; //0xc4c
    volatile uint32_t PCIE1_REG314; //0xc50
    volatile uint32_t PCIE1_REG315; //0xc54
    volatile uint32_t PCIE1_REG316; //0xc58
    volatile uint32_t PCIE1_REG317; //0xc5c
    volatile uint32_t PCIE1_REG318; //0xc60
    volatile uint32_t PCIE1_REG319; //0xc64
    volatile uint32_t PCIE1_REG320; //0xc68
    volatile uint32_t PCIE1_REG321; //0xc6c
    volatile uint32_t PCIE1_REG322; //0xc70
    volatile uint32_t PCIE1_CFG_PBUS_NUM_0; //0xc74
    volatile uint32_t PCIE1_CFG_PBUS_NUM_1; //0xc78
    volatile uint32_t PCIE1_CFG_PBUS_DEV_NUM_0; //0xc7c
    volatile uint32_t PCIE1_CFG_PBUS_DEV_NUM_1; //0xc80
    volatile uint32_t PCIE1_REG323; //0xc84
    volatile uint32_t PCIE1_REG324; //0xc88
    volatile uint32_t PCIE1_REG325; //0xc8c
} reg_pipe_sys_t;

enum PIPE_SYS_REG_PCIE0_PCLK_CLK_DEGLITCH_SW2_REG_FIELD
{
    PIPE_SYS_PCIE0_PCLK_CLK_DEGLITCH_SW2_REG_MASK = (int)0x1f,
    PIPE_SYS_PCIE0_PCLK_CLK_DEGLITCH_SW2_REG_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_PCLK_CLK_CG0_REG_FIELD
{
    PIPE_SYS_PCIE0_PCLK_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_PCIE0_PCLK_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_AUXCLK_CLK_DEGLITCH_SW4_REG_FIELD
{
    PIPE_SYS_PCIE0_AUXCLK_CLK_DEGLITCH_SW4_REG_MASK = (int)0x1ff,
    PIPE_SYS_PCIE0_AUXCLK_CLK_DEGLITCH_SW4_REG_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_AUXCLK_CLK_DIV0_DIV4_REG_FIELD
{
    PIPE_SYS_PCIE0_AUXCLK_CLK_DIV0_DIV4_REG_MASK = (int)0xf,
    PIPE_SYS_PCIE0_AUXCLK_CLK_DIV0_DIV4_REG_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_AUXCLK_CLK_CG0_REG_FIELD
{
    PIPE_SYS_PCIE0_AUXCLK_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_PCIE0_AUXCLK_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_PCLK_CLK_DEGLITCH_SW2_REG_FIELD
{
    PIPE_SYS_PCIE1_PCLK_CLK_DEGLITCH_SW2_REG_MASK = (int)0x1f,
    PIPE_SYS_PCIE1_PCLK_CLK_DEGLITCH_SW2_REG_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_PCLK_CLK_CG0_REG_FIELD
{
    PIPE_SYS_PCIE1_PCLK_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_PCIE1_PCLK_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_AUXCLK_CLK_DEGLITCH_SW4_REG_FIELD
{
    PIPE_SYS_PCIE1_AUXCLK_CLK_DEGLITCH_SW4_REG_MASK = (int)0x1ff,
    PIPE_SYS_PCIE1_AUXCLK_CLK_DEGLITCH_SW4_REG_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_AUXCLK_CLK_DIV0_DIV4_REG_FIELD
{
    PIPE_SYS_PCIE1_AUXCLK_CLK_DIV0_DIV4_REG_MASK = (int)0xf,
    PIPE_SYS_PCIE1_AUXCLK_CLK_DIV0_DIV4_REG_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_AUXCLK_CLK_CG0_REG_FIELD
{
    PIPE_SYS_PCIE1_AUXCLK_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_PCIE1_AUXCLK_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_VP0_INT_CLK_CLK_DEGLITCH_SW2_REG_FIELD
{
    PIPE_SYS_VP0_INT_CLK_CLK_DEGLITCH_SW2_REG_MASK = (int)0x1f,
    PIPE_SYS_VP0_INT_CLK_CLK_DEGLITCH_SW2_REG_POS = 0,
};

enum PIPE_SYS_REG_VP0_INT_CLK_CLK_DIV0_DIV2_REG_FIELD
{
    PIPE_SYS_VP0_INT_CLK_CLK_DIV0_DIV2_REG_MASK = (int)0x3,
    PIPE_SYS_VP0_INT_CLK_CLK_DIV0_DIV2_REG_POS = 0,
};

enum PIPE_SYS_REG_VP0_INT_CLK_CLK_CG0_REG_FIELD
{
    PIPE_SYS_VP0_INT_CLK_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_VP0_INT_CLK_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_VP0_VDAC_CLK_CLK_DEGLITCH_SW2_REG_FIELD
{
    PIPE_SYS_VP0_VDAC_CLK_CLK_DEGLITCH_SW2_REG_MASK = (int)0x1f,
    PIPE_SYS_VP0_VDAC_CLK_CLK_DEGLITCH_SW2_REG_POS = 0,
};

enum PIPE_SYS_REG_VP0_VDAC_CLK_CLK_DIV0_DIV4_2_REG_FIELD
{
    PIPE_SYS_VP0_VDAC_CLK_CLK_DIV0_DIV4_2_REG_MASK = (int)0xf,
    PIPE_SYS_VP0_VDAC_CLK_CLK_DIV0_DIV4_2_REG_POS = 0,
};

enum PIPE_SYS_REG_VP0_VDAC_CLK_CLK_CG0_REG_FIELD
{
    PIPE_SYS_VP0_VDAC_CLK_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_VP0_VDAC_CLK_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_VP0_OUT_CLK_CLK_DEGLITCH_SW2_REG_FIELD
{
    PIPE_SYS_VP0_OUT_CLK_CLK_DEGLITCH_SW2_REG_MASK = (int)0x1f,
    PIPE_SYS_VP0_OUT_CLK_CLK_DEGLITCH_SW2_REG_POS = 0,
};

enum PIPE_SYS_REG_VP0_OUT_CLK_CLK_DIV0_DIV4_6_REG_FIELD
{
    PIPE_SYS_VP0_OUT_CLK_CLK_DIV0_DIV4_6_REG_MASK = (int)0xf,
    PIPE_SYS_VP0_OUT_CLK_CLK_DIV0_DIV4_6_REG_POS = 0,
};

enum PIPE_SYS_REG_VP0_OUT_CLK_CLK_CG0_REG_FIELD
{
    PIPE_SYS_VP0_OUT_CLK_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_VP0_OUT_CLK_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_VP1_INT_CLK_CLK_DEGLITCH_SW2_REG_FIELD
{
    PIPE_SYS_VP1_INT_CLK_CLK_DEGLITCH_SW2_REG_MASK = (int)0x1f,
    PIPE_SYS_VP1_INT_CLK_CLK_DEGLITCH_SW2_REG_POS = 0,
};

enum PIPE_SYS_REG_VP1_INT_CLK_CLK_DIV0_DIV2_REG_FIELD
{
    PIPE_SYS_VP1_INT_CLK_CLK_DIV0_DIV2_REG_MASK = (int)0x3,
    PIPE_SYS_VP1_INT_CLK_CLK_DIV0_DIV2_REG_POS = 0,
};

enum PIPE_SYS_REG_VP1_INT_CLK_CLK_CG0_REG_FIELD
{
    PIPE_SYS_VP1_INT_CLK_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_VP1_INT_CLK_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_VP1_VDAC_CLK_CLK_DEGLITCH_SW2_REG_FIELD
{
    PIPE_SYS_VP1_VDAC_CLK_CLK_DEGLITCH_SW2_REG_MASK = (int)0x1f,
    PIPE_SYS_VP1_VDAC_CLK_CLK_DEGLITCH_SW2_REG_POS = 0,
};

enum PIPE_SYS_REG_VP1_VDAC_CLK_CLK_DIV0_DIV4_2_REG_FIELD
{
    PIPE_SYS_VP1_VDAC_CLK_CLK_DIV0_DIV4_2_REG_MASK = (int)0xf,
    PIPE_SYS_VP1_VDAC_CLK_CLK_DIV0_DIV4_2_REG_POS = 0,
};

enum PIPE_SYS_REG_VP1_VDAC_CLK_CLK_CG0_REG_FIELD
{
    PIPE_SYS_VP1_VDAC_CLK_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_VP1_VDAC_CLK_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_VP1_OUT_CLK_CLK_DEGLITCH_SW2_REG_FIELD
{
    PIPE_SYS_VP1_OUT_CLK_CLK_DEGLITCH_SW2_REG_MASK = (int)0x1f,
    PIPE_SYS_VP1_OUT_CLK_CLK_DEGLITCH_SW2_REG_POS = 0,
};

enum PIPE_SYS_REG_VP1_OUT_CLK_CLK_DIV0_DIV4_6_REG_FIELD
{
    PIPE_SYS_VP1_OUT_CLK_CLK_DIV0_DIV4_6_REG_MASK = (int)0xf,
    PIPE_SYS_VP1_OUT_CLK_CLK_DIV0_DIV4_6_REG_POS = 0,
};

enum PIPE_SYS_REG_VP1_OUT_CLK_CLK_CG0_REG_FIELD
{
    PIPE_SYS_VP1_OUT_CLK_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_VP1_OUT_CLK_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_EMMC_CORE_CLK_CLK_DEGLITCH_SW3_REG_FIELD
{
    PIPE_SYS_EMMC_CORE_CLK_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    PIPE_SYS_EMMC_CORE_CLK_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum PIPE_SYS_REG_EMMC_CORE_CLK_CLK_DIV0_DIV2_REG_FIELD
{
    PIPE_SYS_EMMC_CORE_CLK_CLK_DIV0_DIV2_REG_MASK = (int)0x3,
    PIPE_SYS_EMMC_CORE_CLK_CLK_DIV0_DIV2_REG_POS = 0,
};

enum PIPE_SYS_REG_EMMC_CORE_CLK_CLK_CG0_REG_FIELD
{
    PIPE_SYS_EMMC_CORE_CLK_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_EMMC_CORE_CLK_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_EMMC_CCLK_TX_CLK_CLK_DEGLITCH_SW2_REG_FIELD
{
    PIPE_SYS_EMMC_CCLK_TX_CLK_CLK_DEGLITCH_SW2_REG_MASK = (int)0x1f,
    PIPE_SYS_EMMC_CCLK_TX_CLK_CLK_DEGLITCH_SW2_REG_POS = 0,
};

enum PIPE_SYS_REG_EMMC_CCLK_TX_CLK_CLK_DIV0_DIV10_REG_FIELD
{
    PIPE_SYS_EMMC_CCLK_TX_CLK_CLK_DIV0_DIV10_REG_MASK = (int)0x3ff,
    PIPE_SYS_EMMC_CCLK_TX_CLK_CLK_DIV0_DIV10_REG_POS = 0,
};

enum PIPE_SYS_REG_EMMC_CCLK_TX_CLK_CLK_CG0_REG_FIELD
{
    PIPE_SYS_EMMC_CCLK_TX_CLK_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_EMMC_CCLK_TX_CLK_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_EMMC_TM_CLK_CLK_DEGLITCH_SW3_REG_FIELD
{
    PIPE_SYS_EMMC_TM_CLK_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    PIPE_SYS_EMMC_TM_CLK_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum PIPE_SYS_REG_EMMC_TM_CLK_CLK_DIV0_DIV8_REG_FIELD
{
    PIPE_SYS_EMMC_TM_CLK_CLK_DIV0_DIV8_REG_MASK = (int)0xff,
    PIPE_SYS_EMMC_TM_CLK_CLK_DIV0_DIV8_REG_POS = 0,
};

enum PIPE_SYS_REG_EMMC_TM_CLK_CLK_CG0_REG_FIELD
{
    PIPE_SYS_EMMC_TM_CLK_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_EMMC_TM_CLK_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_EMMC_CCLK_RX_CLK_CLK_DEGLITCH_SW3_REG_FIELD
{
    PIPE_SYS_EMMC_CCLK_RX_CLK_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    PIPE_SYS_EMMC_CCLK_RX_CLK_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum PIPE_SYS_REG_EMMC_CCLK_RX_CLK_CLK_DIV0_DIV10_REG_FIELD
{
    PIPE_SYS_EMMC_CCLK_RX_CLK_CLK_DIV0_DIV10_REG_MASK = (int)0x3ff,
    PIPE_SYS_EMMC_CCLK_RX_CLK_CLK_DIV0_DIV10_REG_POS = 0,
};

enum PIPE_SYS_REG_EMMC_CCLK_RX_CLK_CLK_CG0_REG_FIELD
{
    PIPE_SYS_EMMC_CCLK_RX_CLK_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_EMMC_CCLK_RX_CLK_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_WDT3_LRC_CLK_CLK_DEGLITCH_SW2_REG_FIELD
{
    PIPE_SYS_WDT3_LRC_CLK_CLK_DEGLITCH_SW2_REG_MASK = (int)0x1f,
    PIPE_SYS_WDT3_LRC_CLK_CLK_DEGLITCH_SW2_REG_POS = 0,
};

enum PIPE_SYS_REG_WDT3_LRC_CLK_CLK_CG0_REG_FIELD
{
    PIPE_SYS_WDT3_LRC_CLK_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_WDT3_LRC_CLK_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH1_TX_CLK_DEGLITCH_SW3_REG_FIELD
{
    PIPE_SYS_CLK_SGETH1_TX_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    PIPE_SYS_CLK_SGETH1_TX_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH1_TX_CLK_DIV0_DIV6_REG_FIELD
{
    PIPE_SYS_CLK_SGETH1_TX_CLK_DIV0_DIV6_REG_MASK = (int)0x3f,
    PIPE_SYS_CLK_SGETH1_TX_CLK_DIV0_DIV6_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH1_TX_CLK_CG0_REG_FIELD
{
    PIPE_SYS_CLK_SGETH1_TX_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_CLK_SGETH1_TX_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH1_RX_CLK_DEGLITCH_SW3_REG_FIELD
{
    PIPE_SYS_CLK_SGETH1_RX_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    PIPE_SYS_CLK_SGETH1_RX_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH1_RX_CLK_DIV0_DIV6_REG_FIELD
{
    PIPE_SYS_CLK_SGETH1_RX_CLK_DIV0_DIV6_REG_MASK = (int)0x3f,
    PIPE_SYS_CLK_SGETH1_RX_CLK_DIV0_DIV6_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH1_RX_CLK_CG0_REG_FIELD
{
    PIPE_SYS_CLK_SGETH1_RX_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_CLK_SGETH1_RX_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH1_125_TX_CLK_DEGLITCH_SW3_REG_FIELD
{
    PIPE_SYS_CLK_SGETH1_125_TX_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    PIPE_SYS_CLK_SGETH1_125_TX_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH1_125_TX_CLK_DIV0_DIV6_REG_FIELD
{
    PIPE_SYS_CLK_SGETH1_125_TX_CLK_DIV0_DIV6_REG_MASK = (int)0x3f,
    PIPE_SYS_CLK_SGETH1_125_TX_CLK_DIV0_DIV6_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH1_125_TX_CLK_CG0_REG_FIELD
{
    PIPE_SYS_CLK_SGETH1_125_TX_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_CLK_SGETH1_125_TX_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH1_125_RX_CLK_DEGLITCH_SW3_REG_FIELD
{
    PIPE_SYS_CLK_SGETH1_125_RX_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    PIPE_SYS_CLK_SGETH1_125_RX_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH1_125_RX_CLK_DIV0_DIV6_REG_FIELD
{
    PIPE_SYS_CLK_SGETH1_125_RX_CLK_DIV0_DIV6_REG_MASK = (int)0x3f,
    PIPE_SYS_CLK_SGETH1_125_RX_CLK_DIV0_DIV6_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH1_125_RX_CLK_CG0_REG_FIELD
{
    PIPE_SYS_CLK_SGETH1_125_RX_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_CLK_SGETH1_125_RX_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH2_TX_CLK_DEGLITCH_SW3_REG_FIELD
{
    PIPE_SYS_CLK_SGETH2_TX_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    PIPE_SYS_CLK_SGETH2_TX_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH2_TX_CLK_DIV0_DIV6_REG_FIELD
{
    PIPE_SYS_CLK_SGETH2_TX_CLK_DIV0_DIV6_REG_MASK = (int)0x3f,
    PIPE_SYS_CLK_SGETH2_TX_CLK_DIV0_DIV6_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH2_TX_CLK_CG0_REG_FIELD
{
    PIPE_SYS_CLK_SGETH2_TX_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_CLK_SGETH2_TX_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH2_RX_CLK_DEGLITCH_SW3_REG_FIELD
{
    PIPE_SYS_CLK_SGETH2_RX_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    PIPE_SYS_CLK_SGETH2_RX_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH2_RX_CLK_DIV0_DIV6_REG_FIELD
{
    PIPE_SYS_CLK_SGETH2_RX_CLK_DIV0_DIV6_REG_MASK = (int)0x3f,
    PIPE_SYS_CLK_SGETH2_RX_CLK_DIV0_DIV6_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH2_RX_CLK_CG0_REG_FIELD
{
    PIPE_SYS_CLK_SGETH2_RX_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_CLK_SGETH2_RX_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH2_125_TX_CLK_DEGLITCH_SW3_REG_FIELD
{
    PIPE_SYS_CLK_SGETH2_125_TX_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    PIPE_SYS_CLK_SGETH2_125_TX_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH2_125_TX_CLK_DIV0_DIV6_REG_FIELD
{
    PIPE_SYS_CLK_SGETH2_125_TX_CLK_DIV0_DIV6_REG_MASK = (int)0x3f,
    PIPE_SYS_CLK_SGETH2_125_TX_CLK_DIV0_DIV6_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH2_125_TX_CLK_CG0_REG_FIELD
{
    PIPE_SYS_CLK_SGETH2_125_TX_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_CLK_SGETH2_125_TX_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH2_125_RX_CLK_DEGLITCH_SW3_REG_FIELD
{
    PIPE_SYS_CLK_SGETH2_125_RX_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    PIPE_SYS_CLK_SGETH2_125_RX_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH2_125_RX_CLK_DIV0_DIV6_REG_FIELD
{
    PIPE_SYS_CLK_SGETH2_125_RX_CLK_DIV0_DIV6_REG_MASK = (int)0x3f,
    PIPE_SYS_CLK_SGETH2_125_RX_CLK_DIV0_DIV6_REG_POS = 0,
};

enum PIPE_SYS_REG_CLK_SGETH2_125_RX_CLK_CG0_REG_FIELD
{
    PIPE_SYS_CLK_SGETH2_125_RX_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_CLK_SGETH2_125_RX_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_PHY_LNK_CLK_TX_CLK_DEGLITCH_SW3_REG_FIELD
{
    PIPE_SYS_PHY_LNK_CLK_TX_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    PIPE_SYS_PHY_LNK_CLK_TX_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum PIPE_SYS_REG_PHY_LNK_CLK_TX_CLK_CG0_REG_FIELD
{
    PIPE_SYS_PHY_LNK_CLK_TX_CLK_CG0_REG_MASK = (int)0x1,
    PIPE_SYS_PHY_LNK_CLK_TX_CLK_CG0_REG_POS = 0,
};

enum PIPE_SYS_REG_SOFT_RST_N_REG0_FIELD
{
    PIPE_SYS_PCIE0_PCLK_SOFT_RST_N_REG0_MASK = (int)0x1,
    PIPE_SYS_PCIE0_PCLK_SOFT_RST_N_REG0_POS = 0,
    PIPE_SYS_PCIE0_AUXCLK_SOFT_RST_N_REG0_MASK = (int)0x2,
    PIPE_SYS_PCIE0_AUXCLK_SOFT_RST_N_REG0_POS = 1,
    PIPE_SYS_PCIE1_PCLK_SOFT_RST_N_REG0_MASK = (int)0x4,
    PIPE_SYS_PCIE1_PCLK_SOFT_RST_N_REG0_POS = 2,
    PIPE_SYS_PCIE1_AUXCLK_SOFT_RST_N_REG0_MASK = (int)0x8,
    PIPE_SYS_PCIE1_AUXCLK_SOFT_RST_N_REG0_POS = 3,
    PIPE_SYS_VP0_INT_CLK_SOFT_RST_N_REG0_MASK = (int)0x10,
    PIPE_SYS_VP0_INT_CLK_SOFT_RST_N_REG0_POS = 4,
    PIPE_SYS_VP0_VDAC_CLK_SOFT_RST_N_REG0_MASK = (int)0x20,
    PIPE_SYS_VP0_VDAC_CLK_SOFT_RST_N_REG0_POS = 5,
    PIPE_SYS_VP0_OUT_CLK_SOFT_RST_N_REG0_MASK = (int)0x40,
    PIPE_SYS_VP0_OUT_CLK_SOFT_RST_N_REG0_POS = 6,
    PIPE_SYS_VP1_INT_CLK_SOFT_RST_N_REG0_MASK = (int)0x80,
    PIPE_SYS_VP1_INT_CLK_SOFT_RST_N_REG0_POS = 7,
    PIPE_SYS_VP1_VDAC_CLK_SOFT_RST_N_REG0_MASK = (int)0x100,
    PIPE_SYS_VP1_VDAC_CLK_SOFT_RST_N_REG0_POS = 8,
    PIPE_SYS_VP1_OUT_CLK_SOFT_RST_N_REG0_MASK = (int)0x200,
    PIPE_SYS_VP1_OUT_CLK_SOFT_RST_N_REG0_POS = 9,
    PIPE_SYS_EMMC_CORE_CLK_SOFT_RST_N_REG0_MASK = (int)0x400,
    PIPE_SYS_EMMC_CORE_CLK_SOFT_RST_N_REG0_POS = 10,
    PIPE_SYS_EMMC_CCLK_TX_CLK_SOFT_RST_N_REG0_MASK = (int)0x800,
    PIPE_SYS_EMMC_CCLK_TX_CLK_SOFT_RST_N_REG0_POS = 11,
    PIPE_SYS_EMMC_TM_CLK_SOFT_RST_N_REG0_MASK = (int)0x1000,
    PIPE_SYS_EMMC_TM_CLK_SOFT_RST_N_REG0_POS = 12,
    PIPE_SYS_EMMC_CCLK_RX_CLK_SOFT_RST_N_REG0_MASK = (int)0x2000,
    PIPE_SYS_EMMC_CCLK_RX_CLK_SOFT_RST_N_REG0_POS = 13,
    PIPE_SYS_CLK_SGETH1_TX_SOFT_RST_N_REG0_MASK = (int)0x4000,
    PIPE_SYS_CLK_SGETH1_TX_SOFT_RST_N_REG0_POS = 14,
    PIPE_SYS_CLK_SGETH1_RX_SOFT_RST_N_REG0_MASK = (int)0x8000,
    PIPE_SYS_CLK_SGETH1_RX_SOFT_RST_N_REG0_POS = 15,
    PIPE_SYS_CLK_SGETH1_125_TX_SOFT_RST_N_REG0_MASK = (int)0x10000,
    PIPE_SYS_CLK_SGETH1_125_TX_SOFT_RST_N_REG0_POS = 16,
    PIPE_SYS_CLK_SGETH1_125_RX_SOFT_RST_N_REG0_MASK = (int)0x20000,
    PIPE_SYS_CLK_SGETH1_125_RX_SOFT_RST_N_REG0_POS = 17,
    PIPE_SYS_CLK_SGETH2_TX_SOFT_RST_N_REG0_MASK = (int)0x40000,
    PIPE_SYS_CLK_SGETH2_TX_SOFT_RST_N_REG0_POS = 18,
    PIPE_SYS_CLK_SGETH2_RX_SOFT_RST_N_REG0_MASK = (int)0x80000,
    PIPE_SYS_CLK_SGETH2_RX_SOFT_RST_N_REG0_POS = 19,
    PIPE_SYS_CLK_SGETH2_125_TX_SOFT_RST_N_REG0_MASK = (int)0x100000,
    PIPE_SYS_CLK_SGETH2_125_TX_SOFT_RST_N_REG0_POS = 20,
    PIPE_SYS_CLK_SGETH2_125_RX_SOFT_RST_N_REG0_MASK = (int)0x200000,
    PIPE_SYS_CLK_SGETH2_125_RX_SOFT_RST_N_REG0_POS = 21,
    PIPE_SYS_PHY_LNK_CLK_TX_SOFT_RST_N_REG0_MASK = (int)0x400000,
    PIPE_SYS_PHY_LNK_CLK_TX_SOFT_RST_N_REG0_POS = 22,
    PIPE_SYS_SOFT_RST_N_REG0_MASK = (int)0x7fffff,
    PIPE_SYS_SOFT_RST_N_REG0_POS = 0,
};

enum PIPE_SYS_REG_SOFT_RST_N_REG0_CLR_FIELD
{
    PIPE_SYS_PCIE0_PCLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x1,
    PIPE_SYS_PCIE0_PCLK_SOFT_RST_N_REG0_CLR_POS = 0,
    PIPE_SYS_PCIE0_AUXCLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x2,
    PIPE_SYS_PCIE0_AUXCLK_SOFT_RST_N_REG0_CLR_POS = 1,
    PIPE_SYS_PCIE1_PCLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x4,
    PIPE_SYS_PCIE1_PCLK_SOFT_RST_N_REG0_CLR_POS = 2,
    PIPE_SYS_PCIE1_AUXCLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x8,
    PIPE_SYS_PCIE1_AUXCLK_SOFT_RST_N_REG0_CLR_POS = 3,
    PIPE_SYS_VP0_INT_CLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x10,
    PIPE_SYS_VP0_INT_CLK_SOFT_RST_N_REG0_CLR_POS = 4,
    PIPE_SYS_VP0_VDAC_CLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x20,
    PIPE_SYS_VP0_VDAC_CLK_SOFT_RST_N_REG0_CLR_POS = 5,
    PIPE_SYS_VP0_OUT_CLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x40,
    PIPE_SYS_VP0_OUT_CLK_SOFT_RST_N_REG0_CLR_POS = 6,
    PIPE_SYS_VP1_INT_CLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x80,
    PIPE_SYS_VP1_INT_CLK_SOFT_RST_N_REG0_CLR_POS = 7,
    PIPE_SYS_VP1_VDAC_CLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x100,
    PIPE_SYS_VP1_VDAC_CLK_SOFT_RST_N_REG0_CLR_POS = 8,
    PIPE_SYS_VP1_OUT_CLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x200,
    PIPE_SYS_VP1_OUT_CLK_SOFT_RST_N_REG0_CLR_POS = 9,
    PIPE_SYS_EMMC_CORE_CLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x400,
    PIPE_SYS_EMMC_CORE_CLK_SOFT_RST_N_REG0_CLR_POS = 10,
    PIPE_SYS_EMMC_CCLK_TX_CLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x800,
    PIPE_SYS_EMMC_CCLK_TX_CLK_SOFT_RST_N_REG0_CLR_POS = 11,
    PIPE_SYS_EMMC_TM_CLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x1000,
    PIPE_SYS_EMMC_TM_CLK_SOFT_RST_N_REG0_CLR_POS = 12,
    PIPE_SYS_EMMC_CCLK_RX_CLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x2000,
    PIPE_SYS_EMMC_CCLK_RX_CLK_SOFT_RST_N_REG0_CLR_POS = 13,
    PIPE_SYS_CLK_SGETH1_TX_SOFT_RST_N_REG0_CLR_MASK = (int)0x4000,
    PIPE_SYS_CLK_SGETH1_TX_SOFT_RST_N_REG0_CLR_POS = 14,
    PIPE_SYS_CLK_SGETH1_RX_SOFT_RST_N_REG0_CLR_MASK = (int)0x8000,
    PIPE_SYS_CLK_SGETH1_RX_SOFT_RST_N_REG0_CLR_POS = 15,
    PIPE_SYS_CLK_SGETH1_125_TX_SOFT_RST_N_REG0_CLR_MASK = (int)0x10000,
    PIPE_SYS_CLK_SGETH1_125_TX_SOFT_RST_N_REG0_CLR_POS = 16,
    PIPE_SYS_CLK_SGETH1_125_RX_SOFT_RST_N_REG0_CLR_MASK = (int)0x20000,
    PIPE_SYS_CLK_SGETH1_125_RX_SOFT_RST_N_REG0_CLR_POS = 17,
    PIPE_SYS_CLK_SGETH2_TX_SOFT_RST_N_REG0_CLR_MASK = (int)0x40000,
    PIPE_SYS_CLK_SGETH2_TX_SOFT_RST_N_REG0_CLR_POS = 18,
    PIPE_SYS_CLK_SGETH2_RX_SOFT_RST_N_REG0_CLR_MASK = (int)0x80000,
    PIPE_SYS_CLK_SGETH2_RX_SOFT_RST_N_REG0_CLR_POS = 19,
    PIPE_SYS_CLK_SGETH2_125_TX_SOFT_RST_N_REG0_CLR_MASK = (int)0x100000,
    PIPE_SYS_CLK_SGETH2_125_TX_SOFT_RST_N_REG0_CLR_POS = 20,
    PIPE_SYS_CLK_SGETH2_125_RX_SOFT_RST_N_REG0_CLR_MASK = (int)0x200000,
    PIPE_SYS_CLK_SGETH2_125_RX_SOFT_RST_N_REG0_CLR_POS = 21,
    PIPE_SYS_PHY_LNK_CLK_TX_SOFT_RST_N_REG0_CLR_MASK = (int)0x400000,
    PIPE_SYS_PHY_LNK_CLK_TX_SOFT_RST_N_REG0_CLR_POS = 22,
    PIPE_SYS_SOFT_RST_N_REG0_CLR_MASK = (int)0x7fffff,
    PIPE_SYS_SOFT_RST_N_REG0_CLR_POS = 0,
};

enum PIPE_SYS_REG_PIPE_SYS_DUMMY0_FIELD
{
    PIPE_SYS_PIPE_SYS_DUMMY0_MASK = (int)0xffffffff,
    PIPE_SYS_PIPE_SYS_DUMMY0_POS = 0,
};

enum PIPE_SYS_REG_PIPE_SYS_DUMMY1_FIELD
{
    PIPE_SYS_PIPE_SYS_DUMMY1_MASK = (int)0xffffffff,
    PIPE_SYS_PIPE_SYS_DUMMY1_POS = 0,
};

enum PIPE_SYS_REG_PIPE_SYS_DUMMY2_FIELD
{
    PIPE_SYS_PIPE_SYS_DUMMY2_MASK = (int)0xffffffff,
    PIPE_SYS_PIPE_SYS_DUMMY2_POS = 0,
};

enum PIPE_SYS_REG_PIPE_SYS_DUMMY3_FIELD
{
    PIPE_SYS_PIPE_SYS_DUMMY3_MASK = (int)0xffffffff,
    PIPE_SYS_PIPE_SYS_DUMMY3_POS = 0,
};

enum PIPE_SYS_REG_PIPE_SYS_RD_DUMMY0_FIELD
{
    PIPE_SYS_PIPE_SYS_RD_DUMMY0_MASK = (int)0xffffffff,
    PIPE_SYS_PIPE_SYS_RD_DUMMY0_POS = 0,
};

enum PIPE_SYS_REG_PIPE_SYS_RD_DUMMY1_FIELD
{
    PIPE_SYS_PIPE_SYS_RD_DUMMY1_MASK = (int)0xffffffff,
    PIPE_SYS_PIPE_SYS_RD_DUMMY1_POS = 0,
};

enum PIPE_SYS_REG_PIPE_SYS_RD_DUMMY2_FIELD
{
    PIPE_SYS_PIPE_SYS_RD_DUMMY2_MASK = (int)0xffffffff,
    PIPE_SYS_PIPE_SYS_RD_DUMMY2_POS = 0,
};

enum PIPE_SYS_REG_PIPE_SYS_RD_DUMMY3_FIELD
{
    PIPE_SYS_PIPE_SYS_RD_DUMMY3_MASK = (int)0xffffffff,
    PIPE_SYS_PIPE_SYS_RD_DUMMY3_POS = 0,
};

enum PIPE_SYS_REG_EMMC_CTL0_FIELD
{
    PIPE_SYS_EMMC_EMA_MASK = (int)0x7,
    PIPE_SYS_EMMC_EMA_POS = 0,
    PIPE_SYS_EMMC_EMAW_MASK = (int)0x18,
    PIPE_SYS_EMMC_EMAW_POS = 3,
    PIPE_SYS_EMMC_EMAS_MASK = (int)0x20,
    PIPE_SYS_EMMC_EMAS_POS = 5,
    PIPE_SYS_EMMC_SOFT_CARD_CLK_STABLE_MASK = (int)0x200000,
    PIPE_SYS_EMMC_SOFT_CARD_CLK_STABLE_POS = 21,
    PIPE_SYS_EMMC_SOFT_INT_BCLK_STABLE_MASK = (int)0x400000,
    PIPE_SYS_EMMC_SOFT_INT_BCLK_STABLE_POS = 22,
    PIPE_SYS_EMMC_SOFT_INT_ACLK_STABLE_MASK = (int)0x800000,
    PIPE_SYS_EMMC_SOFT_INT_ACLK_STABLE_POS = 23,
    PIPE_SYS_EMMC_SOFT_INT_TMCLK_STABLE_MASK = (int)0x1000000,
    PIPE_SYS_EMMC_SOFT_INT_TMCLK_STABLE_POS = 24,
    PIPE_SYS_EMMC_SOFT_HOST_REG_VOL_STABLE_MASK = (int)0x2000000,
    PIPE_SYS_EMMC_SOFT_HOST_REG_VOL_STABLE_POS = 25,
    PIPE_SYS_EMMC_SOFT_CARD_DETECT_N_MASK = (int)0xc000000,
    PIPE_SYS_EMMC_SOFT_CARD_DETECT_N_POS = 26,
    PIPE_SYS_EMMC_SOFT_CARD_WRITE_PROT_MASK = (int)0x30000000,
    PIPE_SYS_EMMC_SOFT_CARD_WRITE_PROT_POS = 28,
};

enum PIPE_SYS_REG_EMMC_RD0_FIELD
{
    PIPE_SYS_EMMC_SOFT_RD_GP_OUT_MASK = (int)0xfff,
    PIPE_SYS_EMMC_SOFT_RD_GP_OUT_POS = 0,
    PIPE_SYS_EMMC_SOFT_RD_PDTST_Y_MASK = (int)0xfff000,
    PIPE_SYS_EMMC_SOFT_RD_PDTST_Y_POS = 12,
};

enum PIPE_SYS_REG_EMMC_RD1_FIELD
{
    PIPE_SYS_EMMC_SOFT_RD_CARD_CLK_FREQ_SEL_MASK = (int)0x3ff,
    PIPE_SYS_EMMC_SOFT_RD_CARD_CLK_FREQ_SEL_POS = 0,
    PIPE_SYS_EMMC_SOFT_RD_CARD_CLK_GEN_SEL_MASK = (int)0x400,
    PIPE_SYS_EMMC_SOFT_RD_CARD_CLK_GEN_SEL_POS = 10,
    PIPE_SYS_EMMC_SOFT_RD_CARD_CLK_EN_MASK = (int)0x800,
    PIPE_SYS_EMMC_SOFT_RD_CARD_CLK_EN_POS = 11,
    PIPE_SYS_EMMC_SOFT_RD_INTCLK_EN_MASK = (int)0x1000,
    PIPE_SYS_EMMC_SOFT_RD_INTCLK_EN_POS = 12,
    PIPE_SYS_EMMC_SOFT_RD_SD_VDD1_SEL_MASK = (int)0xe000,
    PIPE_SYS_EMMC_SOFT_RD_SD_VDD1_SEL_POS = 13,
    PIPE_SYS_EMMC_SOFT_RD_SD_VDD1_ON_MASK = (int)0x10000,
    PIPE_SYS_EMMC_SOFT_RD_SD_VDD1_ON_POS = 16,
    PIPE_SYS_EMMC_SOFT_RD_LED_CONTROL_MASK = (int)0x20000,
    PIPE_SYS_EMMC_SOFT_RD_LED_CONTROL_POS = 17,
};

enum PIPE_SYS_REG_EMMC_REG0_FIELD
{
    PIPE_SYS_EMMC_DLL_CTRL_MASK = (int)0xffffff,
    PIPE_SYS_EMMC_DLL_CTRL_POS = 0,
    PIPE_SYS_EMMC_TX_DLL_SEL_MASK = (int)0x1000000,
    PIPE_SYS_EMMC_TX_DLL_SEL_POS = 24,
    PIPE_SYS_EMMC_TX_CLK_INV_SEL_MASK = (int)0x2000000,
    PIPE_SYS_EMMC_TX_CLK_INV_SEL_POS = 25,
    PIPE_SYS_EMMC_TX_CLK_DLY_SEL_MASK = (int)0x4000000,
    PIPE_SYS_EMMC_TX_CLK_DLY_SEL_POS = 26,
};

enum PIPE_SYS_REG_EMMC_REG1_FIELD
{
    PIPE_SYS_EMMC_TX_CLK_DLY_CTL_MASK = (int)0x1ff,
    PIPE_SYS_EMMC_TX_CLK_DLY_CTL_POS = 0,
    PIPE_SYS_EMMC_RX_CLK_INV_SEL_MASK = (int)0x200,
    PIPE_SYS_EMMC_RX_CLK_INV_SEL_POS = 9,
    PIPE_SYS_EMMC_RX_CLK_DLY_SEL_MASK = (int)0x400,
    PIPE_SYS_EMMC_RX_CLK_DLY_SEL_POS = 10,
    PIPE_SYS_EMMC_RX_CLK_DLY_CTL_MASK = (int)0xff800,
    PIPE_SYS_EMMC_RX_CLK_DLY_CTL_POS = 11,
    PIPE_SYS_EMMC_DS_CLK_DLY_CTL_MASK = (int)0x1ff00000,
    PIPE_SYS_EMMC_DS_CLK_DLY_CTL_POS = 20,
    PIPE_SYS_EMMC_DS_CLK_DLY_SEL_MASK = (int)0x20000000,
    PIPE_SYS_EMMC_DS_CLK_DLY_SEL_POS = 29,
};

enum PIPE_SYS_REG_EMMC_REG2_FIELD
{
    PIPE_SYS_EMMC_DLL_CTRL_RD_MASK = (int)0xff,
    PIPE_SYS_EMMC_DLL_CTRL_RD_POS = 0,
    PIPE_SYS_EMMC_AUTO_TUNING_MASK = (int)0x100,
    PIPE_SYS_EMMC_AUTO_TUNING_POS = 8,
    PIPE_SYS_EMMC_AUTO_TUNING_UPDATE_MASK = (int)0x200,
    PIPE_SYS_EMMC_AUTO_TUNING_UPDATE_POS = 9,
};

enum PIPE_SYS_REG_ADDR_HIGH2BIT_XOR_PCIE0_FIELD
{
    PIPE_SYS_PCIE0_AR_BIT63_CFG_MASK = (int)0x1,
    PIPE_SYS_PCIE0_AR_BIT63_CFG_POS = 0,
    PIPE_SYS_PCIE0_AR_BIT62_CFG_MASK = (int)0x2,
    PIPE_SYS_PCIE0_AR_BIT62_CFG_POS = 1,
    PIPE_SYS_PCIE0_AW_BIT63_CFG_MASK = (int)0x4,
    PIPE_SYS_PCIE0_AW_BIT63_CFG_POS = 2,
    PIPE_SYS_PCIE0_AW_BIT62_CFG_MASK = (int)0x8,
    PIPE_SYS_PCIE0_AW_BIT62_CFG_POS = 3,
};

enum PIPE_SYS_REG_ADDR_HIGH2BIT_XOR_PCIE1_FIELD
{
    PIPE_SYS_PCIE1_AR_BIT63_CFG_MASK = (int)0x1,
    PIPE_SYS_PCIE1_AR_BIT63_CFG_POS = 0,
    PIPE_SYS_PCIE1_AR_BIT62_CFG_MASK = (int)0x2,
    PIPE_SYS_PCIE1_AR_BIT62_CFG_POS = 1,
    PIPE_SYS_PCIE1_AW_BIT63_CFG_MASK = (int)0x4,
    PIPE_SYS_PCIE1_AW_BIT63_CFG_POS = 2,
    PIPE_SYS_PCIE1_AW_BIT62_CFG_MASK = (int)0x8,
    PIPE_SYS_PCIE1_AW_BIT62_CFG_POS = 3,
};

enum PIPE_SYS_REG_GDMA2_MODULE_EN_FIELD
{
    PIPE_SYS_GDMA2_MODULE_EN_MASK = (int)0x1,
    PIPE_SYS_GDMA2_MODULE_EN_POS = 0,
};

enum PIPE_SYS_REG_DPTX_CTL_FIELD
{
    PIPE_SYS_SOFT_DP_RST_N_MASK = (int)0x1,
    PIPE_SYS_SOFT_DP_RST_N_POS = 0,
    PIPE_SYS_SOFT_DP_VPN_SEL_MASK = (int)0x2,
    PIPE_SYS_SOFT_DP_VPN_SEL_POS = 1,
    PIPE_SYS_SOFT_DP_APB2SRAM_EN_MASK = (int)0x4,
    PIPE_SYS_SOFT_DP_APB2SRAM_EN_POS = 2,
    PIPE_SYS_SOFT_DP_DEBUG_MODE_MASK = (int)0x18,
    PIPE_SYS_SOFT_DP_DEBUG_MODE_POS = 3,
    PIPE_SYS_SOFT_DP_HOT_PLUG_DETECT_MASK = (int)0x20,
    PIPE_SYS_SOFT_DP_HOT_PLUG_DETECT_POS = 5,
    PIPE_SYS_RD_APB_LINK_RATE_MASK = (int)0x3fc0,
    PIPE_SYS_RD_APB_LINK_RATE_POS = 6,
    PIPE_SYS_RD_APB_LANE_COUNT_MASK = (int)0x7c000,
    PIPE_SYS_RD_APB_LANE_COUNT_POS = 14,
};

enum PIPE_SYS_REG_SGMII_CTRL0_FIELD
{
    PIPE_SYS_SOFT_SGETH1_TBI_SIGDET_MASK = (int)0x3,
    PIPE_SYS_SOFT_SGETH1_TBI_SIGDET_POS = 0,
    PIPE_SYS_SOFT_SGETH2_TBI_SIGDET_MASK = (int)0xc,
    PIPE_SYS_SOFT_SGETH2_TBI_SIGDET_POS = 2,
    PIPE_SYS_SGETH1_MAC_SPEED_O_MASK = (int)0x30,
    PIPE_SYS_SGETH1_MAC_SPEED_O_POS = 4,
    PIPE_SYS_SGETH2_MAC_SPEED_O_MASK = (int)0xc0,
    PIPE_SYS_SGETH2_MAC_SPEED_O_POS = 6,
    PIPE_SYS_SGETH1_SGMII_SPEED_O_MASK = (int)0x300,
    PIPE_SYS_SGETH1_SGMII_SPEED_O_POS = 8,
    PIPE_SYS_SGETH2_SGMII_SPEED_O_MASK = (int)0xc00,
    PIPE_SYS_SGETH2_SGMII_SPEED_O_POS = 10,
};

enum PIPE_SYS_REG_PIPE_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_FIELD
{
    PIPE_SYS_PIPE_PIPE_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    PIPE_SYS_PIPE_PIPE_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_POS = 0,
};

enum PIPE_SYS_REG_PIPE_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    PIPE_SYS_PIPE_PIPE_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    PIPE_SYS_PIPE_PIPE_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum PIPE_SYS_REG_PIPE_SYS_CRG_APB_CLK_TOP_RST_N_REG0_FIELD
{
    PIPE_SYS_PIPE_PIPE_SYS_CRG_APB_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    PIPE_SYS_PIPE_PIPE_SYS_CRG_APB_CLK_TOP_RST_N_REG0_POS = 0,
};

enum PIPE_SYS_REG_PIPE_SYS_CRG_APB_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    PIPE_SYS_PIPE_PIPE_SYS_CRG_APB_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    PIPE_SYS_PIPE_PIPE_SYS_CRG_APB_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum PIPE_SYS_REG_PIPE_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_FIELD
{
    PIPE_SYS_PIPE_PIPE_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    PIPE_SYS_PIPE_PIPE_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_POS = 0,
};

enum PIPE_SYS_REG_PIPE_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    PIPE_SYS_PIPE_PIPE_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    PIPE_SYS_PIPE_PIPE_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum PIPE_SYS_REG_PIPE_SYS_CFG_REG1_FIELD
{
    PIPE_SYS_PIPE_PIPE_SYS_CFG_REG1_MASK = (int)0xffffffff,
    PIPE_SYS_PIPE_PIPE_SYS_CFG_REG1_POS = 0,
};

enum PIPE_SYS_REG_PIPE_SYS_CFG_REG2_FIELD
{
    PIPE_SYS_PIPE_PIPE_SYS_CFG_REG2_MASK = (int)0xffffffff,
    PIPE_SYS_PIPE_PIPE_SYS_CFG_REG2_POS = 0,
};

enum PIPE_SYS_REG_PIPE_SYS_CFG_REG3_FIELD
{
    PIPE_SYS_PIPE_PIPE_SYS_CFG_REG3_MASK = (int)0xffffffff,
    PIPE_SYS_PIPE_PIPE_SYS_CFG_REG3_POS = 0,
};

enum PIPE_SYS_REG_PIPE_SYS_CFG_LOCK_FIELD
{
    PIPE_SYS_PIPE_SYS_CFG_LOCK_MASK = (int)0x1,
    PIPE_SYS_PIPE_SYS_CFG_LOCK_POS = 0,
};

enum PIPE_SYS_REG_DPTX_CONFIG0_FIELD
{
    PIPE_SYS_DPTX_PHY_CONFIG_0_MASK = (int)0xff,
    PIPE_SYS_DPTX_PHY_CONFIG_0_POS = 0,
    PIPE_SYS_DPTX_PHY_REPEATER_ENABLE_MASK = (int)0x100,
    PIPE_SYS_DPTX_PHY_REPEATER_ENABLE_POS = 8,
    PIPE_SYS_DPTX_PHY_SSC_ENABLE_MASK = (int)0x200,
    PIPE_SYS_DPTX_PHY_SSC_ENABLE_POS = 9,
    PIPE_SYS_DPTX_PHY_ELEC_IDLE_MASK = (int)0x3c00,
    PIPE_SYS_DPTX_PHY_ELEC_IDLE_POS = 10,
    PIPE_SYS_DPTX_PHY_PLL_SETTINGS_MASK = (int)0x3fc000,
    PIPE_SYS_DPTX_PHY_PLL_SETTINGS_POS = 14,
    PIPE_SYS_DPTX_PHY_LINK_RATE_MASK = (int)0x3fc00000,
    PIPE_SYS_DPTX_PHY_LINK_RATE_POS = 22,
    PIPE_SYS_DPTX_PHY_TRANSMIT_PRBS7_MASK = (int)0x40000000,
    PIPE_SYS_DPTX_PHY_TRANSMIT_PRBS7_POS = 30,
};

enum PIPE_SYS_REG_DPTX_CONFIG1_FIELD
{
    PIPE_SYS_DPTX_PHY_POWER_DOWN_MASK = (int)0xf,
    PIPE_SYS_DPTX_PHY_POWER_DOWN_POS = 0,
};

enum PIPE_SYS_REG_DPTX_LANE_FIELD
{
    PIPE_SYS_DPTX_PHY_VOLTAGE_DIFF_LANE_1_MASK = (int)0x1f,
    PIPE_SYS_DPTX_PHY_VOLTAGE_DIFF_LANE_1_POS = 0,
    PIPE_SYS_DPTX_PHY_VOLTAGE_DIFF_LANE_0_MASK = (int)0x3e0,
    PIPE_SYS_DPTX_PHY_VOLTAGE_DIFF_LANE_0_POS = 5,
    PIPE_SYS_DPTX_PHY_POSTEMPHASIS_LANE_1_MASK = (int)0x7c00,
    PIPE_SYS_DPTX_PHY_POSTEMPHASIS_LANE_1_POS = 10,
    PIPE_SYS_DPTX_PHY_POSTEMPHASIS_LANE_0_MASK = (int)0xf8000,
    PIPE_SYS_DPTX_PHY_POSTEMPHASIS_LANE_0_POS = 15,
    PIPE_SYS_DPTX_PHY_PREEMPHASIS_LANE_1_MASK = (int)0x1f00000,
    PIPE_SYS_DPTX_PHY_PREEMPHASIS_LANE_1_POS = 20,
    PIPE_SYS_DPTX_PHY_PREEMPHASIS_LANE_0_MASK = (int)0x3e000000,
    PIPE_SYS_DPTX_PHY_PREEMPHASIS_LANE_0_POS = 25,
};

enum PIPE_SYS_REG_PHY_DPTX_PHY_STATUS_FIELD
{
    PIPE_SYS_PHY_DPTX_PHY_STATUS_MASK = (int)0xffffffff,
    PIPE_SYS_PHY_DPTX_PHY_STATUS_POS = 0,
};

enum PIPE_SYS_REG_VPN_SEL_FIELD
{
    PIPE_SYS_VPN_VDAC_SEL_MASK = (int)0x1,
    PIPE_SYS_VPN_VDAC_SEL_POS = 0,
    PIPE_SYS_VPN_DPTX_SEL_MASK = (int)0x2,
    PIPE_SYS_VPN_DPTX_SEL_POS = 1,
    PIPE_SYS_VPN_SYNC_SEL_MASK = (int)0x4,
    PIPE_SYS_VPN_SYNC_SEL_POS = 2,
    PIPE_SYS_VPN_CLK_INV_SEL_MASK = (int)0x8,
    PIPE_SYS_VPN_CLK_INV_SEL_POS = 3,
    PIPE_SYS_VPN0_VDAC_INV_MASK = (int)0x10,
    PIPE_SYS_VPN0_VDAC_INV_POS = 4,
    PIPE_SYS_VPN1_VDAC_INV_MASK = (int)0x20,
    PIPE_SYS_VPN1_VDAC_INV_POS = 5,
    PIPE_SYS_D_VPN_SEL_MASK = (int)0x40,
    PIPE_SYS_D_VPN_SEL_POS = 6,
    PIPE_SYS_VPN_SEL_MASK = (int)0x80,
    PIPE_SYS_VPN_SEL_POS = 7,
};

enum PIPE_SYS_REG_PIPE_SYS_ADJUST_ADB400_EN_FIELD
{
    PIPE_SYS_ADJUST_ADB400_MST_PERIPH_PIPE_EN_MASK = (int)0x1,
    PIPE_SYS_ADJUST_ADB400_MST_PERIPH_PIPE_EN_POS = 0,
    PIPE_SYS_ADJUST_ADB400_MST_CPU_PIPE_EN_MASK = (int)0x2,
    PIPE_SYS_ADJUST_ADB400_MST_CPU_PIPE_EN_POS = 1,
    PIPE_SYS_ADJUST_ADB400_SLV_PIPE_DDR_EN_MASK = (int)0x4,
    PIPE_SYS_ADJUST_ADB400_SLV_PIPE_DDR_EN_POS = 2,
    PIPE_SYS_ADJUST_ADB400_SLV_PIPE_ANA_EN_MASK = (int)0x8,
    PIPE_SYS_ADJUST_ADB400_SLV_PIPE_ANA_EN_POS = 3,
    PIPE_SYS_ADJUST_ADB400_SLV_PIPE_CPU_EN_MASK = (int)0x10,
    PIPE_SYS_ADJUST_ADB400_SLV_PIPE_CPU_EN_POS = 4,
    PIPE_SYS_ADJUST_ADB400_SLV_PIPE_PERIPH_EN_MASK = (int)0x20,
    PIPE_SYS_ADJUST_ADB400_SLV_PIPE_PERIPH_EN_POS = 5,
};

enum PIPE_SYS_REG_HF_DLL_CTRL_RD_REG_FIELD
{
    PIPE_SYS_HF_DLL_CTRL_RD_REG_MASK = (int)0xff,
    PIPE_SYS_HF_DLL_CTRL_RD_REG_POS = 0,
};

enum PIPE_SYS_REG_HF_DLL_CTRL_REG_FIELD
{
    PIPE_SYS_HF_DLL_CTRL_MASK = (int)0xffffff,
    PIPE_SYS_HF_DLL_CTRL_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG0_FIELD
{
    PIPE_SYS_PCIE1_SURPRISE_DOWN_ERR_MASK = (int)0xff,
    PIPE_SYS_PCIE1_SURPRISE_DOWN_ERR_POS = 0,
    PIPE_SYS_PCIE1_POWER_UP_RST_N_MASK = (int)0x100,
    PIPE_SYS_PCIE1_POWER_UP_RST_N_POS = 8,
    PIPE_SYS_PCIE1_BUTTON_RST_N_MASK = (int)0x200,
    PIPE_SYS_PCIE1_BUTTON_RST_N_POS = 9,
    PIPE_SYS_PCIE1_SYS_AUX_PWR_DET_MASK = (int)0x400,
    PIPE_SYS_PCIE1_SYS_AUX_PWR_DET_POS = 10,
    PIPE_SYS_PCIE1_APP_LTSSM_ENABLE_MASK = (int)0x800,
    PIPE_SYS_PCIE1_APP_LTSSM_ENABLE_POS = 11,
    PIPE_SYS_PCIE1_APP_HOLD_PHY_RST_MASK = (int)0x1000,
    PIPE_SYS_PCIE1_APP_HOLD_PHY_RST_POS = 12,
    PIPE_SYS_PCIE1_APP_CLK_REQ_N_MASK = (int)0x2000,
    PIPE_SYS_PCIE1_APP_CLK_REQ_N_POS = 13,
    PIPE_SYS_PCIE1_APP_CLK_PM_EN_MASK = (int)0x4000,
    PIPE_SYS_PCIE1_APP_CLK_PM_EN_POS = 14,
    PIPE_SYS_PCIE1_APP_INIT_RST_MASK = (int)0x8000,
    PIPE_SYS_PCIE1_APP_INIT_RST_POS = 15,
    PIPE_SYS_PCIE1_APP_REQ_ENTR_L1_MASK = (int)0x10000,
    PIPE_SYS_PCIE1_APP_REQ_ENTR_L1_POS = 16,
    PIPE_SYS_PCIE1_APP_READY_ENTR_L23_MASK = (int)0x20000,
    PIPE_SYS_PCIE1_APP_READY_ENTR_L23_POS = 17,
    PIPE_SYS_PCIE1_APP_REQ_EXIT_L1_MASK = (int)0x40000,
    PIPE_SYS_PCIE1_APP_REQ_EXIT_L1_POS = 18,
    PIPE_SYS_PCIE1_APP_XFER_PENDING_MASK = (int)0x80000,
    PIPE_SYS_PCIE1_APP_XFER_PENDING_POS = 19,
    PIPE_SYS_PCIE1_EXP_ROM_VALIDATION_STATUS_STROBE_MASK = (int)0xff00000,
    PIPE_SYS_PCIE1_EXP_ROM_VALIDATION_STATUS_STROBE_POS = 20,
};

enum PIPE_SYS_REG_PCIE1_REG1_FIELD
{
    PIPE_SYS_PCIE1_EXP_ROM_VALIDATION_STATUS_MASK = (int)0xffffff,
    PIPE_SYS_PCIE1_EXP_ROM_VALIDATION_STATUS_POS = 0,
    PIPE_SYS_PCIE1_EXP_ROM_VALIDATION_DETAILS_STROBE_MASK = (int)0xff000000,
    PIPE_SYS_PCIE1_EXP_ROM_VALIDATION_DETAILS_STROBE_POS = 24,
};

enum PIPE_SYS_REG_PCIE1_REG2_FIELD
{
    PIPE_SYS_PCIE1_EXP_ROM_VALIDATION_DETAILS_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_EXP_ROM_VALIDATION_DETAILS_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG3_FIELD
{
    PIPE_SYS_PCIE1_APP_REQ_RETRY_EN_MASK = (int)0x1,
    PIPE_SYS_PCIE1_APP_REQ_RETRY_EN_POS = 0,
    PIPE_SYS_PCIE1_APP_PF_REQ_RETRY_EN_MASK = (int)0x1fe,
    PIPE_SYS_PCIE1_APP_PF_REQ_RETRY_EN_POS = 1,
    PIPE_SYS_PCIE1_CFG_HP_SLOT_CTRL_ACCESS_MASK = (int)0x1fe00,
    PIPE_SYS_PCIE1_CFG_HP_SLOT_CTRL_ACCESS_POS = 9,
    PIPE_SYS_PCIE1_CFG_DLL_STATE_CHGED_EN_MASK = (int)0x1fe0000,
    PIPE_SYS_PCIE1_CFG_DLL_STATE_CHGED_EN_POS = 17,
};

enum PIPE_SYS_REG_PCIE1_REG4_FIELD
{
    PIPE_SYS_PCIE1_CFG_CMD_CPLED_INT_EN_MASK = (int)0xff,
    PIPE_SYS_PCIE1_CFG_CMD_CPLED_INT_EN_POS = 0,
    PIPE_SYS_PCIE1_CFG_HP_INT_EN_MASK = (int)0xff00,
    PIPE_SYS_PCIE1_CFG_HP_INT_EN_POS = 8,
    PIPE_SYS_PCIE1_CFG_PRE_DET_CHGED_EN_MASK = (int)0xff0000,
    PIPE_SYS_PCIE1_CFG_PRE_DET_CHGED_EN_POS = 16,
    PIPE_SYS_PCIE1_CFG_MRL_SENSOR_CHGED_EN_MASK = (int)0xff000000,
    PIPE_SYS_PCIE1_CFG_MRL_SENSOR_CHGED_EN_POS = 24,
};

enum PIPE_SYS_REG_PCIE1_REG5_FIELD
{
    PIPE_SYS_PCIE1_CFG_PWR_FAULT_DET_EN_MASK = (int)0xff,
    PIPE_SYS_PCIE1_CFG_PWR_FAULT_DET_EN_POS = 0,
    PIPE_SYS_PCIE1_CFG_ATTEN_BUTTON_PRESSED_EN_MASK = (int)0xff00,
    PIPE_SYS_PCIE1_CFG_ATTEN_BUTTON_PRESSED_EN_POS = 8,
    PIPE_SYS_PCIE1_LOCAL_REF_CLK_REQ_N_MASK = (int)0x10000,
    PIPE_SYS_PCIE1_LOCAL_REF_CLK_REQ_N_POS = 16,
    PIPE_SYS_PCIE1_CLKREQ_IN_N_MASK = (int)0x20000,
    PIPE_SYS_PCIE1_CLKREQ_IN_N_POS = 17,
    PIPE_SYS_PCIE1_CFG_HW_AUTO_SP_DIS_MASK = (int)0x40000,
    PIPE_SYS_PCIE1_CFG_HW_AUTO_SP_DIS_POS = 18,
    PIPE_SYS_PCIE1_RADM_TRGT1_VC_MASK = (int)0x380000,
    PIPE_SYS_PCIE1_RADM_TRGT1_VC_POS = 19,
    PIPE_SYS_PCIE1_APP_DBI_RO_WR_DISABLE_MASK = (int)0x400000,
    PIPE_SYS_PCIE1_APP_DBI_RO_WR_DISABLE_POS = 22,
    PIPE_SYS_PCIE1_VEN_MSI_FUNC_NUM_MASK = (int)0x3800000,
    PIPE_SYS_PCIE1_VEN_MSI_FUNC_NUM_POS = 23,
    PIPE_SYS_PCIE1_VEN_MSI_TC_MASK = (int)0x1c000000,
    PIPE_SYS_PCIE1_VEN_MSI_TC_POS = 26,
};

enum PIPE_SYS_REG_PCIE1_REG6_FIELD
{
    PIPE_SYS_PCIE1_VEN_MSI_VECTOR_MASK = (int)0x1f,
    PIPE_SYS_PCIE1_VEN_MSI_VECTOR_POS = 0,
    PIPE_SYS_PCIE1_CFG_MSI_EN_MASK = (int)0x1fe0,
    PIPE_SYS_PCIE1_CFG_MSI_EN_POS = 5,
};

enum PIPE_SYS_REG_PCIE1_REG7_FIELD
{
    PIPE_SYS_PCIE1_CFG_MSI_MASK_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_MSI_MASK_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG8_FIELD
{
    PIPE_SYS_PCIE1_CFG_MSI_MASK_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_MSI_MASK_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG9_FIELD
{
    PIPE_SYS_PCIE1_CFG_MSI_MASK_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_MSI_MASK_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG10_FIELD
{
    PIPE_SYS_PCIE1_CFG_MSI_MASK_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_MSI_MASK_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG11_FIELD
{
    PIPE_SYS_PCIE1_CFG_MSI_MASK_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_MSI_MASK_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG12_FIELD
{
    PIPE_SYS_PCIE1_CFG_MSI_MASK_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_MSI_MASK_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG13_FIELD
{
    PIPE_SYS_PCIE1_CFG_MSI_MASK_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_MSI_MASK_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG14_FIELD
{
    PIPE_SYS_PCIE1_CFG_MSI_MASK_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_MSI_MASK_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG15_FIELD
{
    PIPE_SYS_PCIE1_CFG_MSI_PENDING_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_MSI_PENDING_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG16_FIELD
{
    PIPE_SYS_PCIE1_CFG_MSI_PENDING_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_MSI_PENDING_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG17_FIELD
{
    PIPE_SYS_PCIE1_CFG_MSI_PENDING_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_MSI_PENDING_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG18_FIELD
{
    PIPE_SYS_PCIE1_CFG_MSI_PENDING_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_MSI_PENDING_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG19_FIELD
{
    PIPE_SYS_PCIE1_CFG_MSI_PENDING_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_MSI_PENDING_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG20_FIELD
{
    PIPE_SYS_PCIE1_CFG_MSI_PENDING_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_MSI_PENDING_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG21_FIELD
{
    PIPE_SYS_PCIE1_CFG_MSI_PENDING_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_MSI_PENDING_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG22_FIELD
{
    PIPE_SYS_PCIE1_CFG_MSI_PENDING_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_MSI_PENDING_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG23_FIELD
{
    PIPE_SYS_PCIE1_CFG_LTR_M_EN_MASK = (int)0x1,
    PIPE_SYS_PCIE1_CFG_LTR_M_EN_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG24_FIELD
{
    PIPE_SYS_PCIE1_APP_LTR_MSG_LATENCY_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_APP_LTR_MSG_LATENCY_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG25_FIELD
{
    PIPE_SYS_PCIE1_APP_LTR_MSG_FUNC_NUM_MASK = (int)0x7,
    PIPE_SYS_PCIE1_APP_LTR_MSG_FUNC_NUM_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG26_FIELD
{
    PIPE_SYS_PCIE1_CFG_LTR_MAX_LATENCY_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_LTR_MAX_LATENCY_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG27_FIELD
{
    PIPE_SYS_PCIE1_CFG_LTR_MAX_LATENCY_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_LTR_MAX_LATENCY_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG28_FIELD
{
    PIPE_SYS_PCIE1_CFG_LTR_MAX_LATENCY_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_LTR_MAX_LATENCY_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG29_FIELD
{
    PIPE_SYS_PCIE1_CFG_LTR_MAX_LATENCY_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_LTR_MAX_LATENCY_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG30_FIELD
{
    PIPE_SYS_PCIE1_CFG_LTR_MAX_LATENCY_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_LTR_MAX_LATENCY_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG31_FIELD
{
    PIPE_SYS_PCIE1_CFG_LTR_MAX_LATENCY_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_LTR_MAX_LATENCY_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG32_FIELD
{
    PIPE_SYS_PCIE1_CFG_LTR_MAX_LATENCY_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_LTR_MAX_LATENCY_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG33_FIELD
{
    PIPE_SYS_PCIE1_CFG_LTR_MAX_LATENCY_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_LTR_MAX_LATENCY_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG34_FIELD
{
    PIPE_SYS_PCIE1_CFG_DISABLE_LTR_CLR_MSG_MASK = (int)0x1,
    PIPE_SYS_PCIE1_CFG_DISABLE_LTR_CLR_MSG_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG35_FIELD
{
    PIPE_SYS_PCIE1_APP_LTR_LATENCY_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_APP_LTR_LATENCY_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG36_FIELD
{
    PIPE_SYS_PCIE1_RADM_MSG_LTR_MASK = (int)0x1,
    PIPE_SYS_PCIE1_RADM_MSG_LTR_POS = 0,
    PIPE_SYS_PCIE1_VEN_MSG_FMT_MASK = (int)0x6,
    PIPE_SYS_PCIE1_VEN_MSG_FMT_POS = 1,
    PIPE_SYS_PCIE1_VEN_MSG_TYPE_MASK = (int)0xf8,
    PIPE_SYS_PCIE1_VEN_MSG_TYPE_POS = 3,
    PIPE_SYS_PCIE1_VEN_MSG_TC_MASK = (int)0x700,
    PIPE_SYS_PCIE1_VEN_MSG_TC_POS = 8,
    PIPE_SYS_PCIE1_VEN_MSG_TD_MASK = (int)0x800,
    PIPE_SYS_PCIE1_VEN_MSG_TD_POS = 11,
    PIPE_SYS_PCIE1_VEN_MSG_EP_MASK = (int)0x1000,
    PIPE_SYS_PCIE1_VEN_MSG_EP_POS = 12,
    PIPE_SYS_PCIE1_VEN_MSG_ATTR_MASK = (int)0x6000,
    PIPE_SYS_PCIE1_VEN_MSG_ATTR_POS = 13,
    PIPE_SYS_PCIE1_VEN_MSG_LEN_MASK = (int)0x1ff8000,
    PIPE_SYS_PCIE1_VEN_MSG_LEN_POS = 15,
    PIPE_SYS_PCIE1_VEN_MSG_FUNC_NUM_MASK = (int)0xe000000,
    PIPE_SYS_PCIE1_VEN_MSG_FUNC_NUM_POS = 25,
};

enum PIPE_SYS_REG_PCIE1_REG37_FIELD
{
    PIPE_SYS_PCIE1_VEN_MSG_TAG_MASK = (int)0xff,
    PIPE_SYS_PCIE1_VEN_MSG_TAG_POS = 0,
    PIPE_SYS_PCIE1_VEN_MSG_CODE_MASK = (int)0xff00,
    PIPE_SYS_PCIE1_VEN_MSG_CODE_POS = 8,
};

enum PIPE_SYS_REG_PCIE1_REG38_FIELD
{
    PIPE_SYS_PCIE1_VEN_MSG_DATA_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_VEN_MSG_DATA_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG39_FIELD
{
    PIPE_SYS_PCIE1_VEN_MSG_DATA_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_VEN_MSG_DATA_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG40_FIELD
{
    PIPE_SYS_PCIE1_SYS_INT_MASK = (int)0xff,
    PIPE_SYS_PCIE1_SYS_INT_POS = 0,
    PIPE_SYS_PCIE1_APPS_PM_XMT_PME_MASK = (int)0xff00,
    PIPE_SYS_PCIE1_APPS_PM_XMT_PME_POS = 8,
    PIPE_SYS_PCIE1_SYS_ATTEN_BUTTON_PRESSED_MASK = (int)0xff0000,
    PIPE_SYS_PCIE1_SYS_ATTEN_BUTTON_PRESSED_POS = 16,
    PIPE_SYS_PCIE1_SYS_PRE_DET_STATE_MASK = (int)0xff000000,
    PIPE_SYS_PCIE1_SYS_PRE_DET_STATE_POS = 24,
};

enum PIPE_SYS_REG_PCIE1_REG41_FIELD
{
    PIPE_SYS_PCIE1_SYS_MRL_SENSOR_STATE_MASK = (int)0xff,
    PIPE_SYS_PCIE1_SYS_MRL_SENSOR_STATE_POS = 0,
    PIPE_SYS_PCIE1_SYS_PWR_FAULT_DET_MASK = (int)0xff00,
    PIPE_SYS_PCIE1_SYS_PWR_FAULT_DET_POS = 8,
    PIPE_SYS_PCIE1_SYS_MRL_SENSOR_CHGED_MASK = (int)0xff0000,
    PIPE_SYS_PCIE1_SYS_MRL_SENSOR_CHGED_POS = 16,
    PIPE_SYS_PCIE1_SYS_PRE_DET_CHGED_MASK = (int)0xff000000,
    PIPE_SYS_PCIE1_SYS_PRE_DET_CHGED_POS = 24,
};

enum PIPE_SYS_REG_PCIE1_REG42_FIELD
{
    PIPE_SYS_PCIE1_SYS_CMD_CPLED_INT_MASK = (int)0xff,
    PIPE_SYS_PCIE1_SYS_CMD_CPLED_INT_POS = 0,
    PIPE_SYS_PCIE1_SYS_EML_INTERLOCK_ENGAGED_MASK = (int)0xff00,
    PIPE_SYS_PCIE1_SYS_EML_INTERLOCK_ENGAGED_POS = 8,
    PIPE_SYS_PCIE1_APP_UNLOCK_MSG_MASK = (int)0x10000,
    PIPE_SYS_PCIE1_APP_UNLOCK_MSG_POS = 16,
    PIPE_SYS_PCIE1_APPS_PM_XMT_TURNOFF_MASK = (int)0x20000,
    PIPE_SYS_PCIE1_APPS_PM_XMT_TURNOFF_POS = 17,
};

enum PIPE_SYS_REG_PCIE1_REG43_FIELD
{
    PIPE_SYS_PCIE1_CFG_PWR_IND_MASK = (int)0xffff,
    PIPE_SYS_PCIE1_CFG_PWR_IND_POS = 0,
    PIPE_SYS_PCIE1_CFG_ATTEN_IND_MASK = (int)0xffff0000,
    PIPE_SYS_PCIE1_CFG_ATTEN_IND_POS = 16,
};

enum PIPE_SYS_REG_PCIE1_REG44_FIELD
{
    PIPE_SYS_PCIE1_CFG_PWR_CTRLER_CTRL_MASK = (int)0xff,
    PIPE_SYS_PCIE1_CFG_PWR_CTRLER_CTRL_POS = 0,
    PIPE_SYS_PCIE1_CFG_SYS_ERR_RC_MASK = (int)0xff00,
    PIPE_SYS_PCIE1_CFG_SYS_ERR_RC_POS = 8,
    PIPE_SYS_PCIE1_CFG_AER_RC_ERR_INT_MASK = (int)0xff0000,
    PIPE_SYS_PCIE1_CFG_AER_RC_ERR_INT_POS = 16,
    PIPE_SYS_PCIE1_CFG_AER_RC_ERR_MSI_MASK = (int)0xff000000,
    PIPE_SYS_PCIE1_CFG_AER_RC_ERR_MSI_POS = 24,
};

enum PIPE_SYS_REG_PCIE1_REG45_FIELD
{
    PIPE_SYS_PCIE1_CFG_AER_INT_MSG_NUM_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_AER_INT_MSG_NUM_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG46_FIELD
{
    PIPE_SYS_PCIE1_CFG_AER_INT_MSG_NUM_1_MASK = (int)0xff,
    PIPE_SYS_PCIE1_CFG_AER_INT_MSG_NUM_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG47_FIELD
{
    PIPE_SYS_PCIE1_CFG_PME_INT_MASK = (int)0xff,
    PIPE_SYS_PCIE1_CFG_PME_INT_POS = 0,
    PIPE_SYS_PCIE1_CFG_PME_MSI_MASK = (int)0xff00,
    PIPE_SYS_PCIE1_CFG_PME_MSI_POS = 8,
    PIPE_SYS_PCIE1_CFG_CRS_SW_VIS_EN_MASK = (int)0xff0000,
    PIPE_SYS_PCIE1_CFG_CRS_SW_VIS_EN_POS = 16,
};

enum PIPE_SYS_REG_PCIE1_REG48_FIELD
{
    PIPE_SYS_PCIE1_CFG_PCIE_CAP_INT_MSG_NUM_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_PCIE_CAP_INT_MSG_NUM_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG49_FIELD
{
    PIPE_SYS_PCIE1_CFG_PCIE_CAP_INT_MSG_NUM_1_MASK = (int)0xff,
    PIPE_SYS_PCIE1_CFG_PCIE_CAP_INT_MSG_NUM_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG50_FIELD
{
    PIPE_SYS_PCIE1_CFG_EML_CONTROL_MASK = (int)0xff,
    PIPE_SYS_PCIE1_CFG_EML_CONTROL_POS = 0,
    PIPE_SYS_PCIE1_RTLH_RFC_UPD_MASK = (int)0x100,
    PIPE_SYS_PCIE1_RTLH_RFC_UPD_POS = 8,
};

enum PIPE_SYS_REG_PCIE1_REG51_FIELD
{
    PIPE_SYS_PCIE1_RTLH_RFC_DATA_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_RTLH_RFC_DATA_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG52_FIELD
{
    PIPE_SYS_PCIE1_RADM_INTA_ASSERTED_MASK = (int)0x1,
    PIPE_SYS_PCIE1_RADM_INTA_ASSERTED_POS = 0,
    PIPE_SYS_PCIE1_RADM_INTB_ASSERTED_MASK = (int)0x2,
    PIPE_SYS_PCIE1_RADM_INTB_ASSERTED_POS = 1,
    PIPE_SYS_PCIE1_RADM_INTC_ASSERTED_MASK = (int)0x4,
    PIPE_SYS_PCIE1_RADM_INTC_ASSERTED_POS = 2,
    PIPE_SYS_PCIE1_RADM_INTD_ASSERTED_MASK = (int)0x8,
    PIPE_SYS_PCIE1_RADM_INTD_ASSERTED_POS = 3,
    PIPE_SYS_PCIE1_RADM_INTA_DEASSERTED_MASK = (int)0x10,
    PIPE_SYS_PCIE1_RADM_INTA_DEASSERTED_POS = 4,
    PIPE_SYS_PCIE1_RADM_INTB_DEASSERTED_MASK = (int)0x20,
    PIPE_SYS_PCIE1_RADM_INTB_DEASSERTED_POS = 5,
    PIPE_SYS_PCIE1_RADM_INTC_DEASSERTED_MASK = (int)0x40,
    PIPE_SYS_PCIE1_RADM_INTC_DEASSERTED_POS = 6,
    PIPE_SYS_PCIE1_RADM_INTD_DEASSERTED_MASK = (int)0x80,
    PIPE_SYS_PCIE1_RADM_INTD_DEASSERTED_POS = 7,
    PIPE_SYS_PCIE1_RADM_CORRECTABLE_ERR_MASK = (int)0x100,
    PIPE_SYS_PCIE1_RADM_CORRECTABLE_ERR_POS = 8,
    PIPE_SYS_PCIE1_RADM_NONFATAL_ERR_MASK = (int)0x200,
    PIPE_SYS_PCIE1_RADM_NONFATAL_ERR_POS = 9,
    PIPE_SYS_PCIE1_RADM_FATAL_ERR_MASK = (int)0x400,
    PIPE_SYS_PCIE1_RADM_FATAL_ERR_POS = 10,
    PIPE_SYS_PCIE1_RADM_PM_PME_MASK = (int)0x800,
    PIPE_SYS_PCIE1_RADM_PM_PME_POS = 11,
    PIPE_SYS_PCIE1_RADM_PM_TO_ACK_MASK = (int)0x1000,
    PIPE_SYS_PCIE1_RADM_PM_TO_ACK_POS = 12,
    PIPE_SYS_PCIE1_HP_PME_MASK = (int)0x1fe000,
    PIPE_SYS_PCIE1_HP_PME_POS = 13,
    PIPE_SYS_PCIE1_HP_INT_MASK = (int)0x1fe00000,
    PIPE_SYS_PCIE1_HP_INT_POS = 21,
};

enum PIPE_SYS_REG_PCIE1_REG53_FIELD
{
    PIPE_SYS_PCIE1_HP_MSI_MASK = (int)0xff,
    PIPE_SYS_PCIE1_HP_MSI_POS = 0,
    PIPE_SYS_PCIE1_RADM_Q_NOT_EMPTY_MASK = (int)0x100,
    PIPE_SYS_PCIE1_RADM_Q_NOT_EMPTY_POS = 8,
    PIPE_SYS_PCIE1_RADM_QOVERFLOW_MASK = (int)0x200,
    PIPE_SYS_PCIE1_RADM_QOVERFLOW_POS = 9,
    PIPE_SYS_PCIE1_PM_XTLH_BLOCK_TLP_MASK = (int)0x400,
    PIPE_SYS_PCIE1_PM_XTLH_BLOCK_TLP_POS = 10,
};

enum PIPE_SYS_REG_PCIE1_REG54_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_START_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_START_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG55_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_START_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_START_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG56_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_START_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_START_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG57_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_START_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_START_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG58_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_START_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_START_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG59_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_START_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_START_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG60_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_START_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_START_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG61_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_START_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_START_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG62_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_START_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_START_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG63_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_START_9_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_START_9_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG64_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_START_10_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_START_10_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG65_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_START_11_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_START_11_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG66_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_START_12_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_START_12_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG67_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_START_13_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_START_13_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG68_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_START_14_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_START_14_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG69_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_START_15_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_START_15_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG70_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG71_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG72_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG73_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG74_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG75_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG76_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG77_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG78_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG79_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_9_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_9_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG80_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_10_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_10_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG81_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_11_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_11_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG82_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_12_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_12_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG83_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_13_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_13_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG84_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_14_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_14_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG85_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_15_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR0_LIMIT_15_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG86_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR1_START_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR1_START_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG87_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR1_START_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR1_START_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG88_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR1_START_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR1_START_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG89_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR1_START_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR1_START_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG90_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR1_START_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR1_START_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG91_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR1_START_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR1_START_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG92_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR1_START_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR1_START_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG93_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR1_START_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR1_START_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG94_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR1_LIMIT_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR1_LIMIT_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG95_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR1_LIMIT_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR1_LIMIT_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG96_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR1_LIMIT_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR1_LIMIT_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG97_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR1_LIMIT_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR1_LIMIT_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG98_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR1_LIMIT_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR1_LIMIT_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG99_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR1_LIMIT_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR1_LIMIT_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG100_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR1_LIMIT_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR1_LIMIT_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG101_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR1_LIMIT_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR1_LIMIT_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG102_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_START_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_START_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG103_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_START_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_START_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG104_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_START_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_START_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG105_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_START_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_START_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG106_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_START_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_START_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG107_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_START_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_START_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG108_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_START_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_START_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG109_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_START_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_START_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG110_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_START_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_START_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG111_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_START_9_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_START_9_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG112_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_START_10_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_START_10_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG113_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_START_11_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_START_11_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG114_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_START_12_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_START_12_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG115_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_START_13_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_START_13_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG116_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_START_14_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_START_14_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG117_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_START_15_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_START_15_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG118_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG119_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG120_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG121_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG122_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG123_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG124_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG125_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG126_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG127_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_9_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_9_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG128_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_10_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_10_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG129_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_11_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_11_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG130_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_12_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_12_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG131_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_13_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_13_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG132_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_14_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_14_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG133_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_15_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR2_LIMIT_15_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG134_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR3_START_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR3_START_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG135_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR3_START_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR3_START_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG136_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR3_START_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR3_START_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG137_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR3_START_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR3_START_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG138_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR3_START_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR3_START_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG139_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR3_START_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR3_START_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG140_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR3_START_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR3_START_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG141_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR3_START_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR3_START_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG142_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR3_LIMIT_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR3_LIMIT_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG143_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR3_LIMIT_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR3_LIMIT_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG144_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR3_LIMIT_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR3_LIMIT_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG145_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR3_LIMIT_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR3_LIMIT_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG146_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR3_LIMIT_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR3_LIMIT_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG147_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR3_LIMIT_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR3_LIMIT_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG148_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR3_LIMIT_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR3_LIMIT_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG149_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR3_LIMIT_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR3_LIMIT_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG150_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_START_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_START_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG151_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_START_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_START_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG152_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_START_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_START_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG153_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_START_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_START_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG154_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_START_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_START_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG155_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_START_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_START_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG156_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_START_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_START_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG157_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_START_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_START_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG158_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_START_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_START_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG159_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_START_9_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_START_9_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG160_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_START_10_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_START_10_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG161_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_START_11_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_START_11_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG162_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_START_12_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_START_12_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG163_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_START_13_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_START_13_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG164_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_START_14_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_START_14_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG165_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_START_15_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_START_15_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG166_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG167_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG168_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG169_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG170_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG171_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG172_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG173_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG174_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG175_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_9_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_9_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG176_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_10_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_10_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG177_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_11_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_11_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG178_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_12_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_12_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG179_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_13_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_13_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG180_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_14_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_14_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG181_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_15_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR4_LIMIT_15_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG182_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR5_START_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR5_START_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG183_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR5_START_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR5_START_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG184_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR5_START_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR5_START_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG185_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR5_START_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR5_START_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG186_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR5_START_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR5_START_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG187_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR5_START_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR5_START_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG188_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR5_START_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR5_START_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG189_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR5_START_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR5_START_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG190_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR5_LIMIT_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR5_LIMIT_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG191_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR5_LIMIT_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR5_LIMIT_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG192_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR5_LIMIT_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR5_LIMIT_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG193_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR5_LIMIT_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR5_LIMIT_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG194_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR5_LIMIT_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR5_LIMIT_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG195_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR5_LIMIT_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR5_LIMIT_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG196_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR5_LIMIT_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR5_LIMIT_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG197_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAR5_LIMIT_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_BAR5_LIMIT_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG198_FIELD
{
    PIPE_SYS_PCIE1_CFG_EXP_ROM_START_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_EXP_ROM_START_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG199_FIELD
{
    PIPE_SYS_PCIE1_CFG_EXP_ROM_START_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_EXP_ROM_START_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG200_FIELD
{
    PIPE_SYS_PCIE1_CFG_EXP_ROM_START_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_EXP_ROM_START_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG201_FIELD
{
    PIPE_SYS_PCIE1_CFG_EXP_ROM_START_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_EXP_ROM_START_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG202_FIELD
{
    PIPE_SYS_PCIE1_CFG_EXP_ROM_START_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_EXP_ROM_START_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG203_FIELD
{
    PIPE_SYS_PCIE1_CFG_EXP_ROM_START_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_EXP_ROM_START_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG204_FIELD
{
    PIPE_SYS_PCIE1_CFG_EXP_ROM_START_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_EXP_ROM_START_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG205_FIELD
{
    PIPE_SYS_PCIE1_CFG_EXP_ROM_START_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_EXP_ROM_START_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG206_FIELD
{
    PIPE_SYS_PCIE1_CFG_EXP_ROM_LIMIT_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_EXP_ROM_LIMIT_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG207_FIELD
{
    PIPE_SYS_PCIE1_CFG_EXP_ROM_LIMIT_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_EXP_ROM_LIMIT_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG208_FIELD
{
    PIPE_SYS_PCIE1_CFG_EXP_ROM_LIMIT_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_EXP_ROM_LIMIT_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG209_FIELD
{
    PIPE_SYS_PCIE1_CFG_EXP_ROM_LIMIT_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_EXP_ROM_LIMIT_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG210_FIELD
{
    PIPE_SYS_PCIE1_CFG_EXP_ROM_LIMIT_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_EXP_ROM_LIMIT_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG211_FIELD
{
    PIPE_SYS_PCIE1_CFG_EXP_ROM_LIMIT_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_EXP_ROM_LIMIT_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG212_FIELD
{
    PIPE_SYS_PCIE1_CFG_EXP_ROM_LIMIT_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_EXP_ROM_LIMIT_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG213_FIELD
{
    PIPE_SYS_PCIE1_CFG_EXP_ROM_LIMIT_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_EXP_ROM_LIMIT_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG214_FIELD
{
    PIPE_SYS_PCIE1_CFG_BUS_MASTER_EN_MASK = (int)0xff,
    PIPE_SYS_PCIE1_CFG_BUS_MASTER_EN_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG215_FIELD
{
    PIPE_SYS_PCIE1_CFG_2NDBUS_NUM_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_2NDBUS_NUM_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG216_FIELD
{
    PIPE_SYS_PCIE1_CFG_2NDBUS_NUM_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_2NDBUS_NUM_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG217_FIELD
{
    PIPE_SYS_PCIE1_CFG_SUBBUS_NUM_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_SUBBUS_NUM_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG218_FIELD
{
    PIPE_SYS_PCIE1_CFG_SUBBUS_NUM_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_SUBBUS_NUM_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG219_FIELD
{
    PIPE_SYS_PCIE1_CFG_2ND_RESET_MASK = (int)0x1,
    PIPE_SYS_PCIE1_CFG_2ND_RESET_POS = 0,
    PIPE_SYS_PCIE1_CFG_MAX_PAYLOAD_SIZE_MASK = (int)0x1fffffe,
    PIPE_SYS_PCIE1_CFG_MAX_PAYLOAD_SIZE_POS = 1,
};

enum PIPE_SYS_REG_PCIE1_REG220_FIELD
{
    PIPE_SYS_PCIE1_CFG_RCB_MASK = (int)0xff,
    PIPE_SYS_PCIE1_CFG_RCB_POS = 0,
    PIPE_SYS_PCIE1_CFG_MEM_SPACE_EN_MASK = (int)0xff00,
    PIPE_SYS_PCIE1_CFG_MEM_SPACE_EN_POS = 8,
};

enum PIPE_SYS_REG_PCIE1_REG221_FIELD
{
    PIPE_SYS_PCIE1_CFG_MAX_RD_REQ_SIZE_MASK = (int)0xffffff,
    PIPE_SYS_PCIE1_CFG_MAX_RD_REQ_SIZE_POS = 0,
    PIPE_SYS_PCIE1_RDLH_LINK_UP_MASK = (int)0x1000000,
    PIPE_SYS_PCIE1_RDLH_LINK_UP_POS = 24,
    PIPE_SYS_PCIE1_SMLH_LTSSM_STATE_MASK = (int)0x7e000000,
    PIPE_SYS_PCIE1_SMLH_LTSSM_STATE_POS = 25,
};

enum PIPE_SYS_REG_PCIE1_REG222_FIELD
{
    PIPE_SYS_PCIE1_PM_CURNT_STATE_MASK = (int)0x7,
    PIPE_SYS_PCIE1_PM_CURNT_STATE_POS = 0,
    PIPE_SYS_PCIE1_SMLH_LINK_UP_MASK = (int)0x8,
    PIPE_SYS_PCIE1_SMLH_LINK_UP_POS = 3,
    PIPE_SYS_PCIE1_SMLH_REQ_RST_NOT_MASK = (int)0x10,
    PIPE_SYS_PCIE1_SMLH_REQ_RST_NOT_POS = 4,
    PIPE_SYS_PCIE1_LINK_REQ_RST_NOT_MASK = (int)0x20,
    PIPE_SYS_PCIE1_LINK_REQ_RST_NOT_POS = 5,
    PIPE_SYS_PCIE1_BRDG_SLV_XFER_PENDING_MASK = (int)0x40,
    PIPE_SYS_PCIE1_BRDG_SLV_XFER_PENDING_POS = 6,
    PIPE_SYS_PCIE1_BRDG_DBI_XFER_PENDING_MASK = (int)0x80,
    PIPE_SYS_PCIE1_BRDG_DBI_XFER_PENDING_POS = 7,
    PIPE_SYS_PCIE1_EDMA_XFER_PENDING_MASK = (int)0x100,
    PIPE_SYS_PCIE1_EDMA_XFER_PENDING_POS = 8,
    PIPE_SYS_PCIE1_RADM_XFER_PENDING_MASK = (int)0x200,
    PIPE_SYS_PCIE1_RADM_XFER_PENDING_POS = 9,
    PIPE_SYS_PCIE1_CFG_REG_SERREN_MASK = (int)0x3fc00,
    PIPE_SYS_PCIE1_CFG_REG_SERREN_POS = 10,
    PIPE_SYS_PCIE1_CFG_COR_ERR_RPT_EN_MASK = (int)0x3fc0000,
    PIPE_SYS_PCIE1_CFG_COR_ERR_RPT_EN_POS = 18,
};

enum PIPE_SYS_REG_PCIE1_REG223_FIELD
{
    PIPE_SYS_PCIE1_CFG_NF_ERR_RPT_EN_MASK = (int)0xff,
    PIPE_SYS_PCIE1_CFG_NF_ERR_RPT_EN_POS = 0,
    PIPE_SYS_PCIE1_CFG_F_ERR_RPT_EN_MASK = (int)0xff00,
    PIPE_SYS_PCIE1_CFG_F_ERR_RPT_EN_POS = 8,
    PIPE_SYS_PCIE1_DIAG_CTRL_BUS_MASK = (int)0x70000,
    PIPE_SYS_PCIE1_DIAG_CTRL_BUS_POS = 16,
};

enum PIPE_SYS_REG_PCIE1_REG224_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG225_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG226_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG227_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG228_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG229_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG230_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG231_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG232_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG233_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_9_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_9_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG234_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_10_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_10_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG235_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_11_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_11_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG236_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_12_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_12_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG237_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_13_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_13_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG238_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_14_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_14_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG239_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_15_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_15_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG240_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_16_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_16_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG241_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_17_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_17_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG242_FIELD
{
    PIPE_SYS_PCIE1_APP_RAS_DES_SD_HOLD_LTSSM_MASK = (int)0x1,
    PIPE_SYS_PCIE1_APP_RAS_DES_SD_HOLD_LTSSM_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG243_FIELD
{
    PIPE_SYS_PCIE1_CXPL_DEBUG_INFO_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CXPL_DEBUG_INFO_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG244_FIELD
{
    PIPE_SYS_PCIE1_CXPL_DEBUG_INFO_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CXPL_DEBUG_INFO_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG245_FIELD
{
    PIPE_SYS_PCIE1_CXPL_DEBUG_INFO_EI_MASK = (int)0xffff,
    PIPE_SYS_PCIE1_CXPL_DEBUG_INFO_EI_POS = 0,
    PIPE_SYS_PCIE1_TRAINING_RST_N_MASK = (int)0x10000,
    PIPE_SYS_PCIE1_TRAINING_RST_N_POS = 16,
    PIPE_SYS_PCIE1_RADM_PM_TURNOFF_MASK = (int)0x20000,
    PIPE_SYS_PCIE1_RADM_PM_TURNOFF_POS = 17,
    PIPE_SYS_PCIE1_RADM_MSG_UNLOCK_MASK = (int)0x40000,
    PIPE_SYS_PCIE1_RADM_MSG_UNLOCK_POS = 18,
    PIPE_SYS_PCIE1_OUTBAND_PWRUP_CMD_MASK = (int)0x7f80000,
    PIPE_SYS_PCIE1_OUTBAND_PWRUP_CMD_POS = 19,
};

enum PIPE_SYS_REG_PCIE1_REG246_FIELD
{
    PIPE_SYS_PCIE1_PM_DSTATE_MASK = (int)0xffffff,
    PIPE_SYS_PCIE1_PM_DSTATE_POS = 0,
    PIPE_SYS_PCIE1_AUX_PM_EN_MASK = (int)0xff000000,
    PIPE_SYS_PCIE1_AUX_PM_EN_POS = 24,
};

enum PIPE_SYS_REG_PCIE1_REG247_FIELD
{
    PIPE_SYS_PCIE1_PM_PME_EN_MASK = (int)0xff,
    PIPE_SYS_PCIE1_PM_PME_EN_POS = 0,
    PIPE_SYS_PCIE1_PM_LINKST_IN_L0S_MASK = (int)0x100,
    PIPE_SYS_PCIE1_PM_LINKST_IN_L0S_POS = 8,
    PIPE_SYS_PCIE1_PM_LINKST_IN_L1_MASK = (int)0x200,
    PIPE_SYS_PCIE1_PM_LINKST_IN_L1_POS = 9,
    PIPE_SYS_PCIE1_PM_L1_ENTRY_STARTED_MASK = (int)0x400,
    PIPE_SYS_PCIE1_PM_L1_ENTRY_STARTED_POS = 10,
    PIPE_SYS_PCIE1_PM_LINKST_IN_L2_MASK = (int)0x800,
    PIPE_SYS_PCIE1_PM_LINKST_IN_L2_POS = 11,
    PIPE_SYS_PCIE1_PM_LINKST_L2_EXIT_MASK = (int)0x1000,
    PIPE_SYS_PCIE1_PM_LINKST_L2_EXIT_POS = 12,
    PIPE_SYS_PCIE1_PM_LINKST_IN_L1SUB_MASK = (int)0x2000,
    PIPE_SYS_PCIE1_PM_LINKST_IN_L1SUB_POS = 13,
    PIPE_SYS_PCIE1_CFG_L1SUB_EN_MASK = (int)0x4000,
    PIPE_SYS_PCIE1_CFG_L1SUB_EN_POS = 14,
    PIPE_SYS_PCIE1_PM_STATUS_MASK = (int)0x7f8000,
    PIPE_SYS_PCIE1_PM_STATUS_POS = 15,
};

enum PIPE_SYS_REG_PCIE1_REG248_FIELD
{
    PIPE_SYS_PCIE1_CFG_OBFF_EN_MASK = (int)0x60,
    PIPE_SYS_PCIE1_CFG_OBFF_EN_POS = 5,
    PIPE_SYS_PCIE1_RADM_MSG_CPU_ACTIVE_MASK = (int)0x80,
    PIPE_SYS_PCIE1_RADM_MSG_CPU_ACTIVE_POS = 7,
    PIPE_SYS_PCIE1_RADM_MSG_OBFF_MASK = (int)0x100,
    PIPE_SYS_PCIE1_RADM_MSG_OBFF_POS = 8,
    PIPE_SYS_PCIE1_RADM_MSG_IDLE_MASK = (int)0x200,
    PIPE_SYS_PCIE1_RADM_MSG_IDLE_POS = 9,
    PIPE_SYS_PCIE1_RADM_VENDOR_MSG_MASK = (int)0x400,
    PIPE_SYS_PCIE1_RADM_VENDOR_MSG_POS = 10,
};

enum PIPE_SYS_REG_PCIE1_REG249_FIELD
{
    PIPE_SYS_PCIE1_RADM_MSG_PAYLOAD_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_RADM_MSG_PAYLOAD_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG250_FIELD
{
    PIPE_SYS_PCIE1_RADM_MSG_PAYLOAD_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_RADM_MSG_PAYLOAD_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG251_FIELD
{
    PIPE_SYS_PCIE1_WAKE_MASK = (int)0x1,
    PIPE_SYS_PCIE1_WAKE_POS = 0,
    PIPE_SYS_PCIE1_RADM_MSG_REQ_ID_MASK = (int)0x1fffe,
    PIPE_SYS_PCIE1_RADM_MSG_REQ_ID_POS = 1,
    PIPE_SYS_PCIE1_TRGT_CPL_TIMEOUT_MASK = (int)0x20000,
    PIPE_SYS_PCIE1_TRGT_CPL_TIMEOUT_POS = 17,
    PIPE_SYS_PCIE1_TRGT_TIMEOUT_CPL_FUNC_NUM_MASK = (int)0x1c0000,
    PIPE_SYS_PCIE1_TRGT_TIMEOUT_CPL_FUNC_NUM_POS = 18,
    PIPE_SYS_PCIE1_TRGT_TIMEOUT_CPL_TC_MASK = (int)0xe00000,
    PIPE_SYS_PCIE1_TRGT_TIMEOUT_CPL_TC_POS = 21,
    PIPE_SYS_PCIE1_TRGT_TIMEOUT_CPL_ATTR_MASK = (int)0x3000000,
    PIPE_SYS_PCIE1_TRGT_TIMEOUT_CPL_ATTR_POS = 24,
};

enum PIPE_SYS_REG_PCIE1_REG252_FIELD
{
    PIPE_SYS_PCIE1_TRGT_TIMEOUT_CPL_LEN_MASK = (int)0xfff,
    PIPE_SYS_PCIE1_TRGT_TIMEOUT_CPL_LEN_POS = 0,
    PIPE_SYS_PCIE1_TRGT_TIMEOUT_LOOKUP_ID_MASK = (int)0xff000,
    PIPE_SYS_PCIE1_TRGT_TIMEOUT_LOOKUP_ID_POS = 12,
    PIPE_SYS_PCIE1_TRGT_LOOKUP_ID_MASK = (int)0xff00000,
    PIPE_SYS_PCIE1_TRGT_LOOKUP_ID_POS = 20,
    PIPE_SYS_PCIE1_TRGT_LOOKUP_EMPTY_MASK = (int)0x10000000,
    PIPE_SYS_PCIE1_TRGT_LOOKUP_EMPTY_POS = 28,
    PIPE_SYS_PCIE1_RADM_CPL_TIMEOUT_MASK = (int)0x20000000,
    PIPE_SYS_PCIE1_RADM_CPL_TIMEOUT_POS = 29,
};

enum PIPE_SYS_REG_PCIE1_REG253_FIELD
{
    PIPE_SYS_PCIE1_RADM_TIMEOUT_FUNC_NUM_MASK = (int)0x7,
    PIPE_SYS_PCIE1_RADM_TIMEOUT_FUNC_NUM_POS = 0,
    PIPE_SYS_PCIE1_RADM_TIMEOUT_CPL_TC_MASK = (int)0x38,
    PIPE_SYS_PCIE1_RADM_TIMEOUT_CPL_TC_POS = 3,
    PIPE_SYS_PCIE1_RADM_TIMEOUT_CPL_ATTR_MASK = (int)0xc0,
    PIPE_SYS_PCIE1_RADM_TIMEOUT_CPL_ATTR_POS = 6,
    PIPE_SYS_PCIE1_RADM_TIMEOUT_CPL_LEN_MASK = (int)0xfff00,
    PIPE_SYS_PCIE1_RADM_TIMEOUT_CPL_LEN_POS = 8,
    PIPE_SYS_PCIE1_RADM_TIMEOUT_CPL_TAG_MASK = (int)0xff00000,
    PIPE_SYS_PCIE1_RADM_TIMEOUT_CPL_TAG_POS = 20,
};

enum PIPE_SYS_REG_PCIE1_REG254_FIELD
{
    PIPE_SYS_PCIE1_EDMA_INT_MASK = (int)0xffff,
    PIPE_SYS_PCIE1_EDMA_INT_POS = 0,
    PIPE_SYS_PCIE1_ASSERT_INTA_GRT_MASK = (int)0x10000,
    PIPE_SYS_PCIE1_ASSERT_INTA_GRT_POS = 16,
    PIPE_SYS_PCIE1_ASSERT_INTB_GRT_MASK = (int)0x20000,
    PIPE_SYS_PCIE1_ASSERT_INTB_GRT_POS = 17,
    PIPE_SYS_PCIE1_ASSERT_INTC_GRT_MASK = (int)0x40000,
    PIPE_SYS_PCIE1_ASSERT_INTC_GRT_POS = 18,
    PIPE_SYS_PCIE1_ASSERT_INTD_GRT_MASK = (int)0x80000,
    PIPE_SYS_PCIE1_ASSERT_INTD_GRT_POS = 19,
    PIPE_SYS_PCIE1_DEASSERT_INTA_GRT_MASK = (int)0x100000,
    PIPE_SYS_PCIE1_DEASSERT_INTA_GRT_POS = 20,
    PIPE_SYS_PCIE1_DEASSERT_INTB_GRT_MASK = (int)0x200000,
    PIPE_SYS_PCIE1_DEASSERT_INTB_GRT_POS = 21,
    PIPE_SYS_PCIE1_DEASSERT_INTC_GRT_MASK = (int)0x400000,
    PIPE_SYS_PCIE1_DEASSERT_INTC_GRT_POS = 22,
    PIPE_SYS_PCIE1_DEASSERT_INTD_GRT_MASK = (int)0x800000,
    PIPE_SYS_PCIE1_DEASSERT_INTD_GRT_POS = 23,
};

enum PIPE_SYS_REG_PCIE1_REG255_FIELD
{
    PIPE_SYS_PCIE1_CFG_INT_PIN_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_INT_PIN_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG256_FIELD
{
    PIPE_SYS_PCIE1_CFG_INT_PIN_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_INT_PIN_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG257_FIELD
{
    PIPE_SYS_PCIE1_CFG_SEND_COR_ERR_MASK = (int)0xff,
    PIPE_SYS_PCIE1_CFG_SEND_COR_ERR_POS = 0,
    PIPE_SYS_PCIE1_CFG_SEND_NF_ERR_MASK = (int)0xff00,
    PIPE_SYS_PCIE1_CFG_SEND_NF_ERR_POS = 8,
    PIPE_SYS_PCIE1_CFG_SEND_F_ERR_MASK = (int)0xff0000,
    PIPE_SYS_PCIE1_CFG_SEND_F_ERR_POS = 16,
    PIPE_SYS_PCIE1_CFG_INT_DISABLE_MASK = (int)0xff000000,
    PIPE_SYS_PCIE1_CFG_INT_DISABLE_POS = 24,
};

enum PIPE_SYS_REG_PCIE1_REG258_FIELD
{
    PIPE_SYS_PCIE1_CFG_NO_SNOOP_EN_MASK = (int)0xff,
    PIPE_SYS_PCIE1_CFG_NO_SNOOP_EN_POS = 0,
    PIPE_SYS_PCIE1_CFG_RELAX_ORDER_EN_MASK = (int)0xff00,
    PIPE_SYS_PCIE1_CFG_RELAX_ORDER_EN_POS = 8,
    PIPE_SYS_PCIE1_CFG_LINK_AUTO_BW_INT_MASK = (int)0x10000,
    PIPE_SYS_PCIE1_CFG_LINK_AUTO_BW_INT_POS = 16,
    PIPE_SYS_PCIE1_CFG_LINK_AUTO_BW_MSI_MASK = (int)0x20000,
    PIPE_SYS_PCIE1_CFG_LINK_AUTO_BW_MSI_POS = 17,
    PIPE_SYS_PCIE1_CFG_BW_MGT_INT_MASK = (int)0x40000,
    PIPE_SYS_PCIE1_CFG_BW_MGT_INT_POS = 18,
    PIPE_SYS_PCIE1_CFG_BW_MGT_MSI_MASK = (int)0x80000,
    PIPE_SYS_PCIE1_CFG_BW_MGT_MSI_POS = 19,
};

enum PIPE_SYS_REG_PCIE1_REG259_FIELD
{
    PIPE_SYS_PCIE1_MSI_CTRL_IO_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_MSI_CTRL_IO_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG260_FIELD
{
    PIPE_SYS_PCIE1_MSI_CTRL_INT_MASK = (int)0x1,
    PIPE_SYS_PCIE1_MSI_CTRL_INT_POS = 0,
    PIPE_SYS_PCIE1_MSI_CTRL_INT_VEC_MASK = (int)0x1fe,
    PIPE_SYS_PCIE1_MSI_CTRL_INT_VEC_POS = 1,
    PIPE_SYS_PCIE1_DEVICE_TYPE_MASK = (int)0x1e00,
    PIPE_SYS_PCIE1_DEVICE_TYPE_POS = 9,
    PIPE_SYS_PCIE1_RBAR_CTRL_UPDATE_MASK = (int)0x1fe000,
    PIPE_SYS_PCIE1_RBAR_CTRL_UPDATE_POS = 13,
};

enum PIPE_SYS_REG_PCIE1_REG261_FIELD
{
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG262_FIELD
{
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG263_FIELD
{
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG264_FIELD
{
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG265_FIELD
{
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG266_FIELD
{
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG267_FIELD
{
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG268_FIELD
{
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG269_FIELD
{
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_RBAR_SIZE_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG270_FIELD
{
    PIPE_SYS_PCIE1_VF_RBAR_CTRL_UPDATE_MASK = (int)0xff,
    PIPE_SYS_PCIE1_VF_RBAR_CTRL_UPDATE_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG271_FIELD
{
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG272_FIELD
{
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG273_FIELD
{
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG274_FIELD
{
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG275_FIELD
{
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG276_FIELD
{
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG277_FIELD
{
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG278_FIELD
{
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG279_FIELD
{
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_VF_RBAR_SIZE_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG280_FIELD
{
    PIPE_SYS_PCIE1_CFG_BR_CTRL_SERREN_MASK = (int)0xff,
    PIPE_SYS_PCIE1_CFG_BR_CTRL_SERREN_POS = 0,
    PIPE_SYS_PCIE1_PM_L1SUB_STATE_MASK = (int)0x700,
    PIPE_SYS_PCIE1_PM_L1SUB_STATE_POS = 8,
    PIPE_SYS_PCIE1_APP_L1SUB_DISABLE_MASK = (int)0x800,
    PIPE_SYS_PCIE1_APP_L1SUB_DISABLE_POS = 11,
    PIPE_SYS_PCIE1_PM_MASTER_STATE_MASK = (int)0x1f000,
    PIPE_SYS_PCIE1_PM_MASTER_STATE_POS = 12,
    PIPE_SYS_PCIE1_PM_SLAVE_STATE_MASK = (int)0x3e0000,
    PIPE_SYS_PCIE1_PM_SLAVE_STATE_POS = 17,
    PIPE_SYS_PCIE1_CFG_UNCOR_INTERNAL_ERR_STS_MASK = (int)0x400000,
    PIPE_SYS_PCIE1_CFG_UNCOR_INTERNAL_ERR_STS_POS = 22,
    PIPE_SYS_PCIE1_CFG_RCVR_OVERFLOW_ERR_STS_MASK = (int)0x800000,
    PIPE_SYS_PCIE1_CFG_RCVR_OVERFLOW_ERR_STS_POS = 23,
    PIPE_SYS_PCIE1_CFG_FC_PROTOCOL_ERR_STS_MASK = (int)0x1000000,
    PIPE_SYS_PCIE1_CFG_FC_PROTOCOL_ERR_STS_POS = 24,
    PIPE_SYS_PCIE1_CFG_MLF_TLP_ERR_STS_MASK = (int)0x2000000,
    PIPE_SYS_PCIE1_CFG_MLF_TLP_ERR_STS_POS = 25,
    PIPE_SYS_PCIE1_CFG_SURPRISE_DOWN_ER_STS_MASK = (int)0x4000000,
    PIPE_SYS_PCIE1_CFG_SURPRISE_DOWN_ER_STS_POS = 26,
    PIPE_SYS_PCIE1_CFG_DL_PROTOCOL_ERR_STS_MASK = (int)0x8000000,
    PIPE_SYS_PCIE1_CFG_DL_PROTOCOL_ERR_STS_POS = 27,
    PIPE_SYS_PCIE1_CFG_ECRC_ERR_STS_MASK = (int)0x10000000,
    PIPE_SYS_PCIE1_CFG_ECRC_ERR_STS_POS = 28,
    PIPE_SYS_PCIE1_CFG_CORRECTED_INTERNAL_ERR_STS_MASK = (int)0x20000000,
    PIPE_SYS_PCIE1_CFG_CORRECTED_INTERNAL_ERR_STS_POS = 29,
    PIPE_SYS_PCIE1_CFG_REPLAY_NUMBER_ROLLOVER_ERR_STS_MASK = (int)0x40000000,
    PIPE_SYS_PCIE1_CFG_REPLAY_NUMBER_ROLLOVER_ERR_STS_POS = 30,
    PIPE_SYS_PCIE1_CFG_REPLAY_TIMER_TIMEOUT_ERR_STS_MASK = (int)0x80000000,
    PIPE_SYS_PCIE1_CFG_REPLAY_TIMER_TIMEOUT_ERR_STS_POS = 31,
};

enum PIPE_SYS_REG_PCIE1_REG281_FIELD
{
    PIPE_SYS_PCIE1_CFG_BAD_DLLP_ERR_STS_MASK = (int)0x1,
    PIPE_SYS_PCIE1_CFG_BAD_DLLP_ERR_STS_POS = 0,
    PIPE_SYS_PCIE1_CFG_BAD_TLP_ERR_STS_MASK = (int)0x2,
    PIPE_SYS_PCIE1_CFG_BAD_TLP_ERR_STS_POS = 1,
    PIPE_SYS_PCIE1_CFG_RCVR_ERR_STS_MASK = (int)0x4,
    PIPE_SYS_PCIE1_CFG_RCVR_ERR_STS_POS = 2,
    PIPE_SYS_PCIE1_APP_DEV_NUM_MASK = (int)0xf8,
    PIPE_SYS_PCIE1_APP_DEV_NUM_POS = 3,
    PIPE_SYS_PCIE1_APP_BUS_NUM_MASK = (int)0xff00,
    PIPE_SYS_PCIE1_APP_BUS_NUM_POS = 8,
};

enum PIPE_SYS_REG_PCIE1_REG282_FIELD
{
    PIPE_SYS_PCIE1_RADM_TRGT1_ATU_SLOC_MATCH_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_RADM_TRGT1_ATU_SLOC_MATCH_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG283_FIELD
{
    PIPE_SYS_PCIE1_RADM_TRGT1_ATU_CBUF_ERR_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_RADM_TRGT1_ATU_CBUF_ERR_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG284_FIELD
{
    PIPE_SYS_PCIE1_CFG_PHY_CONTROL_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_PHY_CONTROL_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG285_FIELD
{
    PIPE_SYS_PCIE1_PHY_CFG_STATUS_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_PHY_CFG_STATUS_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG286_FIELD
{
    PIPE_SYS_PCIE1_PM_ASPM_L1_ENTER_READY_MASK = (int)0x1,
    PIPE_SYS_PCIE1_PM_ASPM_L1_ENTER_READY_POS = 0,
    PIPE_SYS_PCIE1_RADM_SLOT_PWR_LIMIT_MASK = (int)0x2,
    PIPE_SYS_PCIE1_RADM_SLOT_PWR_LIMIT_POS = 1,
};

enum PIPE_SYS_REG_PCIE1_REG287_FIELD
{
    PIPE_SYS_PCIE1_RADM_SLOT_PWR_PAYLOAD_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_RADM_SLOT_PWR_PAYLOAD_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG288_FIELD
{
    PIPE_SYS_PCIE1_PERST_N_REG_MASK = (int)0x1,
    PIPE_SYS_PCIE1_PERST_N_REG_POS = 0,
    PIPE_SYS_PCIE1_PERST_O_CTL_REG_MASK = (int)0x6,
    PIPE_SYS_PCIE1_PERST_O_CTL_REG_POS = 1,
    PIPE_SYS_PCIE1_PHY_RST_REG_MASK = (int)0x8,
    PIPE_SYS_PCIE1_PHY_RST_REG_POS = 3,
    PIPE_SYS_PAD_PCIE1_PERST_OE_MASK = (int)0x10,
    PIPE_SYS_PAD_PCIE1_PERST_OE_POS = 4,
    PIPE_SYS_PCIE1_PERST_CTL_REG_MASK = (int)0x60,
    PIPE_SYS_PCIE1_PERST_CTL_REG_POS = 5,
};

enum PIPE_SYS_REG_PCIE1_RAM_REG_0_FIELD
{
    PIPE_SYS_PCIE1_EDMA_RD_ENG_MSI_EMAA_MASK = (int)0x1c0000,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_MSI_EMAA_POS = 18,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_MSI_EMAB_MASK = (int)0x38000,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_MSI_EMAB_POS = 15,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_MSI_EMASA_MASK = (int)0x4000,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_MSI_EMASA_POS = 14,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_MSI_EMAA_MASK = (int)0x3800,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_MSI_EMAA_POS = 11,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_MSI_EMAB_MASK = (int)0x700,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_MSI_EMAB_POS = 8,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_MSI_EMASA_MASK = (int)0x80,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_MSI_EMASA_POS = 7,
    PIPE_SYS_PCIE1_IB_MCPL_SB_RAM_EMA_MASK = (int)0x70,
    PIPE_SYS_PCIE1_IB_MCPL_SB_RAM_EMA_POS = 4,
    PIPE_SYS_PCIE1_IB_MCPL_SB_RAM_EMAW_MASK = (int)0xc,
    PIPE_SYS_PCIE1_IB_MCPL_SB_RAM_EMAW_POS = 2,
    PIPE_SYS_PCIE1_IB_MCPL_SB_RAM_EMAS_MASK = (int)0x2,
    PIPE_SYS_PCIE1_IB_MCPL_SB_RAM_EMAS_POS = 1,
    PIPE_SYS_PCIE1_IB_MCPL_SB_RAM_EMAP_MASK = (int)0x1,
    PIPE_SYS_PCIE1_IB_MCPL_SB_RAM_EMAP_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_RAM_REG_1_FIELD
{
    PIPE_SYS_PCIE1_IB_MCPL_A2C_CDC_RAM_EMAA_MASK = (int)0x70000000,
    PIPE_SYS_PCIE1_IB_MCPL_A2C_CDC_RAM_EMAA_POS = 28,
    PIPE_SYS_PCIE1_IB_MCPL_A2C_CDC_RAM_EMAB_MASK = (int)0xe000000,
    PIPE_SYS_PCIE1_IB_MCPL_A2C_CDC_RAM_EMAB_POS = 25,
    PIPE_SYS_PCIE1_IB_MCPL_A2C_CDC_RAM_EMASA_MASK = (int)0x1000000,
    PIPE_SYS_PCIE1_IB_MCPL_A2C_CDC_RAM_EMASA_POS = 24,
    PIPE_SYS_PCIE1_IB_RREQ_C2A_CDC_RAM_EMAA_MASK = (int)0xe00000,
    PIPE_SYS_PCIE1_IB_RREQ_C2A_CDC_RAM_EMAA_POS = 21,
    PIPE_SYS_PCIE1_IB_RREQ_C2A_CDC_RAM_EMAB_MASK = (int)0x1c0000,
    PIPE_SYS_PCIE1_IB_RREQ_C2A_CDC_RAM_EMAB_POS = 18,
    PIPE_SYS_PCIE1_IB_RREQ_C2A_CDC_RAM_EMASA_MASK = (int)0x20000,
    PIPE_SYS_PCIE1_IB_RREQ_C2A_CDC_RAM_EMASA_POS = 17,
    PIPE_SYS_PCIE1_IB_WREQ_C2A_CDC_RAM_L_EMAA_MASK = (int)0x1c000,
    PIPE_SYS_PCIE1_IB_WREQ_C2A_CDC_RAM_L_EMAA_POS = 14,
    PIPE_SYS_PCIE1_IB_WREQ_C2A_CDC_RAM_L_EMAB_MASK = (int)0x3800,
    PIPE_SYS_PCIE1_IB_WREQ_C2A_CDC_RAM_L_EMAB_POS = 11,
    PIPE_SYS_PCIE1_IB_WREQ_C2A_CDC_RAM_L_EMASA_MASK = (int)0x400,
    PIPE_SYS_PCIE1_IB_WREQ_C2A_CDC_RAM_L_EMASA_POS = 10,
    PIPE_SYS_PCIE1_IB_WREQ_C2A_CDC_RAM_H_EMAA_MASK = (int)0x380,
    PIPE_SYS_PCIE1_IB_WREQ_C2A_CDC_RAM_H_EMAA_POS = 7,
    PIPE_SYS_PCIE1_IB_WREQ_C2A_CDC_RAM_H_EMAB_MASK = (int)0x70,
    PIPE_SYS_PCIE1_IB_WREQ_C2A_CDC_RAM_H_EMAB_POS = 4,
    PIPE_SYS_PCIE1_IB_WREQ_C2A_CDC_RAM_H_EMASA_MASK = (int)0x8,
    PIPE_SYS_PCIE1_IB_WREQ_C2A_CDC_RAM_H_EMASA_POS = 3,
    PIPE_SYS_PCIE1_OB_CCMP_DATA_RAM_EMAA_MASK = (int)0x7,
    PIPE_SYS_PCIE1_OB_CCMP_DATA_RAM_EMAA_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_RAM_REG_2_FIELD
{
    PIPE_SYS_PCIE1_OB_CCMP_DATA_RAM_EMAB_MASK = (int)0x38000000,
    PIPE_SYS_PCIE1_OB_CCMP_DATA_RAM_EMAB_POS = 27,
    PIPE_SYS_PCIE1_OB_CCMP_DATA_RAM_EMASA_MASK = (int)0x4000000,
    PIPE_SYS_PCIE1_OB_CCMP_DATA_RAM_EMASA_POS = 26,
    PIPE_SYS_PCIE1_SLV_NPW_SAB_RAM_EMA_MASK = (int)0x3800000,
    PIPE_SYS_PCIE1_SLV_NPW_SAB_RAM_EMA_POS = 23,
    PIPE_SYS_PCIE1_SLV_NPW_SAB_RAM_EMAW_MASK = (int)0x600000,
    PIPE_SYS_PCIE1_SLV_NPW_SAB_RAM_EMAW_POS = 21,
    PIPE_SYS_PCIE1_SLV_NPW_SAB_RAM_EMAS_MASK = (int)0x100000,
    PIPE_SYS_PCIE1_SLV_NPW_SAB_RAM_EMAS_POS = 20,
    PIPE_SYS_PCIE1_SLV_NPW_SAB_RAM_EMAP_MASK = (int)0x80000,
    PIPE_SYS_PCIE1_SLV_NPW_SAB_RAM_EMAP_POS = 19,
    PIPE_SYS_PCIE1_OB_PDCMP_DATA_RAM_EMAA_MASK = (int)0x70000,
    PIPE_SYS_PCIE1_OB_PDCMP_DATA_RAM_EMAA_POS = 16,
    PIPE_SYS_PCIE1_OB_PDCMP_DATA_RAM_EMAB_MASK = (int)0xe000,
    PIPE_SYS_PCIE1_OB_PDCMP_DATA_RAM_EMAB_POS = 13,
    PIPE_SYS_PCIE1_OB_PDCMP_DATA_RAM_EMASA_MASK = (int)0x1000,
    PIPE_SYS_PCIE1_OB_PDCMP_DATA_RAM_EMASA_POS = 12,
    PIPE_SYS_PCIE1_OB_PDCMP_HDR_RAM_EMAA_MASK = (int)0xe00,
    PIPE_SYS_PCIE1_OB_PDCMP_HDR_RAM_EMAA_POS = 9,
    PIPE_SYS_PCIE1_OB_PDCMP_HDR_RAM_EMAB_MASK = (int)0x1c0,
    PIPE_SYS_PCIE1_OB_PDCMP_HDR_RAM_EMAB_POS = 6,
    PIPE_SYS_PCIE1_OB_PDCMP_HDR_RAM_EMASA_MASK = (int)0x20,
    PIPE_SYS_PCIE1_OB_PDCMP_HDR_RAM_EMASA_POS = 5,
    PIPE_SYS_PCIE1_CDM_RAS_DES_EC_RAM_EMA_MASK = (int)0x1c,
    PIPE_SYS_PCIE1_CDM_RAS_DES_EC_RAM_EMA_POS = 2,
    PIPE_SYS_PCIE1_CDM_RAS_DES_EC_RAM_EMAW_MASK = (int)0x3,
    PIPE_SYS_PCIE1_CDM_RAS_DES_EC_RAM_EMAW_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_RAM_REG_3_FIELD
{
    PIPE_SYS_PCIE1_CDM_RAS_DES_EC_RAM_EMAS_MASK = (int)0x20000000,
    PIPE_SYS_PCIE1_CDM_RAS_DES_EC_RAM_EMAS_POS = 29,
    PIPE_SYS_PCIE1_CDM_RAS_DES_EC_RAM_EMAP_MASK = (int)0x10000000,
    PIPE_SYS_PCIE1_CDM_RAS_DES_EC_RAM_EMAP_POS = 28,
    PIPE_SYS_PCIE1_EDMARBUFF2RAM_EMA_MASK = (int)0xe000000,
    PIPE_SYS_PCIE1_EDMARBUFF2RAM_EMA_POS = 25,
    PIPE_SYS_PCIE1_EDMARBUFF2RAM_EMAW_MASK = (int)0x1800000,
    PIPE_SYS_PCIE1_EDMARBUFF2RAM_EMAW_POS = 23,
    PIPE_SYS_PCIE1_EDMARBUFF2RAM_EMAS_MASK = (int)0x400000,
    PIPE_SYS_PCIE1_EDMARBUFF2RAM_EMAS_POS = 22,
    PIPE_SYS_PCIE1_EDMARBUFF2RAM_EMAP_MASK = (int)0x200000,
    PIPE_SYS_PCIE1_EDMARBUFF2RAM_EMAP_POS = 21,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_C2W_LUT_EMAA_MASK = (int)0x1c0000,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_C2W_LUT_EMAA_POS = 18,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_C2W_LUT_EMAB_MASK = (int)0x38000,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_C2W_LUT_EMAB_POS = 15,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_C2W_LUT_EMASA_MASK = (int)0x4000,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_C2W_LUT_EMASA_POS = 14,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_OVRL_H_EMA_MASK = (int)0x3800,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_OVRL_H_EMA_POS = 11,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_OVRL_H_EMAW_MASK = (int)0x600,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_OVRL_H_EMAW_POS = 9,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_OVRL_H_EMAS_MASK = (int)0x100,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_OVRL_H_EMAS_POS = 8,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_OVRL_H_EMAP_MASK = (int)0x80,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_OVRL_H_EMAP_POS = 7,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_OVRL_L_EMA_MASK = (int)0x70,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_OVRL_L_EMA_POS = 4,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_OVRL_L_EMAW_MASK = (int)0xc,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_OVRL_L_EMAW_POS = 2,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_OVRL_L_EMAS_MASK = (int)0x2,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_OVRL_L_EMAS_POS = 1,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_OVRL_L_EMAP_MASK = (int)0x1,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_OVRL_L_EMAP_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_RAM_REG_4_FIELD
{
    PIPE_SYS_PCIE1_EDMA_RD_ENG_STSH_LUT_EMAA_MASK = (int)0x70000000,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_STSH_LUT_EMAA_POS = 28,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_STSH_LUT_EMAB_MASK = (int)0xe000000,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_STSH_LUT_EMAB_POS = 25,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_STSH_LUT_EMASA_MASK = (int)0x1000000,
    PIPE_SYS_PCIE1_EDMA_RD_ENG_STSH_LUT_EMASA_POS = 24,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_C2W_LUT_EMAA_MASK = (int)0xe00000,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_C2W_LUT_EMAA_POS = 21,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_C2W_LUT_EMAB_MASK = (int)0x1c0000,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_C2W_LUT_EMAB_POS = 18,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_C2W_LUT_EMASA_MASK = (int)0x20000,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_C2W_LUT_EMASA_POS = 17,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_OVRL_L_EMA_MASK = (int)0x1c000,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_OVRL_L_EMA_POS = 14,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_OVRL_L_EMAW_MASK = (int)0x3000,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_OVRL_L_EMAW_POS = 12,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_OVRL_L_EMAS_MASK = (int)0x800,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_OVRL_L_EMAS_POS = 11,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_OVRL_L_EMAP_MASK = (int)0x400,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_OVRL_L_EMAP_POS = 10,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_OVRL_H_EMA_MASK = (int)0x380,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_OVRL_H_EMA_POS = 7,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_OVRL_H_EMAW_MASK = (int)0x60,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_OVRL_H_EMAW_POS = 5,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_OVRL_H_EMAS_MASK = (int)0x10,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_OVRL_H_EMAS_POS = 4,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_OVRL_H_EMAP_MASK = (int)0x8,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_OVRL_H_EMAP_POS = 3,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_STSH_LUT_EMAA_MASK = (int)0x7,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_STSH_LUT_EMAA_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_RAM_REG_5_FIELD
{
    PIPE_SYS_PCIE1_EDMA_WR_ENG_STSH_LUT_EMAB_MASK = (int)0x70000000,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_STSH_LUT_EMAB_POS = 28,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_STSH_LUT_EMASA_MASK = (int)0x8000000,
    PIPE_SYS_PCIE1_EDMA_WR_ENG_STSH_LUT_EMASA_POS = 27,
    PIPE_SYS_PCIE1_P_DATAQ_EMA_MASK = (int)0x7000000,
    PIPE_SYS_PCIE1_P_DATAQ_EMA_POS = 24,
    PIPE_SYS_PCIE1_P_DATAQ_EMAW_MASK = (int)0xc00000,
    PIPE_SYS_PCIE1_P_DATAQ_EMAW_POS = 22,
    PIPE_SYS_PCIE1_P_DATAQ_EMAS_MASK = (int)0x200000,
    PIPE_SYS_PCIE1_P_DATAQ_EMAS_POS = 21,
    PIPE_SYS_PCIE1_P_DATAQ_EMAP_MASK = (int)0x100000,
    PIPE_SYS_PCIE1_P_DATAQ_EMAP_POS = 20,
    PIPE_SYS_PCIE1_P_HDRQ_EMA_MASK = (int)0xe0000,
    PIPE_SYS_PCIE1_P_HDRQ_EMA_POS = 17,
    PIPE_SYS_PCIE1_P_HDRQ_EMAW_MASK = (int)0x18000,
    PIPE_SYS_PCIE1_P_HDRQ_EMAW_POS = 15,
    PIPE_SYS_PCIE1_P_HDRQ_EMAS_MASK = (int)0x4000,
    PIPE_SYS_PCIE1_P_HDRQ_EMAS_POS = 14,
    PIPE_SYS_PCIE1_P_HDRQ_EMAP_MASK = (int)0x2000,
    PIPE_SYS_PCIE1_P_HDRQ_EMAP_POS = 13,
    PIPE_SYS_PCIE1_XDLH_RETRYRAM_EMA_MASK = (int)0x1c00,
    PIPE_SYS_PCIE1_XDLH_RETRYRAM_EMA_POS = 10,
    PIPE_SYS_PCIE1_XDLH_RETRYRAM_EMAW_MASK = (int)0x300,
    PIPE_SYS_PCIE1_XDLH_RETRYRAM_EMAW_POS = 8,
    PIPE_SYS_PCIE1_XDLH_RETRYRAM_EMAS_MASK = (int)0x80,
    PIPE_SYS_PCIE1_XDLH_RETRYRAM_EMAS_POS = 7,
    PIPE_SYS_PCIE1_OB_NPDCMP_RAM_EMAA_MASK = (int)0x70,
    PIPE_SYS_PCIE1_OB_NPDCMP_RAM_EMAA_POS = 4,
    PIPE_SYS_PCIE1_OB_NPDCMP_RAM_EMAB_MASK = (int)0xe,
    PIPE_SYS_PCIE1_OB_NPDCMP_RAM_EMAB_POS = 1,
    PIPE_SYS_PCIE1_OB_NPDCMP_RAM_EMASA_MASK = (int)0x1,
    PIPE_SYS_PCIE1_OB_NPDCMP_RAM_EMASA_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_AXI_SLV_REG0_FIELD
{
    PIPE_SYS_MATRIX15_PCIE1_S_AWMISC_INFO_HDR_34DW_1_MASK = (int)0xffffffff,
    PIPE_SYS_MATRIX15_PCIE1_S_AWMISC_INFO_HDR_34DW_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_AXI_SLV_REG1_FIELD
{
    PIPE_SYS_MATRIX15_PCIE1_S_AWMISC_INFO_HDR_34DW_0_MASK = (int)0xffffffff,
    PIPE_SYS_MATRIX15_PCIE1_S_AWMISC_INFO_HDR_34DW_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_AXI_SLV_REG2_FIELD
{
    PIPE_SYS_MATRIX15_PCIE1_S_AWMISC_INFO_P_TAG_MASK = (int)0x1fe00,
    PIPE_SYS_MATRIX15_PCIE1_S_AWMISC_INFO_P_TAG_POS = 9,
    PIPE_SYS_MATRIX15_PCIE1_S_ARMISC_INFO_ATU_BYPASS_MASK = (int)0x100,
    PIPE_SYS_MATRIX15_PCIE1_S_ARMISC_INFO_ATU_BYPASS_POS = 8,
    PIPE_SYS_MATRIX15_PCIE1_S_WMISC_INFO_SILENTDROP_MASK = (int)0x80,
    PIPE_SYS_MATRIX15_PCIE1_S_WMISC_INFO_SILENTDROP_POS = 7,
    PIPE_SYS_MATRIX15_PCIE1_S_WMISC_INFO_EP_MASK = (int)0x40,
    PIPE_SYS_MATRIX15_PCIE1_S_WMISC_INFO_EP_POS = 6,
    PIPE_SYS_MATRIX15_PCIE1_S_CSYSREQ_MASK = (int)0x20,
    PIPE_SYS_MATRIX15_PCIE1_S_CSYSREQ_POS = 5,
    PIPE_SYS_MATRIX15_PCIE1_S_AWMISC_INFO_ATU_BYPASS_MASK = (int)0x10,
    PIPE_SYS_MATRIX15_PCIE1_S_AWMISC_INFO_ATU_BYPASS_POS = 4,
    PIPE_SYS_MATRIX15_PCIE1_S_AWQOS_MASK = (int)0xf,
    PIPE_SYS_MATRIX15_PCIE1_S_AWQOS_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_AXI_SLV_REG3_FIELD
{
    PIPE_SYS_MATRIX15_PCIE1_S_ARMISC_INFO_MASK = (int)0x1ffffff0,
    PIPE_SYS_MATRIX15_PCIE1_S_ARMISC_INFO_POS = 4,
    PIPE_SYS_MATRIX15_PCIE1_S_ARQOS_MASK = (int)0xf,
    PIPE_SYS_MATRIX15_PCIE1_S_ARQOS_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_AXI_SLV_REG4_FIELD
{
    PIPE_SYS_MATRIX15_PCIE1_S_AWMISC_INFO_MASK = (int)0x1ffffff,
    PIPE_SYS_MATRIX15_PCIE1_S_AWMISC_INFO_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_AXI_SLV_REG5_FIELD
{
    PIPE_SYS_PCIE1_MATRIX15_S_CACTIVE_MASK = (int)0x20000000,
    PIPE_SYS_PCIE1_MATRIX15_S_CACTIVE_POS = 29,
    PIPE_SYS_PCIE1_MATRIX15_S_CSYSACK_MASK = (int)0x10000000,
    PIPE_SYS_PCIE1_MATRIX15_S_CSYSACK_POS = 28,
    PIPE_SYS_PCIE1_MATRIX15_S_RMISC_INFO_MASK = (int)0xfffc000,
    PIPE_SYS_PCIE1_MATRIX15_S_RMISC_INFO_POS = 14,
    PIPE_SYS_PCIE1_MATRIX15_S_BMISC_INFO_MASK = (int)0x3fff,
    PIPE_SYS_PCIE1_MATRIX15_S_BMISC_INFO_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_AXI_MST_REG0_FIELD
{
    PIPE_SYS_PCIE1_MATRIX12_M_AWMISC_INFO_HDR_34DW_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_MATRIX12_M_AWMISC_INFO_HDR_34DW_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_AXI_MST_REG1_FIELD
{
    PIPE_SYS_PCIE1_MATRIX12_M_AWMISC_INFO_HDR_34DW_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_MATRIX12_M_AWMISC_INFO_HDR_34DW_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_AXI_MST_REG2_FIELD
{
    PIPE_SYS_PCIE1_MATRIX12_M_ARMISC_INFO_1_MASK = (int)0xffff,
    PIPE_SYS_PCIE1_MATRIX12_M_ARMISC_INFO_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_AXI_MST_REG3_FIELD
{
    PIPE_SYS_PCIE1_MATRIX12_M_ARMISC_INFO_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_MATRIX12_M_ARMISC_INFO_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_AXI_MST_REG4_FIELD
{
    PIPE_SYS_PCIE1_MATRIX12_M_AWMISC_INFO_1_MASK = (int)0xffff,
    PIPE_SYS_PCIE1_MATRIX12_M_AWMISC_INFO_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_AXI_MST_REG5_FIELD
{
    PIPE_SYS_PCIE1_MATRIX12_M_AWMISC_INFO_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_MATRIX12_M_AWMISC_INFO_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_AXI_MST_REG6_FIELD
{
    PIPE_SYS_PCIE1_MATRIX12_M_ARMISC_INFO_DMA_MASK = (int)0xfc0000,
    PIPE_SYS_PCIE1_MATRIX12_M_ARMISC_INFO_DMA_POS = 18,
    PIPE_SYS_PCIE1_MATRIX12_M_AWMISC_INFO_DMA_MASK = (int)0x3f000,
    PIPE_SYS_PCIE1_MATRIX12_M_AWMISC_INFO_DMA_POS = 12,
    PIPE_SYS_PCIE1_MATRIX12_M_ARMISC_INFO_LAST_DCMP_TLP_MASK = (int)0x800,
    PIPE_SYS_PCIE1_MATRIX12_M_ARMISC_INFO_LAST_DCMP_TLP_POS = 11,
    PIPE_SYS_PCIE1_MATRIX12_M_CACTIVE_MASK = (int)0x400,
    PIPE_SYS_PCIE1_MATRIX12_M_CACTIVE_POS = 10,
    PIPE_SYS_PCIE1_MATRIX12_M_ARMISC_INFO_ZEROREAD_MASK = (int)0x200,
    PIPE_SYS_PCIE1_MATRIX12_M_ARMISC_INFO_ZEROREAD_POS = 9,
    PIPE_SYS_PCIE1_MATRIX12_M_ARQOS_MASK = (int)0x1e0,
    PIPE_SYS_PCIE1_MATRIX12_M_ARQOS_POS = 5,
    PIPE_SYS_PCIE1_MATRIX12_M_AWMISC_INFO_LAST_DCMP_TLP_MASK = (int)0x10,
    PIPE_SYS_PCIE1_MATRIX12_M_AWMISC_INFO_LAST_DCMP_TLP_POS = 4,
    PIPE_SYS_PCIE1_MATRIX12_M_AWQOS_MASK = (int)0xf,
    PIPE_SYS_PCIE1_MATRIX12_M_AWQOS_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_AXI_MST_REG7_FIELD
{
    PIPE_SYS_PCIE1_MATRIX12_M_AWMISC_INFO_EP_MASK = (int)0x80000000,
    PIPE_SYS_PCIE1_MATRIX12_M_AWMISC_INFO_EP_POS = 31,
    PIPE_SYS_PCIE1_MATRIX12_M_CSYSACK_MASK = (int)0x100000,
    PIPE_SYS_PCIE1_MATRIX12_M_CSYSACK_POS = 20,
    PIPE_SYS_MATRIX12_PCIE1_M_RMISC_INFO_MASK = (int)0xfff80,
    PIPE_SYS_MATRIX12_PCIE1_M_RMISC_INFO_POS = 7,
    PIPE_SYS_MATRIX12_PCIE1_M_CSYSREQ_MASK = (int)0x40,
    PIPE_SYS_MATRIX12_PCIE1_M_CSYSREQ_POS = 6,
    PIPE_SYS_MATRIX12_PCIE1_M_BMISC_INFO_CPL_STAT_MASK = (int)0x38,
    PIPE_SYS_MATRIX12_PCIE1_M_BMISC_INFO_CPL_STAT_POS = 3,
    PIPE_SYS_MATRIX12_PCIE1_M_RMISC_INFO_CPL_STAT_MASK = (int)0x7,
    PIPE_SYS_MATRIX12_PCIE1_M_RMISC_INFO_CPL_STAT_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_DBI_SLV_REG0_FIELD
{
    PIPE_SYS_MATRIX15_PCIE1_DBI_S_CSYSREQ_MASK = (int)0x400,
    PIPE_SYS_MATRIX15_PCIE1_DBI_S_CSYSREQ_POS = 10,
    PIPE_SYS_MATRIX15_PCIE1_DBI_S_ARQOS_MASK = (int)0x3c0,
    PIPE_SYS_MATRIX15_PCIE1_DBI_S_ARQOS_POS = 6,
    PIPE_SYS_MATRIX15_PCIE1_DBI_S_AWQOS_MASK = (int)0x3c,
    PIPE_SYS_MATRIX15_PCIE1_DBI_S_AWQOS_POS = 2,
    PIPE_SYS_PCIE1_DBI_MATRIX15_S_CACTIVE_MASK = (int)0x2,
    PIPE_SYS_PCIE1_DBI_MATRIX15_S_CACTIVE_POS = 1,
    PIPE_SYS_PCIE1_DBI_MATRIX15_S_CSYSACK_MASK = (int)0x1,
    PIPE_SYS_PCIE1_DBI_MATRIX15_S_CSYSACK_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_VEN_MSG_START_T_FIELD
{
    PIPE_SYS_PCIE1_VEN_MSG_START_T_MASK = (int)0x1,
    PIPE_SYS_PCIE1_VEN_MSG_START_T_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_VEN_MSI_START_T_FIELD
{
    PIPE_SYS_PCIE1_VEN_MSI_START_T_MASK = (int)0x1,
    PIPE_SYS_PCIE1_VEN_MSI_START_T_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_APP_LTR_MSG_START_T_FIELD
{
    PIPE_SYS_PCIE1_APP_LTR_MSG_START_T_MASK = (int)0x1,
    PIPE_SYS_PCIE1_APP_LTR_MSG_START_T_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_APP_OBFF_IDLE_MSG_START_T_FIELD
{
    PIPE_SYS_PCIE1_APP_OBFF_IDLE_MSG_START_T_MASK = (int)0x1,
    PIPE_SYS_PCIE1_APP_OBFF_IDLE_MSG_START_T_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_APP_OBFF_OBFF_MSG_START_T_FIELD
{
    PIPE_SYS_PCIE1_APP_OBFF_OBFF_MSG_START_T_MASK = (int)0x1,
    PIPE_SYS_PCIE1_APP_OBFF_OBFF_MSG_START_T_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_APP_OBFF_CPU_ACTIVE_MSG_START_T_FIELD
{
    PIPE_SYS_PCIE1_APP_OBFF_CPU_ACTIVE_MSG_START_T_MASK = (int)0x1,
    PIPE_SYS_PCIE1_APP_OBFF_CPU_ACTIVE_MSG_START_T_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_VEN_MSG_REQ_TIMEOUT_CNT_FIELD
{
    PIPE_SYS_PCIE1_VEN_MSG_REQ_TIMEOUT_CNT_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_VEN_MSG_REQ_TIMEOUT_CNT_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_DUMMY0_FIELD
{
    PIPE_SYS_PCIE0_DUMMY0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DUMMY0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_RD_DUMMY0_FIELD
{
    PIPE_SYS_PCIE0_RD_DUMMY0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_RD_DUMMY0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG0_FIELD
{
    PIPE_SYS_PCIE0_SURPRISE_DOWN_ERR_MASK = (int)0xff,
    PIPE_SYS_PCIE0_SURPRISE_DOWN_ERR_POS = 0,
    PIPE_SYS_PCIE0_POWER_UP_RST_N_MASK = (int)0x100,
    PIPE_SYS_PCIE0_POWER_UP_RST_N_POS = 8,
    PIPE_SYS_PCIE0_BUTTON_RST_N_MASK = (int)0x200,
    PIPE_SYS_PCIE0_BUTTON_RST_N_POS = 9,
    PIPE_SYS_PCIE0_SYS_AUX_PWR_DET_MASK = (int)0x400,
    PIPE_SYS_PCIE0_SYS_AUX_PWR_DET_POS = 10,
    PIPE_SYS_PCIE0_APP_LTSSM_ENABLE_MASK = (int)0x800,
    PIPE_SYS_PCIE0_APP_LTSSM_ENABLE_POS = 11,
    PIPE_SYS_PCIE0_APP_HOLD_PHY_RST_MASK = (int)0x1000,
    PIPE_SYS_PCIE0_APP_HOLD_PHY_RST_POS = 12,
    PIPE_SYS_PCIE0_APP_CLK_REQ_N_MASK = (int)0x2000,
    PIPE_SYS_PCIE0_APP_CLK_REQ_N_POS = 13,
    PIPE_SYS_PCIE0_APP_CLK_PM_EN_MASK = (int)0x4000,
    PIPE_SYS_PCIE0_APP_CLK_PM_EN_POS = 14,
    PIPE_SYS_PCIE0_APP_INIT_RST_MASK = (int)0x8000,
    PIPE_SYS_PCIE0_APP_INIT_RST_POS = 15,
    PIPE_SYS_PCIE0_APP_REQ_ENTR_L1_MASK = (int)0x10000,
    PIPE_SYS_PCIE0_APP_REQ_ENTR_L1_POS = 16,
    PIPE_SYS_PCIE0_APP_READY_ENTR_L23_MASK = (int)0x20000,
    PIPE_SYS_PCIE0_APP_READY_ENTR_L23_POS = 17,
    PIPE_SYS_PCIE0_APP_REQ_EXIT_L1_MASK = (int)0x40000,
    PIPE_SYS_PCIE0_APP_REQ_EXIT_L1_POS = 18,
    PIPE_SYS_PCIE0_APP_XFER_PENDING_MASK = (int)0x80000,
    PIPE_SYS_PCIE0_APP_XFER_PENDING_POS = 19,
    PIPE_SYS_PCIE0_EXP_ROM_VALIDATION_STATUS_STROBE_MASK = (int)0xff00000,
    PIPE_SYS_PCIE0_EXP_ROM_VALIDATION_STATUS_STROBE_POS = 20,
};

enum PIPE_SYS_REG_PCIE0_REG1_FIELD
{
    PIPE_SYS_PCIE0_EXP_ROM_VALIDATION_STATUS_MASK = (int)0xffffff,
    PIPE_SYS_PCIE0_EXP_ROM_VALIDATION_STATUS_POS = 0,
    PIPE_SYS_PCIE0_EXP_ROM_VALIDATION_DETAILS_STROBE_MASK = (int)0xff000000,
    PIPE_SYS_PCIE0_EXP_ROM_VALIDATION_DETAILS_STROBE_POS = 24,
};

enum PIPE_SYS_REG_PCIE0_REG2_FIELD
{
    PIPE_SYS_PCIE0_EXP_ROM_VALIDATION_DETAILS_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_EXP_ROM_VALIDATION_DETAILS_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG3_FIELD
{
    PIPE_SYS_PCIE0_APP_REQ_RETRY_EN_MASK = (int)0x1,
    PIPE_SYS_PCIE0_APP_REQ_RETRY_EN_POS = 0,
    PIPE_SYS_PCIE0_APP_PF_REQ_RETRY_EN_MASK = (int)0x1fe,
    PIPE_SYS_PCIE0_APP_PF_REQ_RETRY_EN_POS = 1,
    PIPE_SYS_PCIE0_CFG_HP_SLOT_CTRL_ACCESS_MASK = (int)0x1fe00,
    PIPE_SYS_PCIE0_CFG_HP_SLOT_CTRL_ACCESS_POS = 9,
    PIPE_SYS_PCIE0_CFG_DLL_STATE_CHGED_EN_MASK = (int)0x1fe0000,
    PIPE_SYS_PCIE0_CFG_DLL_STATE_CHGED_EN_POS = 17,
};

enum PIPE_SYS_REG_PCIE0_REG4_FIELD
{
    PIPE_SYS_PCIE0_CFG_CMD_CPLED_INT_EN_MASK = (int)0xff,
    PIPE_SYS_PCIE0_CFG_CMD_CPLED_INT_EN_POS = 0,
    PIPE_SYS_PCIE0_CFG_HP_INT_EN_MASK = (int)0xff00,
    PIPE_SYS_PCIE0_CFG_HP_INT_EN_POS = 8,
    PIPE_SYS_PCIE0_CFG_PRE_DET_CHGED_EN_MASK = (int)0xff0000,
    PIPE_SYS_PCIE0_CFG_PRE_DET_CHGED_EN_POS = 16,
    PIPE_SYS_PCIE0_CFG_MRL_SENSOR_CHGED_EN_MASK = (int)0xff000000,
    PIPE_SYS_PCIE0_CFG_MRL_SENSOR_CHGED_EN_POS = 24,
};

enum PIPE_SYS_REG_PCIE0_REG5_FIELD
{
    PIPE_SYS_PCIE0_CFG_PWR_FAULT_DET_EN_MASK = (int)0xff,
    PIPE_SYS_PCIE0_CFG_PWR_FAULT_DET_EN_POS = 0,
    PIPE_SYS_PCIE0_CFG_ATTEN_BUTTON_PRESSED_EN_MASK = (int)0xff00,
    PIPE_SYS_PCIE0_CFG_ATTEN_BUTTON_PRESSED_EN_POS = 8,
    PIPE_SYS_PCIE0_LOCAL_REF_CLK_REQ_N_MASK = (int)0x10000,
    PIPE_SYS_PCIE0_LOCAL_REF_CLK_REQ_N_POS = 16,
    PIPE_SYS_PCIE0_CLKREQ_IN_N_MASK = (int)0x20000,
    PIPE_SYS_PCIE0_CLKREQ_IN_N_POS = 17,
    PIPE_SYS_PCIE0_CFG_HW_AUTO_SP_DIS_MASK = (int)0x40000,
    PIPE_SYS_PCIE0_CFG_HW_AUTO_SP_DIS_POS = 18,
    PIPE_SYS_PCIE0_RADM_TRGT1_VC_MASK = (int)0x380000,
    PIPE_SYS_PCIE0_RADM_TRGT1_VC_POS = 19,
    PIPE_SYS_PCIE0_APP_DBI_RO_WR_DISABLE_MASK = (int)0x400000,
    PIPE_SYS_PCIE0_APP_DBI_RO_WR_DISABLE_POS = 22,
    PIPE_SYS_PCIE0_VEN_MSI_FUNC_NUM_MASK = (int)0x3800000,
    PIPE_SYS_PCIE0_VEN_MSI_FUNC_NUM_POS = 23,
    PIPE_SYS_PCIE0_VEN_MSI_TC_MASK = (int)0x1c000000,
    PIPE_SYS_PCIE0_VEN_MSI_TC_POS = 26,
};

enum PIPE_SYS_REG_PCIE0_REG6_FIELD
{
    PIPE_SYS_PCIE0_VEN_MSI_VECTOR_MASK = (int)0x1f,
    PIPE_SYS_PCIE0_VEN_MSI_VECTOR_POS = 0,
    PIPE_SYS_PCIE0_CFG_MSI_EN_MASK = (int)0x1fe0,
    PIPE_SYS_PCIE0_CFG_MSI_EN_POS = 5,
};

enum PIPE_SYS_REG_PCIE0_REG7_FIELD
{
    PIPE_SYS_PCIE0_CFG_MSI_MASK_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_MSI_MASK_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG8_FIELD
{
    PIPE_SYS_PCIE0_CFG_MSI_MASK_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_MSI_MASK_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG9_FIELD
{
    PIPE_SYS_PCIE0_CFG_MSI_MASK_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_MSI_MASK_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG10_FIELD
{
    PIPE_SYS_PCIE0_CFG_MSI_MASK_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_MSI_MASK_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG11_FIELD
{
    PIPE_SYS_PCIE0_CFG_MSI_MASK_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_MSI_MASK_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG12_FIELD
{
    PIPE_SYS_PCIE0_CFG_MSI_MASK_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_MSI_MASK_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG13_FIELD
{
    PIPE_SYS_PCIE0_CFG_MSI_MASK_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_MSI_MASK_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG14_FIELD
{
    PIPE_SYS_PCIE0_CFG_MSI_MASK_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_MSI_MASK_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG15_FIELD
{
    PIPE_SYS_PCIE0_CFG_MSI_PENDING_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_MSI_PENDING_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG16_FIELD
{
    PIPE_SYS_PCIE0_CFG_MSI_PENDING_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_MSI_PENDING_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG17_FIELD
{
    PIPE_SYS_PCIE0_CFG_MSI_PENDING_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_MSI_PENDING_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG18_FIELD
{
    PIPE_SYS_PCIE0_CFG_MSI_PENDING_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_MSI_PENDING_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG19_FIELD
{
    PIPE_SYS_PCIE0_CFG_MSI_PENDING_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_MSI_PENDING_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG20_FIELD
{
    PIPE_SYS_PCIE0_CFG_MSI_PENDING_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_MSI_PENDING_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG21_FIELD
{
    PIPE_SYS_PCIE0_CFG_MSI_PENDING_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_MSI_PENDING_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG22_FIELD
{
    PIPE_SYS_PCIE0_CFG_MSI_PENDING_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_MSI_PENDING_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG23_FIELD
{
    PIPE_SYS_PCIE0_CFG_LTR_M_EN_MASK = (int)0x1,
    PIPE_SYS_PCIE0_CFG_LTR_M_EN_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG24_FIELD
{
    PIPE_SYS_PCIE0_APP_LTR_MSG_LATENCY_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_APP_LTR_MSG_LATENCY_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG25_FIELD
{
    PIPE_SYS_PCIE0_APP_LTR_MSG_FUNC_NUM_MASK = (int)0x7,
    PIPE_SYS_PCIE0_APP_LTR_MSG_FUNC_NUM_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG26_FIELD
{
    PIPE_SYS_PCIE0_CFG_LTR_MAX_LATENCY_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_LTR_MAX_LATENCY_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG27_FIELD
{
    PIPE_SYS_PCIE0_CFG_LTR_MAX_LATENCY_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_LTR_MAX_LATENCY_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG28_FIELD
{
    PIPE_SYS_PCIE0_CFG_LTR_MAX_LATENCY_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_LTR_MAX_LATENCY_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG29_FIELD
{
    PIPE_SYS_PCIE0_CFG_LTR_MAX_LATENCY_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_LTR_MAX_LATENCY_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG30_FIELD
{
    PIPE_SYS_PCIE0_CFG_LTR_MAX_LATENCY_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_LTR_MAX_LATENCY_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG31_FIELD
{
    PIPE_SYS_PCIE0_CFG_LTR_MAX_LATENCY_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_LTR_MAX_LATENCY_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG32_FIELD
{
    PIPE_SYS_PCIE0_CFG_LTR_MAX_LATENCY_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_LTR_MAX_LATENCY_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG33_FIELD
{
    PIPE_SYS_PCIE0_CFG_LTR_MAX_LATENCY_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_LTR_MAX_LATENCY_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG34_FIELD
{
    PIPE_SYS_PCIE0_CFG_DISABLE_LTR_CLR_MSG_MASK = (int)0x1,
    PIPE_SYS_PCIE0_CFG_DISABLE_LTR_CLR_MSG_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG35_FIELD
{
    PIPE_SYS_PCIE0_APP_LTR_LATENCY_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_APP_LTR_LATENCY_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG36_FIELD
{
    PIPE_SYS_PCIE0_RADM_MSG_LTR_MASK = (int)0x1,
    PIPE_SYS_PCIE0_RADM_MSG_LTR_POS = 0,
    PIPE_SYS_PCIE0_VEN_MSG_FMT_MASK = (int)0x6,
    PIPE_SYS_PCIE0_VEN_MSG_FMT_POS = 1,
    PIPE_SYS_PCIE0_VEN_MSG_TYPE_MASK = (int)0xf8,
    PIPE_SYS_PCIE0_VEN_MSG_TYPE_POS = 3,
    PIPE_SYS_PCIE0_VEN_MSG_TC_MASK = (int)0x700,
    PIPE_SYS_PCIE0_VEN_MSG_TC_POS = 8,
    PIPE_SYS_PCIE0_VEN_MSG_TD_MASK = (int)0x800,
    PIPE_SYS_PCIE0_VEN_MSG_TD_POS = 11,
    PIPE_SYS_PCIE0_VEN_MSG_EP_MASK = (int)0x1000,
    PIPE_SYS_PCIE0_VEN_MSG_EP_POS = 12,
    PIPE_SYS_PCIE0_VEN_MSG_ATTR_MASK = (int)0x6000,
    PIPE_SYS_PCIE0_VEN_MSG_ATTR_POS = 13,
    PIPE_SYS_PCIE0_VEN_MSG_LEN_MASK = (int)0x1ff8000,
    PIPE_SYS_PCIE0_VEN_MSG_LEN_POS = 15,
    PIPE_SYS_PCIE0_VEN_MSG_FUNC_NUM_MASK = (int)0xe000000,
    PIPE_SYS_PCIE0_VEN_MSG_FUNC_NUM_POS = 25,
};

enum PIPE_SYS_REG_PCIE0_REG37_FIELD
{
    PIPE_SYS_PCIE0_VEN_MSG_TAG_MASK = (int)0xff,
    PIPE_SYS_PCIE0_VEN_MSG_TAG_POS = 0,
    PIPE_SYS_PCIE0_VEN_MSG_CODE_MASK = (int)0xff00,
    PIPE_SYS_PCIE0_VEN_MSG_CODE_POS = 8,
};

enum PIPE_SYS_REG_PCIE0_REG38_FIELD
{
    PIPE_SYS_PCIE0_VEN_MSG_DATA_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_VEN_MSG_DATA_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG39_FIELD
{
    PIPE_SYS_PCIE0_VEN_MSG_DATA_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_VEN_MSG_DATA_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG40_FIELD
{
    PIPE_SYS_PCIE0_SYS_INT_MASK = (int)0xff,
    PIPE_SYS_PCIE0_SYS_INT_POS = 0,
    PIPE_SYS_PCIE0_APPS_PM_XMT_PME_MASK = (int)0xff00,
    PIPE_SYS_PCIE0_APPS_PM_XMT_PME_POS = 8,
    PIPE_SYS_PCIE0_SYS_ATTEN_BUTTON_PRESSED_MASK = (int)0xff0000,
    PIPE_SYS_PCIE0_SYS_ATTEN_BUTTON_PRESSED_POS = 16,
    PIPE_SYS_PCIE0_SYS_PRE_DET_STATE_MASK = (int)0xff000000,
    PIPE_SYS_PCIE0_SYS_PRE_DET_STATE_POS = 24,
};

enum PIPE_SYS_REG_PCIE0_REG41_FIELD
{
    PIPE_SYS_PCIE0_SYS_MRL_SENSOR_STATE_MASK = (int)0xff,
    PIPE_SYS_PCIE0_SYS_MRL_SENSOR_STATE_POS = 0,
    PIPE_SYS_PCIE0_SYS_PWR_FAULT_DET_MASK = (int)0xff00,
    PIPE_SYS_PCIE0_SYS_PWR_FAULT_DET_POS = 8,
    PIPE_SYS_PCIE0_SYS_MRL_SENSOR_CHGED_MASK = (int)0xff0000,
    PIPE_SYS_PCIE0_SYS_MRL_SENSOR_CHGED_POS = 16,
    PIPE_SYS_PCIE0_SYS_PRE_DET_CHGED_MASK = (int)0xff000000,
    PIPE_SYS_PCIE0_SYS_PRE_DET_CHGED_POS = 24,
};

enum PIPE_SYS_REG_PCIE0_REG42_FIELD
{
    PIPE_SYS_PCIE0_SYS_CMD_CPLED_INT_MASK = (int)0xff,
    PIPE_SYS_PCIE0_SYS_CMD_CPLED_INT_POS = 0,
    PIPE_SYS_PCIE0_SYS_EML_INTERLOCK_ENGAGED_MASK = (int)0xff00,
    PIPE_SYS_PCIE0_SYS_EML_INTERLOCK_ENGAGED_POS = 8,
    PIPE_SYS_PCIE0_APP_UNLOCK_MSG_MASK = (int)0x10000,
    PIPE_SYS_PCIE0_APP_UNLOCK_MSG_POS = 16,
    PIPE_SYS_PCIE0_APPS_PM_XMT_TURNOFF_MASK = (int)0x20000,
    PIPE_SYS_PCIE0_APPS_PM_XMT_TURNOFF_POS = 17,
};

enum PIPE_SYS_REG_PCIE0_REG43_FIELD
{
    PIPE_SYS_PCIE0_CFG_PWR_IND_MASK = (int)0xffff,
    PIPE_SYS_PCIE0_CFG_PWR_IND_POS = 0,
    PIPE_SYS_PCIE0_CFG_ATTEN_IND_MASK = (int)0xffff0000,
    PIPE_SYS_PCIE0_CFG_ATTEN_IND_POS = 16,
};

enum PIPE_SYS_REG_PCIE0_REG44_FIELD
{
    PIPE_SYS_PCIE0_CFG_PWR_CTRLER_CTRL_MASK = (int)0xff,
    PIPE_SYS_PCIE0_CFG_PWR_CTRLER_CTRL_POS = 0,
    PIPE_SYS_PCIE0_CFG_SYS_ERR_RC_MASK = (int)0xff00,
    PIPE_SYS_PCIE0_CFG_SYS_ERR_RC_POS = 8,
    PIPE_SYS_PCIE0_CFG_AER_RC_ERR_INT_MASK = (int)0xff0000,
    PIPE_SYS_PCIE0_CFG_AER_RC_ERR_INT_POS = 16,
    PIPE_SYS_PCIE0_CFG_AER_RC_ERR_MSI_MASK = (int)0xff000000,
    PIPE_SYS_PCIE0_CFG_AER_RC_ERR_MSI_POS = 24,
};

enum PIPE_SYS_REG_PCIE0_REG45_FIELD
{
    PIPE_SYS_PCIE0_CFG_AER_INT_MSG_NUM_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_AER_INT_MSG_NUM_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG46_FIELD
{
    PIPE_SYS_PCIE0_CFG_AER_INT_MSG_NUM_1_MASK = (int)0xff,
    PIPE_SYS_PCIE0_CFG_AER_INT_MSG_NUM_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG47_FIELD
{
    PIPE_SYS_PCIE0_CFG_PME_INT_MASK = (int)0xff,
    PIPE_SYS_PCIE0_CFG_PME_INT_POS = 0,
    PIPE_SYS_PCIE0_CFG_PME_MSI_MASK = (int)0xff00,
    PIPE_SYS_PCIE0_CFG_PME_MSI_POS = 8,
    PIPE_SYS_PCIE0_CFG_CRS_SW_VIS_EN_MASK = (int)0xff0000,
    PIPE_SYS_PCIE0_CFG_CRS_SW_VIS_EN_POS = 16,
};

enum PIPE_SYS_REG_PCIE0_REG48_FIELD
{
    PIPE_SYS_PCIE0_CFG_PCIE_CAP_INT_MSG_NUM_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_PCIE_CAP_INT_MSG_NUM_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG49_FIELD
{
    PIPE_SYS_PCIE0_CFG_PCIE_CAP_INT_MSG_NUM_1_MASK = (int)0xff,
    PIPE_SYS_PCIE0_CFG_PCIE_CAP_INT_MSG_NUM_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG50_FIELD
{
    PIPE_SYS_PCIE0_CFG_EML_CONTROL_MASK = (int)0xff,
    PIPE_SYS_PCIE0_CFG_EML_CONTROL_POS = 0,
    PIPE_SYS_PCIE0_RTLH_RFC_UPD_MASK = (int)0x100,
    PIPE_SYS_PCIE0_RTLH_RFC_UPD_POS = 8,
};

enum PIPE_SYS_REG_PCIE0_REG51_FIELD
{
    PIPE_SYS_PCIE0_RTLH_RFC_DATA_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_RTLH_RFC_DATA_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG52_FIELD
{
    PIPE_SYS_PCIE0_RADM_INTA_ASSERTED_MASK = (int)0x1,
    PIPE_SYS_PCIE0_RADM_INTA_ASSERTED_POS = 0,
    PIPE_SYS_PCIE0_RADM_INTB_ASSERTED_MASK = (int)0x2,
    PIPE_SYS_PCIE0_RADM_INTB_ASSERTED_POS = 1,
    PIPE_SYS_PCIE0_RADM_INTC_ASSERTED_MASK = (int)0x4,
    PIPE_SYS_PCIE0_RADM_INTC_ASSERTED_POS = 2,
    PIPE_SYS_PCIE0_RADM_INTD_ASSERTED_MASK = (int)0x8,
    PIPE_SYS_PCIE0_RADM_INTD_ASSERTED_POS = 3,
    PIPE_SYS_PCIE0_RADM_INTA_DEASSERTED_MASK = (int)0x10,
    PIPE_SYS_PCIE0_RADM_INTA_DEASSERTED_POS = 4,
    PIPE_SYS_PCIE0_RADM_INTB_DEASSERTED_MASK = (int)0x20,
    PIPE_SYS_PCIE0_RADM_INTB_DEASSERTED_POS = 5,
    PIPE_SYS_PCIE0_RADM_INTC_DEASSERTED_MASK = (int)0x40,
    PIPE_SYS_PCIE0_RADM_INTC_DEASSERTED_POS = 6,
    PIPE_SYS_PCIE0_RADM_INTD_DEASSERTED_MASK = (int)0x80,
    PIPE_SYS_PCIE0_RADM_INTD_DEASSERTED_POS = 7,
    PIPE_SYS_PCIE0_RADM_CORRECTABLE_ERR_MASK = (int)0x100,
    PIPE_SYS_PCIE0_RADM_CORRECTABLE_ERR_POS = 8,
    PIPE_SYS_PCIE0_RADM_NONFATAL_ERR_MASK = (int)0x200,
    PIPE_SYS_PCIE0_RADM_NONFATAL_ERR_POS = 9,
    PIPE_SYS_PCIE0_RADM_FATAL_ERR_MASK = (int)0x400,
    PIPE_SYS_PCIE0_RADM_FATAL_ERR_POS = 10,
    PIPE_SYS_PCIE0_RADM_PM_PME_MASK = (int)0x800,
    PIPE_SYS_PCIE0_RADM_PM_PME_POS = 11,
    PIPE_SYS_PCIE0_RADM_PM_TO_ACK_MASK = (int)0x1000,
    PIPE_SYS_PCIE0_RADM_PM_TO_ACK_POS = 12,
    PIPE_SYS_PCIE0_HP_PME_MASK = (int)0x1fe000,
    PIPE_SYS_PCIE0_HP_PME_POS = 13,
    PIPE_SYS_PCIE0_HP_INT_MASK = (int)0x1fe00000,
    PIPE_SYS_PCIE0_HP_INT_POS = 21,
};

enum PIPE_SYS_REG_PCIE0_REG53_FIELD
{
    PIPE_SYS_PCIE0_HP_MSI_MASK = (int)0xff,
    PIPE_SYS_PCIE0_HP_MSI_POS = 0,
    PIPE_SYS_PCIE0_RADM_Q_NOT_EMPTY_MASK = (int)0x100,
    PIPE_SYS_PCIE0_RADM_Q_NOT_EMPTY_POS = 8,
    PIPE_SYS_PCIE0_RADM_QOVERFLOW_MASK = (int)0x200,
    PIPE_SYS_PCIE0_RADM_QOVERFLOW_POS = 9,
    PIPE_SYS_PCIE0_PM_XTLH_BLOCK_TLP_MASK = (int)0x400,
    PIPE_SYS_PCIE0_PM_XTLH_BLOCK_TLP_POS = 10,
};

enum PIPE_SYS_REG_PCIE0_REG54_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_START_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_START_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG55_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_START_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_START_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG56_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_START_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_START_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG57_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_START_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_START_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG58_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_START_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_START_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG59_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_START_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_START_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG60_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_START_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_START_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG61_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_START_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_START_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG62_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_START_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_START_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG63_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_START_9_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_START_9_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG64_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_START_10_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_START_10_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG65_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_START_11_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_START_11_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG66_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_START_12_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_START_12_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG67_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_START_13_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_START_13_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG68_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_START_14_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_START_14_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG69_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_START_15_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_START_15_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG70_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG71_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG72_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG73_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG74_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG75_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG76_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG77_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG78_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG79_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_9_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_9_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG80_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_10_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_10_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG81_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_11_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_11_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG82_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_12_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_12_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG83_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_13_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_13_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG84_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_14_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_14_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG85_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_15_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR0_LIMIT_15_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG86_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR1_START_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR1_START_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG87_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR1_START_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR1_START_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG88_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR1_START_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR1_START_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG89_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR1_START_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR1_START_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG90_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR1_START_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR1_START_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG91_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR1_START_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR1_START_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG92_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR1_START_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR1_START_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG93_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR1_START_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR1_START_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG94_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR1_LIMIT_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR1_LIMIT_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG95_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR1_LIMIT_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR1_LIMIT_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG96_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR1_LIMIT_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR1_LIMIT_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG97_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR1_LIMIT_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR1_LIMIT_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG98_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR1_LIMIT_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR1_LIMIT_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG99_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR1_LIMIT_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR1_LIMIT_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG100_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR1_LIMIT_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR1_LIMIT_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG101_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR1_LIMIT_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR1_LIMIT_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG102_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_START_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_START_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG103_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_START_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_START_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG104_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_START_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_START_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG105_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_START_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_START_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG106_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_START_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_START_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG107_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_START_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_START_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG108_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_START_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_START_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG109_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_START_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_START_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG110_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_START_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_START_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG111_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_START_9_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_START_9_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG112_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_START_10_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_START_10_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG113_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_START_11_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_START_11_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG114_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_START_12_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_START_12_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG115_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_START_13_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_START_13_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG116_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_START_14_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_START_14_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG117_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_START_15_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_START_15_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG118_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG119_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG120_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG121_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG122_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG123_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG124_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG125_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG126_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG127_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_9_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_9_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG128_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_10_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_10_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG129_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_11_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_11_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG130_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_12_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_12_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG131_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_13_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_13_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG132_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_14_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_14_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG133_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_15_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR2_LIMIT_15_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG134_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR3_START_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR3_START_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG135_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR3_START_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR3_START_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG136_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR3_START_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR3_START_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG137_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR3_START_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR3_START_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG138_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR3_START_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR3_START_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG139_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR3_START_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR3_START_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG140_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR3_START_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR3_START_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG141_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR3_START_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR3_START_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG142_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR3_LIMIT_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR3_LIMIT_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG143_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR3_LIMIT_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR3_LIMIT_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG144_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR3_LIMIT_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR3_LIMIT_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG145_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR3_LIMIT_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR3_LIMIT_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG146_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR3_LIMIT_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR3_LIMIT_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG147_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR3_LIMIT_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR3_LIMIT_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG148_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR3_LIMIT_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR3_LIMIT_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG149_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR3_LIMIT_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR3_LIMIT_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG150_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_START_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_START_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG151_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_START_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_START_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG152_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_START_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_START_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG153_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_START_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_START_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG154_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_START_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_START_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG155_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_START_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_START_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG156_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_START_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_START_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG157_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_START_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_START_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG158_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_START_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_START_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG159_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_START_9_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_START_9_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG160_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_START_10_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_START_10_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG161_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_START_11_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_START_11_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG162_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_START_12_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_START_12_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG163_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_START_13_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_START_13_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG164_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_START_14_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_START_14_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG165_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_START_15_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_START_15_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG166_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG167_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG168_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG169_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG170_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG171_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG172_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG173_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG174_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG175_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_9_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_9_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG176_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_10_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_10_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG177_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_11_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_11_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG178_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_12_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_12_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG179_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_13_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_13_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG180_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_14_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_14_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG181_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_15_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR4_LIMIT_15_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG182_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR5_START_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR5_START_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG183_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR5_START_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR5_START_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG184_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR5_START_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR5_START_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG185_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR5_START_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR5_START_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG186_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR5_START_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR5_START_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG187_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR5_START_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR5_START_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG188_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR5_START_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR5_START_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG189_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR5_START_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR5_START_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG190_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR5_LIMIT_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR5_LIMIT_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG191_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR5_LIMIT_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR5_LIMIT_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG192_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR5_LIMIT_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR5_LIMIT_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG193_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR5_LIMIT_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR5_LIMIT_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG194_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR5_LIMIT_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR5_LIMIT_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG195_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR5_LIMIT_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR5_LIMIT_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG196_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR5_LIMIT_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR5_LIMIT_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG197_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAR5_LIMIT_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_BAR5_LIMIT_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG198_FIELD
{
    PIPE_SYS_PCIE0_CFG_EXP_ROM_START_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_EXP_ROM_START_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG199_FIELD
{
    PIPE_SYS_PCIE0_CFG_EXP_ROM_START_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_EXP_ROM_START_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG200_FIELD
{
    PIPE_SYS_PCIE0_CFG_EXP_ROM_START_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_EXP_ROM_START_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG201_FIELD
{
    PIPE_SYS_PCIE0_CFG_EXP_ROM_START_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_EXP_ROM_START_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG202_FIELD
{
    PIPE_SYS_PCIE0_CFG_EXP_ROM_START_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_EXP_ROM_START_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG203_FIELD
{
    PIPE_SYS_PCIE0_CFG_EXP_ROM_START_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_EXP_ROM_START_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG204_FIELD
{
    PIPE_SYS_PCIE0_CFG_EXP_ROM_START_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_EXP_ROM_START_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG205_FIELD
{
    PIPE_SYS_PCIE0_CFG_EXP_ROM_START_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_EXP_ROM_START_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG206_FIELD
{
    PIPE_SYS_PCIE0_CFG_EXP_ROM_LIMIT_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_EXP_ROM_LIMIT_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG207_FIELD
{
    PIPE_SYS_PCIE0_CFG_EXP_ROM_LIMIT_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_EXP_ROM_LIMIT_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG208_FIELD
{
    PIPE_SYS_PCIE0_CFG_EXP_ROM_LIMIT_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_EXP_ROM_LIMIT_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG209_FIELD
{
    PIPE_SYS_PCIE0_CFG_EXP_ROM_LIMIT_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_EXP_ROM_LIMIT_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG210_FIELD
{
    PIPE_SYS_PCIE0_CFG_EXP_ROM_LIMIT_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_EXP_ROM_LIMIT_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG211_FIELD
{
    PIPE_SYS_PCIE0_CFG_EXP_ROM_LIMIT_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_EXP_ROM_LIMIT_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG212_FIELD
{
    PIPE_SYS_PCIE0_CFG_EXP_ROM_LIMIT_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_EXP_ROM_LIMIT_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG213_FIELD
{
    PIPE_SYS_PCIE0_CFG_EXP_ROM_LIMIT_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_EXP_ROM_LIMIT_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG214_FIELD
{
    PIPE_SYS_PCIE0_CFG_BUS_MASTER_EN_MASK = (int)0xff,
    PIPE_SYS_PCIE0_CFG_BUS_MASTER_EN_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG215_FIELD
{
    PIPE_SYS_PCIE0_CFG_2NDBUS_NUM_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_2NDBUS_NUM_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG216_FIELD
{
    PIPE_SYS_PCIE0_CFG_2NDBUS_NUM_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_2NDBUS_NUM_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG217_FIELD
{
    PIPE_SYS_PCIE0_CFG_SUBBUS_NUM_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_SUBBUS_NUM_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG218_FIELD
{
    PIPE_SYS_PCIE0_CFG_SUBBUS_NUM_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_SUBBUS_NUM_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG219_FIELD
{
    PIPE_SYS_PCIE0_CFG_2ND_RESET_MASK = (int)0x1,
    PIPE_SYS_PCIE0_CFG_2ND_RESET_POS = 0,
    PIPE_SYS_PCIE0_CFG_MAX_PAYLOAD_SIZE_MASK = (int)0x1fffffe,
    PIPE_SYS_PCIE0_CFG_MAX_PAYLOAD_SIZE_POS = 1,
};

enum PIPE_SYS_REG_PCIE0_REG220_FIELD
{
    PIPE_SYS_PCIE0_CFG_RCB_MASK = (int)0xff,
    PIPE_SYS_PCIE0_CFG_RCB_POS = 0,
    PIPE_SYS_PCIE0_CFG_MEM_SPACE_EN_MASK = (int)0xff00,
    PIPE_SYS_PCIE0_CFG_MEM_SPACE_EN_POS = 8,
};

enum PIPE_SYS_REG_PCIE0_REG221_FIELD
{
    PIPE_SYS_PCIE0_CFG_MAX_RD_REQ_SIZE_MASK = (int)0xffffff,
    PIPE_SYS_PCIE0_CFG_MAX_RD_REQ_SIZE_POS = 0,
    PIPE_SYS_PCIE0_RDLH_LINK_UP_MASK = (int)0x1000000,
    PIPE_SYS_PCIE0_RDLH_LINK_UP_POS = 24,
    PIPE_SYS_PCIE0_SMLH_LTSSM_STATE_MASK = (int)0x7e000000,
    PIPE_SYS_PCIE0_SMLH_LTSSM_STATE_POS = 25,
};

enum PIPE_SYS_REG_PCIE0_REG222_FIELD
{
    PIPE_SYS_PCIE0_PM_CURNT_STATE_MASK = (int)0x7,
    PIPE_SYS_PCIE0_PM_CURNT_STATE_POS = 0,
    PIPE_SYS_PCIE0_SMLH_LINK_UP_MASK = (int)0x8,
    PIPE_SYS_PCIE0_SMLH_LINK_UP_POS = 3,
    PIPE_SYS_PCIE0_SMLH_REQ_RST_NOT_MASK = (int)0x10,
    PIPE_SYS_PCIE0_SMLH_REQ_RST_NOT_POS = 4,
    PIPE_SYS_PCIE0_LINK_REQ_RST_NOT_MASK = (int)0x20,
    PIPE_SYS_PCIE0_LINK_REQ_RST_NOT_POS = 5,
    PIPE_SYS_PCIE0_BRDG_SLV_XFER_PENDING_MASK = (int)0x40,
    PIPE_SYS_PCIE0_BRDG_SLV_XFER_PENDING_POS = 6,
    PIPE_SYS_PCIE0_BRDG_DBI_XFER_PENDING_MASK = (int)0x80,
    PIPE_SYS_PCIE0_BRDG_DBI_XFER_PENDING_POS = 7,
    PIPE_SYS_PCIE0_EDMA_XFER_PENDING_MASK = (int)0x100,
    PIPE_SYS_PCIE0_EDMA_XFER_PENDING_POS = 8,
    PIPE_SYS_PCIE0_RADM_XFER_PENDING_MASK = (int)0x200,
    PIPE_SYS_PCIE0_RADM_XFER_PENDING_POS = 9,
    PIPE_SYS_PCIE0_CFG_REG_SERREN_MASK = (int)0x3fc00,
    PIPE_SYS_PCIE0_CFG_REG_SERREN_POS = 10,
    PIPE_SYS_PCIE0_CFG_COR_ERR_RPT_EN_MASK = (int)0x3fc0000,
    PIPE_SYS_PCIE0_CFG_COR_ERR_RPT_EN_POS = 18,
};

enum PIPE_SYS_REG_PCIE0_REG223_FIELD
{
    PIPE_SYS_PCIE0_CFG_NF_ERR_RPT_EN_MASK = (int)0xff,
    PIPE_SYS_PCIE0_CFG_NF_ERR_RPT_EN_POS = 0,
    PIPE_SYS_PCIE0_CFG_F_ERR_RPT_EN_MASK = (int)0xff00,
    PIPE_SYS_PCIE0_CFG_F_ERR_RPT_EN_POS = 8,
    PIPE_SYS_PCIE0_DIAG_CTRL_BUS_MASK = (int)0x70000,
    PIPE_SYS_PCIE0_DIAG_CTRL_BUS_POS = 16,
};

enum PIPE_SYS_REG_PCIE0_REG224_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG225_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG226_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG227_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG228_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG229_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG230_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG231_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG232_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG233_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_9_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_9_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG234_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_10_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_10_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG235_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_11_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_11_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG236_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_12_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_12_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG237_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_13_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_13_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG238_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_14_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_14_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG239_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_15_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_15_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG240_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_16_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_16_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG241_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_17_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_17_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG242_FIELD
{
    PIPE_SYS_PCIE0_APP_RAS_DES_SD_HOLD_LTSSM_MASK = (int)0x1,
    PIPE_SYS_PCIE0_APP_RAS_DES_SD_HOLD_LTSSM_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG243_FIELD
{
    PIPE_SYS_PCIE0_CXPL_DEBUG_INFO_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CXPL_DEBUG_INFO_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG244_FIELD
{
    PIPE_SYS_PCIE0_CXPL_DEBUG_INFO_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CXPL_DEBUG_INFO_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG245_FIELD
{
    PIPE_SYS_PCIE0_CXPL_DEBUG_INFO_EI_MASK = (int)0xffff,
    PIPE_SYS_PCIE0_CXPL_DEBUG_INFO_EI_POS = 0,
    PIPE_SYS_PCIE0_TRAINING_RST_N_MASK = (int)0x10000,
    PIPE_SYS_PCIE0_TRAINING_RST_N_POS = 16,
    PIPE_SYS_PCIE0_RADM_PM_TURNOFF_MASK = (int)0x20000,
    PIPE_SYS_PCIE0_RADM_PM_TURNOFF_POS = 17,
    PIPE_SYS_PCIE0_RADM_MSG_UNLOCK_MASK = (int)0x40000,
    PIPE_SYS_PCIE0_RADM_MSG_UNLOCK_POS = 18,
    PIPE_SYS_PCIE0_OUTBAND_PWRUP_CMD_MASK = (int)0x7f80000,
    PIPE_SYS_PCIE0_OUTBAND_PWRUP_CMD_POS = 19,
};

enum PIPE_SYS_REG_PCIE0_REG246_FIELD
{
    PIPE_SYS_PCIE0_PM_DSTATE_MASK = (int)0xffffff,
    PIPE_SYS_PCIE0_PM_DSTATE_POS = 0,
    PIPE_SYS_PCIE0_AUX_PM_EN_MASK = (int)0xff000000,
    PIPE_SYS_PCIE0_AUX_PM_EN_POS = 24,
};

enum PIPE_SYS_REG_PCIE0_REG247_FIELD
{
    PIPE_SYS_PCIE0_PM_PME_EN_MASK = (int)0xff,
    PIPE_SYS_PCIE0_PM_PME_EN_POS = 0,
    PIPE_SYS_PCIE0_PM_LINKST_IN_L0S_MASK = (int)0x100,
    PIPE_SYS_PCIE0_PM_LINKST_IN_L0S_POS = 8,
    PIPE_SYS_PCIE0_PM_LINKST_IN_L1_MASK = (int)0x200,
    PIPE_SYS_PCIE0_PM_LINKST_IN_L1_POS = 9,
    PIPE_SYS_PCIE0_PM_L1_ENTRY_STARTED_MASK = (int)0x400,
    PIPE_SYS_PCIE0_PM_L1_ENTRY_STARTED_POS = 10,
    PIPE_SYS_PCIE0_PM_LINKST_IN_L2_MASK = (int)0x800,
    PIPE_SYS_PCIE0_PM_LINKST_IN_L2_POS = 11,
    PIPE_SYS_PCIE0_PM_LINKST_L2_EXIT_MASK = (int)0x1000,
    PIPE_SYS_PCIE0_PM_LINKST_L2_EXIT_POS = 12,
    PIPE_SYS_PCIE0_PM_LINKST_IN_L1SUB_MASK = (int)0x2000,
    PIPE_SYS_PCIE0_PM_LINKST_IN_L1SUB_POS = 13,
    PIPE_SYS_PCIE0_CFG_L1SUB_EN_MASK = (int)0x4000,
    PIPE_SYS_PCIE0_CFG_L1SUB_EN_POS = 14,
    PIPE_SYS_PCIE0_PM_STATUS_MASK = (int)0x7f8000,
    PIPE_SYS_PCIE0_PM_STATUS_POS = 15,
};

enum PIPE_SYS_REG_PCIE0_REG248_FIELD
{
    PIPE_SYS_PCIE0_CFG_OBFF_EN_MASK = (int)0x60,
    PIPE_SYS_PCIE0_CFG_OBFF_EN_POS = 5,
    PIPE_SYS_PCIE0_RADM_MSG_CPU_ACTIVE_MASK = (int)0x80,
    PIPE_SYS_PCIE0_RADM_MSG_CPU_ACTIVE_POS = 7,
    PIPE_SYS_PCIE0_RADM_MSG_OBFF_MASK = (int)0x100,
    PIPE_SYS_PCIE0_RADM_MSG_OBFF_POS = 8,
    PIPE_SYS_PCIE0_RADM_MSG_IDLE_MASK = (int)0x200,
    PIPE_SYS_PCIE0_RADM_MSG_IDLE_POS = 9,
    PIPE_SYS_PCIE0_RADM_VENDOR_MSG_MASK = (int)0x400,
    PIPE_SYS_PCIE0_RADM_VENDOR_MSG_POS = 10,
};

enum PIPE_SYS_REG_PCIE0_REG249_FIELD
{
    PIPE_SYS_PCIE0_RADM_MSG_PAYLOAD_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_RADM_MSG_PAYLOAD_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG250_FIELD
{
    PIPE_SYS_PCIE0_RADM_MSG_PAYLOAD_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_RADM_MSG_PAYLOAD_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG251_FIELD
{
    PIPE_SYS_PCIE0_WAKE_MASK = (int)0x1,
    PIPE_SYS_PCIE0_WAKE_POS = 0,
    PIPE_SYS_PCIE0_RADM_MSG_REQ_ID_MASK = (int)0x1fffe,
    PIPE_SYS_PCIE0_RADM_MSG_REQ_ID_POS = 1,
    PIPE_SYS_PCIE0_TRGT_CPL_TIMEOUT_MASK = (int)0x20000,
    PIPE_SYS_PCIE0_TRGT_CPL_TIMEOUT_POS = 17,
    PIPE_SYS_PCIE0_TRGT_TIMEOUT_CPL_FUNC_NUM_MASK = (int)0x1c0000,
    PIPE_SYS_PCIE0_TRGT_TIMEOUT_CPL_FUNC_NUM_POS = 18,
    PIPE_SYS_PCIE0_TRGT_TIMEOUT_CPL_TC_MASK = (int)0xe00000,
    PIPE_SYS_PCIE0_TRGT_TIMEOUT_CPL_TC_POS = 21,
    PIPE_SYS_PCIE0_TRGT_TIMEOUT_CPL_ATTR_MASK = (int)0x3000000,
    PIPE_SYS_PCIE0_TRGT_TIMEOUT_CPL_ATTR_POS = 24,
};

enum PIPE_SYS_REG_PCIE0_REG252_FIELD
{
    PIPE_SYS_PCIE0_TRGT_TIMEOUT_CPL_LEN_MASK = (int)0xfff,
    PIPE_SYS_PCIE0_TRGT_TIMEOUT_CPL_LEN_POS = 0,
    PIPE_SYS_PCIE0_TRGT_TIMEOUT_LOOKUP_ID_MASK = (int)0xff000,
    PIPE_SYS_PCIE0_TRGT_TIMEOUT_LOOKUP_ID_POS = 12,
    PIPE_SYS_PCIE0_TRGT_LOOKUP_ID_MASK = (int)0xff00000,
    PIPE_SYS_PCIE0_TRGT_LOOKUP_ID_POS = 20,
    PIPE_SYS_PCIE0_TRGT_LOOKUP_EMPTY_MASK = (int)0x10000000,
    PIPE_SYS_PCIE0_TRGT_LOOKUP_EMPTY_POS = 28,
    PIPE_SYS_PCIE0_RADM_CPL_TIMEOUT_MASK = (int)0x20000000,
    PIPE_SYS_PCIE0_RADM_CPL_TIMEOUT_POS = 29,
};

enum PIPE_SYS_REG_PCIE0_REG253_FIELD
{
    PIPE_SYS_PCIE0_RADM_TIMEOUT_FUNC_NUM_MASK = (int)0x7,
    PIPE_SYS_PCIE0_RADM_TIMEOUT_FUNC_NUM_POS = 0,
    PIPE_SYS_PCIE0_RADM_TIMEOUT_CPL_TC_MASK = (int)0x38,
    PIPE_SYS_PCIE0_RADM_TIMEOUT_CPL_TC_POS = 3,
    PIPE_SYS_PCIE0_RADM_TIMEOUT_CPL_ATTR_MASK = (int)0xc0,
    PIPE_SYS_PCIE0_RADM_TIMEOUT_CPL_ATTR_POS = 6,
    PIPE_SYS_PCIE0_RADM_TIMEOUT_CPL_LEN_MASK = (int)0xfff00,
    PIPE_SYS_PCIE0_RADM_TIMEOUT_CPL_LEN_POS = 8,
    PIPE_SYS_PCIE0_RADM_TIMEOUT_CPL_TAG_MASK = (int)0xff00000,
    PIPE_SYS_PCIE0_RADM_TIMEOUT_CPL_TAG_POS = 20,
};

enum PIPE_SYS_REG_PCIE0_REG254_FIELD
{
    PIPE_SYS_PCIE0_EDMA_INT_MASK = (int)0xffff,
    PIPE_SYS_PCIE0_EDMA_INT_POS = 0,
    PIPE_SYS_PCIE0_ASSERT_INTA_GRT_MASK = (int)0x10000,
    PIPE_SYS_PCIE0_ASSERT_INTA_GRT_POS = 16,
    PIPE_SYS_PCIE0_ASSERT_INTB_GRT_MASK = (int)0x20000,
    PIPE_SYS_PCIE0_ASSERT_INTB_GRT_POS = 17,
    PIPE_SYS_PCIE0_ASSERT_INTC_GRT_MASK = (int)0x40000,
    PIPE_SYS_PCIE0_ASSERT_INTC_GRT_POS = 18,
    PIPE_SYS_PCIE0_ASSERT_INTD_GRT_MASK = (int)0x80000,
    PIPE_SYS_PCIE0_ASSERT_INTD_GRT_POS = 19,
    PIPE_SYS_PCIE0_DEASSERT_INTA_GRT_MASK = (int)0x100000,
    PIPE_SYS_PCIE0_DEASSERT_INTA_GRT_POS = 20,
    PIPE_SYS_PCIE0_DEASSERT_INTB_GRT_MASK = (int)0x200000,
    PIPE_SYS_PCIE0_DEASSERT_INTB_GRT_POS = 21,
    PIPE_SYS_PCIE0_DEASSERT_INTC_GRT_MASK = (int)0x400000,
    PIPE_SYS_PCIE0_DEASSERT_INTC_GRT_POS = 22,
    PIPE_SYS_PCIE0_DEASSERT_INTD_GRT_MASK = (int)0x800000,
    PIPE_SYS_PCIE0_DEASSERT_INTD_GRT_POS = 23,
};

enum PIPE_SYS_REG_PCIE0_REG255_FIELD
{
    PIPE_SYS_PCIE0_CFG_INT_PIN_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_INT_PIN_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG256_FIELD
{
    PIPE_SYS_PCIE0_CFG_INT_PIN_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_INT_PIN_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG257_FIELD
{
    PIPE_SYS_PCIE0_CFG_SEND_COR_ERR_MASK = (int)0xff,
    PIPE_SYS_PCIE0_CFG_SEND_COR_ERR_POS = 0,
    PIPE_SYS_PCIE0_CFG_SEND_NF_ERR_MASK = (int)0xff00,
    PIPE_SYS_PCIE0_CFG_SEND_NF_ERR_POS = 8,
    PIPE_SYS_PCIE0_CFG_SEND_F_ERR_MASK = (int)0xff0000,
    PIPE_SYS_PCIE0_CFG_SEND_F_ERR_POS = 16,
    PIPE_SYS_PCIE0_CFG_INT_DISABLE_MASK = (int)0xff000000,
    PIPE_SYS_PCIE0_CFG_INT_DISABLE_POS = 24,
};

enum PIPE_SYS_REG_PCIE0_REG258_FIELD
{
    PIPE_SYS_PCIE0_CFG_NO_SNOOP_EN_MASK = (int)0xff,
    PIPE_SYS_PCIE0_CFG_NO_SNOOP_EN_POS = 0,
    PIPE_SYS_PCIE0_CFG_RELAX_ORDER_EN_MASK = (int)0xff00,
    PIPE_SYS_PCIE0_CFG_RELAX_ORDER_EN_POS = 8,
    PIPE_SYS_PCIE0_CFG_LINK_AUTO_BW_INT_MASK = (int)0x10000,
    PIPE_SYS_PCIE0_CFG_LINK_AUTO_BW_INT_POS = 16,
    PIPE_SYS_PCIE0_CFG_LINK_AUTO_BW_MSI_MASK = (int)0x20000,
    PIPE_SYS_PCIE0_CFG_LINK_AUTO_BW_MSI_POS = 17,
    PIPE_SYS_PCIE0_CFG_BW_MGT_INT_MASK = (int)0x40000,
    PIPE_SYS_PCIE0_CFG_BW_MGT_INT_POS = 18,
    PIPE_SYS_PCIE0_CFG_BW_MGT_MSI_MASK = (int)0x80000,
    PIPE_SYS_PCIE0_CFG_BW_MGT_MSI_POS = 19,
};

enum PIPE_SYS_REG_PCIE0_REG259_FIELD
{
    PIPE_SYS_PCIE0_MSI_CTRL_IO_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_MSI_CTRL_IO_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG260_FIELD
{
    PIPE_SYS_PCIE0_MSI_CTRL_INT_MASK = (int)0x1,
    PIPE_SYS_PCIE0_MSI_CTRL_INT_POS = 0,
    PIPE_SYS_PCIE0_MSI_CTRL_INT_VEC_MASK = (int)0x1fe,
    PIPE_SYS_PCIE0_MSI_CTRL_INT_VEC_POS = 1,
    PIPE_SYS_PCIE0_DEVICE_TYPE_MASK = (int)0x1e00,
    PIPE_SYS_PCIE0_DEVICE_TYPE_POS = 9,
    PIPE_SYS_PCIE0_RBAR_CTRL_UPDATE_MASK = (int)0x1fe000,
    PIPE_SYS_PCIE0_RBAR_CTRL_UPDATE_POS = 13,
};

enum PIPE_SYS_REG_PCIE0_REG261_FIELD
{
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG262_FIELD
{
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG263_FIELD
{
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG264_FIELD
{
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG265_FIELD
{
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG266_FIELD
{
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG267_FIELD
{
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG268_FIELD
{
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG269_FIELD
{
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_RBAR_SIZE_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG270_FIELD
{
    PIPE_SYS_PCIE0_VF_RBAR_CTRL_UPDATE_MASK = (int)0xff,
    PIPE_SYS_PCIE0_VF_RBAR_CTRL_UPDATE_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG271_FIELD
{
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG272_FIELD
{
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG273_FIELD
{
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_2_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_2_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG274_FIELD
{
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_3_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_3_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG275_FIELD
{
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_4_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_4_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG276_FIELD
{
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_5_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_5_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG277_FIELD
{
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_6_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_6_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG278_FIELD
{
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_7_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_7_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG279_FIELD
{
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_8_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_VF_RBAR_SIZE_8_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG280_FIELD
{
    PIPE_SYS_PCIE0_CFG_BR_CTRL_SERREN_MASK = (int)0xff,
    PIPE_SYS_PCIE0_CFG_BR_CTRL_SERREN_POS = 0,
    PIPE_SYS_PCIE0_PM_L1SUB_STATE_MASK = (int)0x700,
    PIPE_SYS_PCIE0_PM_L1SUB_STATE_POS = 8,
    PIPE_SYS_PCIE0_APP_L1SUB_DISABLE_MASK = (int)0x800,
    PIPE_SYS_PCIE0_APP_L1SUB_DISABLE_POS = 11,
    PIPE_SYS_PCIE0_PM_MASTER_STATE_MASK = (int)0x1f000,
    PIPE_SYS_PCIE0_PM_MASTER_STATE_POS = 12,
    PIPE_SYS_PCIE0_PM_SLAVE_STATE_MASK = (int)0x3e0000,
    PIPE_SYS_PCIE0_PM_SLAVE_STATE_POS = 17,
    PIPE_SYS_PCIE0_CFG_UNCOR_INTERNAL_ERR_STS_MASK = (int)0x400000,
    PIPE_SYS_PCIE0_CFG_UNCOR_INTERNAL_ERR_STS_POS = 22,
    PIPE_SYS_PCIE0_CFG_RCVR_OVERFLOW_ERR_STS_MASK = (int)0x800000,
    PIPE_SYS_PCIE0_CFG_RCVR_OVERFLOW_ERR_STS_POS = 23,
    PIPE_SYS_PCIE0_CFG_FC_PROTOCOL_ERR_STS_MASK = (int)0x1000000,
    PIPE_SYS_PCIE0_CFG_FC_PROTOCOL_ERR_STS_POS = 24,
    PIPE_SYS_PCIE0_CFG_MLF_TLP_ERR_STS_MASK = (int)0x2000000,
    PIPE_SYS_PCIE0_CFG_MLF_TLP_ERR_STS_POS = 25,
    PIPE_SYS_PCIE0_CFG_SURPRISE_DOWN_ER_STS_MASK = (int)0x4000000,
    PIPE_SYS_PCIE0_CFG_SURPRISE_DOWN_ER_STS_POS = 26,
    PIPE_SYS_PCIE0_CFG_DL_PROTOCOL_ERR_STS_MASK = (int)0x8000000,
    PIPE_SYS_PCIE0_CFG_DL_PROTOCOL_ERR_STS_POS = 27,
    PIPE_SYS_PCIE0_CFG_ECRC_ERR_STS_MASK = (int)0x10000000,
    PIPE_SYS_PCIE0_CFG_ECRC_ERR_STS_POS = 28,
    PIPE_SYS_PCIE0_CFG_CORRECTED_INTERNAL_ERR_STS_MASK = (int)0x20000000,
    PIPE_SYS_PCIE0_CFG_CORRECTED_INTERNAL_ERR_STS_POS = 29,
    PIPE_SYS_PCIE0_CFG_REPLAY_NUMBER_ROLLOVER_ERR_STS_MASK = (int)0x40000000,
    PIPE_SYS_PCIE0_CFG_REPLAY_NUMBER_ROLLOVER_ERR_STS_POS = 30,
    PIPE_SYS_PCIE0_CFG_REPLAY_TIMER_TIMEOUT_ERR_STS_MASK = (int)0x80000000,
    PIPE_SYS_PCIE0_CFG_REPLAY_TIMER_TIMEOUT_ERR_STS_POS = 31,
};

enum PIPE_SYS_REG_PCIE0_REG281_FIELD
{
    PIPE_SYS_PCIE0_CFG_BAD_DLLP_ERR_STS_MASK = (int)0x1,
    PIPE_SYS_PCIE0_CFG_BAD_DLLP_ERR_STS_POS = 0,
    PIPE_SYS_PCIE0_CFG_BAD_TLP_ERR_STS_MASK = (int)0x2,
    PIPE_SYS_PCIE0_CFG_BAD_TLP_ERR_STS_POS = 1,
    PIPE_SYS_PCIE0_CFG_RCVR_ERR_STS_MASK = (int)0x4,
    PIPE_SYS_PCIE0_CFG_RCVR_ERR_STS_POS = 2,
    PIPE_SYS_PCIE0_APP_DEV_NUM_MASK = (int)0xf8,
    PIPE_SYS_PCIE0_APP_DEV_NUM_POS = 3,
    PIPE_SYS_PCIE0_APP_BUS_NUM_MASK = (int)0xff00,
    PIPE_SYS_PCIE0_APP_BUS_NUM_POS = 8,
};

enum PIPE_SYS_REG_PCIE0_REG282_FIELD
{
    PIPE_SYS_PCIE0_RADM_TRGT1_ATU_SLOC_MATCH_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_RADM_TRGT1_ATU_SLOC_MATCH_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG283_FIELD
{
    PIPE_SYS_PCIE0_RADM_TRGT1_ATU_CBUF_ERR_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_RADM_TRGT1_ATU_CBUF_ERR_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG284_FIELD
{
    PIPE_SYS_PCIE0_CFG_PHY_CONTROL_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_PHY_CONTROL_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG285_FIELD
{
    PIPE_SYS_PCIE0_PHY_CFG_STATUS_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_PHY_CFG_STATUS_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG286_FIELD
{
    PIPE_SYS_PCIE0_PM_ASPM_L1_ENTER_READY_MASK = (int)0x1,
    PIPE_SYS_PCIE0_PM_ASPM_L1_ENTER_READY_POS = 0,
    PIPE_SYS_PCIE0_RADM_SLOT_PWR_LIMIT_MASK = (int)0x2,
    PIPE_SYS_PCIE0_RADM_SLOT_PWR_LIMIT_POS = 1,
};

enum PIPE_SYS_REG_PCIE0_REG287_FIELD
{
    PIPE_SYS_PCIE0_RADM_SLOT_PWR_PAYLOAD_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_RADM_SLOT_PWR_PAYLOAD_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG288_FIELD
{
    PIPE_SYS_PCIE0_PERST_N_REG_MASK = (int)0x1,
    PIPE_SYS_PCIE0_PERST_N_REG_POS = 0,
    PIPE_SYS_PCIE0_PERST_O_CTL_REG_MASK = (int)0x6,
    PIPE_SYS_PCIE0_PERST_O_CTL_REG_POS = 1,
    PIPE_SYS_PCIE0_PHY_RST_REG_MASK = (int)0x8,
    PIPE_SYS_PCIE0_PHY_RST_REG_POS = 3,
    PIPE_SYS_PAD_PCIE0_PERST_OE_MASK = (int)0x10,
    PIPE_SYS_PAD_PCIE0_PERST_OE_POS = 4,
    PIPE_SYS_PCIE0_PERST_CTL_REG_MASK = (int)0x60,
    PIPE_SYS_PCIE0_PERST_CTL_REG_POS = 5,
};

enum PIPE_SYS_REG_PCIE0_RAM_REG_0_FIELD
{
    PIPE_SYS_PCIE0_EDMA_RD_ENG_MSI_EMAA_MASK = (int)0x1c0000,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_MSI_EMAA_POS = 18,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_MSI_EMAB_MASK = (int)0x38000,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_MSI_EMAB_POS = 15,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_MSI_EMASA_MASK = (int)0x4000,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_MSI_EMASA_POS = 14,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_MSI_EMAA_MASK = (int)0x3800,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_MSI_EMAA_POS = 11,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_MSI_EMAB_MASK = (int)0x700,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_MSI_EMAB_POS = 8,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_MSI_EMASA_MASK = (int)0x80,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_MSI_EMASA_POS = 7,
    PIPE_SYS_PCIE0_IB_MCPL_SB_RAM_EMA_MASK = (int)0x70,
    PIPE_SYS_PCIE0_IB_MCPL_SB_RAM_EMA_POS = 4,
    PIPE_SYS_PCIE0_IB_MCPL_SB_RAM_EMAW_MASK = (int)0xc,
    PIPE_SYS_PCIE0_IB_MCPL_SB_RAM_EMAW_POS = 2,
    PIPE_SYS_PCIE0_IB_MCPL_SB_RAM_EMAS_MASK = (int)0x2,
    PIPE_SYS_PCIE0_IB_MCPL_SB_RAM_EMAS_POS = 1,
    PIPE_SYS_PCIE0_IB_MCPL_SB_RAM_EMAP_MASK = (int)0x1,
    PIPE_SYS_PCIE0_IB_MCPL_SB_RAM_EMAP_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_RAM_REG_1_FIELD
{
    PIPE_SYS_PCIE0_IB_MCPL_A2C_CDC_RAM_EMAA_MASK = (int)0x70000000,
    PIPE_SYS_PCIE0_IB_MCPL_A2C_CDC_RAM_EMAA_POS = 28,
    PIPE_SYS_PCIE0_IB_MCPL_A2C_CDC_RAM_EMAB_MASK = (int)0xe000000,
    PIPE_SYS_PCIE0_IB_MCPL_A2C_CDC_RAM_EMAB_POS = 25,
    PIPE_SYS_PCIE0_IB_MCPL_A2C_CDC_RAM_EMASA_MASK = (int)0x1000000,
    PIPE_SYS_PCIE0_IB_MCPL_A2C_CDC_RAM_EMASA_POS = 24,
    PIPE_SYS_PCIE0_IB_RREQ_C2A_CDC_RAM_EMAA_MASK = (int)0xe00000,
    PIPE_SYS_PCIE0_IB_RREQ_C2A_CDC_RAM_EMAA_POS = 21,
    PIPE_SYS_PCIE0_IB_RREQ_C2A_CDC_RAM_EMAB_MASK = (int)0x1c0000,
    PIPE_SYS_PCIE0_IB_RREQ_C2A_CDC_RAM_EMAB_POS = 18,
    PIPE_SYS_PCIE0_IB_RREQ_C2A_CDC_RAM_EMASA_MASK = (int)0x20000,
    PIPE_SYS_PCIE0_IB_RREQ_C2A_CDC_RAM_EMASA_POS = 17,
    PIPE_SYS_PCIE0_IB_WREQ_C2A_CDC_RAM_L_EMAA_MASK = (int)0x1c000,
    PIPE_SYS_PCIE0_IB_WREQ_C2A_CDC_RAM_L_EMAA_POS = 14,
    PIPE_SYS_PCIE0_IB_WREQ_C2A_CDC_RAM_L_EMAB_MASK = (int)0x3800,
    PIPE_SYS_PCIE0_IB_WREQ_C2A_CDC_RAM_L_EMAB_POS = 11,
    PIPE_SYS_PCIE0_IB_WREQ_C2A_CDC_RAM_L_EMASA_MASK = (int)0x400,
    PIPE_SYS_PCIE0_IB_WREQ_C2A_CDC_RAM_L_EMASA_POS = 10,
    PIPE_SYS_PCIE0_IB_WREQ_C2A_CDC_RAM_H_EMAA_MASK = (int)0x380,
    PIPE_SYS_PCIE0_IB_WREQ_C2A_CDC_RAM_H_EMAA_POS = 7,
    PIPE_SYS_PCIE0_IB_WREQ_C2A_CDC_RAM_H_EMAB_MASK = (int)0x70,
    PIPE_SYS_PCIE0_IB_WREQ_C2A_CDC_RAM_H_EMAB_POS = 4,
    PIPE_SYS_PCIE0_IB_WREQ_C2A_CDC_RAM_H_EMASA_MASK = (int)0x8,
    PIPE_SYS_PCIE0_IB_WREQ_C2A_CDC_RAM_H_EMASA_POS = 3,
    PIPE_SYS_PCIE0_OB_CCMP_DATA_RAM_EMAA_MASK = (int)0x7,
    PIPE_SYS_PCIE0_OB_CCMP_DATA_RAM_EMAA_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_RAM_REG_2_FIELD
{
    PIPE_SYS_PCIE0_OB_CCMP_DATA_RAM_EMAB_MASK = (int)0x38000000,
    PIPE_SYS_PCIE0_OB_CCMP_DATA_RAM_EMAB_POS = 27,
    PIPE_SYS_PCIE0_OB_CCMP_DATA_RAM_EMASA_MASK = (int)0x4000000,
    PIPE_SYS_PCIE0_OB_CCMP_DATA_RAM_EMASA_POS = 26,
    PIPE_SYS_PCIE0_SLV_NPW_SAB_RAM_EMA_MASK = (int)0x3800000,
    PIPE_SYS_PCIE0_SLV_NPW_SAB_RAM_EMA_POS = 23,
    PIPE_SYS_PCIE0_SLV_NPW_SAB_RAM_EMAW_MASK = (int)0x600000,
    PIPE_SYS_PCIE0_SLV_NPW_SAB_RAM_EMAW_POS = 21,
    PIPE_SYS_PCIE0_SLV_NPW_SAB_RAM_EMAS_MASK = (int)0x100000,
    PIPE_SYS_PCIE0_SLV_NPW_SAB_RAM_EMAS_POS = 20,
    PIPE_SYS_PCIE0_SLV_NPW_SAB_RAM_EMAP_MASK = (int)0x80000,
    PIPE_SYS_PCIE0_SLV_NPW_SAB_RAM_EMAP_POS = 19,
    PIPE_SYS_PCIE0_OB_PDCMP_DATA_RAM_EMAA_MASK = (int)0x70000,
    PIPE_SYS_PCIE0_OB_PDCMP_DATA_RAM_EMAA_POS = 16,
    PIPE_SYS_PCIE0_OB_PDCMP_DATA_RAM_EMAB_MASK = (int)0xe000,
    PIPE_SYS_PCIE0_OB_PDCMP_DATA_RAM_EMAB_POS = 13,
    PIPE_SYS_PCIE0_OB_PDCMP_DATA_RAM_EMASA_MASK = (int)0x1000,
    PIPE_SYS_PCIE0_OB_PDCMP_DATA_RAM_EMASA_POS = 12,
    PIPE_SYS_PCIE0_OB_PDCMP_HDR_RAM_EMAA_MASK = (int)0xe00,
    PIPE_SYS_PCIE0_OB_PDCMP_HDR_RAM_EMAA_POS = 9,
    PIPE_SYS_PCIE0_OB_PDCMP_HDR_RAM_EMAB_MASK = (int)0x1c0,
    PIPE_SYS_PCIE0_OB_PDCMP_HDR_RAM_EMAB_POS = 6,
    PIPE_SYS_PCIE0_OB_PDCMP_HDR_RAM_EMASA_MASK = (int)0x20,
    PIPE_SYS_PCIE0_OB_PDCMP_HDR_RAM_EMASA_POS = 5,
    PIPE_SYS_PCIE0_CDM_RAS_DES_EC_RAM_EMA_MASK = (int)0x1c,
    PIPE_SYS_PCIE0_CDM_RAS_DES_EC_RAM_EMA_POS = 2,
    PIPE_SYS_PCIE0_CDM_RAS_DES_EC_RAM_EMAW_MASK = (int)0x3,
    PIPE_SYS_PCIE0_CDM_RAS_DES_EC_RAM_EMAW_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_RAM_REG_3_FIELD
{
    PIPE_SYS_PCIE0_CDM_RAS_DES_EC_RAM_EMAS_MASK = (int)0x20000000,
    PIPE_SYS_PCIE0_CDM_RAS_DES_EC_RAM_EMAS_POS = 29,
    PIPE_SYS_PCIE0_CDM_RAS_DES_EC_RAM_EMAP_MASK = (int)0x10000000,
    PIPE_SYS_PCIE0_CDM_RAS_DES_EC_RAM_EMAP_POS = 28,
    PIPE_SYS_PCIE0_EDMARBUFF2RAM_EMA_MASK = (int)0xe000000,
    PIPE_SYS_PCIE0_EDMARBUFF2RAM_EMA_POS = 25,
    PIPE_SYS_PCIE0_EDMARBUFF2RAM_EMAW_MASK = (int)0x1800000,
    PIPE_SYS_PCIE0_EDMARBUFF2RAM_EMAW_POS = 23,
    PIPE_SYS_PCIE0_EDMARBUFF2RAM_EMAS_MASK = (int)0x400000,
    PIPE_SYS_PCIE0_EDMARBUFF2RAM_EMAS_POS = 22,
    PIPE_SYS_PCIE0_EDMARBUFF2RAM_EMAP_MASK = (int)0x200000,
    PIPE_SYS_PCIE0_EDMARBUFF2RAM_EMAP_POS = 21,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_C2W_LUT_EMAA_MASK = (int)0x1c0000,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_C2W_LUT_EMAA_POS = 18,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_C2W_LUT_EMAB_MASK = (int)0x38000,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_C2W_LUT_EMAB_POS = 15,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_C2W_LUT_EMASA_MASK = (int)0x4000,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_C2W_LUT_EMASA_POS = 14,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_OVRL_H_EMA_MASK = (int)0x3800,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_OVRL_H_EMA_POS = 11,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_OVRL_H_EMAW_MASK = (int)0x600,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_OVRL_H_EMAW_POS = 9,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_OVRL_H_EMAS_MASK = (int)0x100,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_OVRL_H_EMAS_POS = 8,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_OVRL_H_EMAP_MASK = (int)0x80,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_OVRL_H_EMAP_POS = 7,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_OVRL_L_EMA_MASK = (int)0x70,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_OVRL_L_EMA_POS = 4,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_OVRL_L_EMAW_MASK = (int)0xc,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_OVRL_L_EMAW_POS = 2,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_OVRL_L_EMAS_MASK = (int)0x2,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_OVRL_L_EMAS_POS = 1,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_OVRL_L_EMAP_MASK = (int)0x1,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_OVRL_L_EMAP_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_RAM_REG_4_FIELD
{
    PIPE_SYS_PCIE0_EDMA_RD_ENG_STSH_LUT_EMAA_MASK = (int)0x70000000,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_STSH_LUT_EMAA_POS = 28,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_STSH_LUT_EMAB_MASK = (int)0xe000000,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_STSH_LUT_EMAB_POS = 25,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_STSH_LUT_EMASA_MASK = (int)0x1000000,
    PIPE_SYS_PCIE0_EDMA_RD_ENG_STSH_LUT_EMASA_POS = 24,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_C2W_LUT_EMAA_MASK = (int)0xe00000,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_C2W_LUT_EMAA_POS = 21,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_C2W_LUT_EMAB_MASK = (int)0x1c0000,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_C2W_LUT_EMAB_POS = 18,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_C2W_LUT_EMASA_MASK = (int)0x20000,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_C2W_LUT_EMASA_POS = 17,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_OVRL_L_EMA_MASK = (int)0x1c000,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_OVRL_L_EMA_POS = 14,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_OVRL_L_EMAW_MASK = (int)0x3000,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_OVRL_L_EMAW_POS = 12,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_OVRL_L_EMAS_MASK = (int)0x800,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_OVRL_L_EMAS_POS = 11,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_OVRL_L_EMAP_MASK = (int)0x400,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_OVRL_L_EMAP_POS = 10,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_OVRL_H_EMA_MASK = (int)0x380,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_OVRL_H_EMA_POS = 7,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_OVRL_H_EMAW_MASK = (int)0x60,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_OVRL_H_EMAW_POS = 5,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_OVRL_H_EMAS_MASK = (int)0x10,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_OVRL_H_EMAS_POS = 4,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_OVRL_H_EMAP_MASK = (int)0x8,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_OVRL_H_EMAP_POS = 3,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_STSH_LUT_EMAA_MASK = (int)0x7,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_STSH_LUT_EMAA_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_RAM_REG_5_FIELD
{
    PIPE_SYS_PCIE0_EDMA_WR_ENG_STSH_LUT_EMAB_MASK = (int)0x70000000,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_STSH_LUT_EMAB_POS = 28,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_STSH_LUT_EMASA_MASK = (int)0x8000000,
    PIPE_SYS_PCIE0_EDMA_WR_ENG_STSH_LUT_EMASA_POS = 27,
    PIPE_SYS_PCIE0_P_DATAQ_EMA_MASK = (int)0x7000000,
    PIPE_SYS_PCIE0_P_DATAQ_EMA_POS = 24,
    PIPE_SYS_PCIE0_P_DATAQ_EMAW_MASK = (int)0xc00000,
    PIPE_SYS_PCIE0_P_DATAQ_EMAW_POS = 22,
    PIPE_SYS_PCIE0_P_DATAQ_EMAS_MASK = (int)0x200000,
    PIPE_SYS_PCIE0_P_DATAQ_EMAS_POS = 21,
    PIPE_SYS_PCIE0_P_DATAQ_EMAP_MASK = (int)0x100000,
    PIPE_SYS_PCIE0_P_DATAQ_EMAP_POS = 20,
    PIPE_SYS_PCIE0_P_HDRQ_EMA_MASK = (int)0xe0000,
    PIPE_SYS_PCIE0_P_HDRQ_EMA_POS = 17,
    PIPE_SYS_PCIE0_P_HDRQ_EMAW_MASK = (int)0x18000,
    PIPE_SYS_PCIE0_P_HDRQ_EMAW_POS = 15,
    PIPE_SYS_PCIE0_P_HDRQ_EMAS_MASK = (int)0x4000,
    PIPE_SYS_PCIE0_P_HDRQ_EMAS_POS = 14,
    PIPE_SYS_PCIE0_P_HDRQ_EMAP_MASK = (int)0x2000,
    PIPE_SYS_PCIE0_P_HDRQ_EMAP_POS = 13,
    PIPE_SYS_PCIE0_XDLH_RETRYRAM_EMA_MASK = (int)0x1c00,
    PIPE_SYS_PCIE0_XDLH_RETRYRAM_EMA_POS = 10,
    PIPE_SYS_PCIE0_XDLH_RETRYRAM_EMAW_MASK = (int)0x300,
    PIPE_SYS_PCIE0_XDLH_RETRYRAM_EMAW_POS = 8,
    PIPE_SYS_PCIE0_XDLH_RETRYRAM_EMAS_MASK = (int)0x80,
    PIPE_SYS_PCIE0_XDLH_RETRYRAM_EMAS_POS = 7,
    PIPE_SYS_PCIE0_OB_NPDCMP_RAM_EMAA_MASK = (int)0x70,
    PIPE_SYS_PCIE0_OB_NPDCMP_RAM_EMAA_POS = 4,
    PIPE_SYS_PCIE0_OB_NPDCMP_RAM_EMAB_MASK = (int)0xe,
    PIPE_SYS_PCIE0_OB_NPDCMP_RAM_EMAB_POS = 1,
    PIPE_SYS_PCIE0_OB_NPDCMP_RAM_EMASA_MASK = (int)0x1,
    PIPE_SYS_PCIE0_OB_NPDCMP_RAM_EMASA_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_AXI_SLV_REG0_FIELD
{
    PIPE_SYS_MATRIX15_PCIE0_S_AWMISC_INFO_HDR_34DW_1_MASK = (int)0xffffffff,
    PIPE_SYS_MATRIX15_PCIE0_S_AWMISC_INFO_HDR_34DW_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_AXI_SLV_REG1_FIELD
{
    PIPE_SYS_MATRIX15_PCIE0_S_AWMISC_INFO_HDR_34DW_0_MASK = (int)0xffffffff,
    PIPE_SYS_MATRIX15_PCIE0_S_AWMISC_INFO_HDR_34DW_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_AXI_SLV_REG2_FIELD
{
    PIPE_SYS_MATRIX15_PCIE0_S_AWMISC_INFO_P_TAG_MASK = (int)0x1fe00,
    PIPE_SYS_MATRIX15_PCIE0_S_AWMISC_INFO_P_TAG_POS = 9,
    PIPE_SYS_MATRIX15_PCIE0_S_ARMISC_INFO_ATU_BYPASS_MASK = (int)0x100,
    PIPE_SYS_MATRIX15_PCIE0_S_ARMISC_INFO_ATU_BYPASS_POS = 8,
    PIPE_SYS_MATRIX15_PCIE0_S_WMISC_INFO_SILENTDROP_MASK = (int)0x80,
    PIPE_SYS_MATRIX15_PCIE0_S_WMISC_INFO_SILENTDROP_POS = 7,
    PIPE_SYS_MATRIX15_PCIE0_S_WMISC_INFO_EP_MASK = (int)0x40,
    PIPE_SYS_MATRIX15_PCIE0_S_WMISC_INFO_EP_POS = 6,
    PIPE_SYS_MATRIX15_PCIE0_S_CSYSREQ_MASK = (int)0x20,
    PIPE_SYS_MATRIX15_PCIE0_S_CSYSREQ_POS = 5,
    PIPE_SYS_MATRIX15_PCIE0_S_AWMISC_INFO_ATU_BYPASS_MASK = (int)0x10,
    PIPE_SYS_MATRIX15_PCIE0_S_AWMISC_INFO_ATU_BYPASS_POS = 4,
    PIPE_SYS_MATRIX15_PCIE0_S_AWQOS_MASK = (int)0xf,
    PIPE_SYS_MATRIX15_PCIE0_S_AWQOS_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_AXI_SLV_REG3_FIELD
{
    PIPE_SYS_MATRIX15_PCIE0_S_ARMISC_INFO_MASK = (int)0x1ffffff0,
    PIPE_SYS_MATRIX15_PCIE0_S_ARMISC_INFO_POS = 4,
    PIPE_SYS_MATRIX15_PCIE0_S_ARQOS_MASK = (int)0xf,
    PIPE_SYS_MATRIX15_PCIE0_S_ARQOS_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_AXI_SLV_REG4_FIELD
{
    PIPE_SYS_MATRIX15_PCIE0_S_AWMISC_INFO_MASK = (int)0x1ffffff,
    PIPE_SYS_MATRIX15_PCIE0_S_AWMISC_INFO_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_AXI_SLV_REG5_FIELD
{
    PIPE_SYS_PCIE0_MATRIX15_S_CACTIVE_MASK = (int)0x20000000,
    PIPE_SYS_PCIE0_MATRIX15_S_CACTIVE_POS = 29,
    PIPE_SYS_PCIE0_MATRIX15_S_CSYSACK_MASK = (int)0x10000000,
    PIPE_SYS_PCIE0_MATRIX15_S_CSYSACK_POS = 28,
    PIPE_SYS_PCIE0_MATRIX15_S_RMISC_INFO_MASK = (int)0xfffc000,
    PIPE_SYS_PCIE0_MATRIX15_S_RMISC_INFO_POS = 14,
    PIPE_SYS_PCIE0_MATRIX15_S_BMISC_INFO_MASK = (int)0x3fff,
    PIPE_SYS_PCIE0_MATRIX15_S_BMISC_INFO_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_AXI_MST_REG0_FIELD
{
    PIPE_SYS_PCIE0_MATRIX12_M_AWMISC_INFO_HDR_34DW_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_MATRIX12_M_AWMISC_INFO_HDR_34DW_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_AXI_MST_REG1_FIELD
{
    PIPE_SYS_PCIE0_MATRIX12_M_AWMISC_INFO_HDR_34DW_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_MATRIX12_M_AWMISC_INFO_HDR_34DW_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_AXI_MST_REG2_FIELD
{
    PIPE_SYS_PCIE0_MATRIX12_M_ARMISC_INFO_1_MASK = (int)0xffff,
    PIPE_SYS_PCIE0_MATRIX12_M_ARMISC_INFO_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_AXI_MST_REG3_FIELD
{
    PIPE_SYS_PCIE0_MATRIX12_M_ARMISC_INFO_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_MATRIX12_M_ARMISC_INFO_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_AXI_MST_REG4_FIELD
{
    PIPE_SYS_PCIE0_MATRIX12_M_AWMISC_INFO_1_MASK = (int)0xffff,
    PIPE_SYS_PCIE0_MATRIX12_M_AWMISC_INFO_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_AXI_MST_REG5_FIELD
{
    PIPE_SYS_PCIE0_MATRIX12_M_AWMISC_INFO_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_MATRIX12_M_AWMISC_INFO_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_AXI_MST_REG6_FIELD
{
    PIPE_SYS_PCIE0_MATRIX12_M_ARMISC_INFO_DMA_MASK = (int)0xfc0000,
    PIPE_SYS_PCIE0_MATRIX12_M_ARMISC_INFO_DMA_POS = 18,
    PIPE_SYS_PCIE0_MATRIX12_M_AWMISC_INFO_DMA_MASK = (int)0x3f000,
    PIPE_SYS_PCIE0_MATRIX12_M_AWMISC_INFO_DMA_POS = 12,
    PIPE_SYS_PCIE0_MATRIX12_M_ARMISC_INFO_LAST_DCMP_TLP_MASK = (int)0x800,
    PIPE_SYS_PCIE0_MATRIX12_M_ARMISC_INFO_LAST_DCMP_TLP_POS = 11,
    PIPE_SYS_PCIE0_MATRIX12_M_CACTIVE_MASK = (int)0x400,
    PIPE_SYS_PCIE0_MATRIX12_M_CACTIVE_POS = 10,
    PIPE_SYS_PCIE0_MATRIX12_M_ARMISC_INFO_ZEROREAD_MASK = (int)0x200,
    PIPE_SYS_PCIE0_MATRIX12_M_ARMISC_INFO_ZEROREAD_POS = 9,
    PIPE_SYS_PCIE0_MATRIX12_M_ARQOS_MASK = (int)0x1e0,
    PIPE_SYS_PCIE0_MATRIX12_M_ARQOS_POS = 5,
    PIPE_SYS_PCIE0_MATRIX12_M_AWMISC_INFO_LAST_DCMP_TLP_MASK = (int)0x10,
    PIPE_SYS_PCIE0_MATRIX12_M_AWMISC_INFO_LAST_DCMP_TLP_POS = 4,
    PIPE_SYS_PCIE0_MATRIX12_M_AWQOS_MASK = (int)0xf,
    PIPE_SYS_PCIE0_MATRIX12_M_AWQOS_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_AXI_MST_REG7_FIELD
{
    PIPE_SYS_PCIE0_MATRIX12_M_AWMISC_INFO_EP_MASK = (int)0x80000000,
    PIPE_SYS_PCIE0_MATRIX12_M_AWMISC_INFO_EP_POS = 31,
    PIPE_SYS_PCIE0_MATRIX12_M_CSYSACK_MASK = (int)0x100000,
    PIPE_SYS_PCIE0_MATRIX12_M_CSYSACK_POS = 20,
    PIPE_SYS_MATRIX12_PCIE0_M_RMISC_INFO_MASK = (int)0xfff80,
    PIPE_SYS_MATRIX12_PCIE0_M_RMISC_INFO_POS = 7,
    PIPE_SYS_MATRIX12_PCIE0_M_CSYSREQ_MASK = (int)0x40,
    PIPE_SYS_MATRIX12_PCIE0_M_CSYSREQ_POS = 6,
    PIPE_SYS_MATRIX12_PCIE0_M_BMISC_INFO_CPL_STAT_MASK = (int)0x38,
    PIPE_SYS_MATRIX12_PCIE0_M_BMISC_INFO_CPL_STAT_POS = 3,
    PIPE_SYS_MATRIX12_PCIE0_M_RMISC_INFO_CPL_STAT_MASK = (int)0x7,
    PIPE_SYS_MATRIX12_PCIE0_M_RMISC_INFO_CPL_STAT_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_DBI_SLV_REG0_FIELD
{
    PIPE_SYS_MATRIX15_PCIE0_DBI_S_CSYSREQ_MASK = (int)0x400,
    PIPE_SYS_MATRIX15_PCIE0_DBI_S_CSYSREQ_POS = 10,
    PIPE_SYS_MATRIX15_PCIE0_DBI_S_ARQOS_MASK = (int)0x3c0,
    PIPE_SYS_MATRIX15_PCIE0_DBI_S_ARQOS_POS = 6,
    PIPE_SYS_MATRIX15_PCIE0_DBI_S_AWQOS_MASK = (int)0x3c,
    PIPE_SYS_MATRIX15_PCIE0_DBI_S_AWQOS_POS = 2,
    PIPE_SYS_PCIE0_DBI_MATRIX15_S_CACTIVE_MASK = (int)0x2,
    PIPE_SYS_PCIE0_DBI_MATRIX15_S_CACTIVE_POS = 1,
    PIPE_SYS_PCIE0_DBI_MATRIX15_S_CSYSACK_MASK = (int)0x1,
    PIPE_SYS_PCIE0_DBI_MATRIX15_S_CSYSACK_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_VEN_MSG_START_T_FIELD
{
    PIPE_SYS_PCIE0_VEN_MSG_START_T_MASK = (int)0x1,
    PIPE_SYS_PCIE0_VEN_MSG_START_T_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_VEN_MSI_START_T_FIELD
{
    PIPE_SYS_PCIE0_VEN_MSI_START_T_MASK = (int)0x1,
    PIPE_SYS_PCIE0_VEN_MSI_START_T_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_APP_LTR_MSG_START_T_FIELD
{
    PIPE_SYS_PCIE0_APP_LTR_MSG_START_T_MASK = (int)0x1,
    PIPE_SYS_PCIE0_APP_LTR_MSG_START_T_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_APP_OBFF_IDLE_MSG_START_T_FIELD
{
    PIPE_SYS_PCIE0_APP_OBFF_IDLE_MSG_START_T_MASK = (int)0x1,
    PIPE_SYS_PCIE0_APP_OBFF_IDLE_MSG_START_T_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_APP_OBFF_OBFF_MSG_START_T_FIELD
{
    PIPE_SYS_PCIE0_APP_OBFF_OBFF_MSG_START_T_MASK = (int)0x1,
    PIPE_SYS_PCIE0_APP_OBFF_OBFF_MSG_START_T_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_APP_OBFF_CPU_ACTIVE_MSG_START_T_FIELD
{
    PIPE_SYS_PCIE0_APP_OBFF_CPU_ACTIVE_MSG_START_T_MASK = (int)0x1,
    PIPE_SYS_PCIE0_APP_OBFF_CPU_ACTIVE_MSG_START_T_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_VEN_MSG_REQ_TIMEOUT_CNT_FIELD
{
    PIPE_SYS_PCIE0_VEN_MSG_REQ_TIMEOUT_CNT_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_VEN_MSG_REQ_TIMEOUT_CNT_POS = 0,
};

enum PIPE_SYS_REG_PIPE_ADJUST_ADB400_MST_AXI_EN_FIELD
{
    PIPE_SYS_PIPE_ADJUST_ADB400_MST_AXI_EN_MASK = (int)0x1,
    PIPE_SYS_PIPE_ADJUST_ADB400_MST_AXI_EN_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG300_FIELD
{
    PIPE_SYS_PCIE0_RADM_INT_CLR_MASK = (int)0xf,
    PIPE_SYS_PCIE0_RADM_INT_CLR_POS = 0,
    PIPE_SYS_PCIE0_MSG_INTR_CLR_MASK = (int)0xfff0,
    PIPE_SYS_PCIE0_MSG_INTR_CLR_POS = 4,
    PIPE_SYS_PCIE0_RADM_ERR_INT_CLR_MASK = (int)0x70000,
    PIPE_SYS_PCIE0_RADM_ERR_INT_CLR_POS = 16,
};

enum PIPE_SYS_REG_PCIE0_REG301_FIELD
{
    PIPE_SYS_PCIE0_PCIE_AUX_INT_CLR_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_PCIE_AUX_INT_CLR_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG302_FIELD
{
    PIPE_SYS_PCIE0_PCIE_AUX_INT_CLR_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_PCIE_AUX_INT_CLR_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG303_FIELD
{
    PIPE_SYS_PCIE0_PCIE_AUX_INT_CLR_2_MASK = (int)0x3,
    PIPE_SYS_PCIE0_PCIE_AUX_INT_CLR_2_POS = 0,
    PIPE_SYS_PCIE0_ASSERT_INT_CLR_MASK = (int)0x3c,
    PIPE_SYS_PCIE0_ASSERT_INT_CLR_POS = 2,
    PIPE_SYS_PCIE0_MCTP_RFIFO_RD_MASK = (int)0x40,
    PIPE_SYS_PCIE0_MCTP_RFIFO_RD_POS = 6,
    PIPE_SYS_PCIE0_MCTP_SOFT_RFIFO_WCLR_MASK = (int)0x80,
    PIPE_SYS_PCIE0_MCTP_SOFT_RFIFO_WCLR_POS = 7,
    PIPE_SYS_PCIE0_MCTP_SOFT_RFIFO_RCLR_MASK = (int)0x100,
    PIPE_SYS_PCIE0_MCTP_SOFT_RFIFO_RCLR_POS = 8,
};

enum PIPE_SYS_REG_PCIE0_REG304_FIELD
{
    PIPE_SYS_PCIE0_RADM_TIMEOUT_INT_CLR_MASK = (int)0x1fffffff,
    PIPE_SYS_PCIE0_RADM_TIMEOUT_INT_CLR_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG305_FIELD
{
    PIPE_SYS_PCIE0_MSG_REQ_TIMEOUT_CHECK_MASK = (int)0x3f,
    PIPE_SYS_PCIE0_MSG_REQ_TIMEOUT_CHECK_POS = 0,
    PIPE_SYS_PCIE0_MSG_INTR_MSK_MASK = (int)0x3ffc0,
    PIPE_SYS_PCIE0_MSG_INTR_MSK_POS = 6,
    PIPE_SYS_PCIE0_MSG_INTR_RAW_MASK = (int)0x3ffc0000,
    PIPE_SYS_PCIE0_MSG_INTR_RAW_POS = 18,
};

enum PIPE_SYS_REG_PCIE0_REG306_FIELD
{
    PIPE_SYS_PCIE0_MSG_INTR_STT_MASK = (int)0xfff,
    PIPE_SYS_PCIE0_MSG_INTR_STT_POS = 0,
    PIPE_SYS_PCIE0_RADM_ERR_INT_MASK_MASK = (int)0x7000,
    PIPE_SYS_PCIE0_RADM_ERR_INT_MASK_POS = 12,
    PIPE_SYS_PCIE0_ASSERT_INT_MASK_MASK = (int)0x78000,
    PIPE_SYS_PCIE0_ASSERT_INT_MASK_POS = 15,
    PIPE_SYS_PCIE0_RADM_INT_MASK_MASK = (int)0x780000,
    PIPE_SYS_PCIE0_RADM_INT_MASK_POS = 19,
};

enum PIPE_SYS_REG_PCIE0_REG307_FIELD
{
    PIPE_SYS_PCIE0_PCIE_IP_INT_MASK_MASK = (int)0x7ffffff,
    PIPE_SYS_PCIE0_PCIE_IP_INT_MASK_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG308_FIELD
{
    PIPE_SYS_PCIE0_RADM_TIMEOUT_INT_MASK_MASK = (int)0x1fffffff,
    PIPE_SYS_PCIE0_RADM_TIMEOUT_INT_MASK_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG309_FIELD
{
    PIPE_SYS_PCIE0_PCIE_AUX_INT_MASK_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_PCIE_AUX_INT_MASK_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG310_FIELD
{
    PIPE_SYS_PCIE0_PCIE_AUX_INT_MASK_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_PCIE_AUX_INT_MASK_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG311_FIELD
{
    PIPE_SYS_PCIE0_PCIE_AUX_INT_MASK_2_MASK = (int)0x3,
    PIPE_SYS_PCIE0_PCIE_AUX_INT_MASK_2_POS = 0,
    PIPE_SYS_PCIE0_ASSERT_INT_CLR_CTL_MASK = (int)0x4,
    PIPE_SYS_PCIE0_ASSERT_INT_CLR_CTL_POS = 2,
    PIPE_SYS_PCIE0_RADM_INT_CLR_CTL_MASK = (int)0x8,
    PIPE_SYS_PCIE0_RADM_INT_CLR_CTL_POS = 3,
    PIPE_SYS_PCIE0_RADM_ERR_INT_RAW_MASK = (int)0x70,
    PIPE_SYS_PCIE0_RADM_ERR_INT_RAW_POS = 4,
    PIPE_SYS_PCIE0_ASSERT_INT_RAW_MASK = (int)0x780,
    PIPE_SYS_PCIE0_ASSERT_INT_RAW_POS = 7,
    PIPE_SYS_PCIE0_RADM_INT_RAW_MASK = (int)0x7800,
    PIPE_SYS_PCIE0_RADM_INT_RAW_POS = 11,
    PIPE_SYS_PCIE0_RADM_ERR_INT_STA_MASK = (int)0x38000,
    PIPE_SYS_PCIE0_RADM_ERR_INT_STA_POS = 15,
    PIPE_SYS_PCIE0_ASSERT_INT_STA_MASK = (int)0x3c0000,
    PIPE_SYS_PCIE0_ASSERT_INT_STA_POS = 18,
    PIPE_SYS_PCIE0_RADM_INT_STA_MASK = (int)0x3c00000,
    PIPE_SYS_PCIE0_RADM_INT_STA_POS = 22,
};

enum PIPE_SYS_REG_PCIE0_REG312_FIELD
{
    PIPE_SYS_PCIE0_RADM_TIMEOUT_INT_RAW_MASK = (int)0x1fffffff,
    PIPE_SYS_PCIE0_RADM_TIMEOUT_INT_RAW_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG313_FIELD
{
    PIPE_SYS_PCIE0_RADM_TIMEOUT_INT_STA_MASK = (int)0x1fffffff,
    PIPE_SYS_PCIE0_RADM_TIMEOUT_INT_STA_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG314_FIELD
{
    PIPE_SYS_PCIE0_PCIE_AUX_INT_RAW_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_PCIE_AUX_INT_RAW_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG315_FIELD
{
    PIPE_SYS_PCIE0_PCIE_AUX_INT_STA_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_PCIE_AUX_INT_STA_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG316_FIELD
{
    PIPE_SYS_PCIE0_PCIE_AUX_INT_RAW_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_PCIE_AUX_INT_RAW_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG317_FIELD
{
    PIPE_SYS_PCIE0_PCIE_AUX_INT_STA_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_PCIE_AUX_INT_STA_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG318_FIELD
{
    PIPE_SYS_PCIE0_PCIE_AUX_INT_RAW_2_MASK = (int)0x3,
    PIPE_SYS_PCIE0_PCIE_AUX_INT_RAW_2_POS = 0,
    PIPE_SYS_PCIE0_PCIE_AUX_INT_STA_2_MASK = (int)0xc,
    PIPE_SYS_PCIE0_PCIE_AUX_INT_STA_2_POS = 2,
    PIPE_SYS_PCIE0_MCTP_FIFO_WARN_LEVEL_REG_MASK = (int)0x3f0,
    PIPE_SYS_PCIE0_MCTP_FIFO_WARN_LEVEL_REG_POS = 4,
};

enum PIPE_SYS_REG_PCIE0_REG319_FIELD
{
    PIPE_SYS_PCIE0_RADM_TRGT1_ATU_SLOC_MATCH_MASK_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_RADM_TRGT1_ATU_SLOC_MATCH_MASK_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG320_FIELD
{
    PIPE_SYS_PCIE0_MCTP_RFIFO_RDAT_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_MCTP_RFIFO_RDAT_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG321_FIELD
{
    PIPE_SYS_PCIE0_MCTP_RFIFO_RDAT_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_MCTP_RFIFO_RDAT_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG322_FIELD
{
    PIPE_SYS_PCIE0_MCTP_RFIFO_RFLVL_MASK = (int)0x3f,
    PIPE_SYS_PCIE0_MCTP_RFIFO_RFLVL_POS = 0,
    PIPE_SYS_PCIE0_MCTP_RD_RFIFO_WFLVL_MASK = (int)0xfc0,
    PIPE_SYS_PCIE0_MCTP_RD_RFIFO_WFLVL_POS = 6,
    PIPE_SYS_PCIE0_RX_MCTP_INTR_MSK_MASK = (int)0x7000,
    PIPE_SYS_PCIE0_RX_MCTP_INTR_MSK_POS = 12,
    PIPE_SYS_PCIE0_RX_MCTP_INTR_RAW_MASK = (int)0x38000,
    PIPE_SYS_PCIE0_RX_MCTP_INTR_RAW_POS = 15,
    PIPE_SYS_PCIE0_RX_MCTP_INTR_STT_MASK = (int)0x1c0000,
    PIPE_SYS_PCIE0_RX_MCTP_INTR_STT_POS = 18,
};

enum PIPE_SYS_REG_PCIE0_CFG_PBUS_NUM_0_FIELD
{
    PIPE_SYS_PCIE0_CFG_PBUS_NUM_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_PBUS_NUM_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_CFG_PBUS_NUM_1_FIELD
{
    PIPE_SYS_PCIE0_CFG_PBUS_NUM_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_PBUS_NUM_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_CFG_PBUS_DEV_NUM_0_FIELD
{
    PIPE_SYS_PCIE0_CFG_PBUS_DEV_NUM_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_CFG_PBUS_DEV_NUM_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_CFG_PBUS_DEV_NUM_1_FIELD
{
    PIPE_SYS_PCIE0_CFG_PBUS_DEV_NUM_1_MASK = (int)0xff,
    PIPE_SYS_PCIE0_CFG_PBUS_DEV_NUM_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG323_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_18_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_18_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG324_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_19_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_19_POS = 0,
};

enum PIPE_SYS_REG_PCIE0_REG325_FIELD
{
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_20_MASK = (int)0x3ffff,
    PIPE_SYS_PCIE0_DIAG_STATUS_BUS_20_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG300_FIELD
{
    PIPE_SYS_PCIE1_RADM_INT_CLR_MASK = (int)0xf,
    PIPE_SYS_PCIE1_RADM_INT_CLR_POS = 0,
    PIPE_SYS_PCIE1_MSG_INTR_CLR_MASK = (int)0xfff0,
    PIPE_SYS_PCIE1_MSG_INTR_CLR_POS = 4,
    PIPE_SYS_PCIE1_RADM_ERR_INT_CLR_MASK = (int)0x70000,
    PIPE_SYS_PCIE1_RADM_ERR_INT_CLR_POS = 16,
};

enum PIPE_SYS_REG_PCIE1_REG301_FIELD
{
    PIPE_SYS_PCIE1_PCIE_AUX_INT_CLR_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_PCIE_AUX_INT_CLR_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG302_FIELD
{
    PIPE_SYS_PCIE1_PCIE_AUX_INT_CLR_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_PCIE_AUX_INT_CLR_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG303_FIELD
{
    PIPE_SYS_PCIE1_PCIE_AUX_INT_CLR_2_MASK = (int)0x3,
    PIPE_SYS_PCIE1_PCIE_AUX_INT_CLR_2_POS = 0,
    PIPE_SYS_PCIE1_ASSERT_INT_CLR_MASK = (int)0x3c,
    PIPE_SYS_PCIE1_ASSERT_INT_CLR_POS = 2,
    PIPE_SYS_PCIE1_MCTP_RFIFO_RD_MASK = (int)0x40,
    PIPE_SYS_PCIE1_MCTP_RFIFO_RD_POS = 6,
    PIPE_SYS_PCIE1_MCTP_SOFT_RFIFO_WCLR_MASK = (int)0x80,
    PIPE_SYS_PCIE1_MCTP_SOFT_RFIFO_WCLR_POS = 7,
    PIPE_SYS_PCIE1_MCTP_SOFT_RFIFO_RCLR_MASK = (int)0x100,
    PIPE_SYS_PCIE1_MCTP_SOFT_RFIFO_RCLR_POS = 8,
};

enum PIPE_SYS_REG_PCIE1_REG304_FIELD
{
    PIPE_SYS_PCIE1_RADM_TIMEOUT_INT_CLR_MASK = (int)0x1fffffff,
    PIPE_SYS_PCIE1_RADM_TIMEOUT_INT_CLR_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG305_FIELD
{
    PIPE_SYS_PCIE1_MSG_REQ_TIMEOUT_CHECK_MASK = (int)0x3f,
    PIPE_SYS_PCIE1_MSG_REQ_TIMEOUT_CHECK_POS = 0,
    PIPE_SYS_PCIE1_MSG_INTR_MSK_MASK = (int)0x3ffc0,
    PIPE_SYS_PCIE1_MSG_INTR_MSK_POS = 6,
    PIPE_SYS_PCIE1_MSG_INTR_RAW_MASK = (int)0x3ffc0000,
    PIPE_SYS_PCIE1_MSG_INTR_RAW_POS = 18,
};

enum PIPE_SYS_REG_PCIE1_REG306_FIELD
{
    PIPE_SYS_PCIE1_MSG_INTR_STT_MASK = (int)0xfff,
    PIPE_SYS_PCIE1_MSG_INTR_STT_POS = 0,
    PIPE_SYS_PCIE1_RADM_ERR_INT_MASK_MASK = (int)0x7000,
    PIPE_SYS_PCIE1_RADM_ERR_INT_MASK_POS = 12,
    PIPE_SYS_PCIE1_ASSERT_INT_MASK_MASK = (int)0x78000,
    PIPE_SYS_PCIE1_ASSERT_INT_MASK_POS = 15,
    PIPE_SYS_PCIE1_RADM_INT_MASK_MASK = (int)0x780000,
    PIPE_SYS_PCIE1_RADM_INT_MASK_POS = 19,
};

enum PIPE_SYS_REG_PCIE1_REG307_FIELD
{
    PIPE_SYS_PCIE1_PCIE_IP_INT_MASK_MASK = (int)0x7ffffff,
    PIPE_SYS_PCIE1_PCIE_IP_INT_MASK_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG308_FIELD
{
    PIPE_SYS_PCIE1_RADM_TIMEOUT_INT_MASK_MASK = (int)0x1fffffff,
    PIPE_SYS_PCIE1_RADM_TIMEOUT_INT_MASK_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG309_FIELD
{
    PIPE_SYS_PCIE1_PCIE_AUX_INT_MASK_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_PCIE_AUX_INT_MASK_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG310_FIELD
{
    PIPE_SYS_PCIE1_PCIE_AUX_INT_MASK_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_PCIE_AUX_INT_MASK_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG311_FIELD
{
    PIPE_SYS_PCIE1_PCIE_AUX_INT_MASK_2_MASK = (int)0x3,
    PIPE_SYS_PCIE1_PCIE_AUX_INT_MASK_2_POS = 0,
    PIPE_SYS_PCIE1_ASSERT_INT_CLR_CTL_MASK = (int)0x4,
    PIPE_SYS_PCIE1_ASSERT_INT_CLR_CTL_POS = 2,
    PIPE_SYS_PCIE1_RADM_INT_CLR_CTL_MASK = (int)0x8,
    PIPE_SYS_PCIE1_RADM_INT_CLR_CTL_POS = 3,
    PIPE_SYS_PCIE1_RADM_ERR_INT_RAW_MASK = (int)0x70,
    PIPE_SYS_PCIE1_RADM_ERR_INT_RAW_POS = 4,
    PIPE_SYS_PCIE1_ASSERT_INT_RAW_MASK = (int)0x780,
    PIPE_SYS_PCIE1_ASSERT_INT_RAW_POS = 7,
    PIPE_SYS_PCIE1_RADM_INT_RAW_MASK = (int)0x7800,
    PIPE_SYS_PCIE1_RADM_INT_RAW_POS = 11,
    PIPE_SYS_PCIE1_RADM_ERR_INT_STA_MASK = (int)0x38000,
    PIPE_SYS_PCIE1_RADM_ERR_INT_STA_POS = 15,
    PIPE_SYS_PCIE1_ASSERT_INT_STA_MASK = (int)0x3c0000,
    PIPE_SYS_PCIE1_ASSERT_INT_STA_POS = 18,
    PIPE_SYS_PCIE1_RADM_INT_STA_MASK = (int)0x3c00000,
    PIPE_SYS_PCIE1_RADM_INT_STA_POS = 22,
};

enum PIPE_SYS_REG_PCIE1_REG312_FIELD
{
    PIPE_SYS_PCIE1_RADM_TIMEOUT_INT_RAW_MASK = (int)0x1fffffff,
    PIPE_SYS_PCIE1_RADM_TIMEOUT_INT_RAW_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG313_FIELD
{
    PIPE_SYS_PCIE1_RADM_TIMEOUT_INT_STA_MASK = (int)0x1fffffff,
    PIPE_SYS_PCIE1_RADM_TIMEOUT_INT_STA_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG314_FIELD
{
    PIPE_SYS_PCIE1_PCIE_AUX_INT_RAW_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_PCIE_AUX_INT_RAW_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG315_FIELD
{
    PIPE_SYS_PCIE1_PCIE_AUX_INT_STA_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_PCIE_AUX_INT_STA_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG316_FIELD
{
    PIPE_SYS_PCIE1_PCIE_AUX_INT_RAW_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_PCIE_AUX_INT_RAW_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG317_FIELD
{
    PIPE_SYS_PCIE1_PCIE_AUX_INT_STA_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_PCIE_AUX_INT_STA_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG318_FIELD
{
    PIPE_SYS_PCIE1_PCIE_AUX_INT_RAW_2_MASK = (int)0x3,
    PIPE_SYS_PCIE1_PCIE_AUX_INT_RAW_2_POS = 0,
    PIPE_SYS_PCIE1_PCIE_AUX_INT_STA_2_MASK = (int)0xc,
    PIPE_SYS_PCIE1_PCIE_AUX_INT_STA_2_POS = 2,
    PIPE_SYS_PCIE1_MCTP_FIFO_WARN_LEVEL_REG_MASK = (int)0x3f0,
    PIPE_SYS_PCIE1_MCTP_FIFO_WARN_LEVEL_REG_POS = 4,
};

enum PIPE_SYS_REG_PCIE1_REG319_FIELD
{
    PIPE_SYS_PCIE1_RADM_TRGT1_ATU_SLOC_MATCH_MASK_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_RADM_TRGT1_ATU_SLOC_MATCH_MASK_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG320_FIELD
{
    PIPE_SYS_PCIE1_MCTP_RFIFO_RDAT_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_MCTP_RFIFO_RDAT_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG321_FIELD
{
    PIPE_SYS_PCIE1_MCTP_RFIFO_RDAT_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_MCTP_RFIFO_RDAT_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG322_FIELD
{
    PIPE_SYS_PCIE1_MCTP_RFIFO_RFLVL_MASK = (int)0x3f,
    PIPE_SYS_PCIE1_MCTP_RFIFO_RFLVL_POS = 0,
    PIPE_SYS_PCIE1_MCTP_RD_RFIFO_WFLVL_MASK = (int)0xfc0,
    PIPE_SYS_PCIE1_MCTP_RD_RFIFO_WFLVL_POS = 6,
    PIPE_SYS_PCIE1_RX_MCTP_INTR_MSK_MASK = (int)0x7000,
    PIPE_SYS_PCIE1_RX_MCTP_INTR_MSK_POS = 12,
    PIPE_SYS_PCIE1_RX_MCTP_INTR_RAW_MASK = (int)0x38000,
    PIPE_SYS_PCIE1_RX_MCTP_INTR_RAW_POS = 15,
    PIPE_SYS_PCIE1_RX_MCTP_INTR_STT_MASK = (int)0x1c0000,
    PIPE_SYS_PCIE1_RX_MCTP_INTR_STT_POS = 18,
};

enum PIPE_SYS_REG_PCIE1_CFG_PBUS_NUM_0_FIELD
{
    PIPE_SYS_PCIE1_CFG_PBUS_NUM_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_PBUS_NUM_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_CFG_PBUS_NUM_1_FIELD
{
    PIPE_SYS_PCIE1_CFG_PBUS_NUM_1_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_PBUS_NUM_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_CFG_PBUS_DEV_NUM_0_FIELD
{
    PIPE_SYS_PCIE1_CFG_PBUS_DEV_NUM_0_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_CFG_PBUS_DEV_NUM_0_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_CFG_PBUS_DEV_NUM_1_FIELD
{
    PIPE_SYS_PCIE1_CFG_PBUS_DEV_NUM_1_MASK = (int)0xff,
    PIPE_SYS_PCIE1_CFG_PBUS_DEV_NUM_1_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG323_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_18_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_18_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG324_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_19_MASK = (int)0xffffffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_19_POS = 0,
};

enum PIPE_SYS_REG_PCIE1_REG325_FIELD
{
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_20_MASK = (int)0x3ffff,
    PIPE_SYS_PCIE1_DIAG_STATUS_BUS_20_POS = 0,
};

#ifdef __cplusplus
}
#endif

#endif

