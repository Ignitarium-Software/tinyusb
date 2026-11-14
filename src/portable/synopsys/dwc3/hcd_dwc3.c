/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Koji Kitayama
 * Portions copyrighted (c) 2021 Roland Winistoerfer
 * Copyright (c) 2025 Altera Corporation
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

// Synopsys DWC3 host controller driver (xHCI mode), built on the generic library in src/portable/xhci.
//
// Current scope: one device (no hub), MSC bulk endpoints. The xHCI root hub exposes two TinyUSB
// rhports (see DWC3_RHPORT_HS / DWC3_RHPORT_SS in the vendor header): controller init runs on the SS
// rhport, interrupts are owned by the HS rhport, and the TinyUSB rhport equals the xHCI port number.

#include "tusb_option.h"

#if CFG_TUH_ENABLED && defined(TUP_USBIP_DWC3)

#include "host/hcd.h"
#include "host/usbh.h"
#include "common/tusb_private.h"
#include "dwc3_common.h"
#include "xhci_commands.h"
#include "xhci_endpoints.h"
#include "xhci_interrupts.h"
#include "xhci_doorbell.h"
#include "xhci_events.h"

#define XHCI_SPEED_SS    (4)
#define XHCI_QUEUE_SZ    (10U)
#define XHCI_DCI_MAX     (31)

typedef struct {
  uint8_t* buffer;
  uint32_t buflen;
} dwc3_ep_buf_t;

//--------------------------------------------------------------------+
// Driver state
//--------------------------------------------------------------------+
static struct xhci_data xhci_handle TU_ATTR_ALIGNED(64);
static dwc3_ep_buf_t ep_data[XHCI_DCI_MAX];
static tusb_control_request_t ctrl_req;
static int usb_set_config = 0;
static uint8_t device_addr = 0;

// Command completion events are produced by the ISR and consumed by the task issuing the command
OSAL_QUEUE_DEF(NULL, dwc3_xhci_cmd_qdef, XHCI_QUEUE_SZ, xcc_event_t);
static osal_queue_t xhci_cmd_q;

//--------------------------------------------------------------------+
// Internal helpers
//--------------------------------------------------------------------+
static bool cmd_queue_init(void) {
  xhci_cmd_q = osal_queue_create(&dwc3_xhci_cmd_qdef);
  return xhci_cmd_q != NULL;
}

static void cmd_event_complete(xcc_event_t event, bool in_isr) {
  (void) osal_queue_send(xhci_cmd_q, &event, in_isr);
}

// Block (task context) until the command just queued completes
static int wait_for_command_completion_event(struct xhci_data* xhci_ptr, int type) {
  xcc_event_t event = {0};
  while (!osal_queue_receive(xhci_cmd_q, &event, OSAL_TIMEOUT_WAIT_FOREVER)) {}

  DEBUG("CC event values are");
  DEBUG("pointer   : %lx", event.cmd_trb_ptr);
  DEBUG("Status field  : %x", event.status_field);
  DEBUG("Control fields : %x", event.control_field);

  if (((event.status_field & 0xff000000U) >> 24) != 1U) {
    return -1;
  }

  if (type == ENABLE_SLOT_CMD) {
    // Get slot id from the CC event trb
    xhci_update_device_slot_id(&xhci_ptr->dev_data, (uint8_t) ((event.control_field & 0xff000000U) >> 24));
  }

  xhci_ptr->xcr_ring->xcr_dequeue_ptr = (xhci_trb_t*) (event.cmd_trb_ptr);
  return 0;
}

// Only the USB2 (HS) root-hub port needs an explicit reset
static void reset_usb_port(uint8_t rhport) {
  if (rhport == DWC3_RHPORT_HS) {
    reset_xhci_port(rhport);
  }
}

static bool usb_port_reset_end(uint8_t rhport) {
  if (rhport == DWC3_RHPORT_HS) {
    return is_xhci_port_reset_end(rhport);
  }
  return true;
}

static bool hcd_enable_slot(void) {
  xhci_enable_slot_command(xhci_handle.xcr_ring);
  return wait_for_command_completion_event(&xhci_handle, ENABLE_SLOT_CMD) == 0;
}

