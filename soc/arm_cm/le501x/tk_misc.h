#ifndef __TK_MISC_H
#define __TK_MISC_H

#ifdef __cplusplus
extern "C" {
#endif

#define IS_TK_SCANCFG_NPRR(NPRR) (((NPRR) >= 0U) && ((NPRR) <= 7))
#define IS_TK_SCANCFG_DNPR(DNPR) (((DNPR) == TK_DNPR_DISABLE) || \
                                  ((DNPR) == TK_DNPR_ENABLE))
#define IS_TK_SCANCFG_MULTION(MULTION) (((MULTION) == TK_MULTION_DISABLE) || \
                                        ((MULTION) == TK_MULTION_ENABLE))
#define IS_TK_DEBOUNCE(DEBOUNCE) (((DEBOUNCE) >= 0U) && ((DEBOUNCE) <= 255U))
#define IS_TK_CHANNEL_EN(CHANNELEN) (((CHANNELEN)&0x0000U) == 0U)
#define IS_TK_GBSEN(GBSEN) (((GBSEN) >= 0U) && ((GBSEN) <= 255U))
#define IS_TK_SCANCR_LP(LP) (((LP) == TK_LP_DISABLE) || \
                             ((LP) == TK_LP_ENABLE))
#define IS_TK_ICOMGS(ICOMGS) (((ICOMGS)&0x00U) == 0U)
#define IS_TK_CDCFSWDIV(CDCFSWDIV) (((CDCFSWDIV)&0x00U) == 0U)
#define IS_TK_LOW_POWER_SCAN_PERIOD(LOWPOWERSCANPERIOD) (((LOWPOWERSCANPERIOD) >= 0U) && ((LOWPOWERSCANPERIOD) <= 2U))
#define IS_TK_KEY_DEBOUNCE_COUNT(KEYDEBOUNCECOUNT) (((KEYDEBOUNCECOUNT) > 0U) && ((KEYDEBOUNCECOUNT) <= 3U))
#define IS_TK_LP_DELAY(LPDELAY) (((LPDELAY) >= 0U) && ((LPDELAY) <= 255U))
#define IS_TK_SCAN_PERIOD(SCANPERIOD) (((SCANPERIOD) > 0U) && ((SCANPERIOD) <= 3U))
#define IS_TK_GSMASK(GSMASK) (((GSMASK)&0x0000U) == 0U)
#define IS_TK_LSENSEGS(LSENSEGS) (((LSENSEGS)&0x00U) == 0U)

#ifdef __cplusplus
}
#endif

#endif
