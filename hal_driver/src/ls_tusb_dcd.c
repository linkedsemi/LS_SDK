/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Koji KITAYAMA
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */

#include "tusb_option.h"

#if CFG_TUD_ENABLED

#if __GNUC__ > 8 && defined(__ARM_FEATURE_UNALIGNED)
/* GCC warns that an address may be unaligned, even though
 * the target CPU has the capability for unaligned memory access. */
_Pragma("GCC diagnostic ignored \"-Waddress-of-packed-member\"");
#endif

#include "usbd.h"
#include "usbd_pvt.h"
#include "platform.h"
#include "cpu.h"
#include "dcd.h"
#include "musb_type.h"
#include "ls_msp_usb.h"
#include "field_manipulate.h"
#include "linked_async_framework.h"
#include "ls_dbg.h"
#include "log.h"

#include "compile_flag.h"

#define USB_TX_BUF_ADDR         (8)
#define USB_TX_FIFO_SZ          (1)
#define USB_TX_BUF_SIZE         (1<<(3+USB_TX_FIFO_SZ))
#define USB_RX_BUF_ADDR         (USB_TX_BUF_ADDR + USB_TX_BUF_SIZE / 8)

/*------------------------------------------------------------------
 * MACRO TYPEDEF CONSTANT ENUM DECLARATION
 *------------------------------------------------------------------*/

typedef struct {
    uint_fast16_t beg; /* offset of including first element */
    uint_fast16_t end; /* offset of excluding the last element */
} free_block_t;

typedef struct TU_ATTR_PACKED {
    uint8_t TXMAXP;
    uint8_t  TXCSRL;
    uint8_t  TXCSRH;
    uint8_t RXMAXP;
    uint8_t  RXCSRL;
    uint8_t  RXCSRH;
    uint16_t RXCOUNT;
    uint16_t RESERVED[3];
} hw_endpoint_t;

typedef union {
    uint8_t   u8;
    uint16_t  u16;
    uint32_t  u32;
} hw_fifo_t;

typedef enum {
    USB_EP0_STAGE_SETUP,        /* received SETUP */
    USB_EP0_STAGE_PRE_TX,       /* Pre IN data */
    USB_EP0_STAGE_TX,           /* IN data */
    USB_EP0_STAGE_PRE_RX,       /* Pre OUT data */
    USB_EP0_STAGE_RX,           /* OUT data */
    USB_EP0_STAGE_PRE_STATUSIN,     /* (after OUT data) */
    USB_EP0_STAGE_STATUSIN,     /* (after OUT data) */
    USB_EP0_STAGE_STATUSOUT     /* (after IN data) */
} ep0_state_t;

typedef struct 
{
    struct co_list_hdr list_hdr;
    void      *buf;      /* the start address of a transfer data buffer */
    uint16_t  length;    /* the number of bytes in the buffer */
    uint16_t  remaining; /* the number of bytes remaining in the buffer */
} pipe_state_t;

typedef struct
{
    tusb_control_request_t setup_packet;
    uint16_t     remaining_ctrl; /* The number of bytes remaining in data stage of control transfer. */
    uint8_t      rx_buf_addr;
    pipe_state_t pipe0;
    ep0_state_t  ep0_state;
    bool         is_set_addr;
    uint8_t      addr;
    pipe_state_t pipe[2][7];   /* pipe[direction][endpoint number - 1] */
    uint16_t     pipe_buf_is_fifo[2]; /* Bitmap. Each bit means whether 1:TU_FIFO or 0:POD. */
} dcd_data_t;

static dcd_data_t _dcd;

static linked_async_inst_t dcd_async_inst;

static void handle_xfer_in(uint_fast8_t ep_addr);

static void dcd_linked_async_end(void *param)
{
    linked_async_end(&dcd_async_inst, NULL, 0);
}

static void dcd_linked_async_pre_process(struct linked_async_inst_s *inst, struct co_list_hdr *hdr)
{
    pipe_state_t *pipe = (void *)hdr;
    uint8_t ep_addr = TUSB_DIR_IN_MASK | (pipe - _dcd.pipe[TUSB_DIR_IN] + 1);
    handle_xfer_in(ep_addr);
}

static bool dcd_linked_async_callback(struct linked_async_inst_s *inst, struct co_list_hdr *hdr, void *dummy, uint8_t status)
{
    return false;
}

static inline volatile hw_endpoint_t* edpt_regs(unsigned epnum_minus1)
{
    USB0->EPIDX = epnum_minus1 + 1;
    return (volatile hw_endpoint_t*)&USB0->TXMAXP;
}

