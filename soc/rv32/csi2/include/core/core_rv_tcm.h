#ifndef __CORE_RV_TCM_H__
#define __CORE_RV_TCM_H__

#if (CONFIG_CPU_XUANTIE_E907 || CONFIG_CPU_XUANTIE_E907F || CONFIG_CPU_XUANTIE_E907FD || CONFIG_CPU_XUANTIE_E907P || CONFIG_CPU_XUANTIE_E907FP || CONFIG_CPU_XUANTIE_E907FDP \
        || CONFIG_CPU_XUANTIE_R908 || CONFIG_CPU_XUANTIE_R908FD || CONFIG_CPU_XUANTIE_R908FDV \
        || CONFIG_CPU_XUANTIE_R908_CP || CONFIG_CPU_XUANTIE_R908FD_CP || CONFIG_CPU_XUANTIE_R908FDV_CP \
        || CONFIG_CPU_XUANTIE_R908_CP_XT || CONFIG_CPU_XUANTIE_R908FD_CP_XT || CONFIG_CPU_XUANTIE_R908FDV_CP_XT)

#if (CONFIG_CPU_XUANTIE_R908 || CONFIG_CPU_XUANTIE_R908FD || CONFIG_CPU_XUANTIE_R908FDV \
        || CONFIG_CPU_XUANTIE_R908_CP || CONFIG_CPU_XUANTIE_R908FD_CP || CONFIG_CPU_XUANTIE_R908FDV_CP \
        || CONFIG_CPU_XUANTIE_R908_CP_XT || CONFIG_CPU_XUANTIE_R908FD_CP_XT || CONFIG_CPU_XUANTIE_R908FDV_CP_XT)
#define __TCM_ECC_SUPPORT 1
#endif