static bool hcd_send_address_cmd(void) {
  xhci_update_device_dev_speed(&xhci_handle);

  int ret = xhci_init_input_device_context(&xhci_handle);
  if (ret != 0) {
    ERROR("XHCI Error -%d!!!", ret);
    return false;
  }

  xhci_update_dcbaa_entry(&xhci_handle);
  xhci_set_device_address(&xhci_handle);

  if (wait_for_command_completion_event(&xhci_handle, ADDRESS_DEVICE_CMD) != 0) {
    return false;
  }

  xhci_update_device_address(&xhci_handle);

  if (xhci_handle.dev_data.dev_addr == 0U) {
    return false; // device address can not be zero after address command is sent
  }

  display_xhci_device_params(&xhci_handle.dev_data);
  xhci_display_ip_context(xhci_handle.ip_ctx);
  xhci_display_op_context(xhci_handle.op_ctx);
  xhci_display_event_trbs(&xhci_handle);

  return true;
}

static void hcd_xhci_set_configuration(void) {
  xhci_update_slot_context(&xhci_handle);
  xhci_init_endpoint_context(&xhci_handle, BULK_OUT);
  xhci_init_endpoint_context(&xhci_handle, BULK_IN);
  xhci_configure_endpoint(&xhci_handle);
  (void) wait_for_command_completion_event(&xhci_handle, CONFIGURE_ENDPOINT_CMD);
}

// Align EP0 max packet size of the input context with the device descriptor (Evaluate Context).
// TODO: not called yet; usbh has no hook after reading the device descriptor.
TU_ATTR_UNUSED static bool hcd_evaluate_xhci_context(void) {
  tusb_desc_device_t usb_desc;
  TU_ASSERT(tuh_descriptor_get_device_local(device_addr, &usb_desc));
  const uint16_t ep0_pkt_size =
    (uint16_t) ((xhci_handle.ip_ctx->xe_context[0].xec_info & ~EP_CTX_MAX_PKT_SIZE_MSK) >> EP_CTX_MAX_PKT_SIZE_POS);
  // USB3 encodes bMaxPacketSize0 as an exponent of 2
  const uint16_t desc_max_pkt_size = (usb_desc.bcdUSB >= 0x300U) ? (uint16_t) (1U << usb_desc.bMaxPacketSize0)
                                                                  : usb_desc.bMaxPacketSize0;

  if (ep0_pkt_size != desc_max_pkt_size) {
    xhci_update_endpoint_packetsize(xhci_handle.ip_ctx, desc_max_pkt_size);
    xhci_evaluate_endpoint(&xhci_handle);
    TU_VERIFY(wait_for_command_completion_event(&xhci_handle, EVALUATE_CONTEXT_CMD) == 0);
  }

  return true;
}

// Find the endpoint private data (transfer ring) for an endpoint address
static struct ep_priv* ep_priv_find(uint8_t ep_addr) {
  if (tu_edpt_number(ep_addr) == 0) {
    return &xhci_handle.ep0;
  }
  if (xhci_handle.msc_eps.ep_in.ep_addr == ep_addr) {
    return &xhci_handle.msc_eps.ep_in;
  }
  if (xhci_handle.msc_eps.ep_out.ep_addr == ep_addr) {
    return &xhci_handle.msc_eps.ep_out;
  }
  return NULL;
}

static void handle_endpoint_transfer(uint8_t ep_dci, uint8_t ep_addr) {
  uint8_t* buffer = ep_data[ep_dci].buffer;
  uint32_t buflen = ep_data[ep_dci].buflen;

  if ((tu_edpt_number(ep_addr) == 0 && buflen != 0) || tu_edpt_dir(ep_addr) == TUSB_DIR_IN) {
    dwc3_dcache_invalidate(buffer, buflen);
  }
}

//--------------------------------------------------------------------+
// Controller API
//--------------------------------------------------------------------+

// Initialize controller to host mode. The whole controller is brought up on the SS rhport.
bool hcd_init(uint8_t rhport, const tusb_rhport_init_t* rh_init) {
  (void) rh_init;

  if (rhport != DWC3_RHPORT_SS) {
    return true;
  }

  TU_ASSERT(dwc3_mcu_init(rhport));

  if (!cmd_queue_init()) {
    ERROR("Error in creating xHCI command queue");
    return false;
  }

  int ret = dwc3_init();
  if (ret != 0) {
    ERROR("dwc3 Error -%d!!!", ret);
    return false;
  }

  tu_memclr(&xhci_handle, sizeof(xhci_handle));

  if (!xhci_init(&xhci_handle)) {
    ERROR("xHCI init failed !!!");
    return false;
  }

  return true;
}