static void pipe_write_packet(void *buf, volatile void *fifo, unsigned len)
{
    volatile hw_fifo_t *reg = (volatile hw_fifo_t*)fifo;
    uintptr_t addr = (uintptr_t)buf;
    while (len >= 4) {
        reg->u32 = *(uint32_t const *)addr;
        addr += 4;
        len  -= 4;
    }
    if (len >= 2) {
        reg->u16 = *(uint16_t const *)addr;
        addr += 2;
        len  -= 2;
    }
    if (len) {
        reg->u8 = *(uint8_t const *)addr;
    }
}

static void pipe_read_packet(void *buf, volatile void *fifo, unsigned len)
{
    volatile hw_fifo_t *reg = (volatile hw_fifo_t*)fifo;
    uintptr_t addr = (uintptr_t)buf;
    while (len >= 4) {
        *(uint32_t *)addr = reg->u32;
        addr += 4;
        len  -= 4;
    }
    if (len >= 2) {
        *(uint16_t *)addr = reg->u16;
        addr += 2;
        len  -= 2;
    }
    if (len) {
        *(uint8_t *)addr = reg->u8;
    }
}

static void pipe_read_write_packet_ff(tu_fifo_t *f, volatile void *fifo, unsigned len, unsigned dir)
{
    static const struct {
        void (*tu_fifo_get_info)(tu_fifo_t *f, tu_fifo_buffer_info_t *info);
        void (*tu_fifo_advance)(tu_fifo_t *f, uint16_t n);
        void (*pipe_read_write)(void *buf, volatile void *fifo, unsigned len);
    } ops[] = {
        /* OUT */ {tu_fifo_get_write_info,tu_fifo_advance_write_pointer,pipe_read_packet},
        /* IN  */ {tu_fifo_get_read_info, tu_fifo_advance_read_pointer, pipe_write_packet},
    };
    tu_fifo_buffer_info_t info;
    ops[dir].tu_fifo_get_info(f, &info);
    unsigned total_len = len;
    len = TU_MIN(total_len, info.len_lin);
    ops[dir].pipe_read_write(info.ptr_lin, fifo, len);
    unsigned rem = total_len - len;
    if (rem) {
        len = TU_MIN(rem, info.len_wrap);
        ops[dir].pipe_read_write(info.ptr_wrap, fifo, len);
        rem -= len;
    }
    ops[dir].tu_fifo_advance(f, total_len - rem);
}

static void handle_xfer_in(uint_fast8_t ep_addr)
{
    unsigned epnum_minus1 = tu_edpt_number(ep_addr) - 1;
    pipe_state_t  *pipe = &_dcd.pipe[tu_edpt_dir(ep_addr)][epnum_minus1];
    const unsigned rem  = pipe->remaining;

    volatile hw_endpoint_t *regs = edpt_regs(epnum_minus1);
    const unsigned mps = regs->TXMAXP;
    const unsigned len = TU_MIN(mps, rem);
    uint8_t       *buf = pipe->buf;

    regs->TXCSRH |= USB_TXCSRH1_MODE;
    // TU_LOG1("   %p mps %d len %d rem %d\n", buf, mps, len, rem);
    if (len) {
        if (_dcd.pipe_buf_is_fifo[TUSB_DIR_IN] & TU_BIT(epnum_minus1)) {
            pipe_read_write_packet_ff((tu_fifo_t *)buf, &USB0->FIFO1_WORD + epnum_minus1, len, TUSB_DIR_IN);
        } else {
            pipe_write_packet(buf, &USB0->FIFO1_WORD + epnum_minus1, len);
            pipe->buf       = buf + len;
        }
        pipe->remaining = rem - len;
    }
    regs->TXCSRL = USB_TXCSRL1_TXRDY;
}

static void handle_xfer_out(uint8_t rhport, uint8_t ep_addr, bool isr)
{
    unsigned epnum_minus1 = tu_edpt_number(ep_addr) - 1;
    pipe_state_t  *pipe = &_dcd.pipe[tu_edpt_dir(ep_addr)][epnum_minus1];
    volatile hw_endpoint_t *regs = edpt_regs(epnum_minus1);
    // TU_LOG1(" RXCSRL%d = %x\n", epnum_minus1 + 1, regs->RXCSRL);

    const unsigned mps = regs->RXMAXP;
    const unsigned rem = pipe->remaining;
    const unsigned vld = regs->RXCOUNT;
    const unsigned len = TU_MIN(TU_MIN(rem, mps), vld);
    uint8_t       *buf = pipe->buf;

    if(!buf)
    {
        return;
    }

    if (len) {
        if (_dcd.pipe_buf_is_fifo[TUSB_DIR_OUT] & TU_BIT(epnum_minus1)) {
            pipe_read_write_packet_ff((tu_fifo_t *)buf, &USB0->FIFO1_WORD + epnum_minus1, len, TUSB_DIR_OUT);
        } else {
            pipe_read_packet(buf, &USB0->FIFO1_WORD + epnum_minus1, len);
            pipe->buf       = buf + len;
        }
        pipe->remaining = rem - len;
    }

    if ((len < mps) || (rem == len)) {
        pipe->buf = NULL;
        dcd_event_xfer_complete(rhport, ep_addr,
                                pipe->length - pipe->remaining,
                                XFER_RESULT_SUCCESS, isr);
    }
    CLEAR_BIT(regs->RXCSRL, USB_RXCSRL1_RXRDY); /* Clear RXRDY bit */
}

