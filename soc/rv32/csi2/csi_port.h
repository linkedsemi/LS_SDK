#ifndef __CSI_PORT_H

#ifdef __cplusplus
extern "C" {
#endif

/* MEXSTATUS Register Definitions */
#define MEXSTATUS_RESET_Pos                           0U
#define MEXSTATUS_RESET_Msk                      (0x3UL << MEXSTATUS_RESET_Pos)                                             /*!< MEXSTATUS: RESET Position */
#define MEXSTATUS_SLEEP_Pos                           2U
#define MEXSTATUS_SLEEP_Msk                      (0x3UL << MEXSTATUS_SLEEP_Pos)                                             /*!< MEXSTATUS: RESET Position */
/*@} end of group CSI_MEXSTATUS */

/**
  \brief   CPU System Reset
  \details Triggle CPU System Reset
  */
__STATIC_INLINE void csi_system_reset (void)
{
    uint32_t mexstatus;
    mexstatus = __get_MEXSTATUS();
    mexstatus &= (~(MEXSTATUS_RESET_Msk));
    mexstatus |= (uint32_t)(0x2 << MEXSTATUS_RESET_Pos);
    __set_MEXSTATUS(mexstatus);
}

/**
  \brief   CPU Core Reset
  \details Triggle CPU Core Reset
  */
__STATIC_INLINE void csi_core_reset (void)
{
    uint32_t mexstatus;
    mexstatus = __get_MEXSTATUS();
    mexstatus &= (~(MEXSTATUS_RESET_Msk));
    mexstatus |= (uint32_t)(0x1 << MEXSTATUS_RESET_Pos);
    __set_MEXSTATUS(mexstatus);
}

#ifdef __cplusplus
}
#endif

#endif /* __CSI_PORT_H */
