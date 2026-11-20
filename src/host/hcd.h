/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
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

#ifndef _TUSB_HCD_H_
#define _TUSB_HCD_H_

#include "common/tusb_common.h"
#include "osal/osal.h"
#include "common/tusb_fifo.h"

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(TUH_HCD_NAME) && !CFG_TUH_HCD_MULTI
  #error "TUH_HCD_NAME / host/hcd_rename.h used while CFG_TUH_HCD_MULTI == 0"
#endif

//--------------------------------------------------------------------+
// Configuration
//--------------------------------------------------------------------+

// Max number of endpoints pair per device
// TODO optimize memory usage
#ifndef CFG_TUH_ENDPOINT_MAX
  #define CFG_TUH_ENDPOINT_MAX   16
//  #ifdef TUP_HCD_ENDPOINT_MAX
//    #define CFG_TUH_ENDPPOINT_MAX   TUP_HCD_ENDPOINT_MAX
//  #else
//    #define
//  #endif
#endif

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF
//--------------------------------------------------------------------+
typedef enum {
  HCD_EVENT_DEVICE_ATTACH,
  HCD_EVENT_DEVICE_REMOVE,
  HCD_EVENT_XFER_COMPLETE,

  USBH_EVENT_FUNC_CALL, // Not an HCD event
  HCD_EVENT_COUNT
} hcd_eventid_t;

typedef struct {
  uint8_t rhport;
  uint8_t event_id;
  uint8_t dev_addr;

  union {
    // Attach, Remove
    struct {
      uint8_t hub_addr;
      uint8_t hub_port;
      uint8_t speed;
    } connection;

    // XFER_COMPLETE
    struct {
      uint8_t ep_addr;
      uint8_t result;
      uint32_t len;
    } xfer_complete;

    // FUNC_CALL
    struct {
      void (*func) (void*);
      void* param;
    }func_call;
  };
} hcd_event_t;

//--------------------------------------------------------------------+
// Memory API
//--------------------------------------------------------------------+

// clean/flush data cache: write cache -> memory.
// Required before an DMA TX transfer to make sure data is in memory
bool hcd_dcache_clean(void const* addr, uint32_t data_size);

// invalidate data cache: mark cache as invalid, next read will read from memory
// Required BOTH before and after an DMA RX transfer
bool hcd_dcache_invalidate(void const* addr, uint32_t data_size);

// clean and invalidate data cache
// Required before an DMA transfer where memory is both read/write by DMA
bool hcd_dcache_clean_invalidate(void const* addr, uint32_t data_size);

//--------------------------------------------------------------------+
// Controller API
//--------------------------------------------------------------------+

// optional hcd configuration, called by tuh_configure()
bool hcd_configure(uint8_t rhport, uint32_t cfg_id, const void* cfg_param);

// Initialize controller to host mode
bool hcd_init(uint8_t rhport, const tusb_rhport_init_t* rh_init);

// De-initialize controller
bool hcd_deinit(uint8_t rhport);

// Interrupt Handler
void hcd_int_handler(uint8_t rhport, bool in_isr);

// Enable USB interrupt
void hcd_int_enable (uint8_t rhport);

// Disable USB interrupt
void hcd_int_disable(uint8_t rhport);

// Get frame number (1ms)
uint32_t hcd_frame_number(uint8_t rhport);

//--------------------------------------------------------------------+
// Port API
//--------------------------------------------------------------------+

// Get the current connect status of roothub port
bool hcd_port_connect_status(uint8_t rhport);

// Reset USB bus on the port. Return immediately, bus reset sequence may not be complete.
// Some port would require hcd_port_reset_end() to be invoked after 10ms to complete the reset sequence.
void hcd_port_reset(uint8_t rhport);

// Complete bus reset sequence, may be required by some controllers
void hcd_port_reset_end(uint8_t rhport);

// Get port link speed
tusb_speed_t hcd_port_speed_get(uint8_t rhport);

// HCD closes all opened endpoints belong to this device
void hcd_device_close(uint8_t rhport, uint8_t dev_addr);

//--------------------------------------------------------------------+
// Endpoints API
//--------------------------------------------------------------------+

// Open an endpoint
// return true if successfully opened or endpoint is currently opened
bool hcd_edpt_open(uint8_t rhport, uint8_t daddr, tusb_desc_endpoint_t const * ep_desc);

// Close an endpoint
bool hcd_edpt_close(uint8_t rhport, uint8_t daddr, uint8_t ep_addr);

// Submit a transfer, when complete hcd_event_xfer_complete() must be invoked
bool hcd_edpt_xfer(uint8_t rhport, uint8_t daddr, uint8_t ep_addr, uint8_t * buffer, uint32_t buflen);