static bool edpt_n_xfer(uint8_t rhport, uint8_t ep_addr, uint8_t *buffer, uint16_t total_bytes)
{
    (void)rhport;

    unsigned epnum_minus1 = tu_edpt_number(ep_addr) - 1;
    unsigned dir_in       = tu_edpt_dir(ep_addr);

    /* Ensure that the configuration for pipe and possible out data handling should not be interrupted. By mzhou. */
    pipe_state_t *pipe = &_dcd.pipe[dir_in][epnum_minus1];

    pipe->length       = total_bytes;
    pipe->remaining    = total_bytes;
    pipe->buf          = buffer;

    if (dir_in) {
        linked_async_start(&dcd_async_inst, (void *)&pipe->list_hdr);
    } else {
        volatile hw_endpoint_t *regs = edpt_regs(epnum_minus1);
        if(regs->RXCOUNT)
        {
            handle_xfer_out(rhport, ep_addr, false);
        }
    }
    return true;
}

static bool edpt0_xfer(uint8_t rhport, uint8_t ep_addr, uint8_t *buffer, uint16_t total_bytes)
{
    dcd_data_t *usb_data = &_dcd;
    TU_ASSERT(total_bytes <= 64);

    USB0->EPIDX = 0;

    if (usb_data->ep0_state == USB_EP0_STAGE_PRE_TX || usb_data->ep0_state == USB_EP0_STAGE_TX)
    {
        TU_ASSERT(total_bytes <= _dcd.remaining_ctrl);
        const unsigned rem = _dcd.remaining_ctrl;
        const unsigned len = TU_MIN(TU_MIN(rem, 64), total_bytes);
        pipe_write_packet(buffer, &USB0->FIFO0_WORD, len);

        _dcd.pipe0.buf       = buffer + len;
        _dcd.pipe0.length    = len;
        _dcd.pipe0.remaining = 0;

        _dcd.remaining_ctrl  = rem - len;
        if ((len < 64) || (rem == len)) {
            _dcd.ep0_state = USB_EP0_STAGE_STATUSOUT;
            USB0->CSRL0 = USB_CSRL0_TXRDY | USB_CSRL0_DATAEND;
        } else {
            _dcd.ep0_state = USB_EP0_STAGE_TX;
            USB0->CSRL0 = USB_CSRL0_TXRDY;
        }
    }
    else if (usb_data->ep0_state == USB_EP0_STAGE_PRE_RX || usb_data->ep0_state == USB_EP0_STAGE_RX)
    {
        const unsigned rem = _dcd.remaining_ctrl;
        const unsigned len = TU_MIN(TU_MIN(rem, 64), total_bytes);
        _dcd.pipe0.buf       = buffer;
        _dcd.pipe0.length    = len;
        _dcd.pipe0.remaining = len;
        usb_data->ep0_state = USB_EP0_STAGE_RX;

        USB0->CSRL0 = USB_CSRL0_RXRDYC;
    }
    else if (usb_data->ep0_state == USB_EP0_STAGE_PRE_STATUSIN || usb_data->ep0_state == USB_EP0_STAGE_STATUSIN)
    {
        _dcd.pipe0.buf = NULL;
        _dcd.pipe0.length    = 0;
        _dcd.pipe0.remaining = 0;
        usb_data->ep0_state = USB_EP0_STAGE_STATUSIN;
        /* Clear RX FIFO and reverse the transaction direction */
        USB0->CSRL0 = USB_CSRL0_RXRDYC | USB_CSRL0_DATAEND | USB_CSRL0_TXRDY;
    }

    return true;
}

