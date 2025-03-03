#ifndef __I3C_MISC_H
#define __I3C_MISC_H

#ifdef __cplusplus
extern "C" {
#endif


/*******************  Bit definition for I3C_CR register  *********************/
#define I3C_CR_DCNT                         I3C_CR_DCNT_MASK                      /*!< Data Byte Count */
#define I3C_CR_RNW                          I3C_CR_RNW_MASK                       /*!< Read Not Write */
#define I3C_CR_CCC                          I3C_CR_CCC_MASK                       /*!< 8-Bit CCC code */
#define I3C_CR_ADD                          I3C_CR_ADD_MASK                       /*!< Target Address */
#define I3C_CR_MTYPE                        I3C_CR_MTYPE_MASK                     /*!< Message Type */  
#define I3C_CR_MTYPE_0                      (0x1UL << I3C_CR_MTYPE_POS)             /*!< 0x08000000 */
#define I3C_CR_MTYPE_1                      (0x2UL << I3C_CR_MTYPE_POS)             /*!< 0x10000000 */
#define I3C_CR_MTYPE_2                      (0x4UL << I3C_CR_MTYPE_POS)             /*!< 0x20000000 */
#define I3C_CR_MTYPE_3                      (0x8UL << I3C_CR_MTYPE_POS)
#define I3C_CR_MEND                         I3C_CR_MEND_MASK                      /*!< Message End */ 

/*******************  Bit definition for I3C_CFGR register  *******************/
#define I3C_CFGR_EN                         I3C_CFGR_MASTER_EN_MASK                         /*!< Peripheral Enable */
// #define I3C_CFGR_CRINIT                     I3C_CFGR_CRINIT_MASK                  /*!< Peripheral Init mode (Target/Controller) */
#define I3C_CFGR_NOARBH                     I3C_CFGR_NOARBH_MASK                  /*!< No Arbitration Header (7'h7E)*/
#define I3C_CFGR_RSTPTRN                    I3C_CFGR_RSTPTRN_MASK                 /*!< Reset Pattern enable */
#define I3C_CFGR_EXITPTRN                   I3C_CFGR_EXITPTRN_MASK                /*!< Exit Pattern enable */
#define I3C_CFGR_HKSDAEN                    I3C_CFGR_HKSDAEN_MASK                 /*!< High-Keeper on SDA Enable */
#define I3C_CFGR_HJACK                      I3C_CFGR_HJACK_MASK                   /*!< Hot Join Acknowledgment */
#define I3C_CFGR_RXDMAEN                    I3C_CFGR_RXDMAEN_MASK                 /*!< RX FIFO DMA mode Enable */
#define I3C_CFGR_RXFLUSH                    I3C_CFGR_RXFLUSH_MASK                 /*!< RX FIFO Flush */
#define I3C_CFGR_RXTHRES                    I3C_CFGR_RXTHRES_MASK                 /*!< RX FIFO Threshold */
#define I3C_CFGR_TXDMAEN                    I3C_CFGR_TXDMAEN_MASK                 /*!< TX FIFO DMA mode Enable */
#define I3C_CFGR_TXFLUSH                    I3C_CFGR_TXFLUSH_MASK                 /*!< TX FIFO Flush */
#define I3C_CFGR_TXTHRES                    I3C_CFGR_TXTHRES_MASK                 /*!< TX FIFO Threshold */
// #define I3C_CFGR_SDMAEN                     I3C_CFGR_SDMAEN_MASK                  /*!< Status FIFO DMA mode Enable */
#define I3C_CFGR_SFLUSH                     I3C_CFGR_SFLUSH_MASK                  /*!< Status FIFO Flush */
#define I3C_CFGR_SMODE                      I3C_CFGR_SMODE_MASK                   /*!< Status FIFO mode Enable */
// #define I3C_CFGR_TMODE                      I3C_CFGR_TMODE_MASK                   /*!< Control FIFO mode Enable */
#define I3C_CFGR_CDMAEN                     I3C_CFGR_CDMAEN_MASK                  /*!< Control FIFO DMA mode Enable */
#define I3C_CFGR_CFLUSH                     I3C_CFGR_CFLUSH_MASK                  /*!< Control FIFO Flush */
#define I3C_CFGR_TSFSET                     I3C_CFGR_TSFSET_MASK                  /*!< Transfer Set */

/*******************  Bit definition for I3C_RDR register  ********************/
#define I3C_RDR_RDB0                        I3C_RDR_R_DATA_MASK                        /*!< Receive Data Byte */

/*******************  Bit definition for I3C_TDR register  ********************/
#define I3C_TDR_TDB0                        I3C_TDR_W_DATA_MASK                        /*!< Transmit Data Byte */


/*******************  Bit definition for I3C_IBIDR register  ******************/
#define I3C_IBIDR_IBIDBx                    (0xFFFFFFFFUL << I3C_IBIDR_IBIDB0_POS)/*!< IBI Data Byte, full double word */
#define I3C_IBIDR_IBIDB0                    I3C_IBIDR_IBIDB0_MASK                 /*!< IBI Data Byte 0 */
#define I3C_IBIDR_IBIDB1                    I3C_IBIDR_IBIDB1_MASK                 /*!< IBI Data Byte 1 */
#define I3C_IBIDR_IBIDB2                    I3C_IBIDR_IBIDB2_MASK                 /*!< IBI Data Byte 2 */
#define I3C_IBIDR_IBIDB3                    I3C_IBIDR_IBIDB3_MASK                 /*!< IBI Data Byte 3 */


/*******************  Bit definition for I3C_SR register  *********************/
#define I3C_SR_MID                          I3C_SR_MID_MASK                       /*!< Message Identifier */
#define I3C_SR_DIR                          I3C_SR_DIR_MASK                       /*!< Message Direction */
#define I3C_SR_ABT                          I3C_SR_ABT_MASK                       /*!< Target Abort Indication */
// #define I3C_SR_RADDR               I3C_SR_RADDR_MASK
// #define I3C_SR_IBIRDCNT            I3C_SR_IBIRDCNT_MASK
#define I3C_SR_XDCNT                        I3C_SR_XDCNT_MASK                     /*!< Transfer Data Byte Count status */

/*******************  Bit definition for I3C_SER register  ********************/
#define I3C_SER_CODERR                      I3C_SER_CODERR_MASK                   /*!< Protocol Error Code */
#define I3C_SER_PERR                        I3C_SER_PERR_MASK                     /*!< Protocol Error */
#define I3C_SER_STALL                       I3C_SER_STALL_MASK                    /*!< SCL Stall Error */
#define I3C_SER_DOVR                        I3C_SER_DOVR_MASK                     /*!< RX/TX FIFO Overrun */
#define I3C_SER_COVR                        I3C_SER_COVR_MASK                     /*!< Status/Control FIFO Overrun */
#define I3C_SER_ANACK                       I3C_SER_ANACK_MASK                    /*!< Address Not Acknowledged */
#define I3C_SER_DNACK                       I3C_SER_DNACK_MASK                    /*!< Data Not Acknowledged */
#define I3C_SER_DERR                        I3C_SER_DERR_MASK                     /*!< Data Error during the controller-role hand-off procedure */

/*******************  Bit definition for I3C_EVR register  ********************/
#define I3C_EVR_CFEF                        I3C_EVR_CFEF_MASK                     /*!< Control FIFO Empty Flag */
#define I3C_EVR_TXFEF                       I3C_EVR_TXFEF_MASK                    /*!< TX FIFO Empty Flag */
#define I3C_EVR_SFNEF                       I3C_EVR_SFNEF_MASK                    /*!< TX FIFO Empty Flag */
#define I3C_EVR_CFNFF                       I3C_EVR_CFNFF_MASK                    /*!< Control FIFO Not Full Flag */
#define I3C_EVR_TXFNFF                      I3C_EVR_TXFNFF_MASK                   /*!< TX FIFO Not Full Flag */
#define I3C_EVR_RXFNEF                      I3C_EVR_RXFNEF_MASK                   /*!< RX FIFO Not Empty Flag */
#define I3C_EVR_FCF                         I3C_EVR_FCF_MASK                      /*!< Frame Complete Flag */
#define I3C_EVR_ERRF                        I3C_EVR_ERRF_MASK                     /*!< Error Flag */
#define I3C_EVR_IBIF                        I3C_EVR_IBIF_MASK                     /*!< IBI Flag */
#define I3C_EVR_CRF                         I3C_EVR_CRF_MASK                      /*!< Controller-role Request Flag */
#define I3C_EVR_HJF                         I3C_EVR_HJF_MASK                      /*!< Hot Join Flag */
#define I3C_EVR_RXTGTENDF                   I3C_EVR_RXTGTENDF_MASK                     /*!< Reception Target End Flag */


/*******************  Bit definition for I3C_IER register  ********************/
#define I3C_IER_HJIE                        I3C_IER_HJIE_MASK                     /*!< Hot Join Interrupt Enable */
#define I3C_IER_CRIE                        I3C_IER_CRIE_MASK                     /*!< Controller-role Interrupt Enable */
#define I3C_IER_IBIIE                       I3C_IER_IBIIE_MASK                    /*!< IBI Interrupt Enable */
#define I3C_IER_ERRIE                       I3C_IER_ERRIE_MASK                    /*!< Error Interrupt Enable */
#define I3C_IER_RXTGTENDIE                  I3C_IER_RXTGTENDIE_MASK               /*!< Reception Target End Interrupt Enable */
#define I3C_IER_FCIE                        I3C_IER_FCIE_MASK                     /*!< Frame Complete Interrupt Enable */
#define I3C_IER_RXFNEIE                     I3C_IER_RXFNEIE_MASK                  /*!< RX FIFO Not Empty Interrupt Enable */
#define I3C_IER_TXFNFIE                     I3C_IER_TXFNFIE_MASK                  /*!< TX FIFO Not Full Interrupt Enable */
#define I3C_IER_CFNFIE                      I3C_IER_CFNFIE_MASK                   /*!< Control FIFO Not Full Interrupt Enable */
#define I3C_IER_SFNEIE                      I3C_IER_SFNEIE_MASK                   /*!< Status FIFO Not Empty Interrupt Enable */


/*******************  Bit definition for I3C_CEVR register  *******************/
#define I3C_CEVR_CHJF                        I3C_IER_HJIE_MASK
#define I3C_CEVR_CCRF                        I3C_IER_CRIE_MASK
#define I3C_CEVR_CIBIF                       I3C_IER_IBIIE_MASK
#define I3C_CEVR_CERRF                       I3C_IER_ERRIE_MASK
#define I3C_CEVR_CRXTGTENDF                  I3C_IER_RXTGTENDIE_MASK
#define I3C_CEVR_CFCF                        I3C_IER_FCIE_MASK
#define I3C_CEVR_CRXFNEF                     I3C_IER_RXFNEIE_MASK
#define I3C_CEVR_CTXFNFF                     I3C_IER_TXFNFIE_MASK
#define I3C_CEVR_CCFNFF                      I3C_IER_CFNFIE_MASK

/******************  Bit definition for I3C_DEVR0 register  *******************/
//wait for update


/*******************  Bit definition for I3C_RMR register  ********************/
#define I3C_RMR_IBIRDCNT_Pos                (0U)
#define I3C_RMR_IBIRDCNT_Msk                (0x7UL << I3C_RMR_IBIRDCNT_Pos)         /*!< 0x00000007 */
#define I3C_RMR_IBIRDCNT                    I3C_RMR_IBIRDCNT_Msk                    /*!< Data Count when reading IBI data */
#define I3C_RMR_RCODE_Pos                   (8U)
#define I3C_RMR_RCODE_Msk                   (0xFFUL << I3C_RMR_RCODE_Pos)           /*!< 0x0000FF00 */
#define I3C_RMR_RCODE                       I3C_RMR_RCODE_Msk                       /*!< CCC code of received command */
#define I3C_RMR_RADD_Pos                    (17U)
#define I3C_RMR_RADD_Msk                    (0x7FUL << I3C_RMR_RADD_Pos)            /*!< 0x00FE0000 */
#define I3C_RMR_RADD                        I3C_RMR_RADD_Msk                        /*!< Target Address Received during accepted IBI or Controller-role request */


#define I3C_CR_MEND                         I3C_CR_MEND_MASK
#define I3C_CR_MTYPE                        I3C_CR_MTYPE_MASK
#define I3C_CR_CCC                          I3C_CR_CCC_MASK
#define I3C_CR_ADDR                         I3C_CR_ADDR_MASK
#define I3C_CR_RNW                          I3C_CR_RNW_MASK
#define I3C_CR_DCNT                         I3C_CR_DCNT_MASK


/******************  Bit definition for I3C_DEVRX register  *******************/
#define I3C_DEVRX_DA                        I3C_DEVRX_DA_MASK                          /*!< Dynamic Address Target x */
#define I3C_DEVRX_IBIACK                    I3C_DEVRX_IBIACK_MASK                      /*!< IBI Acknowledge from Target x */
#define I3C_DEVRX_CRACK                     I3C_DEVRX_CRACK_MASK                       /*!< Controller-role Acknowledge from Target x */
#define I3C_DEVRX_IBIDEN                    I3C_DEVRX_IBIDEN_MASK                      /*!< IBI Additional Data Enable */
#define I3C_DEVRX_SUSP                      I3C_DEVRX_SUSP_MASK                        /*!< Suspended Transfer */
#define I3C_DEVRX_DIS                       I3C_DEVRX_DIS_MASK                         /*!< Disable Register access */


/****************  Bit definition for I3C_TIMINGR0 register  ******************/
#define I3C_TIMINGR0_SCLL_PP                I3C_TIMINGR0_SCLL_PP_MASK             /*!< SCL Low duration during I3C Push-Pull phases */
#define I3C_TIMINGR0_SCLH_I3C               I3C_TIMINGR0_SCLH_I3C_MASK            /*!< SCL High duration during I3C Open-drain and Push-Pull phases */
#define I3C_TIMINGR0_SCLL_OD                I3C_TIMINGR0_SCLL_OD_MASK             /*!< SCL Low duration during  I3C Open-drain phases and I2C transfer */
#define I3C_TIMINGR0_SCLH_I2C               I3C_TIMINGR0_SCLH_I2C_MASK            /*!< SCL High duration during I2C transfer */

/****************  Bit definition for I3C_TIMINGR1 register  ******************/
#define I3C_TIMINGR1_AVAL                   I3C_TIMINGR1_AVAL_MASK                /*!< Timing for I3C Bus Idle or Available condition */
#define I3C_TIMINGR1_ASNCR                  I3C_TIMINGR1_ASNCR_MASK               /*!< Activity State of the New Controller */
#define I3C_TIMINGR1_ASNCR_0                (0x1UL << I3C_TIMINGR1_ASNCR_POS)       /*!< 0x00000100 */
#define I3C_TIMINGR1_ASNCR_1                (0x2UL << I3C_TIMINGR1_ASNCR_POS)       /*!< 0x00000200 */
#define I3C_TIMINGR1_FREE                   I3C_TIMINGR1_FREE_MASK                /*!< Timing for I3C Bus Free condition */
#define I3C_TIMINGR1_SDA_HD                 I3C_TIMINGR1_SDA_HD_MASK              /*!< SDA Hold Duration */

/****************  Bit definition for I3C_TIMINGR2 register  ******************/
#define I3C_TIMINGR2_STALLT                 I3C_TIMINGR2_STALLT_MASK              /*!< Stall on T bit */
#define I3C_TIMINGR2_STALLD                 I3C_TIMINGR2_STALLD_MASK              /*!< Stall on PAR bit of data bytes */
#define I3C_TIMINGR2_STALLC                 I3C_TIMINGR2_STALLC_MASK              /*!< Stall on PAR bit of CCC byte */
#define I3C_TIMINGR2_STALLA                 I3C_TIMINGR2_STALLA_MASK              /*!< Stall on ACK bit */
#define I3C_TIMINGR2_STALL                  I3C_TIMINGR2_STALL_MASK               /*!< Controller Stall duration */


/*******************  Bit definition for I3C_BCR register  ********************/
#define I3C_BCR_BCR_POS                     (0U)
#define I3C_BCR_BCR_Msk                     (0xFFUL << I3C_BCR_BCR_POS)             /*!< 0x000000FF */
#define I3C_BCR_BCR                         I3C_BCR_BCR_Msk                         /*!< Bus Characteristics */
#define I3C_BCR_BCR0_POS                    (0U)
#define I3C_BCR_BCR0_Msk                    (0x1UL << I3C_BCR_BCR0_POS)             /*!< 0x00000001 */
#define I3C_BCR_BCR0                        I3C_BCR_BCR0_Msk                        /*!< Max Data Speed Limitation */
#define I3C_BCR_BCR1_POS                    (1U)
#define I3C_BCR_BCR1_Msk                    (0x1UL << I3C_BCR_BCR1_POS)             /*!< 0x00000002 */
#define I3C_BCR_BCR1                        I3C_BCR_BCR1_Msk                        /*!< IBI Request capable */
#define I3C_BCR_BCR2_POS                    (2U)
#define I3C_BCR_BCR2_Msk                    (0x1UL << I3C_BCR_BCR2_POS)             /*!< 0x00000004 */
#define I3C_BCR_BCR2                        I3C_BCR_BCR2_Msk                        /*!< IBI Payload additional Mandatory Data Byte */
#define I3C_BCR_BCR3_POS                    (3U)
#define I3C_BCR_BCR3_Msk                    (0x1UL << I3C_BCR_BCR3_POS)             /*!< 0x00000008 */
#define I3C_BCR_BCR3                        I3C_BCR_BCR3_Msk                        /*!< Offline capable */
#define I3C_BCR_BCR4_POS                    (4U)
#define I3C_BCR_BCR4_Msk                    (0x1UL << I3C_BCR_BCR4_POS)             /*!< 0x00000010 */
#define I3C_BCR_BCR4                        I3C_BCR_BCR4_Msk                        /*!< Virtual target support */
#define I3C_BCR_BCR5_POS                    (5U)
#define I3C_BCR_BCR5_Msk                    (0x1UL << I3C_BCR_BCR5_POS)             /*!< 0x00000020 */
#define I3C_BCR_BCR5                        I3C_BCR_BCR5_Msk                        /*!< Advanced capabilities */
#define I3C_BCR_BCR6_POS                    (6U)
#define I3C_BCR_BCR6_Msk                    (0x1UL << I3C_BCR_BCR6_POS)             /*!< 0x00000040 */
#define I3C_BCR_BCR6                        I3C_BCR_BCR6_Msk                        /*!< Device Role shared during Dynamic Address Assignment */

/*******************  Bit definition for I3C_DCR register  ********************/
#define I3C_DCR_DCR_POS                     (0U)
#define I3C_DCR_DCR_Msk                     (0xFFUL << I3C_DCR_DCR_POS)             /*!< 0x000000FF */
#define I3C_DCR_DCR                         I3C_DCR_DCR_Msk                         /*!< Devices Characteristics */




#ifdef __cplusplus
}
#endif

#endif