/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_TCMFunctions TCM Functions
  \brief    Functions that configure TCM.
  @{
  */

/**
 \ingroup    CSI_tcm_register
 \defgroup   CSI_TCM
 \brief      Type definitions for the tcm Registers
 @{
 */

/**
  \brief        Consortium definition for accessing protection area selection register(MITCMCR, 0x7f9).
 */
typedef union {
    struct {
        unsigned long EN: 1;                             /*!< bit:     0  Instruction Tightly-Coupled Memory enable */
        unsigned long ECC_EN: 1;                         /*!< bit:     1  ecc_en */
        unsigned long Interleave: 1;                     /*!< bit:     2  Interleave */
        unsigned long _reserved1: 1;                     /*!< bit:     3  Reserved */
        unsigned long Size: 4;                           /*!< bit:  4..7  Size of ITCM */
        unsigned long _reserved2: 4;                     /*!< bit:  8..11 Reserved */
#if __riscv_xlen == 64
        unsigned long Base_Address: 52;                  /*!< bit: 12..63 Base address of ITCM */
#else
        unsigned long Base_Address: 20;                  /*!< bit: 12..31 Base address of ITCM */
#endif
    } b;                                                 /*!< Structure   Access by bit */
    unsigned long w;                                     /*!< Type        Access by whole register */
} MITCMCR_Type;

#define MITCMCR_Base_Address_Pos             12U                                                 /*!< MITCMCR: Base_Address Position */
#define MITCMCR_Base_Address_Msk             (0xfffffffffffffULL << MITCMCR_Base_Address_Pos)    /*!< MITCMCR: Base_Address Mask */

#define MITCMCR_Size_Pos                     4U                                                  /*!< MITCMCR: Size Position */
#define MITCMCR_Size_Msk                     (0xfULL << MITCMCR_Size_Pos)                        /*!< MITCMCR: Size Mask */

#define MITCMCR_INTERLEAVE_Pos               2U                                                  /*!< MITCMCR: Interleave Position */
#define MITCMCR_INTERLEAVE_Msk               (0x1ULL << MITCMCR_INTERLEAVE_Pos)                  /*!< MITCMCR: Interleave Mask */

#define MITCMCR_ECC_EN_Pos                   1U                                                  /*!< MITCMCR: ECC_EN Position */
#define MITCMCR_ECC_EN_Msk                   (0x1ULL << MITCMCR_ECC_EN_Pos)                      /*!< MITCMCR: ECC_EN Mask */

#define MITCMCR_EN_Pos                       0U                                                  /*!< MITCMCR: EN Position */
#define MITCMCR_EN_Msk                       (0x1ULL << MITCMCR_EN_Pos)                          /*!< MITCMCR: EN Mask */

/**
  \brief        Consortium definition for accessing protection area selection register(MDTCMCR, 0x7f8).
 */
typedef union {
    struct {
        unsigned long EN: 1;                             /*!< bit:     0  Data Tightly-Coupled Memory enable */
        unsigned long ECC_EN: 1;                         /*!< bit:     1  ecc_en */
        unsigned long Interleave: 1;                     /*!< bit:     2  Interleave */
        unsigned long _reserved1: 1;                     /*!< bit:     3  Reserved */
        unsigned long Size: 4;                           /*!< bit:  4..7  Size of DTCM */
        unsigned long _reserved2: 4;                     /*!< bit:  8..11 Reserved */
#if __riscv_xlen == 64
        unsigned long Base_Address: 52;                  /*!< bit: 12..63 Base address of DTCM */
#else
        unsigned long Base_Address: 20;                  /*!< bit: 12..31 Base address of DTCM */
#endif
    } b;                                                 /*!< Structure   Access by bit */
    unsigned long w;                                     /*!< Type        Access by whole register */
} MDTCMCR_Type;

#define MDTCMCR_Base_Address_Pos             12U                                                 /*!< MDTCMCR: Base_Address Position */
#define MDTCMCR_Base_Address_Msk             (0xfffffffffffffULL << MDTCMCR_Base_Address_Pos)    /*!< MDTCMCR: Base_Address Mask */

#define MDTCMCR_Size_Pos                     4U                                                  /*!< MDTCMCR: Size Position */
#define MDTCMCR_Size_Msk                     (0xfULL << MDTCMCR_Size_Pos)                        /*!< MDTCMCR: Size Mask */

#define MDTCMCR_INTERLEAVE_Pos               2U                                                  /*!< MDTCMCR: Interleave Position */
#define MDTCMCR_INTERLEAVE_Msk               (0x1ULL << MDTCMCR_INTERLEAVE_Pos)                  /*!< MDTCMCR: Interleave Mask */

#define MDTCMCR_ECC_EN_Pos                   1U                                                  /*!< MDTCMCR: ECC_EN Position */
#define MDTCMCR_ECC_EN_Msk                   (0x1ULL << MDTCMCR_ECC_EN_Pos)                      /*!< MDTCMCR: ECC_EN Mask */

#define MDTCMCR_EN_Pos                       0U                                                  /*!< MDTCMCR: EN Position */
#define MDTCMCR_EN_Msk                       (0x1ULL << MDTCMCR_EN_Pos)                          /*!< MDTCMCR: EN Mask */

/*@} end of group CSI_TCM_bitfield */

/**
  \brief        Enable ITCM
  \details      Turns on ITCM.
  */
__STATIC_INLINE void csi_itcm_enable (void)
{
    __set_MITCMCR(__get_MITCMCR() | MITCMCR_EN_Msk);
}

/**
  \brief        Enable DTCM
  \details      Turns on DTCM.
  */
__STATIC_INLINE void csi_dtcm_enable (void)
{
    __set_MDTCMCR(__get_MDTCMCR() | MDTCMCR_EN_Msk);
}

/**
  \brief        Disable ITCM
  \details      Turns off ITCM.
  */
__STATIC_INLINE void csi_itcm_disable (void)
{
    __set_MITCMCR(__get_MITCMCR() & (~MITCMCR_EN_Msk));
}

/**
  \brief        Disable DTCM
  \details      Turns off DTCM.
  */
__STATIC_INLINE void csi_dtcm_disable (void)
{
    __set_MDTCMCR(__get_MDTCMCR() & (~MDTCMCR_EN_Msk));
}

/**
  \brief        Get ITCM Size
  \details      Get ITCM Size.
  \return       ITCM size (bytes).
  */
__STATIC_INLINE uint32_t csi_itcm_get_size(void)
{
    MITCMCR_Type sizemask;
    uint32_t ret;

    sizemask.w = __get_MITCMCR();
    switch (sizemask.b.Size)
    {
#if __riscv_xlen == 64
        case 0x3: ret = 8 << 10; break;
        case 0x4: ret = 16 << 10; break;
        case 0x5: ret = 32 << 10; break;
        case 0x6: ret = 64 << 10; break;
        case 0x7: ret = 128 << 10; break;
        case 0x8: ret = 256 << 10; break;
        case 0x9: ret = 512 << 10; break;
        case 0xa: ret = 1024 << 10; break;
        default: ret = 0; break;
#else
        case 0x3: ret = 4 << 10; break;
        case 0x4: ret = 8 << 10; break;
        case 0x5: ret = 16 << 10; break;
        case 0x6: ret = 32 << 10; break;
        case 0x7: ret = 64 << 10; break;
        case 0x8: ret = 128 << 10; break;
        case 0x9: ret = 256 << 10; break;
        case 0xa: ret = 512 << 10; break;
        case 0xb: ret = 1 << 20; break;
        case 0xc: ret = 2 << 20; break;
        case 0xd: ret = 4 << 20; break;
        case 0xe: ret = 8 << 20; break;
        case 0xf: ret = 16 << 20; break;
        default: ret = 0; break;
#endif
    }
    return ret;
}

/**
  \brief        Get DTCM Size
  \details      Get DTCM Size.
  \return       DTCM size (bytes).
  */
__STATIC_INLINE uint32_t csi_dtcm_get_size(void)
{
    MDTCMCR_Type sizemask;
    uint32_t ret;

    sizemask.w = __get_MDTCMCR();
    switch (sizemask.b.Size)
    {
#if __riscv_xlen == 64
        case 0x3: ret = 8 << 10; break;
        case 0x4: ret = 16 << 10; break;
        case 0x5: ret = 32 << 10; break;
        case 0x6: ret = 64 << 10; break;
        case 0x8: ret = 128 << 10; break;
        case 0x9: ret = 256 << 10; break;
        case 0xa: ret = 512 << 10; break;
        case 0xb: ret = 1024 << 10; break;
        default:ret = 0; break;
#else
        case 0x3: ret = 4 << 10; break;
        case 0x4: ret = 8 << 10; break;
        case 0x5: ret = 16 << 10; break;
        case 0x6: ret = 32 << 10; break;
        case 0x7: ret = 64 << 10; break;
        case 0x8: ret = 128 << 10; break;
        case 0x9: ret = 256 << 10; break;
        case 0xa: ret = 512 << 10; break;
        case 0xb: ret = 1 << 20; break;
        case 0xc: ret = 2 << 20; break;
        case 0xd: ret = 4 << 20; break;
        case 0xe: ret = 8 << 20; break;
        case 0xf: ret = 16 << 20; break;
        default: ret = 0; break;
#endif
    }
    return ret;
}

/**
  \brief        Set ITCM Base Address
  \details      Set ITCM Base Address.
  \param [in]   base_addr   ITCM base address.
  */
__STATIC_INLINE void csi_itcm_set_base_addr(unsigned long base_addr)
{
#if __riscv_xlen == 32
    base_addr = base_addr >> 12;
#endif
    __set_MITCMCR((__get_MITCMCR() & (~MITCMCR_Base_Address_Msk)) | (base_addr << MITCMCR_Base_Address_Pos));
}

/**
  \brief        Set DTCM Base Address
  \details      Set DTCM Base Address.
  \param [in]   base_addr   DTCM base address.
  */
__STATIC_INLINE void csi_dtcm_set_base_addr(unsigned long base_addr)
{
#if __riscv_xlen == 32
    base_addr = base_addr >> 12;
#endif
    __set_MDTCMCR((__get_MDTCMCR() & (~MDTCMCR_Base_Address_Msk)) | (base_addr << MDTCMCR_Base_Address_Pos));
}

/*@} end of CSI_Core_TCMFunctions */

/* ##########################  ECC functions  #################################### */

/**
  \brief        Enable ITCM-ECC
  \details      Turns on ITCM-ECC.
  */
__STATIC_INLINE void csi_itcm_ecc_enable (void)
{
#if __TCM_ECC_SUPPORT
    __set_MITCMCR(__get_MITCMCR() | MITCMCR_ECC_EN_Msk);
#endif
}

/**
  \brief        Disable ITCM-ECC
  \details      Turns off ITCM-ECC.
  */
__STATIC_INLINE void csi_itcm_ecc_disable (void)
{
#if __TCM_ECC_SUPPORT
    __set_MITCMCR(__get_MITCMCR() & (~MITCMCR_ECC_EN_Msk));
#endif
}

/**
  \brief        Enable DTCM-ECC
  \details      Turns on DTCM-ECC.
  */
__STATIC_INLINE void csi_dtcm_ecc_enable (void)
{
#if __TCM_ECC_SUPPORT
    __set_MDTCMCR(__get_MDTCMCR() | MDTCMCR_ECC_EN_Msk);
#endif
}

/**
  \brief        Disable DTCM-ECC
  \details      Turns off DTCM-ECC.
  */
__STATIC_INLINE void csi_dtcm_ecc_disable (void)
{
#if __TCM_ECC_SUPPORT
    __set_MDTCMCR(__get_MDTCMCR() & (~MDTCMCR_ECC_EN_Msk));
#endif
}

/*@} end of CSI_Core_ECCFunctions */

#endif
#endif