static void ep0_setup(uint8_t rhport)
{
    volatile reg_usb_t *usb_instance = USB0;
    dcd_data_t *usb_data = &_dcd;

    while (usb_instance->COUNT0 != 8);
    usb_data->is_set_addr = false;
    pipe_read_packet(&usb_data->setup_packet, (void *)&usb_instance->FIFO0_WORD, sizeof(usb_data->setup_packet));

    _dcd.pipe0.buf       = NULL;
    _dcd.pipe0.length    = 0;
    _dcd.pipe0.remaining = 0;
    _dcd.remaining_ctrl   = _dcd.setup_packet.wLength;

    dcd_event_setup_received(rhport, (const uint8_t*)(uintptr_t)&_dcd.setup_packet, true);

    if (usb_data->setup_packet.wLength == 0) {
        /* No data stage, must send zlp to host */
        usb_data->ep0_state = USB_EP0_STAGE_PRE_STATUSIN;
        if (usb_data->setup_packet.bRequest == 5) {
            usb_data->is_set_addr = true;
        }
    } else if (usb_data->setup_packet.bmRequestType & 0x80) {
        /* IN stage, send data to host */
        usb_data->ep0_state = USB_EP0_STAGE_PRE_TX;
        usb_instance->CSRL0 = USB_CSRL0_RXRDYC;
        while ((usb_instance->CSRL0 & USB_CSRL0_RXRDY) != 0);
    } else {
        /* OUT stage, recive data from host */
        usb_data->ep0_state = USB_EP0_STAGE_PRE_RX;
    }
}

static void process_ep0(uint8_t rhport)
{
    USB0->EPIDX = 0;

    volatile reg_usb_t *usb_instance = USB0;
    uint16_t csr = usb_instance->CSRL0;

    dcd_data_t *usb_data = &_dcd;

    if (csr & USB_CSRL0_DATAEND) {
        return;
    }

    if (csr & USB_CSRL0_STALLED) {
        /* Returned STALL packet to HOST. */
        usb_instance->CSRL0 = csr & ~USB_CSRL0_STALLED;
        _dcd.ep0_state = USB_EP0_STAGE_SETUP;
        csr = usb_instance->CSRL0;
    }

    if (csr & USB_CSRL0_SETEND) {
        usb_instance->CSRL0 = USB_CSRL0_SETENDC;
        switch (usb_data->ep0_state) {
        case USB_EP0_STAGE_TX:
            usb_data->ep0_state = USB_EP0_STAGE_STATUSOUT;
            break;
        case USB_EP0_STAGE_RX:
            usb_data->ep0_state = USB_EP0_STAGE_STATUSIN;
            break;
        default:
            log_output(false, "SetupEnd came in a wrong ep0stage %s\n", usb_data->ep0_state);
        }
        csr = usb_instance->CSRL0;
    }

    switch (usb_data->ep0_state) {
    case USB_EP0_STAGE_PRE_TX:
        break;
    case USB_EP0_STAGE_PRE_STATUSIN:
        break;
    case USB_EP0_STAGE_PRE_RX:
        break;
    case USB_EP0_STAGE_TX:
        /* irq on clearing txpktrdy */
        if ((csr & USB_CSRL0_TXRDY) == 0) {
            if (_dcd.remaining_ctrl) {
                dcd_event_xfer_complete(rhport,
                                        tu_edpt_addr(0, TUSB_DIR_IN),
                                        _dcd.pipe0.length - _dcd.pipe0.remaining,
                                        XFER_RESULT_SUCCESS, true);
            }
        }
        break;

    case USB_EP0_STAGE_RX:
        /* irq on set rxpktrdy */
        if (csr & USB_CSRL0_RXRDY) {
            if (_dcd.pipe0.buf) {
                /* DATA OUT */
                const unsigned vld = USB0->COUNT0;
                const unsigned rem = _dcd.pipe0.remaining;
                const unsigned len = TU_MIN(TU_MIN(rem, 64), vld);
                pipe_read_packet(_dcd.pipe0.buf, &USB0->FIFO0_WORD, len);

                _dcd.pipe0.remaining = rem - len;
                _dcd.remaining_ctrl -= len;
                _dcd.pipe0.buf = NULL;

                if (_dcd.remaining_ctrl == 0) {
                    /* rx ok, move status in */
                    _dcd.ep0_state = USB_EP0_STAGE_STATUSIN;
                }

                dcd_event_xfer_complete(rhport,
                                        tu_edpt_addr(0, TUSB_DIR_OUT),
                                        _dcd.pipe0.length - _dcd.pipe0.remaining,
                                        XFER_RESULT_SUCCESS, true);
            }
        }
        break;
    case USB_EP0_STAGE_STATUSIN:
        /* end of sequence #2 or #3 (no data), host move status stage, another Endpoint 0 interrupt will be generated to indicate that the
            request has completed */
        if (usb_data->is_set_addr) {
            usb_data->is_set_addr = false;
            usb_instance->FADDR = usb_data->addr;
        }
        dcd_event_xfer_complete(rhport,
                        tu_edpt_addr(0, TUSB_DIR_IN),
                        0,
                        XFER_RESULT_SUCCESS, true);
        if (csr & USB_CSRL0_RXRDY) {
            ep0_setup(rhport);
        } else {
            usb_data->ep0_state = USB_EP0_STAGE_SETUP;
        }
        break;
    case USB_EP0_STAGE_STATUSOUT:
        /* end of sequence #1, host move status stage, the interrupt is just a confirmation that the request
            completed successfully.*/
        dcd_event_xfer_complete(rhport,
                        0,
                        0,
                        XFER_RESULT_SUCCESS, true);
        if (csr & USB_CSRL0_RXRDY) {
            ep0_setup(rhport);
        } else {
            usb_data->ep0_state = USB_EP0_STAGE_SETUP;
        }
        break;
    case USB_EP0_STAGE_SETUP:
        // setup begin
        if (csr & USB_CSRL0_RXRDY) {
            ep0_setup(rhport);
        }
        break;
    }
}