// Interrupts are owned by the HS rhport
void hcd_int_enable(uint8_t rhport) {
  if (rhport == DWC3_RHPORT_HS) {
    enable_xhci_interrupts();
    (void) dwc3_int_set(rhport, true);
  }
}

void hcd_int_disable(uint8_t rhport) {
  if (rhport == DWC3_RHPORT_HS) {
    (void) dwc3_int_set(rhport, false);
  }
}

// Get frame number (1ms): MFINDEX counts 125us micro-frames
uint32_t hcd_frame_number(uint8_t rhport) {
  (void) rhport;
  return xhci_get_mfindex() >> 3;
}

//--------------------------------------------------------------------+
// Port API
//--------------------------------------------------------------------+

// PORTSC.CCS of the root-hub port
bool hcd_port_connect_status(uint8_t rhport) {
  return xhci_port_status(rhport);
}

void hcd_port_reset(uint8_t rhport) {
  reset_usb_port(rhport);
}

// Completes the reset, then enables a slot and addresses the device (xHCI assigns the address)
void hcd_port_reset_end(uint8_t rhport) {
  TU_ASSERT(usb_port_reset_end(rhport), );
  TU_ASSERT(hcd_enable_slot(), );
  TU_ASSERT(hcd_send_address_cmd(), );
}

tusb_speed_t hcd_port_speed_get(uint8_t rhport) {
  switch (xhci_get_port_speed(rhport)) {
    case 4: return TUSB_SPEED_SS;
    case 3: return TUSB_SPEED_HIGH;
    case 2: return TUSB_SPEED_FULL;
    case 1: return TUSB_SPEED_LOW;
    default: return TUSB_SPEED_INVALID;
  }
}

// Release the slot of the (single) device. usbh also closes the default address 0 during enumeration;
// that must not tear down the slot that is being enumerated.
void hcd_device_close(uint8_t rhport, uint8_t dev_addr) {
  if (dev_addr == 0 || dev_addr != device_addr) {
    return;
  }

  if (rhport == DWC3_RHPORT_SS) {
    xhci_warm_reset(rhport); // warm reset for usb3 ports only
  }

  const uint32_t slotid = xhci_handle.dev_data.slot_id;
  if (slotid != 0U) {
    xhci_disable_slot_command(xhci_handle.xcr_ring, slotid);

    if (wait_for_command_completion_event(&xhci_handle, DISABLE_SLOT_CMD) != 0) {
      ERROR("xHCI command failed");
      return;
    }

    deallocate_xhci_context(&xhci_handle);
    device_addr = 0U;
    usb_set_config = 0;
  }
}

//--------------------------------------------------------------------+
// Endpoints API
//--------------------------------------------------------------------+

// Endpoint contexts are configured from the full configuration descriptor, see
// hcd_parse_full_conf_descriptor(), so there is nothing to do per endpoint here
bool hcd_edpt_open(uint8_t rhport, uint8_t dev_addr, const tusb_desc_endpoint_t* ep_desc) {
  (void) rhport;
  (void) dev_addr;
  (void) ep_desc;
  return true;
}

// Not supported: dropping a single endpoint needs a Configure Endpoint command with drop flags,
// which the xHCI library does not implement yet. Endpoints are released by hcd_device_close().
bool hcd_edpt_close(uint8_t rhport, uint8_t dev_addr, uint8_t ep_addr) {
  (void) rhport;
  (void) dev_addr;
  (void) ep_addr;
  return false;
}

bool hcd_setup_send(uint8_t rhport, uint8_t dev_addr, const uint8_t setup_packet[8]) {
  (void) rhport;
  memcpy(&ctrl_req, setup_packet, sizeof(ctrl_req));

  if ((tusb_request_code_t) setup_packet[1] == TUSB_REQ_SET_CONFIGURATION) {
    hcd_xhci_set_configuration();
    usb_set_config = 1;
  }

  if ((tusb_request_code_t) setup_packet[1] == TUSB_REQ_SET_ADDRESS) {
    device_addr = (uint8_t) ctrl_req.wValue;
  }

  // xHCI sends setup + data + status as one TD, the data stage is queued by hcd_edpt_xfer()
  hcd_event_xfer_complete(dev_addr, 0, 8, XFER_RESULT_SUCCESS, true);
  return true;
}

