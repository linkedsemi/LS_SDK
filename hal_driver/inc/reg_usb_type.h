#ifndef REG_USB_TYPE_H_
#define REG_USB_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint8_t FADDR;
    volatile uint8_t POWER;
    volatile uint8_t IS_TX[2];
    volatile uint8_t IS_RX[2];
    volatile uint8_t IS_USB;
    volatile uint8_t IE_TX[2];
    volatile uint8_t IE_RX[2];
    volatile uint8_t IE_USB;
    volatile uint8_t FRAME[2];
    volatile uint8_t INDEX;
    volatile uint8_t DEVCTL;
    volatile uint8_t TXMAXP;
    volatile uint8_t TXCSR[2];
    volatile uint8_t RXMAXP;
    volatile uint8_t RXCSR[2];
    volatile uint8_t COUNT[2];
    volatile uint8_t TXTYPE;
    volatile uint8_t NACKLIMIT_TXINTV;
    volatile uint8_t RXTYPE;
    volatile uint8_t RXINTV;
    volatile uint8_t RESERVED0[3];
    volatile uint8_t FIFO_SIZE;
    volatile uint32_t FIFO[16];
}reg_usb_t;

enum USB_REG_FADDR_FIELD
{
    USB_FADDR_MASK = (int)0xff,
    USB_FADDR_POS = 0,
};

enum USB_REG_POWER_FIELD
{
    USB_ISO_UPD_MASK = (int)0x80,
    USB_ISO_UPD_POS = 7,
    USB_VBUS_VAL_MASK = (int)0x40,
    USB_VBUS_VAL_POS = 6,
    USB_VBUS_SESS_MASK = (int)0x20,
    USB_VBUS_SESS_POS = 5,
    USB_VBUS_LO_MASK = (int)0x10,
    USB_VBUS_LO_POS = 4,
    USB_USB_RST_MASK = (int)0x8,
    USB_USB_RST_POS = 3,
    USB_RESUME_MASK = (int)0x4,
    USB_RESUME_POS = 2,
    USB_SUSPEND_MD_MASK = (int)0x2,
    USB_SUSPEND_MD_POS = 1,
    USB_SUSPEND_EN_MASK = (int)0x1,
    USB_SUSPEND_EN_POS = 0,
};

enum USB_REG_IS_TX_FIELD
{
    USB_IS_TX_EP6_MASK = (int)0x40,
    USB_IS_TX_EP6_POS = 6,
    USB_IS_TX_EP5_MASK = (int)0x20,
    USB_IS_TX_EP5_POS = 5,
    USB_IS_TX_EP4_MASK = (int)0x10,
    USB_IS_TX_EP4_POS = 4,
    USB_IS_TX_EP3_MASK = (int)0x8,
    USB_IS_TX_EP3_POS = 3,
    USB_IS_TX_EP2_MASK = (int)0x4,
    USB_IS_TX_EP2_POS = 2,
    USB_IS_TX_EP1_MASK = (int)0x2,
    USB_IS_TX_EP1_POS = 1,
    USB_IS_TX_EP0_MASK = (int)0x1,
    USB_IS_TX_EP0_POS = 0,
};

enum USB_REG_IS_RX_FIELD
{
    USB_IS_RX_EP6_MASK = (int)0x40,
    USB_IS_RX_EP6_POS = 6,
    USB_IS_RX_EP5_MASK = (int)0x20,
    USB_IS_RX_EP5_POS = 5,
    USB_IS_RX_EP4_MASK = (int)0x10,
    USB_IS_RX_EP4_POS = 4,
    USB_IS_RX_EP3_MASK = (int)0x8,
    USB_IS_RX_EP3_POS = 3,
    USB_IS_RX_EP2_MASK = (int)0x4,
    USB_IS_RX_EP2_POS = 2,
    USB_IS_RX_EP1_MASK = (int)0x2,
    USB_IS_RX_EP1_POS = 1,
    USB_IS_RX_EP0_MASK = (int)0x1,
    USB_IS_RX_EP0_POS = 0,
};