static void process_edpt_n(uint8_t rhport, uint_fast8_t ep_addr)
{
    const unsigned dir_in     = tu_edpt_dir(ep_addr);
    const unsigned epn_minus1 = tu_edpt_number(ep_addr) - 1;

    volatile hw_endpoint_t *regs = edpt_regs(epn_minus1);
    if (dir_in) {
        // TU_LOG1(" TXCSRL%d = %x\n", epn_minus1 + 1, regs->TXCSRL);
        if (regs->TXCSRL & USB_TXCSRL1_STALLED) {
            regs->TXCSRL &= ~(USB_TXCSRL1_STALLED | USB_TXCSRL1_UNDRN);
            return;
        }
        pipe_state_t  *pipe = &_dcd.pipe[tu_edpt_dir(ep_addr)][epn_minus1];
        if (pipe->remaining)
        {
            handle_xfer_in(ep_addr);
        }
        else
        {
            usbd_defer_func(dcd_linked_async_end, NULL, true);
            dcd_event_xfer_complete(rhport, ep_addr,
                                    pipe->length - pipe->remaining,
                                    XFER_RESULT_SUCCESS, true);
        }
    } else {
        // TU_LOG1(" RXCSRL%d = %x\n", epn_minus1 + 1, regs->RXCSRL);
        if (regs->RXCSRL & USB_RXCSRL1_STALLED) {
            regs->RXCSRL &= ~(USB_RXCSRL1_STALLED | USB_RXCSRL1_OVER);
            return;
        }
        handle_xfer_out(rhport, ep_addr, true);
    }
}

static void process_bus_reset(uint8_t rhport)
{
    /* When bmRequestType is REQUEST_TYPE_INVALID(0xFF),
    * a control transfer state is SETUP or STATUS stage. */
    /* When pipe0.buf has not NULL, DATA stage works in progress. */
    _dcd.pipe0.buf = NULL;
    _dcd.rx_buf_addr = USB_RX_BUF_ADDR;
    _dcd.ep0_state = USB_EP0_STAGE_SETUP;

    USB0->TXIE = 1; /* Enable only EP0 */
    USB0->RXIE = 0; 

    /* Clear FIFO settings */
    for (unsigned i = 1; i < TUP_DCD_ENDPOINT_MAX; ++i) {
        USB0->EPIDX     = i;
        USB0->TXFIFO_SIZE[0] = 0;
        USB0->TXFIFO_SIZE[1] = 0;
        USB0->RXFIFO_SIZE[0] = 0;
        USB0->RXFIFO_SIZE[1] = 0;
    }
    dcd_event_bus_reset(rhport, TUSB_SPEED_FULL, true);
}

/*------------------------------------------------------------------
 * Device API
 *------------------------------------------------------------------*/

static void USB_IRQHandler(void)
{
    tud_int_handler(0);
}

void dcd_init(uint8_t rhport)
{
    (void)rhport;
    linked_async_init(&dcd_async_inst, dcd_linked_async_pre_process, dcd_linked_async_callback);
    HAL_USB_MSP_Init(USB_IRQHandler);
    HAL_USB_MSP_Busy_Set();
    USB0->IE |= USB_IE_SUSPND;
    _dcd.rx_buf_addr = USB_RX_BUF_ADDR;
    _dcd.ep0_state = USB_EP0_STAGE_SETUP;
    dcd_connect(rhport);
}

void dcd_int_enable(uint8_t rhport)
{
    (void)rhport;
    HAL_USB_MSP_EnableIRQ();
}

void dcd_int_disable(uint8_t rhport)
{
    (void)rhport;
    HAL_USB_MSP_DisableIRQ();
}

