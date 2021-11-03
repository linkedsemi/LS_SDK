#ifndef COMPILE_FLAG_H_
#define COMPILE_FLAG_H_
#include <stdint.h>
#if (ROM_CODE==1 || BOOT_RAM==1)
#define ROM_SYMBOL
#define XIP_BANNED 
#if defined(BOOT_ROM)
#define LL_PKT_ISR 
#else
#define LL_PKT_ISR __attribute((section(".ll_pkt_isr")))
#endif
#else
#define ROM_SYMBOL __attribute__((weak))
#ifdef FLASH_PROG_ALGO
#define XIP_BANNED
#else
#define XIP_BANNED __attribute__((section(".xip_banned")))
#endif
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
#endif

#endif