// Abort a queued transfer. Note: it can only abort transfer that has not been started
// Return true if a queued transfer is aborted, false if there is no transfer to abort
bool hcd_edpt_abort_xfer(uint8_t rhport, uint8_t dev_addr, uint8_t ep_addr);

// Submit a special transfer to send 8-byte Setup Packet, when complete hcd_event_xfer_complete() must be invoked
bool hcd_setup_send(uint8_t rhport, uint8_t daddr, uint8_t const setup_packet[8]);

// clear stall, data toggle is also reset to DATA0
bool hcd_edpt_clear_stall(uint8_t rhport, uint8_t dev_addr, uint8_t ep_addr);

// [optional] configure endpoints from the full configuration descriptor before SET_CONFIGURATION
// completes (needed by xHCI). Default (weak, in usbh.c) returns true.
bool hcd_parse_full_conf_descriptor(tusb_desc_configuration_t *desc_cfg, uint8_t rhport);

//--------------------------------------------------------------------+
// Multiple HCD support (CFG_TUH_HCD_MULTI), see host/hcd_rename.h
//--------------------------------------------------------------------+
#if CFG_TUH_HCD_MULTI

typedef struct {
  const char* name;                                                     // "dwc2", "dwc3" (debug/logging)
  bool     (*configure)(uint8_t, uint32_t, const void*);                // optional
  bool     (*init)(uint8_t, const tusb_rhport_init_t*);
  bool     (*deinit)(uint8_t);                                          // optional
  void     (*int_handler)(uint8_t, bool);
  void     (*int_enable)(uint8_t);
  void     (*int_disable)(uint8_t);
  uint32_t (*frame_number)(uint8_t);                                    // optional
  bool     (*port_connect_status)(uint8_t);
  void     (*port_reset)(uint8_t);
  void     (*port_reset_end)(uint8_t);
  tusb_speed_t (*port_speed_get)(uint8_t);
  void     (*device_close)(uint8_t, uint8_t);
  bool     (*edpt_open)(uint8_t, uint8_t, tusb_desc_endpoint_t const*);
  bool     (*edpt_close)(uint8_t, uint8_t, uint8_t);                    // optional
  bool     (*edpt_xfer)(uint8_t, uint8_t, uint8_t, uint8_t*, uint32_t);
  bool     (*edpt_abort_xfer)(uint8_t, uint8_t, uint8_t);               // optional
  bool     (*setup_send)(uint8_t, uint8_t, uint8_t const[8]);
  bool     (*edpt_clear_stall)(uint8_t, uint8_t, uint8_t);              // optional
  bool     (*parse_full_conf_descriptor)(tusb_desc_configuration_t*, uint8_t); // optional
} hcd_driver_t;

// Per-rhport driver table, provided by the application/BSP (NULL for unused rhports)
extern hcd_driver_t const* const tuh_hcd_drivers[CFG_TUH_HCD_MULTI_COUNT];

#define _TUH_HCD_FN(_n, _o)  hcd_##_n##_##_o

// Prototypes of the renamed API of driver _n. Optional ops are weak: unimplemented ones resolve to NULL.
#define TUH_HCD_DRIVER_DECLARE(_n) \
  TU_ATTR_WEAK bool _TUH_HCD_FN(_n, configure)(uint8_t rhport, uint32_t cfg_id, const void* cfg_param); \
  bool _TUH_HCD_FN(_n, init)(uint8_t rhport, const tusb_rhport_init_t* rh_init); \
  TU_ATTR_WEAK bool _TUH_HCD_FN(_n, deinit)(uint8_t rhport); \
  void _TUH_HCD_FN(_n, int_handler)(uint8_t rhport, bool in_isr); \
  void _TUH_HCD_FN(_n, int_enable)(uint8_t rhport); \
  void _TUH_HCD_FN(_n, int_disable)(uint8_t rhport); \
  TU_ATTR_WEAK uint32_t _TUH_HCD_FN(_n, frame_number)(uint8_t rhport); \
  bool _TUH_HCD_FN(_n, port_connect_status)(uint8_t rhport); \
  void _TUH_HCD_FN(_n, port_reset)(uint8_t rhport); \
  void _TUH_HCD_FN(_n, port_reset_end)(uint8_t rhport); \
  tusb_speed_t _TUH_HCD_FN(_n, port_speed_get)(uint8_t rhport); \
  void _TUH_HCD_FN(_n, device_close)(uint8_t rhport, uint8_t dev_addr); \
  bool _TUH_HCD_FN(_n, edpt_open)(uint8_t rhport, uint8_t daddr, tusb_desc_endpoint_t const* ep_desc); \
  TU_ATTR_WEAK bool _TUH_HCD_FN(_n, edpt_close)(uint8_t rhport, uint8_t daddr, uint8_t ep_addr); \
  bool _TUH_HCD_FN(_n, edpt_xfer)(uint8_t rhport, uint8_t daddr, uint8_t ep_addr, uint8_t* buffer, uint32_t buflen); \
  TU_ATTR_WEAK bool _TUH_HCD_FN(_n, edpt_abort_xfer)(uint8_t rhport, uint8_t daddr, uint8_t ep_addr); \
  bool _TUH_HCD_FN(_n, setup_send)(uint8_t rhport, uint8_t daddr, uint8_t const setup_packet[8]); \
  TU_ATTR_WEAK bool _TUH_HCD_FN(_n, edpt_clear_stall)(uint8_t rhport, uint8_t daddr, uint8_t ep_addr); \
  TU_ATTR_WEAK bool _TUH_HCD_FN(_n, parse_full_conf_descriptor)(tusb_desc_configuration_t* desc_cfg, uint8_t rhport)