// Receive Set Address request, mcu port must also include status IN response
void dcd_set_address(uint8_t rhport, uint8_t dev_addr)
{
    (void)rhport;
    (void)dev_addr;
    _dcd.pipe0.buf       = NULL;
    _dcd.pipe0.length    = 0;
    _dcd.pipe0.remaining = 0;
    _dcd.addr = dev_addr;
    _dcd.ep0_state = USB_EP0_STAGE_STATUSIN;

    /* Clear RX FIFO to return ACK. */
    USB0->CSRL0 = USB_CSRL0_RXRDYC | USB_CSRL0_DATAEND | USB_CSRL0_TXRDY;
}

// Wake up host
void dcd_remote_wakeup(uint8_t rhport)
{
    (void)rhport;
    USB0->POWER |= USB_POWER_RESUME;

    // unsigned cnt = SystemCoreClock / 1000;
    // while (cnt--) __NOP();
    DELAY_US(1000);

    USB0->POWER &= ~USB_POWER_RESUME;
    dcd_event_bus_signal(rhport, DCD_EVENT_RESUME, false);
}

// Connect by enabling internal pull-up resistor on D+/D-
void dcd_connect(uint8_t rhport)
{
    (void)rhport;
    USB0->POWER |= USB_POWER_SOFTCONN;
}

// Disconnect by disabling internal pull-up resistor on D+/D-
void dcd_disconnect(uint8_t rhport)
{
    (void)rhport;
    USB0->POWER &= ~USB_POWER_SOFTCONN;
}

void dcd_sof_enable(uint8_t rhport, bool en)
{
    (void) rhport;
    (void) en;

    // TODO implement later
}

//--------------------------------------------------------------------+
// Endpoint API
//--------------------------------------------------------------------+

// Configure endpoint's registers according to descriptor
bool dcd_edpt_open(uint8_t rhport, tusb_desc_endpoint_t const * ep_desc)
{
    (void) rhport;

    const unsigned ep_addr = ep_desc->bEndpointAddress;
    const unsigned epn     = tu_edpt_number(ep_addr);
    const unsigned dir_in  = tu_edpt_dir(ep_addr);
    const unsigned xfer    = ep_desc->bmAttributes.xfer;
    const unsigned mps     = tu_edpt_packet_size(ep_desc);

    TU_ASSERT(epn < TUP_DCD_ENDPOINT_MAX);

    pipe_state_t *pipe = &_dcd.pipe[dir_in][epn - 1];
    pipe->buf       = NULL;
    pipe->length    = 0;
    pipe->remaining = 0;

    volatile hw_endpoint_t *regs = edpt_regs(epn - 1);
    if (dir_in) {
        regs->TXMAXP = mps;
        regs->TXCSRH = (xfer == TUSB_XFER_ISOCHRONOUS) ? USB_TXCSRH1_ISO : 0;
        if (regs->TXCSRL & USB_TXCSRL1_TXRDY)
            regs->TXCSRL = USB_TXCSRL1_CLRDT | USB_TXCSRL1_FLUSH;
        else
            regs->TXCSRL = USB_TXCSRL1_CLRDT;
        USB0->TXIE |= TU_BIT(epn);
    } else {
        regs->RXMAXP = mps;
        regs->RXCSRH = (xfer == TUSB_XFER_ISOCHRONOUS) ? USB_RXCSRH1_ISO : 0;
        if (regs->RXCSRL & USB_RXCSRL1_RXRDY)
            regs->RXCSRL = USB_RXCSRL1_CLRDT | USB_RXCSRL1_FLUSH;
        else
            regs->RXCSRL = USB_RXCSRL1_CLRDT;
        USB0->RXIE |= TU_BIT(epn);
    }

    /* Setup FIFO */
    if (dir_in) 
    {
        USB0->TXFIFO_SIZE[0] = USB_TX_BUF_ADDR;
        USB0->TXFIFO_SIZE[1] = USB_TX_FIFO_SZ << USB_TX_FIFO_SIZE_POS;
    }
    else
    {
        TU_ASSERT(_dcd.rx_buf_addr < 16);
        USB0->RXFIFO_SIZE[0] = _dcd.rx_buf_addr;
        switch(mps)
        {
        case 8:
            USB0->RXFIFO_SIZE[1] = 0 << USB_RX_FIFO_SIZE_POS;
            _dcd.rx_buf_addr += 1;
        break;
        case 16:
            USB0->RXFIFO_SIZE[1] = 1 << USB_RX_FIFO_SIZE_POS;
            _dcd.rx_buf_addr += 2;
        break;
        case 32:
            USB0->RXFIFO_SIZE[1] = 2 << USB_RX_FIFO_SIZE_POS;
            _dcd.rx_buf_addr += 4;
        break;
        case 64:
            USB0->RXFIFO_SIZE[1] = 3 << USB_RX_FIFO_SIZE_POS;
            _dcd.rx_buf_addr += 8;
        break;
        default:
            TU_ASSERT(0,0);
        break;
        }
    }
    return true;
}