bool hcd_edpt_xfer(uint8_t rhport, uint8_t dev_addr, uint8_t ep_addr, uint8_t* buffer, uint32_t buflen) {
  (void) rhport;
  const uint8_t ep_num = tu_edpt_number(ep_addr);
  const uint8_t dir = (uint8_t) tu_edpt_dir(ep_addr);
  const uint8_t ep_dci = xhci_get_ep_dci(ep_addr);

  // There is no separate status stage for the xHCI controller: complete it immediately
  if (buffer == NULL && buflen == 0 && usb_set_config == 0) {
    hcd_event_xfer_complete(dev_addr, ep_num, 8, XFER_RESULT_SUCCESS, true);
    return true;
  }

  TU_ASSERT(ep_dci < XHCI_DCI_MAX);
  ep_data[ep_dci].buffer = buffer;
  ep_data[ep_dci].buflen = buflen;

  if (ep_num == 0) {
    xhci_configure_setup_stage(&xhci_handle, buffer, (usb_control_request_t*) &ctrl_req);
    ring_xhci_ep0_db(&xhci_handle.op_regs);
  } else {
    if (dir == TUSB_DIR_OUT) {
      dwc3_dcache_clean(buffer, buflen);
    }
    xhci_endpoint_transfer(&xhci_handle, (int) ep_num, dir, buffer, buflen);
  }

  return true;
}

// Not supported: aborting needs Stop Endpoint + Set TR Dequeue on the endpoint ring
bool hcd_edpt_abort_xfer(uint8_t rhport, uint8_t dev_addr, uint8_t ep_addr) {
  (void) rhport;
  (void) dev_addr;
  (void) ep_addr;
  return false;
}

// Clear the Halted state after a STALL: Reset Endpoint (also resets the sequence number),
// then point the dequeue pointer at the current enqueue pointer to skip the stalled TD.
bool hcd_edpt_clear_stall(uint8_t rhport, uint8_t dev_addr, uint8_t ep_addr) {
  (void) rhport;
  (void) dev_addr;

  struct ep_priv* ep = ep_priv_find(ep_addr);
  TU_VERIFY(ep != NULL && ep->ep_tr_enq_ptr != NULL);

  const uint8_t slot_id = xhci_handle.dev_data.slot_id;
  const uint8_t dci = xhci_get_ep_dci(ep_addr);

  xhci_reset_endpoint_command(xhci_handle.xcr_ring, slot_id, dci);
  TU_VERIFY(wait_for_command_completion_event(&xhci_handle, RESET_ENDPOINT_CMD) == 0);

  xhci_set_tr_dequeue_command(xhci_handle.xcr_ring, slot_id, dci, ep->ep_tr_enq_ptr, ep->pcs_flag);
  TU_VERIFY(wait_for_command_completion_event(&xhci_handle, SET_TR_DEQUEUE_PTR_CMD) == 0);

  return true;
}

// Configure the endpoint contexts from the full configuration descriptor (optional HCD op).
bool hcd_parse_full_conf_descriptor(tusb_desc_configuration_t* desc_cfg, uint8_t rhport) {
  (void) rhport;
  const uint8_t usb_speed = xhci_handle.dev_data.dev_speed;

  uint16_t const total_len = tu_le16toh(desc_cfg->wTotalLength);
  uint8_t const* desc_end = ((uint8_t const*) desc_cfg) + total_len;
  uint8_t const* p_desc = tu_desc_next(desc_cfg);
  uint8_t assoc_itf_count = 1;
  uint32_t err_flag = 0U;

  usb_endpoint_descriptor_t xhci_ep_desc;

  DEBUG("Parsing Complete Configuration Descriptors");

  while (p_desc < desc_end) {
    TU_ASSERT(TUSB_DESC_INTERFACE == tu_desc_type(p_desc));

    tusb_desc_interface_t const* desc_itf = (tusb_desc_interface_t const*) (uintptr_t) p_desc;

    // Only MSC is supported for now
    if (desc_itf->bInterfaceClass != TUSB_CLASS_MSC) {
      PRINT("Device does not support MSC");
      PRINT("Enumeration process completed");
      return false;
    }

    uint16_t const drv_len =
      tu_desc_get_interface_total_len(desc_itf, assoc_itf_count, (uint16_t) (desc_end - p_desc));

    tusb_desc_endpoint_t const* ep_desc = (tusb_desc_endpoint_t const*) (uintptr_t) tu_desc_next(desc_itf);

    for (int i = 0; i < 2; i++) {
      TU_ASSERT(TUSB_DESC_ENDPOINT == ep_desc->bDescriptorType && TUSB_XFER_BULK == ep_desc->bmAttributes.xfer);

      xhci_ep_desc.bLength = ep_desc->bLength;
      xhci_ep_desc.bDescriptorType = ep_desc->bDescriptorType;
      xhci_ep_desc.bEndpointAddress = ep_desc->bEndpointAddress;
      (void) memcpy(&xhci_ep_desc.bmAttributes, &ep_desc->bmAttributes, sizeof(xhci_ep_desc.bmAttributes));
      xhci_ep_desc.wMaxPacketSize = ep_desc->wMaxPacketSize;
      xhci_ep_desc.bInterval = ep_desc->bInterval;

      ep_desc = (tusb_desc_endpoint_t const*) (uintptr_t) tu_desc_next(ep_desc);
      if (usb_speed == XHCI_SPEED_SS) {
        // skip the SuperSpeed endpoint companion descriptor
        ep_desc = (tusb_desc_endpoint_t const*) (uintptr_t) tu_desc_next(ep_desc);
      }

      if (xhci_parse_endpoint_descriptor(&xhci_handle, &xhci_ep_desc) != 0) {
        ERROR("Failed to parse endpoint descriptor");
        return false;
      }
      err_flag = 1U;
    }

    p_desc += drv_len;
  }

  return err_flag != 0U;
}