enum USB_REG_IS_USB_FIELD
{
    USB_IS_SESSION_MASK = (int)0x20,
    USB_IS_SESSION_POS = 5,
    USB_IS_SOF_MASK = (int)0x8,
    USB_IS_SOF_POS = 3,
    USB_IS_RST_MASK = (int)0x4,
    USB_IS_RST_POS = 2,
    USB_IS_RESUME_MASK = (int)0x2,
    USB_IS_RESUME_POS = 1,
    USB_IS_SUSPEND_MASK = (int)0x1,
    USB_IS_SUSPEND_POS = 0,
};

enum USB_REG_IE_TX_FIELD
{
    USB_IE_TX_EP6_MASK = (int)0x40,
    USB_IE_TX_EP6_POS = 6,
    USB_IE_TX_EP5_MASK = (int)0x20,
    USB_IE_TX_EP5_POS = 5,
    USB_IE_TX_EP4_MASK = (int)0x10,
    USB_IE_TX_EP4_POS = 4,
    USB_IE_TX_EP3_MASK = (int)0x8,
    USB_IE_TX_EP3_POS = 3,
    USB_IE_TX_EP2_MASK = (int)0x4,
    USB_IE_TX_EP2_POS = 2,
    USB_IE_TX_EP1_MASK = (int)0x2,
    USB_IE_TX_EP1_POS = 1,
    USB_IE_TX_EP0_MASK = (int)0x1,
    USB_IE_TX_EP0_POS = 0,
};

enum USB_REG_IE_RX_FIELD
{
    USB_IE_RX_EP6_MASK = (int)0x40,
    USB_IE_RX_EP6_POS = 6,
    USB_IE_RX_EP5_MASK = (int)0x20,
    USB_IE_RX_EP5_POS = 5,
    USB_IE_RX_EP4_MASK = (int)0x10,
    USB_IE_RX_EP4_POS = 4,
    USB_IE_RX_EP3_MASK = (int)0x8,
    USB_IE_RX_EP3_POS = 3,
    USB_IE_RX_EP2_MASK = (int)0x4,
    USB_IE_RX_EP2_POS = 2,
    USB_IE_RX_EP1_MASK = (int)0x2,
    USB_IE_RX_EP1_POS = 1,
    USB_IE_RX_EP0_MASK = (int)0x1,
    USB_IE_RX_EP0_POS = 0,
};

enum USB_REG_IE_USB_FIELD
{
    USB_IE_SESSION_MASK = (int)0x20,
    USB_IE_SESSION_POS = 5,
    USB_IE_SOF_MASK = (int)0x8,
    USB_IE_SOF_POS = 3,
    USB_IE_RST_MASK = (int)0x4,
    USB_IE_RST_POS = 2,
    USB_IE_RESUME_MASK = (int)0x2,
    USB_IE_RESUME_POS = 1,
    USB_IE_SUSPEND_MASK = (int)0x1,
    USB_IE_SUSPEND_POS = 0,
};

enum USB_REG_FRAME1_FIELD
{
    USB_FRAME_L_MASK = (int)0xff,
    USB_FRAME_L_POS = 0,
};

enum USB_REG_FRAME2_FIELD
{
    USB_FRAME_H_MASK = (int)0x7,
    USB_FRAME_H_POS = 0,
};

enum USB_REG_INDEX_FIELD
{
    USB_EP_IDX_MASK = (int)0xf,
    USB_EP_IDX_POS = 0,
};

enum USB_REG_DEVCTL_FIELD
{
    USB_CID_MASK = (int)0x80,
    USB_CID_POS = 7,
    USB_PU_CON_MASK = (int)0x10,
    USB_PU_CON_POS = 4,
    USB_PD_CON_MASK = (int)0x8,
    USB_PD_CON_POS = 3,
    USB_HOST_MD_MASK = (int)0x4,
    USB_HOST_MD_POS = 2,
    USB_HOST_REQ_MASK = (int)0x2,
    USB_HOST_REQ_POS = 1,
    USB_SESSION_MASK = (int)0x1,
    USB_SESSION_POS = 0,
};

enum USB_REG_TXMAXP_FIELD
{
    USB_TX_MAX_PKT_MASK = (int)0xff,
    USB_TX_MAX_PKT_POS = 0,
};