void dcd_edpt_close_all(uint8_t rhport)
{
    (void) rhport;
    volatile hw_endpoint_t *regs = (volatile hw_endpoint_t *)(uintptr_t)&USB0->TXMAXP;
    unsigned const ie = HAL_USB_MSP_GetEnableIRQ();
    HAL_USB_MSP_DisableIRQ();
    USB0->TXIE = 1; /* Enable only EP0 */
    USB0->RXIE = 0; 
    for (unsigned i = 1; i < TUP_DCD_ENDPOINT_MAX; ++i) {
        USB0->EPIDX     = i;
        regs->TXMAXP = 0;
        regs->TXCSRH = 0;
        if (regs->TXCSRL & USB_TXCSRL1_TXRDY)
            regs->TXCSRL = USB_TXCSRL1_CLRDT | USB_TXCSRL1_FLUSH;
        else
            regs->TXCSRL = USB_TXCSRL1_CLRDT;

        regs->RXMAXP = 0;
        regs->RXCSRH = 0;
        if (regs->RXCSRL & USB_RXCSRL1_RXRDY)
            regs->RXCSRL = USB_RXCSRL1_CLRDT | USB_RXCSRL1_FLUSH;
        else
            regs->RXCSRL = USB_RXCSRL1_CLRDT;

        // USB0->EPIDX     = i;
        USB0->TXFIFO_SIZE[0] = 0;
        USB0->TXFIFO_SIZE[1] = 0;
        USB0->RXFIFO_SIZE[0] = 0;
        USB0->RXFIFO_SIZE[1] = 0;
    }
    if (ie) HAL_USB_MSP_EnableIRQ();
}

void dcd_edpt_close(uint8_t rhport, uint8_t ep_addr)
{
    (void)rhport;
    unsigned const epn    = tu_edpt_number(ep_addr);
    unsigned const dir_in = tu_edpt_dir(ep_addr);

    hw_endpoint_t volatile *regs = edpt_regs(epn - 1);
    unsigned const ie = HAL_USB_MSP_GetEnableIRQ();
    HAL_USB_MSP_DisableIRQ();
    if (dir_in) {
        USB0->TXIE  &= ~TU_BIT(epn);
        regs->TXMAXP = 0;
        regs->TXCSRH = 0;
        if (regs->TXCSRL & USB_TXCSRL1_TXRDY)
            regs->TXCSRL = USB_TXCSRL1_CLRDT | USB_TXCSRL1_FLUSH;
        else
            regs->TXCSRL = USB_TXCSRL1_CLRDT;

        // USB0->EPIDX     = epn;
        USB0->TXFIFO_SIZE[0]  = 0;
        USB0->TXFIFO_SIZE[1]  = 0;
    } else {
        USB0->RXIE  &= ~TU_BIT(epn);
        regs->RXMAXP = 0;
        regs->RXCSRH = 0;
        if (regs->RXCSRL & USB_RXCSRL1_RXRDY)
            regs->RXCSRL = USB_RXCSRL1_CLRDT | USB_RXCSRL1_FLUSH;
        else
            regs->RXCSRL = USB_RXCSRL1_CLRDT;
        USB0->RXFIFO_SIZE[0]  = 0;
        USB0->RXFIFO_SIZE[1]  = 0;
    }
    if (ie) HAL_USB_MSP_EnableIRQ();
}

// Submit a transfer, When complete dcd_event_xfer_complete() is invoked to notify the stack
bool dcd_edpt_xfer(uint8_t rhport, uint8_t ep_addr, uint8_t * buffer, uint16_t total_bytes)
{
    (void)rhport;
    bool ret;
    // TU_LOG1("X %x %d\n", ep_addr, total_bytes);
    unsigned const epnum = tu_edpt_number(ep_addr);
    unsigned const ie = HAL_USB_MSP_GetEnableIRQ();
    HAL_USB_MSP_DisableIRQ();
    if (epnum) {
        _dcd.pipe_buf_is_fifo[tu_edpt_dir(ep_addr)] &= ~TU_BIT(epnum - 1);
        ret = edpt_n_xfer(rhport, ep_addr, buffer, total_bytes);
    } else
        ret = edpt0_xfer(rhport, ep_addr, buffer, total_bytes);
    if (ie) HAL_USB_MSP_EnableIRQ();
    return ret;
}

