/*
 * The MIT License (MIT)
 *
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

// Standard hcd_* API for CFG_TUH_HCD_MULTI builds: each call is dispatched by rhport to the driver
// registered in tuh_hcd_drivers[]. Missing optional ops return the same default as the weak stubs
// in usbh.c. See host/hcd_rename.h for the overall design.

#include "tusb_option.h"

#if CFG_TUH_ENABLED && CFG_TUH_HCD_MULTI

#include "host/hcd.h"

//--------------------------------------------------------------------+
// Helper
//--------------------------------------------------------------------+
TU_ATTR_ALWAYS_INLINE static inline hcd_driver_t const* hcd_drv(uint8_t rhport) {
  return (rhport < CFG_TUH_HCD_MULTI_COUNT) ? tuh_hcd_drivers[rhport] : NULL;
}

// Fetch the driver of rhport, or assert and return _ret if the rhport has no driver
#define HCD_DRV_OR_RETURN(_drv, _rhport, _ret)    \
  hcd_driver_t const* _drv = hcd_drv(_rhport);    \
  TU_ASSERT(_drv != NULL, _ret)

#define HCD_DRV_OR_RETURN_VOID(_drv, _rhport)     \
  hcd_driver_t const* _drv = hcd_drv(_rhport);    \
  TU_ASSERT(_drv != NULL, )

void tuh_hcd_multi_log(void) {
#if CFG_TUSB_DEBUG >= 2
  #define _HCD_OP_STR(_d, _op) ((_d)->_op ? "y" : "-")
  TU_LOG2("HCD multi: %u rhport entries\r\n", (unsigned) CFG_TUH_HCD_MULTI_COUNT);
  for (uint8_t i = 0; i < CFG_TUH_HCD_MULTI_COUNT; i++) {
    hcd_driver_t const* d = tuh_hcd_drivers[i];
    if (d == NULL) {
      TU_LOG2("  rhport %u: none\r\n", i);
      continue;
    }
    TU_LOG2("  rhport %u: %s  configure=%s deinit=%s frame_number=%s edpt_close=%s abort=%s clear_stall=%s"
            " parse_conf=%s\r\n",
            i, d->name, _HCD_OP_STR(d, configure), _HCD_OP_STR(d, deinit), _HCD_OP_STR(d, frame_number),
            _HCD_OP_STR(d, edpt_close), _HCD_OP_STR(d, edpt_abort_xfer), _HCD_OP_STR(d, edpt_clear_stall),
            _HCD_OP_STR(d, parse_full_conf_descriptor));
  }
  #undef _HCD_OP_STR
#endif
}

//--------------------------------------------------------------------+
// Controller API
//--------------------------------------------------------------------+
bool hcd_configure(uint8_t rhport, uint32_t cfg_id, const void* cfg_param) {
  HCD_DRV_OR_RETURN(drv, rhport, false);
  return drv->configure ? drv->configure(rhport, cfg_id, cfg_param) : false;
}

bool hcd_init(uint8_t rhport, const tusb_rhport_init_t* rh_init) {
  static bool logged = false;
  if (!logged) {
    logged = true;
    tuh_hcd_multi_log();
  }

  HCD_DRV_OR_RETURN(drv, rhport, false);
  return drv->init(rhport, rh_init);
}

bool hcd_deinit(uint8_t rhport) {
  HCD_DRV_OR_RETURN(drv, rhport, false);
  return drv->deinit ? drv->deinit(rhport) : false;
}

// Called from the controller ISR: table lookup + call only, nothing blocking
void hcd_int_handler(uint8_t rhport, bool in_isr) {
  HCD_DRV_OR_RETURN_VOID(drv, rhport);
  drv->int_handler(rhport, in_isr);
}

void hcd_int_enable(uint8_t rhport) {
  HCD_DRV_OR_RETURN_VOID(drv, rhport);
  drv->int_enable(rhport);
}

void hcd_int_disable(uint8_t rhport) {
  HCD_DRV_OR_RETURN_VOID(drv, rhport);
  drv->int_disable(rhport);
}

uint32_t hcd_frame_number(uint8_t rhport) {
  HCD_DRV_OR_RETURN(drv, rhport, 0);
  return drv->frame_number ? drv->frame_number(rhport) : 0;
}

//--------------------------------------------------------------------+
// Port API
//--------------------------------------------------------------------+
bool hcd_port_connect_status(uint8_t rhport) {
  HCD_DRV_OR_RETURN(drv, rhport, false);
  return drv->port_connect_status(rhport);
}

void hcd_port_reset(uint8_t rhport) {
  HCD_DRV_OR_RETURN_VOID(drv, rhport);
  drv->port_reset(rhport);
}

void hcd_port_reset_end(uint8_t rhport) {
  HCD_DRV_OR_RETURN_VOID(drv, rhport);
  drv->port_reset_end(rhport);
}

tusb_speed_t hcd_port_speed_get(uint8_t rhport) {
  HCD_DRV_OR_RETURN(drv, rhport, TUSB_SPEED_INVALID);
  return drv->port_speed_get(rhport);
}

void hcd_device_close(uint8_t rhport, uint8_t dev_addr) {
  HCD_DRV_OR_RETURN_VOID(drv, rhport);
  drv->device_close(rhport, dev_addr);
}

//--------------------------------------------------------------------+
// Endpoints API
//--------------------------------------------------------------------+
bool hcd_edpt_open(uint8_t rhport, uint8_t daddr, tusb_desc_endpoint_t const* ep_desc) {
  HCD_DRV_OR_RETURN(drv, rhport, false);
  return drv->edpt_open(rhport, daddr, ep_desc);
}

bool hcd_edpt_close(uint8_t rhport, uint8_t daddr, uint8_t ep_addr) {
  HCD_DRV_OR_RETURN(drv, rhport, false);
  return drv->edpt_close ? drv->edpt_close(rhport, daddr, ep_addr) : false;
}

bool hcd_edpt_xfer(uint8_t rhport, uint8_t daddr, uint8_t ep_addr, uint8_t* buffer, uint32_t buflen) {
  HCD_DRV_OR_RETURN(drv, rhport, false);
  return drv->edpt_xfer(rhport, daddr, ep_addr, buffer, buflen);
}

bool hcd_edpt_abort_xfer(uint8_t rhport, uint8_t daddr, uint8_t ep_addr) {
  HCD_DRV_OR_RETURN(drv, rhport, false);
  return drv->edpt_abort_xfer ? drv->edpt_abort_xfer(rhport, daddr, ep_addr) : false;
}

bool hcd_setup_send(uint8_t rhport, uint8_t daddr, uint8_t const setup_packet[8]) {
  HCD_DRV_OR_RETURN(drv, rhport, false);
  return drv->setup_send(rhport, daddr, setup_packet);
}

bool hcd_edpt_clear_stall(uint8_t rhport, uint8_t daddr, uint8_t ep_addr) {
  HCD_DRV_OR_RETURN(drv, rhport, false);
  return drv->edpt_clear_stall ? drv->edpt_clear_stall(rhport, daddr, ep_addr) : false;
}

bool hcd_parse_full_conf_descriptor(tusb_desc_configuration_t* desc_cfg, uint8_t rhport) {
  HCD_DRV_OR_RETURN(drv, rhport, false);
  return drv->parse_full_conf_descriptor ? drv->parse_full_conf_descriptor(desc_cfg, rhport) : true;
}

#endif