//--------------------------------------------------------------------+
// Interrupt
//--------------------------------------------------------------------+

// Translate xHCI DCI to TinyUSB endpoint address
static const uint8_t DCI2EP[30] = {
  0x00, 0x01, 0x81, 0x02, 0x82, 0x03, 0x83,
  0x04, 0x84, 0x05, 0x85, 0x06, 0x86
};

void hcd_int_handler(uint8_t rhport, bool in_isr) {
  (void) rhport;

  // ack USBSTS/IMAN; on controller error the xHCI is restarted and there is nothing to process
  if (!xhci_irq_ack()) {
    return;
  }

  xhci_event_trb_t event_data = xhci_get_event(&xhci_handle);
  const xhci_event_trb_type_t trb_id = (xhci_event_trb_type_t) event_data.event_trb.trb_control_field.trb_type;

  switch (trb_id) {
    case TRANSFER_EVENT: {
      xtc_event_t tr_event = event_data.tr_event;
      const int ep_dci = (int) tr_event.tc_ctrl_params.ep_dci;
      if (ep_dci < 1 || ep_dci > (int) TU_ARRAY_SIZE(DCI2EP)) {
        break;
      }
      const uint8_t ep_addr = DCI2EP[ep_dci - 1];

      if (tr_event.tc_status_params.compl_code == (uint32_t) EVENT_SUCCESS) {
        const uint32_t xfer_bytes = tr_event.tc_status_params.transfer_len;
        handle_endpoint_transfer((uint8_t) ep_dci, ep_addr);
        hcd_event_xfer_complete(device_addr, ep_addr, xfer_bytes, XFER_RESULT_SUCCESS, in_isr);
      } else if (tr_event.tc_status_params.compl_code == (uint32_t) STALL_ERROR) {
        hcd_event_xfer_complete(device_addr, ep_addr, 0, XFER_RESULT_STALLED, in_isr);
      } else {
        // other completion codes are not reported yet (unchanged from the previous port)
      }
      break;
    }

    case PORT_STATUS_CHANGE_EVENT: {
      const xhci_psceg_params_t rh_params = xhci_handle_psceg_event(event_data.psc_event);

      // RH port id should be always less than maximum supported port
      if ((rh_params.rhport < 1U) || (rh_params.rhport > xhci_handle.xhc_cap_ptr->hcsparams1_params.max_ports)) {
        break;
      }
      if (rh_params.dev_attach_flag == 1) {
        hcd_event_device_attach((uint8_t) rh_params.rhport, in_isr);
        xhci_update_device_rh_params(&xhci_handle, rh_params);
      } else if (rh_params.dev_attach_flag == -1) {
        hcd_event_device_remove((uint8_t) rh_params.rhport, in_isr);
      } else {
        // Nothing to be handled for tinyusb stack
      }
      break;
    }

    case COMMAND_COMPLETION_EVENT:
      cmd_event_complete(event_data.cc_event, in_isr);
      break;

    default:
      break;
  }
}

#endif
