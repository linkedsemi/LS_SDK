 /*
 * Copyright (C) 2024 Alibaba Group Holding Limited
 */

#ifndef __PERF_EVENT_LIST_H__
#define __PERF_EVENT_LIST_H__

#include <stdint.h>

/* Auto-generated on 2026-02-09 17:39:34 */
/* Total events: 103 */

/* Domain Definitions */
#define PERF_DOMAIN_HARDWARE 0x00
#define PERF_DOMAIN_SOFTWARE 0x01
#define PERF_DOMAIN_FUNCTION_TRACE 0x02
#define PERF_DOMAIN_HOOK 0x03

/* Event Definitions */
#define PERF_HARDWARE_CACHE_L1I_RD_ACCESS            0x00000001  /* hardware::cache.l1i.rd.access */
#define PERF_HARDWARE_CACHE_L1I_RD_MISS              0x00000002  /* hardware::cache.l1i.rd.miss */
#define PERF_HARDWARE_TLB_L1I_MISS                   0x00000003  /* hardware::tlb.l1i.miss */
#define PERF_HARDWARE_TLB_JTLB_MISS                  0x00000005  /* hardware::tlb.jtlb.miss */
#define PERF_HARDWARE_INST_COND_BRANCH_MISPRED       0x00000006  /* hardware::inst.cond_branch.mispred */
#define PERF_HARDWARE_INST_COND_BRANCH               0x00000007  /* hardware::inst.cond_branch */
#define PERF_HARDWARE_INST_INDIRECT_BRANCH_MISPRED   0x00000008  /* hardware::inst.indirect_branch.mispred */
#define PERF_HARDWARE_INST_INDIRECT_BRANCH           0x00000009  /* hardware::inst.indirect_branch */
#define PERF_HARDWARE_INST_STORE                     0x0000000B  /* hardware::inst.store */
#define PERF_HARDWARE_CACHE_L1D_RD_ACCESS            0x0000000C  /* hardware::cache.l1d.rd.access */
#define PERF_HARDWARE_CACHE_L1D_RD_MISS              0x0000000D  /* hardware::cache.l1d.rd.miss */
#define PERF_HARDWARE_CACHE_L1D_WR_ACCESS            0x0000000E  /* hardware::cache.l1d.wr.access */
#define PERF_HARDWARE_CACHE_L1D_WR_MISS              0x0000000F  /* hardware::cache.l1d.wr.miss */
#define PERF_HARDWARE_INST_ISSUE                     0x00000016  /* hardware::inst.issue */
#define PERF_HARDWARE_INST_IFU_BRANCH_TARGET_MISPRED 0x0000001B  /* hardware::inst.ifu_branch_target.mispred */
#define PERF_HARDWARE_INST_IFU_BRANCH_TARGET         0x0000001C  /* hardware::inst.ifu_branch_target */
#define PERF_HARDWARE_INST_ALU                       0x0000001D  /* hardware::inst.alu */
#define PERF_HARDWARE_INST_VECTOR_SIMD               0x0000001F  /* hardware::inst.vector_simd */
#define PERF_HARDWARE_INST_CSR                       0x00000020  /* hardware::inst.csr */
#define PERF_HARDWARE_INST_ATOMIC                    0x00000021  /* hardware::inst.atomic */
#define PERF_HARDWARE_INTERRUPT_NUM                  0x00000023  /* hardware::interrupt.num */
#define PERF_HARDWARE_INST_ECALL                     0x00000025  /* hardware::inst.ecall */
#define PERF_HARDWARE_INST_LONG_JUMP                 0x00000026  /* hardware::inst.long_jump */
#define PERF_HARDWARE_STALL_FRONTEND                 0x00000027  /* hardware::stall.frontend */
#define PERF_HARDWARE_STALL_BACKEND                  0x00000028  /* hardware::stall.backend */
#define PERF_HARDWARE_STALL_SYNC                     0x00000029  /* hardware::stall.sync */
#define PERF_HARDWARE_INST_FP                        0x0000002A  /* hardware::inst.fp */
#define PERF_HARDWARE_CYCLES_M_MODE                  0x0000002B  /* hardware::cycles.m_mode */
#define PERF_HARDWARE_CYCLES_S_MODE                  0x0000002C  /* hardware::cycles.s_mode */
#define PERF_HARDWARE_CYCLES_U_MODE                  0x0000002D  /* hardware::cycles.u_mode */
#define PERF_HARDWARE_EXCEPTION_NUM                  0x0000002E  /* hardware::exception.num */
#define PERF_HARDWARE_PIPELINE_FLUSH                 0x0000002F  /* hardware::pipeline.flush */
#define PERF_HARDWARE_INST_LOAD                      0x00000030  /* hardware::inst.load */
#define PERF_HARDWARE_INST_FUSED                     0x00000031  /* hardware::inst.fused */
#define PERF_HARDWARE_INST_MULT                      0x00000032  /* hardware::inst.mult */
#define PERF_HARDWARE_INST_DIV                       0x00000033  /* hardware::inst.div */
#define PERF_HARDWARE_INST_MULT_INNER_FORWARD        0x00000034  /* hardware::inst.mult_inner_forward */
#define PERF_HARDWARE_INST_DIV_BUFFER_HIT            0x00000035  /* hardware::inst.div_buffer_hit */
#define PERF_HARDWARE_INST_BRANCH                    0x00000036  /* hardware::inst.branch */
#define PERF_HARDWARE_INST_UNCOND_BRANCH             0x00000037  /* hardware::inst.uncond_branch */
#define PERF_HARDWARE_INST_BRANCH_MISPRED            0x00000038  /* hardware::inst.branch.mispred */
#define PERF_HARDWARE_INST_UNCOND_BRANCH_MISPRED     0x00000039  /* hardware::inst.uncond_branch.mispred */
#define PERF_HARDWARE_INST_TAKEN_BRANCH_MISPRED      0x0000003A  /* hardware::inst.taken_branch.mispred */
#define PERF_HARDWARE_INST_TAKEN_COND_BRANCH         0x0000003B  /* hardware::inst.taken_cond_branch */
#define PERF_HARDWARE_INST_TAKEN_COND_BRANCH_MISPRED 0x0000003C  /* hardware::inst.taken_cond_branch.mispred */
#define PERF_HARDWARE_INST_UNALIGN_LOAD              0x0000003D  /* hardware::inst.unalign_load */
#define PERF_HARDWARE_INST_UNALIGN_STORE             0x0000003E  /* hardware::inst.unalign_store */
#define PERF_HARDWARE_INST_LR                        0x0000003F  /* hardware::inst.lr */
#define PERF_HARDWARE_INST_SC                        0x00000040  /* hardware::inst.sc */
#define PERF_HARDWARE_INST_AMO                       0x00000041  /* hardware::inst.amo */
#define PERF_HARDWARE_INST_BARRIER                   0x00000042  /* hardware::inst.barrier */
#define PERF_HARDWARE_INST_SC_FAILED                 0x00000043  /* hardware::inst.sc.failed */
#define PERF_HARDWARE_BUS_BARRIER                    0x00000044  /* hardware::bus.barrier */
#define PERF_HARDWARE_INST_FP_DIV                    0x00000045  /* hardware::inst.fp_div */
#define PERF_HARDWARE_INST_FP_LOAD                   0x00000046  /* hardware::inst.fp_load */
#define PERF_HARDWARE_INST_FP_STORE                  0x00000047  /* hardware::inst.fp_store */
#define PERF_HARDWARE_INST_VECTOR_DIV                0x00000048  /* hardware::inst.vector_div */
#define PERF_HARDWARE_INST_VECTOR_LOAD               0x00000049  /* hardware::inst.vector_load */
#define PERF_HARDWARE_INST_VECTOR_STORE              0x0000004A  /* hardware::inst.vector_store */
#define PERF_HARDWARE_INST_VECTOR_MICRO_OP           0x0000004B  /* hardware::inst.vector_micro_op */
#define PERF_HARDWARE_INTERRUPT_ECC                  0x0000004C  /* hardware::interrupt.ecc */
#define PERF_HARDWARE_INTERRUPT_ASYNC_ABORT          0x0000004D  /* hardware::interrupt.async_abort */
#define PERF_HARDWARE_STALL_IF                       0x0000004E  /* hardware::stall.if */
#define PERF_HARDWARE_STALL_IP                       0x0000004F  /* hardware::stall.ip */
#define PERF_HARDWARE_STALL_IB                       0x00000050  /* hardware::stall.ib */
#define PERF_HARDWARE_STALL_IF_REFILL                0x00000051  /* hardware::stall.if_refill */
#define PERF_HARDWARE_STALL_IF_MMU                   0x00000052  /* hardware::stall.if_mmu */
#define PERF_HARDWARE_STALL_IB_MISPRED               0x00000053  /* hardware::stall.ib_mispred */
#define PERF_HARDWARE_STALL_IB_FIFO                  0x00000054  /* hardware::stall.ib_fifo */
#define PERF_HARDWARE_STALL_IB_IND_BTB_RD            0x00000055  /* hardware::stall.ib_ind_btb_rd */
#define PERF_HARDWARE_STALL_IB_VSETVL                0x00000056  /* hardware::stall.ib_vsetvl */
#define PERF_HARDWARE_STALL_ID                       0x00000057  /* hardware::stall.id */
#define PERF_HARDWARE_STALL_RF                       0x00000058  /* hardware::stall.rf */
#define PERF_HARDWARE_STALL_EU                       0x00000059  /* hardware::stall.eu */
#define PERF_HARDWARE_PIPELINE_ID_INST_PIPEDOWN      0x0000005A  /* hardware::pipeline.id_inst_pipedown */
#define PERF_HARDWARE_PIPELINE_RF_INST_PIPEDOWN      0x0000005B  /* hardware::pipeline.rf_inst_pipedown */
#define PERF_HARDWARE_PIPELINE_ID_ONE_INST_PIPEDOWN  0x0000005C  /* hardware::pipeline.id_one_inst_pipedown */
#define PERF_HARDWARE_STALL_ID_CSR_BEFORE_FENCE      0x0000005D  /* hardware::stall.id_csr_before_fence */
#define PERF_HARDWARE_STALL_ID_VSETVL_FOF            0x0000005E  /* hardware::stall.id_vsetvl_fof */
#define PERF_HARDWARE_STALL_ID_FLUSH                 0x0000005F  /* hardware::stall.id_flush */
#define PERF_HARDWARE_STALL_ID_MISPRED               0x00000060  /* hardware::stall.id_mispred */
#define PERF_HARDWARE_STALL_ID_IID_NOT_VLD           0x00000061  /* hardware::stall.id_iid_not_vld */
#define PERF_HARDWARE_PIPELINE_RF_ONE_INST_PIPEDOWN  0x00000062  /* hardware::pipeline.rf_one_inst_pipedown */
#define PERF_HARDWARE_STALL_RF_RAW                   0x00000063  /* hardware::stall.rf_raw */
#define PERF_HARDWARE_STALL_RF_WAW                   0x00000064  /* hardware::stall.rf_waw */
#define PERF_HARDWARE_STALL_RF_STRUCTURE             0x00000065  /* hardware::stall.rf_structure */
#define PERF_HARDWARE_STALL_RF_CSR_AFTER_FENCE       0x00000066  /* hardware::stall.rf_csr_after_fence */
#define PERF_HARDWARE_STALL_EU_IU_FULL               0x00000067  /* hardware::stall.eu_iu_full */
#define PERF_HARDWARE_STALL_EU_IU_CONTROL_FULL       0x00000068  /* hardware::stall.eu_iu_control_full */
#define PERF_HARDWARE_STALL_EU_CP0_FULL              0x00000069  /* hardware::stall.eu_cp0_full */
#define PERF_HARDWARE_STALL_EU_LSU_LOAD_FULL         0x0000006A  /* hardware::stall.eu_lsu_load_full */
#define PERF_HARDWARE_STALL_EU_LSU_STORE_FULL        0x0000006B  /* hardware::stall.eu_lsu_store_full */
#define PERF_HARDWARE_STALL_EU_VFPU_FULL             0x0000006C  /* hardware::stall.eu_vfpu_full */
#define PERF_HARDWARE_STALL_EU_BJU_FULL              0x0000006D  /* hardware::stall.eu_bju_full */
#define PERF_HARDWARE_STALL_IU_DP_PIPE0              0x0000006E  /* hardware::stall.iu_dp_pipe0 */
#define PERF_HARDWARE_STALL_IU_MULT_PIPE0            0x0000006F  /* hardware::stall.iu_mult_pipe0 */
#define PERF_HARDWARE_STALL_IU_DIV_EX1_PIPE0         0x00000070  /* hardware::stall.iu_div_ex1_pipe0 */
#define PERF_HARDWARE_STALL_IU_DP_PIPE1              0x00000071  /* hardware::stall.iu_dp_pipe1 */
#define PERF_HARDWARE_CYCLES_HART                    0x00001000  /* hardware::cycles.hart */
#define PERF_HARDWARE_INST_RET                       0x00001001  /* hardware::inst.ret */
#define PERF_HOOK_EXAMPLE_SAMPLING_HOOK1             0x03000001  /* hook::example_sampling_hook1 */
#define PERF_HOOK_EXAMPLE_SAMPLING_HOOK2             0x03000002  /* hook::example_sampling_hook2 */
#define PERF_HOOK_TICKS                              0x03000003  /* hook::ticks */

#endif /* __PERF_EVENT_LIST_H__ */