enum USB_REG_EP_CSR1_FIELD
{
    USB_EP0_SV_SETUP_END_MASK = (int)0x80,
    USB_EP0_SV_SETUP_END_POS = 7,
    USB_EP0_SV_RX_PKT_RDY_MASK = (int)0x40,
    USB_EP0_SV_RX_PKT_RDY_POS = 6,
    USB_EP0_SEND_STALL_MASK = (int)0x20,
    USB_EP0_SEND_STALL_POS = 5,
    USB_EP0_SETUP_END_MASK = (int)0x10,
    USB_EP0_SETUP_END_POS = 4,
    USB_EP0_DATA_END_MASK = (int)0x8,
    USB_EP0_DATA_END_POS = 3,
    USB_EP0_SENT_STALL_MASK = (int)0x4,
    USB_EP0_SENT_STALL_POS = 2,
    USB_EP0_TX_PKT_RDY_MASK = (int)0x2,
    USB_EP0_TX_PKT_RDY_POS = 1,
    USB_EP0_RX_PKT_RDY_MASK = (int)0x1,
    USB_EP0_RX_PKT_RDY_POS = 0,
};

enum USB_REG_EP_CSR2_FIELD
{
    USB_EP0_FLUSH_FIFO_MASK = (int)0x1,
    USB_EP0_FLUSH_FIFO_POS = 0,
};

enum USB_REG_RXMAXP_FIELD
{
    USB_RX_MAX_PKT_MASK = (int)0xff,
    USB_RX_MAX_PKT_POS = 0,
};

enum USB_REG_RXCSR1_FIELD
{
    USB_CLR_DATA_TOG_MASK = (int)0x80,
    USB_CLR_DATA_TOG_POS = 7,
    USB_SENT_STALL_MASK = (int)0x40,
    USB_SENT_STALL_POS = 6,
    USB_SEND_STALL_MASK = (int)0x20,
    USB_SEND_STALL_POS = 5,
    USB_FLUSH_FIFO_MASK = (int)0x10,
    USB_FLUSH_FIFO_POS = 4,
    USB_DATA_ERR_MASK = (int)0x8,
    USB_DATA_ERR_POS = 3,
    USB_OVER_RUN_MASK = (int)0x4,
    USB_OVER_RUN_POS = 2,
    USB_FIFO_FULL_MASK = (int)0x2,
    USB_FIFO_FULL_POS = 1,
    USB_RX_PKT_RDY_MASK = (int)0x1,
    USB_RX_PKT_RDY_POS = 0,
};

enum USB_REG_RXCSR2_FIELD
{
    USB_AUTO_CLR_MASK = (int)0x80,
    USB_AUTO_CLR_POS = 7,
    USB_ISO_MASK = (int)0x40,
    USB_ISO_POS = 6,
};

enum USB_REG_COUNT_FIELD
{
    USB_FIFO_CNT_MASK = (int)0x7f,
    USB_FIFO_CNT_POS = 0,
};

enum USB_REG_TX_FIFO_ADDR_FIELD
{
    USB_TX_FIFO_ADDR_MASK = (int)0xff,
    USB_TX_FIFO_ADDR_POS = 0,
};

enum USB_REG_TX_FIFO_SIZE_FIELD
{
    USB_TX_FIFO_SIZE_MASK = (int)0xe0,
    USB_TX_FIFO_SIZE_POS = 5,
    USB_TX_FIFO_DPB_MASK = (int)0x10,
    USB_TX_FIFO_DPB_POS = 4,
};

enum USB_REG_RX_FIFO_ADDR_FIELD
{
    USB_RX_FIFO_ADDR_MASK = (int)0xff,
    USB_RX_FIFO_ADDR_POS = 0,
};

enum USB_REG_RX_FIFO_SIZE_FIELD
{
    USB_RX_FIFO_SIZE_MASK = (int)0xe0,
    USB_RX_FIFO_SIZE_POS = 5,
    USB_RX_FIFO_DPB_MASK = (int)0x10,
    USB_RX_FIFO_DPB_POS = 4,
};

#endif