// Submit a transfer where is managed by FIFO, When complete dcd_event_xfer_complete() is invoked to notify the stack - optional, however, must be listed in usbd.c
bool dcd_edpt_xfer_fifo(uint8_t rhport, uint8_t ep_addr, tu_fifo_t * ff, uint16_t total_bytes)
{
    (void)rhport;
    bool ret;
    // TU_LOG1("X %x %d\n", ep_addr, total_bytes);
    unsigned const epnum = tu_edpt_number(ep_addr);
    TU_ASSERT(epnum);
    unsigned const ie = HAL_USB_MSP_GetEnableIRQ();
    HAL_USB_MSP_DisableIRQ();
    _dcd.pipe_buf_is_fifo[tu_edpt_dir(ep_addr)] |= TU_BIT(epnum - 1);
    ret = edpt_n_xfer(rhport, ep_addr, (uint8_t*)ff, total_bytes);
    if (ie) HAL_USB_MSP_EnableIRQ();
    return ret;
}

// Stall endpoint
void dcd_edpt_stall(uint8_t rhport, uint8_t ep_addr)
{
    (void)rhport;
    unsigned const epn = tu_edpt_number(ep_addr);
    unsigned const ie  = HAL_USB_MSP_GetEnableIRQ();
    HAL_USB_MSP_DisableIRQ();
    if (0 == epn) {
        if (!ep_addr) { /* Ignore EP80 */
            _dcd.ep0_state = USB_EP0_STAGE_SETUP;
            _dcd.pipe0.buf = NULL;
            USB0->EPIDX = 0;
            USB0->CSRL0 = USB_CSRL0_STALL;
        }
    } else {
        volatile hw_endpoint_t *regs = edpt_regs(epn - 1);
        if (tu_edpt_dir(ep_addr)) { /* IN */
            regs->TXCSRL = USB_TXCSRL1_STALL;
        } else { /* OUT */
            TU_ASSERT(!(regs->RXCSRL & USB_RXCSRL1_RXRDY),);
            regs->RXCSRL = USB_RXCSRL1_STALL;
        }
    }
    if (ie) HAL_USB_MSP_EnableIRQ();
}

// clear stall, data toggle is also reset to DATA0
void dcd_edpt_clear_stall(uint8_t rhport, uint8_t ep_addr)
{
    (void)rhport;
    unsigned const epn = tu_edpt_number(ep_addr);
    hw_endpoint_t volatile *regs = edpt_regs(epn - 1);
    unsigned const ie = HAL_USB_MSP_GetEnableIRQ();
    HAL_USB_MSP_DisableIRQ();
    if (tu_edpt_dir(ep_addr)) { /* IN */
        regs->TXCSRL = USB_TXCSRL1_CLRDT;
    } else { /* OUT */
        regs->RXCSRL = USB_RXCSRL1_CLRDT; 
    }
    if (ie) HAL_USB_MSP_EnableIRQ();
}

/*-------------------------------------------------------------------
 * ISR
 *-------------------------------------------------------------------*/
void dcd_int_handler(uint8_t rhport)
{
    uint_fast8_t is, txis, rxis;

    is   = USB0->IS;   /* read and clear interrupt status */
    txis = USB0->TXIS; /* read and clear interrupt status */
    rxis = USB0->RXIS; /* read and clear interrupt status */

    is &= USB0->IE; /* Clear disabled interrupts */
    if (is & USB_IS_DISCON) {
    }
    if (is & USB_IS_SOF) {
        dcd_event_bus_signal(rhport, DCD_EVENT_SOF, true);
    }
    if (is & USB_IS_RESET) {
        USB0->POWER |= USB_POWER_PWRDNPHY;
        process_bus_reset(rhport);
    }
    if (is & USB_IS_RESUME) {
        dcd_event_bus_signal(rhport, DCD_EVENT_RESUME, true);
    }
    if (is & USB_IS_SUSPEND) {
        dcd_event_bus_signal(rhport, DCD_EVENT_SUSPEND, true);
    }

    txis &= USB0->TXIE; /* Clear disabled interrupts */
    if (txis & USB_TXIE_EP0) {
        process_ep0(rhport);
        txis &= ~TU_BIT(0);
    }
    while (txis) {
        unsigned const num = __builtin_ctz(txis);
        process_edpt_n(rhport, tu_edpt_addr(num, TUSB_DIR_IN));
        txis &= ~TU_BIT(num);
    }
    rxis &= USB0->RXIE; /* Clear disabled interrupts */
    while (rxis) {
        unsigned const num = __builtin_ctz(rxis);
        process_edpt_n(rhport, tu_edpt_addr(num, TUSB_DIR_OUT));
        rxis &= ~TU_BIT(num);
    }
}
#endif
