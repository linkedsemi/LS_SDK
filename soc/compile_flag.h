#ifndef COMPILE_FLAG_H_
#define COMPILE_FLAG_H_
#include <stdint.h>
#if (ROM_CODE==1||(defined(FLASH_PROG_ALGO)&&defined(LE501X)))
#define ROM_SYMBOL
#else 
#define ROM_SYMBOL __attribute__((weak))
#endif

#if defined(__ICCARM__)
#define __XIP_BANNED_LABEL "__iar_init$$done"
#else
#define __XIP_BANNED_LABEL ""
#endif

#if (ROM_CODE==1 || BOOT_RAM==1)
#define XIP_BANNED_FUNC(__NAME,...) __NAME(__VA_ARGS__)
#if defined(BOOT_ROM)
#define LL_PKT_ISR 
#else
#define LL_PKT_ISR __attribute((section(".ll_pkt_isr")))
#endif
#else
#define XIP_BANNED_FUNC(__NAME,...) __attribute__((section(__XIP_BANNED_LABEL".xip_banned."#__NAME))) __NAME(__VA_ARGS__)
#define LL_PKT_ISR 
#endif

#define LL_PKT_ISR_DATA __attribute((section(".ll_pkt_isr_data")))
#define LL_EVT_ISR
#define RESET_RETAIN __attribute__((section(".reset_retain")))
#define NOINLINE __attribute__((noinline))
#if defined(__CC_ARM)
#define _Static_assert(expr, msg) int __static_assert(int static_assert_failed[(expr)?1:-1])
extern const uint32_t Image$$RESET_RETAIN_DATA$$Base;
#define RESET_RETAIN_BASE (&Image$$RESET_RETAIN_DATA$$Base)
extern const uint32_t Image$$RESET_RETAIN_DATA$$Limit;
#define RESET_RETAIN_END (&Image$$RESET_RETAIN_DATA$$Limit)
#elif defined(__GNUC__)
extern uint32_t reset_retain_start;
#define RESET_RETAIN_BASE   (&(reset_retain_start))
extern uint32_t reset_retain_end;
#define RESET_RETAIN_END   (&(reset_retain_end))
#elif defined(__ICCARM__)
#pragma section="RESET_RETAIN"
#define RESET_RETAIN_BASE __section_begin("RESET_RETAIN")
#define RESET_RETAIN_END __section_end("RESET_RETAIN")
#endif

#endif