// Defines `hcd_driver_t const hcd_<_n>_driver` with every op of driver _n (use in BSP/application only)
#define TUH_HCD_DRIVER_DEFINE(_n) \
  TUH_HCD_DRIVER_DECLARE(_n); \
  hcd_driver_t const hcd_##_n##_driver = { \
    .name                       = #_n, \
    .configure                  = _TUH_HCD_FN(_n, configure), \
    .init                       = _TUH_HCD_FN(_n, init), \
    .deinit                     = _TUH_HCD_FN(_n, deinit), \
    .int_handler                = _TUH_HCD_FN(_n, int_handler), \
    .int_enable                 = _TUH_HCD_FN(_n, int_enable), \
    .int_disable                = _TUH_HCD_FN(_n, int_disable), \
    .frame_number               = _TUH_HCD_FN(_n, frame_number), \
    .port_connect_status        = _TUH_HCD_FN(_n, port_connect_status), \
    .port_reset                 = _TUH_HCD_FN(_n, port_reset), \
    .port_reset_end             = _TUH_HCD_FN(_n, port_reset_end), \
    .port_speed_get             = _TUH_HCD_FN(_n, port_speed_get), \
    .device_close               = _TUH_HCD_FN(_n, device_close), \
    .edpt_open                  = _TUH_HCD_FN(_n, edpt_open), \
    .edpt_close                 = _TUH_HCD_FN(_n, edpt_close), \
    .edpt_xfer                  = _TUH_HCD_FN(_n, edpt_xfer), \
    .edpt_abort_xfer            = _TUH_HCD_FN(_n, edpt_abort_xfer), \
    .setup_send                 = _TUH_HCD_FN(_n, setup_send), \
    .edpt_clear_stall           = _TUH_HCD_FN(_n, edpt_clear_stall), \
    .parse_full_conf_descriptor = _TUH_HCD_FN(_n, parse_full_conf_descriptor), \
  }

// Log every rhport entry and which optional ops are present (CFG_TUSB_DEBUG >= 2)
void tuh_hcd_multi_log(void);

#endif // CFG_TUH_HCD_MULTI

//--------------------------------------------------------------------+
// USBH implemented API
//--------------------------------------------------------------------+

// Called by HCD to notify stack
extern void hcd_event_handler(hcd_event_t const* event, bool in_isr);

// Helper to send device attach event
TU_ATTR_ALWAYS_INLINE static inline
void hcd_event_device_attach(uint8_t rhport, bool in_isr) {
  hcd_event_t event;
  event.rhport              = rhport;
  event.event_id            = HCD_EVENT_DEVICE_ATTACH;
  event.connection.hub_addr = 0;
  event.connection.hub_port = 0;

  hcd_event_handler(&event, in_isr);
}

// Helper to send device removal event
TU_ATTR_ALWAYS_INLINE static inline
void hcd_event_device_remove(uint8_t rhport, bool in_isr) {
  hcd_event_t event;
  event.rhport              = rhport;
  event.event_id            = HCD_EVENT_DEVICE_REMOVE;
  event.connection.hub_addr = 0;
  event.connection.hub_port = 0;

  hcd_event_handler(&event, in_isr);
}

// Helper to send USB transfer event
TU_ATTR_ALWAYS_INLINE static inline
void hcd_event_xfer_complete(uint8_t dev_addr, uint8_t ep_addr, uint32_t xferred_bytes, xfer_result_t result, bool in_isr) {
  hcd_event_t event = {
    .rhport   = 0, // TODO correct rhport
    .event_id = HCD_EVENT_XFER_COMPLETE,
    .dev_addr = dev_addr,
  };
  event.xfer_complete.ep_addr = ep_addr;
  event.xfer_complete.result = result;
  event.xfer_complete.len = xferred_bytes;

  hcd_event_handler(&event, in_isr);
}

#ifdef __cplusplus
 }
#endif

#endif
